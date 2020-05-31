#include "dma_hal/dma_init.h"

#ifndef DMA_SETUP_H_
#define DMA_SETUP_H_
//  Parametros

#define DMA_CLK     RCC_DMA1
#define DMA_NVIC    NVIC_DMA1_CHANNEL4_IRQ
#define DMA_NUM     DMA1
#define DMA_CHANNEL DMA_CHANNEL4


//  Functions
extern void dma_init(void);
extern void send_by_dma(char *recv_word1, uint16_t size);


#endif
