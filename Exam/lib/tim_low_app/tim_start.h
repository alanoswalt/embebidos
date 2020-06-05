//  Copyright 2020 Jenifer, Alan
#include <stdint.h>
#include "tim_hal/tim_init.h"
#ifndef TIM_SETUP_H_
#define TIM_SETUP_H_
//  Parametros
#define TIMNUM2 TIM2
#define CLKTIM2 RCC_TIM2
#define TIMNUM3 TIM3
#define CLKTIM3 RCC_TIM3
#define NVICTIM2 NVIC_TIM2_IRQ
#define TIM_CH3 TIM_OC3
//  Functions
extern void tim_setup(void);
extern void tim3_setup(void);
//extern void inline temp_sensor(void);
extern void tim_status(short st);
extern void tim3_duty_cycle(short dc);
#endif
