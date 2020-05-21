//  Copyright 2020 Jenifer, Alan
#include "adc_i2c_init.h"

static I2C_config i2c; 
void ADC_init() {
    rcc_periph_clock_enable(RCC_GPIOC);    // I2C
    i2c_set_outputs(&i2c, GPIOC, GPIO15, GPIO14);
    i2c_set_thold(&i2c, 1);  /**< Hoja de datos dice que 0 ns y setup time min 100 ns */
    i2c_set_trise(&i2c,  2);  /**< En fast-mode son 300 ns */
    i2c_set_timeout(&i2c, 8);  /**<  */ 
    /**
     *  ADC slava address 0x48
     *  Modify config register 0x01
     *  Init configuration: continous convertion mode, bla bla 
     */
    i2c_write(&i2c, 0x48, 0x01, 0xC483);
    wait(50);
}
uint16_t get_adc_value(void) {
    return i2c_read(&i2c, 0x48, 0x00) * 205 / RESOLUTION;
}
void adc_off(void){
    /**
     * Nothing to do
    */
}
void adc_on(void){
    /**
     * Nothing to do
    */
}