/*
 * monitor.c
 *
 *  Created on: 2020. 7. 2.
 *      Author: user
 */
#include "extref.h"
#include "candb.h"

void Monitoring(void)
{
	char str[80];

	if (ERR_ISOLATION)
	{
		Uart1Transmit("Isolation Error\r\n");
	}

	if (WRN_OVERIBP)
	{
		sprintf(str, "IBP warning:%d\r\n", CELL_V_DEVI);
		Uart1Transmit(str);
	}

	if (ERR_OVERIBP)
	{
		sprintf(str, "IBP cut-off:%d\r\n", CELL_V_DEVI);
		Uart1Transmit(str);
	}

	if (WRN_UNDERCELLV)
	{
		sprintf(str, "Low voltage warning:%d\r\n", CELL_V_LOW);
		Uart1Transmit(str);
	}

	if (ERR_UNDERCELLV)
	{
		sprintf(str, "Low voltage cut-off:%d\r\n", CELL_V_LOW);
		Uart1Transmit(str);
	}

	if (WRN_OVERCELLV)
	{
		sprintf(str, "High voltage warning:%d\r\n", CELL_V_HIGH);
		Uart1Transmit(str);
	}

	if (ERR_OVERCELLV)
	{
		sprintf(str, "High voltage cut-off:%d\r\n", CELL_V_HIGH);
		Uart1Transmit(str);
	}

	if (WRN_DISCHARGEUNDERTEMP)
	{
		sprintf(str, "Low temperature warning:%d\r\n", CELL_T_LOW);
		Uart1Transmit(str);
	}

	if (ERR_DISCHARGEUNDERTEMP)
	{
		sprintf(str, "Low temperature cut-off:%d\r\n", CELL_T_LOW);
		Uart1Transmit(str);
	}

	if (WRN_DISCHARGEOVERTEMP)
	{
		sprintf(str, "High temperature warning:%d\r\n", CELL_T_LOW);
		Uart1Transmit(str);
	}

	if (ERR_DISCHARGEOVERTEMP)
	{
		sprintf(str, "High temperature cut-off:%d\r\n", CELL_T_LOW);
		Uart1Transmit(str);
	}
	if (WRN_OVERDISCHARGE)
	{
		sprintf(str, "Over discharge warning:%ld\r\n", ulSum_Vol);
		Uart1Transmit(str);
	}

	if (ERR_OVERDISCHARGE)
	{
		sprintf(str, "Over discharge cut-off:%ld\r\n", ulSum_Vol);
		Uart1Transmit(str);
	}

	if (WRN_OVERDISCHARGECURRENT)
	{
		sprintf(str, "Over discharge current warning:%d\r\n", usDischargeCurrent);
		Uart1Transmit(str);
	}

	if (ERR_OVERDISCHARGECURRENT)
	{
		sprintf(str, "Over discharge current cut-off:%d\r\n", usDischargeCurrent);
		Uart1Transmit(str);
	}

	if (WRN_CHARGEUNDERTEMP)
	{
		sprintf(str, "Low temperature warning:%d\r\n", CELL_T_LOW);
		Uart1Transmit(str);
	}
	if (ERR_CHARGEUNDERTEMP)
	{
		sprintf(str, "Low temperature cut-off:%d\r\n", CELL_T_LOW);
		Uart1Transmit(str);
	}

	if (WRN_CHARGEOVERTEMP)
	{
		sprintf(str, "High temperature warning:%d\r\n", CELL_T_LOW);
		Uart1Transmit(str);
	}

	if (ERR_CHARGEOVERTEMP)
	{
		sprintf(str, "High temperature cut-off:%d\r\n", CELL_T_LOW);
		Uart1Transmit(str);
	}

	if (WRN_OVERCHARGECURRENT)
	{
		sprintf(str, "Over charge current warning:%d\r\n", usChargeCurrent);
		Uart1Transmit(str);
	}
	if (ERR_OVERCHARGECURRENT)
	{
		sprintf(str, "Over charge current cut-off:%d\r\n", usChargeCurrent);
		Uart1Transmit(str);
	}

	if (WRN_OVERCHARGE)
	{
		sprintf(str, "Over charge warning:%ld\r\n", ulSum_Vol);
		Uart1Transmit(str);
	}
	if (ERR_OVERCHARGE)
	{
		sprintf(str, "Over charge cut-off:%ld\r\n", ulSum_Vol);
		Uart1Transmit(str);
	}
}

void print_adc(void)
{
	if (C_ADC_PRINT)
	{
		char str[100];
//		sprintf(str, "A/D_V:%6d, CHG_A:%4d, SOC:%4d, DC_Temp1:%4d, DC_Temp2:%4d\r\n",
//				(int16_t) (ulCurrentAdcAvg * 33000 / 4095), I_TOT_ACTUAL, SOC, DC_TEMP1,
//				DC_TEMP2);
		Uart1Transmit(str);
	}
}

void print_etc(uint8_t datalog_en)
{
	if (datalog_en == 1)
	{
		char str[80];

//		sprintf(str, ",%4d,%4d,%4d,%1d,%1d,%1d,%1d,%1d,%1d", SOC, usChargeCurrent, usDischargeCurrent, CHARGE_RELAY,
//		DISCHARGE_RELAY, HEATER, KEY_ON, CHGR_ON, BUZZER);

		Uart1Transmit(str);
	}
}


/******************** LTC6811 API ********************/

void print_error(int error)
{
	char str[80];

	if (error < 0)
	{
		Uart1Transmit("Error!!!\r\n");
	}
	else
	{
		sprintf(str, "E_code = %d\r\n", error);
		Uart1Transmit(str);
	}
}

// brief Prints cell voltage codes to the serial port
void print_cells(uint8_t datalog_en)
{
	char str[256];

	if (datalog_en == 0)
	{

		if (C_CELL_PRINT == 1)
		{
			Uart1Transmit("\t");
			for (int i = 0; i < bms_ic[0].ic_reg.cell_channels; i++)
			{
				sprintf(str, "C%d     ", i + 1);
				Uart1Transmit(str);
			}
			Uart1Transmit("\r\n");

			for (int n = 0; n < TOTAL_IC; n++)
			{
				sprintf(str, " IC%d\t", n + 1);
				Uart1Transmit(str);
				for (int i = 0; i < bms_ic[0].ic_reg.cell_channels; i++)
				{
					sprintf(str, "%d, ", bms_ic[n].cells.c_codes[i]);
					Uart1Transmit(str);
				}
				Uart1Transmit("\r\n");
			}

			sprintf(str, "\tMin:%d, Avg:%d, Max:%d, Diff:%d, Sum:%ld, Num:%d, SOC:%d\r\n\r\n", CELL_V_LOW, CELL_V_AVG,
			CELL_V_HIGH, CELL_V_DEVI, ulSum_Vol, TOT_CELLS, SOC);
			Uart1Transmit(str);
		}
	}
	else
	{
		char pstr[80] = { 0, };
		char vstr[7] = { 0, };

		sprintf(pstr, "\r\n%3d", TOT_CELLS);

		for (int n = 0; n < TOTAL_IC; n++)
		{
			for (int i = 0; i < 12; i++)
			{
				sprintf(vstr, ",%5d", bms_ic[n].cells.c_codes[i]);
				strcat(pstr, vstr);
			}

			Uart1Transmit(pstr);
			memset(pstr, 0, sizeof(pstr));
		}

	}
}

// brief Prints GPIO voltage codes and Vref2 voltage code onto the serial port
void print_aux(uint8_t datalog_en)
{
	if (datalog_en == 0)
	{
		char str[256];

		if (C_CELL_PRINT == 1)
		{
			Uart1Transmit("\t");
			for (int i = 0; i < 2; i++)
			{
				sprintf(str, "T%d   ", i + 1);
				Uart1Transmit(str);
			}
			Uart1Transmit("\r\n");

			for (int n = 0; n < TOTAL_IC; n++)
			{
				sprintf(str, " IC%d\t", n + 1);
				Uart1Transmit(str);

				for (int i = 0; i < 2; i++)
				{
					sprintf(str, "%d, ", nTemp[n * 2 + i]);
					Uart1Transmit(str);
				}
				Uart1Transmit("\r\n");
			}

			sprintf(str, "\tMin:%d, Avg:%d, Max:%d, Diff:%d, Num:%d\r\n\r\n", CELL_T_LOW, CELL_T_LOW, CELL_T_HIGH,
			CELL_T_DEVI, TOT_PLACE);
			Uart1Transmit(str);
		}
	}
	else
	{
		char pstr[80] = { 0, };
		char vstr[7] = { 0, };

		sprintf(pstr, ",%2d", TOT_PLACE);

		int k = 0;
		for (int n = 0; n < TOTAL_IC; n++)
		{
			for (int i = 0; i < 2; i++)
			{
				sprintf(vstr, ",%4d", nTemp[n * 2 + i]);
				strcat(pstr, vstr);
			}

			//Uart1Transmit(pstr);
			//memset(pstr, 0, sizeof(pstr));

			if (k % 10 == 0 && k != 0)
			{
				Uart1Transmit(pstr);
				memset(pstr, 0, sizeof(pstr));
			}
			k++;
		}

		if (k < 10)
		{
			Uart1Transmit(pstr);
		}

	}
}

// brief Prints Status voltage codes and Vref2 voltage code onto the serial port
void print_stat()
{
	char str[80];

	for (int n = 0; n < TOTAL_IC; n++)
	{
		sprintf(str, " IC %d SOC:%d, Itemp:%d, VregA:%d, VregD:%d\r\n", n + 1, bms_ic[n].stat.stat_codes[0] * 20,
				bms_ic[n].stat.stat_codes[1], bms_ic[n].stat.stat_codes[2], bms_ic[n].stat.stat_codes[3]);
		Uart1Transmit(str);
	}

	Uart1Transmit("\r\n");
}

void print_pec()
{
	char str[80];

	for (int n = 0; n < TOTAL_IC; n++)
	{
		sprintf(str, "\r\n%d : PEC Errors Detected on IC%d\r\n", bms_ic[n].crc_count.pec_count, n + 1);
		Uart1Transmit(str);
	}
}

// brief Prints Open wire test results to the serial port
void print_open()
{
	char str[80];

	for (int n = 0; n < TOTAL_IC; n++)
	{
		if (bms_ic[n].system_open_wire == 0)
		{
			sprintf(str, "No Opens Detected on IC: %d\r\n", n + 1);
			Uart1Transmit(str);
		}
		else
		{
			for (int cell = 0; cell < bms_ic[0].ic_reg.cell_channels + 1; cell++)
			{
				if ((bms_ic[n].system_open_wire & (1 << cell)) > 0)
				{
					sprintf(str, "There is an open wire on IC: %d Channel: %d\r\n", n + 1, cell);
					Uart1Transmit(str);
				}
			}
		}

	}
}

// brief Prints the configuration data that is going to be written to the LTC6811 to the serial port.
void print_config()
{
	char str[80];

	Uart1Transmit("Written Configuration:\r\n");

	for (int n = 0; n < TOTAL_IC; n++)
	{
		sprintf(str, " IC %d: %d, %d, %d, %d, %d, %d, Calculated PEC: %d\r\n", n + 1, bms_ic[n].configa.tx_data[0],
				bms_ic[n].configa.tx_data[1], bms_ic[n].configa.tx_data[2], bms_ic[n].configa.tx_data[3],
				bms_ic[n].configa.tx_data[4], bms_ic[n].configa.tx_data[5], pec15_calc(6, &bms_ic[n].configa.tx_data[0]));
		Uart1Transmit(str);
	}
	Uart1Transmit("\r\n");
}

