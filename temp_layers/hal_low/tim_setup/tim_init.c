#include "tim_init.h"

//Function using TIM1, can change prescaler and period
void tim_init(PRESC, PERI){
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_clock_enable(RCC_AFIO);        // Need AFIO clock
    
    timer_disable_counter(TIM2);
    timer_disable_irq(TIM2,TIM_DIER_UIE);
    
    timer_set_mode(TIM2,
                   TIM_CR1_CKD_CK_INT,
                   TIM_CR1_CMS_EDGE,
                   TIM_CR1_DIR_UP);
    timer_set_prescaler(TIM2,PRESC);//
    
    timer_disable_preload(TIM2);
    timer_continuous_mode(TIM2);
    timer_set_period(TIM2,PERI);//0.1s
    
    nvic_enable_irq(NVIC_TIM2_IRQ);
    timer_enable_irq(TIM2,TIM_DIER_UIE);
    timer_enable_counter(TIM2);
    
}