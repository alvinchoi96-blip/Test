#include "BmsMainCntrl_Soc.h"
#include "Soc_Cfg.h"
#include "Rte_SWC_BMS_MainCntrl.h"
/* =========================================================
 *  extern declarations (State / Estimator)
 *  - 별도 헤더 없이 사용하기 위한 명시적 선언
 * ========================================================= */

/* ---- State layer ---- */
extern void   BmsSoc_State_Init(void);
extern void   BmsSoc_State_OnInputs(uint16 packVoltage_mV,
                                    sint16 packCurrent_mA,
                                    sint16 packTemp_dC,
                                    uint8  ignOn,
                                    uint8  chgConnected,
                                    uint8  inputValid);
extern uint8  BmsSoc_State_IsRestReady(void);
extern void   BmsSoc_State_ApplyCcDelta(sint16 deltaSoc_x10);
extern void   BmsSoc_State_ApplyOcvSoc(uint16 ocvSoc_x10);
extern uint16 BmsSoc_State_GetSoc(void);
extern uint16 BmsSoc_State_GetSoh(void);
extern uint8  BmsSoc_State_IsOutputValid(void);

/* ---- Estimator layer ---- */
extern uint8  BmsSoc_Estimator_CheckInputValid(uint16 packVoltage_mV,
                                               sint16 packCurrent_mA,
                                               sint16 packTemp_dC);
extern sint16 BmsSoc_Estimator_CalcDeltaSocCc_x10(sint16 packCurrent_mA);
extern uint16 BmsSoc_Estimator_EstimateSocFromOcv_x10(uint16 packVoltage_mV);

/* =========================================================
 *  Facade Internal State
 * ========================================================= */
static uint8 gSocInitDone = 0u;

/* =========================================================
 *  Public APIs
 * ========================================================= */

void BmsMainCntrl_Soc_Init(void)
{
    BmsSoc_State_Init();
    gSocInitDone = 1u;
}

/* =========================================================
 *  SoC main processing (1000ms)
 * ========================================================= */
void BmsMainCntrl_Soc_Process_1000ms(BmsSoc_Output_t* out)
{
    uint8  inputValid;
    sint16 deltaSocCc_x10;
    uint16 socFromOcv_x10;

    if (gSocInitDone == 0u)
    {
        BmsMainCntrl_Soc_Init();
    }

    /* 값 Mapping, Global Data Type 내용 활용 */
    const uint32 packVoltageSum = g_Input_CellMeas.packVoltageSum;
    const sint32 packCurrent    = g_Input_CurrMeas.packCurrent;
    const sint16 packTemp       = g_Input_TempMeas.cellTempAverage;
    /* ignSignal은 e_IgnStat(enum)임 → SoC 로직이 0/1 기대면 추후 정식 매핑 필요 */
    const uint8 ignOn           = (g_Input_Signal.ignSignal != 0u) ? 1u : 0u;
    const uint8 chgConnected    = (g_Input_Signal.chargeConnectedFlag != 0u) ? 1u : 0u;

    /* 1. 입력 유효성 판단 */
    inputValid = BmsSoc_Estimator_CheckInputValid((uint16)packVoltageSum, (sint16)packCurrent, packTemp);

    /* 2. State에 입력 전달 */
    BmsSoc_State_OnInputs((uint16)packVoltageSum, (sint16)packCurrent, packTemp, ignOn, chgConnected, inputValid);

    /* 3. Coulomb Counting */
    deltaSocCc_x10 = BmsSoc_Estimator_CalcDeltaSocCc_x10((sint16)packCurrent);

    BmsSoc_State_ApplyCcDelta(deltaSocCc_x10);

    /* 4. OCV 보정 */
    if (BmsSoc_State_IsRestReady() != 0u)
    {
        socFromOcv_x10 = BmsSoc_Estimator_EstimateSocFromOcv_x10((uint16)packVoltageSum);
        BmsSoc_State_ApplyOcvSoc(socFromOcv_x10);
    }

    /* 6. 출력 구성 */
    out->soc_x10  = BmsSoc_State_GetSoc();
    out->soh_x10  = BmsSoc_State_GetSoh();
    out->socValid = BmsSoc_State_IsOutputValid();
}

/* =========================================================
 *  SOH Stub
 * ========================================================= */
void BmsMainCntrl_Soh_Process_1000ms(BmsModeContext_Type g_BmsModeContext, uint32 * calculateSohValue)
{
    if(g_BmsModeContext.isModeChanged && g_BmsModeContext.previousMode == BmsMd_Driving)
    {
        /* Driving -> Driving 상태 천이이나, 오류로 인해 들어온 경우 방어*/
        if(g_BmsModeContext.previousMode == BmsMd_Driving)
            return;

        /* SOH 실행 확인 */
        Rte_Call_R_SocCalc_calculateSoh(&calculateSohValue);
    }
}
