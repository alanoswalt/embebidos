/** Copyright 2020 Jenifer ,Alan
 * Implement the system of 1. and use 2. to send the sampled data through UART to a PC terminal, while being able to configure temperature thresholds through commands sent from the terminal
 * Points 1.[a-c] must be implemented. This includes sampling temperature every 0.1 seconds. The values of MaxTempTh and MinTempTh can be initially set to an arbitrary value that may change by configuring it.
 * In NORMAL mode, every 0.5 seconds the blue pill will send status data to the PC terminal through UART. The status data must include current temperature (last sampled temperature is fine), values for Max and Min Temp Thresholds, and whether or not the Max or Min Temperatures are reached currently. All the data shall be printed in 1 line. A sample message can be:
 * Temp: 25C, MaxTempTh: 28C, MinTempTh: 24C, MaxTemp: Off, MinTemp: Off
 * Whenever a “config key” has been pressed, the program will enter CONFIG mode, where Max or Min Temp Thresholds will be configured. In this mode, all interruptions other than UART Rx must be disabled i.e. no sampling will be done, and no status will be sent to the UART Tx. One config key will represent the MaxTempTh and another the MinTempTh, a suggestion is to use “x” and “n” keys.
 * If the MaxTempTh key was pressed the terminal will prompt the user with a message like:
 * Set Max Temperature Threshold (C):
 * Then the user will input the value in degrees Celsius and press . Upon recognizing the key, the value will be stored as the new MaxTempTh.
 * If data entered is not valid e.g. 3az23, the blue pill will send an error message saying something like:
 * Error, invalid data was sent. Please send a valid temperature (integer numbers)
 * The same behaviour will happen for the MinTempTh
 *
 */
#include "main.h"
char minTempChar[] = "100";  /**< minTemp in char type to send by uart */
char maxTempChar[] = "200";  /**< maxTemp in char type to send by uart */
char recv_word[RECV_SIZE] = "d";  /**< array containing received characters  */
char status_message[] = "Temp: XXXC\r\n";  /**< Message with the current temp */
char mintemp_on[]= "MinTemp_On\r\n";
char mintemp_off[]="MinTemp_Off\r\n";
char maxtemp_on[]="MaxTemp_On\r\n";
char maxtemp_off[]="MaxTemp_Off\r\n";
unsigned char k = 0;  /**< position received character into recv_word */
uint16_t maxTemp = 90, minTemp = 50;  /**< temp thresholds */
char j = 0;  /**< increment every 0.1 sec up to 0.5*/
short duty_cycle = 0;
//static I2C_config i2c; 
/**
 * Flags for occured interruptions
 */
uint8_t volatile temp_handler = FALSE;
uint8_t volatile uart1_handler = FALSE;
/**
 *  A Temp sensor. Has the hanlder to do every proces of the ADC.
 */
void inline temp_sensor(void) {
    temp_handler = TRUE;
}
/**
 *  Uart_irq flag. Has the hanlder to do every proces of the ADC.
 */
void inline uart1_stop_receiving(void) {
    uart1_handler = TRUE;
}
////////////////////////RTOS HANDLERS//////////////
/**
 * RTOS
 */
QueueHandle_t xQueue;
EventGroupHandle_t button_event_group; //Crear el handler del evento, typo de dato handler
SemaphoreHandle_t swtimer_semaphore_hdl;

extern void vApplicationStackOverflowHook(
	xTaskHandle *pxTask,
	signed portCHAR *pcTaskName);

void vApplicationStackOverflowHook(
  xTaskHandle *pxTask __attribute((unused)),
  signed portCHAR *pcTaskName __attribute((unused))
) {
	for(;;);	// Loop forever here..
}
void exti0_isr(void){
    BaseType_t xHigherPriorityTaskWoken;
	exti_reset_request(BUTTON_PIN_EXTI); //
    //Aqui se setea el vit al evento, el ultimo es para despert al task con mayor prioridad
    xEventGroupSetBitsFromISR(button_event_group,BUTTON_EVENT_BIT0,&xHigherPriorityTaskWoken); 
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
void exti1_isr(void){
    BaseType_t xHigherPriorityTaskWoken;
	exti_reset_request(BUTTON_PIN_EXTI1); //
    //Aqui se setea el vit al evento, el ultimo es para despert al task con mayor prioridad
    xEventGroupSetBitsFromISR(button_event_group,BUTTON_EVENT_BIT1,&xHigherPriorityTaskWoken); 
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
void exti2_isr(void){
    BaseType_t xHigherPriorityTaskWoken;
	exti_reset_request(BUTTON_PIN_EXTI2); //
    //Aqui se setea el vit al evento, el ultimo es para despert al task con mayor prioridad
    xEventGroupSetBitsFromISR(button_event_group,BUTTON_EVENT_BIT2,&xHigherPriorityTaskWoken); 
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*static void led_setup(void){
	rcc_periph_clock_enable(LED_RCC);
	gpio_set_mode(LED_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL, LED_PIN1|LED_PIN2|LED_PIN3);
}

static void button_setup(void){
	//rcc_periph_clock_enable(BUTTON_RCC);
	rcc_periph_clock_enable(RCC_AFIO);

	nvic_enable_irq(BUTTON_PIN_IRQ);
    nvic_enable_irq(BUTTON_PIN_IRQ1);
    nvic_enable_irq(BUTTON_PIN_IRQ2);

	gpio_set_mode(BUTTON_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, BUTTON_PIN0|BUTTON_PIN1|BUTTON_PIN2);
    gpio_set(BUTTON_PORT,BUTTON_PIN0|BUTTON_PIN1|BUTTON_PIN2);

	exti_select_source(BUTTON_PIN_EXTI|BUTTON_PIN_EXTI1|BUTTON_PIN_EXTI2, BUTTON_PORT);
	exti_set_trigger(BUTTON_PIN_EXTI|BUTTON_PIN_EXTI1|BUTTON_PIN_EXTI2, EXTI_TRIGGER_FALLING);
	exti_enable_request(BUTTON_PIN_EXTI|BUTTON_PIN_EXTI1|BUTTON_PIN_EXTI2);
}*/
////////////////////////////////////////////

/**
 * Recive an int and transform it into a char
 * @param array for store the values.
 * @param value_int value reive form the ADC.
 * @param index position in the array
 * @param t times the process will ocurre
 */
void convertIntToChar(char *array, uint16_t value_int, char index) {
    char t = 2;
    do {
        array[index--]=(value_int%10)+48;
        value_int/=10;
    }while(t--);
}
/**
 * Send each part form the word to uart until the end of line.
 * @see uart_putc()
 * @param word word to send from uart.
 */
void send_word(char * word) {
    while (*word != '\0') {
        uart_putc(*word++);
    }
}
/**
 * Change the behavior of temperature LEDs.
 * @see gpio_toggle_to_min()
 * @see gpio_toggle_to_normal()
 * @see gpio_toggle_to_max()
 * @param flag indication of what process to do.
 */
void leds_dinamic(uint8_t flag) {
    if (flag == 1) {
        gpio_toggle_to_min();
    } else if (flag == 2) {
        gpio_toggle_to_normal();
    } else if (flag == 3) {
        gpio_toggle_to_max();
    }
}
static void debouncing(void *args __attribute((unused))) {
    EventBits_t event_bits;
    for (;;) {
        event_bits = xEventGroupWaitBits(
                        button_event_group,
                        BUTTON_EVENT_BIT0|BUTTON_EVENT_BIT1|BUTTON_EVENT_BIT2,
                        pdFALSE, //No clear on exit
                        pdFALSE, //Wait for ANY bit to be set
                        500);
        if(event_bits!=0){ //A Button was pressed
            vTaskDelay(pdMS_TO_TICKS(100)); //Wait for 10ms
            if(event_bits & BUTTON_EVENT_BIT0){ //The Button was pressed
                tim_status(0);
                adc_status(0);
                gpio_toggle(LED_PORT,LED_PIN1);
                send_word("Button_one\r\n");
                //Clear button event flag that may have been set again during deboucing delay
                vTaskDelay(pdMS_TO_TICKS(100)); //Wait for 10ms
                xEventGroupClearBits(button_event_group,BUTTON_EVENT_BIT0); 
                tim_status(1);
                adc_status(1);
            }
            if(event_bits & BUTTON_EVENT_BIT1){ //The Button was pressed
                tim_status(0);
                adc_status(0);
                gpio_toggle(LED_PORT,LED_PIN2);
                send_word("Button_two\r\n");
                //Clear button event flag that may have been set again during deboucing delay
                vTaskDelay(pdMS_TO_TICKS(100)); //Wait for 10ms
                xEventGroupClearBits(button_event_group,BUTTON_EVENT_BIT1); 
                tim_status(1);
                adc_status(1);
            }
            if(event_bits & BUTTON_EVENT_BIT2){ //The Button was pressed
                tim_status(0);
                adc_status(0);
                gpio_toggle(LED_PORT,LED_PIN3);
                send_word("Button_three\r\n");
                //Clear button event flag that may have been set again during deboucing delay
                vTaskDelay(pdMS_TO_TICKS(100)); //Wait for 10ms
                xEventGroupClearBits(button_event_group,BUTTON_EVENT_BIT2);
                tim_status(1);
                adc_status(1); 
            }
        }
    }
}
/**
 * Information recive from ADC has diferent effects.
 * @see read adc()
 * @see leds_dinamic()
 * @see send_word()
 * @see convertIntToChar()
 * @param adc value that has the number form the adc.
 */
void adc_status_changed(void *arg __attribute__((unused))) {
    uint16_t adc;
    while(1){
        if(temp_handler == TRUE){
            temp_handler = FALSE;
            adc = read_adc();
            if (adc < minTemp) {
                leds_dinamic(1);
                xQueueSend(xQueue, &mintemp_on, 10);
                send_word(mintemp_on);
            } else if (adc > maxTemp) {
                leds_dinamic(3);
                xQueueSend(xQueue, &maxtemp_on, 10);
                send_word(maxtemp_on);
            } else {
                leds_dinamic(2);
                xQueueSend(xQueue, &maxtemp_off, 10);
                xQueueSend(xQueue, &mintemp_off, 10);
                send_word(maxtemp_off);
                send_word(mintemp_off);
            }
            if (j == 4) {
                convertIntToChar(status_message, adc, 8);
                j = 0;
                xQueueSend(xQueue, &status_message, 10);
                send_word(status_message);
                show_temp_lcd(status_message);     
            } else {
                j++;
            }
        }  
    }
}
/**
 * Information recive from ADC has diferent effects.
 * @see tim_status()
 * @see adc_status(()
 * @see read_uart()
 * @see tim3_duty_cycle()
 * @see convertIntToChar()
 * @see send_word()
 * @param i value in postition of the mesage of the UART.
 * @param aux value to change de dimming of the LED
 */
void uart_status_changed(void *arg __attribute__((unused))) {
    while(1) {
        char i = 0;
        uint16_t aux = 0;
        if (uart1_handler == TRUE) {
            uart1_handler = FALSE;
            recv_word[k] = read_uart();  //  usart_recv(USART1);
            if (recv_word[k] == 'q') {  //  Aumentar duty_cycle
                tim_status(0);
                adc_status(0);
                for (; i < k; i++) {
                    aux = aux*10+(recv_word[i]-48);
                }
                duty_cycle = aux;
                if (duty_cycle <= 100 && duty_cycle >= 0) {
                    tim3_duty_cycle(duty_cycle);
                    //  timer_set_oc_value(TIM3,TIM_OC3,duty_cycle);
                    send_word("okq");
                }
                k = 255;
                adc_status(1);
                tim_status(1);
            } else if (recv_word[k] == 'w') {
                tim_status(0);
                adc_status(0);
                for (; i < k; i++) {
                    aux = aux*10+(recv_word[i]-48);
                }
                duty_cycle = aux;
                if (duty_cycle <= 100 && duty_cycle >= 0) {
                    tim3_duty_cycle(duty_cycle);
                    send_word("okw\r\n");
                }
                k = 255;
                adc_status(1);
                tim_status(1);
            }else if (recv_word[k] == 'x') {  //  cambiar maxTemp
                gpio_toggle(GPIOC, GPIO13);
                tim_status(0);
                adc_status(0);
                for (; i < k; i++) {
                    aux = aux*10+(recv_word[i]-48);
                }
                maxTemp = aux;
                convertIntToChar(maxTempChar, maxTemp, 13);
                send_word(maxTempChar);
                k = 255;
                adc_status(1);
                tim_status(1);
            } else if (recv_word[k] == 'n') {
                tim_status(0);
                adc_status(0);
                for (; i < k; i++) {
                    aux = aux*10+(recv_word[i]-48);
                }
                minTemp = aux;
                convertIntToChar(minTempChar, minTemp, 13);
                send_word(minTempChar);
                k = 255;
                adc_status(1);
                tim_status(1);
            }
            k++;
        }
    } 
}
int main(void) {
    /**
     * If WHICH_ADC is 1 the adc from the uC will be taken otherwise an external ADC
     * in this case ADS1115 driven by I2C protocol. PORTB PIN6 in use as SDA bus and 
     * PORTB PIN7 as SCL. You could modify this in i2c_Virtual.h file.
    */
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    WHICH_ADC(2);
    gpio_setup();
    ADC_setup();
    uart_setup();
    tim_setup();
    tim3_setup();
    lcd_setup();
    //led_setup();
    //button_setup();
    //lcd_fill(LINES);
    xQueue = xQueueCreate(1, sizeof(char));
    button_event_group = xEventGroupCreate(); //even group regresa un handler que referencia al evento, este se llamara button_event_group
    swtimer_semaphore_hdl = xSemaphoreCreateMutex();
    xTaskCreate(adc_status_changed,"ADC",100,NULL,configMAX_PRIORITIES-1,NULL);
    xTaskCreate(uart_status_changed,"UART",100,NULL,3,NULL);
	xTaskCreate(debouncing,"DEBOUNCING",100,NULL,configMAX_PRIORITIES-1,NULL);
    vTaskStartScheduler();
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
// End main.c
