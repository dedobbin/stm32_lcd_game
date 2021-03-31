#ifndef INC_LCD_H_
#define INC_LCD_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

void LCD_data(uint8_t data);
void LCD_command(uint8_t data);
void LCD_text(char* str);
void LCD_home();
void LCD_home2();
void LCD_init();

#endif /* INC_LCD_H_ */
