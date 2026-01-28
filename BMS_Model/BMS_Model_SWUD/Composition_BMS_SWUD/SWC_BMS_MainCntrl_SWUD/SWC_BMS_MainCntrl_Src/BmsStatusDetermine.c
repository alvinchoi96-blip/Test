/**
 * @file BmsStatusDetermine.c
 * @brief BMS Detailed Logic Implementation
 */

#include "BmsStatusDetermine.h"
#include "Rte_SWC_BMS_MainCntrl.h" /* RTE API 사용을 위해 포함 */

/*******************************************************************************
 * Function: BMS_Logic_ReadInputs
 * Description: RTE 포트를 통해 외부 신호 수신
 *******************************************************************************/
void BMS_Logic_ReadInputs(e_IgnStat* ign, boolean* chgConn, e_VcuCanCmd* vcuCmd, boolean* isFault)
{
    /* 1. Ignition Status 읽기 */
    if (Rte_Read_rp_SigInput_ignStatus(ign) != RTE_E_OK) {
        *ign = IGN_OFF; /* Read Fail 시 안전값(OFF) 설정 */
    }

    /* 2. 충전기 연결 상태 읽기 */
    if (Rte_Read_rp_SigInput_chargerConnectedFlag(chgConn) != RTE_E_OK) {
        *chgConn = FALSE;
    }

    /* 3. VCU 상위 제어기 명령 읽기 */
    if (Rte_Read_rp_VcuCanCmd_bmsActionCmd(vcuCmd) != RTE_E_OK) {
        *vcuCmd = VCU_CMD_NONE;
    }

    /* 4. 고장 상태 읽기 (FaultDTC 컴포넌트로부터) */
    if (Rte_Read_rp_FaultInfo_isFaultActive(isFault) != RTE_E_OK) {
        *isFault = TRUE; /* 통신 실패 시 안전을 위해 Fault로 간주 */
    }
}

/*******************************************************************************
 * Function: BMS_Logic_DetermineState
 * Description: 입력값 우선순위에 따라 BMS 운전 모드 결정
 *******************************************************************************/
void BMS_Logic_DetermineState(e_IgnStat ign, boolean chgConn, e_VcuCanCmd vcuCmd, boolean isFault, BMS_OperationModeType* currentMode)
{
    /* Priority 1: Critical Fault (최우선: 고장 발생 시) */
    if (isFault == TRUE)
    {
        *currentMode = BMS_MODE_FAULT;
    }
    /* Priority 2: VCU Force Relay ON (상위 제어기 강제 구동 명령) */
    else if (vcuCmd == VCU_CMD_RELAY_ON)
    {
        *currentMode = BMS_MODE_DRIVE;
    }
    /* Priority 3: Charger Connected (충전기 연결 시) */
    else if (chgConn == TRUE)
    {
        *currentMode = BMS_MODE_CHARGE;
    }
    /* Priority 4: Ignition Active (시동 키 ON 또는 START) */
    else if ((ign == IGN_ON) || (ign == IGN_START))
    {
        *currentMode = BMS_MODE_DRIVE;
    }
    /* Default: Standby (그 외 대기 상태) */
    else
    {
        *currentMode = BMS_MODE_STANDBY;
    }
}

/*******************************************************************************
 * Function: BMS_Logic_ControlRelays
 * Description: 결정된 모드에 따라 RelayDriver 컴포넌트에 명령(C/S Call) 전송
 *******************************************************************************/
void BMS_Logic_ControlRelays(BMS_OperationModeType currentMode)
{
    /* Drive 또는 Charge 모드일 때만 릴레이 연결 */
    if ((currentMode == BMS_MODE_DRIVE) || (currentMode == BMS_MODE_CHARGE))
    {
        /* Relay Enable 요청 (Soft Start 적용) */
        /* 정의된 상수 RELAY_SOFT(1) 사용 */
        (void)Rte_Call_cp_RelayControlReq_relayEnableReq(RELAY_SOFT);
    }
    else
    {
        /* Relay Disable 요청 (즉시 차단) */
        (void)Rte_Call_cp_RelayControlReq_relayDisableReq();
    }
}

/*******************************************************************************
 * Function: BMS_Logic_WriteOutputs
 * Description: 현재 BMS 상태를 외부로 출력
 *******************************************************************************/
void BMS_Logic_WriteOutputs(BMS_OperationModeType currentMode)
{
    /* BMS 현재 모드를 P-Port로 송신 */
    (void)Rte_Write_pp_BmsModeInfo_bmsMode(currentMode);
}