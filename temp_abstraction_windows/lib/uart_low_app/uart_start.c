//  Copyright 2020 Jenifer, Alan
#include "uart_start.h"
/**
 * Uart setup
 * Creating UART init and nvic
 */
void uart_setup(void) {
    uart_init(USARTCKL, USARTNUM, 9600);
    usart_nvic(USARTNVIC, USARTNUM);
}
/**
 * Uart irq
 * Clear flag
 */
void usart1_isr(void) {
    uart1_clear_flag();
    uart1_stop_receiving();
}
/**
 * Uart send 
 */
void inline uart_putc(char ch) {
    usart_send_blocking(USART1, ch);
}
/**
 * Uart read the information
 */
uint16_t read_uart(void) {
    return usart_recv(USARTNUM);
}
