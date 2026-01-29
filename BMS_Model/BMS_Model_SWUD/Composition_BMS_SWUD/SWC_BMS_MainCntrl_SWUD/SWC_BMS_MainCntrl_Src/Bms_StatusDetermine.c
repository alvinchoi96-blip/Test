/**
 * @file BmsStatusDetermine.c
 * @brief State Machine & Control Logic
 */
#include "BMS_MainCntrl_GlobalData.h"      /* 전역 변수 접근 */
#include "Bms_StatusDetermine.h"
#include "Rte_SWC_BMS_MainCntrl.h"

void BMS_Logic_MainSequence(e_VcuCanCmd* currentMode)
{
    /* Step 1: Check Faults (Depth 2 호출) */
    e_VcuCanCmd faultMode = BMS_Logic_CheckFaults();

    /* Step 2: Determine Operation Mode */
    if (faultMode == Emergency)
    {
        *currentMode = Emergency;
    }
    else
    {
        /* Fault가 없을 때만 정상 모드 판단 (Depth 2 호출) */
        *currentMode = BMS_Logic_DecideOperationMode(FALSE);
    }

    /* Step 3: Execute Control (Depth 2 호출) */
    BMS_Logic_ExecuteControl(*currentMode);

    /* Step 4: Update Outputs */
    BMS_Logic_UpdateOutputs(*currentMode);
}

e_VcuCanCmd BMS_Logic_CheckFaults(void)
{
    /* Critical Faults Check */
    if (g_Input_FaultFlag.errOverCharge || g_Input_FaultFlag.errOverDischarge || 
        g_Input_FaultFlag.errIsolation  || g_Input_FaultFlag.errOverCellVmax)
    {
        return Emergency;
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

void BMS_Logic_ExecuteControl(e_VcuCanCmd targetMode)
{
    if (targetMode == Driving) {
        (void)Rte_Call_R_RelayControlReq_relayEnableReq(1U); /* Soft Start */
    } else {
        (void)Rte_Call_R_RelayControlReq_relayDisableReq();
    }
}

void BMS_Logic_UpdateOutputs(e_VcuCanCmd currentMode)
{
    (void)Rte_Write_P_PackMeasData_Tx_bmsModeInfo(currentMode);
    
    if ((currentMode == Driving) && (g_Input_Signal.chargeConnectedFlag == TRUE)) {
        (void)Rte_Write_P_ChgData_Tx_chargingStatus(Charging);
    } else {
        (void)Rte_Write_P_ChgData_Tx_chargingStatus(NotCharging);
    }
}