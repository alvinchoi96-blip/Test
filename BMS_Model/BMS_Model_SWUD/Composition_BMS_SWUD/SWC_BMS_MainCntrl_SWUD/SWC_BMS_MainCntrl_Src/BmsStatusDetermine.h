#ifndef BMS_STATUS_DETERMINE_H
#define BMS_STATUS_DETERMINE_H

#include "Rte_Type.h" /* RTE 기본 타입 참조 */

/* ==================================================================================
 * 1. Interface-based Data Structures (전역 데이터 타입 정의)
 * ================================================================================== */

/* [Interface: SignalInput] 시그널 입력 */
typedef struct
{
    e_IgnStat ignSignal;
    boolean chargeConnectedFlag;
} Input_Signal_Type;

/* [Interface: VcuCanCmd] VCU 명령 */
typedef struct
{
    e_VcuCanCmd bmsActionCmd;
} Input_VcuCmd_Type;

/* [Interface: CellMeasData] 셀 전압 측정 데이터 */
typedef struct
{
    uint8  cellSerialNum;
    uint16 cellVoltageAverage;
    uint16 cellVoltageMax;
    uint16 cellVoltageMin;
    uint16 ibpLevel;
    uint32 packVoltageSum;
    CellVoltageData cellVoltageIndividual; /* Array Type */
} Input_CellMeas_Type;

/* [Interface: CurrMeasData] 전류 측정 데이터 */
typedef struct
{
    sint32 packCurrent;
} Input_CurrMeas_Type;

/* [Interface: TempMeasData] 온도 측정 데이터 */
typedef struct
{
    sint16 cellTempAverage;
    sint16 cellTempMax;
    sint16 cellTempMin;
} Input_TempMeas_Type;

/* [Interface: FaultFlag] 고장 및 경고 플래그 (Full List from RTE) */
typedef struct
{
    /* --- Errors (Faults) --- */
    boolean errOverCharge;
    boolean errOverDischarge;
    boolean errOverChargeCurrent;
    boolean errOverDischargeCurrent;
    boolean errOverCellVmax;
    boolean errUnderCellVmin;
    boolean errOverIbp;
    boolean errIsolation;
    
    boolean errChargeOverTemp;
    boolean errChargeUnderTemp;
    boolean errDischargeOverTemp;
    boolean errDischargeUnderTemp;

    /* --- Warnings (Alerts) --- */
    boolean warnOverCharge;
    boolean warnOverDisCharge; /* Note: Typo in RTE API Name preserved (DisCharge) */
    boolean warnOverChargeCurrent;
    boolean warnOverDischargeCurrent;
    boolean warnOverCellVmax;
    boolean warnUnderCellVmin;
    boolean warnOverIbp;
    
    boolean warnChargeOverTemp;
    boolean warnChargeUnderTemp;
    boolean warnDischargeOverTemp;
    boolean warnDischargeUnderTemp;
} Input_FaultFlag_Type;


/* ==================================================================================
 * 2. Global Variables Declaration (외부 참조 선언)
 * ================================================================================== */
extern Input_Signal_Type    g_Input_Signal;
extern Input_VcuCmd_Type    g_Input_VcuCmd;
extern Input_CellMeas_Type  g_Input_CellMeas;
extern Input_CurrMeas_Type  g_Input_CurrMeas;
extern Input_TempMeas_Type  g_Input_TempMeas;
extern Input_FaultFlag_Type g_Input_FaultFlag;


/* ==================================================================================
 * 3. Function Prototypes
 * ================================================================================== */
/* 전역 변수를 참조하므로 인자를 최소화했습니다 */
void BMS_Logic_DetermineState(e_VcuCanCmd* currentMode);
void BMS_Logic_ControlRelays(e_VcuCanCmd currentMode);
void BMS_Logic_WriteOutputs(e_VcuCanCmd currentMode);

#endif /* BMS_STATUS_DETERMINE_H */