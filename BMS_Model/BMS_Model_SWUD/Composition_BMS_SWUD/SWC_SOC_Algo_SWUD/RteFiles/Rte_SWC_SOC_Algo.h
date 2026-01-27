#ifndef RTE_SWC_SOC_ALGO_H
#define RTE_SWC_SOC_ALGO_H

#include "Rte_SWC_SOC_Algo_Type.h"

#define Rte_Read_R_PackMeasData_Tx_bmsModeInfo Rte_Read_SWC_SOC_Algo_R_PackMeasData_Tx_bmsModeInfo
#define Rte_Read_R_PackMeasData_Tx_cellTempAverage Rte_Read_SWC_SOC_Algo_R_PackMeasData_Tx_cellTempAverage
#define Rte_Read_R_PackMeasData_Tx_packCurrent Rte_Read_SWC_SOC_Algo_R_PackMeasData_Tx_packCurrent
#define Rte_Read_R_PackMeasData_Tx_packVoltageSum Rte_Read_SWC_SOC_Algo_R_PackMeasData_Tx_packVoltageSum

extern CONSTP2CONST(Rte_CDS_SWC_SOC_Algo, RTE_CONST, RTE_CONST) Rte_Inst_SWC_SOC_Algo;

extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_SOC_Algo_R_PackMeasData_Tx_bmsModeInfo(P2VAR(e_VcuCanCmd, AUTOMATIC, RTE_APPL_DATA) bmsModeInfo);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_SOC_Algo_R_PackMeasData_Tx_cellTempAverage(P2VAR(sint16, AUTOMATIC, RTE_APPL_DATA) cellTempAverage);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_SOC_Algo_R_PackMeasData_Tx_packCurrent(P2VAR(sint32, AUTOMATIC, RTE_APPL_DATA) packCurrent);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_SOC_Algo_R_PackMeasData_Tx_packVoltageSum(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) packVoltageSum);
FUNC(void, SWC_SOC_Algo_CODE) REoiSWC_SOC_Algo_P_SocCalc_calculateSoc(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calculatedSocValue);
FUNC(void, SWC_SOC_Algo_CODE) REoiSWC_SOC_Algo_P_SocCalc_calculateSoh(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) calculateSohValue);
FUNC(void, SWC_SOC_Algo_CODE) REoiSWC_SOC_Algo_P_SocCalc_calculateCapacity(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) calculatedCapacity);
FUNC(void, SWC_SOC_Algo_CODE) REtSWC_SOC_Algo_ReadBattStatus_100ms();

#endif