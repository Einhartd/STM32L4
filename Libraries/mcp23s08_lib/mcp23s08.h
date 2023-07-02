/*
 * mcp23s08.h
 *
 *  Created on: Jun 20, 2023
 *      Author: kniacha
 */

#ifndef INC_MCP23S08_H_

//	Library required to use uint8_t
#include <stdint.h>
#include <math.h>

//	Commonly used MCP23S08 registers

//	DEVICE OPCODE
#define MCP_READ	0x41	//	Reading from mcp
#define MCP_WRITE	0x40	//	Writing to mcp

//	REGISTER ADDRESS
#define MCP_IODIR	0x00	//	Setting the direction of the pins
#define MCP_IPOL	0x01
#define MCP_GPINTEN 0x02
#define MCP_DEFVAL	0x03
#define MCP_INTCON	0x04
#define MCP_IOCON	0x05
#define MCP_GPPU	0x06	//	Enabling pull-up for inputs
#define MCP_INTF	0x07
#define MCP_INTCAP	0x08
#define MCP_GPIO	0x09	//	Reading the state of the inputs
#define MCP_OLAT	0x0A	//	Changing the state of the outputs

//	MCP23S08 Functions

//	Reading the value of the register
//	reg - read register
//	return - value of the read register
uint8_t mcp_reg_read(uint8_t reg);

//	Writing a new value to the register
// reg - the register we are writing to
// value - the value to be saved
// return - the function does not return any value
void mcp_reg_write(uint8_t reg, uint8_t value);

//	controlling the operation of a specific output
//	pin - number of pin to set up
//	value - choosing logic level for output (1-high, 0-low)
void MCP_GPIO_WritePin(float pin, int value);

//  function that checks the status of outputs (if pin is input function returns error (-1))
//  pin - number of pin to check status on
int MCP_GPIO_ReadPin(float pin);


#define INC_MCP23S08_H_



#endif /* INC_MCP23S08_H_ */
