#ifndef BMS_MAINCNTRL_GLOBALDATA_H
#define BMS_MAINCNTRL_GLOBALDATA_H


#include "Rte_Type.h" /* RTE 기본 타입 참조 */

#define OFF 0U
#define ON  1U

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
    /* --- Summary Flags (Logic Optimization) --- */
    boolean isAnyError;   /* 하나라도 Error가 있으면 TRUE */
    boolean isAnyWarning; /* 하나라도 Warning이 있으면 TRUE */

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
 * 3. Tx Interface-based Data Structures (출력/Tx 데이터 타입 정의)
 * ================================================================================== */

 /* [Interface: PackMeasData_Tx] 측정값 Tx */
typedef struct
{
    uint32     packVoltageSum;
    sint32     packCurrent;
    sint16     cellTempAverage;
    e_VcuCanCmd bmsModeInfo;   /* 종합 상태(결정 결과)를 Tx로 송신 */
} Bms_PackMeasData_TxType;

/* [Interface: PackCalculatedData_Tx] 계산값 Tx */
typedef struct
{
    uint16 ibpLevel;
    uint16 socLevel;
    uint32 sohLevel;
    uint16 capacityLevel;
} Bms_PackCalculatedData_TxType;

/* [Interface: BattStatusFlags_Tx] 상태 플래그 Tx */
typedef struct
{
    boolean      cellBalancingFlag;
    f_Voltage    voltage;
    f_Temp       temp;
    f_Current    current;
    f_Ibp        ibp;
    f_IsolResist isol;
} Bms_BattStatusFlags_TxType;

/* [Interface: ChargeControl] 충전 시퀀스 제어 데이터 */
typedef struct
{
    uint32    chgTargetVoltage;
    uint16    chgTargetCurrent;
    e_ChgInfo chargingStatus;
} Bms_ChargeControl_Type;

/* 모드 변경 여부 판단용 구조체 */
typedef struct {
    boolean isModeChanged;
    e_VcuCanCmd previousMode;
    e_VcuCanCmd determinedMode;
} BmsModeContext_Type;

extern BmsModeContext_Type g_BmsModeContext;
extern Bms_ChargeControl_Type g_ChargeControl;

#endif /* BMS_MAINCNTRL_GLOBALDATA_H */
