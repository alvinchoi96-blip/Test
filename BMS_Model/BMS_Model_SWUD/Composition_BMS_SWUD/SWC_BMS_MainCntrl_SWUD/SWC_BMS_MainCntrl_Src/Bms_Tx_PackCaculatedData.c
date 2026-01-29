#include "Bms_Tx_PackCalculatedData.h"
#include "Rte_SWC_BMS_MainCntrl.h"

/* 송신 분기 제어를 위한 상태값 */
typedef enum
{
    TX_POLICY_NORMAL = 0,   /* 전체 DataElement 송신 */
    TX_POLICY_LIMITED,      /* 제한 송신 */
    TX_POLICY_BLOCK         /* 송신 차단 */
} TxPolicyType;

void Bms_Tx_PackCalculatedData_Write(const Bms_PackCalculatedData_TxType* txData)
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
        /* soc/soh/capacity가 모두 0이면 제한 송신 분기로 진입 */
        if ((txData->socLevel == 0U) && (txData->sohLevel == 0U) && (txData->capacityLevel == 0U))
        {
            policy = TX_POLICY_LIMITED;
        }
    }

    /* 분기별 송신 처리 */
    switch (policy)
    {
        case TX_POLICY_NORMAL:
            /* P_PackCalculatedData_Tx: 전체 DataElement 송신 */
            (void)Rte_Write_SWC_BMS_MainCntrl_P_PackCalculatedData_Tx_ibpLevel(txData->ibpLevel);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_PackCalculatedData_Tx_socLevel(txData->socLevel);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_PackCalculatedData_Tx_sohLevel(txData->sohLevel);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_PackCalculatedData_Tx_capacityLevel(txData->capacityLevel);
            break;

        case TX_POLICY_LIMITED:
            /* P_PackCalculatedData_Tx: 제한 송신(현재 구현 기준: ibpLevel만 송신) */
            (void)Rte_Write_SWC_BMS_MainCntrl_P_PackCalculatedData_Tx_ibpLevel(txData->ibpLevel);
            break;

        case TX_POLICY_BLOCK:
        default:
            /* 송신 차단: Rte_Write 호출 없음 */
            break;
    }
}
