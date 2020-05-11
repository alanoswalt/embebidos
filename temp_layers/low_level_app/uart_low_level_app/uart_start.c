#include "uart_start.h"

//Change Baud Rate in header
void uart_setup(void){
    uart_init(BR);
}

/*void usart1_isr(void){
    display_dimer()
}*/