#include "Soc_Cfg.h"

/* SOC [%] :  0    10   20   30   40   50   60   70   80   90   100 */
const uint16 BmsSoc_OcvSocBp_X10[BMS_SOC_OCV_POINTS] =
{
      0, 100, 200, 300, 400,
    500, 600, 700, 800, 900, 1000
};

/* Typical Li-ion OCV curve (mV) */
const uint16 BmsSoc_OcvTable_mV[BMS_SOC_OCV_POINTS] =
{
    3000, 3400, 3600, 3700, 3750,
    3800, 3850, 3900, 4000, 4100, 4200
};
