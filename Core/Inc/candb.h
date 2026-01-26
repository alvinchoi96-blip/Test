/*
 * can.h
 *
 *  Created on: 2020. 11.2.
 *      Author: JeongHwan
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_

#ifdef ROOT
#define EXT
#else
#define EXT extern
#endif
#include "main.h"

/*****************************************************************
 * ******************BMS_CANDB************************************
******************************************************************/

#define	ERR_FLAG1 					un200_TxData.BY[1]
#define	ERR_FLAG2 					un200_TxData.BY[3]
#define	WARN_FLAG1 					un200_TxData.BY[0]
#define	WARN_FLAG2 					un200_TxData.BY[2]
#define	WRN_OVERCHARGE 				un200_TxData.B.warnOverCharge
#define	WRN_OVERDISCHARGE 			un200_TxData.B.warnOverDischarge
#define	WRN_OVERCELLV 				un200_TxData.B.warnOverCellVmax
#define	WRN_UNDERCELLV 				un200_TxData.B.warnUnderCellVmin
#define	WRN_CHARGEOVERTEMP 			un200_TxData.B.warnChargeOverTemp
#define	WRN_CHARGEUNDERTEMP 		un200_TxData.B.warnChargeUnderTemp
#define	WRN_DISCHARGEOVERTEMP 		un200_TxData.B.warnDischargeOverTemp
#define	WRN_DISCHARGEUNDERTEMP 		un200_TxData.B.warnDischargeUnderTemp
#define	WRN_OVERIBP 				un200_TxData.B.warnOverIbp
#define	WRN_OVERCHARGECURRENT 		un200_TxData.B.warnOverChargeCurrent
#define	WRN_OVERDISCHARGECURRENT	un200_TxData.B.warnOverDischargeCurrent
#define	ERR_OVERCHARGE 				un200_TxData.B.errOverCharge
#define	ERR_OVERDISCHARGE 			un200_TxData.B.errOverDischarge
#define	ERR_OVERCELLV 				un200_TxData.B.errOverCellVmax
#define	ERR_UNDERCELLV	 			un200_TxData.B.errUnderCellVmin
#define	ERR_CHARGEOVERTEMP 			un200_TxData.B.errChargeOverTemp
#define	ERR_CHARGEUNDERTEMP 		un200_TxData.B.errChargeUnderTemp
#define	ERR_DISCHARGEOVERTEMP 		un200_TxData.B.errDischargeOverTemp
#define	ERR_DISCHARGEUNDERTEMP 		un200_TxData.B.errDischargeUnderTemp
#define	ERR_OVERIBP 				un200_TxData.B.errOverIbp
#define	ERR_OVERCHARGECURRENT 		un200_TxData.B.errOverChargeCurrent
#define	ERR_OVERDISCHARGECURRENT 	un200_TxData.B.errOverDischargeCurrent
#define	ERR_FAULTFLAG 				un200_TxData.B.errFaultFlag
#define	WARN_FLAG 					un200_TxData.B.WarningFlag
#define	ERR_ISOLATION 				un200_TxData.B.errIsolation

EXT union BMS_DTC
{
	uint8 BY[8];
	struct
	{
		uint8 warnOverCharge :1;								//Over charge warning
		uint8 warnOverDischarge :1;							//Over discharge warning
		uint8 warnOverCellVmax :1;							//Over cell voltage warning
		uint8 warnUnderCellVmin :1;							//Under cell voltage warning
		uint8 warnChargeOverTemp :1;							//Charge Over temperature warning
		uint8 warnChargeUnderTemp :1;							//Charge Under temperature warning
		uint8 warnDischargeOverTemp :1;						//Discharge Over temperature warning
		uint8 warnDischargeUnderTemp :1;						//Discharge Under temperature warning

		uint8 errOverCharge :1;								//Over charge power shutdown error
		uint8 errOverDischarge :1;							//Over discharge power shutdown error
		uint8 errOverCellVmax :1;								//Over cell voltage shutdown error
		uint8 errUnderCellVmin :1;							//Under cell voltage shutdown error
		uint8 errChargeOverTemp :1;							//Charge Over temperature shutdown error
		uint8 errChargeUnderTemp :1;							//Charge Under temperature shutdown error
		uint8 errDischargeOverTemp :1;						//Discharge Over temperature shutdown error
		uint8 errDischargeUnderTemp :1;						//Discharge Under temperature shutdown error

		uint8 warnOverIbp :1;									//Over difference voltage of cells warning
		uint8 warnOverChargeCurrent :1;						//Over charge current warning
		uint8 warnOverDischargeCurrent :1;					//Over discharge current warning
		uint8 notuse1 :5;

		uint8 errOverIbp :1;									//Over difference voltage of cells error
		uint8 errOverChargeCurrent :1;						//Over charge current error
		uint8 errOverDischargeCurrent :1;						//Over discharge current error
		uint8 errIsolation :1;								//Isolation error(고전압 +와 샤시 GND의 절연저항값이 기준치 초과시 발생)"
		uint8 notuse2 :4;										//

		uint8 errFaultFlag :1;							//Generic Fault flag in the battery pack(Battery Pack 내부적 에러 발생시 정비필요사항)
		uint8 WarningFlag :1;
		uint8 notuse3 :6;

		uint8 notuse4;

		uint8 notuse5;

		uint8 notuse6;
	} B;
} un200_TxData;

#define	ST_CHARGE		un201_TxData.B.stCharge
#define	ST_DISCHARGE	un201_TxData.B.stDisharge
#define	ST_DISCHRELAY	un201_TxData.B.stDischargeRelay
#define	ST_CHGRELAY		un201_TxData.B.stChargeRelay
#define	ST_BMS_READY	un201_TxData.B.stBms_Ready
#define	ST_PRERELAY		un201_TxData.B.stPrechargeRelay
#define	ST_BUZZER		un201_TxData.B.Buzzer
#define	ST_CB			un201_TxData.B.stCB
#define	ST_PWRSW		un201_TxData.B.stPowerSwitch
#define	ST_KEYON		un201_TxData.B.stKeyON
#define	ST_ACON			un201_TxData.B.stACON
#define	SW_VER			un201_TxData.B.software_version
#define	V_TOT_ACTUAL	un201_TxData.B.vTotalActual
#define	I_TOT_ACTUAL	un201_TxData.B.iTotalActual

EXT union BMS_201_MSG
{
	uint8 BY[8];
	struct
	{
		uint8 stCharge :1;
		uint8 stDisharge :1;
		uint8 stDischargeRelay :1;											//Status of Main Relay On/Off
		uint8 stChargeRelay :1;											//Status of Heater On/Off
		uint8 stBms_Ready :1;											//BMS Ready
		uint8 stPrechargeRelay :1;									//Status of Precharge Relay On/Off
		uint8 Buzzer :1;
		uint8 stCB :1;												//

		uint8 stPowerSwitch :1;												//
		uint8 stKeyON :1;
		uint8 stACON :1;
		uint8 notuse1 :5;

		uint8 software_version;
		uint8 notuse2;
		uint16 vTotalActual;											//Actual voltage of the battery pack
		int16_t iTotalActual;											//Actual current of the battery pack (충전:+, 방전:-)
	} B;
} un201_TxData;

#define	V_MIN_DISCHARGE		un202_TxData.B.vMinDischarge
#define	I_MAX_DISCHARGE		un202_TxData.B.iMaxDischarge
#define	V_MAX_CHARGE		un202_TxData.B.vMaxCharge
#define	I_MAX_CHARGE		un202_TxData.B.iMaxCharge

EXT union BMS_202_MSG
{
	uint8 BY[8];
	struct
	{
		uint16 vMinDischarge;									//Min voltage limit at discharging(방전시 최저전압 셋팅값)
		uint16 iMaxDischarge;									//Max current limit at discharging
		uint16 vMaxCharge;									//Max voltage limit at charging
		uint16 iMaxCharge;									//Max current limit at charging
	} B;
} un202_TxData;

#define REM_AH			un205_TxData.B.ahRemainedCap
#define SOC				un205_TxData.B.Soc
#define SOH				un205_TxData.B.Soh
#define REM_WH			un205_TxData.B.RemainedWh

EXT union BMS_205_MSG
{
	uint8 BY[8];
	struct
	{
		uint16 ahRemainedCap;									//Remained Capacity
		uint16 Soc;											//State Of Charge
		uint16 Soh;											//State Of Health
		uint16 RemainedWh;									//Remained Watt Hour
	} B;
} un205_TxData;

#define	CELL_V_HIGH		un206_TxData.B.vHighCell
#define	CELL_V_LOW		un206_TxData.B.vLowCell
#define	CELL_V_AVG		un206_TxData.B.vAverageCell
#define	CELL_V_DEVI		un206_TxData.B.vDeviationCell

EXT union BMS_206_MSG
{
	uint8 BY[8];
	struct
	{
		int16_t vHighCell;										//Highest voltage among battery cells
		int16_t vLowCell;										//Lowest voltage among battery cells
		int16_t vAverageCell;									//Average voltage of battery cells
		int16_t vDeviationCell;								//Deviation voltage of battery cells
	} B;
} un206_TxData;

#define CELL_T_HIGH		un207_TxData.B.tHighPlace
#define CELL_T_LOW		un207_TxData.B.tLowPlace
#define CELL_T_AVG		un207_TxData.B.tAveragePlace
#define CELL_T_DEVI		un207_TxData.B.tDeviationPlace

EXT union BMS_207_MSG
{
	uint8 BY[8];
	struct
	{
		int16_t tHighPlace;									//Highest temperature among battery cells
		int16_t tLowPlace;										//Lowest temperature among battery cells
		int16_t tAveragePlace;									//Average temperature of battery cells
		uint16 tDeviationPlace;								//Deviation temperature of battery cells
	} B;
} un207_TxData;

#define	TOT_CELLS	un208_TxData.B.ucTotalCells
#define	TOT_PLACE	un208_TxData.B.ucTotalPlace
#define	DC_TEMP1	un208_TxData.B.usDc_Temp1
#define	DC_TEMP2	un208_TxData.B.usDc_Temp2

EXT union BMS_208_MSG2
{
	uint8 BY[8];
	struct
	{
		uint8 ucTotalCells;									//Total numbers of cells
		uint8 ucTotalPlace;									//Total numbers of temperature sensors
		uint16 usDc_Temp1;									//DC Temperature 1
		uint16 usDc_Temp2;									//DC Temperature 2
		uint16 notuse;
	} B;
} un208_TxData;

#define VCU_RELAY_ON	un209_RxData.B.Main_RelayOnOff

EXT union VCU_209_MSG
{
	uint8 BY[8];
	struct
	{
		uint8 notuse;											//Total numbers of cells

		uint8 Main_RelayOnOff :1;								//Main Relay ON request of BMS in VCU
		uint8 notuse1 :7;										//Main Relay ON request of BMS in VCU

		uint8 notuse3[6];										//
	} B;
} un209_RxData;

#define	C_DEBUG			un2f0_RxData.B.Debug
#define	C_CELL_PRINT	un2f0_RxData.B.Cell_Print
#define	C_ADC_PRINT		un2f0_RxData.B.ADC_Print
#define	C_DATA_LOG		un2f0_RxData.B.Data_Log
#define	C_SETTING		un2f0_RxData.B.Data_Log
#define	C_FLASH_WR		un2f0_RxData.B.Flash_Wr
#define	C_RELAYS		un2f0_RxData.B.Relays
#define	C_HEATER		un2f0_RxData.B.Heater
#define	C_BUZZER		un2f0_RxData.B.Buzzer
#define	C_COOLHIGH		un2f0_RxData.B.CoolHigh
#define	C_COOLLOW		un2f0_RxData.B.CoolLow
#define	C_HOTHIGH		un2f0_RxData.B.HotHigh
#define	C_HOTLOW		un2f0_RxData.B.HotLow

EXT union DEBUG_2f0_MSG
{
	uint8 BY[8];
	struct
	{
		uint8 Debug :1;
		uint8 Cell_Print :1;
		uint8 ADC_Print :1;
		uint8 Data_Log :1;
		uint8 Settings :1;
		uint8 notuse1 :3;

		uint8 Flash_Wr :1;
		uint8 Relays :2;
		uint8 Heater :2;
		uint8 Buzzer :2;
		uint8 notuse2 :1;

		uint8 notuse3[2];

		uint8 CoolHigh;
		uint8 CoolLow;
		uint8 HotHigh;
		uint8 HotLow;
	} B;
} un2f0_RxData;

#define	CELLV_01				un511_TxData.B.CellV_01
#define	CELLV_02				un511_TxData.B.CellV_02
#define	CELLV_03				un511_TxData.B.CellV_03
#define	CELLV_04				un511_TxData.B.CellV_04
/*****************************************************************
 * ******************Cell data************************************
******************************************************************/

EXT union YamahaBMS_511
{
	uint8 BY[8];
	struct
	{
		uint16 CellV_01;
		uint16 CellV_02;
		uint16 CellV_03;
		uint16 CellV_04;
	} B;
} un511_TxData;

#define	CELLV_05				un512_TxData.B.CellV_05
#define	CELLV_06				un512_TxData.B.CellV_06
#define	CELLV_07				un512_TxData.B.CellV_07
#define	CELLV_08				un512_TxData.B.CellV_08

EXT union YamahaBMS_512
{
	uint8 BY[8];
	struct
	{
		uint16 CellV_05;
		uint16 CellV_06;
		uint16 CellV_07;
		uint16 CellV_08;
	} B;
} un512_TxData;

#define	CELLV_09				un513_TxData.B.CellV_09
#define	CELLV_10				un513_TxData.B.CellV_10
#define	CELLV_11				un513_TxData.B.CellV_11
#define	CELLV_12				un513_TxData.B.CellV_12

EXT union YamahaBMS_513
{
	uint8 BY[8];
	struct
	{
		uint16 CellV_09;
		uint16 CellV_10;
		uint16 CellV_11;
		uint16 CellV_12;
	} B;
} un513_TxData;

#define	CELLV_13				un514_TxData.B.CellV_13
#define	CELLV_14				un514_TxData.B.CellV_14
#define	CELLV_15				un514_TxData.B.CellV_15
#define	CELLV_16				un514_TxData.B.CellV_16

EXT union YamahaBMS_514
{
	uint8 BY[8];
	struct
	{
		uint16 CellV_13;
		uint16 CellV_14;
		uint16 CellV_15;
		uint16 CellV_16;
	} B;
} un514_TxData;

#define	CELLV_17				un515_TxData.B.CellV_17
#define	CELLV_18				un515_TxData.B.CellV_18
#define	CELLV_19				un515_TxData.B.CellV_19
#define	CELLV_20				un515_TxData.B.CellV_20

EXT union YamahaBMS_515
{
	uint8 BY[8];
	struct
	{
		uint16 CellV_17;
		uint16 CellV_18;
		uint16 CellV_19;
		uint16 CellV_20;
	} B;
} un515_TxData;

#define	CELLT_1				un517_TxData.B.CellT_1
#define	CELLT_2				un517_TxData.B.CellT_2
#define	CELLT_3				un517_TxData.B.CellT_3
#define	CELLT_4				un517_TxData.B.CellT_4
EXT union YamahaBMS_517
{
	uint8 BY[6];
	struct
	{
		uint16 CellT_1;
		int16_t CellT_2;
		int16_t CellT_3;
		int16_t CellT_4;
	} B;
} un517_TxData;
#endif /* INC_CAN_H_ */
