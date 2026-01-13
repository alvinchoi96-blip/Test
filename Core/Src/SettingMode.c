/*
 * SettingMode.c
 *
 *  Created on: 2022. 3. 3.
 *      Author: 82107
 */

#include "main.h"
#include "EEProm_data.h"
#include "candb.h"
#include "SettingMode.h"
#include "extref.h"
#ifdef ROOT
#define EXT
#else
#define EXT extern
#endif

void WriteToFlash(void)
{
	HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD);
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);

	flash_cmd[0] = 0x50;											// enable write status register
	flash_cmd[1] = 0x00;											// enable write status register
	flash_cmd[2] = 0x00;											// enable write status register
	flash_cmd[3] = 0x02;											// enable write status register
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);			// CS = low
	HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 1, 10);					// send command
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);				// CS = high

	HAL_Delay(1);

	flash_cmd[0] = 0x01;											// write status register
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);			// CS = low
	HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 2, 10);					// send command
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);				// CS = high

	HAL_Delay(1);

	flash_cmd[0] = 0x06;											// write enable
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);			// CS = low
	HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 1, 10);					// send command
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);				// CS = high

	HAL_Delay(1);

	flash_cmd[0] = 0x05;											// read status
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);			// CS = low
	HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 1, 10);					// send block 0 erase command
	HAL_SPI_Receive(&hspi1, &flash_ststus, 1, 10);					// receive status
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);				// CS = high

	HAL_Delay(1);

	flash_cmd[0] = 0x52;											// block 0(32K) erase
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);			// CS = low
	HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 4, 10);					// send command
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);				// CS = high

	HAL_Delay(1);

	flash_ststus = 1;
	while(flash_ststus & 1)
	{
		flash_cmd[0] = 0x05;										// read status
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);		// CS = low
		HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 1, 10);				// send block 0 erase command
		HAL_SPI_Receive(&hspi1, &flash_ststus, 1, 10);				// receive status
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);			// CS = high
		HAL_Delay(1);
	}

	flash_cmd[0] = 0x06;											// write enable
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);			// CS = low
	HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 1, 10);					// send command
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);				// CS = high

	HAL_Delay(1);

	flash_cmd[0] = 0xAF;											// Auto Address Increment
	flash_cmd[3] = 0x02;											// first ROM data byte
	flash_cmd[4] = unRom.BY[0];										// first ROM data byte
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);			// CS = low
	HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 5, 10);					// send command
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);				// CS = high
	HAL_Delay(1);

	for(uint32_t i = 1; i < 1600; i++)
	{
		flash_cmd[1] = unRom.BY[i];									// next ROM data byte
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);		// CS = low
		HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 2, 10);				// send command
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);			// CS = high
		HAL_Delay(1);
	}

	flash_cmd[0] = 0x04;											// write disable
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);			// CS = low
	HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 1, 10);					// send command
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);				// CS = high

	flash_cmd[0] = 0x05;											// read status
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);			// CS = low
	HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 1, 10);					// send command
	HAL_SPI_Receive(&hspi1, &flash_ststus, 1, 10);					// receive status
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);				// CS = high
	HAL_Delay(1);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, ON);				//notice data saving has completed(buzzer)
	HAL_RTC_WaitForSynchro(&hrtc);
//	TimeUpdate();
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
	HAL_Delay(200);
//	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_BKP_CLK_ENABLE();
//	ReadFromFlash();
}

void ReadFromFlash(void)
{
	uint32_t i;
	for(i = 0; i < 1600; i++)
		unRom.BY[i] = 0;

	//	uint8_t flash_cmd[4] = {0x03, 0x00, 0x00, 0x00};
	//uint8_t flash_cmd[4] = {0x03, 0x00, 0x02, 0x00};
	flash_cmd[0] = 0x03;
	flash_cmd[3] = 0x02;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);			// CS = low
	HAL_SPI_Transmit(&hspi1, &flash_cmd[0], 4, 10);					// send read command
	HAL_SPI_Receive(&hspi1, &unRom.BY[0], 1600, 1000);				// receive
	while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_RX);		// wait
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);			// CS = high
	HAL_Delay(100);
	ValueAssign();
}

void SettingMode(void)
{
	if(!SettingmodeFlag)
	{
		if(++usTimeUpdateTmr >= TMR2S_100HZ)
		{
			usTimeUpdateTmr = 0;
			TimeUpdate();
			FB_YEAR = BCDtoDEC(DateToUpdate.Year);
			FB_MONTH = BCDtoDEC(DateToUpdate.Month);
			FB_DATE = BCDtoDEC(DateToUpdate.Date);
			FB_HOUR = BCDtoDEC(sTime.Hours);
			FB_MINUTE = BCDtoDEC(sTime.Minutes);
			FB_SAVE_COMPLETE = OFF;
			CAN_Tx_Process(0x3FC, un3FCValueFeedback.BY);
		}
	}
	else
	{
		usTimeUpdateTmr = 0;
		unSettingBit.B.ModeFeedback = SettingmodeFlag;

		//********************************
		//Over Charge Protection / Release
		//********************************
		if(unSettingBit.B.ChargeCutLevel)
		{
			FB_VOLTAGE = unRom.B.OverVoltageCut;				//4.200V -> 4200
			if(CMD_UP)
			{
				FB_VOLTAGE += 50;
				CMD_UP = 0;
			}
			if(CMD_DOWN)
			{
				FB_VOLTAGE -= 50;
				CMD_DOWN = 0;
			}
			unRom.B.OverVoltageCut = FB_VOLTAGE;
		}
		if(unSettingBit.B.ChargeReleaseLevel)
		{
			FB_VOLTAGE = unRom.B.OverVoltageRelease;				//4.200V -> 4200
			if(CMD_UP)
			{
				FB_VOLTAGE += 50;
				CMD_UP = 0;
			}
			if(CMD_DOWN)
			{
				FB_VOLTAGE -= 50;
				CMD_DOWN = 0;
			}
			unRom.B.OverVoltageRelease = FB_VOLTAGE;
		}
		if(unRom.B.OverVoltageRelease >= unRom.B.OverVoltageCut)			//Error-Release hysteresis
		{
			unRom.B.OverVoltageRelease = unRom.B.OverVoltageCut-50;
		}
		//********************************
		//Over Discharge Protection / Release
		//********************************
		if(unSettingBit.B.DischargeCutLevel)
		{
			FB_VOLTAGE = unRom.B.UnderVoltageCut;				//4.200V -> 4200
			if(CMD_UP)
			{
				FB_VOLTAGE += 50;
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_VOLTAGE -= 50;
				CMD_DOWN = 0;
			}
			unRom.B.UnderVoltageCut = FB_VOLTAGE;
		}
		if(unSettingBit.B.DischargeReleaseLevel)
		{
			FB_VOLTAGE = unRom.B.UnderVoltageRelease;				//4.200V -> 4200
			if(CMD_UP)
			{
				FB_VOLTAGE += 50;
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_VOLTAGE -= 50;
				CMD_DOWN = 0;
			}
			unRom.B.UnderVoltageRelease = FB_VOLTAGE;
		}
		if(unRom.B.UnderVoltageRelease <= unRom.B.UnderVoltageCut)			//Error-Release hysteresis
		{
			unRom.B.UnderVoltageRelease = unRom.B.UnderVoltageCut+50;
		}
		//********************************
		//IBP(Imbalance protection) / Release
		//********************************
		if(unSettingBit.B.IBPLevel)
		{
			FB_VOLTAGE = unRom.B.IBPCut;				//4.200V -> 4200
			if(CMD_UP)
			{
				FB_VOLTAGE += 50;
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_VOLTAGE -= 50;
				CMD_DOWN = 0;
			}
			unRom.B.IBPCut = FB_VOLTAGE;
		}
		if(unSettingBit.B.IBPReleaseLevel)
		{
			FB_VOLTAGE = unRom.B.IBPRelease;				//4.200V -> 4200
			if(CMD_UP)
			{
				FB_VOLTAGE += 50;
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_VOLTAGE -= 50;
				CMD_DOWN = 0;
			}
			unRom.B.IBPRelease = FB_VOLTAGE;
		}
		if(unRom.B.IBPRelease >= unRom.B.IBPCut)			//Error-Release hysteresis
		{
			unRom.B.IBPRelease = unRom.B.IBPCut-100;
		}
		//********************************
		//Cell balance range
		//********************************
		if(unSettingBit.B.CellBalanceStartIBPLevel)
		{
			FB_VOLTAGE = unRom.B.BalanceStartLVL;
			if(CMD_UP)
			{
				FB_VOLTAGE += 10;
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_VOLTAGE -= 10;
				CMD_DOWN = 0;
			}
			unRom.B.BalanceStartLVL = FB_VOLTAGE;
		}
		if(unSettingBit.B.CellBalanceTargetIBPLevel)
		{
			FB_VOLTAGE = unRom.B.BalanceTargetLVL;				//4.200V -> 4200
			if(CMD_UP)
			{
				FB_VOLTAGE += 10;
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_VOLTAGE -= 10;
				CMD_DOWN = 0;
			}
			unRom.B.BalanceTargetLVL = FB_VOLTAGE;
		}
		if(unRom.B.BalanceTargetLVL >= unRom.B.BalanceStartLVL)
		{
			unRom.B.BalanceTargetLVL = unRom.B.BalanceStartLVL-10;
		}
		if(unRom.B.BalanceStartLVL < 10)
		{
			unRom.B.BalanceStartLVL = 0;
			unRom.B.BalanceTargetLVL = 0;
		}
		//********************************
		//Over Temp Protection
		//********************************
		if(unSettingBit.B.HighTempCutLevel)
		{
			FB_TEMP = unRom.B.OverTempCut;
			if(CMD_UP)
			{
				FB_TEMP += 5;									//1 degree c = 1
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_TEMP -= 5;
				CMD_DOWN = 0;
			}
			unRom.B.OverTempCut = FB_TEMP;
		}
		if(unSettingBit.B.HighTempReleaseLevel)
		{
			FB_TEMP = unRom.B.OverTempRelease;
			if(CMD_UP)
			{
				FB_TEMP += 5;
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_TEMP -= 5;
				CMD_DOWN = 0;
			}
			unRom.B.OverTempRelease = FB_TEMP;
		}
		if(unRom.B.OverTempRelease >= unRom.B.OverTempCut)
		{
			unRom.B.OverTempRelease = unRom.B.OverTempCut-5;
		}
		//********************************
		//Under Temp Protection
		//********************************
		if(unSettingBit.B.LowTempCutLevel)
		{
			FB_TEMP = unRom.B.UnderTempCut;
			if(CMD_UP)
			{
				FB_TEMP += 5;									//1 degree c = 1
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_TEMP -= 5;
				CMD_DOWN = 0;
			}
			unRom.B.UnderTempCut = FB_TEMP;
		}
		if(unSettingBit.B.LowTempReleaseLevel)
		{
			FB_TEMP = unRom.B.UnderTempRelease;
			if(CMD_UP)
			{
				FB_TEMP += 5;
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_TEMP -= 5;
				CMD_DOWN = 0;
			}
			unRom.B.UnderTempRelease = FB_TEMP;
		}
		if(unRom.B.UnderTempRelease <= unRom.B.UnderTempCut)
		{
			unRom.B.UnderTempRelease = unRom.B.UnderTempCut+5;
		}
		//********************************
		//Charge over current Protection
		//********************************
		if(unSettingBit.B.ChargeCurrentCutLevel)
		{
			FB_CURRENT = unRom.B.OverChargeCurrentCut;
			if(CMD_UP)
			{
				FB_CURRENT += 10;									//10:1
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_CURRENT -= 10;
				CMD_DOWN = 0;
			}
			unRom.B.OverChargeCurrentCut = FB_CURRENT;
		}
		//********************************
		//Discharge over current Protection
		//********************************

		if(unSettingBit.B.DischargeCurrentCutLevel)
		{
			FB_CURRENT = unRom.B.OverDischargeCurrentCut;
			if(CMD_UP)
			{
				FB_CURRENT += 50;
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_CURRENT -= 50;
				CMD_DOWN = 0;
			}
			unRom.B.OverDischargeCurrentCut = FB_CURRENT;
		}
		if(unRom.B.UnderTempRelease <= unRom.B.UnderTempCut)
		{
			unRom.B.UnderTempRelease = unRom.B.UnderTempCut+5;
		}
		//********************************
		//Cycle Configure
		//********************************
		FB_CYCLE = unRom.B.Cycle;
		if(unSettingBit.B.Cycle)
		{

			if(CMD_UP)
			{
				FB_CYCLE += 100;									//1 :1
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_CYCLE -= 100;
				CMD_DOWN = 0;
			}
			unRom.B.Cycle = FB_CYCLE;
		}
		if(unRom.B.Cycle > 2500 && unRom.B.Cycle < 60000)
		{
			unRom.B.Cycle = 2500;
		}
		else if(unRom.B.Cycle > 60000)
		{
			unRom.B.Cycle = 0;
		}
		//********************************
		//Capacity configure
		//********************************
		FB_CAPACITY = unRom.B.Capacity;
		if(unSettingBit.B.Capacity_pack)
		{

			if(CMD_UP)
			{
				FB_CAPACITY += 10;									//10 :1
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_CAPACITY -= 10;
				CMD_DOWN = 0;
			}
			unRom.B.Capacity = FB_CAPACITY;
		}
		if(unRom.B.Capacity > 2500 && unRom.B.Capacity < 60000)
		{
			unRom.B.Capacity = 2500;
		}
		else if(unRom.B.Capacity > 60000)
		{
			unRom.B.Capacity = 0;
		}

		CAN_Tx_Process(0x3FB, un3FBValueFeedback.BY);


		//********************************
		//Date Configure
		//********************************

		if(unSettingBit.B.Year)
		{
			if(CMD_UP)
			{
				FB_YEAR += 1;									//1 :1
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_YEAR -= 1;
				CMD_DOWN = 0;
			}
			unRom.B.Year = FB_YEAR;
		}
		if(unSettingBit.B.Month)
		{
			if(CMD_UP)
			{
				FB_MONTH += 1;									//1 :1
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_MONTH -= 1;
				CMD_DOWN = 0;
			}
			if(FB_MONTH > 12 && FB_MONTH <= 20)
			{
				FB_MONTH = 1;
			}
			if(FB_MONTH == 0 || FB_MONTH > 20)
			{
				FB_MONTH = 12;
			}
			unRom.B.Month = FB_MONTH;
		}
		if(unSettingBit.B.Day)
		{
			if(CMD_UP)
			{
				FB_DATE += 1;									//1 :1
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_DATE -= 1;
				CMD_DOWN = 0;
			}
			if(FB_DATE > 31 && FB_DATE <= 40)
			{
				FB_DATE = 1;
			}
			if(FB_DATE == 0 || FB_DATE > 40)
			{
				FB_DATE = 31;
			}
			unRom.B.Date = FB_DATE;
		}
		if(unSettingBit.B.Time)
		{
			if(CMD_UP)
			{
				FB_HOUR += 1;									//1 :1
				CMD_UP = 0;
			}
			if(CMD_DOWN)
			{
				FB_HOUR -= 1;
				CMD_DOWN = 0;
			}
			if(FB_HOUR >= 24 && FB_HOUR <= 40)
			{
				FB_HOUR = 0;
			}
			if( FB_HOUR > 40)
			{
				FB_HOUR = 23;
			}
			unRom.B.Hour = FB_HOUR;
		}
		if(unSettingBit.B.Minute)
		{
			if(CMD_UP)
			{
				FB_MINUTE += 5;									//1 :1
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_MINUTE -= 5;
				CMD_DOWN = 0;
			}
			if(FB_MINUTE > 60 && FB_MINUTE <= 100)
			{
				FB_MINUTE = 0;
			}
			if(FB_MINUTE > 100 )
			{
				FB_MINUTE = 59;
			}
			unRom.B.Minute = FB_MINUTE;
		}
		//********************************
		//Pack Serial number Configure
		//********************************
		FB_S = unRom.B.Serial;
		if(unSettingBit.B.Serial)
		{
			if(CMD_UP)
			{
				FB_S += 1;									//1 :1
				CMD_UP = 0;
			}

			if(CMD_DOWN)
			{
				FB_S -= 1;
				CMD_DOWN = 0;
			}

			unRom.B.Serial = FB_S;
		}
		if(SavemodeFlag)
		{
			FB_SAVE_COMPLETE = ON;
			DateToUpdate.Year = DECtoBCD(FB_YEAR);
			DateToUpdate.Month = DECtoBCD(FB_MONTH);
			DateToUpdate.Date = DECtoBCD(FB_DATE);
			sTime.Hours = DECtoBCD(FB_HOUR);
			sTime.Minutes = DECtoBCD(FB_MINUTE);
			WriteToFlash();
			SavemodeFlag = 0;
			HAL_RTC_WaitForSynchro(&hrtc);
		}
		if(unSettingBit.B.SetDefault)
			SetDefault();
		SettingmodeFlag = OFF;
		CAN_Tx_Process(0x3FA, unSettingBit.BY);					//monitoring button feedback(3F2->3FA)
		CAN_Tx_Process(0x3FC, un3FCValueFeedback.BY);
	}
}

void SetDefault(void)
{
	unRom.B.OverVoltageCut = 4250;
	unRom.B.OverVoltageRelease = 4200;
	unRom.B.UnderVoltageCut = 2750;
	unRom.B.UnderVoltageRelease = 2900;

	unRom.B.OverTempCut = 70;
	unRom.B.OverTempRelease = 50;
	unRom.B.UnderTempCut = -20;
	unRom.B.UnderTempRelease = -5;

	unRom.B.OverChargeCurrentCut = 200;				//200: 20.0A
	unRom.B.OverDischargeCurrentCut = 3000;			//3000 : 300.0A

	unRom.B.IBPCut = 1000;							// 1000 : 1.000V
	unRom.B.IBPRelease = 350;						// 300 : 0.300V
	unRom.B.BalanceStartLVL = 50;					//50 : 50mV
	unRom.B.BalanceTargetLVL = 10;					//10 : 10mV
/*
	unRom.B.Year = 22;								//2000 : 00, 2022 : 22
	unRom.B.Month = 12;
	unRom.B.Date = 17;
	unRom.B.Hour = 0;
	unRom.B.Minute = 0;
*/
	unRom.B.Serial = 20;
	unRom.B.Parellel = 40;

	unRom.B.Capacity = 1000;						// 1000 : 100.0Ah
	unRom.B.Cycle = 0;
	CMD_SET_DEFAULT = 0;
}
void ValueAssign(void)
{

	//charge temp variables can not be changed with monitoring device
	CHG_OVER_TEMP_ERR = 50;
	CHG_OVER_TEMP_WARN = 40;
	CHG_UNDER_TEMP_WARN = 0;
	CHG_UNDER_TEMP_ERR = -10;
	CHG_OVER_CURR_WARN = 150;				//15A
	DSC_OVER_CURR_WARN = 1700;				//170A
	/////////////////////////////////
	//Voltage Warnings / Errors	//
	/////////////////////////////////
	if(unRom.B.OverVoltageCut < 3000 || unRom.B.OverVoltageCut > 5000)
	{
		unRom.B.OverVoltageCut = 4250;
	}

	OVER_VOL_ERR = unRom.B.OverVoltageCut;

	if(unRom.B.OverVoltageRelease < 3000 || unRom.B.OverVoltageRelease > unRom.B.OverVoltageCut)
	{
		unRom.B.OverVoltageRelease = unRom.B.OverVoltageCut - 50;
	}

	OVER_VOL_WARN = unRom.B.OverVoltageRelease;

	if(unRom.B.UnderVoltageCut < 2000 || unRom.B.UnderVoltageCut > 4000)
	{
		unRom.B.UnderVoltageCut = 2750;
	}

	UNDER_VOL_ERR = unRom.B.UnderVoltageCut;
	if(unRom.B.UnderVoltageRelease < unRom.B.UnderVoltageCut || unRom.B.UnderVoltageRelease > 4000)
	{
		unRom.B.UnderVoltageRelease = unRom.B.UnderVoltageCut + 100;
	}

	UNDER_VOL_WARN = unRom.B.UnderVoltageRelease;
	/////////////////////////////////
	//Temp Warnings / Errors		//
	/////////////////////////////////
	if(unRom.B.OverTempCut < 40 || unRom.B.OverTempCut > 100)
	{
		unRom.B.OverTempCut = 70;
	}

	DSC_OVER_TEMP_ERR = unRom.B.OverTempCut;
	if(unRom.B.OverTempRelease < 20 || unRom.B.OverTempRelease > unRom.B.OverTempCut)
	{
		unRom.B.OverTempRelease = unRom.B.OverTempCut - 10;
	}

	DSC_OVER_TEMP_WARN = unRom.B.OverTempRelease;

	if(unRom.B.UnderTempCut < -50 || unRom.B.UnderTempCut > -5)
	{
		unRom.B.UnderTempCut = -20;
	}

	DSC_UNDER_TEMP_ERR = unRom.B.UnderTempCut;
	if(unRom.B.UnderTempRelease < unRom.B.UnderTempCut || unRom.B.UnderTempRelease > 30)
	{
		unRom.B.UnderTempRelease = unRom.B.UnderTempCut + 10;
	}

	DSC_UNDER_TEMP_WARN = unRom.B.UnderTempRelease;
	/////////////////////////////////
	//Current Warnings / Errors	//
	/////////////////////////////////
	if(unRom.B.OverChargeCurrentCut < 100 || unRom.B.OverChargeCurrentCut > 350)
	{
		unRom.B.OverChargeCurrentCut = 200;
	}

	CHG_OVER_CURR_ERR = unRom.B.OverChargeCurrentCut;
	if(unRom.B.OverDischargeCurrentCut < 1000 || unRom.B.OverDischargeCurrentCut > 3000)
	{
		unRom.B.OverDischargeCurrentCut = 2500;
	}

	DSC_OVER_CURR_ERR = unRom.B.OverDischargeCurrentCut;
	/////////////////////////////////////////////
	//Voltage Imbalalnace Warnings / Errors	//
	/////////////////////////////////////////////
	if(unRom.B.IBPCut < 100 || unRom.B.IBPCut > 1000)
	{
		unRom.B.IBPCut = 1000;
	}

	VOL_IBP_ERR = unRom.B.IBPCut;
	if(unRom.B.IBPRelease < 100 || unRom.B.IBPRelease > unRom.B.IBPCut)
	{
		unRom.B.IBPRelease = 350;
	}

	VOL_IBP_WARN = unRom.B.IBPRelease;
	/////////////////////////////////////////////
	//Cell balancing level variables			//
	/////////////////////////////////////////////
	if(unRom.B.BalanceStartLVL < 10 || unRom.B.BalanceStartLVL >= 100)
	{
		unRom.B.BalanceStartLVL = 50;
	}

	BALANCE_RANGE = unRom.B.BalanceStartLVL;
	if(unRom.B.BalanceTargetLVL < 10 || unRom.B.BalanceTargetLVL >= BALANCE_RANGE)
	{
		unRom.B.BalanceTargetLVL = 10;
	}
	Balancing_Hysteresis = unRom.B.BalanceTargetLVL;

	if(unRom.B.Year == 0)
		unRom.B.Year = 22;

	HAL_RTC_WaitForSynchro(&hrtc);
	DateToUpdate.Month = DECtoBCD(unRom.B.Month);
	DateToUpdate.Date = DECtoBCD(unRom.B.Date);
	DateToUpdate.Year = DECtoBCD(unRom.B.Year);
	sTime.Hours = DECtoBCD(unRom.B.Hour);
	sTime.Minutes = DECtoBCD(unRom.B.Minute);
	HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD);							//rom data assign
	HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD);							//read time and date from backup timer(runs when Vbb off)

	HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD);							//apply to main timer(Vbb is ON)

	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);

}
uint8_t BCDtoDEC(uint8_t BCD)
{
	uint8_t DEC = 0;
	DEC = ((BCD&0xFF)>>4)*10 + (BCD&0x0F)%10;
	return DEC;
}
uint8_t DECtoBCD(uint8_t DEC)
{
	uint8_t BCD = 0;
	BCD = ((DEC/10)<<4) | (DEC%10);
	return BCD;
}
void TimeUpdate(void)
{
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD);
}
void Errorlog(void)												//called once per a second
{
	if(ERR_FAULTFLAG)
	{
		if((un200_TxData.BY[1] == ErrBuffer[0]) && (un200_TxData.BY[3] == ErrBuffer[1]))							//new error == previous error??
		{
			if(++ulErrlogTmr >= TMR10M_1HZ)
			{
				ulErrlogTmr = 0;
				ErrValueAssign();
			}
		}
		else
		{
			ulErrlogTmr = 0;
			ErrValueAssign();
		}
	}
}
void ErrValueAssign(void)
{
	TimeUpdate();
	ErrBuffer[0] = un200_TxData.BY[1];
	ErrBuffer[1] = un200_TxData.BY[3];
	if(++ERRINDEX > 99)
		ERRINDEX = 0;
	unRom.B.Alm[ERRINDEX].ErrOverVoltage = ERR_OVERCHARGE | ERR_OVERCELLV;
	unRom.B.Alm[ERRINDEX].ErrUnderVoltage = ERR_OVERDISCHARGE | ERR_UNDERCELLV;
	unRom.B.Alm[ERRINDEX].ErrChargeTemp = ERR_CHARGEOVERTEMP | ERR_CHARGEUNDERTEMP;
	unRom.B.Alm[ERRINDEX].ErrDischargeTemp = ERR_DISCHARGEOVERTEMP | ERR_DISCHARGEUNDERTEMP;
	unRom.B.Alm[ERRINDEX].ErrOverIBP = ERR_OVERIBP;
	unRom.B.Alm[ERRINDEX].ErrChargeCurrent = ERR_OVERCHARGECURRENT;
	unRom.B.Alm[ERRINDEX].ErrDischargeCurrent = ERR_OVERDISCHARGECURRENT;
	unRom.B.Alm[ERRINDEX].ChargeStatusbit = !AC_ON_SIG;
	//time information
	unRom.B.Alm[ERRINDEX].Month = BCDtoDEC(DateToUpdate.Month);
	unRom.B.Alm[ERRINDEX].Date = BCDtoDEC(DateToUpdate.Date);
	unRom.B.Alm[ERRINDEX].Hour = BCDtoDEC(sTime.Hours);
	unRom.B.Alm[ERRINDEX].Minute = BCDtoDEC(sTime.Minutes);

	unRom.B.Alm[ERRINDEX].PackVoltage = V_TOT_ACTUAL;
	unRom.B.Alm[ERRINDEX].IBPLevel = CELL_V_DEVI;
	unRom.B.Alm[ERRINDEX].Temp = CELL_T_AVG;
	unRom.B.Alm[ERRINDEX].Current = I_TOT_ACTUAL;
}

void ErrorDisplay(void)
{
	if(CMD_ERRLOG_CALL)
	{
		CMD_ERRLOG_CALL = 0;
		ERRDISP_INDEX = ERRINDEX;
	}
	if(CMD_ERRUP)
	{
		CMD_ERRUP = 0;
		ERRDISP_INDEX++;
	}
	if(CMD_ERRDOWN)
	{
		CMD_ERRDOWN = 0;
		ERRDISP_INDEX--;
	}
	if(ERRDISP_INDEX > 99 && ERRDISP_INDEX < 200)
		ERRDISP_INDEX = 0;
	if(ERRDISP_INDEX >= 200)
		ERRDISP_INDEX = 99;
	/* time information
	un3FD_ErrDisplay1.B.
	*/
	un3FD_ErrDisplay1.B.ErrOverVoltage = unRom.B.Alm[ERRDISP_INDEX].ErrOverVoltage;
	un3FD_ErrDisplay1.B.ErrUnderVoltage = unRom.B.Alm[ERRDISP_INDEX].ErrUnderVoltage;
	un3FD_ErrDisplay1.B.ErrChargeTemp = unRom.B.Alm[ERRDISP_INDEX].ErrChargeTemp;
	un3FD_ErrDisplay1.B.ErrDischargeTemp = unRom.B.Alm[ERRDISP_INDEX].ErrDischargeTemp;
	un3FD_ErrDisplay1.B.ErrOverIBP = unRom.B.Alm[ERRDISP_INDEX].ErrOverIBP;
	un3FD_ErrDisplay1.B.ErrChargeCurrent = unRom.B.Alm[ERRDISP_INDEX].ErrChargeCurrent;
	un3FD_ErrDisplay1.B.ErrDischargeCurrent = unRom.B.Alm[ERRDISP_INDEX].ErrDischargeCurrent;
	un3FD_ErrDisplay1.B.ChargeStatusbit = unRom.B.Alm[ERRDISP_INDEX].ChargeStatusbit;
	//time information
	un3FD_ErrDisplay1.B.Month = unRom.B.Alm[ERRDISP_INDEX].Month;
	un3FD_ErrDisplay1.B.Date = unRom.B.Alm[ERRDISP_INDEX].Date;
	un3FD_ErrDisplay1.B.Hour = unRom.B.Alm[ERRDISP_INDEX].Hour;
	un3FD_ErrDisplay1.B.Minute = unRom.B.Alm[ERRDISP_INDEX].Minute;
	un3FD_ErrDisplay1.B.ErrDispIndex = ERRDISP_INDEX;
	CAN_Tx_Process(0x3FD, un3FD_ErrDisplay1.BY);
	HAL_Delay(5);
	un3FE_ErrDisplay2.B.Voltage = unRom.B.Alm[ERRDISP_INDEX].PackVoltage;
	un3FE_ErrDisplay2.B.Dev = unRom.B.Alm[ERRDISP_INDEX].IBPLevel;
	un3FE_ErrDisplay2.B.Temp = unRom.B.Alm[ERRDISP_INDEX].Temp;
	un3FE_ErrDisplay2.B.Current = unRom.B.Alm[ERRDISP_INDEX].Current;
	CAN_Tx_Process(0x3FE, un3FE_ErrDisplay2.BY);

}
