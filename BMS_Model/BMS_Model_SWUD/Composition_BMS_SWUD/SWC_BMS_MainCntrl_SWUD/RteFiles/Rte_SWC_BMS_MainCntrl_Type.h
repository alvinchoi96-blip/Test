#ifndef RTE_SWC_BMS_MAINCNTRL_TYPE_H
#define RTE_SWC_BMS_MAINCNTRL_TYPE_H

#include "Rte_Type.h"

#define	IGN_LOCK	0U	/* ENUM_IgnStat */
#define	IGN_ACC	1U	/* ENUM_IgnStat */
#define	IGN_ON	2U	/* ENUM_IgnStat */
#define	IGN_START	3U	/* ENUM_IgnStat */
#define	BmsMd_StandAlone	0U	/* ENUM_VcuCmd_BmsMode */
#define	BmsMd_Standby	1U	/* ENUM_VcuCmd_BmsMode */
#define	BmsMd_Driving	2U	/* ENUM_VcuCmd_BmsMode */
#define	BmsMd_Charging	3U	/* ENUM_VcuCmd_BmsMode */
#define	BmsMd_ShutDown	4U	/* ENUM_VcuCmd_BmsMode */
#define	BmsMd_Emergency	5U	/* ENUM_VcuCmd_BmsMode */
#define	ChgSt_NotCharging	0U	/* ENUM_ChgInfo */
#define	ChgSt_ChargerConnected	1U	/* ENUM_ChgInfo */
#define	ChgSt_Charging	2U	/* ENUM_ChgInfo */
#define	ChgSt_FullCharged	5U	/* ENUM_ChgInfo */
#define	ChgSt_ChargeMalfunction	10U	/* ENUM_ChgInfo */
#define	FltLv_Normal	0U	/* ENUM_FaultLevel */
#define	FltLv_Warning	1U	/* ENUM_FaultLevel */
#define	FltLv_Error	2U	/* ENUM_FaultLevel */
#define	Immediate	0U	/* ENUM_relayEnableSpeed */
#define	Soft	1U	/* ENUM_relayEnableSpeed */

#endif