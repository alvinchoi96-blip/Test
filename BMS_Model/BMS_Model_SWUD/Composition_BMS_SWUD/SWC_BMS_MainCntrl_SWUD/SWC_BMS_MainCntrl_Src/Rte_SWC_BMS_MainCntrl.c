#include "Rte_SWC_BMS_MainCntrl.h"
#include "BMS_MainCntrl_GlobalData.h"
#include "Bms_StatusDetermine.h"
#include "BmsMainCntrl_Soc.h"

/* ==================================================================================
 * Global Variables Definition (실제 메모리 할당)
 * ================================================================================== */
Input_Signal_Type    g_Input_Signal;
Input_VcuCmd_Type    g_Input_VcuCmd;
Input_CellMeas_Type  g_Input_CellMeas;
Input_CurrMeas_Type  g_Input_CurrMeas;
Input_TempMeas_Type  g_Input_TempMeas;
Input_FaultFlag_Type g_Input_FaultFlag;

/* Soc 판단용 선언 */
Std_ReturnType ret;
uint32  packVoltageSum_u32;
sint32  packCurrent_s32;
sint16  cellTempAvg_s16;
e_IgnStat ignSignal;
boolean chgConnectedFlag;

BmsSoc_Input_t in;
BmsSoc_Output_t out;

/* 내부 상태 관리 변수 */
static e_VcuCanCmd g_BmsCurrentMode = Standby;

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_BattStatusProcess_10ms()
{
    BMS_Input_ProcessAll();
    BMS_Logic_MainSequence(&g_BmsCurrentMode);
}

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_SoX_1000ms(void)
{
    //Workspace by KSM.
    /* Read Section */
    /* 1) RTE Read */
    ret = Rte_Read_R_CellMeasData_packVoltageSum(&packVoltageSum_u32);
    (void)ret;

    ret = Rte_Read_R_CurrMeasData_packCurrent(&packCurrent_s32);
    (void)ret;

    ret = Rte_Read_R_TempMeasData_cellTempAverage(&cellTempAvg_s16);
    (void)ret;

    ret = Rte_Read_R_SignalInput_ignSignal(&ignSignal);
    (void)ret;

    ret = Rte_Read_R_SignalInput_chargeConnectedFlag(&chgConnectedFlag);
    (void)ret;

    /* 2) SoC 입력 구성 (현재 SoC 모듈 타입에 맞춰 축소 캐스팅) */
    in.packVoltage_mV  = Bms_ClampU32ToU16(packVoltageSum_u32); /* TODO: SoC 모듈이 uint32로 받는 게 더 정확 */
    in.packCurrent_mA  = Bms_ClampS32ToS16(packCurrent_s32);    /* TODO: SoC 모듈이 sint32로 받는 게 더 정확 */
    in.packTemp_dC     = cellTempAvg_s16;

    /* ignOn/chgConnected는 “존재 여부”만 필요해서 0/1로 정규화 */
    in.ignOn           = (ignSignal != (e_IgnStat)0) ? (uint8)1u : (uint8)0u;
    in.chgConnected    = (chgConnectedFlag != (boolean)0) ? (uint8)1u : (uint8)0u;

    /* 3) SoC Process 진행 */
    BmsMainCntrl_Soc_Process_1000ms(&in, &out);
    
     /* 4) RTE Write (PackCalculatedData_Tx) */
    (void)Rte_Write_P_PackCalculatedData_Tx_socLevel(out.soc_x10);

    /* RTE는 sohLevel이 uint32라서 확장 캐스팅 */
    (void)Rte_Write_P_PackCalculatedData_Tx_sohLevel((uint32)out.soh_x10);

    /*  HMI 게이지: 0~100%로 보고 싶으면 out.soc_x10(0~1000)을 0~100으로 변환 */
    (void)Rte_Write_P_HMI_SigOutput_socGauge((uint8)(out.soc_x10 / 10u));

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
