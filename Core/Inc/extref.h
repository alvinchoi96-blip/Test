/*
 * extref.h
 *
 *  Created on: Jul 1, 2020
 *      Author: user
 */

#ifndef INC_EXTREF_H_
#define INC_EXTREF_H_

#ifdef ROOT
#define EXT
#else
#define EXT extern
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include <Spec_define.h>
#include "LTC6811.h"
#include "candb.h"
#include <EEProm_data.h>

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern CAN_HandleTypeDef hcan;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern UART_HandleTypeDef huart1;
extern RTC_HandleTypeDef hrtc;
/* Flags -----------------------------------------------*/
#define F_T05MS			unT_Flags.B.t05ms
#define F_T10MS			unT_Flags.B.t10ms
#define F_MON			unT_Flags.B.Monitor
#define F_SOCLED		unT_Flags.B.SocLed
#define F_CHARGING		unT_Flags.B.Charging
#define F_KEYOFF		unT_Flags.B.KeyOff
#define F_CB			unT_Flags.B.CellBalance

EXT volatile union T_Flags
{
	uint8 BY;
	struct
	{
		uint8 t05ms :1;
		uint8 t10ms :1;
		uint8 Monitor :1;
		uint8 SocLed :1;
		uint8 Charging :1;
		uint8 KeyOff :1;
		uint8 CellBalance :1;
		uint8 PwrOff :1;
	} B;
} unT_Flags;

#define F_OFF			ucPwrOffFlag

EXT uint8 ucPwrOffFlag;

/* GPIO Input Ports -----------------------------------------------*/
#define POWER_ON			unInputPort.B.Power_On
#define POWER_ENABLE		unInputPort.B.Power_Enalbe
#define AC_ON_SIG			unInputPort.B.AC_On_Signal
#define KEY_ON_SIG			unInputPort.B.Key_On_Signal

EXT volatile union InputPort
{
	uint8 BY;
	struct
	{
		uint8 Power_On :1;
		uint8 Power_Enalbe :1;
		uint8 AC_On_Signal :1;
		uint8 Key_On_Signal :1;
		uint8 Reserved :4;
	} B;
} unInputPort;

EXT uint8 ucChtPower_On;
EXT uint8 ucChtPower_Enalbe;
EXT uint8 ucChtAC_On_Signal;
EXT uint8 ucChtKey_On_Signal;

/* GPIO OutPut Ports -----------------------------------------------*/
#define	SPI_EN 					unOutPutPort.B.SPI_Enable
#define	ERR_LED					unOutPutPort.B.Error_LED
#define	FULL_LED				unOutPutPort.B.Full_LED
#define	ERR_BUZZ				unOutPutPort.B.Error_Buzzer
#define	BUZZER					unOutPutPort.B.Buzzer_Out
#define	BUZZER_UVERR			unOutPutPort.B.Buzzer_UVerr
#define	HEATER_M				unOutPutPort.B.Heater_Minus
#define	HEATER_P				unOutPutPort.B.Heater_Plus
#define	CHARGE_M				unOutPutPort.B.Charger_Minus
#define	CHARGE_P				unOutPutPort.B.Charger_Plus
#define	DISCHARGE_M				unOutPutPort.B.Discharge_Minus
#define	DISCHARGE_P				unOutPutPort.B.Discharge_Plus
#define	BAT_20p					unOutPutPort.B.Batt_20p
#define	BAT_40p					unOutPutPort.B.Batt_40p
#define	BAT_60p					unOutPutPort.B.Batt_60p
#define	BAT_80p					unOutPutPort.B.Batt_80p
#define	BAT_100p				unOutPutPort.B.Batt_100p

EXT union OutPutPort
{
	uint8 BY[3];

	struct
	{
		uint8 SPI_Enable:1;							//LTC6820 enable
		uint8 Error_LED :1;
		uint8 Full_LED :1;
		uint8 Error_Buzzer :1;
		uint8 Buzzer_Out :1;
		uint8 Buzzer_UVerr :1;

		uint8 Reserved1 :2;

		uint8 Heater_Minus :1;
		uint8 Heater_Plus :1;
		uint8 Charger_Minus :1;
		uint8 Charger_Plus :1;
		uint8 Discharge_Minus :1;
		uint8 Discharge_Plus :1;
		uint8 Reserved2 :2;

		uint8 Batt_20p :1;
		uint8 Batt_40p :1;
		uint8 Batt_60p :1;
		uint8 Batt_80p :1;
		uint8 Batt_100p :1;
		uint8 Reserved3 :3;

	} B;
} unOutPutPort;

/* Timers -----------------------------------------------*/
#define TMR30MS_100HZ		3									// 0.03 sec/100HZ
#define TMR50MS_100HZ		5									// 0.05 sec/100HZ
#define TMR01S_100HZ		10									// 0.1 sec/100HZ
#define TMR02S_100HZ		(TMR01S_100HZ * 2)					// 0.2 sec/100HZ
#define TMR03S_100HZ		(TMR01S_100HZ * 3)					// 0.3 sec/100HZ
#define TMR04S_100HZ		(TMR01S_100HZ * 4)					// 0.4 sec/100HZ
#define TMR05S_100HZ		(TMR01S_100HZ * 5)					// 0.5 sec/100HZ
#define TMR07S_100HZ		(TMR01S_100HZ * 7)					// 0.5 sec/100HZ
#define TMR1S_100HZ			(TMR01S_100HZ * 10)					//  1 sec/100HZ
#define TMR1R3S_100HZ		(TMR1S_100HZ + TMR03S_100HZ)		// 1.3 sec/100HZ
#define TMR1R6S_100HZ		(TMR1R3S_100HZ + TMR03S_100HZ)		// 1.6 sec/100HZ
#define TMR2S_100HZ			(TMR1S_100HZ * 2)					//  2 sec/100HZ
#define TMR3S_100HZ			(TMR1S_100HZ * 3)					//  3 sec/100HZ
#define TMR4S_100HZ			(TMR1S_100HZ * 4)					//  4 sec/100HZ
#define TMR7S_100HZ			(TMR1S_100HZ * 7)					//  7 sec/100HZ
#define TMR10S_100HZ		(TMR1S_100HZ * 10)					// 10 sec/100HZ
#define TMR20S_100HZ		(TMR1S_100HZ * 20)					// 20 sec/100HZ
#define TMR30S_100HZ		(TMR1S_100HZ * 30)					// 30 sec/100HZ
#define TMR60S_100HZ		(TMR1S_100HZ * 60)					// 60 sec/100HZ
#define TMR2MIN_100HZ		(TMR60S_100HZ * 2)					// 60 sec/100HZ
#define TMR5MIN_100HZ		(TMR60S_100HZ * 5)					// 60 sec/100HZ


#define TMR10S_1HZ			10									// 10sec/1HZ
#define TMR12S_1HZ			12									// 10sec/1HZ
#define TMR10M_1HZ			600
#define TMR30M_1HZ			1800								// 30 min/1HZ
#define TMR1H_1HZ			3600								// 1hour/1HZ

EXT uint8 ucLTC_WAIT_Count;
EXT uint8 ucBuzzer_Count;
EXT uint8 ucChgLED_Count;
EXT uint16 usChargeStepTmr;
EXT uint8 Charge_Restart_cnt;
EXT uint32 SleepMode_count;

EXT uint8 ucPWRoffSWCnt;
EXT uint16 usTimeoutCnt;
EXT uint8 ucMonTimerCnt;
EXT uint8 ucSocTimerCnt;
EXT uint16 usSohTimerCnt;
EXT uint16 usChgTimeUpCnt;
EXT uint32 ulP_Interval_timer;
EXT uint16 usCellBalanceCnt;
EXT uint8 CAN_100ms_Count;
/* Warn/Error Timeout variable-------------------------------------------*/
EXT uint16 usChgModeTimerCnt;
EXT uint16 usIBPerrTmr;
EXT uint16 usDCHG_CUVPtmr;
EXT uint16 usDCHG_PIBPtmr;
EXT uint16 usDCHG_OCPtmr;
EXT uint16 usDCHG_UVPtmr;
EXT uint16 usBUZZER_UVPtmr;
EXT uint16 usErrRelease_tmr;

EXT uint16 usCHG_POVRtmr;
EXT uint16 usCHG_OVRtmr;
/* CAN Timeout variable-------------------------------------------*/
EXT uint8 ucCanTxTimer;
EXT uint32 unTxMailbox;
//0x309
EXT uint16 usVCU_RelayCommandCnt;
EXT boolean VCU_RelayCommandFlag;
EXT uint8 ucVCU_RelayCommandBuf[6];

//0x501
EXT uint8 ucChargeStartSignalCnt;
EXT uint8 ucChargeStopSignalCnt;
EXT boolean ChargeStartSignalFlag;
EXT uint8 ucChargeStartSignalBuf[6];

void CAN_Timeout(void);


/* Sequence Step Variable --------------------------------------*/
EXT uint8 CHG_LED;
EXT uint8 ucRelayStep;
EXT uint8 ucMonStep;
EXT uint8 ucChargeStep;
EXT uint8 ucChgStCode;

/* Cell ADC Buffers -----------------------------------------------*/
EXT uint16 usCellVolBuf[TOTAL_IC][12][9];
EXT uint32 ulCellVolTot[TOTAL_IC][12];
EXT uint16 usCellVolAvg[TOTAL_IC][12];
EXT uint16 usCellTempBuf[TOTAL_IC][1][5];
EXT uint32 ulCellTempTot[TOTAL_IC][1];
EXT uint16 usCellTempAvg[TOTAL_IC][1];
EXT int16_t nTemp[TOTAL_IC * 2];


/* A/D Conversion Buffers -----------------------------------------------*/
#define	ADC_VREF			usAdcVRef

EXT uint16 usAdcVRef;
EXT uint32 ulSum_Vol;											// sum of cell voltage 1mV scale
EXT int32_t lSumAh;
EXT uint16 usSocAh;
EXT int32_t lRemAsec;

EXT uint16 ulChargeCurrAdcBuf[9];
EXT uint32 ulChargeCurrAdcTot;
EXT uint32 ulChargeCurrAdcAvg;

EXT uint16 ulDischargeCurrAdcBuf[9];
EXT uint32 ulDischargeCurrAdcTot;
EXT uint32 ulDischargeCurrAdcAvg;

EXT uint16 usChargeCurrent;
EXT uint16 usDischargeCurrent;

//ADC Command Configurations
EXT uint8 ADC_OPT              ; // See LTC6811_daisy.h for Options
EXT uint8 ADC_CONVERSION_MODE  ;     // MD_7KHZ_3KHZ; //MD_26HZ_2KHZ;//MD_7KHZ_3KHZ; // See LTC6811_daisy.h for Options
EXT uint8 ADC_DCP              ;     // See LTC6811_daisy.h for Options

/* CAN Data -----------------------------------------------*/
EXT CAN_TxHeaderTypeDef TxHeader;
EXT CAN_RxHeaderTypeDef RxHeader;
EXT uint8 ucTxData[8];
EXT uint8 ucRxData[8];
EXT uint8 DataAssign_step;
EXT uint16 usTargetVoltage;
EXT uint16 usTargetCurrent;

EXT uint8 ucpUartRx1Buf[16];
/* Cell Data  -----------------------------------------------*/
EXT cell_asic bms_ic[TOTAL_IC];

/* EEPROM Data  -----------------------------------------------*/
EXT __IO uint32 ulFlashData[16];


#define PRODID			unFlashData.B.ProductId
#define CAN_BASE		unFlashData.B.CanBase
EXT union FlashData
{
	uint32 W[16];

	struct
	{
		uint32 ProductId;              		// 25: 0;
		uint32 CanBase;              		// 25: 0;

		uint32 notuse[15];              	//
	} B;
} unFlashData;

/* Private function prototypes -----------------------------------------------*/
void print_error(sint32 error);
void print_cells(uint8 datalog_en);           // Print cell voltages
void print_aux(uint8 datalog_en);             // Print cell temperature
void print_stat(void);
void print_pec(void);
void print_open(void);
void print_config(void);
void print_etc(uint8 datalog_en);
void print_settings(void);

void User_Init(void);                           						// Initialize the values and functions
void DC_Temp_Process(void);                     						// If inlet temperatur goes high, charging will be stopped
void CAN_Send_Process(void);                    						// Send the datas via CAN
void Heating_Process(void);                  							// Cell balancing, controling 3-way valve
void Warn_Error_Process(void);          								// warning and cut-off check
void DCHG_Warn_Error_Process(void);
void CHG_Warn_Error_Process(void);
void Shutdown_Process(void);                    						// Shutdown Process
void ChargeProcess(void);                      						// Common charge sequence
void Sequence_Timeout(uint8 ucChgStCode);								// timeout during charge sequence
void Relays_Control(boolean cmd);
void Relays_OFF(void);
void PwrOff_Process(void);                         						// Key On / Start / Off sequence

void Calculate_SOC(void);                       						// Calculate the SOC
void SOC_LED_Process(void);                     						// Determine Turning On or Off the LEDs of SOC
void BMS_Mode(void);													// Discharge / Charge mode - set by IGN
void Buzzer_Output(void);
void Charge_LED_Output(void);
void Write_Port_Output(void);

void Read_IGN(void);
void Ad_Conversion(void);
void Read_CellData(void);
void Read_TempData(void);
int16_t Vol2Temp(uint16 vol);         								// Calculate the voltage to temperature
sint32 Vol2Temp_10k(double vol);   										// Calculate the voltage to temperature with 10k ohm
int16_t Vol2Temp_5k(uint16 vol);              						// Calculate the voltage to temperature with 5k ohm
void Cell_Balancing(void);              								// Turn on resistance of high voltage cells
uint16 Get_OCV_SOC(uint16 vol);               						// Get SOC from OCV table
void SetSOC_LED(uint16 soc);                  						// Turn On / Off the SOC LEDs according to the SOC
void BatteryCooling(uint8 OnOff);             						// Turn the 3-way valve On / Off, turn on when over 40, turn off when under 38


//void CAN_Standby(uint8 OnOff);                						// Turn the CAN operation Normal / Standby
void Monitoring(void);
void Uart1Transmit(char *str);                  						// Send the data via RS232
void Uart1Receive(void);                        						// Receive the data via RS232
void CAN_Tx_Process(uint16 id, uint8 data[8]);                  	// Send the data via CAN physically
void CAN_Celldata_Assign(void);
void SPI2_CS(uint8 OnOff);
uint8 spi_read_byte(uint8 data);
void spi_write_array(uint8 cnt, uint8 data[]);
void spi_write_read(uint8 w_cnt, uint8 w_data[], uint8 r_cnt, uint8 r_data[]);
void ErrorHandler(char code);

//Setting mode
void SettingMode(void);
void SetDefault(void);

#define FALSE 0
#define TRUE 1

#define OFF 0
#define RECOG 1
#define CHARGING 2
#define FULL 3
#define ERR 4
#define ABORT 5
#endif /* INC_EXTREF_H_ */
