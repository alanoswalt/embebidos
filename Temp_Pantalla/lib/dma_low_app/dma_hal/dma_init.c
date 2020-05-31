#include "dma_init.h"


void dma_start(uint32_t clk, uint32_t dma_nvic_channel, uint32_t dma, uint32_t channel){
    rcc_periph_clock_enable(clk);
    nvic_set_priority(dma_nvic_channel, 0);
    nvic_enable_irq(dma_nvic_channel);

    dma_channel_reset(dma, channel);
    dma_set_peripheral_address(dma, channel,
                               (uint32_t)&USART1_DR);
    dma_set_read_from_memory(dma, channel);
    dma_enable_memory_increment_mode(dma, channel);
    dma_set_peripheral_size(dma, channel, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(dma, channel, DMA_CCR_MSIZE_8BIT);
    dma_set_priority(dma, channel, DMA_CCR_PL_HIGH);
    //dma_enable_circular_mode(DMA1, DMA_CHANNEL4);
    dma_enable_transfer_complete_interrupt(dma, channel);
    
}