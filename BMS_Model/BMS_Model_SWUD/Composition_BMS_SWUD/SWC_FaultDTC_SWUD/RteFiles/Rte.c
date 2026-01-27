#include "Rte_Internals.h"
#include "Rte_SWC_FaultDTC.h"
#include "Std_Types.h"

CONST(Rte_CDS_SWC_FaultDTC, RTE_CONST) Rte_Instance_SWC_FaultDTC = {
	0 /* dummy entry */
};

CONSTP2CONST(Rte_CDS_SWC_FaultDTC, RTE_CONST, RTE_CONST) Rte_Inst_SWC_FaultDTC = &Rte_Instance_SWC_FaultDTC;

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
