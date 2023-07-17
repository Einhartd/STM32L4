/*
 * seg7.h
 *
 *  Created on: Jul 13, 2023
 *      Author: kniacha
 */

#pragma once


#include <stdint.h>

// show digit on display
// value - digit to be displayed
void seg7_show_digit(uint32_t value);

// Auxiliary function
// Change the active display
void seg7_update(void);
