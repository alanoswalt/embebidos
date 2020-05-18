#include "../ssd1306_oled/lcd.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#ifndef LCD_H_
#define LCD_H_
extern void lcd_setup();
extern void show_temp_lcd(char *str_temp);

#endif
    
