/** Copyright 2020 Jenifer, Alan
*  All variables in this file are in the header.
*/
#include "adc_start.h"
uint16_t read_adc(void) {
    return get_adc_value();
}
/**< Configuration of the ADC with ADC_NUM specify in header*/
void ADC_setup(void) {
    ADC_init();
}
/**< Turn on/off ADC*/
void adc_status(short st) {
    if (st == 0) {
        adc_off();
    } else if (st == 1) {
        adc_on();
    }
}
