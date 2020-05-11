#include <stdint.h>
//Includes duty cycle and time cycle
#include "/home/alan/stm32f103c8t6/temp_layers/low_level_app/tim3_low_level_app/tim3_start.h" 
#include "/home/alan/stm32f103c8t6/temp_layers/hal_low/gpio_setup/gpio_init.h" //RCC AND GPIO
#include "stm32f103c8t6/temp_layers/hal_low/adc_setup/adc_init.h" //ADC
#include "/home/alan/stm32f103c8t6/temp_layers/hal_low/uart_setup/uart_init.h" //RCC, GPIO, NVIC, UART
#include "/home/alan/stm32f103c8t6/temp_layers/hal_low/tim3_setup/tim3_init.h" //TIMER

#ifndef ISR_SETUP_H_
#define ISR_SETUP_H_

#define RECV_SIZE 7

//Variables
extern char j; //0.5 seconds
extern char status_message[];
extern char minTempChar[];
extern char maxTempChar[];

extern char recv_word[RECV_SIZE];
extern unsigned char k;

extern uint16_t maxTemp, minTemp;

//Functions
extern void tim2_isr(void);
extern void convertIntToChar(char *array, uint16_t value_int, char index);
extern void usart1_isr(void);
extern inline void uart_putc(char ch);
extern void send_word(char * word);


#endif