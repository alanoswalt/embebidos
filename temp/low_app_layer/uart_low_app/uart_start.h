//  Copyright 2020 Jenifer, Alan
#include "uart_hal/uart_init.h"
#ifndef UART_SETUP_H_
#define UART_SETUP_H_
//  Parametros
#define USARTNUM    USART1
#define USARTCKL    RCC_USART1
#define USARTNVIC   NVIC_USART1_IRQ
//  Functions
extern void uart_setup(void);
extern void uart1_stop_receiving(void);
extern void inline uart_putc(char ch);
extern uint16_t read_uart(void);
#endif
