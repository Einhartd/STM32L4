/*
 * eeprom.h
 *
 *  Created on: 5 lip 2023
 *      Author: kniacha
 */

#pragma once

#include "stm32l4xx.h"

// The delay needed to finish recording
// The function automatically implements the delay only when it is needed
void eeprom_wait(void);

// Reading data from the EEPROM
// addr - initial data address
// data - buffer for the data to be read
// size - number of bytes to be read
// return - HAL_OK if read was successful, wpp. error
HAL_StatusTypeDef eeprom_read(uint32_t addr, void* data, uint32_t size);


// Writing data to the EEPROM
// addr - initial address of the data
// data - buffer for writing data
// size - number of bytes to be written
// return - HAL_OK if write succeeds, otherwise error
HAL_StatusTypeDef eeprom_write(uint32_t addr, const void* data, uint32_t size);
