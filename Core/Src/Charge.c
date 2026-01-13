/*
 * Charge.c
 *charge process for golfcart BMS,
 *  Created on: 2022. 9. 28.
 *      Author: Alvin
 */
#include "candb.h"
#include "extref.h"
#include "main.h"
void ChargeProcess(void)
{
	switch(ucChargeStep)
	{
	case 0://AC Plug recognized
		ERR_LED = ON;														//Green LED ON
		FULL_LED = OFF;
		if(I_TOT_ACTUAL > 20)
		{
			usChargeStepTmr = 0;
			ucChargeStep = 1;												//Charge started
		}
		else
		{
			if(V_TOT_ACTUAL > 800)
			{
				if(++usChargeStepTmr >= TMR30S_100HZ)
				{
					usChargeStepTmr = 0;
					ucChargeStep = 5;										//Full-charged
				}
			}
			else
			{
				if(++usChargeStepTmr >= TMR30S_100HZ)
				{
					usChargeStepTmr = 0;
					ucChargeStep = 10;										//Charge error
				}
			}
		}
		break;
	case 1:
		FULL_LED = OFF;
		if(++ucChgLED_Count == TMR07S_100HZ)
		{
			ucChgLED_Count = 0;
			ERR_LED = !ERR_LED;
		}
		if(V_TOT_ACTUAL > 800)
		{
			if(I_TOT_ACTUAL < 20)
			{
				if(++usChargeStepTmr >= TMR30S_100HZ)
				{
					ucChargeStep = 5;									//full-charged
					usChargeStepTmr = 0;
				}
			}
		}
		else
		{
			if(I_TOT_ACTUAL < 20)
			{
				if(++usChargeStepTmr >= TMR30S_100HZ)
				{
					ucChargeStep = 10;									//charge error - low current
					usChargeStepTmr = 0;
				}
			}
		}
		break;

	case 5://full-charged, no escape until AC plug re-connected
		ERR_LED = ON;														//Green LED on
		FULL_LED = OFF;
		ucChargeStep = 5;
		break;

	case 10://charge error
		if(++ucChgLED_Count == TMR07S_100HZ)								//Red LED blink
		{
			ucChgLED_Count = 0;
			FULL_LED = !FULL_LED;
		}
		ERR_LED = OFF;
		ucChargeStep = 10;
		break;

	default :
		ucChargeStep = 10;
		break;
	}
}
