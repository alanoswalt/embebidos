//  Copyright 2020 Jenifer, Alan
#include "gpio_start.h"
/**
 * Gpio setup
 * Setup of diferent GPIOS, specify in the name
 */
void gpio_setup(void) {
    gpio_init_analog_input(CLKA, PORTA , PIN1);
    gpio_init_pushpull_output(CLKA, PORTA, PIN5|PIN6|PIN7);
    gpio_init_pushpull_output(CLKC, PORTC, PIN13);
    gpio_init_usart_rx_tx(CLKA, PORTA, USART_TX, USART_RX);

    //  Eventos
    led_setup(LED_RCC, LED_PORT,LED_PIN1|LED_PIN2|LED_PIN3);
    button_setup(BUTTON_PIN_IRQ,BUTTON_PIN_IRQ1,BUTTON_PIN_IRQ2,BUTTON_PORT,
                BUTTON_PIN0|BUTTON_PIN1|BUTTON_PIN2,
                BUTTON_PIN_EXTI|BUTTON_PIN_EXTI1|BUTTON_PIN_EXTI2);
    
}

/*static void button_setup(void){
	//rcc_periph_clock_enable(BUTTON_RCC);
	rcc_periph_clock_enable(RCC_AFIO);

	nvic_enable_irq(BUTTON_PIN_IRQ);
    nvic_enable_irq(BUTTON_PIN_IRQ1);
    nvic_enable_irq(BUTTON_PIN_IRQ2);

	gpio_set_mode(BUTTON_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, BUTTON_PIN0|BUTTON_PIN1|BUTTON_PIN2);
    gpio_set(BUTTON_PORT,BUTTON_PIN0|BUTTON_PIN1|BUTTON_PIN2);

	exti_select_source(BUTTON_PIN_EXTI|BUTTON_PIN_EXTI1|BUTTON_PIN_EXTI2, BUTTON_PORT);
	exti_set_trigger(BUTTON_PIN_EXTI|BUTTON_PIN_EXTI1|BUTTON_PIN_EXTI2, EXTI_TRIGGER_FALLING);
	exti_enable_request(BUTTON_PIN_EXTI|BUTTON_PIN_EXTI1|BUTTON_PIN_EXTI2);
}*/

/**
 * Gpio toggle LEDS
 * Change the tresholds and represent it with leds
 */
void gpio_toggle_to_max(void) {
    gpio_clear_(PORTA, PIN7);
    gpio_set_(PORTA, PIN6|PIN5);
}
void gpio_toggle_to_min(void) {
    gpio_clear_(PORTA, PIN5);
    gpio_set_(PORTA, PIN6|PIN7);
}
void gpio_toggle_to_normal(void) {
    gpio_clear_(PORTA, PIN6);
    gpio_set_(PORTA, PIN7|PIN5);
}
