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

    //Eventos
    /*gpio_init_events_led(PORTA,LED_PIN1|LED_PIN2|LED_PIN3);
    gpio_init_events_bottos();*/
}
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
