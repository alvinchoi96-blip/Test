#include "Platform_Types.h"
#include "Soc_Cfg.h"

/* =========================
 *  Local Types
 * ========================= */
typedef struct
{
    /* Last known inputs (for rest detection / debug) */
    uint32 lastPackVoltage_mV;
    sint32 lastPackCurrent_mA;
    sint16 lastPackTemp_dC;

    /* Rest detection */
    uint32 restTimer_ms;

    /* Main state */
    uint16 soc_x10;      /* 0~1000 */
    uint16 soh_x10;      /* 0~1000 (optional) */

    /* Flags */
    uint8  flags;        /* BMS_SOC_FLAG_* */
    uint8  ignOn;
    uint8  chgConnected;

    /* Validity / hold */
    uint8  inputValid;   /* 0/1 */
    uint32 invalidHold_ms;

} BmsSoc_State_t;

/* =========================
 *  Local State (Single Instance)
 * ========================= */
static BmsSoc_State_t gSoc;

/* =========================
 *  Local Helpers
 * ========================= */
static uint16 BmsSoc_ClampU16(uint16 v, uint16 lo, uint16 hi)
{
    if (v < lo) { return lo; }
    if (v > hi) { return hi; }
    return v;
}

static uint16 BmsSoc_AbsDiffU16(uint16 a, uint16 b)
{
    return (a >= b) ? (uint16)(a - b) : (uint16)(b - a);
}

static sint16 BmsSoc_AbsS16(sint16 v)
{
    return (v >= 0) ? v : (sint16)(-v);
}

static void BmsSoc_SetFlag(uint8 mask)
{
    gSoc.flags = (uint8)(gSoc.flags | mask);
}

static void BmsSoc_ClearFlag(uint8 mask)
{
    gSoc.flags = (uint8)(gSoc.flags & (uint8)(~mask));
}

/* =========================
 *  Public APIs (State Layer)
 *  - 아래 함수들은 Estimator/Facade에서 호출 예정
 * ========================= */

/* 초기화: 시스템 시작/리셋 1회 */
void BmsSoc_State_Init(void)
{
    gSoc.lastPackVoltage_mV = 0u;
    gSoc.lastPackCurrent_mA = 0;
    gSoc.lastPackTemp_dC    = 0;

    gSoc.restTimer_ms       = 0u;

    gSoc.soc_x10            = BMS_SOC_INVALID_DEFAULT_X10;
    gSoc.soh_x10            = 1000u;

    gSoc.flags              = 0u;
    gSoc.ignOn              = 0u;
    gSoc.chgConnected       = 0u;

    gSoc.inputValid         = 0u;
    gSoc.invalidHold_ms     = 0u;
}

/* 입력 업데이트 + Rest 타이머 갱신
 * - voltage/current/temp는 "원시값" 그대로
 * - inputValid는 센서/신호 유효성 판단 결과(Estimator 또는 Facade에서 결정)
 */
void BmsSoc_State_OnInputs(uint16 packVoltage_mV,
                           sint16 packCurrent_mA,
                           sint16 packTemp_dC,
                           uint8 ignOn,
                           uint8 chgConnected,
                           uint8 inputValid)
{
    uint16 dv_mV;
    sint16 absI_mA;

    gSoc.ignOn        = ignOn;
    gSoc.chgConnected = chgConnected;

    /* validity handling */
    if (inputValid != 0u)
    {
        gSoc.inputValid     = 1u;
        gSoc.invalidHold_ms = 0u;
        BmsSoc_SetFlag(BMS_SOC_FLAG_VALID);
    }
    else
    {
        gSoc.inputValid = 0u;
        BmsSoc_ClearFlag(BMS_SOC_FLAG_VALID);

        /* invalid hold timer */
        if (gSoc.invalidHold_ms < BMS_SOC_INVALID_HOLD_MS)
        {
            gSoc.invalidHold_ms += BMS_SOC_CC_DT_MS;
            if (gSoc.invalidHold_ms > BMS_SOC_INVALID_HOLD_MS)
            {
                gSoc.invalidHold_ms = BMS_SOC_INVALID_HOLD_MS;
            }
        }
    }

    /* rest detection update */
    dv_mV    = BmsSoc_AbsDiffU16(packVoltage_mV, gSoc.lastPackVoltage_mV);
    absI_mA  = BmsSoc_AbsS16(packCurrent_mA);

    if ((absI_mA <= (sint16)BMS_SOC_REST_I_THR_MA) &&
        (dv_mV  <= (uint16)BMS_SOC_REST_V_DV_THR_MV) &&
        (gSoc.inputValid != 0u))
    {
        /* accumulate rest time */
        if (gSoc.restTimer_ms < BMS_SOC_REST_TIME_MS)
        {
            gSoc.restTimer_ms += BMS_SOC_CC_DT_MS;
            if (gSoc.restTimer_ms > BMS_SOC_REST_TIME_MS)
            {
                gSoc.restTimer_ms = BMS_SOC_REST_TIME_MS;
            }
        }
    }
    else
    {
        gSoc.restTimer_ms = 0u;
    }

    /* store last inputs */
    gSoc.lastPackVoltage_mV = packVoltage_mV;
    gSoc.lastPackCurrent_mA = packCurrent_mA;
    gSoc.lastPackTemp_dC    = packTemp_dC;
}

/* Rest 상태 여부(OCV 보정 허용 판단에 사용) */
uint8 BmsSoc_State_IsRestReady(void)
{
    return (gSoc.restTimer_ms >= BMS_SOC_REST_TIME_MS) ? (uint8)1u : (uint8)0u;
}

/* CC 결과(Delta SoC)를 state에 반영
 * deltaSoc_x10: (-1000~+1000) 범위 내 권장
 */
void BmsSoc_State_ApplyCcDelta(sint16 deltaSoc_x10)
{
    sint32 tmp;
    uint16 newSoc;

    /* invalid 상태인데 hold 시간 안 지났으면 현재값 유지 */
    if ((gSoc.inputValid == 0u) && (gSoc.invalidHold_ms < BMS_SOC_INVALID_HOLD_MS))
    {
        return;
    }

    /* invalid hold 끝났으면 default로 재기동(보수적) */
    if ((gSoc.inputValid == 0u) && (gSoc.invalidHold_ms >= BMS_SOC_INVALID_HOLD_MS))
    {
        gSoc.soc_x10 = BMS_SOC_INVALID_DEFAULT_X10;
        gSoc.soc_x10 = BmsSoc_ClampU16(gSoc.soc_x10, BMS_SOC_MIN_X10, BMS_SOC_MAX_X10);
        return;
    }

    tmp = (sint32)gSoc.soc_x10 + (sint32)deltaSoc_x10;

    if (tmp < (sint32)BMS_SOC_MIN_X10)
    {
        newSoc = BMS_SOC_MIN_X10;
        BmsSoc_SetFlag(BMS_SOC_FLAG_SATURATED);
    }
    else if (tmp > (sint32)BMS_SOC_MAX_X10)
    {
        newSoc = BMS_SOC_MAX_X10;
        BmsSoc_SetFlag(BMS_SOC_FLAG_SATURATED);
    }
    else
    {
        newSoc = (uint16)tmp;
        BmsSoc_ClearFlag(BMS_SOC_FLAG_SATURATED);
    }

    gSoc.soc_x10 = newSoc;
    BmsSoc_SetFlag(BMS_SOC_FLAG_CC_USED);
}

/* OCV 기반 SoC를 state에 “완만하게” 반영 (Gain/MaxStep 적용)
 * ocvSoc_x10: OCV 테이블로부터 추정된 SoC (0~1000)
 * - RestReady일 때만 호출하는 게 일반적이지만, 여기서도 보호
 */
void BmsSoc_State_ApplyOcvSoc(uint16 ocvSoc_x10)
{
    sint32 err;
    sint32 step;
    sint32 maxStep;
    sint32 gain;
    uint16 clampedOcv;
    sint32 newSoc;

    if (BmsSoc_State_IsRestReady() == 0u)
    {
        return;
    }

    /* invalid 상태인데 hold 시간 안 지났으면 반영 금지 */
    if ((gSoc.inputValid == 0u) && (gSoc.invalidHold_ms < BMS_SOC_INVALID_HOLD_MS))
    {
        return;
    }

    clampedOcv = BmsSoc_ClampU16(ocvSoc_x10, BMS_SOC_MIN_X10, BMS_SOC_MAX_X10);

    err = (sint32)clampedOcv - (sint32)gSoc.soc_x10;

    /* step = err * gain */
    gain    = (sint32)BMS_SOC_OCV_CORR_GAIN_X1000; /* 0~1000 */
    step    = (err * gain) / 1000;

    /* limit per update */
    maxStep = (sint32)BMS_SOC_OCV_CORR_MAX_STEP_X10;
    if (step >  maxStep) { step =  maxStep; }
    if (step < -maxStep) { step = -maxStep; }

    newSoc = (sint32)gSoc.soc_x10 + step;

    if (newSoc < (sint32)BMS_SOC_MIN_X10) { newSoc = (sint32)BMS_SOC_MIN_X10; }
    if (newSoc > (sint32)BMS_SOC_MAX_X10) { newSoc = (sint32)BMS_SOC_MAX_X10; }

    gSoc.soc_x10 = (uint16)newSoc;
    BmsSoc_SetFlag(BMS_SOC_FLAG_OCV_USED);
}

/* SOH 설정(필요하면 Estimator/진단에서 업데이트) */
void BmsSoc_State_SetSoh(uint16 soh_x10)
{
    gSoc.soh_x10 = BmsSoc_ClampU16(soh_x10, 0u, 1000u);
}

/* Getter들 */
uint16 BmsSoc_State_GetSoc(void)     { return gSoc.soc_x10; }
uint16 BmsSoc_State_GetSoh(void)     { return gSoc.soh_x10; }
uint8  BmsSoc_State_GetFlags(void)   { return gSoc.flags;   }
uint16 BmsSoc_State_GetLastV_mV(void){ return gSoc.lastPackVoltage_mV; }
sint16 BmsSoc_State_GetLastI_mA(void){ return gSoc.lastPackCurrent_mA; }
uint32 BmsSoc_State_GetRestTimer(void){ return gSoc.restTimer_ms; }

/* “출력 유효” 판단
 * - 지금은 VALID flag 기반으로 단순화
 * - 프로젝트에 맞게 조건 강화 가능
 */
uint8 BmsSoc_State_IsOutputValid(void)
{
    return ((gSoc.flags & BMS_SOC_FLAG_VALID) != 0u) ? (uint8)1u : (uint8)0u;
}
