#include "gpio_init.h" //Header that externs the function

//Function to chose the PINS to turn on of PORT A
void gpio_init(PIN0,PIN1,PIN2,PIN3,PIN4){
    rcc_periph_clock_enable(RCC_GPIOA);        // Enable GPIOA for ADC
    gpio_set_mode(GPIOA,
                  GPIO_MODE_INPUT,
                  GPIO_CNF_INPUT_ANALOG,
                  PIN0|PIN1);
    
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
                  PIN2|PIN3|PIN4);                // A5,A6,A7
    gpio_set(GPIOA,PIN2|PIN3|PIN4); //LEDS off
    
    
}