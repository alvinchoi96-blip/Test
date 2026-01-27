#ifndef RTE_SWC_CHARGEMNGR_H
#define RTE_SWC_CHARGEMNGR_H

#include "Rte_SWC_ChargeMngr_Type.h"

#define Rte_Read_R_PackMeasData_Tx_cellTempAverage Rte_Read_SWC_ChargeMngr_R_PackMeasData_Tx_cellTempAverage
#define Rte_Read_R_PackMeasData_Tx_packCurrent Rte_Read_SWC_ChargeMngr_R_PackMeasData_Tx_packCurrent
#define Rte_Read_R_PackMeasData_Tx_packVoltageSum Rte_Read_SWC_ChargeMngr_R_PackMeasData_Tx_packVoltageSum

extern CONSTP2CONST(Rte_CDS_SWC_ChargeMngr, RTE_CONST, RTE_CONST) Rte_Inst_SWC_ChargeMngr;

extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_ChargeMngr_R_PackMeasData_Tx_cellTempAverage(P2VAR(sint16, AUTOMATIC, RTE_APPL_DATA) cellTempAverage);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_ChargeMngr_R_PackMeasData_Tx_packCurrent(P2VAR(sint32, AUTOMATIC, RTE_APPL_DATA) packCurrent);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_ChargeMngr_R_PackMeasData_Tx_packVoltageSum(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) packVoltageSum);
FUNC(void, SWC_ChargeMngr_CODE) REoiSWC_ChargeMngr_P_ChgData_chargeSequenceCtrl(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) chgTargetVoltage, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) chgTargetCurrent, P2VAR(e_ChgInfo, AUTOMATIC, RTE_APPL_DATA) chargingStatus);
FUNC(void, SWC_ChargeMngr_CODE) REtSWC_ChargeMngr_ReadBattStatus_100ms();

#endif