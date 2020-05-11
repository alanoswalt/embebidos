#include "adc_init.h"

/* 
 * Read ADC Channel
 */

void ADC_init(ADC_NUM_SELECT){
    // Initialize ADC:
    rcc_peripheral_enable_clock(&RCC_APB2ENR,RCC_APB2ENR_ADC1EN);
    adc_power_off(ADC_NUM_SELECT);
    rcc_peripheral_reset(&RCC_APB2RSTR,RCC_APB2RSTR_ADC1RST);
    rcc_peripheral_clear_reset(&RCC_APB2RSTR,RCC_APB2RSTR_ADC1RST);
    rcc_set_adcpre(RCC_CFGR_ADCPRE_PCLK2_DIV6);    // Set. 12MHz, Max. 14MHz
    adc_set_dual_mode(ADC_CR1_DUALMOD_IND);        // Independent mode
    adc_disable_scan_mode(ADC_NUM_SELECT);
    adc_set_right_aligned(ADC_NUM_SELECT);
    adc_set_single_conversion_mode(ADC_NUM_SELECT);
    //adc_set_sample_time(ADC1,ADC_CHANNEL_TEMP,ADC_SMPR_SMP_239DOT5CYC);
    //adc_set_sample_time(ADC1,ADC_CHANNEL_VREF,ADC_SMPR_SMP_239DOT5CYC);
    //adc_enable_temperature_sensor();
    adc_power_on(ADC_NUM_SELECT);
    adc_reset_calibration(ADC_NUM_SELECT);
    adc_calibrate_async(ADC_NUM_SELECT);
    while ( adc_is_calibrating(ADC_NUM_SELECT) );
}