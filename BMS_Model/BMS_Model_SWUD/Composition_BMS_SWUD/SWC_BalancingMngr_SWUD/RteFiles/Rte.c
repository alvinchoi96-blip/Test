#include "Rte_Internals.h"
#include "Rte_SWC_BalancingMngr.h"
#include "Std_Types.h"

CONST(Rte_CDS_SWC_BalancingMngr, RTE_CONST) Rte_Instance_SWC_BalancingMngr = {
	0 /* dummy entry */
};

CONSTP2CONST(Rte_CDS_SWC_BalancingMngr, RTE_CONST, RTE_CONST) Rte_Inst_SWC_BalancingMngr = &Rte_Instance_SWC_BalancingMngr;

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
