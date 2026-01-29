#include "Rte_SWC_BMS_MainCntrl.h"
//#include "P_PackMeasData_TX_To_SWC_BMS_Status.h"
//#include "P_PackMeasData_TX_To_SWC_ChargeMngr.h"
//#include "P_PackMeasData_TX_To_SWC_SOC_Algo.h"
//#include "P_PackCalculatedData_Tx_To_SWC_BMS_Status.h"
//#include "P_BattStatusFlag_Tx_To_SWC_BMS_Status.h" 
#include "BmsMainCntrl_TxSvc.h"
#include "BmsStatusDetermine.h"

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


/* ==================================================================================
 * Internal Functions: Input Reading (All RTE Read APIs)
 * ================================================================================== */
static void Bms_Read_All_Inputs(void)
{
    /* 1. Signal Inputs */
    if (Rte_Read_R_SignalInput_ignSignal(&g_Input_Signal.ignSignal) != RTE_E_OK) {
        g_Input_Signal.ignSignal = LOCK; 
    }
    if (Rte_Read_R_SignalInput_chargeConnectedFlag(&g_Input_Signal.chargeConnectedFlag) != RTE_E_OK) {
        g_Input_Signal.chargeConnectedFlag = FALSE;
    }

    /* 2. VCU Command */
    if (Rte_Read_R_VcuCanCmd_bmsActionCmd(&g_Input_VcuCmd.bmsActionCmd) != RTE_E_OK) {
        g_Input_VcuCmd.bmsActionCmd = StandAlone;
    }

    /* 3. Cell Measurements */
    Rte_Read_R_CellMeasData_cellSerialNum(&g_Input_CellMeas.cellSerialNum);
    Rte_Read_R_CellMeasData_cellVoltageAverage(&g_Input_CellMeas.cellVoltageAverage);
    Rte_Read_R_CellMeasData_cellVoltageIndividual(g_Input_CellMeas.cellVoltageIndividual); /* Array */
    Rte_Read_R_CellMeasData_cellVoltageMax(&g_Input_CellMeas.cellVoltageMax);
    Rte_Read_R_CellMeasData_cellVoltageMin(&g_Input_CellMeas.cellVoltageMin);
    Rte_Read_R_CellMeasData_ibpLevel(&g_Input_CellMeas.ibpLevel);
    Rte_Read_R_CellMeasData_packVoltageSum(&g_Input_CellMeas.packVoltageSum);

    /* 4. Current Measurements */
    Rte_Read_R_CurrMeasData_packCurrent(&g_Input_CurrMeas.packCurrent);

    /* 5. Temperature Measurements */
    Rte_Read_R_TempMeasData_cellTempAverage(&g_Input_TempMeas.cellTempAverage);
    Rte_Read_R_TempMeasData_cellTempMax(&g_Input_TempMeas.cellTempMax);
    Rte_Read_R_TempMeasData_cellTempMin(&g_Input_TempMeas.cellTempMin);

    /* 6. Fault Flags - Errors (생략 없음) */
    Rte_Read_R_FaultFlag_errOverCharge(&g_Input_FaultFlag.errOverCharge);
    Rte_Read_R_FaultFlag_errOverDischarge(&g_Input_FaultFlag.errOverDischarge);
    Rte_Read_R_FaultFlag_errOverChargeCurrent(&g_Input_FaultFlag.errOverChargeCurrent);
    Rte_Read_R_FaultFlag_errOverDischargeCurrent(&g_Input_FaultFlag.errOverDischargeCurrent);
    Rte_Read_R_FaultFlag_errOverCellVmax(&g_Input_FaultFlag.errOverCellVmax);
    Rte_Read_R_FaultFlag_errUnderCellVmin(&g_Input_FaultFlag.errUnderCellVmin);
    Rte_Read_R_FaultFlag_errOverIbp(&g_Input_FaultFlag.errOverIbp);
    Rte_Read_R_FaultFlag_errIsolation(&g_Input_FaultFlag.errIsolation);
    
    Rte_Read_R_FaultFlag_errChargeOverTemp(&g_Input_FaultFlag.errChargeOverTemp);
    Rte_Read_R_FaultFlag_errChargeUnderTemp(&g_Input_FaultFlag.errChargeUnderTemp);
    Rte_Read_R_FaultFlag_errDischargeOverTemp(&g_Input_FaultFlag.errDischargeOverTemp);
    Rte_Read_R_FaultFlag_errDischargeUnderTemp(&g_Input_FaultFlag.errDischargeUnderTemp);

    /* 7. Fault Flags - Warnings (생략 없음) */
    Rte_Read_R_FaultFlag_warnOverCharge(&g_Input_FaultFlag.warnOverCharge);
    Rte_Read_R_FaultFlag_warnOverDisCharge(&g_Input_FaultFlag.warnOverDisCharge);
    Rte_Read_R_FaultFlag_warnOverChargeCurrent(&g_Input_FaultFlag.warnOverChargeCurrent);
    Rte_Read_R_FaultFlag_warnOverDischargeCurrent(&g_Input_FaultFlag.warnOverDischargeCurrent);
    Rte_Read_R_FaultFlag_warnOverCellVmax(&g_Input_FaultFlag.warnOverCellVmax);
    Rte_Read_R_FaultFlag_warnUnderCellVmin(&g_Input_FaultFlag.warnUnderCellVmin);
    Rte_Read_R_FaultFlag_warnOverIbp(&g_Input_FaultFlag.warnOverIbp);
    
    Rte_Read_R_FaultFlag_warnChargeOverTemp(&g_Input_FaultFlag.warnChargeOverTemp);
    Rte_Read_R_FaultFlag_warnChargeUnderTemp(&g_Input_FaultFlag.warnChargeUnderTemp);
    Rte_Read_R_FaultFlag_warnDischargeOverTemp(&g_Input_FaultFlag.warnDischargeOverTemp);
    Rte_Read_R_FaultFlag_warnDischargeUnderTemp(&g_Input_FaultFlag.warnDischargeUnderTemp);
}


/* ==================================================================================
 * Main Runnable: 10ms Cycle
 * ================================================================================== */
FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_BattStatusProcess_10ms()
{
    /* [Step 1] 모든 입력 데이터 전역 변수에 최신화 (다른 Runnable도 이 값을 공유) */
    Bms_Read_All_Inputs();

    /* [Step 2] 상태 판단 로직 수행 (전역 변수 사용) */
    BMS_Logic_DetermineState(&g_BmsCurrentMode);

    /* [Step 3] 릴레이 제어 수행 */
    BMS_Logic_ControlRelays(g_BmsCurrentMode);

    /* [Step 4] 출력 업데이트 */
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
