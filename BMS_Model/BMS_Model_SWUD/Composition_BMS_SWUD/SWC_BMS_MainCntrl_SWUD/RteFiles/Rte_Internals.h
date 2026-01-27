#ifndef RTE_INTERNALS_H
#define RTE_INTERNALS_H

#include "Rte_Type.h"

typedef struct _Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CellMeasData_Type_
{
	VAR(uint8, AUTOMATIC) cellSerialNum ;
	VAR(uint16, AUTOMATIC) cellVoltageAverage ;
	VAR(CellVoltageData, AUTOMATIC) cellVoltageIndividual ;
	VAR(uint16, AUTOMATIC) cellVoltageMax ;
	VAR(uint16, AUTOMATIC) cellVoltageMin ;
	VAR(uint16, AUTOMATIC) ibpLevel ;
	VAR(uint32, AUTOMATIC) packVoltageSum ;
}Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CellMeasData_Type;
typedef struct _Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CurrMeasData_Type_
{
	VAR(sint32, AUTOMATIC) packCurrent ;
}Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CurrMeasData_Type;
typedef struct _Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag_Type_
{
	VAR(boolean, AUTOMATIC) errChargeOverTemp ;
	VAR(boolean, AUTOMATIC) errChargeUnderTemp ;
	VAR(boolean, AUTOMATIC) errDischargeOverTemp ;
	VAR(boolean, AUTOMATIC) errDischargeUnderTemp ;
	VAR(boolean, AUTOMATIC) errIsolation ;
	VAR(boolean, AUTOMATIC) errOverCellVmax ;
	VAR(boolean, AUTOMATIC) errOverCharge ;
	VAR(boolean, AUTOMATIC) errOverChargeCurrent ;
	VAR(boolean, AUTOMATIC) errOverDischarge ;
	VAR(boolean, AUTOMATIC) errOverDischargeCurrent ;
	VAR(boolean, AUTOMATIC) errOverIbp ;
	VAR(boolean, AUTOMATIC) errUnderCellVmin ;
	VAR(boolean, AUTOMATIC) warnChargeOverTemp ;
	VAR(boolean, AUTOMATIC) warnChargeUnderTemp ;
	VAR(boolean, AUTOMATIC) warnDischargeOverTemp ;
	VAR(boolean, AUTOMATIC) warnDischargeUnderTemp ;
	VAR(boolean, AUTOMATIC) warnOverCellVmax ;
	VAR(boolean, AUTOMATIC) warnOverCharge ;
	VAR(boolean, AUTOMATIC) warnOverChargeCurrent ;
	VAR(boolean, AUTOMATIC) warnOverDisCharge ;
	VAR(boolean, AUTOMATIC) warnOverDischargeCurrent ;
	VAR(boolean, AUTOMATIC) warnOverIbp ;
	VAR(boolean, AUTOMATIC) warnUnderCellVmin ;
}Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag_Type;
typedef struct _Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_TempMeasData_Type_
{
	VAR(sint16, AUTOMATIC) cellTempAverage ;
	VAR(sint16, AUTOMATIC) cellTempMax ;
	VAR(sint16, AUTOMATIC) cellTempMin ;
}Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_TempMeasData_Type;
typedef struct _Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_VcuCanCmd_Type_
{
	VAR(e_VcuCanCmd, AUTOMATIC) bmsActionCmd ;
}Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_VcuCanCmd_Type;
typedef struct _Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_SignalInput_Type_
{
	VAR(boolean, AUTOMATIC) chargeConnectedFlag ;
	VAR(e_IgnStat, AUTOMATIC) ignSignal ;
}Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_SignalInput_Type;
typedef struct _Rte_BufferDataStructureType_
{
	VAR(Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CellMeasData_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CellMeasData ;
	VAR(Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CurrMeasData_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CurrMeasData ;
	VAR(Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag ;
	VAR(Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_SignalInput_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_SignalInput ;
	VAR(Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_TempMeasData_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_TempMeasData ;
	VAR(Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_VcuCanCmd_Type, TYPEDEF) Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_VcuCanCmd ;
}Rte_BufferDataStructureType;

#endif