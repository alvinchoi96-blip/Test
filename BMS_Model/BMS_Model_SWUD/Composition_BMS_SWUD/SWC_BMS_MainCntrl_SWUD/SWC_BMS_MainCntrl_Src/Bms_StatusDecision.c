/**
 * @file Bms_StatusDecision.c
 * @brief State Machine Decision Logic
 */
#include "BMS_MainCntrl_GlobalData.h"
#include "Bms_StatusDecision.h"
#include "Rte_SWC_BMS_MainCntrl.h"

/* 외부 참조 */
extern BmsModeContext_Type g_BmsModeContext;

/* =========================================================================
 * Internal Static Helper Functions (If needed)
 * ========================================================================= */
static e_VcuCanCmd CalculateNextOperationMode(void);

/* =========================================================================
 * Function Implementation
 * ========================================================================= */

e_FaultLevel BMS_Logic_CheckFaults(void)
{
    /* 에러 우선 순위 검사 */
    if (g_Input_FaultFlag.isAnyError == TRUE)
    {
        return FltLv_Error;
    }
    if (g_Input_FaultFlag.isAnyWarning == TRUE)
    {
        return FltLv_Warning;
    }
    return FltLv_Normal;
}

/* [NEW] 긴급 모드 설정 액션 함수 */
void BMS_Logic_SetEmergencyMode(void)
{
    g_BmsModeContext.previousMode = g_BmsModeContext.determinedMode;
    g_BmsModeContext.determinedMode = BmsMd_Emergency;
    
    /* 긴급 상황 진입 시 즉시 플래그 처리 */
    g_BmsModeContext.isModeChanged = TRUE; 
}

/* [NEW] 정상 운전 판단 액션 함수 */
void BMS_Logic_DetermineNormalOperation(void)
{
    e_VcuCanCmd nextMode;
    
    g_BmsModeContext.previousMode = g_BmsModeContext.determinedMode;
    
    /* VCU 명령 및 충전기 연결 상태에 따른 모드 계산 */
    g_BmsModeContext.determinedMode = CalculateNextOperationMode();
    
    if (g_BmsModeContext.previousMode != g_BmsModeContext.determinedMode)
    {
        g_BmsModeContext.isModeChanged = TRUE;
    }
}

/* 내부 로직: 실제 VCU 명령 해석 */
static e_VcuCanCmd CalculateNextOperationMode(void)
{
    /* 충전기 연결 시 최우선으로 충전 모드 진입 */
    if (g_Input_Signal.chargeConnectedFlag == TRUE)
    {
        return BmsMd_Charging;
    }
    /* 그 외 VCU 요청 따름 */
    return g_Input_VcuCmd.bmsActionCmd;
}