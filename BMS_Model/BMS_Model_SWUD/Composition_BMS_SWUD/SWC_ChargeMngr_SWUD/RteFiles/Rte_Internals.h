#ifndef RTE_INTERNALS_H
#define RTE_INTERNALS_H

#include "Rte_Type.h"

typedef struct _Rte_ReceiverBuffer_SWC_ChargeMngr_R_PackMeasData_Tx_Type_
{
	VAR(sint16, AUTOMATIC) cellTempAverage ;
	VAR(sint32, AUTOMATIC) packCurrent ;
	VAR(uint32, AUTOMATIC) packVoltageSum ;
}Rte_ReceiverBuffer_SWC_ChargeMngr_R_PackMeasData_Tx_Type;
typedef struct _Rte_BufferDataStructureType_
{
	VAR(Rte_ReceiverBuffer_SWC_ChargeMngr_R_PackMeasData_Tx_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_ChargeMngr_R_PackMeasData_Tx ;
}Rte_BufferDataStructureType;

#endif