#include "Rte_Internals.h"
#include "Rte_SWC_BMS_Status_Tx.h"
#include "Std_Types.h"

VAR(Rte_BufferDataStructureType, RTE_VAR) Rte_BDS;
CONST(Rte_CDS_SWC_BMS_Status_Tx, RTE_CONST) Rte_Instance_SWC_BMS_Status_Tx = {
	0 /* dummy entry */
};

CONSTP2CONST(Rte_CDS_SWC_BMS_Status_Tx, RTE_CONST, RTE_CONST) Rte_Inst_SWC_BMS_Status_Tx = &Rte_Instance_SWC_BMS_Status_Tx;
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx_cellBalancingFlag(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) cellBalancingFlag)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*cellBalancingFlag = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx.cellBalancingFlag;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx_currentFaultFlags(P2VAR(f_Current, AUTOMATIC, RTE_APPL_DATA) currentFaultFlags)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*currentFaultFlags = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx.currentFaultFlags;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx_ibpFaultFlags(P2VAR(f_Ibp, AUTOMATIC, RTE_APPL_DATA) ibpFaultFlags)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*ibpFaultFlags = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx.ibpFaultFlags;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx_packIsolationFaultFlag(P2VAR(f_IsolResist, AUTOMATIC, RTE_APPL_DATA) packIsolationFaultFlag)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*packIsolationFaultFlag = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx.packIsolationFaultFlag;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx_tempFaultFlags(P2VAR(f_Temp, AUTOMATIC, RTE_APPL_DATA) tempFaultFlags)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*tempFaultFlags = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx.tempFaultFlags;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx_voltageFaultFlags(P2VAR(f_Voltage, AUTOMATIC, RTE_APPL_DATA) voltageFaultFlags)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*voltageFaultFlags = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx.voltageFaultFlags;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_ChgData_Tx_chargingStatus(P2VAR(e_ChgInfo, AUTOMATIC, RTE_APPL_DATA) chargingStatus)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*chargingStatus = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_ChgData_Tx.chargingStatus;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_ChgData_Tx_chgTargetCurrent(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) chgTargetCurrent)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*chgTargetCurrent = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_ChgData_Tx.chgTargetCurrent;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_ChgData_Tx_chgTargetVoltage(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) chgTargetVoltage)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*chgTargetVoltage = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_ChgData_Tx.chgTargetVoltage;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx_capacityLevel(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) capacityLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*capacityLevel = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx.capacityLevel;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx_ibpLevel(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) ibpLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*ibpLevel = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx.ibpLevel;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx_socLevel(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) socLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*socLevel = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx.socLevel;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx_sohLevel(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) sohLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*sohLevel = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx.sohLevel;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_PackMeasData_Tx_bmsModeInfo(P2VAR(e_VcuCanCmd, AUTOMATIC, RTE_APPL_DATA) bmsModeInfo)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*bmsModeInfo = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackMeasData_Tx.bmsModeInfo;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_PackMeasData_Tx_cellTempAverage(P2VAR(sint16, AUTOMATIC, RTE_APPL_DATA) cellTempAverage)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*cellTempAverage = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackMeasData_Tx.cellTempAverage;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_PackMeasData_Tx_packCurrent(P2VAR(sint32, AUTOMATIC, RTE_APPL_DATA) packCurrent)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*packCurrent = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackMeasData_Tx.packCurrent;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_Status_Tx_R_PackMeasData_Tx_packVoltageSum(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) packVoltageSum)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*packVoltageSum = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackMeasData_Tx.packVoltageSum;
	
	return Rte_Status;
}
