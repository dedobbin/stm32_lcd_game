#include "lcd.h"

// Address depends on screen module. solder pads (usually labeled A0-A1-A2 ) can be used to change address
// The device 7 bits address value in data sheet must be shifted to the left (says HAL_I2C_Master_Transmit)
const int LCD_addr = 0x27 << 1;

#define PIN_RS    (1 << 0)
#define PIN_EN    (1 << 2)
#define BACKLIGHT (1 << 3)

void LCD_send(uint8_t data, uint8_t flags)
{
	while( HAL_I2C_IsDeviceReady(&hi2c1, LCD_addr, 1, HAL_MAX_DELAY) != HAL_OK);

	//uint8_t flags = 0;
    uint8_t up = data & 0xF0;
    uint8_t lo = (data << 4) & 0xF0;

    //TODO: taken from https://github.com/afiskon/stm32-i2c-lcd-1602/ but i don't see why data is send twice?
    ///Arduino-LiquidCrystal-I2C sends 2 bytes ??
    uint8_t data_arr[4];
    data_arr[0] = up|flags|BACKLIGHT|PIN_EN;
    data_arr[1] = up|flags|BACKLIGHT;
    data_arr[2] = lo|flags|BACKLIGHT|PIN_EN;
    data_arr[3] = lo|flags|BACKLIGHT;

    //HAL_StatusTypeDef res = HAL_I2C_Master_Transmit(&hi2c1, LCD_addr, data_arr, sizeof(data_arr), HAL_MAX_DELAY);
    HAL_I2C_Master_Transmit(&hi2c1, LCD_addr, data_arr, sizeof(data_arr), HAL_MAX_DELAY);
    HAL_Delay(5);
}


void LCD_data(uint8_t data)
{
	LCD_send(data, PIN_RS);
}


void LCD_command(uint8_t data)
{
	LCD_send(data, 0);
}

void LCD_text(char* str)
{
	while(*str){
		LCD_data((uint8_t) *str);
		str++;
	}
}

void LCD_home()
{
	LCD_command(0x2);
}

void LCD_home2()
{
	LCD_command(0xC0);
}

void LCD_init()
{
	LCD_command(0x38); // 2 lines, 5x7
	LCD_home();
	//LCD_command(0xC);  // Turn on (with cursor off)
	LCD_command(0x0E);  // Turn on (with cursor on)
	//LCD_command(0x0F); //Turn on (cursor blinking)
	LCD_command(0x1);	// Clear screen
}
