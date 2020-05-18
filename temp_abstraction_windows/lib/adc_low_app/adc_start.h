//  Copyright 2020 Jenifer, Alan
#include <stdint.h>
#include "adc_hal/adc_init.h"
#ifndef ADC_SETUP_H_
#define ADC_SETUP_H_
//  Parametros
#define ADC_NUM    ADC1
#define ADC_CHANNEL 1
#define ADC_RESOLUT 4096
//  Functions
extern void ADC_setup(void);
extern uint16_t read_adc();
extern void adc_status(short st);
#endif
