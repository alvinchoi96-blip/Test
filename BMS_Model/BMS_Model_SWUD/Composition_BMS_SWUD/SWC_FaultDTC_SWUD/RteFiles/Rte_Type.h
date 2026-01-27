#ifndef RTE_TYPE_H
#define RTE_TYPE_H

#include "Rte.h"

typedef uint16 CellVoltageData[144];
typedef uint8 Rte_TransformerClass;
typedef uint8 Rte_TransformerErrorCode;
typedef struct _Rte_CDS_SWC_FaultDTC_
{
	VAR(uint8, AUTOMATIC) _dummy ;
}Rte_CDS_SWC_FaultDTC;
typedef struct STag_Rte_TransformerError
{
	Rte_TransformerErrorCode errorCode ;
	Rte_TransformerClass transformerClass ;
}Rte_TransformerError;

#endif