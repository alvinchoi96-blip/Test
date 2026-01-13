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

EXT uint16_t CELL_COUNT;
EXT uint16_t AMPERE_HOUR;
EXT uint16_t OVER_VOL_ERR;
EXT uint16_t OVER_VOL_WARN;

EXT uint16_t UNDER_VOL_WARN;
EXT uint16_t UNDER_VOL_ERR;
EXT uint16_t CHG_OVER_TEMP_ERR;
EXT uint16_t CHG_OVER_TEMP_WARN;
EXT int16_t CHG_UNDER_TEMP_WARN;
EXT int16_t CHG_UNDER_TEMP_ERR;
EXT uint16_t DSC_OVER_TEMP_ERR;
EXT uint16_t DSC_OVER_TEMP_WARN;
EXT int16_t DSC_UNDER_TEMP_WARN;
EXT int16_t DSC_UNDER_TEMP_ERR;
EXT uint16_t CHG_OVER_CURR_WARN;
EXT uint16_t CHG_OVER_CURR_ERR;
EXT uint16_t DSC_OVER_CURR_WARN;
EXT uint16_t DSC_OVER_CURR_ERR;
EXT uint16_t VOL_IBP_WARN;
EXT uint16_t VOL_IBP_ERR;
EXT uint16_t BALANCE_RANGE;
EXT uint16_t Balancing_Hysteresis;

#define ERRINDEX						unRom.B.ErrorIndex
EXT union Eeprom														// EEPROM Data
{
	uint8_t BY[1600];													// BYTE ACCESS

	struct 																// Data struct
	{
		uint16_t OverVoltageCut;
		uint16_t OverVoltageRelease;
		uint16_t UnderVoltageCut;
		uint16_t UnderVoltageRelease;

		uint16_t OverTempCut;
		uint16_t OverTempRelease;
		int16_t UnderTempCut;
		int16_t UnderTempRelease;

		uint16_t OverChargeCurrentCut;
		uint16_t OverDischargeCurrentCut;
		uint16_t IBPCut;
		uint16_t IBPRelease;

		uint16_t BalanceStartLVL;
		uint16_t BalanceTargetLVL;
		uint8_t Year;
		uint8_t Month;
		uint8_t Date;
		uint8_t Hour;

		uint8_t Minute;
		uint8_t Serial;
		uint8_t Parellel;
		uint8_t ErrorIndex;
		uint16_t Capacity;
		uint16_t Cycle;													//40byte

		struct AlmRcrd 													// Alarm Record, 14*100 = 1400+@ byte
		{
			uint8_t ErrOverVoltage : 1;
			uint8_t ErrUnderVoltage : 1;
			uint8_t ErrChargeTemp : 1;
			uint8_t ErrDischargeTemp : 1;
			uint8_t ErrOverIBP : 1;
			uint8_t ErrChargeCurrent : 1;
			uint8_t ErrDischargeCurrent : 1;
			uint8_t ChargeStatusbit : 1;

			uint8_t Year;
			uint8_t Month;
			uint8_t Date;
			uint8_t Hour;
			uint8_t Minute;
			uint16_t PackVoltage;
			uint16_t IBPLevel;
			int16_t Temp;
			int16_t Current;
		} Alm[100];
	} B;
} unRom;


#endif /* INC_EEPROM_DATA_H_ */
