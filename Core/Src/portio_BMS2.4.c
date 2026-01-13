/*
 * portio.c
 *
 *  Created on: 2020. 9. 9.
 *      Author: user
 */
#include "extref.h"

/******************************************************************************/
/*          Read Key Input                                                    */
/******************************************************************************/
void Read_IGN(void)
{
//****************Power ON signal************************************************
	if (POWER_ON == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2))
		ucChtPower_On = 11;
	else
	{
		if (!--ucChtPower_On)
		{
			ucChtPower_On = 11;
			POWER_ON = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
		}
	}

//*******************AC ON signal*********************************************
	if (AC_ON_SIG == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
		ucChtAC_On_Signal = 11;
	else
	{
		if (!--ucChtAC_On_Signal)
		{
			ucChtAC_On_Signal = 11;
			AC_ON_SIG = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
		}
	}
	//******************Key ON signal*********************************************
		if (KEY_ON_SIG == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
			ucChtKey_On_Signal = 11;
		else
		{
			if (!--ucChtKey_On_Signal)
			{
				ucChtKey_On_Signal = 11;
				KEY_ON_SIG = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
			}
		}
	//******************CAN signal*********************************************
		ST_PWRSW = POWER_ON;
		ST_KEYON = !KEY_ON_SIG;
		ST_ACON = !AC_ON_SIG;
}
/******************************************************************************/
/*          Write Port Output                                                 */
/******************************************************************************/
void Write_Port_Output(void)			//m-BMS H/W ver3.1.
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, ERR_LED);					//AC-On led output
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, FULL_LED);					//charge error led
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, ERR_BUZZ);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, BUZZER);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, BAT_20p);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, BAT_40p);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, BAT_60p);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, BAT_80p);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, BAT_100p);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, HEATER_M);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, HEATER_P);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, CHARGE_M);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, CHARGE_P);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, DISCHARGE_M);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, DISCHARGE_P);

	//Output pin status to CAN bus
	if(CHARGE_P)
		ST_CHGRELAY = ON;
	else
		ST_CHGRELAY = OFF;

	if(DISCHARGE_P)
		ST_DISCHRELAY = ON;
	else
		ST_DISCHRELAY = OFF;

	if(BUZZER)
		ST_BUZZER = ON;
	else
		ST_BUZZER = OFF;
}


