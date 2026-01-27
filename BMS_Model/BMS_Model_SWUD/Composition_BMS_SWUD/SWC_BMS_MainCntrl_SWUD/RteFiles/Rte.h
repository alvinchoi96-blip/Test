#ifndef RTE_H
#define RTE_H

#include "Std_Types.h"

#define RTE_E_OK ((Std_ReturnType) 0)
#define RTE_E_INVALID ((Std_ReturnType) 1)
#define RTE_E_COMMS_ERROR ((Std_ReturnType) 128)
#define RTE_E_COM_STOPPED ((Std_ReturnType) 128)
#define RTE_E_TIMEOUT ((Std_ReturnType) 129)
#define RTE_E_LIMIT ((Std_ReturnType) 130)
#define RTE_E_NO_DATA ((Std_ReturnType) 131)
#define RTE_E_TRANSMIT_ACK ((Std_ReturnType) 132)
#define RTE_E_NEVER_RECEIVED ((Std_ReturnType) 133)
#define RTE_E_LOST_DATA ((Std_ReturnType) 64)
#define RTE_E_MAX_AGE_EXCEEDED ((Std_ReturnType) 64)
#define RTE_E_SHUTDOWN_NOTIFICATION ((Std_ReturnType) 156)
#define RTE_E_UNCONNECTED ((Std_ReturnType) 134)
#define	RTE_TRANSFORMER_UNSPECIFIED		0x00U
#define	RTE_TRANSFORMER_SERIALIZER		0x01U
#define	RTE_TRANSFORMER_SAFETY		0x02U
#define	RTE_TRANSFORMER_SECURITY		0x03U
#define	RTE_TRANSFORMER_CUSTOM		0xFFU
#define Rte_IsInfrastructureError(status) ((status & 128U) !=0)
#define Rte_HasOverlayedError(status) ((status & 64U) != 0)
#define Rte_ApplicationError(status) (status & 63U)

#endif