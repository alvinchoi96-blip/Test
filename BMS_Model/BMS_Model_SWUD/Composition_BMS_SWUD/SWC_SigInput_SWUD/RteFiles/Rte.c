#include "Rte_Internals.h"
#include "Rte_SWC_SigInput.h"
#include "Std_Types.h"

CONST(Rte_CDS_SWC_SigInput, RTE_CONST) Rte_Instance_SWC_SigInput = {
	0 /* dummy entry */
};

CONSTP2CONST(Rte_CDS_SWC_SigInput, RTE_CONST, RTE_CONST) Rte_Inst_SWC_SigInput = &Rte_Instance_SWC_SigInput;

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
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_SigInput_P_SignalInput_chargeConnectedFlag(VAR(boolean, AUTOMATIC) chargeConnectedFlag)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_SigInput_P_SignalInput_ignSignal(VAR(e_IgnStat, AUTOMATIC) ignSignal)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_SigInput_P_VcuCanCmd_bmsActionCmd(VAR(e_VcuCanCmd, AUTOMATIC) bmsActionCmd)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
