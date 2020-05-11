#include "tim_start.h"


//Change Baud Rate in header file
void tim_setup(void){
    tim_init(PESCALER, PERIOD);
}

/*void tim2_isr(void){
    temp_sensor();
}*/