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

//Parametros Eventos
/*#define LED_PORT GPIOA
#define LED_PIN1  GPIO5
#define LED_PIN2  GPIO6
#define LED_PIN3  GPIO7
#define BUTTON_RCC  RCC_GPIOB
#define BUTTON_PORT GPIOA
#define BUTTON_PIN0  GPIO0
#define BUTTON_PIN1  GPIO1
#define BUTTON_PIN2  GPIO2

#define BUTTON_PIN_IRQ NVIC_EXTI0_IRQ
#define BUTTON_PIN_EXTI EXTI0
#define BUTTON_PIN_IRQ1 NVIC_EXTI1_IRQ
#define BUTTON_PIN_EXTI1 EXTI1
#define BUTTON_PIN_IRQ2 NVIC_EXTI2_IRQ
#define BUTTON_PIN_EXTI2 EXTI2*/
//  Functions
extern void gpio_setup(void);
extern void gpio_toggle_to_max(void);
extern void gpio_toggle_to_max(void);
extern void gpio_toggle_to_max(void);
#endif
