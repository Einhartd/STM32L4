/*
 * lcd.h
 *
 *  Created on: Jun 29, 2023
 *      Author: kniacha
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#define LCD_WIDTH 160
#define LCD_HEIGHT 128

//	DISPLAY REGISTERS
#define ST7735S_SLPOUT			0x11
#define ST7735S_DISPOFF			0x28
#define ST7735S_DISPON			0x29
#define ST7735S_CASET			0x2a
#define ST7735S_RASET			0x2b
#define ST7735S_RAMWR			0x2c
#define ST7735S_MADCTL			0x36
#define ST7735S_COLMOD			0x3a
#define ST7735S_FRMCTR1			0xb1
#define ST7735S_FRMCTR2			0xb2
#define ST7735S_FRMCTR3			0xb3
#define ST7735S_INVCTR			0xb4
#define ST7735S_PWCTR1			0xc0
#define ST7735S_PWCTR2			0xc1
#define ST7735S_PWCTR3			0xc2
#define ST7735S_PWCTR4			0xc3
#define ST7735S_PWCTR5			0xc4
#define ST7735S_VMCTR1			0xc5
#define ST7735S_GAMCTRP1		0xe0
#define ST7735S_GAMCTRN1		0xe1

//	DEFINE USED FOR SENDING DATA TO THE DISPLAY
//	co to kurwa jest?
#define CMD(x) ((x) | 0x100)

//	DEFINED COLORS FOR DISPLAY (INVERTED)
#define BLACK			0x0000
#define RED				0x00f8
#define GREEN			0xe007
#define BLUE			0x1f00
#define YELLOW			0xe0ff
#define MAGENTA			0x1ff8
#define CYAN			0xff07
#define WHITE			0xffff
#define SKY_BLUE		0x3f07
#define BROWN			0xE7B3

//	DISPLAY OFFSETS
#define LCD_OFFSET_X 1
#define LCD_OFFSET_Y 2

//	FUNCTION WHICH INITIALIZES DISPLAY
void lcd_init(void);

//	FUNCTION WHICH DRAWS ONE CHOSEN PIXAL IN CHOSEN COLOR
void lcd_put_pixel(int x, int y, uint16_t color);

//	FUNCTION WHICH SENDS BUFFER DATA
void lcd_copy(void);

void lcd_transfer_done(void);

bool lcd_is_busy(void);
