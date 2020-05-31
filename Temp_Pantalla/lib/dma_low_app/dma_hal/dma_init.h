//  Copyright 2020 Jenifer, Alan
//  Libreries
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/nvic.h>

#ifndef DMA_H_
#define DMA_H_
//  Functions
extern void dma_start(uint32_t clk, uint32_t dma_nvic_channel, uint32_t dma, uint32_t channel);

#endif