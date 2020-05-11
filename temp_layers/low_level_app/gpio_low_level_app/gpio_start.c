#include "gpio_start.h"

void gpio_setup(void){
    //Call pins using ports A, primeros dos puertos ADC, ultimos 3 puertos leds. 
    gpio_init(GPIO_PIN_1_0,GPIO_PIN_1_1,GPIO_PIN_1_2,GPIO_PIN_1_3,GPIO_PIN_1_4);

}