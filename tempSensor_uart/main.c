/* Author: Jenifer ,Alan
 Implement the system of 1. and use 2. to send the sampled data through UART to a PC terminal, while being able to configure temperature thresholds through commands sent from the terminal
 Points 1.[a-c] must be implemented. This includes sampling temperature every 0.1 seconds. The values of MaxTempTh and MinTempTh can be initially set to an arbitrary value that may change by configuring it.
 In NORMAL mode, every 0.5 seconds the blue pill will send status data to the PC terminal through UART. The status data must include current temperature (last sampled temperature is fine), values for Max and Min Temp Thresholds, and whether or not the Max or Min Temperatures are reached currently. All the data shall be printed in 1 line. A sample message can be:
 Temp: 25C, MaxTempTh: 28C, MinTempTh: 24C, MaxTemp: Off, MinTemp: Off
 Whenever a “config key” has been pressed, the program will enter CONFIG mode, where Max or Min Temp Thresholds will be configured. In this mode, all interruptions other than UART Rx must be disabled i.e. no sampling will be done, and no status will be sent to the UART Tx. One config key will represent the MaxTempTh and another the MinTempTh, a suggestion is to use “x” and “n” keys.
 If the MaxTempTh key was pressed the terminal will prompt the user with a message like:
 Set Max Temperature Threshold (C):
 Then the user will input the value in degrees Celsius and press . Upon recognizing the key, the value will be stored as the new MaxTempTh.
 If data entered is not valid e.g. 3az23, the blue pill will send an error message saying something like:
 Error, invalid data was sent. Please send a valid temperature (integer numbers)
 The same behaviour will happen for the MinTempTh
 *
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/timer.h>
#define RECV_SIZE 7

#define GPIO_PORT_LED        GPIOC        // Builtin LED port
#define GPIO_LED        GPIO13        // Builtin LED

char j =0; //0.5 seconds
char status_message[]="Temp: XXXC, MaxTempTh: 200C, MinTempTh: 100C, MaxTemp: Off, MinTemp: Off \r\n";
char minTempChar[]="100";
char maxTempChar[]="200";

char recv_word[RECV_SIZE] = "d";
unsigned char k=0;

uint16_t maxTemp=200, minTemp=100; //valores para probar con el pot

/*
 * Read ADC Channel
 */
static uint16_t read_adc(uint8_t channel) {
    
    adc_set_sample_time(ADC1,channel,ADC_SMPR_SMP_239DOT5CYC);
    adc_set_regular_sequence(ADC1,1,&channel);
    adc_start_conversion_direct(ADC1);
    while ( !adc_eoc(ADC1) );
    return adc_read_regular(ADC1);
}

void gpio_setup(void){
    rcc_periph_clock_enable(RCC_GPIOA);        // Enable GPIOA for ADC
    gpio_set_mode(GPIOA,
                  GPIO_MODE_INPUT,
                  GPIO_CNF_INPUT_ANALOG,
                  GPIO0|GPIO1);
    
    rcc_periph_clock_enable(RCC_GPIOC);        // Enable GPIOC for LED
    gpio_set_mode(GPIOC,
                  GPIO_MODE_OUTPUT_2_MHZ,
                  GPIO_CNF_OUTPUT_PUSHPULL,
                  GPIO13);                // PC13
    gpio_set(GPIO_PORT_LED,GPIO_LED);        // LED off
    
    //PINES PARA LOS LEDS
    gpio_set_mode(GPIOA,
                  GPIO_MODE_OUTPUT_2_MHZ,
                  GPIO_CNF_OUTPUT_PUSHPULL,
                  GPIO5|GPIO6|GPIO7);                // A5,A6,A7
    gpio_set(GPIOA,GPIO5|GPIO6|GPIO7); //LEDS off
    
    
}
void ADC_setup(void){
    // Initialize ADC:
    rcc_peripheral_enable_clock(&RCC_APB2ENR,RCC_APB2ENR_ADC1EN);
    adc_power_off(ADC1);
    rcc_peripheral_reset(&RCC_APB2RSTR,RCC_APB2RSTR_ADC1RST);
    rcc_peripheral_clear_reset(&RCC_APB2RSTR,RCC_APB2RSTR_ADC1RST);
    rcc_set_adcpre(RCC_CFGR_ADCPRE_PCLK2_DIV6);    // Set. 12MHz, Max. 14MHz
    adc_set_dual_mode(ADC_CR1_DUALMOD_IND);        // Independent mode
    adc_disable_scan_mode(ADC1);
    adc_set_right_aligned(ADC1);
    adc_set_single_conversion_mode(ADC1);
    //adc_set_sample_time(ADC1,ADC_CHANNEL_TEMP,ADC_SMPR_SMP_239DOT5CYC);
    //adc_set_sample_time(ADC1,ADC_CHANNEL_VREF,ADC_SMPR_SMP_239DOT5CYC);
    //adc_enable_temperature_sensor();
    adc_power_on(ADC1);
    adc_reset_calibration(ADC1);
    adc_calibrate_async(ADC1);
    while ( adc_is_calibrating(ADC1) );
}
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
        status_message[70]='n';
        status_message[71]=' ';
        
    }else if(adc > maxTemp){
        //prender led rojo A7
        gpio_clear(GPIOA,GPIO7);
        gpio_set(GPIOA,GPIO5);
        gpio_set(GPIOA,GPIO6);
        status_message[56]='n';
        status_message[57]=' ';
    }else{
        //estado neutral, led blanco A6
        gpio_clear(GPIOA,GPIO6);
        gpio_set(GPIOA,GPIO5);
        gpio_set(GPIOA,GPIO7);
        status_message[56]='f';
        status_message[57]='f';
        status_message[70]='f';
        status_message[71]='f';
        
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
void tim_setup(void){
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_clock_enable(RCC_AFIO);        // Need AFIO clock
    
    timer_disable_counter(TIM2);
    timer_disable_irq(TIM2,TIM_DIER_UIE);
    
    timer_set_mode(TIM2,
                   TIM_CR1_CKD_CK_INT,
                   TIM_CR1_CMS_EDGE,
                   TIM_CR1_DIR_UP);
    timer_set_prescaler(TIM2,7200);//
    
    timer_disable_preload(TIM2);
    timer_continuous_mode(TIM2);
    timer_set_period(TIM2,1000);//0.1s
    
    nvic_enable_irq(NVIC_TIM2_IRQ);
    timer_enable_irq(TIM2,TIM_DIER_UIE);
    timer_enable_counter(TIM2);
    
}
void usart1_isr(void){
    USART1_SR = ~(1<<5);
    char i=1;
    uint16_t aux=0;
    
    if (k<4){
        recv_word[k] = usart_recv(USART1);
    
    
    if (recv_word[k] == 'x') { //cambiar maxTemp
        timer_disable_counter(TIM2);
        adc_power_off(ADC1);
        send_word("\r\nSet Max Temperature Threshold (C): ");
        
    }else if (recv_word[k]=='n'){
        timer_disable_counter(TIM2);
        adc_power_off(ADC1);
        send_word("\r\nSet Min Temperature Threshold (C): ");
    }
    
    if(recv_word[k]=='\n'){ //enter
            gpio_clear(GPIOC,GPIO13);
            for(;i<k-1;i++){
                // send_word(recv_word[i]);
                if((recv_word[i]>= 48 && recv_word[i]<=57)){ // checar si son numeros
                    aux=aux*10+(recv_word[i]-48);
                }else{
                    send_word("\r\nError, invalid data was sent. Please send a valid temperature (integer numbers)\r\n");
                    recv_word[0]='f';
                    break;
                }
            }
            
            if (recv_word[0]=='x') {
                maxTemp=aux;
                convertIntToChar(maxTempChar,maxTemp,2);
                status_message[23]=maxTempChar[0];
                status_message[24]=maxTempChar[1];
                status_message[25]=maxTempChar[2];
            }else if(recv_word[0]=='n'){
                minTemp=aux;
                convertIntToChar(minTempChar,minTemp,2);
                status_message[40]=minTempChar[0];
                status_message[41]=minTempChar[1];
                status_message[42]=minTempChar[2];
            }
        
        k=255;
        adc_power_on(ADC1);
        timer_enable_counter(TIM2);
    }
    }else{
        send_word("\r\nError, only 3 digits are allowed\r\n");
        k=255;
        adc_power_on(ADC1);
        timer_enable_counter(TIM2);
    }
    k++;
}
static inline void uart_putc(char ch) {
    usart_send_blocking(USART1,ch);
}
void send_word(char * word) {
    
    while (*word!='\0') {
        uart_putc(*word++);
    }
}
static void uart_setup(void) {
    
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART1);
    
    // UART TX on PA9 (GPIO_USART1_TX)
    gpio_set_mode(GPIOA,
                  GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
                  GPIO_USART1_TX);
    
    // UART RX on PA10
    gpio_set_mode(GPIOA,
                  GPIO_MODE_INPUT,
                  GPIO_CNF_INPUT_PULL_UPDOWN,
                  GPIO_USART1_RX);

                
    
    usart_set_baudrate(USART1,9600);
    usart_set_databits(USART1,8);
    usart_set_stopbits(USART1,USART_STOPBITS_1);
    usart_set_mode(USART1,USART_MODE_TX_RX);
    usart_set_parity(USART1,USART_PARITY_NONE);
    usart_set_flow_control(USART1,USART_FLOWCONTROL_NONE);
    
    nvic_enable_irq(NVIC_USART1_IRQ);
    usart_enable_rx_interrupt(USART1);
    
    usart_enable(USART1);
}
int main(void) {
    
    rcc_clock_setup_in_hse_8mhz_out_72mhz();        // Use this for "blue pill"
    gpio_setup();
    ADC_setup();
    uart_setup();
    tim_setup();
    
    
    for (;;);
    
    return 0;
}

// End main.c