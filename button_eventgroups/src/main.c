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

#define LED_PORT GPIOA
#define LED_PIN1  GPIO5
#define LED_PIN2  GPIO6
#define LED_PIN3  GPIO7
#define PORT_RCC  RCC_GPIOA

#define BUTTON_RCC  RCC_GPIOB
#define BUTTON_PORT GPIOA
#define BUTTON_PIN0  GPIO0
#define BUTTON_PIN1  GPIO1
#define BUTTON_PIN2  GPIO2

#define BUTTON_PIN_IRQ NVIC_EXTI0_IRQ
#define BUTTON_PIN_EXTI EXTI0
#define BUTTON_PIN_IRQ1 NVIC_EXTI1_IRQ
#define BUTTON_PIN_EXTI1 EXTI1
#define BUTTON_PIN_IRQ2 NVIC_EXTI2_IRQ
#define BUTTON_PIN_EXTI2 EXTI2




//RTOS defines
EventGroupHandle_t button_event_group; //Crear el handler del evento, typo de dato handler
#define BUTTON_EVENT_BIT0 (1 << 0)
#define BUTTON_EVENT_BIT1 (1 << 1)
#define BUTTON_EVENT_BIT2 (1 << 2)


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
void led_setup(void){
	//rcc_periph_clock_enable(LED_RCC);
	gpio_set_mode(LED_PORT, GPIO_MODE_OUTPUT_2_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL, LED_PIN1|LED_PIN2|LED_PIN3);
}

static
void button_setup(void){
	//rcc_periph_clock_enable(BUTTON_RCC);
	rcc_periph_clock_enable(RCC_AFIO);

	nvic_enable_irq(BUTTON_PIN_IRQ);
    nvic_enable_irq(BUTTON_PIN_IRQ1);
    nvic_enable_irq(BUTTON_PIN_IRQ2);

	gpio_set_mode(BUTTON_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, BUTTON_PIN0|BUTTON_PIN1|BUTTON_PIN2);
    gpio_set(BUTTON_PORT,BUTTON_PIN0|BUTTON_PIN1|BUTTON_PIN2);

	exti_select_source(BUTTON_PIN_EXTI|BUTTON_PIN_EXTI1|BUTTON_PIN_EXTI2, BUTTON_PORT);
	exti_set_trigger(BUTTON_PIN_EXTI|BUTTON_PIN_EXTI1|BUTTON_PIN_EXTI2, EXTI_TRIGGER_FALLING);
	exti_enable_request(BUTTON_PIN_EXTI|BUTTON_PIN_EXTI1|BUTTON_PIN_EXTI2);
}

void exti0_isr(void){
    BaseType_t xHigherPriorityTaskWoken;
	exti_reset_request(BUTTON_PIN_EXTI); //
    //Aqui se setea el vit al evento, el ultimo es para despert al task con mayor prioridad
    xEventGroupSetBitsFromISR(button_event_group,BUTTON_EVENT_BIT0,&xHigherPriorityTaskWoken); 
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
void exti1_isr(void){
    BaseType_t xHigherPriorityTaskWoken;
	exti_reset_request(BUTTON_PIN_EXTI1); //
    //Aqui se setea el vit al evento, el ultimo es para despert al task con mayor prioridad
    xEventGroupSetBitsFromISR(button_event_group,BUTTON_EVENT_BIT1,&xHigherPriorityTaskWoken); 
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void exti2_isr(void){
    BaseType_t xHigherPriorityTaskWoken;
	exti_reset_request(BUTTON_PIN_EXTI2); //
    //Aqui se setea el vit al evento, el ultimo es para despert al task con mayor prioridad
    xEventGroupSetBitsFromISR(button_event_group,BUTTON_EVENT_BIT2,&xHigherPriorityTaskWoken); 
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void
debouncing(void *args __attribute((unused))) {
    EventBits_t event_bits;
    for (;;) {
        event_bits = xEventGroupWaitBits(
                        button_event_group,
                        BUTTON_EVENT_BIT0|BUTTON_EVENT_BIT1|BUTTON_EVENT_BIT2,
                        pdFALSE, //No clear on exit
                        pdFALSE, //Wait for ANY bit to be set
                        500);
        if(event_bits!=0){ //A Button was pressed
            vTaskDelay(pdMS_TO_TICKS(50)); //Wait for 10ms
            if(event_bits & BUTTON_EVENT_BIT0){ //The Button was pressed
                gpio_toggle(LED_PORT,LED_PIN1);
                //Clear button event flag that may have been set again during deboucing delay
                xEventGroupClearBits(button_event_group,BUTTON_EVENT_BIT0); 
            }
            if(event_bits & BUTTON_EVENT_BIT1){ //The Button was pressed
                gpio_toggle(LED_PORT,LED_PIN2);
                //Clear button event flag that may have been set again during deboucing delay
                xEventGroupClearBits(button_event_group,BUTTON_EVENT_BIT1); 
            }
            if(event_bits & BUTTON_EVENT_BIT2){ //The Button was pressed
                gpio_toggle(LED_PORT,LED_PIN3);
                //Clear button event flag that may have been set again during deboucing delay
                xEventGroupClearBits(button_event_group,BUTTON_EVENT_BIT2); 
            }
        }
    }
}


int
main(void) {

    rcc_periph_clock_enable(PORT_RCC);
    led_setup();
    button_setup();

    button_event_group = xEventGroupCreate(); //even group regresa un handler que referencia al evento, este se llamara button_event_group

    xTaskCreate(debouncing,"DEBOUNCING",100,NULL,configMAX_PRIORITIES-1,NULL);
    vTaskStartScheduler();

    for (;;);
    return 0;
}

// End
