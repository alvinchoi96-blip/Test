#ifndef BMSMAINCNTRL_SOC_H
#define BMSMAINCNTRL_SOC_H

#include "Platform_Types.h"

/* =========================================================
 *  SoC Facade Interface (for BMS Main Control)
 * =========================================================
 *  역할:
 *   - MainCntrl Runnable에서 호출되는 단일 진입점
 *   - Estimator / State 레이어를 내부에서 조합
 *   - RTE 의존 없이 순수 로직 레벨 API 제공
 */

/* 입력 구조체 */
typedef struct
{
    uint32 packVoltage_mV;
    sint32 packCurrent_mA;
    sint16 packTemp_dC;

    uint8  ignOn;
    uint8  chgConnected;

} BmsSoc_Input_t;

/* 출력 구조체 */
typedef struct
{
    uint16 soc_x10;     /* 0.1% scale */
    uint16 soh_x10;     /* 0.1% scale (stub) */
    uint8  socValid;   /* 0/1 */

} BmsSoc_Output_t;


/* =========================================================
 *  Public APIs
 * ========================================================= */

/* 초기화 (Power-On / Reset 1회 호출) */
void BmsMainCntrl_Soc_Init(void);

/* SoC 처리 진입점 (1000ms 주기) */
void BmsMainCntrl_Soc_Process_1000ms(const BmsSoc_Input_t* in,
                                     BmsSoc_Output_t* out);

/* SOH 처리 진입점 (stub)
 * - 현재는 빈 body
 * - 추후 SOH 알고리즘 연결 예정
 */
void BmsMainCntrl_Soh_Process(void);

#endif /* BMSMAINCNTRL_SOC_H */
