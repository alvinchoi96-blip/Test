/*
 * callback.c
 *
 *  Created on: 2020. 11.2.
 *      Author: JeongHwan
 */

#include "extref.h"
#include "candb.h"
#include "SettingMode.h"

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uint8 i;

	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, ucRxData) != HAL_OK)
	{
		uint32 errorcode = hcan->ErrorCode;
		if(errorcode == HAL_CAN_ERROR_NOT_INITIALIZED)
		{
//			HAL_CAN_Init(&hcan);
		}
	}

	switch (RxHeader.StdId)
	{
	case 0x309:
		for (i = 0; i < 2; i++)
		{
			un209_RxData.BY[i] = ucRxData[i];
			ucRxData[i] = 0;
		}
		VCU_RelayCommandFlag = ON;
		break;
	case 0x3F0:
		for (i = 0; i < 2; i++)
		{
			unSettingModeRx.BY[i] = ucRxData[i];
			ucRxData[i] = 0;
		}
		if(unSettingModeRx.BY[0] == 0x0F && unSettingModeRx.BY[1] == 0x0F)
		{
			unSettingModeRx.BY[0] = 0;
			unSettingModeRx.BY[1] = 0;
			SettingmodeFlag = ON;
		}
		break;
	case 0x3F1:
		for (i = 0; i < 2; i++)
		{
			unSaveCMDRx.BY[i] = ucRxData[i];
			ucRxData[i] = 0;
		}
		if(unSaveCMDRx.BY[0] == 0xF0 && unSaveCMDRx.BY[1] == 0xF0)
		{
			unSaveCMDRx.BY[0] = 0;
			unSaveCMDRx.BY[1] = 0;
			SavemodeFlag = ON;
		}
		break;
	case 0x3F2:
		for (i = 0; i < 8; i++)
		{
			unSettingBit.BY[i] = ucRxData[i];
			ucRxData[i] = 0;
		}
	case 0x3F3:
		for (i = 0; i < 2; i++)
		{
			unSettingUpDown.BY[i] = ucRxData[i];
			ucRxData[i] = 0;
		}

		break;
	default:
		break;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (!strncmp("debug on\r", (char*) ucpUartRx1Buf, 9))          // debug on
	{
		C_DEBUG = 1;
		C_CELL_PRINT = 0;
		C_ADC_PRINT = 0;
		C_DATA_LOG = 0;
		C_SETTING = 0;
	}
	else if (!strncmp("debug off\r", (char*) ucpUartRx1Buf, 10))   // debug off
	{
		C_DEBUG = 0;
	}
	else if (!strncmp("cellpr on\r", (char*) ucpUartRx1Buf, 10))   // cell print on
	{
		C_DEBUG = 0;
		C_CELL_PRINT = 1;
		C_ADC_PRINT = 0;
		C_DATA_LOG = 0;
		C_SETTING = 0;
	}
	else if (!strncmp("cellpr off\r", (char*) ucpUartRx1Buf, 11))  // cell print off
	{
		C_CELL_PRINT = 0;
	}
	else if (!strncmp("adcpr on\r", (char*) ucpUartRx1Buf, 9))     // ADC print on
	{
		C_DEBUG = 0;
		C_CELL_PRINT = 0;
		C_ADC_PRINT = 1;
		C_DATA_LOG = 0;
		C_SETTING = 0;
	}
	else if (!strncmp("adcpr off\r", (char*) ucpUartRx1Buf, 10))   // ADC print off
	{
		C_ADC_PRINT = 0;
	}
	else if (!strncmp("log on\r", (char*) ucpUartRx1Buf, 7))       // data log on
	{
		C_DEBUG = 0;
		C_CELL_PRINT = 0;
		C_ADC_PRINT = 0;
		C_DATA_LOG = 1;
		C_SETTING = 0;
	}
	else if (!strncmp("log off\r", (char*) ucpUartRx1Buf, 8))      // data log off
	{
		C_DATA_LOG = 0;
	}
	else if (!strncmp("relay on\r", (char*) ucpUartRx1Buf, 9))     // relay on
	{
		C_RELAYS = 2;
	}
	else if (!strncmp("relay off\r", (char*) ucpUartRx1Buf, 10))   // relay off
	{
		C_RELAYS = 1;
	}
	else if (!strncmp("heater on\r", (char*) ucpUartRx1Buf, 10))   // heater on
	{
		C_HEATER = 2;
	}
	else if (!strncmp("heater off\r", (char*) ucpUartRx1Buf, 11))  // heater off
	{
		C_HEATER = 1;
	}
	else if (!strncmp("buzzer on\r", (char*) ucpUartRx1Buf, 10))   // buzzer on
	{
		C_BUZZER = 2;
	}
	else if (!strncmp("buzzer off\r", (char*) ucpUartRx1Buf, 11))  // buzzer off
	{
		C_BUZZER = 1;
	}
	else if (!strncmp("settings rq\r", (char*) ucpUartRx1Buf, 12)) // settings request
	{
		C_DEBUG = 0;
		C_CELL_PRINT = 0;
		C_ADC_PRINT = 0;
		C_DATA_LOG = 0;
		C_SETTING = 1;
	}
	else if (!strncmp("default\r", (char*) ucpUartRx1Buf, 8))      // default state
	{
		C_DEBUG = 0;
		C_CELL_PRINT = 0;
		C_ADC_PRINT = 0;
		C_DATA_LOG = 0;
		C_RELAYS = 0;
		C_HEATER = 0;
		C_BUZZER = 0;
		C_SETTING = 0;

	}
}

