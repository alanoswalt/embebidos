//  Copyright 2020 Jenifer, Alan
#ifndef ADC_I2C_H_
#define ADC_I2C_H_

#include "../../I2C_low_app/i2c_Virtual.h"
#define RESOLUTION 32768
extern void ADC_init(void);
extern uint16_t get_adc_value(void);
extern void adc_off(void);
extern void adc_on(void);

#endif