#include "Rte_Internals.h"
#include "Rte_SWC_PackMntr.h"
#include "Std_Types.h"

CONST(Rte_CDS_SWC_PackMntr, RTE_CONST) Rte_Instance_SWC_PackMntr = {
	0 /* dummy entry */
};

CONSTP2CONST(Rte_CDS_SWC_PackMntr, RTE_CONST, RTE_CONST) Rte_Inst_SWC_PackMntr = &Rte_Instance_SWC_PackMntr;

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
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_PackMntr_P_CurrMeasData_packCurrent(VAR(sint32, AUTOMATIC) packCurrent)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_PackMntr_P_PackInsulationData_insulationResistanceValue(VAR(uint32, AUTOMATIC) insulationResistanceValue)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
