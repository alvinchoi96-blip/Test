#include "Rte_Internals.h"
#include "Rte_SWC_HMI_Driver.h"
#include "Std_Types.h"

VAR(Rte_BufferDataStructureType, RTE_VAR) Rte_BDS;
CONST(Rte_CDS_SWC_HMI_Driver, RTE_CONST) Rte_Instance_SWC_HMI_Driver = {
	0 /* dummy entry */
};

CONSTP2CONST(Rte_CDS_SWC_HMI_Driver, RTE_CONST, RTE_CONST) Rte_Inst_SWC_HMI_Driver = &Rte_Instance_SWC_HMI_Driver;
CONST(Rte_BufferDataStructureType, RTE_CONST) Rte_InitialBDS = {0};

FUNC(Std_ReturnType, RTE_CODE) Rte_Start()
{
	Std_ReturnType Rte_Status = RTE_E_OK;        
	
	Rte_BDS = Rte_InitialBDS;            
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Stop()
{
	Std_ReturnType Rte_Status = RTE_E_OK;      
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_HMI_Driver_R_HMI_SigOutput_battRalayEnableStatus(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) battRalayEnableStatus)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*battRalayEnableStatus = Rte_BDS.Rte_ReceiverBuffer_SWC_HMI_Driver_R_HMI_SigOutput.battRalayEnableStatus;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_HMI_Driver_R_HMI_SigOutput_bmsFaultLevel(P2VAR(e_FaultLevel, AUTOMATIC, RTE_APPL_DATA) bmsFaultLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*bmsFaultLevel = Rte_BDS.Rte_ReceiverBuffer_SWC_HMI_Driver_R_HMI_SigOutput.bmsFaultLevel;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_HMI_Driver_R_HMI_SigOutput_buzzerOutputFlag(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) buzzerOutputFlag)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*buzzerOutputFlag = Rte_BDS.Rte_ReceiverBuffer_SWC_HMI_Driver_R_HMI_SigOutput.buzzerOutputFlag;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_HMI_Driver_R_HMI_SigOutput_chargingStatus(P2VAR(e_ChgInfo, AUTOMATIC, RTE_APPL_DATA) chargingStatus)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*chargingStatus = Rte_BDS.Rte_ReceiverBuffer_SWC_HMI_Driver_R_HMI_SigOutput.chargingStatus;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_HMI_Driver_R_HMI_SigOutput_socGauge(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) socGauge)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*socGauge = Rte_BDS.Rte_ReceiverBuffer_SWC_HMI_Driver_R_HMI_SigOutput.socGauge;
	
	return Rte_Status;
}
