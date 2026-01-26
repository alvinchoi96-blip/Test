/************************************

Copyright 2018(c) Analog Devices, Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
 - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the
   distribution.
 - Neither the name of Analog Devices, Inc. nor the names of its
   contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.
 - The use of this software may or may not infringe the patent rights
   of one or more patent holders.  This license does not release you
   from the requirement that you obtain separate licenses from these
   patent holders to use this software.
 - Use of the software either in source or binary form, must be run
   on or directly connected to an Analog Devices Inc. component.

THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Copyright 2015 Linear Technology Corp. (LTC)
***********************************************************/

#ifndef LTC681X_H
#define LTC681X_H
#include <stdint.h>
#include <stdbool.h>
#include <Spec_define.h>


//! Cell Voltage data structure.
typedef struct
{
  uint16 c_codes[18];//!< Cell Voltage Codes
  uint8 pec_match[6];//!< If a PEC error was detected during most recent read cmd
} cv;

//! AUX Reg Voltage Data
typedef struct
{
  uint16 a_codes[9];//!< Aux Voltage Codes
  uint8 pec_match[4];//!< If a PEC error was detected during most recent read cmd
} ax;

typedef struct
{
  uint16 stat_codes[4];//!< A two dimensional array of the stat voltage codes.
  uint8 flags[3]; //!< byte array that contains the uv/ov flag data
  uint8 mux_fail[1]; //!< Mux self test status flag
  uint8 thsd[1]; //!< Thermal shutdown status
  uint8 pec_match[2];//!< If a PEC error was detected during most recent read cmd
} st;

typedef struct
{
  uint8 tx_data[6];
  uint8 rx_data[8];
  uint8 rx_pec_match;//!< If a PEC error was detected during most recent read cmd
} ic_register;

typedef struct
{
  uint16 pec_count;
  uint16 cfgr_pec;
  uint16 cell_pec[6];
  uint16 aux_pec[4];
  uint16 stat_pec[2];
} pec_counter;

typedef struct
{
  uint8 cell_channels;
  uint8 stat_channels;
  uint8 aux_channels;
  uint8 num_cv_reg;
  uint8 num_gpio_reg;
  uint8 num_stat_reg;
} register_cfg;

typedef struct
{
  ic_register  configa;
  ic_register  configb;
  cv           cells;
  ax           aux;
  st           stat;
  ic_register  com;
  ic_register  pwm;
  ic_register  pwmb;
  ic_register  sctrl;
  ic_register  sctrlb;
  boolean         isospi_reverse;
  pec_counter  crc_count;
  register_cfg ic_reg;
  sint32         system_open_wire;
} cell_asic;


/*!   calculates  and returns the CRC15
  @returns The calculated pec15 as an unsigned sint32
*/
uint16 pec15_calc(uint8 len, //!< the length of the data array being passed to the function
                    uint8 *data); //!<  the array of data that the PEC will be generated from

void LTC6811_init_reg_limits(cell_asic ic[]);

/*!  Wake isoSPI up from idle state */
void wakeup_idle();//!< number of ICs in the daisy chain

/*!  Wake the LTC6813 from the sleep state */
void wakeup_sleep(); //!< number of ICs in the daisy chain

/*! Sense a command to the bms IC. This code will calculate the PEC code for the transmitted command*/
void cmd_68(uint8 tx_cmd[2]); //!< 2 Byte array containing the BMS command to be sent

//! Writes an array of data to the daisy chain
void write_68(uint8 tx_cmd[2], //!< 2 Byte array containing the BMS command to be sent
              uint8 data[]); //!< Array containing the data to be written to the BMS ICs
//! Issues a command onto the daisy chain and reads back 6*total_ic data in the rx_data array
int8_t read_68(uint8 tx_cmd[2], //!< 2 Byte array containing the BMS command to be sent
               uint8 *rx_data); //!< Array that the read back data will be stored.

/*! Starts the Mux Decoder diagnostic self test

 Running this command will start the Mux Decoder Diagnostic Self Test
 This test takes roughly 1mS to complete. The MUXFAIL bit will be updated,
 the bit will be set to 1 for a failure and 0 if the test has been passed.
 */
void LTC6811_diagn();

//! Sends the poll adc command
//! @returns 1 byte read back after a pladc command. If the byte is not 0xFF ADC conversion has completed
uint8 LTC6811_pladc();

//! This function will block operation until the ADC has finished it's conversion
//! @returns the approximate time it took for the ADC function to complete.
uint32 LTC6811_pollAdc();

/*! Starts cell voltage conversion

  Starts ADC conversions of the LTC6811 Cpin inputs.
  The type of ADC conversion executed can be changed by setting the following parameters:
*/
void LTC6811_adcv(uint8 MD, //!< ADC Conversion Mode
                  uint8 DCP, //!< Controls if Discharge is permitted during conversion
                  uint8 CH //!< Sets which Cell channels are converted
                 );

/*!  Starts cell voltage  and GPIO 1&2 conversion
*/
void LTC6811_adcvax(
  uint8 MD, //!< ADC Conversion Mode
  uint8 DCP //!< Controls if Discharge is permitted during conversion
);


/*!  Starts cell voltage self test conversion
*/
void LTC6811_cvst(
  uint8 MD, //!< ADC Conversion Mode
  uint8 ST //!< Self Test Mode
);

/*!  Starts cell voltage and SOC conversion
*/
void LTC6811_adcvsc(
  uint8 MD, //!< ADC Conversion Mode
  uint8 DCP //!< Controls if Discharge is permitted during conversion
);
/*!  Starts cell voltage overlap conversion
*/
void LTC6811_adol(
  uint8 MD, //!< ADC Conversion Mode
  uint8 DCP //!< Discharge permitted during conversion
);

/*!  Start an open wire Conversion
*/
void LTC6811_adow(
  uint8 MD, //!< ADC Conversion Mode
  uint8 PUP //!< Controls if Discharge is permitted during conversion
);


/*!  Start a GPIO and Vref2 Conversion
*/
void LTC6811_adax(
  uint8 MD, //!< ADC Conversion Mode
  uint8 CHG //!< Sets which GPIO channels are converted
);

/*!  Start an GPIO Redundancy test
*/
void LTC6811_adaxd(
  uint8 MD, //!< ADC Conversion Mode
  uint8 CHG //!< Sets which GPIO channels are converted
);

/*!  Start an Auxiliary Register Self Test Conversion
*/
void LTC6811_axst(
  uint8 MD, //!< ADC Conversion Mode
  uint8 ST //!< Sets if self test 1 or 2 is run
);



/*!  Start a Status ADC Conversion
*/
void LTC6811_adstat(
  uint8 MD, //!< ADC Conversion Mode
  uint8 CHST //!< Sets which Stat channels are converted
);

/*!   Start a Status register redundancy test Conversion
*/
void LTC6811_adstatd(
  uint8 MD, //!< ADC Mode
  uint8 CHST //!< Sets which Status channels are converted
);


/*!  Start a Status Register Self Test Conversion
*/
void LTC6811_statst(
  uint8 MD, //!< ADC Conversion Mode
  uint8 ST //!< Sets if self test 1 or 2 is run
);

void LTC6811_rdcv_reg(uint8 reg, //!<Determines which cell voltage register is read back
                      uint8 *data); //!<An array of the unparsed cell codes
/*! helper function that parses voltage measurement registers
*/
int8_t parse_cells(uint8 current_ic,
                   uint8 cell_reg,
                   uint8 cell_data[],
                   uint16 *cell_codes,
                   uint8 *ic_pec);

/*!  Read the raw data from the LTC6811 auxiliary register

 The function reads a single GPIO voltage register and stores thre read data
 in the *data point as a byte array. This function is rarely used outside of
 the LTC6811_rdaux() command.
 */
void LTC6811_rdaux_reg(uint8 reg, //Determines which GPIO voltage register is read back
                       uint8 *data); //Array of the unparsed auxiliary codes
/*!  Read the raw data from the LTC6811 stat register

 The function reads a single GPIO voltage register and stores thre read data
 in the *data point as a byte array. This function is rarely used outside of
 the LTC6811_rdstat() command.
 */
void LTC6811_rdstat_reg(uint8 reg, //Determines which stat register is read back
                        uint8 *data); //Array of the unparsed stat codes

/*!  Clears the LTC6811 cell voltage registers

The command clears the cell voltage registers and initializes
all values to 1. The register will read back hexadecimal 0xFF
after the command is sent.
*/
void LTC6811_clrcell();
/*! Clears the LTC6811 Auxiliary registers

The command clears the Auxiliary registers and initializes
all values to 1. The register will read back hexadecimal 0xFF
after the command is sent.
*/
void LTC6811_clraux();

/*!  Clears the LTC6811 Stat registers

The command clears the Stat registers and initializes
all values to 1. The register will read back hexadecimal 0xFF
after the command is sent.
*/
void LTC6811_clrstat();

/*!  Clears the LTC6811 SCTRL registers

The command clears the SCTRL registers and initializes
all values to 0. The register will read back hexadecimal 0x00
after the command is sent.
*/
void LTC6811_clrsctrl();

/*! Starts the Mux Decoder diagnostic self test

Running this command will start the Mux Decoder Diagnostic Self Test
This test takes roughly 1mS to complete. The MUXFAIL bit will be updated,
the bit will be set to 1 for a failure and 0 if the test has been passed.
*/
void LTC6811_diagn();

/*!  Reads and parses the LTC6811 cell voltage registers.

 The function is used to read the cell codes of the LTC6811.
 This function will send the requested read commands parse the data
 and store the cell voltages in the cell_asic structure.
 */
uint8 LTC6811_rdcv(uint8 reg, // Controls which cell voltage register is read back.
                     cell_asic ic[]); // Array of the parsed cell codes

/*!  Reads and parses the LTC6811 auxiliary registers.

 The function is used to read the  parsed GPIO codes of the LTC6811. This function will send the requested
 read commands parse the data and store the gpio voltages in the cell_asic structure.
*/
int8_t LTC6811_rdaux(uint8 reg, //Determines which GPIO voltage register is read back.
                     cell_asic ic[]); //!< Measurement Data Structure

/*!  Reads and parses the LTC6811 stat registers.

 The function is used to read the  parsed status codes of the LTC6811. This function will send the requested
 read commands parse the data and store the status voltages in the cell_asic structure
 */
int8_t LTC6811_rdstat(uint8 reg, //!<Determines which Stat  register is read back.
                      cell_asic ic[]); //!< Measurement Data Structure
/*!  Write the LTC6811 CFGRA

 This command will write the configuration registers of the LTC6811s
 connected in a daisy chain stack. The configuration is written in descending
 order so the last device's configuration is written first.
 */
void LTC6811_wrcfg(cell_asic ic[]); //A two dimensional array of the configuration data that will be written
/*!  Write the LTC6811 CFGRB register

 This command will write the configuration registers of the LTC6811s
 connected in a daisy chain stack. The configuration is written in descending
 order so the last device's configuration is written first.
 */
void LTC6811_wrcfgb(cell_asic ic[]); //A two dimensional array of the configuration data that will be written
/*!  Reads the LTC6811 CFGRA register
*/
int8_t LTC6811_rdcfg(cell_asic ic[]); //A two dimensional array that the function stores the read configuration data.

/*!  Reads the LTC6811 CFGRB register
*/
int8_t LTC6811_rdcfgb(cell_asic ic[]); //A two dimensional array that the function stores the read configuration data.


/*!  Reads pwm registers of a LTC6811 daisy chain
*/
int8_t LTC6811_rdpwm(uint8 pwmReg, //!< The PWM Register to be written A or B
                     cell_asic ic[]); //!< ASIC Variable

/*!  Write the LTC6811 PWM register

 This command will write the pwm registers of the LTC6811
 connected in a daisy chain stack. The pwm is written in descending
 order so the last device's pwm is written first.
*/
void LTC6811_wrpwm(uint8 pwmReg,  //!< The PWM Register to be written
                   cell_asic ic[]); //!< ASIC Variable

/*!  issues a stcomm command and clocks data out of the COMM register */
void LTC6811_stcomm();

void LTC6811_set_discharge(sint32 Cell, cell_asic ic[]);

/*!  Reads comm registers of a LTC6811 daisy chain
*/
int8_t LTC6811_rdcomm(cell_asic ic[]); //!< ASIC Variable

/*!  Write the LTC6811 COMM register

 This command will write the comm registers of the LTC6811
 connected in a daisy chain stack. The comm is written in descending
 order so the last device's configuration is written first.
 */
void LTC6811_wrcomm(cell_asic ic[]); ///!< ASIC Variable

/*! Selft Test Helper Function*/
uint16 LTC6811_st_lookup(
  uint8 MD, //ADC Mode
  uint8 ST //Self Test
);

/*! Helper Function to clear DCC bits in the CFGR Registers*/
void clear_discharge(cell_asic ic[]);

/*! Helper function that runs the ADC Self Tests*/
int16_t LTC6811_run_cell_adc_st(uint8 adc_reg,
                                cell_asic ic[]);

/*! Helper function that runs the ADC Digital Redudancy commands and checks output for errors*/
int16_t LTC6811_run_adc_redundancy_st(uint8 adc_mode,
                                      uint8 adc_reg,
                                      cell_asic ic[]);

/*! Helper function that runs the datasheet open wire algorithm*/
void LTC6811_run_openwire(cell_asic ic[]);

/*! Helper Function that runs the ADC Overlap test*/
uint16 LTC6811_run_adc_overlap(cell_asic ic[]);
/*! Helper Function that counts overall PEC errors and register/IC PEC errors*/
void LTC6811_check_pec(uint8 reg,
                       cell_asic ic[]);

/*! Helper Function that resets the PEC error counters */
void LTC6811_reset_crc_count(cell_asic ic[]);

/*! Helper Function to initialize the CFGR data structures*/
void LTC6811_init_cfg(cell_asic ic[]);

/*! Helper function to turn the refon bit HIGH or LOW*/
void LTC6811_set_cfgr_refon(uint8 nIC,
                            cell_asic ic[],
                            boolean refon);

/*! Helper function to turn the ADCOPT bit HIGH or LOW*/
void LTC6811_set_cfgr_adcopt(uint8 nIC,
                             cell_asic ic[],
                             boolean adcopt);

/*! Helper function to turn the GPIO bits HIGH or LOW*/
void LTC6811_set_cfgr_gpio(uint8 nIC,
                           cell_asic ic[],
                           boolean gpio[]);

/*! Helper function to turn the DCC bits HIGH or LOW*/
void LTC6811_set_cfgr_dis(uint8 nIC,
                          cell_asic ic[],
                          boolean dcc[]);
/*!  Helper function to set uv field in CFGRA register*/
void LTC6811_set_cfgr_uv(uint8 nIC,
                         cell_asic ic[],
                         uint16 uv);

/*!  Helper function to set ov field in CFGRA register*/
void LTC6811_set_cfgr_ov(uint8 nIC,
                         cell_asic ic[],
                         uint16 ov);

#endif
