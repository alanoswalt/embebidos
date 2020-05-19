//  Copyright 2020 Jenifer, Alan
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/adc.h>
#ifndef ADC_H_
#define ADC_H_
#define ADC_NUM    ADC1
#define ADC_CHANNEL (uint8_t)1
#define RESOLUTION (uint16_t)4096 /**< 12 BITS, 2^16 */
//  Functions
/*void ADC_init(void);
void adc_off_(void);
void adc_on_(void);
uint16_t get_adc_value(void); */
#endif