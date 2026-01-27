#include "Rte_Internals.h"
#include "Rte_SWC_TempMntr.h"
#include "Std_Types.h"

CONST(Rte_CDS_SWC_TempMntr, RTE_CONST) Rte_Instance_SWC_TempMntr = {
	0 /* dummy entry */
};

CONSTP2CONST(Rte_CDS_SWC_TempMntr, RTE_CONST, RTE_CONST) Rte_Inst_SWC_TempMntr = &Rte_Instance_SWC_TempMntr;

FUNC(Std_ReturnType, RTE_CODE) Rte_Start()
{
	Std_ReturnType Rte_Status = RTE_E_OK;
	 return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Stop()
{
	Std_ReturnType Rte_Status = RTE_E_OK;      
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_TempMntr_P_TempMeasData_cellTempAverage(VAR(sint16, AUTOMATIC) cellTempAverage)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_TempMntr_P_TempMeasData_cellTempMax(VAR(sint16, AUTOMATIC) cellTempMax)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_TempMntr_P_TempMeasData_cellTempMin(VAR(sint16, AUTOMATIC) cellTempMin)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
