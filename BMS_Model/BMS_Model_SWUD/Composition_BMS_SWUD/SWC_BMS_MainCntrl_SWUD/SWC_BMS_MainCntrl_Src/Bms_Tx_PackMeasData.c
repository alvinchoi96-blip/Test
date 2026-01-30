#include "Rte_SWC_BMS_MainCntrl.h"
#include "Bms_TxMapper_ReportBattInfo.h"

/* 송신 분기 제어를 위한 상태값 */
typedef enum
{
    TX_POLICY_NORMAL = 0,   /* 전체 DataElement 송신 */
    TX_POLICY_LIMITED,      /* 제한 송신 */
    TX_POLICY_BLOCK         /* 송신 차단 */
} TxPolicyType;

void Bms_Tx_PackMeasData_Write(const Bms_PackMeasData_TxType* txData)
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
        /* 현재 구현 기준: Emergency 모드이면 제한 송신 분기로 진입 */
        if (txData->bmsModeInfo == BmsMd_Emergency)
        {
            policy = TX_POLICY_LIMITED;
        }
    }

    /* 분기별 송신 처리 */
    switch (policy)
    {
        case TX_POLICY_NORMAL:
            /* P_PackMeasData_Tx: 전체 DataElement 송신 */
            (void)Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_packVoltageSum(txData->packVoltageSum);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_packCurrent(txData->packCurrent);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_cellTempAverage(txData->cellTempAverage);
            (void)Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_bmsModeInfo(txData->bmsModeInfo);
            break;

        case TX_POLICY_LIMITED:
            /* P_PackMeasData_Tx: 제한 송신(현재 구현 기준: bmsModeInfo만 송신) */
            (void)Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_bmsModeInfo(txData->bmsModeInfo);
            break;

        case TX_POLICY_BLOCK:
        default:
            /* 송신 차단: Rte_Write 호출 없음 */
            break;
    }
}
