#include "BmsMainCntrl_Soc.h"
#include "Soc_Cfg.h"

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
void BmsMainCntrl_Soc_Process_1000ms(const BmsSoc_Input_t* in,
                                     BmsSoc_Output_t* out)
{
    uint8  inputValid;
    sint16 deltaSocCc_x10;
    uint16 socFromOcv_x10;

    if (gSocInitDone == 0u)
    {
        BmsMainCntrl_Soc_Init();
    }

    /* 1. 입력 유효성 판단 */
    inputValid = BmsSoc_Estimator_CheckInputValid(
                    in->packVoltage_mV,
                    in->packCurrent_mA,
                    in->packTemp_dC);

    /* 2. State에 입력 전달 */
    BmsSoc_State_OnInputs(in->packVoltage_mV,
                          in->packCurrent_mA,
                          in->packTemp_dC,
                          in->ignOn,
                          in->chgConnected,
                          inputValid);

    /* 3. Coulomb Counting */
    deltaSocCc_x10 =
        BmsSoc_Estimator_CalcDeltaSocCc_x10(in->packCurrent_mA);

    BmsSoc_State_ApplyCcDelta(deltaSocCc_x10);

    /* 4. OCV 보정 */
    if (BmsSoc_State_IsRestReady() != 0u)
    {
        socFromOcv_x10 =
            BmsSoc_Estimator_EstimateSocFromOcv_x10(
                in->packVoltage_mV);

        BmsSoc_State_ApplyOcvSoc(socFromOcv_x10);
    }

    /* 5. SOH 처리 (stub) */
    BmsMainCntrl_Soh_Process_1000ms();

    /* 6. 출력 구성 */
    out->soc_x10  = BmsSoc_State_GetSoc();
    out->soh_x10  = BmsSoc_State_GetSoh();
    out->socValid = BmsSoc_State_IsOutputValid();
}

/* =========================================================
 *  SOH Stub
 * ========================================================= */
void BmsMainCntrl_Soh_Process_1000ms(void)
{
    /* intentionally empty */
}
