#ifndef BMS_STATUS_DETERMINE_H
#define BMS_STATUS_DETERMINE_H

#include "Rte_Type.h" /* RTE 기본 타입(Standard Types) 참조 */

/* =========================================================================
 * Application Data Type Definitions
 * (RTE에 정의되지 않은 타입들을 어플리케이션 레벨에서 정의하여 빌드 에러 해결)
 * ========================================================================= */

/* 1. Ignition Status (e_IgnStat) */
#ifndef IGN_OFF
    typedef uint8 e_IgnStat;
    #define IGN_OFF   0U
    #define IGN_ACC   1U
    #define IGN_ON    2U
    #define IGN_START 3U
#endif

/* 2. VCU Command (e_VcuCanCmd) */
#ifndef VCU_CMD_NONE
    typedef uint8 e_VcuCanCmd;
    #define VCU_CMD_NONE      0U
    #define VCU_CMD_RELAY_ON  1U
    #define VCU_CMD_RELAY_OFF 2U
#endif

/* 3. Relay Control Speed (e_relayEnableSpeed) */
#ifndef RELAY_IMMEDIATE
    typedef uint8 e_relayEnableSpeed;
    #define RELAY_IMMEDIATE 0U /* 즉시 연결 */
    #define RELAY_SOFT      1U /* 프리차지(Soft Start) 적용 */
#endif

/* 4. BMS Operation Mode (Internally managed state) */
typedef enum
{
    BMS_MODE_STANDBY = 0,
    BMS_MODE_DRIVE,
    BMS_MODE_CHARGE,
    BMS_MODE_FAULT
} BMS_OperationModeType;


/* =========================================================================
 * Sub-Function Prototypes
 * ========================================================================= */
void BMS_Logic_ReadInputs(e_IgnStat* ign, boolean* chgConn, e_VcuCanCmd* vcuCmd, boolean* isFault);
void BMS_Logic_DetermineState(e_IgnStat ign, boolean chgConn, e_VcuCanCmd vcuCmd, boolean isFault, BMS_OperationModeType* currentMode);
void BMS_Logic_ControlRelays(BMS_OperationModeType currentMode);
void BMS_Logic_WriteOutputs(BMS_OperationModeType currentMode);

#endif /* BMS_STATUS_DETERMINE_H */