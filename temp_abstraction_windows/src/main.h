//  Copyright 2020 Jenifer, Alan
#ifndef MAIN_SETUP_H_
#define MAIN_SETUP_H_
    #include "gpio_start.h"
    #include "uart_start.h"
    #include "tim_start.h"
    #define FALSE 0
    #define TRUE 1
    #define RECV_SIZE 7
    #define ADC 1
    #if ADC == 0
        #include "low_app_layer/adc_low_app/adc_start.h"
    #else
        #include "adc_i2c_start.h"
    #endif
#endif
