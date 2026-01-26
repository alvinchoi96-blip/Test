/*!
 General BMS Library
 @verbatim

 @endverbatim

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

 Copyright 2017 Linear Technology Corp. (LTC)
 ***********************************************************/

#include <stdlib.h>
#include "stm32f1xx_hal.h"
//#include "LTC6811.h"
//#include "define.h"
#include "extref.h"
#include "main.h"

uint16 crc15Table[256] = { 0x0, 0xc599, 0xceab, 0xb32, 0xd8cf, 0x1d56, 0x1664, 0xd3fd, 0xf407, 0x319e,
		0x3aac,  //!<precomputed CRC15 Table
		0xff35, 0x2cc8, 0xe951, 0xe263, 0x27fa, 0xad97, 0x680e, 0x633c, 0xa6a5, 0x7558, 0xb0c1, 0xbbf3, 0x7e6a, 0x5990, 0x9c09,
		0x973b, 0x52a2, 0x815f, 0x44c6, 0x4ff4, 0x8a6d, 0x5b2e, 0x9eb7, 0x9585, 0x501c, 0x83e1, 0x4678, 0x4d4a, 0x88d3, 0xaf29,
		0x6ab0, 0x6182, 0xa41b, 0x77e6, 0xb27f, 0xb94d, 0x7cd4, 0xf6b9, 0x3320, 0x3812, 0xfd8b, 0x2e76, 0xebef, 0xe0dd, 0x2544,
		0x2be, 0xc727, 0xcc15, 0x98c, 0xda71, 0x1fe8, 0x14da, 0xd143, 0xf3c5, 0x365c, 0x3d6e, 0xf8f7, 0x2b0a, 0xee93, 0xe5a1,
		0x2038, 0x7c2, 0xc25b, 0xc969, 0xcf0, 0xdf0d, 0x1a94, 0x11a6, 0xd43f, 0x5e52, 0x9bcb, 0x90f9, 0x5560, 0x869d, 0x4304,
		0x4836, 0x8daf, 0xaa55, 0x6fcc, 0x64fe, 0xa167, 0x729a, 0xb703, 0xbc31, 0x79a8, 0xa8eb, 0x6d72, 0x6640, 0xa3d9, 0x7024,
		0xb5bd, 0xbe8f, 0x7b16, 0x5cec, 0x9975, 0x9247, 0x57de, 0x8423, 0x41ba, 0x4a88, 0x8f11, 0x57c, 0xc0e5, 0xcbd7, 0xe4e,
		0xddb3, 0x182a, 0x1318, 0xd681, 0xf17b, 0x34e2, 0x3fd0, 0xfa49, 0x29b4, 0xec2d, 0xe71f, 0x2286, 0xa213, 0x678a, 0x6cb8,
		0xa921, 0x7adc, 0xbf45, 0xb477, 0x71ee, 0x5614, 0x938d, 0x98bf, 0x5d26, 0x8edb, 0x4b42, 0x4070, 0x85e9, 0xf84, 0xca1d,
		0xc12f, 0x4b6, 0xd74b, 0x12d2, 0x19e0, 0xdc79, 0xfb83, 0x3e1a, 0x3528, 0xf0b1, 0x234c, 0xe6d5, 0xede7, 0x287e, 0xf93d,
		0x3ca4, 0x3796, 0xf20f, 0x21f2, 0xe46b, 0xef59, 0x2ac0, 0xd3a, 0xc8a3, 0xc391, 0x608, 0xd5f5, 0x106c, 0x1b5e, 0xdec7,
		0x54aa, 0x9133, 0x9a01, 0x5f98, 0x8c65, 0x49fc, 0x42ce, 0x8757, 0xa0ad, 0x6534, 0x6e06, 0xab9f, 0x7862, 0xbdfb, 0xb6c9,
		0x7350, 0x51d6, 0x944f, 0x9f7d, 0x5ae4, 0x8919, 0x4c80, 0x47b2, 0x822b, 0xa5d1, 0x6048, 0x6b7a, 0xaee3, 0x7d1e, 0xb887,
		0xb3b5, 0x762c, 0xfc41, 0x39d8, 0x32ea, 0xf773, 0x248e, 0xe117, 0xea25, 0x2fbc, 0x846, 0xcddf, 0xc6ed, 0x374, 0xd089,
		0x1510, 0x1e22, 0xdbbb, 0xaf8, 0xcf61, 0xc453, 0x1ca, 0xd237, 0x17ae, 0x1c9c, 0xd905, 0xfeff, 0x3b66, 0x3054, 0xf5cd,
		0x2630, 0xe3a9, 0xe89b, 0x2d02, 0xa76f, 0x62f6, 0x69c4, 0xac5d, 0x7fa0, 0xba39, 0xb10b, 0x7492, 0x5368, 0x96f1, 0x9dc3,
		0x585a, 0x8ba7, 0x4e3e, 0x450c, 0x8095 };

void LTC6811_init_reg_limits(cell_asic ic[])
{
	for (uint8 cic = 0; cic < TOTAL_IC; cic++)
	{
		ic[cic].ic_reg.cell_channels = CELL_COUNT;
		ic[cic].ic_reg.aux_channels = 5;
		ic[cic].ic_reg.stat_channels = 4;
		ic[cic].ic_reg.num_cv_reg = 4 ;
		ic[cic].ic_reg.num_gpio_reg = 2;
		ic[cic].ic_reg.num_stat_reg = 3;
	}
}

void wakeup_idle()
{
	uint16 i = 500;

	SPI2_CS(ON);
	while (i--) // 0.01 msec wait for isoSPI ready mode
		;
	SPI2_CS(OFF);
}

//Generic wakeup commannd to wake the LTC6813 from sleep
void wakeup_sleep()
{
	uint16 i = 20000;

	SPI2_CS(ON);
	while (i--) // 0.4 msec(Max) wait for LTC6811 Standby Mode
		;
	SPI2_CS(OFF);
}

//Generic function to write 68xx commands. Function calculated PEC for tx_cmd data
void cmd_68(uint8 tx_cmd[2])
{
	uint8 cmd[4];
	uint16 cmd_pec;

	cmd[0] = tx_cmd[0];
	cmd[1] = tx_cmd[1];
	cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (uint8) (cmd_pec >> 8);
	cmd[3] = (uint8) (cmd_pec);
	SPI2_CS(ON);
	spi_write_array(4, cmd);
	SPI2_CS(OFF);
}

//Generic function to write 68xx commands and write payload data. Function calculated PEC for tx_cmd data
void write_68(uint8 tx_cmd[2], uint8 data[])
{
	const uint8 BYTES_IN_REG = 6;
	const uint8 CMD_LEN = 4 + (8 * TOTAL_IC);
	uint8 *cmd;
	uint16 data_pec;
	uint16 cmd_pec;
	uint8 cmd_index;

	cmd = (uint8*) malloc(CMD_LEN * sizeof(uint8));
	cmd[0] = tx_cmd[0];
	cmd[1] = tx_cmd[1];
	cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (uint8) (cmd_pec >> 8);
	cmd[3] = (uint8) (cmd_pec);
	cmd_index = 4;
	for (uint8 n = TOTAL_IC; n > 0; n--)       // executes for each LTC6811 in daisy chain, this loops starts with
	{												// the last IC on the stack. The first configuration written is
													// received by the last IC in the daisy chain

		for (uint8 current_byte = 0; current_byte < BYTES_IN_REG; current_byte++)
		{
			cmd[cmd_index] = data[((n - 1) * 6) + current_byte];
			cmd_index = cmd_index + 1;
		}

		data_pec = (uint16) pec15_calc(BYTES_IN_REG, &data[(n - 1) * 6]); // calculating the PEC for each Iss configuration register data
		cmd[cmd_index] = (uint8) (data_pec >> 8);
		cmd[cmd_index + 1] = (uint8) data_pec;
		cmd_index = cmd_index + 2;
	}

	SPI2_CS(ON);
	spi_write_array(CMD_LEN, cmd);
	SPI2_CS(OFF);
	free(cmd);
}

//Generic function to write 68xx commands and read data. Function calculated PEC for tx_cmd data
int8_t read_68(uint8 tx_cmd[2], uint8 *rx_data)
{
	const uint8 BYTES_IN_REG = 8;
	uint8 cmd[4];
	uint8 data[256];
	int8_t pec_error = 0;
	uint16 cmd_pec;
	uint16 data_pec;
	uint16 received_pec;

	// data = (uint8 *) malloc((8*TOTAL_IC)*sizeof(uint8)); // This is a problem because it can fail

	cmd[0] = tx_cmd[0];
	cmd[1] = tx_cmd[1];
	cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (uint8) (cmd_pec >> 8);
	cmd[3] = (uint8) (cmd_pec);

	SPI2_CS(ON);
	spi_write_read(4, cmd, (BYTES_IN_REG * TOTAL_IC), data);        //Read the configuration data of all ICs on the daisy chain into
	SPI2_CS(OFF);                          //rx_data[] array

	for (uint8 n = 0; n < TOTAL_IC; n++)       //executes for each LTC6811 in the daisy chain and packs the data
	{
		//into the r_comm array as well as check the received Config data
		//for any bit errors
		for (uint8 current_byte = 0; current_byte < BYTES_IN_REG; current_byte++)
		{
			rx_data[(n * 8) + current_byte] = data[current_byte + (n * BYTES_IN_REG)];
		}
		received_pec = (rx_data[(n * 8) + 6] << 8) + rx_data[(n * 8) + 7];
		data_pec = pec15_calc(6, &rx_data[n * 8]);
		if (received_pec != data_pec)
		{
			pec_error = -1;
		}
	}

	return (pec_error);
}

/*
 Calculates  and returns the CRC15
 */
uint16 pec15_calc(uint8 len, //Number of bytes that will be used to calculate a PEC
		uint8 *data //Array of data that will be used to calculate  a PEC
		)
{
	uint16 remainder, addr;

	remainder = 16;                        //initialize the PEC
	for (uint8 i = 0; i < len; i++)        // loops for each byte in data array
	{
		addr = ((remainder >> 7) ^ data[i]) & 0xff;        //calculate PEC table address
		remainder = (remainder << 8) ^ crc15Table[addr]; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	}
	return (remainder * 2); //The CRC15 has a 0 in the LSB so the remainder must be multiplied by 2
}

//Starts cell voltage conversion
void LTC6811_adcv(uint8 MD, //ADC Mode
		uint8 DCP, //Discharge Permit
		uint8 CH //Cell Channels to be measured
		)
{
	uint8 cmd[4];
	uint8 md_bits;

	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x02;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + 0x60 + (DCP << 4) + CH;
	cmd_68(cmd);
}

//Starts cell voltage and SOC conversion
void LTC6811_adcvsc(uint8 MD, //ADC Mode
		uint8 DCP //Discharge Permit
		)
{
	uint8 cmd[4];
	uint8 md_bits;
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits | 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits | 0x60 | (DCP << 4) | 0x07;
	cmd_68(cmd);

}

// Starts cell voltage  and GPIO 1&2 conversion -> modified for gpio 5 aux in m-BMS3.1ver
void LTC6811_adcvax(uint8 MD, //ADC Mode
		uint8 DCP //Discharge Permit
		)
{
	uint8 cmd[4];
	uint8 md_bits;
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits | 0x04;

	md_bits = (MD & 0x01) << 7;
	cmd[1] = (md_bits | (((DCP & 0x01) << 4) + 0x6F));
	cmd_68(cmd);
}

//Starts cell voltage overlap conversion
void LTC6811_adol(uint8 MD, //ADC Mode
		uint8 DCP //Discharge Permit
		)
{
	uint8 cmd[4];
	uint8 md_bits;
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x02;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + (DCP << 4) + 0x01;
	cmd_68(cmd);
}

//Starts cell voltage self test conversion
void LTC6811_cvst(uint8 MD, //ADC Mode
		uint8 ST //Self Test
		)
{
	uint8 cmd[2];
	uint8 md_bits;

	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x02;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + ((ST) << 5) + 0x07;
	cmd_68(cmd);

}

//Start an Auxiliary Register Self Test Conversion
void LTC6811_axst(uint8 MD, //ADC Mode
		uint8 ST //Self Test
		)
{
	uint8 cmd[4];
	uint8 md_bits;

	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + ((ST & 0x03) << 5) + 0x07;
	cmd_68(cmd);

}

//Start a Status Register Self Test Conversion
void LTC6811_statst(uint8 MD, //ADC Mode
		uint8 ST //Self Test
		)
{
	uint8 cmd[2];
	uint8 md_bits;

	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + ((ST & 0x03) << 5) + 0x0F;
	cmd_68(cmd);

}

//Sends the poll adc command
uint8 LTC6811_pladc()
{
	uint8 cmd[4];
	uint8 adc_state = 0xFF;
	uint16 cmd_pec;

	cmd[0] = 0x07;
	cmd[1] = 0x14;
	cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (uint8) (cmd_pec >> 8);
	cmd[3] = (uint8) (cmd_pec);

	SPI2_CS(ON);
	spi_write_array(4, cmd);
// adc_state = spi_read_byte(0xFF);

	SPI2_CS(OFF);
	return (adc_state);
}

//This function will block operation until the ADC has finished it's conversion
uint32 LTC6811_pollAdc()
{
	uint32 counter = 0;
	uint8 cmd[4];
	uint16 cmd_pec;

	cmd[0] = 0x07;
	cmd[1] = 0x14;
	cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (uint8) (cmd_pec >> 8);
	cmd[3] = (uint8) (cmd_pec);

	SPI2_CS(ON);
	spi_write_array(4, cmd);

	counter = spi_read_byte(0xff);

	SPI2_CS(OFF);

	return (counter);
}

//Start a GPIO and Vref2 Conversion
void LTC6811_adax(uint8 MD, //ADC Mode
		uint8 CHG //GPIO Channels to be measured)
		)
{
	uint8 cmd[4];
	uint8 md_bits;

	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + 0x60 + CHG;
	cmd_68(cmd);

}

//Start an GPIO Redundancy test
void LTC6811_adaxd(uint8 MD, //ADC Mode
		uint8 CHG //GPIO Channels to be measured)
		)
{
	uint8 cmd[4];
	uint8 md_bits;

	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + CHG;
	cmd_68(cmd);
}

//Start a Status ADC Conversion
void LTC6811_adstat(uint8 MD, //ADC Mode
		uint8 CHST //GPIO Channels to be measured
		)
{
	uint8 cmd[4];
	uint8 md_bits;

	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + 0x68 + CHST;
	cmd_68(cmd);
}

// Start a Status register redundancy test Conversion
void LTC6811_adstatd(uint8 MD, //ADC Mode
		uint8 CHST //GPIO Channels to be measured
		)
{
	uint8 cmd[2];
	uint8 md_bits;

	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + 0x08 + CHST;
	cmd_68(cmd);

}

// Start an open wire Conversion
void LTC6811_adow(uint8 MD, //ADC Mode
		uint8 PUP //Discharge Permit
		)
{
	uint8 cmd[2];
	uint8 md_bits;
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x02;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + 0x28 + (PUP << 6); //+ CH;
	cmd_68(cmd);
}

// Reads the raw cell voltage register data
void LTC6811_rdcv_reg(uint8 reg, //Determines which cell voltage register is read back
		uint8 *data) //An array of the unparsed cell codes
{
	const uint8 REG_LEN = 8; //number of bytes in each ICs register + 2 bytes for the PEC
	uint8 cmd[4];
	uint16 cmd_pec;

	if (reg == 1)     //1: RDCVA
	{
		cmd[1] = 0x04;
		cmd[0] = 0x00;
	}
	else if (reg == 2) //2: RDCVB
	{
		cmd[1] = 0x06;
		cmd[0] = 0x00;
	}
	else if (reg == 3) //3: RDCVC
	{
		cmd[1] = 0x08;
		cmd[0] = 0x00;
	}
	else if (reg == 4) //4: RDCVD
	{
		cmd[1] = 0x0A;
		cmd[0] = 0x00;
	}
	else if (reg == 5) //4: RDCVE
	{
		cmd[1] = 0x09;
		cmd[0] = 0x00;
	}
	else if (reg == 6) //4: RDCVF
	{
		cmd[1] = 0x0B;
		cmd[0] = 0x00;
	}

	cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (uint8) (cmd_pec >> 8);
	cmd[3] = (uint8) (cmd_pec);

	SPI2_CS(ON);
	spi_write_read(4, cmd, (REG_LEN * TOTAL_IC), data);
	SPI2_CS(OFF);

}

//helper function that parses voltage measurement registers
int8_t parse_cells(uint8 current_ic, uint8 cell_reg, uint8 cell_data[], uint16 *cell_codes, uint8 *ic_pec)
{

	const uint8 BYT_IN_REG = 6;
	const uint8 CELL_IN_REG = 3;
	int8_t pec_error = 0;
	uint16 parsed_cell;
	uint16 received_pec;
	uint16 data_pec;
	uint8 data_counter = current_ic * NUM_RX_BYT; //data counter

	for (uint8 current_cell = 0; current_cell < CELL_IN_REG; current_cell++)// This loop parses the read back data into cell voltages, it
	{
		// loops once for each of the 3 cell voltage codes in the register

		parsed_cell = cell_data[data_counter] + (cell_data[data_counter + 1] << 8);	//Each cell code is received as two bytes and is combined to
																					// create the parsed cell voltage code
		cell_codes[current_cell + ((cell_reg - 1) * CELL_IN_REG)] = parsed_cell;
		data_counter = data_counter + 2;                       			//Because cell voltage codes are two bytes the data counter
																		//must increment by two for each parsed cell code
	}

	received_pec = (cell_data[data_counter] << 8) | cell_data[data_counter + 1]; //The received PEC for the current_ic is transmitted as the 7th and 8th
																				 //after the 6 cell voltage data bytes
	data_pec = pec15_calc(BYT_IN_REG, &cell_data[(current_ic) * NUM_RX_BYT]);

	if (received_pec != data_pec)
	{
		pec_error = 1;                             				//The pec_error variable is simply set negative if any PEC errors
		ic_pec[cell_reg - 1] = 1;
	}
	else
	{
		ic_pec[cell_reg - 1] = 0;
	}
	data_counter = data_counter + 2;
	return (pec_error);
}

/*
 The function reads a single GPIO voltage register and stores thre read data
 in the *data point as a byte array. This function is rarely used outside of
 the LTC6811_rdaux() command.
 */
void LTC6811_rdaux_reg(uint8 reg, //Determines which GPIO voltage register is read back
		uint8 *data) //Array of the unparsed auxiliary codes
{
	const uint8 REG_LEN = 8; // number of bytes in the register + 2 bytes for the PEC
	uint8 cmd[4];
	uint16 cmd_pec;

	if (reg == 1)     //Read back auxiliary group A
	{
		cmd[1] = 0x0C;
		cmd[0] = 0x00;
	}
	else if (reg == 2)  //Read back auxiliary group B
	{
		cmd[1] = 0x0e;
		cmd[0] = 0x00;
	}
	else if (reg == 3)  //Read back auxiliary group C
	{
		cmd[1] = 0x0D;
		cmd[0] = 0x00;
	}
	else if (reg == 4)  //Read back auxiliary group D
	{
		cmd[1] = 0x0F;
		cmd[0] = 0x00;
	}
	else          //Read back auxiliary group A
	{
		cmd[1] = 0x0C;
		cmd[0] = 0x00;
	}

	cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (uint8) (cmd_pec >> 8);
	cmd[3] = (uint8) (cmd_pec);

	SPI2_CS(ON);
	spi_write_read(4, cmd, (REG_LEN * TOTAL_IC), data);
	SPI2_CS(OFF);

}

/*
 The function reads a single stat  register and stores the read data
 in the *data point as a byte array. This function is rarely used outside of
 the LTC6811_rdstat() command.
 */
void LTC6811_rdstat_reg(uint8 reg, //Determines which stat register is read back
		uint8 *data) //Array of the unparsed stat codes
{
	const uint8 REG_LEN = 8; // number of bytes in the register + 2 bytes for the PEC
	uint8 cmd[4];
	uint16 cmd_pec;

	if (reg == 1)     //Read back statiliary group A
	{
		cmd[1] = 0x10;
		cmd[0] = 0x00;
	}
	else if (reg == 2)  //Read back statiliary group B
	{
		cmd[1] = 0x12;
		cmd[0] = 0x00;
	}

	else          //Read back statiliary group A
	{
		cmd[1] = 0x10;
		cmd[0] = 0x00;
	}

	cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (uint8) (cmd_pec >> 8);
	cmd[3] = (uint8) (cmd_pec);

	SPI2_CS(ON);
	spi_write_read(4, cmd, (REG_LEN * TOTAL_IC), data);
	SPI2_CS(OFF);
}

/*
 The command clears the cell voltage registers and intiallizes
 all values to 1. The register will read back hexadecimal 0xFF
 after the command is sent.
 */
void LTC6811_clrcell()
{
	uint8 cmd[2] = { 0x07, 0x11 };
	cmd_68(cmd);
}

/*
 The command clears the Auxiliary registers and initializes
 all values to 1. The register will read back hexadecimal 0xFF
 after the command is sent.
 */
void LTC6811_clraux()
{
	uint8 cmd[2] = { 0x07, 0x12 };
	cmd_68(cmd);
}

/*
 The command clears the Stat registers and intiallizes
 all values to 1. The register will read back hexadecimal 0xFF
 after the command is sent.

 */
void LTC6811_clrstat()
{
	uint8 cmd[2] = { 0x07, 0x13 };
	cmd_68(cmd);
}
/*
 The command clears the Sctrl registers and initializes
 all values to 0. The register will read back hexadecimal 0x00
 after the command is sent.
 */
void LTC6811_clrsctrl()
{
	uint8 cmd[2] = { 0x00, 0x18 };
	cmd_68(cmd);
}
//Starts the Mux Decoder diagnostic self test
void LTC6811_diagn()
{
	uint8 cmd[2] = { 0x07, 0x15 };
	cmd_68(cmd);
}

//Reads and parses the LTC6811 cell voltage registers.
uint8 LTC6811_rdcv(uint8 reg, 											// Controls which cell voltage register is read back.
		cell_asic ic[]) 												// Array of the parsed cell codes
{
	int8_t pec_error = 0;
	uint8 *cell_data;
	uint8 c_ic = 0;
	cell_data = (uint8*) malloc((NUM_RX_BYT * TOTAL_IC) * sizeof(uint8));

	if (reg == 0)
	{
		for (uint8 cell_reg = 1; cell_reg < ic[0].ic_reg.num_cv_reg + 1; cell_reg++) //executes once for each of the LTC6811 cell voltage registers
		{   																			//increase cell_reg from 1 to 4
			LTC6811_rdcv_reg(cell_reg, cell_data);
			for (sint32 n = 0; n < TOTAL_IC; n++)
			{
				if (ic->isospi_reverse == false)
				{
					c_ic = n;
				}
				else
				{
					c_ic = TOTAL_IC - n - 1;
				}
				pec_error = pec_error
						+ parse_cells(n, cell_reg, cell_data, &ic[c_ic].cells.c_codes[0], &ic[c_ic].cells.pec_match[0]);
			}
		}
	}

	else
	{
		LTC6811_rdcv_reg(reg, cell_data);

		for (sint32 n = 0; n < TOTAL_IC; n++)
		{
			if (ic->isospi_reverse == false)
			{
				c_ic = n;
			}
			else
			{
				c_ic = TOTAL_IC - n - 1;
			}
			pec_error = pec_error
					+ parse_cells(n, reg, &cell_data[8 * c_ic], &ic[c_ic].cells.c_codes[0], &ic[c_ic].cells.pec_match[0]);
		}
	}
	LTC6811_check_pec(CELL, ic);
	free(cell_data);
	return (pec_error);
}

/*
 The function is used
 to read the  parsed GPIO codes of the LTC6811. This function will send the requested
 read commands parse the data and store the gpio voltages in aux_codes variable
 */
int8_t LTC6811_rdaux(uint8 reg, //Determines which GPIO voltage register is read back.
		cell_asic ic[]) //A two dimensional array of the gpio voltage codes.
{
	uint8 *data;
	int8_t pec_error = 0;
	uint8 c_ic = 0;
	data = (uint8*) malloc((NUM_RX_BYT * TOTAL_IC) * sizeof(uint8));

	if (reg == 0)
	{
		for (uint8 gpio_reg = 1; gpio_reg < ic[0].ic_reg.num_gpio_reg + 3; gpio_reg++)//executes once for each of the LTC6811 aux voltage registers
		{
			LTC6811_rdaux_reg(gpio_reg, data);                 		//Reads the raw auxiliary register data into the data[] array
			for (sint32 n = 0; n < TOTAL_IC; n++)
			{
				if (ic->isospi_reverse == false)
				{
					c_ic = n;
				}
				else
				{
					c_ic = TOTAL_IC - n - 1;
				}
				pec_error = parse_cells(n, gpio_reg, data, &ic[c_ic].aux.a_codes[0], &ic[c_ic].aux.pec_match[0]);
			}
		}
	}
	else
	{
		LTC6811_rdaux_reg(reg, data);

		for (sint32 n = 0; n < TOTAL_IC; n++)
		{
			if (ic->isospi_reverse == false)
			{
				c_ic = n;
			}
			else
			{
				c_ic = TOTAL_IC - n - 1;
			}
			pec_error = parse_cells(n, reg, data, &ic[c_ic].aux.a_codes[0], &ic[c_ic].aux.pec_match[0]);
		}

	}
	LTC6811_check_pec(AUX, ic);
	free(data);
	return (pec_error);
}

// Reads and parses the LTC6811 stat registers.
int8_t LTC6811_rdstat(uint8 reg, //Determines which Stat  register is read back.
		cell_asic ic[])

{

	const uint8 BYT_IN_REG = 6;
	const uint8 GPIO_IN_REG = 3;

	uint8 *data;
	uint8 data_counter = 0;
	int8_t pec_error = 0;
	uint16 parsed_stat;
	uint16 received_pec;
	uint16 data_pec;
	uint8 c_ic = 0;
	data = (uint8*) malloc((NUM_RX_BYT * TOTAL_IC) * sizeof(uint8));

	if (reg == 0)
	{

		for (uint8 stat_reg = 1; stat_reg < 3; stat_reg++)          //executes once for each of the LTC6811 stat voltage registers
		{
			data_counter = 0;
			LTC6811_rdstat_reg(stat_reg, data);                       //Reads the raw statiliary register data into the data[] array

			for (uint8 n = 0; n < TOTAL_IC; n++)      // executes for every LTC6811 in the daisy chain
			{
				if (ic->isospi_reverse == false)
				{
					c_ic = n;
				}
				else
				{
					c_ic = TOTAL_IC - n - 1;
				}
				// n is used as the IC counter
				if (stat_reg == 1)
				{
					for (uint8 current_gpio = 0; current_gpio < GPIO_IN_REG; current_gpio++) // This loop parses the read back data into GPIO voltages, it
					{
						// loops once for each of the 3 gpio voltage codes in the register

						parsed_stat = data[data_counter] + (data[data_counter + 1] << 8); //Each gpio codes is received as two bytes and is combined to
						ic[c_ic].stat.stat_codes[current_gpio] = parsed_stat;
						data_counter = data_counter + 2;                 //Because gpio voltage codes are two bytes the data counter

					}
				}
				else if (stat_reg == 2)
				{
					parsed_stat = data[data_counter] + (data[data_counter + 1] << 8); //Each gpio codes is received as two bytes and is combined to
					data_counter = data_counter + 2;
					ic[c_ic].stat.stat_codes[3] = parsed_stat;
					ic[c_ic].stat.flags[0] = data[data_counter++];
					ic[c_ic].stat.flags[1] = data[data_counter++];
					ic[c_ic].stat.flags[2] = data[data_counter++];
					ic[c_ic].stat.mux_fail[0] = (data[data_counter] & 0x02) >> 1;
					ic[c_ic].stat.thsd[0] = data[data_counter++] & 0x01;
				}

				received_pec = (data[data_counter] << 8) + data[data_counter + 1]; //The received PEC for the n is transmitted as the 7th and 8th
				//after the 6 gpio voltage data bytes
				data_pec = pec15_calc(BYT_IN_REG, &data[n * NUM_RX_BYT]);

				if (received_pec != data_pec)
				{
					pec_error = -1; //The pec_error variable is simply set negative if any PEC errors
					ic[c_ic].stat.pec_match[stat_reg - 1] = 1;
					//are detected in the received serial data
				}
				else
				{
					ic[c_ic].stat.pec_match[stat_reg - 1] = 0;
				}

				data_counter = data_counter + 2;                 //Because the transmitted PEC code is 2 bytes long the data_counter
				//must be incremented by 2 bytes to point to the next ICs gpio voltage data
			}

		}

	}
	else
	{

		LTC6811_rdstat_reg(reg, data);
		for (sint32 n = 0; n < TOTAL_IC; n++)            // executes for every LTC6811 in the daisy chain
		{
			// n is used as an IC counter
			if (ic->isospi_reverse == false)
			{
				c_ic = n;
			}
			else
			{
				c_ic = TOTAL_IC - n - 1;
			}
			if (reg == 1)
			{
				for (uint8 current_gpio = 0; current_gpio < GPIO_IN_REG; current_gpio++) // This loop parses the read back data into GPIO voltages, it
				{
					// loops once for each of the 3 gpio voltage codes in the register
					parsed_stat = data[data_counter] + (data[data_counter + 1] << 8); //Each gpio codes is received as two bytes and is combined to
					// create the parsed gpio voltage code

					ic[c_ic].stat.stat_codes[current_gpio] = parsed_stat;
					data_counter = data_counter + 2;                     //Because gpio voltage codes are two bytes the data counter
					//must increment by two for each parsed gpio voltage code

				}
			}
			else if (reg == 2)
			{
				parsed_stat = data[data_counter];
				data_counter++;
				parsed_stat += (data[data_counter] << 8);
				data_counter++;              //Each gpio codes is received as two bytes and is combined to
				ic[c_ic].stat.stat_codes[3] = parsed_stat;
				ic[c_ic].stat.flags[0] = data[data_counter++];
				ic[c_ic].stat.flags[1] = data[data_counter++];
				ic[c_ic].stat.flags[2] = data[data_counter++];
				ic[c_ic].stat.mux_fail[0] = (data[data_counter] & 0x02) >> 1;
				ic[c_ic].stat.thsd[0] = data[data_counter++] & 0x01;
			}

			received_pec = (data[data_counter] << 8) + data[data_counter + 1]; //The received PEC for the n is transmitted as the 7th and 8th
			//after the 6 gpio voltage data bytes
			data_pec = pec15_calc(BYT_IN_REG, &data[n * NUM_RX_BYT]);
			if (received_pec != data_pec)
			{
				pec_error = -1;                             //The pec_error variable is simply set negative if any PEC errors
				ic[c_ic].stat.pec_match[reg - 1] = 1;

			}

			data_counter = data_counter + 2;
		}
	}
	LTC6811_check_pec(STAT, ic);
	free(data);
	return (pec_error);
}

//Write the LTC6811 CFGRA
void LTC6811_wrcfg(cell_asic ic[])
{
	uint8 cmd[2] = { 0x00, 0x01 };
	uint8 write_buffer[256];
	uint8 write_count = 0;
	uint8 c_ic = 0;
	for (uint8 n = 0; n < TOTAL_IC; n++)
	{
		if (ic->isospi_reverse == true)
		{
			c_ic = n;
		}
		else
		{
			c_ic = TOTAL_IC - n - 1;
		}

		for (uint8 data = 0; data < 6; data++)
		{
			write_buffer[write_count] = ic[c_ic].configa.tx_data[data];
			write_count++;
		}
	}
	write_68(cmd, write_buffer);
}

//Write the LTC6811 CFGRB
void LTC6811_wrcfgb(cell_asic ic[])
{
	uint8 cmd[2] = { 0x00, 0x24 };
	uint8 write_buffer[256];
	uint8 write_count = 0;
	uint8 c_ic = 0;
	for (uint8 n = 0; n < TOTAL_IC; n++)
	{
		if (ic->isospi_reverse == true)
		{
			c_ic = n;
		}
		else
		{
			c_ic = TOTAL_IC - n - 1;
		}

		for (uint8 data = 0; data < 6; data++)
		{
			write_buffer[write_count] = ic[c_ic].configb.tx_data[data];
			write_count++;
		}
	}
	write_68(cmd, write_buffer);
}

//Read CFGA
int8_t LTC6811_rdcfg(cell_asic ic[])
{
	uint8 cmd[2] = { 0x00, 0x02 };
	uint8 read_buffer[256];
	int8_t pec_error = 0;
	uint16 data_pec;
	uint16 calc_pec;
	uint8 c_ic = 0;
	pec_error = read_68(cmd, read_buffer);
	for (uint8 n = 0; n < TOTAL_IC; n++)
	{
		if (ic->isospi_reverse == false)
		{
			c_ic = n;
		}
		else
		{
			c_ic = TOTAL_IC - n - 1;
		}

		for (sint32 byte = 0; byte < 8; byte++)
		{
			ic[c_ic].configa.rx_data[byte] = read_buffer[byte + (8 * n)];
		}
		calc_pec = pec15_calc(6, &read_buffer[8 * n]);
		data_pec = read_buffer[7 + (8 * n)] | (read_buffer[6 + (8 * n)] << 8);
		if (calc_pec != data_pec)
		{
			ic[c_ic].configa.rx_pec_match = 1;
		}
		else
			ic[c_ic].configa.rx_pec_match = 0;
	}
	LTC6811_check_pec(CFGRA, ic);
	return (pec_error);
}

//Reads CFGB
int8_t LTC6811_rdcfgb(cell_asic ic[])
{
	uint8 cmd[2] = { 0x00, 0x26 };
	uint8 read_buffer[256];
	int8_t pec_error = 0;
	uint16 data_pec;
	uint16 calc_pec;
	uint8 c_ic = 0;
	pec_error = read_68(cmd, read_buffer);
	for (uint8 n = 0; n < TOTAL_IC; n++)
	{
		if (ic->isospi_reverse == false)
		{
			c_ic = n;
		}
		else
		{
			c_ic = TOTAL_IC - n - 1;
		}

		for (sint32 byte = 0; byte < 8; byte++)
		{
			ic[c_ic].configb.rx_data[byte] = read_buffer[byte + (8 * n)];
		}
		calc_pec = pec15_calc(6, &read_buffer[8 * n]);
		data_pec = read_buffer[7 + (8 * n)] | (read_buffer[6 + (8 * n)] << 8);
		if (calc_pec != data_pec)
		{
			ic[c_ic].configb.rx_pec_match = 1;
		}
		else
			ic[c_ic].configb.rx_pec_match = 0;
	}
	LTC6811_check_pec(CFGRB, ic);
	return (pec_error);
}

//Looks up the result pattern for digital filter self test
uint16 LTC6811_st_lookup(uint8 MD, //ADC Mode
		uint8 ST //Self Test
		)
{
	uint16 test_pattern = 0;
	if (MD == 1)
	{
		if (ST == 1)
		{
			test_pattern = 0x9565;
		}
		else
		{
			test_pattern = 0x6A9A;
		}
	}
	else
	{
		if (ST == 1)
		{
			test_pattern = 0x9555;
		}
		else
		{
			test_pattern = 0x6AAA;
		}
	}
	return (test_pattern);
}

//Clears all of the DCC bits in the configuration registers
void clear_discharge(cell_asic ic[])
{
	for (sint32 i = 0; i < TOTAL_IC; i++)
	{
		ic[i].configa.tx_data[4] = 0;
		ic[i].configa.tx_data[5] = 0;
	}
}

// Runs the Digital Filter Self Test
int16_t LTC6811_run_cell_adc_st(uint8 adc_reg, cell_asic ic[])
{
	int16_t error = 0;
	uint16 expected_result = 0;
	for (sint32 self_test = 1; self_test < 3; self_test++)
	{

		expected_result = LTC6811_st_lookup(2, self_test);
		wakeup_idle();
		switch (adc_reg)
		{
		case CELL:
			wakeup_idle();
			LTC6811_clrcell();
			LTC6811_cvst(2, self_test);
			LTC6811_pollAdc(); //this isn't working
			wakeup_idle();
			error = LTC6811_rdcv(0, ic);
			for (sint32 cic = 0; cic < TOTAL_IC; cic++)
			{
				for (sint32 channel = 0; channel < ic[cic].ic_reg.cell_channels; channel++)
				{
					if (ic[cic].cells.c_codes[channel] != expected_result)
					{
						error = error + 1;
					}
				}
			}
			break;
		case AUX:
			error = 0;
			wakeup_idle();
			LTC6811_clraux();
			LTC6811_axst(2, self_test);
			LTC6811_pollAdc();
			//HAL_Delay(1); // 1000!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			wakeup_idle();
			LTC6811_rdaux(0, ic);
			for (sint32 cic = 0; cic < TOTAL_IC; cic++)
			{
				for (sint32 channel = 0; channel < ic[cic].ic_reg.aux_channels; channel++)
				{
					if (ic[cic].aux.a_codes[channel] != expected_result)
					{
						error = error + 1;
					}
				}
			}
			break;
		case STAT:
			wakeup_idle();
			LTC6811_clrstat();
			LTC6811_statst(2, self_test);
			LTC6811_pollAdc();
			wakeup_idle();
			error = LTC6811_rdstat(0, ic);
			for (sint32 cic = 0; cic < TOTAL_IC; cic++)
			{
				for (sint32 channel = 0; channel < ic[cic].ic_reg.stat_channels; channel++)
				{
					if (ic[cic].stat.stat_codes[channel] != expected_result)
					{
						error = error + 1;
					}
				}
			}
			break;

		default:
			error = -1;
			break;
		}
	}
	return (error);
}

//runs the redundancy self test
int16_t LTC6811_run_adc_redundancy_st(uint8 adc_mode, uint8 adc_reg, cell_asic ic[])
{
	int16_t error = 0;
	for (sint32 self_test = 1; self_test < 3; self_test++)
	{
		wakeup_idle();
		switch (adc_reg)
		{
		case AUX:
			LTC6811_clraux();
			LTC6811_adaxd(adc_mode, AUX_CH_ALL);
			LTC6811_pollAdc();
			wakeup_idle();
			error = LTC6811_rdaux(0, ic);
			for (sint32 cic = 0; cic < TOTAL_IC; cic++)
			{
				for (sint32 channel = 0; channel < ic[cic].ic_reg.aux_channels; channel++)
				{
					if (ic[cic].aux.a_codes[channel] >= 65280)
					{
						error = error + 1;
					}
				}
			}
			break;
		case STAT:
			LTC6811_clrstat();
			LTC6811_adstatd(adc_mode, STAT_CH_ALL);
			LTC6811_pollAdc();
			wakeup_idle();
			error = LTC6811_rdstat(0, ic);
			for (sint32 cic = 0; cic < TOTAL_IC; cic++)
			{
				for (sint32 channel = 0; channel < ic[cic].ic_reg.stat_channels; channel++)
				{
					if (ic[cic].stat.stat_codes[channel] >= 65280)
					{
						error = error + 1;
					}
				}
			}
			break;

		default:
			error = -1;
			break;
		}
	}
	return (error);
}

//Runs the datasheet algorithm for open wire
void LTC6811_run_openwire(cell_asic ic[])
{
	uint16 OPENWIRE_THRESHOLD = 4000;
	const uint8 N_CHANNELS = ic[0].ic_reg.cell_channels;
	//uint8 error;

	cell_asic pullUp_cell_codes[TOTAL_IC];
	cell_asic pullDwn_cell_codes[TOTAL_IC];
	cell_asic openWire_delta[TOTAL_IC];

	wakeup_sleep();
	LTC6811_adow(MD_7KHZ_3KHZ, PULL_UP_CURRENT);
	LTC6811_pollAdc();
	wakeup_idle();
	LTC6811_adow(MD_7KHZ_3KHZ, PULL_UP_CURRENT);
	LTC6811_pollAdc();
	wakeup_idle();
	//error = LTC6811_rdcv(0, pullUp_cell_codes);
	LTC6811_rdcv(0, pullUp_cell_codes);

	wakeup_idle();
	LTC6811_adow(MD_7KHZ_3KHZ, PULL_DOWN_CURRENT);
	LTC6811_pollAdc();
	wakeup_idle();
	LTC6811_adow(MD_7KHZ_3KHZ, PULL_DOWN_CURRENT);
	LTC6811_pollAdc();
	wakeup_idle();
	//error = LTC6811_rdcv(0, pullDwn_cell_codes);
	LTC6811_rdcv(0, pullDwn_cell_codes);

	for (sint32 cic = 0; cic < TOTAL_IC; cic++)
	{
		ic[cic].system_open_wire = 0;
		for (sint32 cell = 0; cell < N_CHANNELS; cell++)
		{
			if (pullDwn_cell_codes[cic].cells.c_codes[cell] > pullUp_cell_codes[cic].cells.c_codes[cell])
			{
				openWire_delta[cic].cells.c_codes[cell] = pullDwn_cell_codes[cic].cells.c_codes[cell]
						- pullUp_cell_codes[cic].cells.c_codes[cell];
			}
			else
			{
				openWire_delta[cic].cells.c_codes[cell] = 0;
			}

		}
	}
	for (sint32 cic = 0; cic < TOTAL_IC; cic++)
	{
		for (sint32 cell = 1; cell < N_CHANNELS; cell++)
		{

			if (openWire_delta[cic].cells.c_codes[cell] > OPENWIRE_THRESHOLD)
			{
				ic[cic].system_open_wire += (1 << cell);

			}
		}
		if (pullUp_cell_codes[cic].cells.c_codes[0] == 0)
		{
			ic[cic].system_open_wire += 1;
		}
		if (pullUp_cell_codes[cic].cells.c_codes[N_CHANNELS - 1] == 0)
		{
			ic[cic].system_open_wire += (1 << (N_CHANNELS));
		}
	}
}

// Runs the ADC overlap test for the IC
uint16 LTC6811_run_adc_overlap(cell_asic ic[])
{
	uint16 error = 0;
	int32_t measure_delta = 0;
	int16_t failure_pos_limit = 20;
	int16_t failure_neg_limit = -20;
	wakeup_idle();
	LTC6811_adol(MD_7KHZ_3KHZ, DCP_DISABLED);
	LTC6811_pollAdc();
	wakeup_idle();
	error = LTC6811_rdcv(0, ic);
	for (sint32 cic = 0; cic < TOTAL_IC; cic++)
	{
		measure_delta = (int32_t) ic[cic].cells.c_codes[6] - (int32_t) ic[cic].cells.c_codes[7];
		if ((measure_delta > failure_pos_limit) || (measure_delta < failure_neg_limit))
		{
			error = error | (1 << (cic - 1));
		}
	}
	return (error);
}

//Helper function that increments PEC counters
void LTC6811_check_pec(uint8 reg, cell_asic ic[])
{
	switch (reg)
	{
	case CFGRA:
		for (sint32 n = 0; n < TOTAL_IC; n++)
		{
			ic[n].crc_count.pec_count = ic[n].crc_count.pec_count + ic[n].configa.rx_pec_match;
			ic[n].crc_count.cfgr_pec = ic[n].crc_count.cfgr_pec + ic[n].configa.rx_pec_match;
		}
		break;

	case CFGRB:
		for (sint32 n = 0; n < TOTAL_IC; n++)
		{
			ic[n].crc_count.pec_count = ic[n].crc_count.pec_count + ic[n].configb.rx_pec_match;
			ic[n].crc_count.cfgr_pec = ic[n].crc_count.cfgr_pec + ic[n].configb.rx_pec_match;
		}
		break;
	case CELL:
		for (sint32 n = 0; n < TOTAL_IC; n++)
		{
			for (sint32 i = 0; i < ic[0].ic_reg.num_cv_reg; i++)
			{
				ic[n].crc_count.pec_count = ic[n].crc_count.pec_count + ic[n].cells.pec_match[i];
				ic[n].crc_count.cell_pec[i] = ic[n].crc_count.cell_pec[i] + ic[n].cells.pec_match[i];
			}
		}
		break;
	case AUX:
		for (sint32 n = 0; n < TOTAL_IC; n++)
		{
			for (sint32 i = 0; i < ic[0].ic_reg.num_gpio_reg; i++)
			{
				ic[n].crc_count.pec_count = ic[n].crc_count.pec_count + (ic[n].aux.pec_match[i]);
				ic[n].crc_count.aux_pec[i] = ic[n].crc_count.aux_pec[i] + (ic[n].aux.pec_match[i]);
			}
		}

		break;
	case STAT:
		for (sint32 n = 0; n < TOTAL_IC; n++)
		{

			for (sint32 i = 0; i < ic[0].ic_reg.num_stat_reg - 1; i++)
			{
				ic[n].crc_count.pec_count = ic[n].crc_count.pec_count + ic[n].stat.pec_match[i];
				ic[n].crc_count.stat_pec[i] = ic[n].crc_count.stat_pec[i] + ic[n].stat.pec_match[i];
			}
		}
		break;
	default:
		break;
	}
}

//Helper Function to reset PEC counters
void LTC6811_reset_crc_count(cell_asic ic[])
{
	for (sint32 n = 0; n < TOTAL_IC; n++)
	{
		ic[n].crc_count.pec_count = 0;
		ic[n].crc_count.cfgr_pec = 0;
		for (sint32 i = 0; i < 6; i++)
		{
			ic[n].crc_count.cell_pec[i] = 0;

		}
		for (sint32 i = 0; i < 4; i++)
		{
			ic[n].crc_count.aux_pec[i] = 0;
		}
		for (sint32 i = 0; i < 2; i++)
		{
			ic[n].crc_count.stat_pec[i] = 0;
		}
	}
}

//Helper function to intialize CFG variables.
void LTC6811_init_cfg(cell_asic ic[])
{
	boolean gpioBits[5] = { true, true, true, true, true };
	boolean dccBits[12] = { false, false, false, false, false, false, false, false, false, false, false, false };

	for (sint32 n = 0; n < TOTAL_IC; n++)
	{
		for (sint32 j = 0; j < 6; j++)
		{
			ic[n].configa.tx_data[j] = 0;
			ic[n].configb.tx_data[j] = 0;
		}
		LTC6811_set_cfgr_refon(n, ic, true);
		LTC6811_set_cfgr_adcopt(n, ic, false);
		LTC6811_set_cfgr_gpio(n, ic, gpioBits);
		LTC6811_set_cfgr_dis(n, ic, dccBits);
	}
}

//Helper function to set CFGR variable
void LTC6811_set_cfgr(uint8 nIC, cell_asic ic[], boolean refon, boolean adcopt, boolean gpio[5], boolean dcc[12])
{
	LTC6811_set_cfgr_refon(nIC, ic, refon);
	LTC6811_set_cfgr_adcopt(nIC, ic, adcopt);
	LTC6811_set_cfgr_gpio(nIC, ic, gpio);
	LTC6811_set_cfgr_dis(nIC, ic, dcc);
}

//Helper function to set the REFON bit
void LTC6811_set_cfgr_refon(uint8 nIC, cell_asic ic[], boolean refon)
{
	if (refon)
	{
		ic[nIC].configa.tx_data[0] = ic[nIC].configa.tx_data[0] | 0x04;
	}
	else
	{
		ic[nIC].configa.tx_data[0] = ic[nIC].configa.tx_data[0] & 0xFB;
	}
}

//Helper function to set the adcopt bit
void LTC6811_set_cfgr_adcopt(uint8 nIC, cell_asic ic[], boolean adcopt)
{
	if (adcopt)
	{
		ic[nIC].configa.tx_data[0] = ic[nIC].configa.tx_data[0] | 0x01;
	}
	else
	{
		ic[nIC].configa.tx_data[0] = ic[nIC].configa.tx_data[0] & 0xFE;
	}
}

//Helper function to set GPIO bits
void LTC6811_set_cfgr_gpio(uint8 nIC, cell_asic ic[], boolean gpio[5])
{
	for (sint32 i = 0; i < 5; i++)
	{
		if (gpio[i])
		{
			ic[nIC].configa.tx_data[0] = ic[nIC].configa.tx_data[0] | (0x01 << (i + 3));
		}
		else
		{
			ic[nIC].configa.tx_data[0] = ic[nIC].configa.tx_data[0] & (~(0x01 << (i + 3)));
		}
	}
}

//Helper function to control discharge
void LTC6811_set_cfgr_dis(uint8 nIC, cell_asic ic[], boolean dcc[12])
{
	for (sint32 i = 0; i < 8; i++)
	{
		if (dcc[i])
		{
			ic[nIC].configa.tx_data[4] = ic[nIC].configa.tx_data[4] | (0x01 << i);
		}
		else
		{
			ic[nIC].configa.tx_data[4] = ic[nIC].configa.tx_data[4] & (~(0x01 << i));
		}
	}
	for (sint32 i = 0; i < 4; i++)
	{
		if (dcc[i + 8])
		{
			ic[nIC].configa.tx_data[5] = ic[nIC].configa.tx_data[5] | (0x01 << i);
		}
		else
		{
			ic[nIC].configa.tx_data[5] = ic[nIC].configa.tx_data[5] & (~(0x01 << i));
		}
	}
}

//Helper Function to set uv value in CFG register
void LTC6811_set_cfgr_uv(uint8 nIC, cell_asic ic[], uint16 uv)
{
	uint16 tmp = (uv / 16) - 1;
	ic[nIC].configa.tx_data[1] = 0x00FF & tmp;
	ic[nIC].configa.tx_data[2] = ic[nIC].configa.tx_data[2] & 0xF0;
	ic[nIC].configa.tx_data[2] = ic[nIC].configa.tx_data[2] | ((0x0F00 & tmp) >> 8);
}

//helper function to set OV value in CFG register
void LTC6811_set_cfgr_ov(uint8 nIC, cell_asic ic[], uint16 ov)
{
	uint16 tmp = (ov / 16);
	ic[nIC].configa.tx_data[3] = 0x00FF & (tmp >> 4);
	ic[nIC].configa.tx_data[2] = ic[nIC].configa.tx_data[2] & 0x0F;
	ic[nIC].configa.tx_data[2] = ic[nIC].configa.tx_data[2] | ((0x000F & tmp) << 4);
}

//Writes the comm register
void LTC6811_wrcomm(cell_asic ic[])
{
	uint8 cmd[2] = { 0x07, 0x21 };
	uint8 write_buffer[256];
	uint8 write_count = 0;
	uint8 c_ic = 0;
	for (uint8 n = 0; n < TOTAL_IC; n++)
	{
		if (ic->isospi_reverse == true)
		{
			c_ic = n;
		}
		else
		{
			c_ic = TOTAL_IC - n - 1;
		}

		for (uint8 data = 0; data < 6; data++)
		{
			write_buffer[write_count] = ic[c_ic].com.tx_data[data];
			write_count++;
		}
	}
	write_68(cmd, write_buffer);
}

/*
 Reads COMM registers of a LTC6811 daisy chain
 */
int8_t LTC6811_rdcomm(cell_asic ic[])
{
	uint8 cmd[2] = { 0x07, 0x22 };
	uint8 read_buffer[256];
	int8_t pec_error = 0;
	uint16 data_pec;
	uint16 calc_pec;
	uint8 c_ic = 0;
	pec_error = read_68(cmd, read_buffer);
	for (uint8 n = 0; n < TOTAL_IC; n++)
	{
		if (ic->isospi_reverse == false)
		{
			c_ic = n;
		}
		else
		{
			c_ic = TOTAL_IC - n - 1;
		}

		for (sint32 byte = 0; byte < 8; byte++)
		{
			ic[c_ic].com.rx_data[byte] = read_buffer[byte + (8 * n)];
		}
		calc_pec = pec15_calc(6, &read_buffer[8 * n]);
		data_pec = read_buffer[7 + (8 * n)] | (read_buffer[6 + (8 * n)] << 8);
		if (calc_pec != data_pec)
		{
			ic[c_ic].com.rx_pec_match = 1;
		}
		else
			ic[c_ic].com.rx_pec_match = 0;
	}
	return (pec_error);
}

/*
 Shifts data in COMM register out over LTC6811 SPI/I2C port
 */
void LTC6811_stcomm()
{

	uint8 cmd[4];
	uint16 cmd_pec;

	cmd[0] = 0x07;
	cmd[1] = 0x23;
	cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (uint8) (cmd_pec >> 8);
	cmd[3] = (uint8) (cmd_pec);

	SPI2_CS(ON);
	spi_write_array(4, cmd);
	for (sint32 i = 0; i < 9; i++)
	{
		spi_read_byte(0xFF);
	}
	SPI2_CS(OFF);

}

//Helper function to set discharge bit in CFG register
void LTC6811_set_discharge(sint32 Cell, cell_asic ic[])
{
	for (sint32 i = 0; i < TOTAL_IC; i++)
	{
		if (Cell < 9)
		{
			ic[i].configa.tx_data[4] = ic[i].configa.tx_data[4] | (1 << (Cell - 1));
		}
		else if (Cell < 13)
		{
			ic[i].configa.tx_data[5] = ic[i].configa.tx_data[5] | (1 << (Cell - 9));
		}
	}
}

// Writes the pwm register
void LTC6811_wrpwm(uint8 pwmReg, cell_asic ic[])
{
	uint8 cmd[2];
	uint8 write_buffer[256];
	uint8 write_count = 0;
	uint8 c_ic = 0;
	if (pwmReg == 0)
	{
		cmd[0] = 0x00;
		cmd[1] = 0x20;
	}
	else
	{
		cmd[0] = 0x00;
		cmd[1] = 0x1C;
	}

	for (uint8 n = 0; n < TOTAL_IC; n++)
	{
		if (ic->isospi_reverse == true)
		{
			c_ic = n;
		}
		else
		{
			c_ic = TOTAL_IC - n - 1;
		}
		for (uint8 data = 0; data < 6; data++)
		{
			write_buffer[write_count] = ic[c_ic].pwm.tx_data[data];
			write_count++;
		}
	}
	write_68(cmd, write_buffer);
}

/*
 Reads pwm registers of a LTC6811 daisy chain
 */
int8_t LTC6811_rdpwm(uint8 pwmReg, cell_asic ic[])
{
	//const uint8 BYTES_IN_REG = 8;

	uint8 cmd[4];
	uint8 read_buffer[256];
	int8_t pec_error = 0;
	uint16 data_pec;
	uint16 calc_pec;
	uint8 c_ic = 0;

	if (pwmReg == 0)
	{
		cmd[0] = 0x00;
		cmd[1] = 0x22;
	}
	else
	{
		cmd[0] = 0x00;
		cmd[1] = 0x1E;
	}

	pec_error = read_68(cmd, read_buffer);
	for (uint8 n = 0; n < TOTAL_IC; n++)
	{
		if (ic->isospi_reverse == false)
		{
			c_ic = n;
		}
		else
		{
			c_ic = TOTAL_IC - n - 1;
		}
		for (sint32 byte = 0; byte < 8; byte++)
		{
			ic[c_ic].pwm.rx_data[byte] = read_buffer[byte + (8 * n)];
		}
		calc_pec = pec15_calc(6, &read_buffer[8 * n]);
		data_pec = read_buffer[7 + (8 * n)] | (read_buffer[6 + (8 * n)] << 8);
		if (calc_pec != data_pec)
		{
			ic[c_ic].pwm.rx_pec_match = 1;
		}
		else
			ic[c_ic].pwm.rx_pec_match = 0;
	}
	return (pec_error);
}

