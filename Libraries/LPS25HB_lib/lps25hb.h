/*
 * lps25hb.h
 *
 *  Created on: Jul 10, 2023
 *      Author: kniacha
 */

#pragma once

#include "stm32l4xx.h"

// LPS25HB sensor initialization
// wake up and automatic measurement
// return - HAL_OK or HAL_ERROR
HAL_StatusTypeDef lps25hb_init(void);

// temperature reading
// return - result in degrees C
float lps25hb_read_temp(void);

// pressure reading
// return - result in hPa
float lps25hb_read_pressure(void);

// pressure sensor calibration
// value - 16-bit measurement correction
void lps25hb_set_calib(uint16_t value);
