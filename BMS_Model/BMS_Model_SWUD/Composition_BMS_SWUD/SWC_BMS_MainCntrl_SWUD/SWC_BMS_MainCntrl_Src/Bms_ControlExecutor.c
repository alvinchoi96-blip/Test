/**
 * @file Bms_ControlExecutor.c
 * @brief Actuator Control & Output Update Implementation
 */

#include "BMS_MainCntrl_GlobalData.h"      /* 전역 변수 접근 */
#include "Bms_StatusDecision.h"
#include "Rte_SWC_BMS_MainCntrl.h"

/* =========================================================================
 * Function Implementation
 * ========================================================================= */

void BMS_Logic_ExecuteControl(e_VcuCanCmd targetMode)
{
    /* Driving 모드일 경우 릴레이 연결 시퀀스 수행 */
    if (targetMode == Driving)
    {
        /* Soft Start (Pre-charge) 요청: Argument 1U */
        (void)Rte_Call_R_RelayControlReq_relayEnableReq(TRUE); 
    }
    else
    {
        /* 그 외 모드(Standby, Emergency 등)에서는 릴레이 차단 요청 */
        (void)Rte_Call_R_RelayControlReq_relayDisableReq();
    }
}

void BMS_Logic_UpdateOutputs(e_VcuCanCmd currentMode)
{
    /* 1. BMS Main Mode 출력 */
    (void)Rte_Write_P_PackMeasData_Tx_bmsModeInfo(currentMode);
    
    /* 2. Charging Status 상세 정보 출력 */
    /* (모드는 Driving이지만, 물리적으로 충전기가 연결된 경우 Charging 상태 송신) */
    if ((currentMode == Driving) && (g_Input_Signal.chargeConnectedFlag == TRUE))
    {
        (void)Rte_Write_P_ChgData_Tx_chargingStatus(Charging);
    }
    else if (g_Input_Signal.chargeConnectedFlag == TRUE)
    {
        /* 릴레이가 붙지 않았지만 충전기는 연결됨 */
        (void)Rte_Write_P_ChgData_Tx_chargingStatus(ChargerConnected);
    }
    else
    {
        (void)Rte_Write_P_ChgData_Tx_chargingStatus(NotCharging);
    }
}