//  Copyright 2020 Jenifer, Alan
#include "uart_init.h"
/**
 * Uart init
 */
void uart_init(uint32_t clk, uint32_t usart_num, uint16_t usart_bd) {
    rcc_periph_clock_enable(clk);
    usart_set_baudrate(usart_num, usart_bd);
    usart_set_databits(usart_num, 8);
    usart_set_stopbits(usart_num, USART_STOPBITS_1);
    usart_set_mode(usart_num, USART_MODE_TX_RX);
    usart_set_parity(usart_num, USART_PARITY_NONE);
    usart_set_flow_control(usart_num, USART_FLOWCONTROL_NONE);
    usart_enable(usart_num);
}
/**
 * Uart setup of the irq
 */
void usart_nvic(uint32_t usart_irq, uint32_t usart_num) {
    nvic_enable_irq(usart_irq);
    usart_enable_rx_interrupt(usart_num);
}
/**
 * Uart clearign flag irq command
 */
void uart1_clear_flag(void) {
    USART1_SR = ~(1<<5);
}
