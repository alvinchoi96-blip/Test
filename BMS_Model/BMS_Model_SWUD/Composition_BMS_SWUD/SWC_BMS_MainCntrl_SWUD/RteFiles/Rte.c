#include "Rte_Internals.h"
#include "Rte_SWC_BMS_MainCntrl.h"
#include "Std_Types.h"
#include "string.h"

VAR(Rte_BufferDataStructureType, RTE_VAR) Rte_BDS;
CONST(Rte_CDS_SWC_BMS_MainCntrl, RTE_CONST) Rte_Instance_SWC_BMS_MainCntrl = {
	0 /* dummy entry */
};

CONSTP2CONST(Rte_CDS_SWC_BMS_MainCntrl, RTE_CONST, RTE_CONST) Rte_Inst_SWC_BMS_MainCntrl = &Rte_Instance_SWC_BMS_MainCntrl;
CONST(Rte_BufferDataStructureType, RTE_CONST) Rte_InitialBDS = {0};

FUNC(Std_ReturnType, RTE_CODE) Rte_Start()
{
	Std_ReturnType Rte_Status = RTE_E_OK;        
	
	Rte_BDS = Rte_InitialBDS;            
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Stop()
{
	Std_ReturnType Rte_Status = RTE_E_OK;      
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_BMS_MainCntrl_R_CellBalanceReq_cellBalanceDisable()
{
	Std_ReturnType Rte_Status = RTE_E_OK;
	 return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_BMS_MainCntrl_R_CellBalanceReq_cellBalanceEnable(P2CONST(uint16, AUTOMATIC, RTE_APPL_CONST) cellVoltageIndividual, VAR(uint16, AUTOMATIC) targetIbpLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK;
	 return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_BMS_MainCntrl_R_ChgData_chargeSequenceCtrl(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) chgTargetVoltage, P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) chgTargetCurrent, P2VAR(e_ChgInfo, AUTOMATIC, RTE_APPL_DATA) chargingStatus)
{
	Std_ReturnType Rte_Status = RTE_E_OK;
	 return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_BMS_MainCntrl_R_RelayControlReq_relayDisableReq()
{
	Std_ReturnType Rte_Status = RTE_E_OK;
	 return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_BMS_MainCntrl_R_RelayControlReq_relayEnableReq(VAR(e_relayEnableSpeed, AUTOMATIC) speed)
{
	Std_ReturnType Rte_Status = RTE_E_OK;
	 return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_BMS_MainCntrl_R_SocCalc_calculateCapacity(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) calculatedCapacity)
{
	Std_ReturnType Rte_Status = RTE_E_OK;
	 return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_BMS_MainCntrl_R_SocCalc_calculateSoc(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calculatedSocValue)
{
	Std_ReturnType Rte_Status = RTE_E_OK;
	 return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_BMS_MainCntrl_R_SocCalc_calculateSoh(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) calculateSohValue)
{
	Std_ReturnType Rte_Status = RTE_E_OK;
	 return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_CellMeasData_cellSerialNum(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) cellSerialNum)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*cellSerialNum = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CellMeasData.cellSerialNum;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_CellMeasData_cellVoltageAverage(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) cellVoltageAverage)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*cellVoltageAverage = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CellMeasData.cellVoltageAverage;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_CellMeasData_cellVoltageIndividual(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) cellVoltageIndividual)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	memcpy(cellVoltageIndividual, &Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CellMeasData.cellVoltageIndividual, sizeof(CellVoltageData));
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_CellMeasData_cellVoltageMax(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) cellVoltageMax)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*cellVoltageMax = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CellMeasData.cellVoltageMax;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_CellMeasData_cellVoltageMin(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) cellVoltageMin)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*cellVoltageMin = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CellMeasData.cellVoltageMin;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_CellMeasData_ibpLevel(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) ibpLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*ibpLevel = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CellMeasData.ibpLevel;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_CellMeasData_packVoltageSum(P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) packVoltageSum)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*packVoltageSum = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CellMeasData.packVoltageSum;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_CurrMeasData_packCurrent(P2VAR(sint32, AUTOMATIC, RTE_APPL_DATA) packCurrent)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*packCurrent = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_CurrMeasData.packCurrent;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errChargeOverTemp(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errChargeOverTemp)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errChargeOverTemp = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errChargeOverTemp;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errChargeUnderTemp(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errChargeUnderTemp)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errChargeUnderTemp = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errChargeUnderTemp;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errDischargeOverTemp(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errDischargeOverTemp)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errDischargeOverTemp = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errDischargeOverTemp;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errDischargeUnderTemp(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errDischargeUnderTemp)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errDischargeUnderTemp = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errDischargeUnderTemp;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errIsolation(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errIsolation)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errIsolation = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errIsolation;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errOverCellVmax(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errOverCellVmax)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errOverCellVmax = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errOverCellVmax;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errOverCharge(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errOverCharge)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errOverCharge = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errOverCharge;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errOverChargeCurrent(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errOverChargeCurrent)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errOverChargeCurrent = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errOverChargeCurrent;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errOverDischarge(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errOverDischarge)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errOverDischarge = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errOverDischarge;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errOverDischargeCurrent(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errOverDischargeCurrent)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errOverDischargeCurrent = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errOverDischargeCurrent;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errOverIbp(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errOverIbp)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errOverIbp = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errOverIbp;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_errUnderCellVmin(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) errUnderCellVmin)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*errUnderCellVmin = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.errUnderCellVmin;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_warnChargeOverTemp(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) warnChargeOverTemp)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*warnChargeOverTemp = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.warnChargeOverTemp;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_warnChargeUnderTemp(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) warnChargeUnderTemp)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*warnChargeUnderTemp = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.warnChargeUnderTemp;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_warnDischargeOverTemp(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) warnDischargeOverTemp)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*warnDischargeOverTemp = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.warnDischargeOverTemp;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_warnDischargeUnderTemp(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) warnDischargeUnderTemp)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*warnDischargeUnderTemp = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.warnDischargeUnderTemp;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_warnOverCellVmax(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) warnOverCellVmax)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*warnOverCellVmax = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.warnOverCellVmax;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_warnOverCharge(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) warnOverCharge)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*warnOverCharge = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.warnOverCharge;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_warnOverChargeCurrent(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) warnOverChargeCurrent)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*warnOverChargeCurrent = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.warnOverChargeCurrent;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_warnOverDisCharge(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) warnOverDisCharge)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*warnOverDisCharge = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.warnOverDisCharge;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_warnOverDischargeCurrent(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) warnOverDischargeCurrent)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*warnOverDischargeCurrent = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.warnOverDischargeCurrent;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_warnOverIbp(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) warnOverIbp)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*warnOverIbp = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.warnOverIbp;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_FaultFlag_warnUnderCellVmin(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) warnUnderCellVmin)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*warnUnderCellVmin = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_FaultFlag.warnUnderCellVmin;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_SignalInput_chargeConnectedFlag(P2VAR(boolean, AUTOMATIC, RTE_APPL_DATA) chargeConnectedFlag)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*chargeConnectedFlag = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_SignalInput.chargeConnectedFlag;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_SignalInput_ignSignal(P2VAR(e_IgnStat, AUTOMATIC, RTE_APPL_DATA) ignSignal)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*ignSignal = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_SignalInput.ignSignal;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_TempMeasData_cellTempAverage(P2VAR(sint16, AUTOMATIC, RTE_APPL_DATA) cellTempAverage)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*cellTempAverage = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_TempMeasData.cellTempAverage;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_TempMeasData_cellTempMax(P2VAR(sint16, AUTOMATIC, RTE_APPL_DATA) cellTempMax)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*cellTempMax = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_TempMeasData.cellTempMax;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_TempMeasData_cellTempMin(P2VAR(sint16, AUTOMATIC, RTE_APPL_DATA) cellTempMin)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*cellTempMin = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_TempMeasData.cellTempMin;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SWC_BMS_MainCntrl_R_VcuCanCmd_bmsActionCmd(P2VAR(e_VcuCanCmd, AUTOMATIC, RTE_APPL_DATA) bmsActionCmd)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	*bmsActionCmd = Rte_BDS.Rte_ReceiverBuffer_SWC_BMS_MainCntrl_R_VcuCanCmd.bmsActionCmd;
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_cellBalancingFlag(VAR(boolean, AUTOMATIC) cellBalancingFlag)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_currentFaultFlags(P2CONST(f_Current, AUTOMATIC, RTE_APPL_CONST) currentFaultFlags)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_ibpFaultFlags(P2CONST(f_Ibp, AUTOMATIC, RTE_APPL_CONST) ibpFaultFlags)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_packIsolationFaultFlag(P2CONST(f_IsolResist, AUTOMATIC, RTE_APPL_CONST) packIsolationFaultFlag)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_tempFaultFlags(P2CONST(f_Temp, AUTOMATIC, RTE_APPL_CONST) tempFaultFlags)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_BattStatusFlags_Tx_voltageFaultFlags(P2CONST(f_Voltage, AUTOMATIC, RTE_APPL_CONST) voltageFaultFlags)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_ChgData_Tx_chargingStatus(VAR(e_ChgInfo, AUTOMATIC) chargingStatus)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_ChgData_Tx_chgTargetCurrent(VAR(uint16, AUTOMATIC) chgTargetCurrent)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_ChgData_Tx_chgTargetVoltage(VAR(uint32, AUTOMATIC) chgTargetVoltage)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_HMI_SigOutput_battRalayEnableStatus(VAR(boolean, AUTOMATIC) battRalayEnableStatus)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_HMI_SigOutput_bmsFaultLevel(VAR(e_FaultLevel, AUTOMATIC) bmsFaultLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_HMI_SigOutput_buzzerOutputFlag(VAR(boolean, AUTOMATIC) buzzerOutputFlag)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_HMI_SigOutput_chargingStatus(VAR(e_ChgInfo, AUTOMATIC) chargingStatus)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_HMI_SigOutput_socGauge(VAR(uint8, AUTOMATIC) socGauge)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_PackCalculatedData_Tx_capacityLevel(VAR(uint16, AUTOMATIC) capacityLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_PackCalculatedData_Tx_ibpLevel(VAR(uint16, AUTOMATIC) ibpLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_PackCalculatedData_Tx_socLevel(VAR(uint16, AUTOMATIC) socLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_PackCalculatedData_Tx_sohLevel(VAR(uint32, AUTOMATIC) sohLevel)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_bmsModeInfo(VAR(e_VcuCanCmd, AUTOMATIC) bmsModeInfo)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_cellTempAverage(VAR(sint16, AUTOMATIC) cellTempAverage)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_packCurrent(VAR(sint32, AUTOMATIC) packCurrent)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SWC_BMS_MainCntrl_P_PackMeasData_Tx_packVoltageSum(VAR(uint32, AUTOMATIC) packVoltageSum)
{
	Std_ReturnType Rte_Status = RTE_E_OK; 
	
	
	return Rte_Status;
}
