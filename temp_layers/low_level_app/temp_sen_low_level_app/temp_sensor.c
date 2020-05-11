
#include "temp_sensor.h"

inline void temp_sensor(void){
    //apagar la bandera
    timer_clear_flag(TIM2,TIM_SR_UIF);
    //gpio_toggle(GPIO_PORT_LED,GPIO_LED);
    uint16_t adc;
    adc = read_adc(1) * 330 / 4095;
    
    if (adc < minTemp){
        //prender led amarillo A5
        gpio_clear(GPIOA,GPIO5);
        gpio_set(GPIOA,GPIO6);
        gpio_set(GPIOA,GPIO7);
        send_word("MinTemp: On\r\n");
        
    }else if(adc > maxTemp){
        //prender led rojo A7
        gpio_clear(GPIOA,GPIO7);
        gpio_set(GPIOA,GPIO5);
        gpio_set(GPIOA,GPIO6);
        send_word("MaxTemp: On\r\n");
    }else{
        //estado neutral, led blanco A6
        gpio_clear(GPIOA,GPIO6);
        gpio_set(GPIOA,GPIO5);
        gpio_set(GPIOA,GPIO7);
        send_word("MaxTemp: Off\r\n");
        send_word("MinTemp: Off\r\n");
        
    }
    
    if(j==4){ //Cuando j vale 4 han pasado 0.5 segundos porque la interrupcion del tim2 ocurre cada 0.1
        convertIntToChar(status_message,adc,8);
        j=0;
        
        //send UART
        send_word(status_message);
    }else j++;
}

void convertIntToChar(char *array, uint16_t value_int, char index){
    char t=2;
    do{
        array[index--]=(value_int%10)+48;
        value_int/=10;
    }while(t--);
    
}