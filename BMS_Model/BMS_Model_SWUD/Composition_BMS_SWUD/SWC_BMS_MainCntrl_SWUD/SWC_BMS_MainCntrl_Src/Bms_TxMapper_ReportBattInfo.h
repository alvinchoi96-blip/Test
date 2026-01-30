#ifndef BMS_TXMAPPER_REPORTBATTINFO_H
#define BMS_TXMAPPER_REPORTBATTINFO_H

#include "BMS_MainCntrl_GlobalData.h" /* g_Input_* */
#include "Rte_Type.h"                /* f_*, e_VcuCanCmd */

/* Tx 타입들은 BMS_MainCntrl_GlobalData.h에 추가해둔 것으로 가정 */
void BMS_TxMap_ReportBattInfo(
    e_VcuCanCmd currentMode,
    Bms_PackMeasData_TxType* outPackMeas,
    Bms_PackCalculatedData_TxType* outPackCalc,
    Bms_BattStatusFlags_TxType* outBattFlags
);


/* P_PackMeasData_Function_Define*/
void Bms_Tx_PackMeasData_Write(
    const Bms_PackMeasData_TxType* txData
);

/* P_PackCalculatedData_Function_Define*/
void Bms_Tx_PackCalculatedData_Write(
    const Bms_PackCalculatedData_TxType* txData
);

/* P_BattStatusFlags_Function_Define*/
void Bms_Tx_BattStatusFlags_Write(
    const Bms_BattStatusFlags_TxType* txData
);


#endif /* BMS_TXMAPPER_REPORTBATTINFO_H */
