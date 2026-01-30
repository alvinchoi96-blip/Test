/**
 * @file BmsStatusDetermine.c
 * @brief State Machine & Control Logic
 */
#include "BMS_MainCntrl_GlobalData.h"      /* 전역 변수 접근 */
#include "Bms_StatusDecision.h"
#include "Rte_SWC_BMS_MainCntrl.h"

/* =========================================================================
 * Function Prototypes
 * ========================================================================= */
e_FaultLevel BMS_Logic_CheckFaults(void);
e_VcuCanCmd BMS_Logic_DecideOperationMode(boolean isFault);


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
    /* 1. Error Check (Any Error Flag) */
    if (g_Input_FaultFlag.isAnyError == TRUE)
    {
        return FltLv_Error;
    }

    /* 2. Warning Check (Any Warning Flag) */
    if (g_Input_FaultFlag.isAnyWarning == TRUE)
    {
        return FltLv_Warning;
    }

    return FltLv_Normal;
}

e_VcuCanCmd BMS_Logic_DecideOperationMode(boolean isFault)
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
}