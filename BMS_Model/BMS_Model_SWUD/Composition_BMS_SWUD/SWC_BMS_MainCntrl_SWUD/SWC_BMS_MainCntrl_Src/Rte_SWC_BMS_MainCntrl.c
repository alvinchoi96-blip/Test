#include "Rte_SWC_BMS_MainCntrl.h"
<<<<<<< HEAD
#include "BmsMainCntrl_TxSvc.h"
#include "BmsStatusDetermine.h"

static uint32      s_tx_packVoltageSum = 0U;
static sint32      s_tx_packCurrent = 0;
static e_VcuCanCmd s_tx_bmsModeInfo = (e_VcuCanCmd)0;
static sint16      s_tx_cellTempAverage = 0;

static void MainCntrl_UpdateTx_PackMeasData(uint32 packVoltageSum, sint32 packCurrent, e_VcuCanCmd bmsModeInfo, sint16 cellTempAverage
)
{
    s_tx_packVoltageSum = packVoltageSum;
    s_tx_packCurrent = packCurrent;
    s_tx_bmsModeInfo = bmsModeInfo;
    s_tx_cellTempAverage = cellTempAverage;
}
#include "P_PackMeasData_TX_To_SWC_ChargeMngr.h"

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_BattStatusProcess_10ms(void)
{
    BmsInputData inputData;
/* Internal Variables for State Management */
    static BMS_OperationModeType currentBmsMode = BMS_MODE_INIT;
    static boolean bRelayCmd = FALSE;
    /* 1. Read Inputs (Signal & Fault Data) */
    BMS_Read_Inputs(&inputData);

    /* 2. Determine System State & Relay Logic */
    BMS_Determine_State(&inputData, &currentBmsMode, &bRelayCmd);

    /* 3. Control Relays (Client-Server Call) */
    BMS_Control_Relays(bRelayCmd);

    /* 4. Update BMS Status Output */
    BMS_Update_Status_Output(currentBmsMode);
}
=======
#include "P_PackMeasData_TX_To_SWC_BMS_Status.h"
#include "P_PackMeasData_TX_To_SWC_ChargeMngr.h"
#include "P_PackMeasData_TX_To_SWC_SOC_Algo.h"
#include "P_PackCalculatedData_Tx_To_SWC_BMS_Status.h"
#include "P_BattStatusFlag_Tx_To_SWC_BMS_Status.h" 
>>>>>>> origin/master

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_SoX_1000ms(void)
{
}

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_PerfomCellBalancing_1000ms(void)
{
}

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_ChargeSequence_100ms(void)
{
}

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_HMI_Output_100ms(void)
{
}


FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_ReportBattInfoData_10ms(void)
{
    const uint32      vSum = s_tx_packVoltageSum;
    const sint32      cur = s_tx_packCurrent;
    const sint16      tAvg = s_tx_cellTempAverage;
    f_Voltage voltageFaultFlags;

    BmsMainCntrl_TxSvc_Send_PackMeasData_Tx(vSum, cur, mode, tAvg);
}
