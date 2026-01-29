#include "Rte_SWC_BMS_MainCntrl.h"
#include "BMS_MainCntrl_GlobalData.h"
#include "Bms_StatusDetermine.h"

/* ==================================================================================
 * Global Variables Definition (실제 메모리 할당)
 * ================================================================================== */
Input_Signal_Type    g_Input_Signal;
Input_VcuCmd_Type    g_Input_VcuCmd;
Input_CellMeas_Type  g_Input_CellMeas;
Input_CurrMeas_Type  g_Input_CurrMeas;
Input_TempMeas_Type  g_Input_TempMeas;
Input_FaultFlag_Type g_Input_FaultFlag;

/* 내부 상태 관리 변수 */
static e_VcuCanCmd g_BmsCurrentMode = Standby;

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_BattStatusProcess_10ms()
{
    BMS_Input_ProcessAll();
    BMS_Logic_MainSequence(&g_BmsCurrentMode);
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
