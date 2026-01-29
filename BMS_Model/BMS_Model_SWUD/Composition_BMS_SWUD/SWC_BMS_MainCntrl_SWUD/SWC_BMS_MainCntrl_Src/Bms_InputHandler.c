/**
 * @file Bms_InputHandler.c
 * @brief RTE Read & Validation Implementation
 */

#include "BMS_MainCntrl_GlobalData.h"      /* 전역 변수 접근 */
#include "Bms_StatusDetermine.h"
#include "Rte_SWC_BMS_MainCntrl.h"

/* =========================================================================
 * Function Prototypes
 * ========================================================================= */
boolean BMS_Input_ValidateSignals(void);


/* =========================================================================
 * Function Implementation
 * ========================================================================= */
void BMS_Input_ProcessAll(void)
{
    /* ======================================================================
     * 1. Raw Data Read (All Inputs without omission)
     * ====================================================================== */

    /* --- 1. Signal Inputs --- */
    if (Rte_Read_R_SignalInput_ignSignal(&g_Input_Signal.ignSignal) != RTE_E_OK) {
        g_Input_Signal.ignSignal = LOCK; /* Read Fail 시 Safe Value */
    }
    if (Rte_Read_R_SignalInput_chargeConnectedFlag(&g_Input_Signal.chargeConnectedFlag) != RTE_E_OK) {
        g_Input_Signal.chargeConnectedFlag = FALSE;
    }

    /* --- 2. VCU Command --- */
    if (Rte_Read_R_VcuCanCmd_bmsActionCmd(&g_Input_VcuCmd.bmsActionCmd) != RTE_E_OK) {
        g_Input_VcuCmd.bmsActionCmd = StandAlone;
    }

    /* --- 3. Cell Measurements --- */
    Rte_Read_R_CellMeasData_packVoltageSum(&g_Input_CellMeas.packVoltageSum);
    Rte_Read_R_CellMeasData_cellVoltageAverage(&g_Input_CellMeas.cellVoltageAverage);
    Rte_Read_R_CellMeasData_cellVoltageMax(&g_Input_CellMeas.cellVoltageMax);
    Rte_Read_R_CellMeasData_cellVoltageMin(&g_Input_CellMeas.cellVoltageMin);
    Rte_Read_R_CellMeasData_ibpLevel(&g_Input_CellMeas.ibpLevel);
    Rte_Read_R_CellMeasData_cellSerialNum(&g_Input_CellMeas.cellSerialNum);
    /* Array 타입은 & 없이 전달 */
    Rte_Read_R_CellMeasData_cellVoltageIndividual(g_Input_CellMeas.cellVoltageIndividual);

    /* --- 4. Current Measurements --- */
    Rte_Read_R_CurrMeasData_packCurrent(&g_Input_CurrMeas.packCurrent);

    /* --- 5. Temperature Measurements --- */
    Rte_Read_R_TempMeasData_cellTempAverage(&g_Input_TempMeas.cellTempAverage);
    Rte_Read_R_TempMeasData_cellTempMax(&g_Input_TempMeas.cellTempMax);
    Rte_Read_R_TempMeasData_cellTempMin(&g_Input_TempMeas.cellTempMin);

    /* --- 6. Fault Flags (Errors) --- */
    /* Voltage & System */
    Rte_Read_R_FaultFlag_errOverCharge(&g_Input_FaultFlag.errOverCharge);
    Rte_Read_R_FaultFlag_errOverDischarge(&g_Input_FaultFlag.errOverDischarge);
    Rte_Read_R_FaultFlag_errOverCellVmax(&g_Input_FaultFlag.errOverCellVmax);
    Rte_Read_R_FaultFlag_errUnderCellVmin(&g_Input_FaultFlag.errUnderCellVmin);
    Rte_Read_R_FaultFlag_errOverIbp(&g_Input_FaultFlag.errOverIbp);
    Rte_Read_R_FaultFlag_errIsolation(&g_Input_FaultFlag.errIsolation);
    
    /* Current */
    Rte_Read_R_FaultFlag_errOverChargeCurrent(&g_Input_FaultFlag.errOverChargeCurrent);
    Rte_Read_R_FaultFlag_errOverDischargeCurrent(&g_Input_FaultFlag.errOverDischargeCurrent);
    
    /* Temperature */
    Rte_Read_R_FaultFlag_errChargeOverTemp(&g_Input_FaultFlag.errChargeOverTemp);
    Rte_Read_R_FaultFlag_errChargeUnderTemp(&g_Input_FaultFlag.errChargeUnderTemp);
    Rte_Read_R_FaultFlag_errDischargeOverTemp(&g_Input_FaultFlag.errDischargeOverTemp);
    Rte_Read_R_FaultFlag_errDischargeUnderTemp(&g_Input_FaultFlag.errDischargeUnderTemp);

    /* --- 7. Fault Flags (Warnings) --- */
    /* Voltage & System */
    Rte_Read_R_FaultFlag_warnOverCharge(&g_Input_FaultFlag.warnOverCharge);
    Rte_Read_R_FaultFlag_warnOverDisCharge(&g_Input_FaultFlag.warnOverDisCharge);
    Rte_Read_R_FaultFlag_warnOverCellVmax(&g_Input_FaultFlag.warnOverCellVmax);
    Rte_Read_R_FaultFlag_warnUnderCellVmin(&g_Input_FaultFlag.warnUnderCellVmin);
    Rte_Read_R_FaultFlag_warnOverIbp(&g_Input_FaultFlag.warnOverIbp);
    
    /* Current */
    Rte_Read_R_FaultFlag_warnOverChargeCurrent(&g_Input_FaultFlag.warnOverChargeCurrent);
    Rte_Read_R_FaultFlag_warnOverDischargeCurrent(&g_Input_FaultFlag.warnOverDischargeCurrent);
    
    /* Temperature */
    Rte_Read_R_FaultFlag_warnChargeOverTemp(&g_Input_FaultFlag.warnChargeOverTemp);
    Rte_Read_R_FaultFlag_warnChargeUnderTemp(&g_Input_FaultFlag.warnChargeUnderTemp);
    Rte_Read_R_FaultFlag_warnDischargeOverTemp(&g_Input_FaultFlag.warnDischargeOverTemp);
    Rte_Read_R_FaultFlag_warnDischargeUnderTemp(&g_Input_FaultFlag.warnDischargeUnderTemp);


    /* ======================================================================
     * 2. Validate Inputs (Global Validation)
     * ====================================================================== */
    if (BMS_Input_ValidateSignals() == FALSE)
    {
        /* 데이터 정합성이 깨진 경우, 안전을 위해 명령을 무시하거나 초기화 */
        /* 시퀀스 다이어그램에서 Validation Fail 경로를 보여주기 좋음 */
        g_Input_VcuCmd.bmsActionCmd = StandAlone;
        g_Input_Signal.ignSignal = LOCK;
    }
}


/*******************************************************************************
 * Function: BMS_Input_ValidateSignals
 * Description: 읽어온 전역 데이터의 정합성(Plausibility) 검증
 *******************************************************************************/
boolean BMS_Input_ValidateSignals(void)
{
    /* Check 1: Voltage vs Current Plausibility */
    /* Pack 전압이 비정상적으로 낮은데 전류가 흐르는 경우 (센서 고장 의심) */
    if ((g_Input_CellMeas.packVoltageSum < 1000U) && (g_Input_CurrMeas.packCurrent > 200)) /* 20.0A */
    {
        return FALSE; /* Invalid */
    }
    
    /* Check 2: Ignition vs VCU Command */
    /* 시동(Ignition)이 꺼져있는데 주행(Driving) 명령이 들어오는 경우 */
    if ((g_Input_Signal.ignSignal == LOCK) && (g_Input_VcuCmd.bmsActionCmd == Driving))
    {
        return FALSE; /* Invalid Command Sequence */
    }

    /* Check 3: Temperature Range Sanity Check */
    /* 온도가 물리적으로 불가능한 값(-40도 미만 또는 150도 초과)인 경우 */
    /* Temp Scale: 1 degC (or 0.1 depending on spec, assuming raw value check) */
    if ((g_Input_TempMeas.cellTempMax > 150) || (g_Input_TempMeas.cellTempMin < -50))
    {
        return FALSE; /* Sensor Error */
    }

    return TRUE; /* Valid */
}