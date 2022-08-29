# stm32_lcd_game
Small game for STM32. Used NUCLEO-F446RE.

Amazing features such as lives, score and 1 button.

<br>

![gameplay](https://nop.koindozer.org/gh/stm32_lcd_game/lcd_game_vid3.gif) 

<br>

As seen in the gameplay (if you can see it!), controls are bit janky. Main goal was to get used to and experiment with the STM32 software, so i will overlook that for now. Also doesn't make proper use of the HD44780 LCD controller instruction set. More serious approach can be found [here](https://github.com/dedobbin/stm32_lcd).

Most files are generated with STM32CubeMX.  
Custom I2C logic for screen written in `Core/Src/lcd.c`.   
Custom game logic in `Core/Src/game.c`. 

## Circuit
(PA8 is D7 on NUCLEO-F446RE board.)


<br><br>

![circuit](https://nop.koindozer.org/gh/stm32_lcd_game/stm32_lcd2.png)
