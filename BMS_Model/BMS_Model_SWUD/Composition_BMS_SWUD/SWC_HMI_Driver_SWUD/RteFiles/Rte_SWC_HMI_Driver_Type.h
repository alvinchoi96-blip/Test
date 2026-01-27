#ifndef RTE_SWC_HMI_DRIVER_TYPE_H
#define RTE_SWC_HMI_DRIVER_TYPE_H

#include "Rte_Type.h"

#define	Normal	0U	/* ENUM_FaultLevel */
#define	Warning	1U	/* ENUM_FaultLevel */
#define	Error	2U	/* ENUM_FaultLevel */
#define	NotCharging	0U	/* ENUM_ChgInfo */
#define	ChargerConnected	1U	/* ENUM_ChgInfo */
#define	Charging	2U	/* ENUM_ChgInfo */
#define	FullCharged	5U	/* ENUM_ChgInfo */
#define	ChargeMalfunction	10U	/* ENUM_ChgInfo */

#endif