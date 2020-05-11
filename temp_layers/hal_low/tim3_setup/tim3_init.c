#include "tim3_init.h"


//Function to change the duty cycle and time of TIM3
void tim3_init(short timeCy, short dutyCy){
    rcc_periph_clock_enable(RCC_TIM3);        // Need TIM3 clock
    rcc_periph_clock_enable(RCC_AFIO);        // Need AFIO clock alternative PWM
    
    // PB0 == TIM3.CH3
    rcc_periph_clock_enable(RCC_GPIOB);        // Need GPIOB clock
    gpio_primary_remap(
                       AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_OFF,    // Optional
                       AFIO_MAPR_TIM3_REMAP_NO_REMAP);        // This is
    gpio_set_mode(GPIOB,GPIO_MODE_OUTPUT_50_MHZ,    // High speed
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,GPIO0);    // GPIOBO=TIM3.CH3
    
    // TIM3:
    timer_disable_counter(TIM3);
    rcc_periph_reset_pulse(RST_TIM3);
    
    timer_set_mode(TIM3,
                   TIM_CR1_CKD_CK_INT,
                   TIM_CR1_CMS_EDGE,
                   TIM_CR1_DIR_UP);
    timer_set_prescaler(TIM3,800);
    // Only needed for advanced timers:
    // timer_set_repetition_counter(TIM2,0);
    timer_enable_preload(TIM3);
    timer_continuous_mode(TIM3);
    timer_set_period(TIM3,timeCy);
    
    timer_disable_oc_output(TIM3,TIM_OC3);
    timer_set_oc_mode(TIM3,TIM_OC3,TIM_OCM_PWM2);
    timer_enable_oc_output(TIM3,TIM_OC3);
    
    timer_set_oc_value(TIM3,TIM_OC3,dutyCy);
    //nvic_enable_irq(NVIC_TIM3_IRQ);
    //timer_enable_irq(TIM3,TIM_DIER_UIE);
    timer_enable_counter(TIM3);
    
}