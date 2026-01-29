#include "Platform_Types.h"
#include "Soc_Cfg.h"

/* =========================================================
 * Estimator Layer: only calculates (no state apply here)
 *  - Input validity check (basic range)
 *  - Coulomb Counting delta SoC calculation
 *  - OCV->SoC estimation (linear interpolation)
 * ========================================================= */

/* =========================================================
 *  Internal constants (formula / scale constants)
 *  - 튜닝 값이 아닌 “수식 상수”라 Cfg로 올리지 않음
 * ========================================================= */

/* Coulomb Counting constants
 * SOC(x10) 계산:
 *   deltaSOC[x10] = -I(mA) * dt(ms) / (Q_mAh * 3600)
 *
 * Q_mAh:
 *   Ah_x10 = Ah * 10
 *   Ah = Ah_x10 / 10
 *   mAh = Ah * 1000 = Ah_x10 * 100
 *
 * denom = Ah_x10 * 100 * 3600 = Ah_x10 * 360000
 */
#define BMS_SOC_CC_DENOM_FACTOR            (360000L)    /* 100 * 3600 */
#define BMS_SOC_MS_PER_SEC                 (1000u)

/* OCV table safety */
#define BMS_SOC_OCV_MIN_POINTS             (2u)

/* =========================================================
 *  Local helpers
 * ========================================================= */
static sint16 BmsSoc_AbsS16(sint16 v)
{
    return (v >= 0) ? v : (sint16)(-v);
}

static uint16 BmsSoc_ClampU16(uint16 v, uint16 lo, uint16 hi)
{
    if (v < lo) { return lo; }
    if (v > hi) { return hi; }
    return v;
}

static sint16 BmsSoc_ClampS16(sint16 v, sint16 lo, sint16 hi)
{
    if (v < lo) { return lo; }
    if (v > hi) { return hi; }
    return v;
}

/* OCV 테이블 보간
 * - 입력: packVoltage_mV
 * - 출력: soc_x10 (0~1000)
 * - 테이블은 증가형(OCV가 SOC와 함께 증가) 가정
 */
static uint16 BmsSoc_InterpSocFromOcv(uint16 packVoltage_mV)
{
    uint16 i;

    if (BMS_SOC_OCV_POINTS < BMS_SOC_OCV_MIN_POINTS)
    {
        /* 테이블이 비정상이면 보수적으로 default 반환 */
        return BMS_SOC_INVALID_DEFAULT_X10;
    }

    /* below minimum */
    if (packVoltage_mV <= BmsSoc_OcvTable_mV[0])
    {
        return BmsSoc_OcvSocBp_X10[0];
    }

    /* above maximum */
    if (packVoltage_mV >= BmsSoc_OcvTable_mV[BMS_SOC_OCV_POINTS - 1u])
    {
        return BmsSoc_OcvSocBp_X10[BMS_SOC_OCV_POINTS - 1u];
    }

    /* find segment and interpolate */
    for (i = 0u; i < (BMS_SOC_OCV_POINTS - 1u); i++)
    {
        const uint16 v0 = BmsSoc_OcvTable_mV[i];
        const uint16 v1 = BmsSoc_OcvTable_mV[i + 1u];

        if ((packVoltage_mV >= v0) && (packVoltage_mV <= v1))
        {
            const uint16 s0 = BmsSoc_OcvSocBp_X10[i];
            const uint16 s1 = BmsSoc_OcvSocBp_X10[i + 1u];

            const uint16 dv = (uint16)(v1 - v0);
            const uint16 dx = (uint16)(packVoltage_mV - v0);

            /* linear interpolation:
             *   s = s0 + (s1-s0) * dx / dv
             */
            if (dv == 0u)
            {
                /* 테이블 이상(중복 전압) 방지 */
                return s0;
            }
            else
            {
                const uint32 num = (uint32)(s1 - s0) * (uint32)dx;
                const uint16 add = (uint16)(num / (uint32)dv);
                return (uint16)(s0 + add);
            }
        }
    }

    /* fallback (should not reach for monotonic table) */
    return BmsSoc_OcvSocBp_X10[BMS_SOC_OCV_POINTS - 1u];
}


/* =========================================================
 *  Public Estimator APIs
 * ========================================================= */

/* 입력 유효성 판단(Estimator 관점)
 * - "값이 말이 되는가?"를 보는 1차 필터
 * - 실제 센서 진단(DTC/Status)은 Facade에서 추가 AND 권장
 */
uint8 BmsSoc_Estimator_CheckInputValid(uint16 packVoltage_mV,
                                       sint16 packCurrent_mA,
                                       sint16 packTemp_dC)
{
    if (packVoltage_mV < BMS_SOC_V_MIN_MV_SANITY) { return 0u; }
    if (packVoltage_mV > BMS_SOC_V_MAX_MV_SANITY) { return 0u; }

    if (packCurrent_mA < BMS_SOC_I_MIN_MA_SANITY) { return 0u; }
    if (packCurrent_mA > BMS_SOC_I_MAX_MA_SANITY) { return 0u; }

    if (packTemp_dC < BMS_SOC_T_MIN_DC_SANITY) { return 0u; }
    if (packTemp_dC > BMS_SOC_T_MAX_DC_SANITY) { return 0u; }

    return 1u;
}

/* Coulomb Counting 기반 delta SoC(x10) 계산
 * 가정(부호):
 *   packCurrent_mA > 0 => 방전 => SoC 감소 (delta 음수)
 *   packCurrent_mA < 0 => 충전 => SoC 증가 (delta 양수)
 */
sint16 BmsSoc_Estimator_CalcDeltaSocCc_x10(sint16 packCurrent_mA)
{
    sint32 i_mA;
    sint32 iEff_mA;
    sint32 delta_x10;
    sint32 denom;
    sint32 absI;

    /* offset 제거 */
    i_mA = (sint32)packCurrent_mA - (sint32)BMS_SOC_CC_I_OFFSET_MA;

    /* deadband 적용(노이즈 억제) */
    absI = (sint32)BmsSoc_AbsS16((sint16)i_mA);
    if (absI <= (sint32)BMS_SOC_CC_I_DEADBAND_MA)
    {
        return 0;
    }

    /* 효율 적용 */
    if (i_mA < 0)
    {
        /* charge */
        iEff_mA = (i_mA * (sint32)BMS_SOC_EFF_CHG_X1000) / 1000;
    }
    else
    {
        /* discharge */
        iEff_mA = (i_mA * (sint32)BMS_SOC_EFF_DISCHG_X1000) / 1000;
    }

    /* denom: Ah_x10 * 360000 */
    denom = (sint32)BMS_SOC_NOM_CAPACITY_AH_X10 * (sint32)BMS_SOC_CC_DENOM_FACTOR;

    if (denom <= 0)
    {
        return 0;
    }

    /* delta SoC(x10) */
    delta_x10 = (-(iEff_mA) * (sint32)BMS_SOC_CC_DT_MS) / denom;

    /* slew limit 적용 (x10 per second) */
    if (BMS_SOC_CC_SLEW_LIMIT_X10_PER_S != 0u)
    {
        sint32 dt_s = (sint32)(BMS_SOC_CC_DT_MS / BMS_SOC_MS_PER_SEC);
        sint32 lim;

        if (dt_s <= 0)
        {
            dt_s = 1;
        }

        lim = (sint32)BMS_SOC_CC_SLEW_LIMIT_X10_PER_S * dt_s;

        delta_x10 = (sint32)BmsSoc_ClampS16((sint16)delta_x10,
                                            (sint16)(-lim),
                                            (sint16)( lim));
    }

    return (sint16)delta_x10;
}

/* OCV 테이블 기반 SoC 추정(x10) */
uint16 BmsSoc_Estimator_EstimateSocFromOcv_x10(uint16 packVoltage_mV)
{
    uint16 soc;

    soc = BmsSoc_InterpSocFromOcv(packVoltage_mV);
    soc = BmsSoc_ClampU16(soc, BMS_SOC_MIN_X10, BMS_SOC_MAX_X10);

    return soc;
}
