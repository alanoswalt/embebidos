#include "tim3_start.h"

short duty_cycle = 0;
short time_cycle = 100;



//Cambiar Baud Rate
void tim3_setup(void){
    tim3_init(time_cycle, duty_cycle);
}