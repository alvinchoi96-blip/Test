/*
 * SettingMode.h
 *
 *  Created on: 2022. 2. 17.
 *      Author: 82107
 */

#ifndef INC_SETTINGMODE_H_
#define INC_SETTINGMODE_H_
#include "main.h"
#include <stdbool.h>
#ifdef ROOT
#define EXT
#else
#define EXT extern
#endif
void WriteToFlash(void);                        						// Write the limit values to the internal flash memory
void ReadFromFlash(void);                       						// Read the limit values from the internal flash memory
void ValueAssign(void);
void TimeUpdate(void);
uint8_t DECtoBCD(uint8_t);
uint8_t BCDtoDEC(uint8_t);
/* Setting mode  -----------------------------------------------*/
EXT bool SettingmodeFlag;
EXT bool SavemodeFlag;

//Time variables******************************************

EXT RTC_DateTypeDef DateToUpdate;
EXT RTC_TimeTypeDef sTime;
EXT uint8_t usTimeUpdateTmr;

//Flash data saving sequence variables******************************************
EXT uint8_t flash_ststus;
EXT uint8_t flash_cmd[5];

//error logging variables******************************************
EXT uint8_t ErrBuffer[2];
EXT uint16_t ulErrlogTmr;
void Errorlog(void);
void ErrValueAssign(void);
void ErrorDisplay(void);
/*****************************************************************
 * ******************PC Command************************************
******************************************************************/
EXT union BMSSettingMode			//enter setting mode when 0x0F0F received
{
	uint8_t BY[2];
	struct
	{	//0byte Switch On/Off forcibly
		uint8_t Highbyte;
		uint8_t Lowbyte;
	} B;
}unSettingModeRx;

EXT union BMSSaveMode			//Save data into EEProm when 0xF0F0 received
{
	uint8_t BY[2];
	struct
	{	//0byte Switch On/Off forcibly
		uint8_t Highbyte;
		uint8_t Lowbyte;
	} B;
} unSaveCMDRx;

#define	CMD_CHG_RELAY				unSettingBit.B.ChargeRelay
#define	CMD_DISCHG_RELAY 			unSettingBit.B.DischargeRelay
#define	CMD_BUZZER		 			unSettingBit.B.Buzzer
#define	CMD_CELLBAL					unSettingBit.B.CellBalance
#define	CMD_ERRLOG_CALL				unSettingBit.B.ErrorlogCall
#define	CMD_SET_DEFAULT				unSettingBit.B.SetDefault
#define	FB_SAVE_COMPLETE			unSettingBit.B.SaveCompleteFB


EXT union BMSsetting_databit														//BMS Setting bit RX. also send as feedback ID 0x3FA
{																	//0x3F2
	uint8_t BY[8];
	struct
	{	//0byte Switch On/Off forcibly
		uint8_t ChargeRelay :1;
		uint8_t DischargeRelay :1;
		uint8_t Buzzer :1;
		uint8_t CellBalance :1;
		uint8_t Reserved1 : 4;

		//1byte
		uint8_t ChargeCutLevel :1;
		uint8_t ChargeReleaseLevel :1;
		uint8_t DischargeCutLevel :1;
		uint8_t DischargeReleaseLevel :1;
		uint8_t HighTempCutLevel :1;
		uint8_t HighTempReleaseLevel :1;
		uint8_t LowTempCutLevel :1;
		uint8_t LowTempReleaseLevel :1;

		//2byte
		uint8_t ChargeCurrentCutLevel :1;
		uint8_t DischargeCurrentCutLevel :1;
		uint8_t IBPLevel :1;
		uint8_t IBPReleaseLevel :1;
		uint8_t CellBalanceStartIBPLevel :1;
		uint8_t CellBalanceTargetIBPLevel :1;
		uint8_t Reserved2 :2;

		//3byte		date,time
		uint8_t Year :1;
		uint8_t Month :1;
		uint8_t Day :1;
		uint8_t Time :1;
		uint8_t Minute :1;
		uint8_t Reserved3 :3;

		//4byte		Battery spec
		uint8_t Serial :1;
		uint8_t Parellel :1;
		uint8_t CellType :1;
		uint8_t Capacity_pack :1;
		uint8_t Cycle :1;
		uint8_t Reserved4 :3;

		//5byte		Error log call command
		uint8_t ErrorlogCall :1;
		uint8_t Reserved5 :7;


		//6byte		default value setting command(erase all user custom)
		uint8_t SetDefault :1;
		uint8_t Reserved6 :6;
		uint8_t SaveCompleteFB :1;

		//mode enabled feedback
		uint8_t Reserved7 :7;
		uint8_t ModeFeedback :1;
	} B;
} unSettingBit;
#define	CMD_UP						unSettingUpDown.B.Up
#define	CMD_DOWN					unSettingUpDown.B.Down
#define	CMD_ERRUP					unSettingUpDown.B.Up_err
#define	CMD_ERRDOWN					unSettingUpDown.B.Down_err
EXT union SettingUpDown				//0x3F3
{
	uint8_t BY[2];
	struct
	{
		uint8_t Up :1;
		uint8_t Reserved1 :3;
		uint8_t Up_err :1;
		uint8_t Reserved2 :3;

		uint8_t Down :1;
		uint8_t Reserved3 :3;
		uint8_t Down_err :1;
		uint8_t Reserved4 :3;
	} B;
} unSettingUpDown;

/*****************************************************************
 * ******************BMS_Feedback*********************************
******************************************************************/
#define	FB_VOLTAGE					un3FBValueFeedback.B.Voltage
#define	FB_TEMP						un3FBValueFeedback.B.Temp
#define	FB_CURRENT					un3FBValueFeedback.B.Current
#define	FB_CAPACITY					un3FBValueFeedback.B.Capacity
EXT union ValueFeedback1
{
	uint8_t BY[8];
	struct
	{
		uint16_t Voltage;
		uint16_t Temp;
		uint16_t Current;
		uint16_t Capacity;
	} B;
} un3FBValueFeedback;

#define	FB_CYCLE				un3FCValueFeedback.B.Cycle
#define	FB_S					un3FCValueFeedback.B.S
#define	FB_YEAR					un3FCValueFeedback.B.Year
#define	FB_MONTH				un3FCValueFeedback.B.Month
#define	FB_DATE					un3FCValueFeedback.B.Date
#define	FB_HOUR					un3FCValueFeedback.B.Hour
#define	FB_MINUTE				un3FCValueFeedback.B.Minute
EXT union ValueFeedback2
{
	uint8_t BY[8];
	struct
	{
		uint16_t Cycle;
		uint8_t S;
		uint8_t Year;
		uint8_t Month;
		uint8_t Date;
		uint8_t Hour;
		uint8_t Minute;
	} B;
} un3FCValueFeedback;

#define ERRDISP_INDEX			un3FD_ErrDisplay1.B.ErrDispIndex
EXT union ValueFeedback3
{
	uint8_t BY[8];
	struct
	{
		uint8_t ErrOverVoltage : 1;
		uint8_t ErrUnderVoltage : 1;
		uint8_t ErrChargeTemp : 1;
		uint8_t ErrDischargeTemp : 1;
		uint8_t ErrOverIBP : 1;
		uint8_t ErrChargeCurrent : 1;
		uint8_t ErrDischargeCurrent : 1;
		uint8_t ChargeStatusbit : 1;

		uint8_t Reserved1;

		uint8_t Month;
		uint8_t Date;
		uint8_t Hour;
		uint8_t Minute;

		uint8_t ErrDispIndex;
	} B;
} un3FD_ErrDisplay1;

EXT union ValueFeedback4
{
	uint8_t BY[8];
	struct
	{
		uint16_t Voltage;
		uint16_t Dev;
		int16_t Temp;
		int16_t Current;
	} B;
} un3FE_ErrDisplay2;
#endif /* INC_SETTINGMODE_H_ */
