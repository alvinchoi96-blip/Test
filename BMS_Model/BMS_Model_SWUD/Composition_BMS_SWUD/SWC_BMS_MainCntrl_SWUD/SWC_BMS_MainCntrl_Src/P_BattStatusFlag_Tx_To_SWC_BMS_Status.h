#ifndef P_BATTSATUSFLAG_TX_TO_SWC_BMS_STATUS_H
#define P_BATTSATUSFLAG_TX_TO_SWC_BMS_STATUS_H

#include "Rte_SWC_BMS_MainCntrl.h"

void P_BattStatusFlag_Tx_To_SWC_BMS_Status_Write(f_Voltage voltageFaultFlags, f_Temp tempFaultFlags,f_Current currentFaultFlags, f_Ibp ibpFaultFlags, f_IsolResist packIsolationFaultFlag, boolean cellBalancingFlag);

#endif