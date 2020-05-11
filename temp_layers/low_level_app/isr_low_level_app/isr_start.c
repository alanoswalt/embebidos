#include "isr_start.h"

char j =0; //0.5 seconds
char status_message[]="Temp: XXXC\r\n";
char minTempChar[]="MinTempTh: 100C\r\n";
char maxTempChar[]="MaxTempTh: 200C\r\n";

char recv_word[RECV_SIZE] = "d";
unsigned char k=0;

uint16_t maxTemp=200, minTemp=100; //valores para probar con el pot

void tim2_isr(void){
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

void usart1_isr(void){
    USART1_SR = ~(1<<5);
    char i=0;
    
    uint16_t aux=0;
    
   
    recv_word[k] = usart_recv(USART1);
    
    if (recv_word[k] == 'q') { //Aumentar duty_cycle
        timer_disable_counter(TIM2);
        adc_power_off(ADC1);
        
        for(;i<k;i++){
            aux=aux*10+(recv_word[i]-48);
        }
        duty_cycle=aux;
        
        if(duty_cycle<=100 && duty_cycle>=0){
            timer_set_oc_value(TIM3,TIM_OC3,duty_cycle);
            send_word("okq");
            
        }
        
        k=255;
        adc_power_on(ADC1);
        timer_enable_counter(TIM2);
        
    }else if (recv_word[k]=='w'){ //w
        timer_disable_counter(TIM2);
        adc_power_off(ADC1);
        
        for(;i<k;i++){
            aux=aux*10+(recv_word[i]-48);
        }
        duty_cycle=aux;
        if(duty_cycle<=100 && duty_cycle>=0){
            timer_set_oc_value(TIM3,TIM_OC3,duty_cycle);
            send_word("okw\r\n");
        }
        
        k=255;
        adc_power_on(ADC1);
        timer_enable_counter(TIM2);
    }
    
    else if (recv_word[k] == 'x') { //cambiar maxTemp
        gpio_toggle(GPIOC, GPIO13);
        
        timer_disable_counter(TIM2);
        adc_power_off(ADC1);
        
        for(;i<k;i++){
            aux=aux*10+(recv_word[i]-48);
        }
        maxTemp=aux;
        convertIntToChar(maxTempChar,maxTemp,13);
        //status_message[23]=maxTempChar[0];
        //status_message[24]=maxTempChar[1];
        //status_message[25]=maxTempChar[2];
        send_word(maxTempChar);
        k=255;
        adc_power_on(ADC1);
        timer_enable_counter(TIM2);
        
        
    }else if (recv_word[k]=='n'){
        timer_disable_counter(TIM2);
        adc_power_off(ADC1);
        for(;i<k;i++){
            aux=aux*10+(recv_word[i]-48);
        }
        minTemp=aux;
        convertIntToChar(minTempChar,minTemp,13);
        send_word(minTempChar);
        
        k=255;
        adc_power_on(ADC1);
        timer_enable_counter(TIM2);
    }
    
    k++;
}

inline void uart_putc(char ch) {
    usart_send_blocking(USART1,ch);
}
void send_word(char * word) {
    
    while (*word!='\0') {
        uart_putc(*word++);
    }
}