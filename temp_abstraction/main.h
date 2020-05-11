//  Copyright 2020 Jenifer, Alan
#ifndef MAIN_SETUP_H_
#define MAIN_SETUP_H_
    #include "low_app_layer/gpio_low_app/gpio_start.h"
    #include "low_app_layer/uart_low_app/uart_start.h"
    #include "low_app_layer/tim_low_app/tim_start.h"
    #define FALSE 0
    #define TRUE 1
    #define RECV_SIZE 7
    #define ADC 1
    #if ADC == 0
        #include "low_app_layer/adc_low_app/adc_start.h"
    #else
        #include "low_app_layer/i2c_low_app/adc_i2c_start.h"
    #endif
#endif
