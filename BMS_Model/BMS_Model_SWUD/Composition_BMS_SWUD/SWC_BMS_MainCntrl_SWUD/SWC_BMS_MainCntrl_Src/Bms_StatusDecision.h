#ifndef BMS_STATUS_DETERMINE_H
#define BMS_STATUS_DETERMINE_H

#include "Rte_Type.h"


/* 입력 데이터를 읽고, 유효성 검증(Validation)까지 수행하는 메인 함수 */
void BMS_Input_ProcessAll(void);

/*신호 유효성 검증 함수 */
boolean BMS_Input_ValidateSignals(void);


/* 전체 로직 시퀀스 실행 */
void BMS_Logic_MainSequence(void);

/* 세부 로직 함수들 */
e_FaultLevel BMS_Logic_CheckFaults(void);
e_VcuCanCmd BMS_Logic_DecideOperationMode(boolean isFault);
void BMS_Logic_ExecuteControl(e_VcuCanCmd targetMode);
void BMS_Logic_UpdateOutputs(e_VcuCanCmd currentMode);

#endif /* BMS_STATUS_DETERMINE_H */