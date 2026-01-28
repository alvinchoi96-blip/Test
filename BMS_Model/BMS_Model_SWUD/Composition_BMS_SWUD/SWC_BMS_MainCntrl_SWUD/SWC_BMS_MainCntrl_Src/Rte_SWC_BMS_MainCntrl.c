#include "Rte_SWC_BMS_MainCntrl.h"
#include "BmsMainCntrl_TxSvc.h"
#include "BmsStatusDetermine.h"
#include "P_PackMeasData_TX_To_SWC_BMS_Status.h"
#include "P_PackMeasData_TX_To_SWC_ChargeMngr.h"
#include "P_PackMeasData_TX_To_SWC_SOC_Algo.h"
#include "P_PackCalculatedData_Tx_To_SWC_BMS_Status.h"
#include "P_BattStatusFlag_Tx_To_SWC_BMS_Status.h" 
    /* 전역 상태 변수 (10ms 주기 간 상태 유지용) */
static BMS_OperationModeType g_BmsCurrentMode = BMS_MODE_STANDBY;

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_BattStatusProcess_10ms(void)
{

/* 로컬 변수: 데이터 흐름 제어용 */
    e_IgnStat ignStatus;
    boolean isChargerConnected;
    e_VcuCanCmd vcuCommand;
    boolean isFaultActive;

    /* 1. 입력 단계 (Input Phase) */
    BMS_Logic_ReadInputs(&ignStatus, &isChargerConnected, &vcuCommand, &isFaultActive);

    /* 2. 판단 단계 (Logic Phase) */
    BMS_Logic_DetermineState(ignStatus, isChargerConnected, vcuCommand, isFaultActive, &g_BmsCurrentMode);

    /* 3. 제어 단계 (Control Phase) */
    BMS_Logic_ControlRelays(g_BmsCurrentMode);

    /* 4. 출력 단계 (Output Phase) */
    BMS_Logic_WriteOutputs(g_BmsCurrentMode);
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
    f_Voltage voltageFaultFlags;
    f_Temp tempFaultFlags;
    f_Current  currentFaultFlags;
    f_Ibp ibpFaultFlags;
    f_IsolResist packIsolationFaultFlag;
    boolean cellBalancingFlag;

    /* P_PackMeasData_TX_To_SWC_BMS_Status 함수 선언*/
    P_PackMeasData_TX_To_SWC_BMS_Status_Write(packVoltageSum, packCurrent, bmsModeInfo, cellTempAverage);

    /* P_PackMeasData_TX_To_SWC_BMS_ChargeMngr 함수 선언*/
    P_PackMeasData_TX_To_SWC_BMS_ChargeMngr_Write(packVoltageSum, packCurrent, bmsModeInfo, cellTempAverage);

    /* P_PackMeasData_TX_To_SWC_BMS_SOC_Algo 함수 선언*/
    P_PackMeasData_TX_To_SWC_BMS_SOC_Algo_Write(packVoltageSum, packCurrent, bmsModeInfo, cellTempAverage);

    /* P_PackCalculatedData_Tx_To_SWC_BMS_Status 함수 선언*/
    P_PackCalculatedData_Tx_To_SWC_BMS_Status_Write(ibpLevel);

    /* P_BattStatusFlag_Tx_To_SWC_BMS_Status 함수 선언*/
    P_BattStatusFlag_Tx_To_SWC_BMS_Status_Write(voltageFaultFlags, tempFaultFlags, currentFaultFlags, ibpFaultFlags, packIsolationFaultFlag, cellBalancingFlag);

}
