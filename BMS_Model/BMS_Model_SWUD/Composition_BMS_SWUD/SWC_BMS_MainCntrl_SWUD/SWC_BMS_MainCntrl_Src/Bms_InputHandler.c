/**
 * @file BmsInputHandler.c
 * @brief Handles RTE reading and Input Validation
 */

#include "BmsStatusDetermine.h"
#include "Rte_SWC_BMS_MainCntrl.h"

/* 전역 변수 메모리 할당 (이 파일에 위치) */
Input_Signal_Type    g_Input_Signal;
Input_VcuCmd_Type    g_Input_VcuCmd;
Input_CellMeas_Type  g_Input_CellMeas;
Input_CurrMeas_Type  g_Input_CurrMeas;
Input_TempMeas_Type  g_Input_TempMeas;
Input_FaultFlag_Type g_Input_FaultFlag;

/*******************************************************************************
 * Function: BMS_Input_ProcessAll
 * Description: 모든 입력을 읽고 유효성 검증 함수를 호출
 *******************************************************************************/
void BMS_Input_ProcessAll(void)
{
    /* 1. RTE Read Calls (Raw Data Acquisition) */
    /* Signals */
    (void)Rte_Read_R_SignalInput_ignSignal(&g_Input_Signal.ignSignal);
    (void)Rte_Read_R_SignalInput_chargeConnectedFlag(&g_Input_Signal.chargeConnectedFlag);
    
    /* VCU Cmd */
    (void)Rte_Read_R_VcuCanCmd_bmsActionCmd(&g_Input_VcuCmd.bmsActionCmd);

    /* Measurements */
    (void)Rte_Read_R_CellMeasData_packVoltageSum(&g_Input_CellMeas.packVoltageSum);
    (void)Rte_Read_R_CurrMeasData_packCurrent(&g_Input_CurrMeas.packCurrent);
    /* ... (나머지 Read 함수들 - 이전 코드 참조) ... */
    
    /* Fault Flags Read */
    (void)Rte_Read_R_FaultFlag_errOverCharge(&g_Input_FaultFlag.errOverCharge);
    /* ... (모든 Fault Read - 이전 코드 참조) ... */

    /* 2. Validate Inputs (Nested Call for Sequence Diagram) */
    if (BMS_Input_ValidateSignals() == FALSE)
    {
        /* 유효하지 않은 신호 감지 시 안전값 강제 설정 (시퀀스 표현용 로직) */
        g_Input_VcuCmd.bmsActionCmd = StandAlone;
        g_Input_Signal.ignSignal = LOCK;
    }
}

/*******************************************************************************
 * Function: BMS_Input_ValidateSignals
 * Description: 입력값의 정합성 체크 (시퀀스 다이어그램용 Depth 추가)
 *******************************************************************************/
boolean BMS_Input_ValidateSignals(void)
{
    /* 예: 전압이 0인데 전류가 흐르는 경우 -> 센서 에러 가능성 */
    if ((g_Input_CellMeas.packVoltageSum < 100U) && (g_Input_CurrMeas.packCurrent > 500))
    {
        return FALSE; /* Invalid */
    }
    
    /* 예: Ignition이 OFF인데 VCU가 구동 명령을 내리는 경우 */
    if ((g_Input_Signal.ignSignal == LOCK) && (g_Input_VcuCmd.bmsActionCmd == Driving))
    {
        return FALSE; /* Invalid Command */
    }

    return TRUE; /* Valid */
}