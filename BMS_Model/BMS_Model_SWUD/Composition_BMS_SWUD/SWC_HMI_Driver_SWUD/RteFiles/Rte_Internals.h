#ifndef RTE_INTERNALS_H
#define RTE_INTERNALS_H

#include "Rte_Type.h"

typedef struct _Rte_ReceiverBuffer_SWC_HMI_Driver_R_HMI_SigOutput_Type_
{
	VAR(boolean, AUTOMATIC) battRalayEnableStatus ;
	VAR(e_FaultLevel, AUTOMATIC) bmsFaultLevel ;
	VAR(boolean, AUTOMATIC) buzzerOutputFlag ;
	VAR(e_ChgInfo, AUTOMATIC) chargingStatus ;
	VAR(uint8, AUTOMATIC) socGauge ;
}Rte_ReceiverBuffer_SWC_HMI_Driver_R_HMI_SigOutput_Type;
typedef struct _Rte_BufferDataStructureType_
{
	VAR(Rte_ReceiverBuffer_SWC_HMI_Driver_R_HMI_SigOutput_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_HMI_Driver_R_HMI_SigOutput ;
}Rte_BufferDataStructureType;

#endif