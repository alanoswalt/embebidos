/* Author: Jenifer ,Alan
 This project is an extension of part 3 of last homework (Temp Sensor and UART reporting). I put the specifications for the last homework below at the end of this assignment. The additional requirements will be:
 A LED will be added to the system, which will be PWM controllable i.e. dimmable. The dimming (LedIntensity) will increment/decrement in jumps of 10% (max is 100%, min is 0%).
 In order to configure the values of MinTempTh, MaxTempTh and LedIntensity, there will be 2 modes supported:
 Mode 1: Increment or Decrement MinTempTh and MaxTempTh in jumps of +/- 1 degree Celcius. Increment or Decrement LedIntensity in jumps of +/- 10%. For this mode, 3 options can be done:
 Connect 6 push buttons to the system, where 2 will be used for MinTempTh, 2 for MaxTempTh and 2 for LedIntensity.
 Use 6 keys of the PC keyboard and send them to the UART, where 2 will be used for MinTempTh, 2 for MaxTempTh and 2 for LedIntensity.
 Create a GUI (in Python/Java/etc) and add 6 buttons that will send commands to the UART, where 2 will be used for MinTempTh, 2 for MaxTempTh and 2 for LedIntensity.
 Mode 2: Set MinTempTh, MaxTempTh and/or LedIntensity values by software. There are 2 options:
 Have a "config key" similar to the previous homework where the UART will prompt the user with a menu to configure any of the 3 values. The menu and way to introduce the values can be decided by you.
 Create a GUI (or extend the one from 2.a.iii.) in Python/Java/etc and add a way to introduce the values of MaxTempTh, MinTempTh and LedIntensity e.g. with a textbox, a slider, etc.
 Reporting of the values will be very similar to the previous homework, it can be done:
 In the UART console with a format similar to: Temp: 25C, MaxTempTh: 28C, MinTempTh: 24C, MaxTemp: Off, MinTemp: Off, Led Intensity: 50%
 Using a GUI, where all values will be displayed, Temp, MaxTempTh, MinTempTh, MaxTemp, MinTemp, LedIntensity.
*/


#include "low_level_app/gpio_low_level_app/gpio_start.h" //Setup GPIO ports and PINS
#include "low_level_app/adc_low_level_app/adc_start.h"   //Setup ADC
#include "low_level_app/uart_low_level_app/uart_start.h" //Setup USART
#include "low_level_app/tim_low_level_app/tim_start.h"   //Setup TIM1 prescaler/period
#include "low_level_app/tim3_low_level_app/tim3_start.h" //Setup TIM3 PWM
#include "low_level_app/isr_low_level_app/isr_start.h"   //Interruptions and functions


int main(void) {
    
    rcc_clock_setup_in_hse_8mhz_out_72mhz();        // Use this for "blue pill"
    //This functions are the ones in charge of the setup of each of the periferics
    gpio_setup();
    ADC_setup();
    uart_setup();
    tim_setup();
    tim3_setup();
    
    
    for (;;);
    
    return 0;
}

// End main.c
