/**
 * @file Bms_StatusDecision.c
 * @brief State Machine Decision Logic
 */
#include "BMS_MainCntrl_GlobalData.h"
#include "Bms_StatusDecision.h"
#include "Rte_SWC_BMS_MainCntrl.h"

/* 외부 참조 */
extern BmsModeContext_Type g_BmsModeContext;

/* =========================================================================
 * Internal Static Helper Functions (If needed)
 * ========================================================================= */
static e_VcuCanCmd CalculateNextOperationMode(void);
static e_VcuCanCmd SetWarnErrFlags(e_VcuCanCmd FltLv);
/* =========================================================================
 * Function Implementation
 * ========================================================================= */

e_VcuCanCmd SetWarnErrFlags(e_VcuCanCmd FltLv)
{
    return FltLv;
}

void SetModeChangedFlag(void)
{
    g_BmsModeContext.isModeChanged = TRUE;
}
e_VcuCanCmd SetNextMode(e_VcuCanCmd nextMode)
{
    return nextMode;
}

e_FaultLevel BMS_Logic_CheckFaults(void)
{
    /* 에러 우선 순위 검사 */
    /*
    if (g_Input_FaultFlag.isAnyError == TRUE)
    {
        SetWarnErrFlags(FltLv_Error);
    }
    if (g_Input_FaultFlag.isAnyWarning == TRUE)
    {
        SetWarnErrFlags(FltLv_Warning);
    }
    SetWarnErrFlags(FltLv_Normal);
    */
    e_FaultLevel FaultLevel = FltLv_Normal;
    if (g_Input_FaultFlag.isAnyWarning == TRUE)
    {
        FaultLevel = SetWarnErrFlags(FltLv_Warning);
        if(g_Input_FaultFlag.isAnyError == TRUE)
        {
            FaultLevel = SetWarnErrFlags(FltLv_Error);
        }
    
    }
    return FaultLevel;
}

/* 긴급 모드 설정 액션 함수 */
void BMS_Logic_SetEmergencyMode(void)
{
    g_BmsModeContext.previousMode = g_BmsModeContext.determinedMode;
    g_BmsModeContext.determinedMode = BmsMd_Emergency;
    
    if (g_BmsModeContext.previousMode != g_BmsModeContext.determinedMode)
    {
        SetModeChangedFlag();
    }
}

/*  정상 운전 판단 액션 함수 */
void BMS_Logic_DetermineNormalOperation(void)
{
    g_BmsModeContext.previousMode = g_BmsModeContext.determinedMode;
    
    /* VCU 명령 및 충전기 연결 상태에 따른 모드 계산 */
    g_BmsModeContext.determinedMode = CalculateNextOperationMode();
    
    if (g_BmsModeContext.previousMode != g_BmsModeContext.determinedMode)
    {
        SetModeChangedFlag();   
    }
}

/* 내부 로직: 실제 VCU 명령 해석 */
static e_VcuCanCmd CalculateNextOperationMode(void)
{
    e_VcuCanCmd nextMode = g_BmsModeContext.previousMode;
    
    if (g_Input_Signal.chargeConnectedFlag == FALSE)
    {
        if(g_Input_VcuCmd.bmsActionCmd == BmsMd_Driving)
        {
            if(g_Input_Signal.ignSignal == IGN_ON || g_Input_Signal.ignSignal == IGN_START)
            {
                nextMode = SetNextMode(BmsMd_Driving);
            }
        }
        else
        {
            nextMode = SetNextMode(BmsMd_Standby);
        }
    }
    else if(g_Input_Signal.chargeConnectedFlag == TRUE)
    {
        if(g_Input_VcuCmd.bmsActionCmd == BmsMd_Charging)
        {
            if(g_Input_Signal.ignSignal == IGN_LOCK || g_Input_Signal.ignSignal == IGN_ACC)
            {
                nextMode = SetNextMode(BmsMd_Charging);
            }
        }
        else
        {
            nextMode = SetNextMode(BmsMd_Standby);
        }
    }
    
    return nextMode;
}