/**
 * @file Bms_TxMapper_ReportBattInfo.c
 * @brief Mapping logic for ReportBattInfoData_10ms (Inputs -> Tx Structs)
 */

#include "Bms_TxMapper_ReportBattInfo.h"

void BMS_TxMap_ReportBattInfo(
    e_VcuCanCmd currentMode,
    Bms_PackMeasData_TxType* outPackMeas,
    Bms_PackCalculatedData_TxType* outPackCalc,
    Bms_BattStatusFlags_TxType* outBattFlags
)
{
    /* ---- Guard ---- */
    if ((outPackMeas == 0) || (outPackCalc == 0) || (outBattFlags == 0))
    {
        return;
    }

    /* =========================================================
     * 1) PackMeasData 매핑
     * ========================================================= */
    outPackMeas->packVoltageSum  = g_Input_CellMeas.packVoltageSum;
    outPackMeas->packCurrent     = g_Input_CurrMeas.packCurrent;
    outPackMeas->cellTempAverage = g_Input_TempMeas.cellTempAverage;
    outPackMeas->bmsModeInfo     = currentMode; /* 외부에서 결정된 종합 모드 */

    /* =========================================================
     * 2) PackCalculatedData 매핑
     * ========================================================= */
    outPackCalc->ibpLevel      = g_Input_CellMeas.ibpLevel;

    /* 아직 연결 안 된 계산 결과는 0으로 유지 (추후 입력 연결 시 여기서 채움) */
    outPackCalc->socLevel      = 0U;
    outPackCalc->sohLevel      = 0U;
    outPackCalc->capacityLevel = 0U;

    /* =========================================================
     * 3) BattStatusFlags 매핑 (FaultFlag -> f_* Full)
     * ========================================================= */

    /* Balancing (추후 연결되면 여기서 채움) */
    outBattFlags->cellBalancingFlag = FALSE;

    /* Voltage */
    outBattFlags->voltage.warnOverCharge    = g_Input_FaultFlag.warnOverCharge;
    outBattFlags->voltage.warnOverDischarge = g_Input_FaultFlag.warnOverDisCharge; /* Typo 유지 */
    outBattFlags->voltage.warnOverCellVmax  = g_Input_FaultFlag.warnOverCellVmax;
    outBattFlags->voltage.warnUnderCellVmin = g_Input_FaultFlag.warnUnderCellVmin;

    outBattFlags->voltage.errOverCharge     = g_Input_FaultFlag.errOverCharge;
    outBattFlags->voltage.errOverDischarge  = g_Input_FaultFlag.errOverDischarge;
    outBattFlags->voltage.errOverCellVmax   = g_Input_FaultFlag.errOverCellVmax;
    outBattFlags->voltage.errUnderCellVmin  = g_Input_FaultFlag.errUnderCellVmin;

    /* Current */
    outBattFlags->current.warnOverChargeCurrent    = g_Input_FaultFlag.warnOverChargeCurrent;
    outBattFlags->current.warnOverDischargeCurrent = g_Input_FaultFlag.warnOverDischargeCurrent;

    outBattFlags->current.errOverChargeCurrent     = g_Input_FaultFlag.errOverChargeCurrent;
    outBattFlags->current.errOverDischargeCurrent  = g_Input_FaultFlag.errOverDischargeCurrent;

    /* Temp */
    outBattFlags->temp.warnChargeOverTemp      = g_Input_FaultFlag.warnChargeOverTemp;
    outBattFlags->temp.warnChargeUnderTemp     = g_Input_FaultFlag.warnChargeUnderTemp;
    outBattFlags->temp.warnDischargeOverTemp   = g_Input_FaultFlag.warnDischargeOverTemp;
    outBattFlags->temp.warnDischargeUnderTemp  = g_Input_FaultFlag.warnDischargeUnderTemp;

    outBattFlags->temp.errChargeOverTemp       = g_Input_FaultFlag.errChargeOverTemp;
    outBattFlags->temp.errChargeUnderTemp      = g_Input_FaultFlag.errChargeUnderTemp;
    outBattFlags->temp.errDischargeOverTemp    = g_Input_FaultFlag.errDischargeOverTemp;
    outBattFlags->temp.errDischargeUnderTemp   = g_Input_FaultFlag.errDischargeUnderTemp;

    /* IBP */
    outBattFlags->ibp.warnOverIbp = g_Input_FaultFlag.warnOverIbp;
    outBattFlags->ibp.errOverIbp  = g_Input_FaultFlag.errOverIbp;

    /* Isolation */
    outBattFlags->isol.errIsolation = g_Input_FaultFlag.errIsolation;
}
