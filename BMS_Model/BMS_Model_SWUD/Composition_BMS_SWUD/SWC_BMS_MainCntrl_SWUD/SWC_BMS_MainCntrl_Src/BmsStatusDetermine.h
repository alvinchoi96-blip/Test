#ifndef SWC_BMS_MAINCNTRL_INTERNAL_H
#define SWC_BMS_MAINCNTRL_INTERNAL_H

#include "Rte_Type.h" // Standard AUTOSAR Types

/* Define internal data structure for cleaner passing */
typedef struct
{
    e_IgnStat ignStatus;
    boolean isChargerConnected;
    e_VcuCanCmd vcuCmd;
    boolean isFaultActive;
} BmsInputData;

/* Internal BMS Operation Modes */
typedef enum
{
    BMS_MODE_INIT = 0,
    BMS_MODE_STANDBY,
    BMS_MODE_DRIVE,
    BMS_MODE_CHARGE,
    BMS_MODE_FAULT,
    BMS_MODE_SLEEP
} BMS_OperationModeType;

/* Sub-function prototypes */
void BMS_Read_Inputs(BmsInputData *pData);
void BMS_Determine_State(const BmsInputData *pData, BMS_OperationModeType *pMode, boolean *pRelayEnable);
void BMS_Control_Relays(boolean enable);
void BMS_Update_Status_Output(BMS_OperationModeType mode);

#endif /* SWC_BMS_MAINCNTRL_INTERNAL_H */