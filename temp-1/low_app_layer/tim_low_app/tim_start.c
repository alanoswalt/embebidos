//  Copyright 2020 Jenifer, Alan
#include "tim_start.h"
/**
 * Timer 2 setup
 * Wth interruptions
 */
void tim_setup(void) {
    tim_init(CLKTIM2, TIMNUM2, 7200, 1000);
    enable_irq(TIMNUM2, NVICTIM2);
}
/**
 * Timer 3 setup
 * With PWM
 */
void tim3_setup(void) {
    tim_init(CLKTIM3, TIMNUM3, 800, 100);
    enable_pwm(TIMNUM3, 0, TIM_CH3);
}
/**
 * Timer 3 change duty cycle
 */
void tim3_duty_cycle(short dc) {
    timer_set_oc_value(TIMNUM3, TIM_CH3, dc);
}
/**
 * Timer 2 on/off
 */
void tim_status(short st) {
    if (st == 0) {
        timer_disable_counter(TIMNUM2);;
    } else if (st == 1) {
        timer_enable_counter(TIMNUM2);
    }
}
/**
 * Timer 2 irq
 */
void tim2_isr(void) {
    timer_clear_flag(TIM2, TIM_SR_UIF);
    temp_sensor();
}
