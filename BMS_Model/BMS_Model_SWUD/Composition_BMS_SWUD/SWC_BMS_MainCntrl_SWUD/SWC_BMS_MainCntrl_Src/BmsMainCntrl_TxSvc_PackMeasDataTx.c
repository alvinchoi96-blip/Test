#include "BmsMainCntrl_TxSvc.h"


static Std_ReturnType s_lastTxResult = E_OK;


static uint32 clamp_u32(uint32 v, uint32 minV, uint32 maxV)
{
    if (v < minV) { return minV; }
    if (v > maxV) { return maxV; }
    return v;
}

static sint32 clamp_s32(sint32 v, sint32 minV, sint32 maxV)
{
    if (v < minV) { return minV; }
    if (v > maxV) { return maxV; }
    return v;
}

static sint16 clamp_s16(sint16 v, sint16 minV, sint16 maxV)
{
    if (v < minV) { return minV; }
    if (v > maxV) { return maxV; }
    return v;
}

Std_ReturnType BmsMainCntrl_TxSvc_GetLastPackMeasTxResult(void)
{
    return s_lastTxResult;
}


Std_ReturnType BmsMainCntrl_TxSvc_Send_PackMeasData_Tx(
    uint32      packVoltageSum,
    sint32      packCurrent,
    e_VcuCanCmd bmsModeInfo,
    sint16      cellTempAverage
)
{
    static uint8 s_tick10ms = 0U;
    boolean tx10ms = FALSE;

    /* 이 함수가 1ms마다 호출된다는 가정일 때만 의미 있음 */
    s_tick10ms++;
    if (s_tick10ms >= 10U)
    {
        s_tick10ms = 0U;
        tx10ms = TRUE;
    }

    if (tx10ms == TRUE)
    {
        Rte_Write_P_PackMeasData_Tx_packVoltageSum();
        Rte_Write_P_PackMeasData_Tx_packCurrent();
        Rte_Write_P_PackMeasData_Tx_bmsModeInfo();
        Rte_Write_P_PackMeasData_Tx_cellTempAverage();
        
    }


}
