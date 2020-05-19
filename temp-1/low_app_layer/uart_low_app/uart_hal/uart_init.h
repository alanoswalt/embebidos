//  Copyright 2020 Jenifer, Alan
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#ifndef UART_H_
#define UART_H_
//  Functions
extern void uart_init(uint32_t clk, uint32_t usart_num, uint16_t usart_bd);
extern void usart_nvic(uint32_t usart_irq, uint32_t usart_num);
extern void uart1_clear_flag(void);
#endif
