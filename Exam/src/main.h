//  Copyright 2020 Jenifer, Alan
#ifndef MAIN_SETUP_H_
#define MAIN_SETUP_H_
    //#include <libopencm3/stm32/exti.h>
    #include "gpio_start.h"
    //#include "dma_start.h"
    #include "uart_start.h"
    #include "tim_start.h"
    #include "adc_start.h"
    //#include "lcd_start.h"
    #include <FreeRTOS.h>
    #include <queue.h>
    #include <task.h>
    #include <timers.h>
    #include <event_groups.h>
    #include <semphr.h>

    #define FALSE 0
    #define TRUE 1
    #define RECV_SIZE 7


#endif
