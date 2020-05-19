/* Simple LED task demo, using timed delays:
 */
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <event_groups.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>

//HAL defines

#define LED_PORT GPIOC
#define LED_PIN  GPIO13
#define LED_RCC  RCC_GPIOC

#define BUTTON_PORT GPIOA
#define BUTTON_PIN  GPIO0
#define BUTTON_RCC  RCC_GPIOA
#define BUTTON_PIN_IRQ NVIC_EXTI0_IRQ
#define BUTTON_PIN_EXTI EXTI0

//RTOS defines
EventGroupHandle_t button_event_group; //Crear el handler del evento, typo de dato handler
#define BUTTON_EVENT_BIT (1 << 0)


extern void vApplicationStackOverflowHook(
	xTaskHandle *pxTask,
	signed portCHAR *pcTaskName);

void
vApplicationStackOverflowHook(
  xTaskHandle *pxTask __attribute((unused)),
  signed portCHAR *pcTaskName __attribute((unused))
) {
	for(;;);	// Loop forever here..
}

static
void led_setup(){
	rcc_periph_clock_enable(LED_RCC);

	gpio_set_mode(LED_PORT, GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL, LED_PIN);
}

static
void button_setup(){
	rcc_periph_clock_enable(BUTTON_RCC);

	rcc_periph_clock_enable(RCC_AFIO);

	nvic_enable_irq(BUTTON_PIN_IRQ);

	gpio_set_mode(BUTTON_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, BUTTON_PIN);
    gpio_set(BUTTON_PORT,BUTTON_PIN);

	exti_select_source(BUTTON_PIN_EXTI, BUTTON_PORT);
	exti_set_trigger(BUTTON_PIN_EXTI, EXTI_TRIGGER_FALLING);
	exti_enable_request(BUTTON_PIN_EXTI);
}

void exti0_isr(void)
{
    BaseType_t xHigherPriorityTaskWoken;
	exti_reset_request(BUTTON_PIN_EXTI);
    xEventGroupSetBitsFromISR(
                        button_event_group,
                        BUTTON_EVENT_BIT,
                        &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void
debouncing(void *args __attribute((unused))) {
    EventBits_t event_bits;
    for (;;) {
        event_bits = xEventGroupWaitBits(
                        button_event_group,
                        BUTTON_EVENT_BIT,
                        pdFALSE, //No clear on exit
                        pdFALSE, //Wait for ANY bit to be set
                        500);
        if(event_bits!=0){ //A Button was pressed
            vTaskDelay(pdMS_TO_TICKS(10)); //Wait for 10ms
            if(event_bits & BUTTON_EVENT_BIT){ //The Button was pressed
                gpio_toggle(LED_PORT,LED_PIN);
                //Clear button event flag that may have been set again during deboucing delay
                xEventGroupClearBits(button_event_group,BUTTON_EVENT_BIT); 
            }
        }
    }
}


int
main(void) {

    led_setup();
    button_setup();

    button_event_group = xEventGroupCreate(); //even group regresa un handler que referencia al evento, este se llamara button_event_group

    xTaskCreate(debouncing,"DEBOUNCING",100,NULL,configMAX_PRIORITIES-1,NULL);
    vTaskStartScheduler();

    for (;;);
    return 0;
}

// End
