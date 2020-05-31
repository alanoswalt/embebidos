/* Task based USART demo:
 * Warren Gay VE3WWG
 *
 * This simple demonstration runs from task1, writing 012...XYZ lines
 * one after the other, at a rate of 5 characters/second. This demo
 * uses usart_send_blocking() to write characters.
 *
 * STM32F103C8T6:
 *	TX:	A9  <====> RX of TTL serial
 *	RX:	A10 <====> TX of TTL serial
 *	CTS:	A11 (not used)
 *	RTS:	A12 (not used)
 *	Config:	8N1
 *	Baud:	38400
 * Caution:
 *	Not all GPIO pins are 5V tolerant, so be careful to
 *	get the wiring correct.
 */


#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/dma.h>

#define RECV_SIZE 4

uint8_t recv_word[6] = "HOLA\r\n";

char i=0;

static inline void uart_putc(char ch);


/*********************************************************************
 * Setup the UART
 *********************************************************************/
static void uart_setup(void) {

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_USART1);

	// UART TX on PA9 (GPIO_USART1_TX)
	gpio_set_mode(GPIOA,
		GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
		GPIO_USART1_TX);
    
    // UART RX on PA10
    gpio_set_mode(GPIOA,
            GPIO_MODE_INPUT,
            GPIO_CNF_INPUT_PULL_UPDOWN,
            GPIO_USART1_RX);

	usart_set_baudrate(USART1,9600);
	usart_set_databits(USART1,8);
	usart_set_stopbits(USART1,USART_STOPBITS_1);
	usart_set_mode(USART1,USART_MODE_TX_RX);
	usart_set_parity(USART1,USART_PARITY_NONE);
	usart_set_flow_control(USART1,USART_FLOWCONTROL_NONE);
    
    //nvic_enable_irq(NVIC_USART1_IRQ);
    //usart_enable_rx_interrupt(USART1);
    
	usart_enable(USART1);
}
void usart1_isr(void){
    USART1_SR = ~(1<<5);
    
    recv_word[i] = usart_recv(USART1);
    usart_send_blocking(USART1,i+48);
    i++;
    if (recv_word[0] == 'o' && recv_word[1] == 'n') {
        gpio_clear(GPIOC,GPIO13);
        recv_word[1] = 'b';
        i=0;
    }else if (recv_word[0] == 'o' && recv_word[1]=='f' && recv_word[2] == 'f'){
        gpio_set(GPIOC,GPIO13);
        recv_word[1] = 'b';
        i=0;
    }
}
/*********************************************************************
 * Send one character to the UART
 *********************************************************************/
static inline void uart_putc(char ch) {
	usart_send_blocking(USART1,ch);
}

/*********************************************************************
 * Send one word
 *********************************************************************/
void send_word(char * word) {
    
    while (*word!='\0') {
        uart_putc(*word++);
    }
}
void dma1_channel4_isr(void){
    dma_clear_interrupt_flags(DMA1, DMA_CHANNEL4, DMA_TCIF);
    usart_disable_tx_dma(USART1);
    gpio_toggle(GPIOC,GPIO13);
}
void send_by_dma(){
    dma_disable_channel(DMA1, DMA_CHANNEL4);
    dma_set_memory_address(DMA1, DMA_CHANNEL4,(uint32_t) recv_word);
    dma_set_number_of_data(DMA1, DMA_CHANNEL4, RECV_SIZE);
    dma_enable_channel(DMA1, DMA_CHANNEL4);
    usart_enable_tx_dma(USART1);
}
static void dma_init(){
    dma_channel_reset(DMA1, DMA_CHANNEL4);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL4,
                               (uint32_t)&USART1_DR);
    dma_set_read_from_memory(DMA1, DMA_CHANNEL4);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL4);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL4, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL4, DMA_CCR_MSIZE_8BIT);
    dma_set_priority(DMA1, DMA_CHANNEL4, DMA_CCR_PL_HIGH);
    //dma_enable_circular_mode(DMA1, DMA_CHANNEL4);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL4);
    
}

int main(void) {

	rcc_clock_setup_in_hse_8mhz_out_72mhz(); // Blue pill
    //char nombre[] = "Alan\r\n";
    
	// PC13:
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(
		GPIOC,
                GPIO_MODE_OUTPUT_2_MHZ,
                GPIO_CNF_OUTPUT_PUSHPULL,
                GPIO13);
    gpio_clear(GPIOC,GPIO13);

	
    //DMA
   
    rcc_periph_clock_enable(RCC_DMA1);
    nvic_set_priority(NVIC_DMA1_CHANNEL4_IRQ, 0);
    nvic_enable_irq(NVIC_DMA1_CHANNEL4_IRQ);
     dma_init();
    uart_setup();
    //uart_putc('A');
    send_by_dma();
    //send_word(nombre);


	for (;;);
    //send_by_dma();
	return 0;
}

// End
