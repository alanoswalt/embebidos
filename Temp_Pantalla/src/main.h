//  Copyright 2020 Jenifer, Alan
#ifndef MAIN_SETUP_H_
#define MAIN_SETUP_H_
    #include <libopencm3/stm32/exti.h>
    #include "gpio_start.h"
    #include "uart_start.h"
    #include "tim_start.h"
    #include "adc_start.h"
    #include "lcd_start.h"
    #include <FreeRTOS.h>
    #include <queue.h>
    #include <task.h>
    #include <timers.h>
    #include <event_groups.h>

    #define FALSE 0
    #define TRUE 1
    #define RECV_SIZE 7

    //Eventos
    #define BUTTON_EVENT_BIT0 (1 << 0)
    #define BUTTON_EVENT_BIT1 (1 << 1)
    #define BUTTON_EVENT_BIT2 (1 << 2)  
    #define LED_PORT GPIOB
    #define LED_PIN1  GPIO0
    #define LED_PIN2  GPIO1
    #define LED_PIN3  GPIO12
    #define LED_RCC  RCC_GPIOB

    #define BUTTON_RCC  RCC_GPIOA
    #define BUTTON_PORT GPIOA
    #define BUTTON_PIN0  GPIO0
    #define BUTTON_PIN1  GPIO1
    #define BUTTON_PIN2  GPIO2

    #define BUTTON_PIN_IRQ NVIC_EXTI0_IRQ
    #define BUTTON_PIN_EXTI EXTI0
    #define BUTTON_PIN_IRQ1 NVIC_EXTI1_IRQ
    #define BUTTON_PIN_EXTI1 EXTI1
    #define BUTTON_PIN_IRQ2 NVIC_EXTI2_IRQ
    #define BUTTON_PIN_EXTI2 EXTI2

#endif
