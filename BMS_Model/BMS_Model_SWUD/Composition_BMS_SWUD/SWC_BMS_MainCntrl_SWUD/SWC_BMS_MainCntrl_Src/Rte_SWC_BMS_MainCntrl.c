#include "Rte_SWC_BMS_MainCntrl.h"
#include "BmsMainCntrl_TxSvc.h"

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

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_BattStatusProcess_10ms(void)
{

}

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
    const e_VcuCanCmd mode = s_tx_bmsModeInfo;
    const sint16      tAvg = s_tx_cellTempAverage;

    BmsMainCntrl_TxSvc_Send_PackMeasData_Tx(vSum, cur, mode, tAvg);
}
