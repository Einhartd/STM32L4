/*
 * wire.h
 *
 *  Created on: Aug 1, 2023
 *      Author: kniacha
 */

#pragma once

#include "stm32l4xx.h"


// INITIALIZATION OF 1-WIRE
// START OF COUNTER USED FOR DELAY
// RETURN HAL_OK / HAL_ERROR
HAL_StatusTypeDef wire_init(void);

// SENDING RESET SEQUENCE VIA 1-WIRE
// RETURN - HAL_OK/HAL_ERROR
HAL_StatusTypeDef wire_reset(void);

// READING DATA VIA 1-WIRE
// READS 8 BITS AND COMBINES INTO A BYTE
// RETURN - READ BYTE
uint8_t wire_read(void);

// SEND DATA VIA 1-WIRE
// BYTE - BYTE TO SEND
void wire_write(uint8_t byte);

// COUNT THE CHECKSUM
// DATA - DATA BLOCK
// LEN - LENGTH OF DATA BLOCK
uint8_t wire_crc(const uint8_t* data, int len);
