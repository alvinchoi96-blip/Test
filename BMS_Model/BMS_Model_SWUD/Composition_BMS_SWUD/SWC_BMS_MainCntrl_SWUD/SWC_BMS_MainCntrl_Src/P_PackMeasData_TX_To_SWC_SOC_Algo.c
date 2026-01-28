#include "P_PackMeasData_TX_To_SWC_SOC_Algo.h"

void P_PackMeasData_TX_To_SWC_SOC_Algo_Write(uint32 packVoltageSum, sint32 packCurrent, e_VcuCanCmd bmsModeInfo, sint16 cellTempAverage)
{
    Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_packVoltageSum(packVoltageSum);
    Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_packCurrent(packCurrent);
    Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_bmsModeInfo(bmsModeInfo);
    Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_cellTempAverage(cellTempAverage);
}