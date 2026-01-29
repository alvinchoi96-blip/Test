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

void BMS_Logic_MainSequence(e_VcuCanCmd* currentMode)
{
    /* [Step 1] 고장 진단 (Fault Check) */
    e_FaultLevel faultLevel = BMS_Logic_CheckFaults();

    /* [Step 2] 운전 모드 결정 (Mode Decision) */
    if (faultLevel == Error)
    {
        *currentMode = Emergency;
    }
    else
    {
        *currentMode = BMS_Logic_DecideOperationMode(FALSE);
    }

    /* [Step 3] 제어 실행 (Execution) -> Bms_ControlExecutor.c로 위임 */
    BMS_Logic_ExecuteControl(*currentMode);

    /* [Step 4] 출력 갱신 (Output) -> Bms_ControlExecutor.c로 위임 */
    BMS_Logic_UpdateOutputs(*currentMode);
}

e_FaultLevel BMS_Logic_CheckFaults(void)
{
    /* 1. Error Check (Any Error Flag) */
    if (g_Input_FaultFlag.isAnyError == TRUE)
    {
        return Error;
    }

    /* 2. Warning Check (Any Warning Flag) */
    if (g_Input_FaultFlag.isAnyWarning == TRUE)
    {
        return Warning;
    }

    return Normal;
}

e_VcuCanCmd BMS_Logic_DecideOperationMode(boolean isFault)
{
    /* VCU Override */
    if (g_Input_VcuCmd.bmsActionCmd == Driving) {
        return Driving;
    }
    /* Charging Logic */
    if (g_Input_Signal.chargeConnectedFlag == TRUE) {
        return Driving; /* Internal State for Relay ON */
    }
    /* Ignition Logic */
    if ((g_Input_Signal.ignSignal == ON) || (g_Input_Signal.ignSignal == START)) {
        return Driving;
    }
    return Standby;
}