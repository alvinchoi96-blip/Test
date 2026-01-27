#ifndef RTE_SWC_BALANCINGMNGR_H
#define RTE_SWC_BALANCINGMNGR_H

#include "Rte_SWC_BalancingMngr_Type.h"

extern CONSTP2CONST(Rte_CDS_SWC_BalancingMngr, RTE_CONST, RTE_CONST) Rte_Inst_SWC_BalancingMngr;

FUNC(void, SWC_BalancingMngr_CODE) REoiSWC_BalancingMngr_P_CellBalanceReq_cellBalanceEnable(P2CONST(uint16, AUTOMATIC, RTE_APPL_CONST) cellVoltageIndividual, VAR(uint16, AUTOMATIC) targetIbpLevel);
FUNC(void, SWC_BalancingMngr_CODE) REoiSWC_BalancingMngr_P_CellBalanceReq_cellBalanceDisable();

#endif