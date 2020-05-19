//  Copyright 2020 Jenifer, Alan

#ifndef ADC_SETUP_H_
#define ADC_SETUP_H_
#include <stdint.h>
//#include "adc_hal/adc_init.h"
/**
     * If WHICH_ADC is 1 the adc from the uC will be taken otherwise an external ADC
     * in this case ADS1115 driven by I2C protocol. PORTB PIN6 in use as SDA bus and 
     * PORTB PIN7 as SCL. You could modify this in i2c_Virtual.h file.
    */

#if defined(WHICH_ADC)
#define WHICH_ADC 2
#endif // WICH_ADC


#if WHICH_ADC == 1
#include "adc_hal/adc_per/adc_init.h"
#else
#include "adc_hal/adc_i2c/adc_i2c_init.h"
#endif
//  Functions
extern void ADC_setup(void);
extern uint16_t read_adc(void);
extern void adc_status(short st);
#endif
