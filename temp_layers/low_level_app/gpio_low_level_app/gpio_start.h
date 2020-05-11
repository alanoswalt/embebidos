#include "/home/alan/stm32f103c8t6/temp_layers/hal_low/gpio_setup/gpio_init.h"
#ifndef GPIO_SETUP_H_
#define GPIO_SETUP_H_

//Parametros
//#define GPIO_PORT_LED        GPIOC        // Builtin LED port
//#define GPIO_LED             GPIO13        // Builtin LED

#define GPIO_PIN_1_0    GPIO0
#define GPIO_PIN_1_1    GPIO1
#define GPIO_PIN_1_2    GPIO5
#define GPIO_PIN_1_3    GPIO6
#define GPIO_PIN_1_4    GPIO7

//Functions
extern void gpio_setup(void);


#endif