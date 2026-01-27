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
uint8 DECtoBCD(uint8);
uint8 BCDtoDEC(uint8);
/* Setting mode  -----------------------------------------------*/
EXT boolean SettingmodeFlag;
EXT boolean SavemodeFlag;

//Time variables******************************************

EXT RTC_DateTypeDef DateToUpdate;
EXT RTC_TimeTypeDef sTime;
EXT uint8 usTimeUpdateTmr;

//Flash data saving sequence variables******************************************
EXT uint8 flash_ststus;
EXT uint8 flash_cmd[5];

//error logging variables******************************************
EXT uint8 ErrBuffer[2];
EXT uint16 ulErrlogTmr;
void Errorlog(void);
void ErrValueAssign(void);
void ErrorDisplay(void);
/*****************************************************************
 * ******************PC Command************************************
******************************************************************/
EXT union BMSSettingMode			//enter setting mode when 0x0F0F received
{
	uint8 BY[2];
	struct
	{	//0byte Switch On/Off forcibly
		uint8 Highbyte;
		uint8 Lowbyte;
	} B;
}unSettingModeRx;

EXT union BMSSaveMode			//Save data into EEProm when 0xF0F0 received
{
	uint8 BY[2];
	struct
	{	//0byte Switch On/Off forcibly
		uint8 Highbyte;
		uint8 Lowbyte;
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
	uint8 BY[8];
	struct
	{	//0byte Switch On/Off forcibly
		uint8 ChargeRelay :1;
		uint8 DischargeRelay :1;
		uint8 Buzzer :1;
		uint8 CellBalance :1;
		uint8 Reserved1 : 4;

		//1byte
		uint8 ChargeCutLevel :1;
		uint8 ChargeReleaseLevel :1;
		uint8 DischargeCutLevel :1;
		uint8 DischargeReleaseLevel :1;
		uint8 HighTempCutLevel :1;
		uint8 HighTempReleaseLevel :1;
		uint8 LowTempCutLevel :1;
		uint8 LowTempReleaseLevel :1;

		//2byte
		uint8 ChargeCurrentCutLevel :1;
		uint8 DischargeCurrentCutLevel :1;
		uint8 IBPLevel :1;
		uint8 IBPReleaseLevel :1;
		uint8 CellBalanceStartIBPLevel :1;
		uint8 CellBalanceTargetIBPLevel :1;
		uint8 Reserved2 :2;

		//3byte		date,time
		uint8 Year :1;
		uint8 Month :1;
		uint8 Day :1;
		uint8 Time :1;
		uint8 Minute :1;
		uint8 Reserved3 :3;

		//4byte		Battery spec
		uint8 Serial :1;
		uint8 Parellel :1;
		uint8 CellType :1;
		uint8 Capacity_pack :1;
		uint8 Cycle :1;
		uint8 Reserved4 :3;

		//5byte		Error log call command
		uint8 ErrorlogCall :1;
		uint8 Reserved5 :7;


		//6byte		default value setting command(erase all user custom)
		uint8 SetDefault :1;
		uint8 Reserved6 :6;
		uint8 SaveCompleteFB :1;

		//mode enabled feedback
		uint8 Reserved7 :7;
		uint8 ModeFeedback :1;
	} B;
} unSettingBit;
#define	CMD_UP						unSettingUpDown.B.Up
#define	CMD_DOWN					unSettingUpDown.B.Down
#define	CMD_ERRUP					unSettingUpDown.B.Up_err
#define	CMD_ERRDOWN					unSettingUpDown.B.Down_err
EXT union SettingUpDown				//0x3F3
{
	uint8 BY[2];
	struct
	{
		uint8 Up :1;
		uint8 Reserved1 :3;
		uint8 Up_err :1;
		uint8 Reserved2 :3;

		uint8 Down :1;
		uint8 Reserved3 :3;
		uint8 Down_err :1;
		uint8 Reserved4 :3;
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
	uint8 BY[8];
	struct
	{
		uint16 Voltage;
		uint16 Temp;
		uint16 Current;
		uint16 Capacity;
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
	uint8 BY[8];
	struct
	{
		uint16 Cycle;
		uint8 S;
		uint8 Year;
		uint8 Month;
		uint8 Date;
		uint8 Hour;
		uint8 Minute;
	} B;
} un3FCValueFeedback;

#define ERRDISP_INDEX			un3FD_ErrDisplay1.B.ErrDispIndex
EXT union ValueFeedback3
{
	uint8 BY[8];
	struct
	{
		uint8 ErrOverVoltage : 1;
		uint8 ErrUnderVoltage : 1;
		uint8 ErrChargeTemp : 1;
		uint8 ErrDischargeTemp : 1;
		uint8 ErrOverIBP : 1;
		uint8 ErrChargeCurrent : 1;
		uint8 ErrDischargeCurrent : 1;
		uint8 ChargeStatusbit : 1;

		uint8 Reserved1;

		uint8 Month;
		uint8 Date;
		uint8 Hour;
		uint8 Minute;

		uint8 ErrDispIndex;
	} B;
} un3FD_ErrDisplay1;

EXT union ValueFeedback4
{
	uint8 BY[8];
	struct
	{
		uint16 Voltage;
		uint16 Dev;
		int16_t Temp;
		int16_t Current;
	} B;
} un3FE_ErrDisplay2;
#endif /* INC_SETTINGMODE_H_ */
