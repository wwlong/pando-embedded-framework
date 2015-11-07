#include <stdint.h>
#include "stm32f10x.h"
#include "usart2.h"
#include "uart4.h"

void usart2_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//Enable clock
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE);

	USART_DeInit(USART2);

	//config IO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	             //USART2 TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;			 //GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 //
	GPIO_Init(GPIOA, &GPIO_InitStructure);		    		 //

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	         	 //USART2 RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USARTx */
	USART_Init(USART2, &USART_InitStructure);

	/* Enable USARTx Receive and Transmit interrupts */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/* Enable the USARTx */
	USART_Cmd(USART2, ENABLE);	
}

/**
*   @brief Set GPIO of tx and rx as GPIO_Mode_Out_PP//GPIO_Mode_IPU,
*/
void usart2_reset_tx_rx(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //Enable clock
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,ENABLE);
    //Configue GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //USART2 TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //GPIO_Mode_IPU;    		 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);
}

void usart2_putchar(unsigned char ch)
{
	USART_SendData(USART2, ch);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC)!= SET);
}

/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval : None
  */
void USART2_IRQHandler(void)                	
{
	uint8_t res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
	{
        res = USART_ReceiveData(USART2); //(USART2->DR);
        uart4_putchar(res);
	}
	
	if(USART_GetFlagStatus(USART2, USART_IT_TXE) != RESET)
	{
		USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
	}
}
