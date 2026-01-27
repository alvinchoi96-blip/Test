#ifndef RTE_SWC_SIGINPUT_H
#define RTE_SWC_SIGINPUT_H

#include "Rte_SWC_SigInput_Type.h"

#define Rte_Write_P_SignalInput_chargeConnectedFlag Rte_Write_SWC_SigInput_P_SignalInput_chargeConnectedFlag
#define Rte_Write_P_SignalInput_ignSignal Rte_Write_SWC_SigInput_P_SignalInput_ignSignal
#define Rte_Write_P_VcuCanCmd_bmsActionCmd Rte_Write_SWC_SigInput_P_VcuCanCmd_bmsActionCmd

extern CONSTP2CONST(Rte_CDS_SWC_SigInput, RTE_CONST, RTE_CONST) Rte_Inst_SWC_SigInput;

extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_SigInput_P_SignalInput_chargeConnectedFlag(VAR(boolean, AUTOMATIC) chargeConnectedFlag);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_SigInput_P_SignalInput_ignSignal(VAR(e_IgnStat, AUTOMATIC) ignSignal);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_SigInput_P_VcuCanCmd_bmsActionCmd(VAR(e_VcuCanCmd, AUTOMATIC) bmsActionCmd);
FUNC(void, SWC_SigInput_CODE) REtSWC_SigInput_SendSignalInput_10ms();
FUNC(void, SWC_SigInput_CODE) REtSWC_SigInput_SendVcuCanCmd_10ms();

#endif