#ifndef BMS_STATUS_DECISION_H
#define BMS_STATUS_DECISION_H

#include "Rte_Type.h"

/* 기존 함수 */
void BMS_Input_ProcessAll(void);
e_FaultLevel BMS_Logic_CheckFaults(void);

/* [NEW] 다이어그램 표현을 위해 세분화된 함수들 */
void BMS_Logic_SetEmergencyMode(void);
void BMS_Logic_DetermineNormalOperation(void);

/* 제어 및 출력 함수 (ControlExecutor 쪽이지만 편의상 여기서 참조하거나 별도 헤더 분리 권장) */
void BMS_Logic_ExecuteControl(e_VcuCanCmd targetMode);
void BMS_Logic_UpdateOutputs(e_VcuCanCmd currentMode);

#endif /* BMS_STATUS_DECISION_H */