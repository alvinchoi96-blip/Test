#include "Rte_SWC_BMS_MainCntrl.h"
#include "BmsStatusDetermine.h"



/*******************************************************************************
 * Sub-Function: BMS_Read_Inputs
 * Description: Reads all necessary data from RTE ports
 *******************************************************************************/
void BMS_Read_Inputs(BmsInputData *pData)
{
    /* Read Ignition Status from SWC_SigInput */
    Rte_Read_rp_SigInput_ignSignal(&pData->ignStatus);

    /* Read Charger Connection Status */
    Rte_Read_rp_SigInput_chargerConnectedFlag(&pData->isChargerConnected);

    /* Read VCU Command (if any) */
    Rte_Read_rp_VcuCanCmd_bmsActionCmd(&pData->vcuCmd);

    /* Read Fault Flags from SWC_FaultDTC (Aggregated Flag or Individual) */
    /* Assuming a summary fault flag interface exists or aggregating here */
    boolean overCharge, overDischarge, isolationFault;
    Rte_Read_rp_FaultFlag_errOverCharge(&overCharge);
    Rte_Read_rp_FaultFlag_errOverDischarge(&overDischarge);
    Rte_Read_rp_FaultFlag_errIsolation(&isolationFault);

    /* Simple fault aggregation logic */
    if (overCharge || overDischarge || isolationFault)
    {
        pData->isFaultActive = TRUE;
    }
    else
    {
        pData->isFaultActive = FALSE;
    }
}

/*******************************************************************************
 * Sub-Function: BMS_Determine_State
 * Description: Implements the core logic from legacy 'Main_Loop'
 *******************************************************************************/
void BMS_Determine_State(const BmsInputData *pData, BMS_OperationModeType *pMode, boolean *pRelayEnable)
{
    /* Priority 1: Fault Condition */
    if (pData->isFaultActive == TRUE)
    {
        *pMode = BMS_MODE_FAULT;
        *pRelayEnable = FALSE; // Cut-off Relays
    }
    /* Priority 2: VCU Command Override */
    else if (pData->vcuCmd == VCU_CMD_RELAY_ON)
    {
        *pMode = BMS_MODE_DRIVE; // Assume Drive mode if VCU forces Relay ON
        *pRelayEnable = TRUE;
    }
    /* Priority 3: Charger Connected */
    else if (pData->isChargerConnected == TRUE)
    {
        *pMode = BMS_MODE_CHARGE;
        *pRelayEnable = TRUE; // Relay must be ON to charge
    }
    /* Priority 4: Ignition ON */
    else if (pData->ignStatus == IGN_ON || pData->ignStatus == IGN_START)
    {
        *pMode = BMS_MODE_DRIVE;
        *pRelayEnable = TRUE;
    }
    /* Default: Standby / Sleep */
    else
    {
        *pMode = BMS_MODE_STANDBY;
        *pRelayEnable = FALSE;
    }
}

/*******************************************************************************
 * Sub-Function: BMS_Control_Relays
 * Description: Executes Relay Control via Client-Server Interface
 *******************************************************************************/
void BMS_Control_Relays(boolean enable)
{
    if (enable == TRUE)
    {
        /* Request Soft Start Relay Enable */
        /* Argument 1: Speed (1=Soft Start, 0=Immediate) */
        Rte_Call_cp_RelayControlReq_relayEnableReq(1);
    }
    else
    {
        /* Request Relay Disable */
        Rte_Call_cp_RelayControlReq_relayDisableReq();
    }
}

/*******************************************************************************
 * Sub-Function: BMS_Update_Status_Output
 * Description: Sends current BMS mode to other components
 *******************************************************************************/
void BMS_Update_Status_Output(BMS_OperationModeType mode)
{
    /* Send BMS Mode Info */
    Rte_Write_pp_BmsModeInfo_bmsModeInfo(mode);
}