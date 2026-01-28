#include "Rte_SWC_BMS_MainCntrl.h"
//#include "P_PackMeasData_TX_To_SWC_BMS_Status.h"
//#include "P_PackMeasData_TX_To_SWC_ChargeMngr.h"
//#include "P_PackMeasData_TX_To_SWC_SOC_Algo.h"
//#include "P_PackCalculatedData_Tx_To_SWC_BMS_Status.h"
//#include "P_BattStatusFlag_Tx_To_SWC_BMS_Status.h" 

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
    /*  
        P_PackMeasData_TX_To_SWC_BMS_Status DataElement 변수 선언
        P_PackMeasData_TX_To_SWC_BMS_ChargeMngr DataElement 변수 선언
        P_PackMeasData_TX_To_SWC_BMS_SOC_Algo DataElement 변수 선언
    */
    uint32 packVoltageSum;
    sint32 packCurrent; 
    e_VcuCanCmd bmsModeInfo;
    sint16 cellTempAverage;

    /* P_PackCalculatedData_Tx_To_SWC_BMS_Status DataElements 변수 선언 */
    uint16 ibpLevel;

    /* P_BattStatusFlag_Tx_To_SWC_BMS_Status DataElements 변수 선언 */
    f_Voltage voltageFaultFlags; //Struct
    f_Temp tempFaultFlags; // Struct
    f_Current  currentFaultFlags; //Struct
    f_Ibp ibpFaultFlags; //Struct
    f_IsolResist packIsolationFaultFlag; //Struct
    

    Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_packVoltageSum(packVoltageSum);
    Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_packCurrent(packCurrent);
    Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_bmsModeInfo(bmsModeInfo);
    Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_cellTempAverage(cellTempAverage);

    Rte_Write_SWC_BMS_MainCntrl_P_PackCalculatedData_Tx_ibpLevel(ibpLevel);

    Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_voltageFaultFlags(&voltageFaultFlags);
    Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_tempFaultFlags(&tempFaultFlags);
    Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_currentFaultFlags(&currentFaultFlags);
    Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_ibpFaultFlags(&ibpFaultFlags);
    Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_packIsolationFaultFlag(&packIsolationFaultFlag);
}
