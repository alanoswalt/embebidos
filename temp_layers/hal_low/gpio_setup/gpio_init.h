//Libreries
#include "/home/alan/stm32f103c8t6/temp_layers/hal_low/rcc_header.h"
#include <libopencm3/stm32/gpio.h>

#ifndef GPIO_H_
#define GPIO_H_

//Parametros
#define GPIO_PORT_LED        GPIOC        // Builtin LED port
#define GPIO_LED        GPIO13        // Builtin LED

//Functions
extern void gpio_init(PIN0,PIN1,PIN2,PIN3,PIN4);


#endif