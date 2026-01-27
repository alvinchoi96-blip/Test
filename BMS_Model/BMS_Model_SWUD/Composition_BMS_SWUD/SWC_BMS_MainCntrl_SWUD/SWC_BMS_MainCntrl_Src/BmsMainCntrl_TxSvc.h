#ifndef BMSMAINCNTRL_TXSVC_H
#define BMSMAINCNTRL_TXSVC_H

#include "Rte_SWC_BMS_MainCntrl.h"
/* Rte_SWC_BMS_MainCntrl.h 내부에서 보통 Std_Types.h가 포함되지만,
 * 환경에 따라 누락될 수 있어 안전하게 명시해도 됨.
 * (중복 include는 헤더가드로 안전)
 */
#include "Std_Types.h"

 /* ====== 옵션: 값 범위(프로젝트 스케일에 맞게 조정) ====== */
#define BMS_TX_PACK_VOLT_SUM_MIN   (0UL)
#define BMS_TX_PACK_VOLT_SUM_MAX   (500000UL)

#define BMS_TX_PACK_CURR_MIN       ((sint32)-100000L)
#define BMS_TX_PACK_CURR_MAX       ((sint32) 100000L)

#define BMS_TX_CELL_TEMP_MIN       ((sint16)-400)
#define BMS_TX_CELL_TEMP_MAX       ((sint16) 1250)

/* 10ms마다 항상 송신(Port: P_PackMeasData_Tx, TargetData 4개) */
Std_ReturnType BmsMainCntrl_TxSvc_Send_PackMeasData_Tx(
    uint32      packVoltageSum,
    sint32      packCurrent,
    e_VcuCanCmd bmsModeInfo,
    sint16      cellTempAverage
);

/* (선택) 마지막 송신 결과 조회 */
Std_ReturnType BmsMainCntrl_TxSvc_GetLastPackMeasTxResult(void);

#endif /* BMSMAINCNTRL_TXSVC_H */
