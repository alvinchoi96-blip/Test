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

void BMS_Logic_MainSequence(void)
{
    /* [Step 1] 고장 진단 (Fault Check) */
    e_FaultLevel faultLevel = BMS_Logic_CheckFaults();
    g_BmsModeContext.isModeChanged = FALSE;
    g_BmsModeContext.previousMode = g_BmsModeContext.determinedMode;
    /* [Step 2] 운전 모드 결정 (Mode Decision) */
    if (faultLevel == FltLv_Error)
    {
        g_BmsModeContext.determinedMode = BmsMd_Emergency;
    }
    else
    {
        /* 현재 상태 판단 */
        g_BmsModeContext.determinedMode = BMS_Logic_DecideOperationMode(FALSE);
    }

    /* 상태 전환 인식 - Flag Set */
    if(g_BmsModeContext.previousMode != g_BmsModeContext.determinedMode)
    {   
        g_BmsModeContext.isModeChanged = TRUE;          
    }

    /* [Step 3] 제어 실행 (Execution) -> Bms_ControlExecutor.c로 위임 */
    BMS_Logic_ExecuteControl(g_BmsModeContext.determinedMode);

    /* [Step 4] 출력 갱신 (Output) -> Bms_ControlExecutor.c로 위임 */
    BMS_Logic_UpdateOutputs(g_BmsModeContext.determinedMode);
}

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

/* 긴급 상태 설정 */
void BMS_Logic_SetEmergencyMode(void)
{
    /* VCU Override */
    if (g_Input_VcuCmd.bmsActionCmd == BmsMd_Driving) {
        return BmsMd_Driving;
    }
    /* Charging Logic */
    if (g_Input_Signal.chargeConnectedFlag == TRUE) {
        return BmsMd_Charging; /* Internal State for Relay ON */
    }
    /* Ignition Logic */
    if ((g_Input_Signal.ignSignal == ON) || (g_Input_Signal.ignSignal == IGN_START)) {
        return BmsMd_Driving;
    }
    return BmsMd_Standby;
    g_BmsModeContext.previousMode = g_BmsModeContext.determinedMode;
    g_BmsModeContext.determinedMode = BmsMd_Emergency;
    
    /* 긴급 상태 진입 시 즉시 플래그 처리 */
    g_BmsModeContext.isModeChanged = TRUE; 
}

/* 정상 운전 판단 */
void BMS_Logic_DetermineNormalOperation(void)
{
    
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