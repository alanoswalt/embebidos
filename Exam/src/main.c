#include "main.h"

int main(void) {
    /**
     * If WHICH_ADC is 1 the adc from the uC will be taken otherwise an external ADC
     * in this case ADS1115 driven by I2C protocol. PORTB PIN6 in use as SDA bus and 
     * PORTB PIN7 as SCL. You could modify this in i2c_Virtual.h file.
    */
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    //WHICH_ADC(1);
    //dma_init();
    gpio_setup();
    ADC_setup();
    uart_setup();
    tim_setup();
    tim3_setup();
    //lcd_setup();
    //led_setup();
    //button_setup();
    //lcd_fill(LINES);
    //xStatusQueue = xQueueCreate(15, sizeof(char));
    //xTempQueue = xQueueCreate(14,sizeof(char));
    //xQueue = xQueueCreate(10, sizeof(char));
    //button_event_group = xEventGroupCreate(); //even group regresa un handler que referencia al evento, este se llamara button_event_group
    //semaphore_hdl = xSemaphoreCreateMutex();
    //xTaskCreate(adc_status_changed,"ADC",100,NULL,configMAX_PRIORITIES-1,&xHandleADC);
    //xTaskCreate(send_word,"SEND",100,NULL,configMAX_PRIORITIES-1,NULL);
    //xTaskCreate(uart_status_changed,"UART",100,NULL,3,NULL);
	//xTaskCreate(debouncing,"DEBOUNCING",100,NULL,configMAX_PRIORITIES-1,NULL);
    //xTaskCreate(uart_print_data,"SERIAL_PRINT",100,NULL,1,NULL);
    //vTaskStartScheduler();
    for (;;);
	return 0;
    /**
    *  Pooling system always checking the flag of the interruptions.
    */
    /*while (1) {
        if (temp_handler == TRUE) {
            temp_handler = FALSE;
            adc_status_changed();
        }
        if (uart1_handler == TRUE) {
            uart1_handler = FALSE;
            uart_status_changed();
        }
    }*/
}