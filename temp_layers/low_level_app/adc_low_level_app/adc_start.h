#include <stdint.h>
#include "/home/alan/stm32f103c8t6/temp_layers/hal_low/adc_setup/adc_init.h"
#ifndef ADC_SETUP_H_
#define ADC_SETUP_H_

//Parametros
#define ADC_NUM    ADC1

//Functions
extern void ADC_setup(void);
extern uint16_t read_adc(uint8_t channel); 


#endif