/*
 * lcd.c
 *
 *  Created on: Jun 29, 2023
 *      Author: kniacha
 */

#include "lcd.h"
#include "spi.h"

//	VARIABLES
static const uint16_t init_table[] = {
		CMD(ST7735S_FRMCTR1), 0x01, 0x2c, 0x2d,
		CMD(ST7735S_FRMCTR2), 0x01, 0x2c, 0x2d,
		CMD(ST7735S_FRMCTR3), 0x01, 0x2c, 0x2d, 0x01, 0x2c, 0x2d,
		CMD(ST7735S_INVCTR), 0x07,
		CMD(ST7735S_PWCTR1), 0xa2, 0x02, 0x84,
		CMD(ST7735S_PWCTR2), 0xc5,
		CMD(ST7735S_PWCTR3), 0x0a, 0x00,
		CMD(ST7735S_PWCTR4), 0x8a, 0x2a,
		CMD(ST7735S_PWCTR5), 0x8a, 0xee,
		CMD(ST7735S_VMCTR1), 0x0e,
		CMD(ST7735S_GAMCTRP1), 0x0f, 0x1a, 0x0f, 0x18, 0x2f, 0x28, 0x20, 0x22,
		0x1f, 0x1b, 0x23, 0x37, 0x00, 0x07, 0x02, 0x10,
		CMD(ST7735S_GAMCTRN1), 0x0f, 0x1b, 0x0f, 0x17, 0x33, 0x2c, 0x29, 0x2e,
		0x30, 0x30, 0x39, 0x3f, 0x00, 0x07, 0x03, 0x10,
		CMD(0xf0), 0x01,
		CMD(0xf6), 0x00,
		CMD(ST7735S_COLMOD), 0x05,
		CMD(ST7735S_MADCTL), 0xa0,
};

static uint16_t frame_buffer[LCD_WIDTH * LCD_HEIGHT];


//	FUNCTIONS

static void lcd_cmd(uint8_t cmd){
	//	Ustawienie linii dc na niska oznacza wysylanie komendy
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}


static void lcd_data(uint8_t data){
	//	Ustawienie linii dc na wysoka oznacza wysylanie danych
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &data, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}


static void lcd_send(uint16_t value){
	//	0x100 oznacza 9 bit liczby 16-bitowej (0 to wyslanie komendy a 1 to wyslanie danych)
	//	jesli iloczyn binarny bedzie rozny od zera to wykona sie warunek
	if(value & 0x100){
		lcd_cmd(value);
	}
	//	Mamy zero wiec wysylamy dane
	else{
		lcd_data(value);
	}
}


void lcd_init(void){
	int i;
	//	Display reset (setting low on lcd_rst pin resets the display)
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(100);

	//	sending starting setup in this loop (lcd_send can distinguish command and data)
	for(i=0; i<sizeof(init_table)/sizeof(uint16_t); i++){
		lcd_send(init_table[i]);
	}
	HAL_Delay(200);

	lcd_cmd(ST7735S_SLPOUT);
	HAL_Delay(120);

	//	turning on display
	lcd_cmd(ST7735S_DISPON);

}


static void lcd_data16(uint16_t value){

/*	lcd_data przyjmuje jako argument 1 bajt danych (jezeli podamy dane dwobajtowa to bardziej znaczace bity zostana pominiete)
 *	by wyslac wartosc 2. bajtowa trzeba oddzielnie wyslac po bajcie zaczynajac od najbardziej znaczacego bitu
 *	pierwsza linia wysyla bajt najbardziej znaczacych bitow
 *	druga linia wysyla pozostaly bajt
 */
	lcd_data(value>>8);
	lcd_data(value);
}



//	FUNCTION WHICH SETS THE DRAWING WINDOW

//	CASET - ustawia poczatkowa i koncowa kolumne rysowanego obszaru
//	RASET - ustawia poczatkowy i koncowy wiersz rysowanego obszaru
//	RAMWR - rozpoczyna przesylanie danych do zdefiniowanego obszaru
static void lcd_set_window(int x, int y, int width, int height){

//	Ustawienie dlugosci na osi x
	lcd_cmd(ST7735S_CASET);
//	Rejestr wymaga wartosci 16 bitowych jednak spi ogarnia tylko 8 bitow, wiec po to uzywamy funkcji lcd_data16
	lcd_data16(LCD_OFFSET_X + x);	//	punkt poczatkowy
	lcd_data16(LCD_OFFSET_X + x + width - 1);	//	punkt koncowy

//	Ustawienie dlugosci na osi y
	lcd_cmd(ST7735S_RASET);
	lcd_data16(LCD_OFFSET_Y + y);	//	punkt poczatkowy
	lcd_data16(LCD_OFFSET_Y + y + height - 1);	//	punkt koncowy
}


void lcd_put_pixel(int x, int y, uint16_t color){
	frame_buffer[x+y*LCD_WIDTH] = color;
}


void lcd_copy(void){
	lcd_set_window(0,0,LCD_WIDTH, LCD_HEIGHT);
	lcd_cmd(ST7735S_RAMWR);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit_DMA(&hspi2, (uint8_t*)frame_buffer, sizeof(frame_buffer));
}


void lcd_transfer_done(void){

	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}


bool lcd_is_busy(void){
	if(HAL_SPI_GetState(&hspi2)==HAL_SPI_STATE_BUSY){
		return true;
	}
	else{
		return false;
	}
}

