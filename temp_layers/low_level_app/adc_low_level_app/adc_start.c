#include "adc_start.h"

uint16_t read_adc(uint8_t channel) {
    
    adc_set_sample_time(ADC_NUM,channel,ADC_SMPR_SMP_239DOT5CYC);
    adc_set_regular_sequence(ADC_NUM,1,&channel);
    adc_start_conversion_direct(ADC_NUM);
    while (!adc_eoc(ADC_NUM));
    return adc_read_regular(ADC_NUM);
}


//Function that calls anther function, where you can activate the desire ADC
void ADC_setup(void){
    //Call pins using ports A, primeros dos puertos ADC, ultimos 3 puertos leds. 
    ADC_init(ADC_NUM);

}