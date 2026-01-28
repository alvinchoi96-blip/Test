#ifndef P_PACKMEASDATA_TX_TO_SWC_BMS_STATUS_H
#define P_PACKMEASDATA_TX_TO_SWC_BMS_STATUS_H

#include "Rte_SWC_BMS_MainCntrl.h"

void P_PackMeasData_TX_To_SWC_BMS_Status_Write(uint32 packVoltageSum, sint32 packCurrent, e_VcuCanCmd bmsModeInfo, sint16 cellTempAverage);

#endif /* P_PACKMEASDATA_TX_TO_SWC_BMS_STATUS_H */
