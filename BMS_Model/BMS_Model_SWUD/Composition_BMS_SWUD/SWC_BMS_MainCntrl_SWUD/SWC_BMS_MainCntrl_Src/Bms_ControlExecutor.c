/**
 * @file Bms_ControlExecutor.c
 * @brief Actuator Control Implementation
 */
#include "BMS_MainCntrl_GlobalData.h"
#include "Rte_SWC_BMS_MainCntrl.h"

/* =========================================================================
 * Internal Functions
 * ========================================================================= */
static void PerformRelayConnectSequence(void);
static void PerformRelayCutoffSequence(void);

/* =========================================================================
 * Function Implementation
 * ========================================================================= */

void BMS_Logic_ExecuteControl(e_VcuCanCmd targetMode)
{
    /* 다이어그램에서 조건 분기 확인 가능 */
    if ((targetMode == BmsMd_Driving) || (targetMode == BmsMd_Charging))
    {
        /* 연결 시퀀스 함수 호출 */
        PerformRelayConnectSequence();
    }
    else
    {
        /* 차단 시퀀스 함수 호출 */
        PerformRelayCutoffSequence();
    }
}

void BMS_Logic_UpdateOutputs(e_VcuCanCmd currentMode)
{
    /* RTE Write API 호출 */
    (void)Rte_Write_P_PackMeasData_Tx_bmsModeInfo(currentMode);
    
    /* 2. Charging Status 상세 정보 출력 */
    /* (모드는 Driving이지만, 물리적으로 충전기가 연결된 경우 Charging 상태 송신) */
    if ((currentMode == BmsMd_Driving) && (g_Input_Signal.chargeConnectedFlag == TRUE))
    {
        (void)Rte_Write_P_ChgData_Tx_chargingStatus(ChgSt_Charging);
    }
    else if (g_Input_Signal.chargeConnectedFlag == TRUE)
    {
        /* 릴레이가 붙지 않았지만 충전기는 연결됨 */
        (void)Rte_Write_P_ChgData_Tx_chargingStatus(ChgSt_ChargerConnected);
    }
    else
    {
        (void)Rte_Write_P_ChgData_Tx_chargingStatus(ChgSt_NotCharging);
    }
    /* 진단 정보 업데이트가 필요하다면 여기서 추가 호출 가능 */
}

/* --- Internal Action Functions --- */

static void PerformRelayConnectSequence(void)
{
    /* Soft Start (Pre-charge) 요청 */
    (void)Rte_Call_R_RelayControlReq_relayEnableReq(Soft); 
}

static void PerformRelayCutoffSequence(void)
{
    /* 즉시 차단 요청 */
    (void)Rte_Call_R_RelayControlReq_relayDisableReq();
}