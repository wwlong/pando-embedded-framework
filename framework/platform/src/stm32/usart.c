#include <stdlib.h>
#include "platform/include/pando_serial.h"
#include "stm32f10x.h"

//define the max length to receive
#define USART_RECEIVED_MAX_LEN (120)

//the received data buffer
uint8_t g_usart1_received_buf[USART_RECEIVED_MAX_LEN];

//declare the data handler when receiving data
data_handler_callback g_rx_data_handler;

void serial_port1_init(void)
{
    //enable usart1, GPIOA clock.
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
    USART_DeInit(USART1); //reset usart1
    
    //config usart1 gpio. USART1 Tx(PA.09)
    GPIO_InitTypeDef gpio_structure;
    gpio_structure.GPIO_Pin = GPIO_Pin_9;
    gpio_structure.GPIO_Mode = GPIO_Mode_AF_PP; //alternate function push-pull
    gpio_structure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &gpio_structure); //init PA.09
    gpio_structure.GPIO_Pin = GPIO_Pin_10;
    gpio_structure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //input floating
    GPIO_Init(GPIOA, &gpio_structure); //init PA.10

    // config usart1 NVIC
    NVIC_InitTypeDef nvic_structure;
    nvic_structure.NVIC_IRQChannel = USART1_IRQn;
    nvic_structure.NVIC_IRQChannelPreemptionPriority = 3;
    nvic_structure.NVIC_IRQChannelSubPriority = 3;
    nvic_structure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_structure);

    // usart config
    USART_InitTypeDef usart_structure;
    usart_structure.USART_BaudRate = 115200;
    usart_structure.USART_WordLength = USART_WordLength_8b;
    usart_structure.USART_StopBits = USART_StopBits_1;
    usart_structure.USART_Parity = USART_Parity_No;
    usart_structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_structure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &usart_structure);

    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); //enable idle irq

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_DeInit(DMA1_Channel5);
    DMA_InitTypeDef dma_structure;
    dma_structure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
    dma_structure.DMA_MemoryBaseAddr = (uint32_t)g_usart1_received_buf;
    dma_structure.DMA_DIR = DMA_DIR_PeripheralSRC;
    dma_structure.DMA_BufferSize = USART_RECEIVED_MAX_LEN;
    dma_structure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma_structure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma_structure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma_structure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma_structure.DMA_Mode = DMA_Mode_Circular;
    dma_structure.DMA_Priority = DMA_Priority_VeryHigh;
    dma_structure.DMA_M2M = DMA_M2M_Disable;  
    DMA_Init(DMA1_Channel5, &dma_structure);
    DMA_Cmd(DMA1_Channel5, ENABLE);

    //receive data with dma
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
    USART_Cmd(USART1, ENABLE);
    return;
}

void on_serial_port1_recv_data_callback(data_handler_callback data_recv_cb)
{
    g_rx_data_handler = data_recv_cb;
    return;
}

void usart1_putchar(unsigned char ch)
{
    USART_SendData(USART1, ch);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!= SET);
    return;
}

uint16_t serial_port1_send(uint8_t *buffer, uint16_t length)
{
    uint16_t tx_index;
    for(tx_index = 0; tx_index < length; tx_index++)
    {
        usart1_putchar(buffer[tx_index]);
    }

    return tx_index;
}

void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
    {
        uint8_t tmp = USART_ReceiveData(USART1);
        DMA_Cmd(DMA1_Channel5, DISABLE); //close DMA
        uint16_t rx_length = USART_RECEIVED_MAX_LEN - DMA_GetCurrDataCounter(DMA1_Channel5);
        if(NULL != g_rx_data_handler)
        {
            g_rx_data_handler(g_usart1_received_buf, rx_length);
        }

        //set data length of transmission
        DMA_SetCurrDataCounter(DMA1_Channel5, USART_RECEIVED_MAX_LEN);
        //open DMA
        DMA_Cmd(DMA1_Channel5,ENABLE);
    }

    if(USART_GetFlagStatus(USART1, USART_IT_TXE) != RESET)
    {
        USART_ITConfig(USART1, USART_IT_TXE, DISABLE); //disable transmit interrupt 
    }
}
