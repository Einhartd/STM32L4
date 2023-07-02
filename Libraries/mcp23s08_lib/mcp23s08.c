/*
 * mcp23s08.c
 *
 *  Created on: Jun 20, 2023
 *      Author: kniacha
 */

#include "spi.h"
#include "mcp23s08.h"

void mcp_reg_write(uint8_t reg, uint8_t value)
{
	uint8_t tx[3] = { MCP_WRITE, reg, value };

	HAL_GPIO_WritePin(IOEXP_CS_GPIO_Port, IOEXP_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, tx, 3, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(IOEXP_CS_GPIO_Port, IOEXP_CS_Pin, GPIO_PIN_SET);
}

uint8_t mcp_reg_read(uint8_t reg)
{
	uint8_t txrx[3] = { MCP_READ, reg, 0xff};

	HAL_GPIO_WritePin(IOEXP_CS_GPIO_Port, IOEXP_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2, txrx, txrx, 3, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(IOEXP_CS_GPIO_Port, IOEXP_CS_Pin, GPIO_PIN_SET);

	return txrx[2];
}

void MCP_GPIO_WritePin(float pin, int value){

	//	Calculating float number into binary
	float calc_pin = pow(2.0, pin);
	uint8_t bin_pin = (uint8_t)calc_pin;

	//	Setting up the direction for output
	mcp_reg_write(MCP_IODIR, ~(bin_pin));

	//	Setting up value of the output pin
	if(value==1){
		mcp_reg_write(MCP_OLAT, bin_pin);
	}
	else{
		mcp_reg_write(MCP_OLAT, ~(bin_pin));
	}

}


int MCP_GPIO_ReadPin(float pin){


	//	Calculating float number into binary
	float calc_pin = pow(2.0, pin);
	uint8_t bin_pin = (uint8_t)calc_pin;

	//	Checking whether pin is configured as input or output
	uint8_t reg = mcp_reg_read(MCP_IODIR);

	//	If it's input return error
	if((reg & bin_pin)!=0){
		return -1;
	}
	else{
	//	If it's output check for status
		reg = mcp_reg_read(MCP_OLAT);

		reg = reg & bin_pin;
		if(reg==0){
			return 0;
		}
		else{
			return 1;
		}
	}


	return reg;

}
