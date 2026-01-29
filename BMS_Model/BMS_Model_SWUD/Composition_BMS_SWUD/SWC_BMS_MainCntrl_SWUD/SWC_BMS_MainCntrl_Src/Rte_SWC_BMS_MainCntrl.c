#include "Rte_SWC_BMS_MainCntrl.h"
#include "BMS_MainCntrl_GlobalData.h"
#include "Bms_StatusDetermine.h"


#include "Bms_Tx_PackMeasData.h"
#include "Bms_Tx_PackCalculatedData.h"
#include "Bms_Tx_BattStatusFlags.h"
#include "Bms_TxMapper_ReportBattInfo.h"

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

/*******************************************************************************
 * Runnable: REtSWC_BMS_MainCntrl_ReportBattInfoData_10ms
 * Purpose : 배터리 종합 상태를 Tx 데이터(Port DataElement)로 송신한다.
 *
 * Sequence:
 *  1) Tx 매핑 수행
 *     - BMS_TxMap_ReportBattInfo()
 *     - 전역 입력 데이터(g_Input_*)와 현재 모드(g_BmsCurrentMode)를 참조하여
 *       다음 Tx 구조체를 구성한다.
 *         a) Bms_PackMeasData_TxType
 *         b) Bms_PackCalculatedData_TxType
 *         c) Bms_BattStatusFlags_TxType
 *
 *  2) PackMeasData 송신
 *     - Bms_Tx_PackMeasData_Write()
 *     - P_PackMeasData_Tx 포트의 DataElement를 Rte_Write로 송신한다.
 *
 *  3) PackCalculatedData 송신
 *     - Bms_Tx_PackCalculatedData_Write()
 *     - P_PackCalculatedData_Tx 포트의 DataElement를 Rte_Write로 송신한다.
 *
 *  4) BattStatusFlags 송신
 *     - Bms_Tx_BattStatusFlags_Write()
 *     - P_BattStatusFlags_Tx 포트의 DataElement를 Rte_Write로 송신한다.
 *
 * Notes:
 *  - 입력 Read 및 상태 판단(모드 결정)은 다른 Runnable에서 수행되며,
 *    본 Runnable은 매핑 및 송신(Report)만 수행한다.
 ******************************************************************************/
FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_ReportBattInfoData_10ms(void)
{
    Bms_PackMeasData_TxType       txMeas = {0};
    Bms_PackCalculatedData_TxType txCalc = {0};
    Bms_BattStatusFlags_TxType    txFlag = {0};

    /* 다른 Runnable에서 결정한 상태를 그대로 사용 */
    BMS_TxMap_ReportBattInfo(g_BmsCurrentMode, &txMeas, &txCalc, &txFlag);

    Bms_Tx_PackMeasData_Write(&txMeas);
    Bms_Tx_PackCalculatedData_Write(&txCalc);
    Bms_Tx_BattStatusFlags_Write(&txFlag);
}
