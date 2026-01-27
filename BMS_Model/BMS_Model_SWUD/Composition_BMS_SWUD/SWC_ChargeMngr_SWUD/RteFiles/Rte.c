#include "Rte_Internals.h"
#include "Rte_SWC_ChargeMngr.h"
#include "Std_Types.h"

VAR(Rte_BufferDataStructureType, RTE_VAR) Rte_BDS;
CONST(Rte_CDS_SWC_ChargeMngr, RTE_CONST) Rte_Instance_SWC_ChargeMngr = {
	0 /* dummy entry */
};

CONSTP2CONST(Rte_CDS_SWC_ChargeMngr, RTE_CONST, RTE_CONST) Rte_Inst_SWC_ChargeMngr = &Rte_Instance_SWC_ChargeMngr;
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_ChargeMngr_R_PackMeasData_Tx_cellTempAverage(P2VAR(sint16, AUTOMATIC, RTE_APPL_DATA) cellTempAverage)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*cellTempAverage = Rte_BDS.Rte_ReceiverBuffer_SWC_ChargeMngr_R_PackMeasData_Tx.cellTempAverage;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_ChargeMngr_R_PackMeasData_Tx_packCurrent(P2VAR(sint32, AUTOMATIC, RTE_APPL_DATA) packCurrent)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*packCurrent = Rte_BDS.Rte_ReceiverBuffer_SWC_ChargeMngr_R_PackMeasData_Tx.packCurrent;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_ChargeMngr_R_PackMeasData_Tx_packVoltageSum(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) packVoltageSum)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*packVoltageSum = Rte_BDS.Rte_ReceiverBuffer_SWC_ChargeMngr_R_PackMeasData_Tx.packVoltageSum;
	
	return Rte_Status;
}
