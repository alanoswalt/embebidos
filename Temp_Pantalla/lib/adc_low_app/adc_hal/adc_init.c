//  Copyright 2020 Jenifer, Alan
#include "adc_init.h"
/* 
 * Read ADC Channel, Channel 1, ADC1 and Pin A1 
 * Initialize ADC
 */
/*void ADC_init(void) {
    rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_ADC1EN);
    adc_power_off(ADC_NUM);
    rcc_peripheral_reset(&RCC_APB2RSTR, RCC_APB2RSTR_ADC1RST);
    rcc_peripheral_clear_reset(&RCC_APB2RSTR, RCC_APB2RSTR_ADC1RST);
    rcc_set_adcpre(RCC_CFGR_ADCPRE_PCLK2_DIV6);   /**< Set. 12MHz, Max. 14MHz */
    //adc_set_dual_mode(ADC_CR1_DUALMOD_IND);        /**< Independent mode */
  /*  adc_disable_scan_mode(ADC_NUM);
    adc_set_right_aligned(ADC_NUM);
    adc_set_single_conversion_mode(ADC_NUM);
    adc_power_on(ADC_NUM);
    adc_reset_calibration(ADC_NUM);
    adc_calibrate_async(ADC_NUM);
    while ( adc_is_calibrating(ADC_NUM));
}*/
/* 
 * Read ADC Channel
 * Recive ADC Data
 */
/*uint16_t get_adc_value(void) {
    uint8_t ch = 1;
     adc_set_sample_time(ADC_NUM, ADC_CHANNEL, ADC_SMPR_SMP_239DOT5CYC);
    adc_set_regular_sequence(ADC_NUM, 1, &ch);
    adc_start_conversion_direct(ADC_NUM);
    while (!adc_eoc(ADC_NUM));
    return adc_read_regular(ADC_NUM)* 330 / (RESOLUTION);
}
void adc_off_(void) {
    adc_power_off(ADC_NUM);
}
void adc_on_(void) {
    adc_power_on(ADC_NUM);
}*/