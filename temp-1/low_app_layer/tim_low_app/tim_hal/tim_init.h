//  Copyright 2020 Jenifer, Alan
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/gpio.h>
#ifndef TIM_H_
#define TIM_H_
//  Functions
extern void tim_init(uint32_t clktim, uint32_t tim, uint32_t PRESC, uint32_t PERI);
extern void enable_irq(uint32_t tim, uint32_t tim_nvic);
extern void enable_pwm(uint32_t tim, uint8_t dutyCy, uint32_t out_ch);
#endif
