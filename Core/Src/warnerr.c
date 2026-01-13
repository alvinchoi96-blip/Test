/*
 * warnerr.c
 *
 *  Created on: Jul 2, 2020
 *      Author: user
 */
#include "extref.h"
#include "candb.h"
#include "EEProm_data.h"
void Warn_Error_Process(void)
{
	////////////////////////////////////////////////////////////////////////////
	// charge temperature high
	if(ST_CHARGE)
	{
		if (CELL_T_HIGH > CHG_OVER_TEMP_WARN * 10)
		{
			if (CELL_T_HIGH > CHG_OVER_TEMP_ERR * 10)
			{
				ERR_CHARGEOVERTEMP = 1;									// 0x200 12,1,errOverTemp
			}
			else
			{
				WRN_CHARGEOVERTEMP = 1;									// 0x200 4,1,warnOverCellTemp
				ERR_CHARGEOVERTEMP = 0;									// 0x200 12,1,errOverTemp
			}
		}
		else
		{
			WRN_CHARGEOVERTEMP = 0;										// 0x200 4,1,warnOverCellTemp
			ERR_CHARGEOVERTEMP = 0;										// 0x200 12,1,errOverTemp
		}

		////////////////////////////////////////////////////////////////////////////
		// charge temperature low
		if (CELL_T_LOW < CHG_UNDER_TEMP_WARN * 10)
		{
			if (CELL_T_LOW < CHG_UNDER_TEMP_ERR * 10)
			{
				ERR_CHARGEUNDERTEMP = 1;								// 0x200 13,1,errUnderTemp
			}
			else
			{
				WRN_CHARGEUNDERTEMP = 1;								// 0x200 5,1,warnUnderTemp
				ERR_CHARGEUNDERTEMP = 0;								// 0x200 13,1,errUnderTemp
			}
		}
		else
		{
			WRN_CHARGEUNDERTEMP = 0;									// 0x200 5,1,warnUnderTemp
			ERR_CHARGEUNDERTEMP = 0;									// 0x200 13,1,errUnderTemp
		}
	}

	else
	{
		////////////////////////////////////////////////////////////////////////////
		// discharge temperature high
		if (CELL_T_HIGH > DSC_OVER_TEMP_WARN * 10)
		{
			if (CELL_T_HIGH > DSC_OVER_TEMP_ERR * 10)
			{
				ERR_DISCHARGEOVERTEMP = 1;								// 0x200 14,1,errOverTemp
			}
			else
			{
				WRN_DISCHARGEOVERTEMP = 1;								// 0x200 6,1,warnOverCellTemp
				ERR_DISCHARGEOVERTEMP = 0;								// 0x200 14,1,errOverTemp
			}
		}
		else
		{
			WRN_DISCHARGEOVERTEMP = 0;									// 0x200 6,1,warnOverCellTemp
			ERR_DISCHARGEOVERTEMP = 0;									// 0x200 14,1,errOverTemp
		}

		////////////////////////////////////////////////////////////////////////////
		// discharge temperature low
		if (CELL_T_LOW < DSC_UNDER_TEMP_WARN * 10)
		{
			if (CELL_T_LOW < DSC_UNDER_TEMP_ERR * 10)
			{
				ERR_DISCHARGEUNDERTEMP = 1;								// 0x200 15,1,errUnderTemp
			}
			else
			{
				WRN_DISCHARGEUNDERTEMP = 1;								// 0x200 7,1,warnUnderTemp
				ERR_DISCHARGEUNDERTEMP = 0;								// 0x200 15,1,errUnderTemp
			}
		}
		else
		{
			WRN_DISCHARGEUNDERTEMP = 0;									// 0x200 7,1,warnUnderTemp
			ERR_DISCHARGEUNDERTEMP = 0;									// 0x200 15,1,errUnderTemp
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	// IBP is very high then cut-off
	if (CELL_V_DEVI > VOL_IBP_WARN)
	{
		if (CELL_V_DEVI > VOL_IBP_ERR)
		{
			if(++usIBPerrTmr >= TMR2S_100HZ)									//10second delay ;
			{
				usIBPerrTmr = TMR2S_100HZ;
				ERR_OVERIBP = 1;										// 0x200 24,1,errOverIBP
			}
		}
		else
		{
			usIBPerrTmr = 0;
			WRN_OVERIBP = 1;											// 0x200 16,1,warnOverIBP
//			ERR_OVERIBP = 0;											// 0x200 24,1,errOverIBP			error release disabled
		}
	}
	else
	{
		WRN_OVERIBP = 0;												// 0x200 16,1,warnOverIBP
//		ERR_OVERIBP = 0;												// 0x200 24,1,errOverIBP			error release disabled
	}


	if (ERR_FLAG1 || ERR_FLAG2)
		ERR_FAULTFLAG = 1;												// 0x200 32, 1, errFaultFlag
	if (ERR_FAULTFLAG == 1)
	{
		if (!WARN_FLAG && !ERR_FLAG1 && !ERR_FLAG2)
		{
			ERR_FAULTFLAG = 0;
		}
	}
	if (WARN_FLAG1 || WARN_FLAG2)
		WARN_FLAG = 1;												// 0x200 32, 1, errFaultFlag
	else
		WARN_FLAG = 0;												// 0x200 32, 1, errFaultFlag
}

void DCHG_Warn_Error_Process(void)									//Over voltage protection disabled in discharge mode - for regen
{
/*	//////////////////////////////////////////////////////////////////////////////
	// over charging Voltage
	if (ulSum_Vol > OVER_VOL_WARN * TOT_CELLS)
	{
		if (ulSum_Vol > OVER_VOL_ERR * TOT_CELLS)
		{

			ERR_OVERCHARGE = 1;										// 0x200 8,1,errOverCharge
		}
		else
		{
			WRN_OVERCHARGE = 1;										// 0x200 0,1,warnOverCharge
			ERR_OVERCHARGE = 0;										// 0x200 8,1,errOverCharge
		}
	}
	else
	{
		WRN_OVERCHARGE = 0;											// 0x200 0,1,warnOverCharge
		ERR_OVERCHARGE = 0;											// 0x200 8,1,errOverCharge
	}
*/

	//////////////////////////////////////////////////////////////////////////////
	// over charge current
	/*	if (usChargeCurrent  > CHG_OVER_CURR_WARN)
	{
		if (usChargeCurrent  > CHG_OVER_CURR_E]RR)
		{
			ERR_OVERCHARGECURRENT = 1;								// 0x200 25,1,errOverChargeCurrent
		}
		else
		{
			WRN_OVERCHARGECURRENT = 1;								// 0x200 17,1,warnOverChargeCurrent
			ERR_OVERCHARGECURRENT = 0;								// 0x200 25,1,errOverChargeCurrent
		}
	}
	else
	{
		WRN_OVERCHARGECURRENT = 0;									// 0x200 17,1,warnOverChargeCurrent
		ERR_OVERCHARGECURRENT = 0;									// 0x200 25,1,errOverChargeCurrent
	}
	 */
	//////////////////////////////////////////////////////////////////////////////
	// over discharge current
	if (usDischargeCurrent  > DSC_OVER_CURR_WARN)
	{
		if (usDischargeCurrent > DSC_OVER_CURR_ERR)					//250A, 10sec
		{
			if(++usDCHG_OCPtmr >= TMR10S_100HZ)
			{
				ERR_OVERDISCHARGECURRENT = 1;						// 0x200 26,1,errOverDischargeCurrent
				usDCHG_OCPtmr = TMR10S_100HZ;
			}
		}
		else
		{
			WRN_OVERDISCHARGECURRENT = 1;							// 0x200 18,1,warnOverDischargeCurrent
			ERR_OVERDISCHARGECURRENT = 0;							// 0x200 26,1,errOverDischargeCurrent
			usDCHG_OCPtmr = 0;
		}
	}
	else
	{
		WRN_OVERDISCHARGECURRENT = 0;								// 0x200 18,1,warnOverDischargeCurrent
		ERR_OVERDISCHARGECURRENT = 0;								// 0x200 26,1,errOverDischargeCurrent
		usDCHG_OCPtmr = 0;
	}
	if (usDischargeCurrent  > 3000)
	{
		ERR_OVERDISCHARGECURRENT = 1;
	}
	//////////////////////////////////////////////////////////////////////////////
	// over discharge
	if (ulSum_Vol < UNDER_VOL_WARN * TOT_CELLS)
	{
		if (ulSum_Vol <= UNDER_VOL_ERR * TOT_CELLS)
		{
			if(++usDCHG_UVPtmr >= TMR5MIN_100HZ)
			{
				ERR_OVERDISCHARGE = 1;									// 0x200 9,1,errOverDischarge
				usDCHG_UVPtmr = TMR5MIN_100HZ;
			}

		}
		else
		{
			WRN_OVERDISCHARGE = 1;									// 0x200 1,1,warnOverDischarge
			ERR_OVERDISCHARGE = 0;									// 0x200 9,1,errOverDischarge
			usDCHG_UVPtmr = 0;
		}
	}
	else
	{
		WRN_OVERDISCHARGE = 0;										// 0x200 1,1,warnOverDischarge
		ERR_OVERDISCHARGE = 0;										// 0x200 9,1,errOverDischarge
		usDCHG_UVPtmr = 0;
	}
/*
	//////////////////////////////////////////////////////////////////////////////
	// cell high voltage
	if (CELL_V_HIGH > OVER_VOL_WARN)
	{
		if (CELL_V_HIGH > OVER_VOL_ERR)
		{
			ERR_OVERCELLV = 1;											// 0x200 10,1,errOverCellVmax
		}
		else
		{
			WRN_OVERCELLV = 1;											// 0x200 2,1,warnOverCellVmax
			ERR_OVERCELLV = 0;											// 0x200 10,1,errOverCellVmax
		}
	}
	else
	{
		WRN_OVERCELLV = 0;												// 0x200 2,1,warnOverCellVmax
		ERR_OVERCELLV = 0;												// 0x200 10,1,errOverCellVmax
	}
*/
	//////////////////////////////////////////////////////////////////////////////
	// cell low voltage
	if (CELL_V_LOW < UNDER_VOL_WARN)
	{
		if (CELL_V_LOW <= UNDER_VOL_ERR)
		{
			if(++usDCHG_CUVPtmr >= TMR5MIN_100HZ)
			{
			ERR_UNDERCELLV = 1;											// 0x200 11,1,errUnderCellVmin
			usDCHG_CUVPtmr = TMR5MIN_100HZ;
			}
		}
		else
		{
			WRN_UNDERCELLV = 1;											// 0x200 3,1,warnUnderCellVmin
			ERR_UNDERCELLV = 0;											// 0x200 11,1,errUnderCellVmin
			usDCHG_CUVPtmr = 0;
		}
	}
	else
	{
		WRN_UNDERCELLV = 0;												// 0x200 3,1,warnUnderCellVmin
		ERR_UNDERCELLV = 0;												// 0x200 11,1,errUnderCellVmin
		usDCHG_CUVPtmr = 0;
	}
//
//충전이 끊어져 charge mode 종료되면(방전모드진입) error release 안되는 문제 -> 5분간 release 조건 충족하면 charge error release
//
	if (CELL_V_HIGH <= OVER_VOL_ERR)
	{
		if(++usCHG_POVRtmr >= TMR5MIN_100HZ)
		{
			WRN_OVERCELLV = 0;												// 0x200 2,1,warnOverCellVmax
			ERR_OVERCELLV = 0;												// 0x200 10,1,errOverCellVmax
			usCHG_POVRtmr = TMR5MIN_100HZ;
		}
	}
	else
		usCHG_POVRtmr = 0;

	if (ulSum_Vol <= OVER_VOL_ERR * TOT_CELLS)
	{
		if(++usCHG_OVRtmr >= TMR5MIN_100HZ)
		{
			WRN_OVERCHARGE = 0;											// 0x200 0,1,warnOverCharge
			ERR_OVERCHARGE = 0;											// 0x200 8,1,errOverCharge
			usCHG_OVRtmr = TMR5MIN_100HZ;
		}
	}
	else
		usCHG_OVRtmr = 0;
}

void CHG_Warn_Error_Process(void)
{
	//////////////////////////////////////////////////////////////////////////////
	// over charging Voltage
	if (ulSum_Vol > OVER_VOL_WARN * TOT_CELLS)
	{
		if (ulSum_Vol > OVER_VOL_ERR * TOT_CELLS)
		{
			ERR_OVERCHARGE = 1;										// 0x200 8,1,errOverCharge
		}
		else
		{
			WRN_OVERCHARGE = 1;										// 0x200 0,1,warnOverCharge
			ERR_OVERCHARGE = 0;										// 0x200 8,1,errOverCharge
		}
	}
	else
	{
		WRN_OVERCHARGE = 0;											// 0x200 0,1,warnOverCharge
		ERR_OVERCHARGE = 0;											// 0x200 8,1,errOverCharge
	}

	//////////////////////////////////////////////////////////////////////////////
	// over charge current
	if (usChargeCurrent  > CHG_OVER_CURR_WARN)
	{
		if (usChargeCurrent  > CHG_OVER_CURR_ERR)
		{
			ERR_OVERCHARGECURRENT = 1;								// 0x200 25,1,errOverChargeCurrent
		}
		else
		{
			WRN_OVERCHARGECURRENT = 1;								// 0x200 17,1,warnOverChargeCurrent
			ERR_OVERCHARGECURRENT = 0;								// 0x200 25,1,errOverChargeCurrent
		}
	}
	else
	{
		WRN_OVERCHARGECURRENT = 0;									// 0x200 17,1,warnOverChargeCurrent
		ERR_OVERCHARGECURRENT = 0;									// 0x200 25,1,errOverChargeCurrent
	}
/*
	//////////////////////////////////////////////////////////////////////////////
	// over discharge current
	if (usDischargeCurrent  > DSC_OVER_CURR_WARN)
	{
		if (usDischargeCurrent > DSC_OVER_CURR_ERR)
		{
			ERR_OVERDISCHARGECURRENT = 1;							// 0x200 26,1,errOverDischargeCurrent
		}
		else
		{
			WRN_OVERDISCHARGECURRENT = 1;							// 0x200 18,1,warnOverDischargeCurrent
			ERR_OVERDISCHARGECURRENT = 0;							// 0x200 26,1,errOverDischargeCurrent
		}
	}
	else
	{
		WRN_OVERDISCHARGECURRENT = 0;								// 0x200 18,1,warnOverDischargeCurrent
		ERR_OVERDISCHARGECURRENT = 0;								// 0x200 26,1,errOverDischargeCurrent
	}
*/
/*	//////////////////////////////////////////////////////////////////////////////
	// over discharge
	if (ulSum_Vol < UNDER_VOL_WARN * TOT_CELLS)
	{
		if (ulSum_Vol <= UNDER_VOL_ERR * TOT_CELLS)
		{
			ERR_OVERDISCHARGE = 1;									// 0x200 9,1,errOverDischarge
		}
		else
		{
			WRN_OVERDISCHARGE = 1;									// 0x200 1,1,warnOverDischarge
			ERR_OVERDISCHARGE = 0;									// 0x200 9,1,errOverDischarge
		}
	}
	else
	{
		WRN_OVERDISCHARGE = 0;										// 0x200 1,1,warnOverDischarge
		ERR_OVERDISCHARGE = 0;										// 0x200 9,1,errOverDischarge
	}
*/
	//////////////////////////////////////////////////////////////////////////////
	// cell high voltage
	if (CELL_V_HIGH > OVER_VOL_WARN)
	{
		if (CELL_V_HIGH > OVER_VOL_ERR)
		{
			ERR_OVERCELLV = 1;											// 0x200 10,1,errOverCellVmax
		}
		else
		{
			WRN_OVERCELLV = 1;											// 0x200 2,1,warnOverCellVmax
			ERR_OVERCELLV = 0;											// 0x200 10,1,errOverCellVmax
		}
	}
	else
	{
		WRN_OVERCELLV = 0;												// 0x200 2,1,warnOverCellVmax
		ERR_OVERCELLV = 0;												// 0x200 10,1,errOverCellVmax
	}

/*	//////////////////////////////////////////////////////////////////////////////
	// cell low voltage
	if (CELL_V_LOW < UNDER_VOL_WARN)
	{
		if (CELL_V_LOW <= UNDER_VOL_ERR)
		{
			ERR_UNDERCELLV = 1;											// 0x200 11,1,errUnderCellVmin
		}
		else
		{
			WRN_UNDERCELLV = 1;											// 0x200 3,1,warnUnderCellVmin
			ERR_UNDERCELLV = 0;											// 0x200 11,1,errUnderCellVmin
		}
	}
	else
	{
		WRN_UNDERCELLV = 0;												// 0x200 3,1,warnUnderCellVmin
		ERR_UNDERCELLV = 0;												// 0x200 11,1,errUnderCellVmin
	}
*/
}
