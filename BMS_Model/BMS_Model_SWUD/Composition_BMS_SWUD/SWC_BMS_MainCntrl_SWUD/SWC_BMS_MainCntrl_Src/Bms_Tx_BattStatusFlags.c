#include "Rte_SWC_BMS_MainCntrl.h"
#include "Bms_TxMapper_ReportBattInfo.h"

/* 송신 분기 제어를 위한 상태값 */
typedef enum
{
    TX_POLICY_NORMAL = 0,   /* 전체 DataElement 송신 */
    TX_POLICY_LIMITED,      /* 제한 송신 */
    TX_POLICY_BLOCK         /* 송신 차단 */
} TxPolicyType;

void Bms_Tx_BattStatusFlags_Write(const Bms_BattStatusFlags_TxType* txData)
{
    /* 송신 분기 선택 변수 */
    TxPolicyType policy = TX_POLICY_NORMAL;

    /* 입력 포인터 유효성 검사 */
    if (txData == NULL_PTR)
    {
        /* 입력 데이터가 없으면 송신을 수행하지 않음 */
        policy = TX_POLICY_BLOCK;
    }
    else
    {
        /* isol.errIsolation == TRUE이면 제한 송신 분기로 진입 */
        if (txData->isol.errIsolation == TRUE)
        {
            policy = TX_POLICY_LIMITED;
        }
    }

    /* 분기별 송신 처리 */
    switch (policy)
    {
        case TX_POLICY_NORMAL:
            /* P_BattStatusFlags_Tx: 전체 DataElement 송신 */
            (void)Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_cellBalancingFlag(txData->cellBalancingFlag);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_voltageFaultFlags(&txData->voltage);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_tempFaultFlags(&txData->temp);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_currentFaultFlags(&txData->current);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_ibpFaultFlags(&txData->ibp);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_packIsolationFaultFlag(&txData->isol);
            break;

        case TX_POLICY_LIMITED:
            /* P_BattStatusFlags_Tx: 제한 송신(현재 구현 기준: isol + balancing 강제 FALSE 송신) */
            (void)Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_packIsolationFaultFlag(&txData->isol);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_cellBalancingFlag(FALSE);
            break;

        case TX_POLICY_BLOCK:
        default:
            /* 송신 차단: Rte_Write 호출 없음 */
            break;
    }
}
