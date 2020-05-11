#include "/home/alan/stm32f103c8t6/temp_layers/hal_low/tim3_setup/tim3_init.h" //TIMER
#include "/home/alan/stm32f103c8t6/temp_layers/hal_low/adc_setup/adc_init.h" //ADC
#include "/home/alan/stm32f103c8t6/temp_layers/hal_low/gpio_setup/gpio_init.h" //RCC AND GPIO

#ifndef TEMP_SENSOR_SETUP_H_
#define TEMP_SENSOR_SETUP_H_



//Variables

extern char j; //0.5 seconds
extern uint16_t maxTemp, minTemp;
extern char status_message[];

//Functions
extern inline void temp_sensor(void);
void convertIntToChar(char *array, uint16_t value_int, char index);


#endif