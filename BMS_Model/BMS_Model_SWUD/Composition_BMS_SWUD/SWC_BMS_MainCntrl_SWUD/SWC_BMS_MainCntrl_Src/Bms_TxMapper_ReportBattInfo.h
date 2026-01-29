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


#endif /* BMS_TXMAPPER_REPORTBATTINFO_H */
