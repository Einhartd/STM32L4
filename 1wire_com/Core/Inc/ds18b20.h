/*
 * ds18b20.h
 *
 *  Created on: Aug 1, 2023
 *      Author: kniacha
 */

#pragma once

#include "stm32l4xx.h"

#define DS18B20_ROM_CODE_SIZE		8

// INITIALIZATION OF 1-WIRE
// RETURN - HAL_OK/HAL_ERROR
HAL_StatusTypeDef ds18b20_init(void);

// READ THE SENSOR ADDRESS AND COUNT THE CRC
// ROM_CODE - SPACE FOR STORING READ DATA
// RETURN - HAL_OK/HAL_ERROR
HAL_StatusTypeDef ds18b20_read_address(uint8_t* rom_code);

// START MEASURING TEMPERATURE
// ROM_CODE - SENSOR ADDRESS OR NULL
// RETURN - HAL_OK/HAL_ERROR
HAL_StatusTypeDef ds18b20_start_measure(const uint8_t* rom_code);

// GET THE TEMPERATURE
// ROM_CODE - SENSOR ADDRESS OR NULL
// RETURN - TEMPERATURE IN CELSIUS
float ds18b20_get_temp(const uint8_t* rom_code);
