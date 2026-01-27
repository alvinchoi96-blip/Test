#ifndef RTE_INTERNALS_H
#define RTE_INTERNALS_H

#include "Rte_Type.h"

typedef struct _Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx_Type_
{
	VAR(uint16, AUTOMATIC) capacityLevel ;
	VAR(uint16, AUTOMATIC) ibpLevel ;
	VAR(uint16, AUTOMATIC) socLevel ;
	VAR(uint32, AUTOMATIC) sohLevel ;
}Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx_Type;
typedef struct _Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx_Type_
{
	VAR(boolean, AUTOMATIC) cellBalancingFlag ;
	VAR(f_Current, AUTOMATIC) currentFaultFlags ;
	VAR(f_Ibp, AUTOMATIC) ibpFaultFlags ;
	VAR(f_IsolResist, AUTOMATIC) packIsolationFaultFlag ;
	VAR(f_Temp, AUTOMATIC) tempFaultFlags ;
	VAR(f_Voltage, AUTOMATIC) voltageFaultFlags ;
}Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx_Type;
typedef struct _Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_ChgData_Tx_Type_
{
	VAR(e_ChgInfo, AUTOMATIC) chargingStatus ;
	VAR(uint16, AUTOMATIC) chgTargetCurrent ;
	VAR(uint32, AUTOMATIC) chgTargetVoltage ;
}Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_ChgData_Tx_Type;
typedef struct _Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackMeasData_Tx_Type_
{
	VAR(e_VcuCanCmd, AUTOMATIC) bmsModeInfo ;
	VAR(sint16, AUTOMATIC) cellTempAverage ;
	VAR(sint32, AUTOMATIC) packCurrent ;
	VAR(uint32, AUTOMATIC) packVoltageSum ;
}Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackMeasData_Tx_Type;
typedef struct _Rte_BufferDataStructureType_
{
	VAR(Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_BattStatusFlags_Tx ;
	VAR(Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_ChgData_Tx_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_ChgData_Tx ;
	VAR(Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackCalculatedData_Tx ;
	VAR(Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackMeasData_Tx_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_BMS_Status_Tx_R_PackMeasData_Tx ;
}Rte_BufferDataStructureType;

#endif