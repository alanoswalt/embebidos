#include "dma_start.h"



void dma_init(void){
    dma_start(DMA_CLK,DMA_NVIC,DMA_NUM,DMA_CHANNEL);
}


void send_by_dma(char *recv_word1, uint16_t size){
    dma_disable_channel(DMA_NUM, DMA_CHANNEL4);
    dma_set_memory_address(DMA_NUM, DMA_CHANNEL,(uint32_t) recv_word1);
    dma_set_number_of_data(DMA_NUM, DMA_CHANNEL, size);
    dma_enable_channel(DMA_NUM, DMA_CHANNEL);
    usart_enable_tx_dma(USART1);
}

void dma1_channel4_isr(void){
    dma_clear_interrupt_flags(DMA_NUM, DMA_CHANNEL, DMA_TCIF);
    usart_disable_tx_dma(USART1);
    gpio_toggle(GPIOC,GPIO13);
}