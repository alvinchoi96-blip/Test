#ifndef BMS_STATUS_DECISION_H
#define BMS_STATUS_DECISION_H

#include "Rte_Type.h"


/* 입력 데이터를 읽고, 유효성 검증(Validation)까지 수행하는 메인 함수 */
void BMS_Input_ProcessAll(void);

/*신호 유효성 검증 함수 */
boolean BMS_Input_ValidateSignals(void);


/* 전체 로직 시퀀스 실행 */
void BMS_Logic_MainSequence(void);

/* 세부 로직 함수들 */
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