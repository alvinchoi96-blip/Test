/**
 * @file BmsStatusDetermine.c
 * @brief BMS Logic Implementation using Global Variables
 */

#include "BmsStatusDetermine.h"
#include "Rte_SWC_BMS_MainCntrl.h" 

/*******************************************************************************
 * Function: BMS_Logic_DetermineState
 * Description: 전역 입력 변수들을 확인하여 BMS 운전 모드를 결정
 *******************************************************************************/
void BMS_Logic_DetermineState(e_VcuCanCmd* currentMode)
{
    /* 1. 고장 진단 (Fault Aggregation) - Critical Faults Check */
    boolean isCriticalFault = FALSE;

    if (g_Input_FaultFlag.errOverCharge || g_Input_FaultFlag.errOverDischarge || 
        g_Input_FaultFlag.errOverCellVmax || g_Input_FaultFlag.errIsolation ||
        g_Input_FaultFlag.errDischargeOverTemp || g_Input_FaultFlag.errOverChargeCurrent)
    {
        isCriticalFault = TRUE;
    }

    /* 2. 상태 결정 우선순위 로직 */
    /* Priority 1: Critical Fault -> Emergency */
    if (isCriticalFault == TRUE)
    {
        *currentMode = Emergency; /* 5U */
    }
    /* Priority 2: VCU Force Command -> Driving (Override) */
    else if (g_Input_VcuCmd.bmsActionCmd == Driving)
    {
        *currentMode = Driving; /* 2U */
    }
    /* Priority 3: Charger Connected -> Charging Logic */
    /* Rte_Type 정의상 Driving=2, Charging=2(ENUM_ChgInfo)이므로,
       BmsMode는 Driving으로 설정하되, 출력 시 ChargingStatus를 별도로 송신 */
    else if (g_Input_Signal.chargeConnectedFlag == TRUE)
    {
        *currentMode = Driving; /* Relay ON을 위해 Driving 모드 진입 */
    }
    /* Priority 4: Ignition ON/START -> Driving */
    else if ((g_Input_Signal.ignSignal == ON) || (g_Input_Signal.ignSignal == START))
    {
        *currentMode = Driving; /* 2U */
    }
    /* Default: Standby */
    else
    {
        *currentMode = Standby; /* 1U */
    }
}

/*******************************************************************************
 * Function: BMS_Logic_ControlRelays
 * Description: 결정된 모드에 따라 Relay 제어 (Soft Start 포함)
 *******************************************************************************/
void BMS_Logic_ControlRelays(e_VcuCanCmd currentMode)
{
    /* Driving 모드이거나 충전기가 연결되어 있을 때 Relay ON */
    if (currentMode == Driving) 
    {
        /* Relay Enable 요청 (Soft Start = 1U) */
        (void)Rte_Call_R_RelayControlReq_relayEnableReq(1U); 
    }
    else if (currentMode == Emergency || currentMode == Shut_Down)
    {
        /* Relay Disable 요청 (즉시 차단) */
        (void)Rte_Call_R_RelayControlReq_relayDisableReq();
    }
    else /* Standby */
    {
        (void)Rte_Call_R_RelayControlReq_relayDisableReq();
    }
}

/*******************************************************************************
 * Function: BMS_Logic_WriteOutputs
 * Description: BMS 상태 및 전역 변수에 저장된 측정값 출력
 *******************************************************************************/
void BMS_Logic_WriteOutputs(e_VcuCanCmd currentMode)
{
    /* 1. BMS Mode Info 송신 */
    (void)Rte_Write_P_PackMeasData_Tx_bmsModeInfo(currentMode);

    /* 2. Charging Status 송신 */
    /* 모드는 Driving이지만, 실제로 충전기가 연결되어 있다면 'Charging' 상태 출력 */
    if ((currentMode == Driving) && (g_Input_Signal.chargeConnectedFlag == TRUE))
    {
        (void)Rte_Write_P_ChgData_Tx_chargingStatus(Charging); /* 2U */
    }
    else if (g_Input_Signal.chargeConnectedFlag == TRUE)
    {
        (void)Rte_Write_P_ChgData_Tx_chargingStatus(ChargerConnected); /* 1U */
    }
    else
    {
        (void)Rte_Write_P_ChgData_Tx_chargingStatus(NotCharging); /* 0U */
    }

    /* 3. (Optional) 측정값 재전송 (Pass-through) */
    /* 다른 컴포넌트나 HMI 등에서 값을 쓰기 위해 필요한 경우 전송 */
    // Rte_Write_P_PackMeasData_Tx_packCurrent(g_Input_CurrMeas.packCurrent);
}