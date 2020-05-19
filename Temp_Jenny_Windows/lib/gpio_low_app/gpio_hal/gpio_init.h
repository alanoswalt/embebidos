//  Copyright 2020 Jenifer, Alan
//  Libreries
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#ifndef GPIO_H_
#define GPIO_H_
//  Functions
extern void gpio_init_analog_input(uint32_t clk, uint32_t port, uint16_t pines);
extern void gpio_init_pushpull_output(uint32_t clk, uint32_t port, uint16_t pines);
extern void gpio_init_usart_rx_tx(uint32_t clk, uint32_t port, uint32_t usart_tx, uint32_t usart_rx);
extern void gpio_clear_(uint32_t port, uint16_t pines);
extern void gpio_set_(uint32_t port, uint16_t pines);
#endif
