//  Copyright 2020 Jenifer, Alan
#include "tim_init.h"
/**
 * Timer setup
 * All definitions in header.
 */
void tim_init(uint32_t clktim, uint32_t tim, uint32_t PRESC, uint32_t PERI) {
    rcc_periph_clock_enable(clktim);
    rcc_periph_clock_enable(RCC_AFIO);
    timer_disable_counter(tim);
    timer_disable_irq(tim, TIM_DIER_UIE);
    timer_set_mode(tim,
                   TIM_CR1_CKD_CK_INT,
                   TIM_CR1_CMS_EDGE,
                   TIM_CR1_DIR_UP);
    timer_set_prescaler(tim, PRESC);
    timer_disable_preload(tim);
    timer_continuous_mode(tim);
    timer_set_period(tim, PERI);
    timer_enable_counter(tim);
}
/**
 * Timer irq setup.
 */
void enable_irq(uint32_t tim, uint32_t tim_nvic) {
    nvic_enable_irq(NVIC_TIM2_IRQ);
    timer_enable_irq(tim, TIM_DIER_UIE);
}
/**
 * Timer irq setup.
 */
void enable_pwm(uint32_t tim, uint8_t dutyCy, uint32_t out_ch) {
    timer_disable_counter(tim);
    rcc_periph_clock_enable(RCC_GPIOB);
    gpio_primary_remap(
                       AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_OFF,
                       AFIO_MAPR_TIM3_REMAP_NO_REMAP);
    /*gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO0);*/
    timer_disable_oc_output(tim, out_ch);
    timer_set_oc_mode(tim, out_ch, TIM_OCM_PWM2);
    timer_enable_oc_output(tim, out_ch);
    timer_set_oc_value(tim, out_ch, dutyCy);
    timer_enable_counter(tim);
}
