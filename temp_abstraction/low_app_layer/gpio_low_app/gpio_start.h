//  Copyright 2020 Jenifer, Alan
#include "gpio_hal/gpio_init.h"
#ifndef GPIO_SETUP_H_
#define GPIO_SETUP_H_
//  Parametros
#define PIN13   GPIO13  // Builtin LED
#define PIN0    GPIO0
#define PIN1    GPIO1
#define PIN5    GPIO5
#define PIN6    GPIO6
#define PIN7    GPIO7
#define PORTA   GPIOA
#define PORTC   GPIOC
#define CLKA    RCC_GPIOA
#define CLKC    RCC_GPIOC
#define USART_TX GPIO_USART1_TX
#define USART_RX GPIO_USART1_RX
//  Functions
extern void gpio_setup(void);
extern void gpio_toggle_to_max(void);
extern void gpio_toggle_to_min(void);
extern void gpio_toggle_to_normal(void);
#endif
