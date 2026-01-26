 /*
 * sub.c
 *
 *  Created on: 2020. 11.2.
 *      Author: JeongHwan
 */

#define ROOT 1

#include "main.h"
#include "EEProm_data.h"
#include "const.h"
#include "candb.h"
#include "SettingMode.h"
#include "extref.h"

/******************** APIs ********************/

void User_Init(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, ON); // Power enable hold

	//battery voltage select
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4))
	{
		CELL_COUNT = 7;
	}
	else
	{
		CELL_COUNT = 10;
	}
		TOT_CELLS = TOTAL_IC * CELL_COUNT;			//20S


	uint32 i;

	ReadFromFlash();

	//////////////////////////////////////////////////////////////////////////////
	CAN_BASE = 0x300;

	ucChtPower_On = 11;
	ucChtPower_Enalbe = 11;
	ucChtAC_On_Signal = 11;
	ucChtKey_On_Signal = 11;

	//0x201_TxData
	ST_BMS_READY = ON;

	//0x208_TxData
	TOT_CELLS = TOTAL_IC * CELL_COUNT;      					// cTotalCells
	TOT_PLACE = TOTAL_IC * 2;               					// cTotalPlace

	//uc202_TxData
//	V_MIN_DISCHARGE = (int16_t)(VOL_LOW * TOT_CELLS / 100); 				// vMinDischarge, 0.1V scale
//	V_MAX_CHARGE = (int16_t)(VOL_HIGH * TOT_CELLS / 100); 				// vMaxCharge, 0.1V scale
	I_MAX_DISCHARGE = (int16_t)DSC_OVER_CURR_WARN;      			// iMaxDischarge, 0.1A scale
	I_MAX_CHARGE = (int16_t)CHG_OVER_CURR_WARN;      				// iMaxCharge, 0.1A scale


	if (HAL_ADCEx_Calibration_Start(&hadc1) != HAL_OK)    		// ADC Calibration Start
	{
		ErrorHandler(2);
	}

	if (HAL_UART_Receive_IT(&huart1, (uint8*) ucpUartRx1Buf, 16) != HAL_OK)
	{
		ErrorHandler(4);
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, ON); //LTC 6820 power enable
	LTC6811_init_cfg(bms_ic);             						// intialize CFG variables
	LTC6811_reset_crc_count(bms_ic);      						// reset PEC counters
	LTC6811_init_reg_limits(bms_ic);      						//
	wakeup_sleep();                      						// wake the LTC6811 from the sleep state
	LTC6811_wrcfg(bms_ic);                						//

///	SOC = Get_OCV_SOC(i);  										// SOC is 0.1% scale, Vol is mV scale

//	REM_AH = (uint32) SOC * (uint16)AMPERE_HOUR / 100;
//	lRemAsec = REM_AH *3600;

//	CAN_Tx_Process(CAN_BASE + 2, un202_TxData.BY);
//	CAN_Tx_Process(CAN_BASE + 8, un202_TxData.BY);
	for(i=0;i<8;i++)			//cell data initialize
	{
		un511_TxData.BY[i]=0x00;
		un512_TxData.BY[i]=0x00;
		un513_TxData.BY[i]=0x00;
		un514_TxData.BY[i]=0x00;
		un515_TxData.BY[i]=0x00;
		un517_TxData.BY[i]=0x00;
	}

	CHARGE_M = 0;
	DISCHARGE_M = 0;

	SW_VER = 23;
}

void Main_Loop(void)
{
	while (F_T10MS == OFF)
		;																// 10msec interval wait
	F_T10MS = OFF;

	Ad_Conversion();

	if(++ucLTC_WAIT_Count == TMR50MS_100HZ)
	{
		ucLTC_WAIT_Count = 0;
		Read_CellData();
	}
	Read_IGN();

	if (++ucSocTimerCnt == TMR1S_100HZ)
	{
		ucSocTimerCnt = 0;
		Errorlog();
		Calculate_SOC();
		Cell_Balancing();
		CAN_Celldata_Assign();
		Read_TempData();
	}

	SettingMode();

	if(VCU_RELAY_ON)
	{
		Relays_Control(ON);
	}
	else
	{
		if(!ERR_FAULTFLAG)
		{
			Relays_Control(ON);
			VCU_RELAY_ON = 0;
		}
		else
		{
			Shutdown_Process();
		}
	}

	Warn_Error_Process();
	if(ST_CHARGE)
		CHG_Warn_Error_Process();
	else
		DCHG_Warn_Error_Process();

	if(I_TOT_ACTUAL > 5 && I_TOT_ACTUAL <= 200 )				//Charge current 0.5~20A? (distinguish charging/discharging(Regen))
	{
		if(++usChgModeTimerCnt >= TMR60S_100HZ)
		{
			ST_CHARGE = 1;
			usChgModeTimerCnt = TMR60S_100HZ;
		}
		if(!AC_ON_SIG)
		{
			ST_CHARGE = 1;
			usChgModeTimerCnt = TMR60S_100HZ;
		}
	}
	else
	{
		usChgModeTimerCnt = 0;
		ST_CHARGE = 0;
	}

	if(++CAN_100ms_Count >= TMR01S_100HZ )
	{
		CAN_Send_Process();
		CAN_100ms_Count = 0;
		if(CMD_ERRLOG_CALL || CMD_ERRUP || CMD_ERRDOWN)
			ErrorDisplay();
	}

	CAN_Timeout();														//CAN Command recognize(10min timeout)
	if(!AC_ON_SIG)
	{
		ChargeProcess();
	}
	else
	{
		FULL_LED = OFF;
		ERR_LED = OFF;
		ucChargeStep = 0;
		Charge_Restart_cnt = 0;
	}

	Write_Port_Output();

	Buzzer_Output();

	PwrOff_Process();
}



/******************************************************************************/
/*          A/D Conversion                                                    */
/******************************************************************************/

void Ad_Conversion(void)

{
	uint16 i;
	uint32 ulTmp1;
	int32_t lTmp1;
	ADC_ChannelConfTypeDef sConfig = { 0 };

	sConfig.Channel = ADC_CHANNEL_10;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 0);

	ulChargeCurrAdcBuf[8] = HAL_ADC_GetValue(&hadc1);
	ulChargeCurrAdcTot -= ulChargeCurrAdcBuf[0];
	ulChargeCurrAdcTot += ulChargeCurrAdcBuf[8];
	ulChargeCurrAdcAvg = ulChargeCurrAdcTot >> 3;
	for (i = 0; i < 8; i++)
		ulChargeCurrAdcBuf[i] = ulChargeCurrAdcBuf[i + 1];

	HAL_ADC_Stop(&hadc1);

	sConfig.Channel = ADC_CHANNEL_11;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 0);

	ulDischargeCurrAdcBuf[8] = HAL_ADC_GetValue(&hadc1);
	ulDischargeCurrAdcTot -= ulDischargeCurrAdcBuf[0];
	ulDischargeCurrAdcTot += ulDischargeCurrAdcBuf[8];
	ulDischargeCurrAdcAvg = ulDischargeCurrAdcTot >> 3;
	for (i = 0; i < 8; i++)
		ulDischargeCurrAdcBuf[i] = ulDischargeCurrAdcBuf[i + 1];

	HAL_ADC_Stop(&hadc1);

	if(ulChargeCurrAdcAvg >= 15)
	{
		ulTmp1 = (uint32)(ulChargeCurrAdcAvg);
		ulTmp1 *= 33000;
		ulTmp1 /= 4095;
		lTmp1 = (uint32)(ulTmp1*200/1500);

		I_TOT_ACTUAL = (int16_t) lTmp1;
	}
	else
	{
		ulTmp1 = (uint32)(ulDischargeCurrAdcAvg);
		ulTmp1 *= 33000;
		ulTmp1 /= 4095;
		lTmp1 = (uint32)(ulTmp1*200/1500);
		if(lTmp1 <= 10)
			lTmp1 = 0;								//
		I_TOT_ACTUAL = (int16_t) (-lTmp1);
	}
/*
	ulTmp1 *= 33000;
	ulTmp1 /= 4095;
	lTmp1 = (uint32)(ulTmp1*200/1500);

	I_TOT_ACTUAL = (int16_t) lTmp1;				// 0x201 48,16,iTotalActual "Actual current of the battery pack (충전:+, 방전:-)"
	lSumAh += I_TOT_ACTUAL * 10;
*/
	if (lTmp1 > 0)
	{
		usChargeCurrent = (uint16) lTmp1;
		usDischargeCurrent = 0;
	}
	else
	{
		usChargeCurrent = 0;
		usDischargeCurrent = (uint16) (-lTmp1);
	}

}
/******************************************************************************/
/*          LTC6811-1 cell data read                                          */
/******************************************************************************/
void Read_CellData(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, ON);	//LTC 6820 ON
	uint8 n, i, j;
	uint32 ulSum = 0;
	uint16 usMax = 0, usMin = 0xffff;
	wakeup_idle();

	LTC6811_rdcv(0, bms_ic);
	LTC6811_rdaux(2, bms_ic);

	/******** Cell Voltage Read / Calculate Sum & Average *************************/
	for (n = 0; n < TOTAL_IC; n++)
	{
		for (i = 0; i < bms_ic[0].ic_reg.cell_channels; i++)
		{
			if (bms_ic[n].cells.c_codes[i] == 0xffff)
				usCellVolBuf[n][i][8] = 0;
			else
				usCellVolBuf[n][i][8] = bms_ic[n].cells.c_codes[i];
			ulCellVolTot[n][i] -= usCellVolBuf[n][i][0];
			ulCellVolTot[n][i] += usCellVolBuf[n][i][8];
			usCellVolAvg[n][i] = (uint16) (ulCellVolTot[n][i] >> 3);

			for (j = 0; j < 8; j++)
				usCellVolBuf[n][i][j] = usCellVolBuf[n][i][j + 1];

			ulSum += usCellVolAvg[n][i];

			if (usCellVolAvg[n][i] > usMax)
				usMax = usCellVolAvg[n][i];

			if (usCellVolAvg[n][i] < usMin)
				usMin = usCellVolAvg[n][i];
		}
	}

	if (usMin == 0xffff)
		usMin = 0;

	ulSum_Vol = ulSum / 10;          							// divide by 10 to change mV scale
	CELL_V_HIGH = usMax / 10;									// 0x206 0,16,vHighCell "Highest voltage among battery cells"
	CELL_V_LOW = usMin / 10;          							// 0x206 16,16,vLowCell "Lowest voltage among battery cells"
	CELL_V_AVG = (uint16) (ulSum / TOT_CELLS) / 10;			// 0x206 32,16,vAverageCell "Average voltage of battery cells"
	CELL_V_DEVI = (usMax - usMin) / 10;  						// 0x206 48,16,vDeviationCell "Deviation voltage of battery cells"
	V_TOT_ACTUAL = (int16_t) (ulSum_Vol / 100);					// 0x201 32,16,vTotalActual "Actual voltage of the battery pack"

	LTC6811_adcvax(ADC_CONVERSION_MODE, ADC_DCP);				// AD Conversion Start for all cells & temp sensors

}
/******************************************************************************/
/*          LTC6811-1 temp data read                                          */
/******************************************************************************/
void Read_TempData(void)
{
	int16_t sTemp;
	wakeup_idle();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, OFF); //LTC 6820 power enable
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, ON);
	LTC6811_adcvax(ADC_CONVERSION_MODE, ADC_DCP);
	LTC6811_adax(ADC_CONVERSION_MODE, 5);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, OFF);
	usCellTempBuf[0][0][4] = bms_ic[0].aux.a_codes[4];			//LTC6811 GPIO5
	if(usCellTempBuf[0][0][0]==0)
	{
		sTemp = Vol2Temp(usCellTempBuf[0][0][4]);
	}
	else
	{
		sTemp = Vol2Temp(usCellTempAvg[0][0]);
	}
	ulCellTempTot[0][0] -= usCellTempBuf[0][0][0];
	ulCellTempTot[0][0] += usCellTempBuf[0][0][4];
	usCellTempAvg[0][0] = (uint16) (ulCellTempTot[0][0] >> 2);

	for (sint32 j = 0; j < 4; j++)
		usCellTempBuf[0][0][j] = usCellTempBuf[0][0][j + 1];

	CELL_T_HIGH = sTemp;											// 0x207 0,16,tHighPlace "Highest temperature among battery cells"
	CELL_T_LOW = sTemp;											// 0x207 16,16,tLowPlace "Lowest temperature among battery cells"
	CELL_T_AVG = sTemp;											// 0x207 32,16,tAveragePlace "Average temperature of battery cells"
	CELL_T_DEVI = 0;
}
//////////////////////////////////////////////////////////////////////////////
//		Cell Balancing
//////////////////////////////////////////////////////////////////////////////
void Cell_Balancing(void)
{
	ST_CB = F_CB; //signal can display

	if(++usCellBalanceCnt == TMR10S_1HZ)						//밸런싱 중에 셀 전압 센싱이 낮게 나오기 때문에 밸런싱off후 밸런싱 대상 선정 필요
	{
		usCellBalanceCnt = 0;
		for (sint32 n=0; n<TOTAL_IC; n++)
		{
			bms_ic[TOTAL_IC-n-1].configa.tx_data[4]  = 0;
			bms_ic[TOTAL_IC-n-1].configa.tx_data[5] &= 0xf0;
		}
		wakeup_sleep();
		LTC6811_wrcfg(bms_ic);
	}
	if(V_TOT_ACTUAL > 650)
	{
		if (usDischargeCurrent < 15) 								// balancing only not discharging
		{
			if (CELL_V_DEVI > BALANCE_RANGE)
			{
				F_CB = 1;
			}

		}
		else
			F_CB = 0;
	}
	else
		F_CB = 0;

	if(F_CB)
	{
		for (sint32 n=0; n<TOTAL_IC; n++)
		{
			for (sint32 i=0; i<bms_ic[n].ic_reg.cell_channels; i++)
			{

				if (bms_ic[n].cells.c_codes[i] > CELL_V_HIGH * 10 - 10)
				{
					if (i<8)
					{
						bms_ic[TOTAL_IC-n-1].configa.tx_data[4] |= 1<<(i);
					}
					else
					{
						bms_ic[TOTAL_IC-n-1].configa.tx_data[5] |= 1<<(i-8);
					}
				}
			}
		}
		wakeup_sleep();
		LTC6811_wrcfg(bms_ic);
		if(CELL_V_DEVI < Balancing_Hysteresis)
		{
			F_CB = 0;
			for (sint32 n=0; n<TOTAL_IC; n++)
			{
				bms_ic[TOTAL_IC-n-1].configa.tx_data[4]  = 0;
				bms_ic[TOTAL_IC-n-1].configa.tx_data[5] &= 0xf0;
			}
		}
	}
}


void CAN_Celldata_Assign(void)
{

	switch(DataAssign_step)
	{
	case 0 :
		//0x517
		CELLT_1 = Vol2Temp(usCellTempAvg[0][0]) * 10;
		CELLT_2 = Vol2Temp(usCellTempAvg[0][1]) * 10;
		DataAssign_step++;
		CAN_Tx_Process(0x30A, un517_TxData.BY);
		break;
	case 1 :
		//0x511
		CELLV_01 = usCellVolAvg[0][0];
		CELLV_02 = usCellVolAvg[0][1];
		CELLV_03 = usCellVolAvg[0][2];
		CELLV_04 = usCellVolAvg[0][3];
		DataAssign_step++;
		CAN_Tx_Process(0x30B, un511_TxData.BY);
		if(CELL_COUNT==4 && TOTAL_IC==1)
		{
			DataAssign_step = 0;
		}
		break;
	case 2 :
		//0x512
		CELLV_05 = usCellVolAvg[0][4];
		CELLV_06 = usCellVolAvg[0][5];
		CELLV_07 = usCellVolAvg[0][6];
		CELLV_08 = usCellVolAvg[0][7];
		DataAssign_step++;
		if(CELL_COUNT==7 && TOTAL_IC==1)
		{
			DataAssign_step = 0;
			CELLV_08 = 0;
		}
		if(CELL_COUNT==7 && TOTAL_IC==2)
		{
			CELLV_08 = 0;
		}
		CAN_Tx_Process(0x30C, un512_TxData.BY);
		break;
	case 3 :
		//0x513
		CELLV_09 = usCellVolAvg[0][8];
		CELLV_10 = usCellVolAvg[0][9];
		CELLV_11 = usCellVolAvg[1][0];
		CELLV_12 = usCellVolAvg[1][1];
		DataAssign_step++;
		if(CELL_COUNT==7 && TOTAL_IC==2)
		{

			CELLV_09 = 0;
			CELLV_10 = 0;
		}
		CAN_Tx_Process(0x30D, un513_TxData.BY);
		break;
	case 4 :
		//0x514
		CELLV_13 = usCellVolAvg[1][2];
		CELLV_14 = usCellVolAvg[1][3];
		CELLV_15 = usCellVolAvg[1][4];
		CELLV_16 = usCellVolAvg[1][5];
		DataAssign_step++;
		CAN_Tx_Process(0x30E, un514_TxData.BY);
		break;
	case 5 :
		//0x515
		CELLV_17 = usCellVolAvg[1][6];
		CELLV_18 = usCellVolAvg[1][7];
		CELLV_19 = usCellVolAvg[1][8];
		CELLV_20 = usCellVolAvg[1][9];
		DataAssign_step++;
		if(CELL_COUNT==7 && TOTAL_IC==2)
		{
			CELLV_18 = 0;
			CELLV_19 = 0;
			CELLV_20 = 0;
		}
		CAN_Tx_Process(0x30F, un515_TxData.BY);
		break;
	case 6 :

		CELLT_3 = Vol2Temp(usCellTempAvg[1][0]) * 10;
		CELLT_4 = Vol2Temp(usCellTempAvg[1][1]) * 10;

		DataAssign_step++;

		break;
	default :
		DataAssign_step = 0;
		break;
	}

}


void CAN_Send_Process(void)
{
	CAN_Tx_Process(CAN_BASE + 1, un201_TxData.BY);
	switch (ucCanTxTimer)
	{
	case 0:
		CAN_Tx_Process(CAN_BASE, un200_TxData.BY);
		++ucCanTxTimer;

		break;

	case 1:
	               //for BMS 1,2,3
		++ucCanTxTimer;
		break;

	case 2:

		++ucCanTxTimer;
		break;

	case 3:
		CAN_Tx_Process(CAN_BASE + 5, un205_TxData.BY);
		++ucCanTxTimer;
		break;

	case 4:
		CAN_Tx_Process(CAN_BASE + 6, un206_TxData.BY);
		++ucCanTxTimer;
		break;

	case 5:
		CAN_Tx_Process(CAN_BASE + 7, un207_TxData.BY);
		++ucCanTxTimer;
		break;

	case 6:

		++ucCanTxTimer;
		break;

	case 7:

		++ucCanTxTimer;
		break;

	case 8:
		++ucCanTxTimer;
		break;

	case 9:
		++ucCanTxTimer;

		break;

	default:
		break;
	}

	if (ucCanTxTimer > 9)
		ucCanTxTimer = 0;

}

void CAN_Tx_Process(uint16 id, uint8 data[8])
{
	uint8 i;

	TxHeader.StdId = id;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;

	for (i = 0; i < 8; i++)
	{
		ucTxData[i] = data[i];
	}

	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, ucTxData, &unTxMailbox) != HAL_OK)
	{
		uint32 errorcode = hcan.ErrorCode;
		if(errorcode == HAL_CAN_ERROR_NOT_INITIALIZED)
			HAL_CAN_Init(&hcan);
	}
}

void CAN_Timeout(void)
{
	if(++usVCU_RelayCommandCnt == TMR2MIN_100HZ)
	{
		usVCU_RelayCommandCnt = 0;
		ucVCU_RelayCommandBuf[5] = VCU_RelayCommandFlag;
		for (sint32 v = 0; v < 5; v++)
		{
			ucVCU_RelayCommandBuf[v] = ucVCU_RelayCommandBuf[v + 1];
		}
		VCU_RelayCommandFlag = 0;
		if(!ucVCU_RelayCommandBuf[0]
		&& !ucVCU_RelayCommandBuf[1]
		&& !ucVCU_RelayCommandBuf[2]
		&& !ucVCU_RelayCommandBuf[3]
		&& !ucVCU_RelayCommandBuf[4]
	    && !ucVCU_RelayCommandBuf[5])
		{
			VCU_RELAY_ON = OFF;
		}
	}
}

void Shutdown_Process(void)
{
	HEATER_M = OFF;
	HEATER_P = OFF;
	CHARGE_M = OFF;
	CHARGE_P = OFF;
	DISCHARGE_M = OFF;
	DISCHARGE_P = OFF;
}

void PwrOff_Process(void)
{
	if(ST_PWRSW == 0)												//apply data save logic later
	{
		if(++ucPWRoffSWCnt == TMR1S_100HZ)
		{

			F_OFF = 1;
		}
	}
	else
		ucPWRoffSWCnt = 0;

	if(I_TOT_ACTUAL > -15 &&  I_TOT_ACTUAL < 1)
	{
		if(++SleepMode_count >= 360000 * 24 * 7)						//1hour * 24 * 7= 7day
		{
			F_OFF = 1;
		}
		if(V_TOT_ACTUAL <= 650)
		{
			if(SleepMode_count > 360000 * 3)
				F_OFF = 1;
		}
	}
	else
		SleepMode_count = 0;
}

void Relays_Control(boolean cmd)
{
	CHARGE_P = cmd;
	DISCHARGE_P = cmd;
	HEATER_P = cmd;
}

void Calculate_SOC(void)
{
	lRemAsec += lSumAh / 100;
//	usSocAh = (uint16) (lRemAsec / 36 / (uint16)AMPERE_HOUR);
	lSumAh = 0;

	SOC = Get_OCV_SOC(CELL_V_AVG);//vol);  										// SOC is 0.1% scale, Vol is mV scale
	REM_AH = (uint32) SOC * (uint16)AMPERE_HOUR / 100;					// 0.01Ah scale
	REM_WH = 4976*SOC/1000;
			//(uint32) REM_AH * ulSum_Vol / 1000;
}

void SOC_LED_Process(void)
{
	if (F_SOCLED)
		SetSOC_LED(SOC);
	else
		SetSOC_LED(0);
}

/******************** port_output ********************/

void Buzzer_Output(void)
{
	if(ERR_FAULTFLAG)
	{
		switch (BUZZER)
		{
		case 0:
			if(++ucBuzzer_Count == TMR03S_100HZ)
			{
				ucBuzzer_Count = 0;
				BUZZER = ON;
			}
			break;
		case 1:
			if(++ucBuzzer_Count == TMR07S_100HZ)
			{
				ucBuzzer_Count = 0;
				BUZZER = OFF;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		ucBuzzer_Count = 0;
		BUZZER = OFF;
	}

}

void AC_ON_LED_Output(void)
{
	if((V_TOT_ACTUAL >= 750) && I_TOT_ACTUAL <= 10)
	{
		ERR_LED = ON;
	}
	else
	{
		switch (ERR_LED)
		{
		case 0:
			if(++ucChgLED_Count == TMR1S_100HZ)
			{
				ucChgLED_Count = 0;
				ERR_LED = ON;
			}
			break;
		case 1:
			if(++ucChgLED_Count == TMR1S_100HZ)
			{
				ucChgLED_Count = 0;
				ERR_LED = OFF;
			}
			break;

		default:
			break;
		}
	}
	if((V_TOT_ACTUAL < 750) && I_TOT_ACTUAL <= 10)
	{
		FULL_LED = ON;								//charge error led on
	}
	else
		FULL_LED = OFF;
}

int16_t Vol2Temp(uint16 vol)
{
	uint32 uwTmp;
	int16_t temp, t;

	uwTmp = (uint32) vol * 100;

	if (uwTmp < 211818)          						// over 110 degree C
		temp = 9999;
	else if (uwTmp > 2920446) 							// under -50 degree C
		temp = -9999;
	else
	{
		for (t = 0; t < 161; t++)
		{
			if (uwTmp >= ulTemp_Vol[t])
			{
				temp = (t - 50) * 10;
				t = (int16_t) ((uwTmp - ulTemp_Vol[t]) * 10 / (ulTemp_Vol[t - 1] - ulTemp_Vol[t]));
				temp -= t;
				break;
			}
		}
	}

	return temp; 										// 0.1 degree C scale
}

int16_t Vol2Temp_5k(uint16 vol)
{
	int16_t temp, t;

	if (vol < usTemp_Vol_5k[160])		 				// over 110 degree C
		temp = 9999;

	else if (vol > usTemp_Vol_5k[0]) 					// under -50 degree C
		temp = -9999;
	else
	{
		for (t = 0; t < 161; t++)
		{
			if (vol >= usTemp_Vol_5k[t])
			{
				temp = (int16_t) (t - 50) * 10;
				t = ((vol - usTemp_Vol_5k[t]) * 10) / (usTemp_Vol_5k[t - 1] - usTemp_Vol_5k[t]);
				temp -= t;
				break;
			}
		}
	}

	return temp; 												// 0.1 degree C scale
}

uint16 Get_OCV_SOC(uint16 vol)
{
	uint16 s, soc;

	if (vol <= usOCV[0])
		return 0;

	if (vol >= usOCV[100])
		return 1000;

	for (s = 0; s < 101; s++)
	{
		if (vol <= usOCV[s])
			break;
	}
	soc = s * 10;
	soc -= (usOCV[s] - vol) * 10 / (usOCV[s] - usOCV[s - 1]);

	return soc;        											// 0.1% scale
}
/*
void SetSOC_LED(uint16 soc)
{
	if (soc < 700)        										// under 70%
	{
		SOC_LED&= 0x81;
	}
	else if (soc < 800)   										// over 70%
	{
		SOC_LED &= 0x81;
		SOC_LED |= 0x02;
	}
	else if (soc < 900)   										// over 80%
	{
		SOC_LED &= 0x81;
		SOC_LED |= 0x06;
	}
	else if (soc < 950)   // over 90%
	{
		SOC_LED &= 0x81;
		SOC_LED |= 0x0e;
	}
	else if (soc < 1000)  // over 95%
	{
		SOC_LED &= 0x81;
		SOC_LED |= 0x1e;
	}
	else                  // over 100%
	{
		SOC_LED &= 0x81;
		SOC_LED |= 0x3e;
	}
}
*/


/******************** SPI ********************/

uint8 spi_read_byte(uint8 data)
{
	uint8 r_data[10] = { 0 };

	if (HAL_SPI_Receive(&hspi2, r_data, 1, 10) != HAL_OK)
	{
		ErrorHandler(17);
	}

	return r_data[0];
}

void spi_write_array(uint8 cnt, uint8 data[])
{
	if (HAL_SPI_Transmit(&hspi2, data, cnt, 10) != HAL_OK)
	{
		ErrorHandler(18);
	}
}

void spi_write_read(uint8 w_cnt, uint8 w_data[], uint8 r_cnt, uint8 r_data[])
{
	if (HAL_SPI_Transmit(&hspi2, w_data, w_cnt, 10) != HAL_OK)
	{
		ErrorHandler(19);
	}

	if (HAL_SPI_Receive(&hspi2, r_data, r_cnt, 10) != HAL_OK)
	{
		ErrorHandler(20);
	}
}

void SPI2_CS(uint8 OnOff)				//for LTC6820 wake up -	PB12(STM32F103RCT)
{
	if (OnOff)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);       // On
		else
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);         // Off
}

void Uart1Transmit(char *str)
{
	HAL_UART_Transmit(&huart1, (uint8*) str, strlen(str), 10);
}

void Uart1Receive(void)
{
	if (HAL_UART_Receive_IT(&huart1, (uint8*) ucpUartRx1Buf, sizeof(ucpUartRx1Buf)) != HAL_OK)
	{
		ErrorHandler(21);
	}
}

void ErrorHandler(char code)
{
	if (C_DEBUG)
	{
		char str[80];
		sprintf(str, "ErrorHandler : %d\r\n", code);
		Uart1Transmit(str);
	}
}
