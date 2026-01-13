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
	uint8_t BY;
	struct
	{
		uint8_t t05ms :1;
		uint8_t t10ms :1;
		uint8_t Monitor :1;
		uint8_t SocLed :1;
		uint8_t Charging :1;
		uint8_t KeyOff :1;
		uint8_t CellBalance :1;
		uint8_t PwrOff :1;
	} B;
} unT_Flags;

#define F_OFF			ucPwrOffFlag

EXT uint8_t ucPwrOffFlag;

/* GPIO Input Ports -----------------------------------------------*/
#define POWER_ON			unInputPort.B.Power_On
#define POWER_ENABLE		unInputPort.B.Power_Enalbe
#define AC_ON_SIG			unInputPort.B.AC_On_Signal
#define KEY_ON_SIG			unInputPort.B.Key_On_Signal

EXT volatile union InputPort
{
	uint8_t BY;
	struct
	{
		uint8_t Power_On :1;
		uint8_t Power_Enalbe :1;
		uint8_t AC_On_Signal :1;
		uint8_t Key_On_Signal :1;
		uint8_t Reserved :4;
	} B;
} unInputPort;

EXT uint8_t ucChtPower_On;
EXT uint8_t ucChtPower_Enalbe;
EXT uint8_t ucChtAC_On_Signal;
EXT uint8_t ucChtKey_On_Signal;

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
	uint8_t BY[3];

	struct
	{
		uint8_t SPI_Enable:1;							//LTC6820 enable
		uint8_t Error_LED :1;
		uint8_t Full_LED :1;
		uint8_t Error_Buzzer :1;
		uint8_t Buzzer_Out :1;
		uint8_t Buzzer_UVerr :1;

		uint8_t Reserved1 :2;

		uint8_t Heater_Minus :1;
		uint8_t Heater_Plus :1;
		uint8_t Charger_Minus :1;
		uint8_t Charger_Plus :1;
		uint8_t Discharge_Minus :1;
		uint8_t Discharge_Plus :1;
		uint8_t Reserved2 :2;

		uint8_t Batt_20p :1;
		uint8_t Batt_40p :1;
		uint8_t Batt_60p :1;
		uint8_t Batt_80p :1;
		uint8_t Batt_100p :1;
		uint8_t Reserved3 :3;

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

EXT uint8_t ucLTC_WAIT_Count;
EXT uint8_t ucBuzzer_Count;
EXT uint8_t ucChgLED_Count;
EXT uint16_t usChargeStepTmr;
EXT uint8_t Charge_Restart_cnt;
EXT uint32_t SleepMode_count;

EXT uint8_t ucPWRoffSWCnt;
EXT uint16_t usTimeoutCnt;
EXT uint8_t ucMonTimerCnt;
EXT uint8_t ucSocTimerCnt;
EXT uint16_t usSohTimerCnt;
EXT uint16_t usChgTimeUpCnt;
EXT uint32_t ulP_Interval_timer;
EXT uint16_t usCellBalanceCnt;
EXT uint8_t CAN_100ms_Count;
/* Warn/Error Timeout variable-------------------------------------------*/
EXT uint16_t usChgModeTimerCnt;
EXT uint16_t usIBPerrTmr;
EXT uint16_t usDCHG_CUVPtmr;
EXT uint16_t usDCHG_PIBPtmr;
EXT uint16_t usDCHG_OCPtmr;
EXT uint16_t usDCHG_UVPtmr;
EXT uint16_t usBUZZER_UVPtmr;
EXT uint16_t usErrRelease_tmr;

EXT uint16_t usCHG_POVRtmr;
EXT uint16_t usCHG_OVRtmr;
/* CAN Timeout variable-------------------------------------------*/
EXT uint8_t ucCanTxTimer;
EXT uint32_t unTxMailbox;
//0x309
EXT uint16_t usVCU_RelayCommandCnt;
EXT bool VCU_RelayCommandFlag;
EXT uint8_t ucVCU_RelayCommandBuf[6];

//0x501
EXT uint8_t ucChargeStartSignalCnt;
EXT uint8_t ucChargeStopSignalCnt;
EXT bool ChargeStartSignalFlag;
EXT uint8_t ucChargeStartSignalBuf[6];

void CAN_Timeout(void);


/* Sequence Step Variable --------------------------------------*/
EXT uint8_t CHG_LED;
EXT uint8_t ucRelayStep;
EXT uint8_t ucMonStep;
EXT uint8_t ucChargeStep;
EXT uint8_t ucChgStCode;

/* Cell ADC Buffers -----------------------------------------------*/
EXT uint16_t usCellVolBuf[TOTAL_IC][12][9];
EXT uint32_t ulCellVolTot[TOTAL_IC][12];
EXT uint16_t usCellVolAvg[TOTAL_IC][12];
EXT uint16_t usCellTempBuf[TOTAL_IC][1][5];
EXT uint32_t ulCellTempTot[TOTAL_IC][1];
EXT uint16_t usCellTempAvg[TOTAL_IC][1];
EXT int16_t nTemp[TOTAL_IC * 2];


/* A/D Conversion Buffers -----------------------------------------------*/
#define	ADC_VREF			usAdcVRef

EXT uint16_t usAdcVRef;
EXT uint32_t ulSum_Vol;											// sum of cell voltage 1mV scale
EXT int32_t lSumAh;
EXT uint16_t usSocAh;
EXT int32_t lRemAsec;

EXT uint16_t ulChargeCurrAdcBuf[9];
EXT uint32_t ulChargeCurrAdcTot;
EXT uint32_t ulChargeCurrAdcAvg;

EXT uint16_t ulDischargeCurrAdcBuf[9];
EXT uint32_t ulDischargeCurrAdcTot;
EXT uint32_t ulDischargeCurrAdcAvg;

EXT uint16_t usChargeCurrent;
EXT uint16_t usDischargeCurrent;

//ADC Command Configurations
EXT uint8_t ADC_OPT              ; // See LTC6811_daisy.h for Options
EXT uint8_t ADC_CONVERSION_MODE  ;     // MD_7KHZ_3KHZ; //MD_26HZ_2KHZ;//MD_7KHZ_3KHZ; // See LTC6811_daisy.h for Options
EXT uint8_t ADC_DCP              ;     // See LTC6811_daisy.h for Options

/* CAN Data -----------------------------------------------*/
EXT CAN_TxHeaderTypeDef TxHeader;
EXT CAN_RxHeaderTypeDef RxHeader;
EXT uint8_t ucTxData[8];
EXT uint8_t ucRxData[8];
EXT uint8_t DataAssign_step;
EXT uint16_t usTargetVoltage;
EXT uint16_t usTargetCurrent;

EXT uint8_t ucpUartRx1Buf[16];
/* Cell Data  -----------------------------------------------*/
EXT cell_asic bms_ic[TOTAL_IC];

/* EEPROM Data  -----------------------------------------------*/
EXT __IO uint32_t ulFlashData[16];


#define PRODID			unFlashData.B.ProductId
#define CAN_BASE		unFlashData.B.CanBase
EXT union FlashData
{
	uint32_t W[16];

	struct
	{
		uint32_t ProductId;              		// 25: 0;
		uint32_t CanBase;              		// 25: 0;

		uint32_t notuse[15];              	//
	} B;
} unFlashData;

/* Private function prototypes -----------------------------------------------*/
void print_error(int error);
void print_cells(uint8_t datalog_en);           // Print cell voltages
void print_aux(uint8_t datalog_en);             // Print cell temperature
void print_stat(void);
void print_pec(void);
void print_open(void);
void print_config(void);
void print_etc(uint8_t datalog_en);
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
void Sequence_Timeout(uint8_t ucChgStCode);								// timeout during charge sequence
void Relays_Control(bool cmd);
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
int16_t Vol2Temp(uint16_t vol);         								// Calculate the voltage to temperature
int Vol2Temp_10k(double vol);   										// Calculate the voltage to temperature with 10k ohm
int16_t Vol2Temp_5k(uint16_t vol);              						// Calculate the voltage to temperature with 5k ohm
void Cell_Balancing(void);              								// Turn on resistance of high voltage cells
uint16_t Get_OCV_SOC(uint16_t vol);               						// Get SOC from OCV table
void SetSOC_LED(uint16_t soc);                  						// Turn On / Off the SOC LEDs according to the SOC
void BatteryCooling(uint8_t OnOff);             						// Turn the 3-way valve On / Off, turn on when over 40, turn off when under 38


//void CAN_Standby(uint8_t OnOff);                						// Turn the CAN operation Normal / Standby
void Monitoring(void);
void Uart1Transmit(char *str);                  						// Send the data via RS232
void Uart1Receive(void);                        						// Receive the data via RS232
void CAN_Tx_Process(uint16_t id, uint8_t data[8]);                  	// Send the data via CAN physically
void CAN_Celldata_Assign(void);
void SPI2_CS(uint8_t OnOff);
uint8_t spi_read_byte(uint8_t data);
void spi_write_array(uint8_t cnt, uint8_t data[]);
void spi_write_read(uint8_t w_cnt, uint8_t w_data[], uint8_t r_cnt, uint8_t r_data[]);
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
