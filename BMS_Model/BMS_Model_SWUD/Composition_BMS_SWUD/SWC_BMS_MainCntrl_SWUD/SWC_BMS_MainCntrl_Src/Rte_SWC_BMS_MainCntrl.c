#include "Rte_SWC_BMS_MainCntrl.h"
#include "BMS_MainCntrl_GlobalData.h"
#include "BmsMainCntrl_Soc.h"
#include "Bms_StatusDecision.h"



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

/* SOC Output 용 변수 할당*/
BmsSoc_Output_t soc_Out;
uint32 calculateSohValue;

static BmsModeContext_Type g_BmsModeContext = {BmsMd_StandAlone, BmsMd_StandAlone, FALSE};

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_InputDataRead_10ms(void)
{
    /* 1. 입력 처리: 모든 센서 및 신호 읽기 */
    BMS_Input_ProcessAll();
}

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_BattStatusProcess_10ms(void)
{
    e_FaultLevel currentFaultLevel;

    /* 2. 고장 진단: 현재 결함 상태 확인 */
    currentFaultLevel = BMS_Logic_CheckFaults();

    /* 3. 모드 결정 로직: 조건에 따라 구체적인 모드 설정 함수 호출 */
    /* 다이어그램 상에서 분기별로 서로 다른 함수가 호출되는 모습이 표현됨 */
    if (currentFaultLevel == FltLv_Error)
    {
        /* 치명적 오류 시 긴급 모드 설정 함수 호출 */
        BMS_Logic_SetEmergencyMode();
    }
    else
    {
        /* 정상 또는 경고 수준일 때 운전 모드 판단 함수 호출 */
        BMS_Logic_DetermineNormalOperation();
    }

    /* 4. 물리적 제어 실행: 결정된 모드에 맞춰 릴레이/컨택터 구동 */
    BMS_Logic_ExecuteControl(g_BmsModeContext.determinedMode);

    /* 5. 출력 업데이트: 최종 데이터 및 상태 플래그 송신 */
    BMS_Logic_UpdateOutputs(g_BmsModeContext.determinedMode);
}

FUNC(void, SWC_BMS_MainCntrl_CODE) REtSWC_BMS_MainCntrl_SoX_1000ms(void)
{
    //Workspace by KSM.
    /* SOC Read Section */
    BmsMainCntrl_Soc_Process_1000ms(&soc_Out);
    
     /* RTE Write (PackCalculatedData_Tx) */
    (void)Rte_Write_P_PackCalculatedData_Tx_socLevel(soc_Out.soc_x10);
    /* RTE는 sohLevel이 uint32라서 확장 캐스팅 */
    (void)Rte_Write_P_PackCalculatedData_Tx_sohLevel((uint32)soc_Out.soh_x10);
    /*  HMI 게이지: 0~100%로 보고 싶으면 out.soc_x10(0~1000)을 0~100으로 변환 */
    (void)Rte_Write_P_HMI_SigOutput_socGauge((uint8)(soc_Out.soc_x10 / 10u));

    /* SOH 진행 판단 */
    BmsMainCntrl_Soh_Process_1000ms(g_BmsModeContext, &calculateSohValue);
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
    BMS_TxMap_ReportBattInfo(g_BmsModeContext.determinedMode, &txMeas, &txCalc, &txFlag);

    Bms_Tx_PackMeasData_Write(&txMeas);
    Bms_Tx_PackCalculatedData_Write(&txCalc);
    Bms_Tx_BattStatusFlags_Write(&txFlag);
}
