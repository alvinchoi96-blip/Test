#include "P_PackCalculatedData_Tx_To_SWC_BMS_Status.h"

void P_PackCalculatedData_Tx_To_SWC_BMS_Status_Write(uint16 ibpLevel)
{
    Rte_Write_SWC_BMS_MainCntrl_P_PackCalculatedData_Tx_ibpLevel(ibpLevel);
}