#ifndef __DEFINE_H
#define __DEFINE_H

//BMS V3.10_Pre-Release version
//default data


//#define CELL_COUNT          10
#define TOTAL_IC            2
#define PARALLEL            24
/*
#define AMPERE_HOUR         (48.0 * PARALLEL)			//must change into (uint16) in code
#define OVER_VOL_ERR        4250
#define OVER_VOL_WARN       4100
#define VOL_HIGH            4150
#define VOL_LOW             3100
#define UNDER_VOL_WARN      2900
#define UNDER_VOL_ERR       2750
#define CHG_OVER_TEMP_ERR   50
#define CHG_OVER_TEMP_WARN  45
#define CHG_UNDER_TEMP_WARN 0
#define CHG_UNDER_TEMP_ERR  -20
#define DSC_OVER_TEMP_ERR   60
#define DSC_OVER_TEMP_WARN  50
#define DSC_UNDER_TEMP_WARN -10
#define DSC_UNDER_TEMP_ERR  -20
#define CHG_OVER_CURR_WARN  (14 * PARALLEL)
#define CHG_OVER_CURR_ERR   (30 * PARALLEL)
#define DSC_OVER_CURR_WARN  (60 * PARALLEL)
#define DSC_OVER_CURR_ERR   (72 * PARALLEL)

#define VOL_IBP_WARN		200 				// mV
#define VOL_IBP_ERR			500 				// mV
#define COOL_HIGH			400
#define COOL_LOW			380
#define HOT_HIGH			0
#define HOT_LOW				50
*/
#define OFFSET              0     								// 0x00 BMS_NO == 1

#define H                   1
#define L                   0

#define ON                  1
#define OFF                 0

#define ENABLED             1
#define DISABLED            0

#define DATALOG_ENABLED     DATA_LOG
#define DATALOG_DISABLED    0

#define MD_422HZ_1KHZ       0
#define MD_27KHZ_14KHZ      1
#define MD_7KHZ_3KHZ        2
#define MD_26HZ_2KHZ        3

#define ADC_OPT_ENABLED     1
#define ADC_OPT_DISABLED    0

#define CELL_CH_ALL         0
#define CELL_CH_1and7       1
#define CELL_CH_2and8       2
#define CELL_CH_3and9       3
#define CELL_CH_4and10      4
#define CELL_CH_5and11      5
#define CELL_CH_6and12      6

#define SELFTEST_1          1
#define SELFTEST_2          2

#define AUX_CH_ALL          0
#define AUX_CH_GPIO1        1
#define AUX_CH_GPIO2        2
#define AUX_CH_GPIO3        3
#define AUX_CH_GPIO4        4
#define AUX_CH_GPIO5        5
#define AUX_CH_VREF2        6

#define STAT_CH_ALL         0
#define STAT_CH_SOC         1
#define STAT_CH_ITEMP       2
#define STAT_CH_VREGA       3
#define STAT_CH_VREGD       4

#define DCP_DISABLED        0
#define DCP_ENABLED         1

#define PULL_UP_CURRENT     1
#define PULL_DOWN_CURRENT   0

#define NUM_RX_BYT          8
#define CELL                1
#define AUX                 2
#define STAT                3
#define CFGRA               0
#define CFGRB               4

#define BATTERY_SIM           0
#define ALWAYS_BALANCING      0



#define FLASH_ADDR_START 	((uint32)0x803F800)

#endif
