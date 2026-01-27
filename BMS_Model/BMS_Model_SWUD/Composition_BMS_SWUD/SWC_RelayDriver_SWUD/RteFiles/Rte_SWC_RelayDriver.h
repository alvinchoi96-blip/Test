#ifndef RTE_SWC_RELAYDRIVER_H
#define RTE_SWC_RELAYDRIVER_H

#include "Rte_SWC_RelayDriver_Type.h"

extern CONSTP2CONST(Rte_CDS_SWC_RelayDriver, RTE_CONST, RTE_CONST) Rte_Inst_SWC_RelayDriver;

FUNC(void, SWC_RelayDriver_CODE) REoiSWC_RelayDriver_P_RelayControlReq_relayEnableReq(VAR(e_relayEnableSpeed, AUTOMATIC) speed);
FUNC(void, SWC_RelayDriver_CODE) REoiSWC_RelayDriver_P_RelayControlReq_relayDisableReq();

#endif