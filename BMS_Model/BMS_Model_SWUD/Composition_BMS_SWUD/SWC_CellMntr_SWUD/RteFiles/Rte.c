#include "Rte_Internals.h"
#include "Rte_SWC_CellMntr.h"
#include "Std_Types.h"

CONST(Rte_CDS_SWC_CellMntr, RTE_CONST) Rte_Instance_SWC_CellMntr = {
	0 /* dummy entry */
};

CONSTP2CONST(Rte_CDS_SWC_CellMntr, RTE_CONST, RTE_CONST) Rte_Inst_SWC_CellMntr = &Rte_Instance_SWC_CellMntr;

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
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_CellMntr_P_CellMeasData_cellSerialNum(VAR(uint8, AUTOMATIC) cellSerialNum)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_CellMntr_P_CellMeasData_cellVoltageAverage(VAR(uint16, AUTOMATIC) cellVoltageAverage)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_CellMntr_P_CellMeasData_cellVoltageIndividual(P2CONST(uint16, AUTOMATIC, RTE_APPL_CONST) cellVoltageIndividual)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_CellMntr_P_CellMeasData_cellVoltageMax(VAR(uint16, AUTOMATIC) cellVoltageMax)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_CellMntr_P_CellMeasData_cellVoltageMin(VAR(uint16, AUTOMATIC) cellVoltageMin)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_CellMntr_P_CellMeasData_ibpLevel(VAR(uint16, AUTOMATIC) ibpLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_CellMntr_P_CellMeasData_packVoltageSum(VAR(uint32, AUTOMATIC) packVoltageSum)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
