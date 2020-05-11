#include "/home/alan/stm32f103c8t6/temp_layers/hal_low/tim_setup/tim_init.h"
#include "/home/alan/stm32f103c8t6/temp_layers/low_level_app/temp_sen_low_level_app/temp_sensor.h"


#ifndef TIM_SETUP_H_
#define TIM_SETUP_H_

//Parametros
#define PESCALER 7200
#define PERIOD 1000



//Functions
extern void tim_setup(void);
//extern void tim2_isr(void);

#endif