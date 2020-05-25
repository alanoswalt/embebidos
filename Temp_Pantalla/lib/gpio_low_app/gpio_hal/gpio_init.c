//  Copyright 2020 Jenifer, Alan
#include "gpio_init.h"
/**
 * GPIO - ADC
 */
void gpio_init_analog_input(uint32_t clk, uint32_t port, uint16_t pines) {
    rcc_periph_clock_enable(clk);        // Enable GPIOA for ADC
    gpio_set_mode(port,
                  GPIO_MODE_INPUT,
                  GPIO_CNF_INPUT_ANALOG,
                  pines);
}
/**
 * GPIO - LEDS
 */
void gpio_init_pushpull_output(uint32_t clk, uint32_t port, uint16_t pines) {
    rcc_periph_clock_enable(clk);
    gpio_set_mode(port,
                  GPIO_MODE_OUTPUT_2_MHZ,
                  GPIO_CNF_OUTPUT_PUSHPULL,
                  pines);                //  A5,A6,A7
    gpio_set(port, pines);  //  Current state: off
}
/**
 * GPIO - LEDS - EVENTS
 */
void led_setup(uint32_t clk, uint32_t port, uint16_t pines){
	rcc_periph_clock_enable(clk);
	gpio_set_mode(port, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, pines);
}

/**
 * GPIO - BUTTONS - EVENTS
 */
void button_setup(uint32_t exti_0,uint32_t exti_1,uint32_t exti_2, uint32_t port, uint16_t pines,uint16_t exti_b){
	//rcc_periph_clock_enable(BUTTON_RCC);
	rcc_periph_clock_enable(RCC_AFIO);

	nvic_enable_irq(exti_0);
    nvic_enable_irq(exti_1);
    nvic_enable_irq(exti_2);

	gpio_set_mode(port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, pines);
    gpio_set(port,pines);

	exti_select_source(exti_b, port);
	exti_set_trigger(exti_b, EXTI_TRIGGER_FALLING);
	exti_enable_request(exti_b);
}


/**
 * GPIO - UART
 * Set the configuration for TX and RX
 */
void gpio_init_usart_rx_tx(uint32_t clk, uint32_t port, uint32_t usart_tx, uint32_t usart_rx) {
    rcc_periph_clock_enable(clk);
    gpio_set_mode(port,
                  GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
                  usart_tx);  /**< UART TX on PA9 (GPIO_USART1_TX)*/
    gpio_set_mode(port,
                  GPIO_MODE_INPUT,
                  GPIO_CNF_INPUT_PULL_UPDOWN,
                  usart_rx);  /**< UART RX on PA10*/
}
/**
 * GPIO clear or set programs
 */
void gpio_clear_(uint32_t port, uint16_t pines) {
    gpio_clear(port, pines);
}
void gpio_set_(uint32_t port, uint16_t pines) {
    gpio_set(port, pines);
}
