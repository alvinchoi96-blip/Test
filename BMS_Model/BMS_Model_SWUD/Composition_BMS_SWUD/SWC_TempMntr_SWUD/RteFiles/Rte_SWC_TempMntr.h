#ifndef RTE_SWC_TEMPMNTR_H
#define RTE_SWC_TEMPMNTR_H

#include "Rte_SWC_TempMntr_Type.h"

#define Rte_Write_P_TempMeasData_cellTempAverage Rte_Write_SWC_TempMntr_P_TempMeasData_cellTempAverage
#define Rte_Write_P_TempMeasData_cellTempMax Rte_Write_SWC_TempMntr_P_TempMeasData_cellTempMax
#define Rte_Write_P_TempMeasData_cellTempMin Rte_Write_SWC_TempMntr_P_TempMeasData_cellTempMin

extern CONSTP2CONST(Rte_CDS_SWC_TempMntr, RTE_CONST, RTE_CONST) Rte_Inst_SWC_TempMntr;

extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_TempMntr_P_TempMeasData_cellTempAverage(VAR(sint16, AUTOMATIC) cellTempAverage);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_TempMntr_P_TempMeasData_cellTempMax(VAR(sint16, AUTOMATIC) cellTempMax);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_TempMntr_P_TempMeasData_cellTempMin(VAR(sint16, AUTOMATIC) cellTempMin);
FUNC(void, SWC_TempMntr_CODE) REtSWC_TempMntr_SendTempMeasData_10ms();

#endif