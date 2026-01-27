#ifndef RTE_TYPE_H
#define RTE_TYPE_H

#include "Rte.h"

typedef uint8 e_VcuCanCmd;
typedef uint8 e_ChgInfo;
typedef uint8 Rte_TransformerClass;
typedef uint8 Rte_TransformerErrorCode;
typedef struct _f_Voltage_
{
	boolean warnOverCharge ;
	boolean warnOverDischarge ;
	boolean warnOverCellVmax ;
	boolean warnUnderCellVmin ;
	boolean errOverCharge ;
	boolean errOverDischarge ;
	boolean errOverCellVmax ;
	boolean errUnderCellVmin ;
}f_Voltage;
typedef struct _Rte_CDS_SWC_BMS_Status_Tx_
{
	VAR(uint8, AUTOMATIC) _dummy ;
}Rte_CDS_SWC_BMS_Status_Tx;
typedef struct _f_Temp_
{
	boolean warnChargeOverTemp ;
	boolean warnChargeUnderTemp ;
	boolean warnDischargeOverTemp ;
	boolean warnDischargeUnderTemp ;
	boolean errChargeOverTemp ;
	boolean errChargeUnderTemp ;
	boolean errDischargeOverTemp ;
	boolean errDischargeUnderTemp ;
}f_Temp;
typedef struct _f_Current_
{
	boolean warnOverChargeCurrent ;
	boolean warnOverDischargeCurrent ;
	boolean errOverChargeCurrent ;
	boolean errOverDischargeCurrent ;
}f_Current;
typedef struct _f_Ibp_
{
	boolean warnOverIbp ;
	boolean errOverIbp ;
}f_Ibp;
typedef struct _f_IsolResist_
{
	boolean errIsolation ;
}f_IsolResist;
typedef struct STag_Rte_TransformerError
{
	Rte_TransformerErrorCode errorCode ;
	Rte_TransformerClass transformerClass ;
}Rte_TransformerError;

#endif