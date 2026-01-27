/*
 * EEProm_data.h
 *
 *  Created on: 2022. 1. 25.
 *      Author: 82107
 */

#ifndef INC_EEPROM_DATA_H_
#define INC_EEPROM_DATA_H_

#ifdef ROOT
#define EXT
#else
#define EXT extern
#endif


/* Include system library */
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "extref.h"

EXT uint16 CELL_COUNT;
EXT uint16 AMPERE_HOUR;
EXT uint16 OVER_VOL_ERR;
EXT uint16 OVER_VOL_WARN;

EXT uint16 UNDER_VOL_WARN;
EXT uint16 UNDER_VOL_ERR;
EXT uint16 CHG_OVER_TEMP_ERR;
EXT uint16 CHG_OVER_TEMP_WARN;
EXT int16_t CHG_UNDER_TEMP_WARN;
EXT int16_t CHG_UNDER_TEMP_ERR;
EXT uint16 DSC_OVER_TEMP_ERR;
EXT uint16 DSC_OVER_TEMP_WARN;
EXT int16_t DSC_UNDER_TEMP_WARN;
EXT int16_t DSC_UNDER_TEMP_ERR;
EXT uint16 CHG_OVER_CURR_WARN;
EXT uint16 CHG_OVER_CURR_ERR;
EXT uint16 DSC_OVER_CURR_WARN;
EXT uint16 DSC_OVER_CURR_ERR;
EXT uint16 VOL_IBP_WARN;
EXT uint16 VOL_IBP_ERR;
EXT uint16 BALANCE_RANGE;
EXT uint16 Balancing_Hysteresis;

#define ERRINDEX						unRom.B.ErrorIndex
EXT union Eeprom														// EEPROM Data
{
	uint8 BY[1600];													// BYTE ACCESS

	struct 																// Data struct
	{
		uint16 OverVoltageCut;
		uint16 OverVoltageRelease;
		uint16 UnderVoltageCut;
		uint16 UnderVoltageRelease;

		uint16 OverTempCut;
		uint16 OverTempRelease;
		int16_t UnderTempCut;
		int16_t UnderTempRelease;

		uint16 OverChargeCurrentCut;
		uint16 OverDischargeCurrentCut;
		uint16 IBPCut;
		uint16 IBPRelease;

		uint16 BalanceStartLVL;
		uint16 BalanceTargetLVL;
		uint8 Year;
		uint8 Month;
		uint8 Date;
		uint8 Hour;

		uint8 Minute;
		uint8 Serial;
		uint8 Parellel;
		uint8 ErrorIndex;
		uint16 Capacity;
		uint16 Cycle;													//40byte

		struct AlmRcrd 													// Alarm Record, 14*100 = 1400+@ byte
		{
			uint8 ErrOverVoltage : 1;
			uint8 ErrUnderVoltage : 1;
			uint8 ErrChargeTemp : 1;
			uint8 ErrDischargeTemp : 1;
			uint8 ErrOverIBP : 1;
			uint8 ErrChargeCurrent : 1;
			uint8 ErrDischargeCurrent : 1;
			uint8 ChargeStatusbit : 1;

			uint8 Year;
			uint8 Month;
			uint8 Date;
			uint8 Hour;
			uint8 Minute;
			uint16 PackVoltage;
			uint16 IBPLevel;
			int16_t Temp;
			int16_t Current;
		} Alm[100];
	} B;
} unRom;


#endif /* INC_EEPROM_DATA_H_ */
