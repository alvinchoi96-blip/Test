#ifndef RTE_SWC_CHARGEMNGR_TYPE_H
#define RTE_SWC_CHARGEMNGR_TYPE_H

#include "Rte_Type.h"

#define	NotCharging	0U	/* ENUM_ChgInfo */
#define	ChargerConnected	1U	/* ENUM_ChgInfo */
#define	Charging	3U	/* ENUM_VcuCmd_BmsMode */
#define	FullCharged	5U	/* ENUM_ChgInfo */
#define	ChargeMalfunction	10U	/* ENUM_ChgInfo */
#define	StandAlone	0U	/* ENUM_VcuCmd_BmsMode */
#define	Standby	1U	/* ENUM_VcuCmd_BmsMode */
#define	Driving	2U	/* ENUM_VcuCmd_BmsMode */
#define	Shut_Down	4U	/* ENUM_VcuCmd_BmsMode */
#define	Emergency	5U	/* ENUM_VcuCmd_BmsMode */

#endif