#include "stm32f10x.h"
#include "uart4.h"
//#include "usart1.h"

#define UART4_BAUDRATE 57600

void uart4_init(void)
{
	GPIO_InitTypeDef gpio_structure;
	USART_InitTypeDef usart_structure;
	NVIC_InitTypeDef nvic_structure;
	
	// enable uart4, GPIOC clock.
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	// config uart4 gpio(PC.10)
	gpio_structure.GPIO_Pin = GPIO_Pin_10;
	gpio_structure.GPIO_Mode = GPIO_Mode_AF_PP; // alternate function push-pull
	gpio_structure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpio_structure);
	gpio_structure.GPIO_Pin = GPIO_Pin_11;
	gpio_structure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // input floating
	GPIO_Init(GPIOC, &gpio_structure); // init PC.11

	// config uart4 NVIC
	nvic_structure.NVIC_IRQChannel = UART4_IRQn;
	nvic_structure.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_structure.NVIC_IRQChannelSubPriority = 2;
	nvic_structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_structure);

	// uart config
	usart_structure.USART_BaudRate = UART4_BAUDRATE;
	usart_structure.USART_WordLength = USART_WordLength_8b;
	usart_structure.USART_StopBits = USART_StopBits_1;
	usart_structure.USART_Parity = USART_Parity_No;
	usart_structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_structure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &usart_structure);

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	USART_Cmd(UART4, ENABLE);
	
	uart4_putchar(0x35);
}

void uart4_putchar(unsigned char ch)
{
	USART_SendData(UART4, ch);
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC)!= SET);
}

/**
  * @brief  This function handles UART4 global interrupt request.
  * @param  None
  * @retval : None
  */
void UART4_IRQHandler(void)
{
	uint8_t res;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		res = USART_ReceiveData(UART4); //(UART4->DR);	//读取接收到的数据
		uart4_putchar(res);
		if(res == 0xcc)
		{  //YMODEM_C
//			usart1_putchar(0x43);
		}
		else if(res == 0xdd)
		{   //YMODEM_ACK
//			usart1_putchar(0x06);
		}
	} 
		
	//这段是为了避免STM32 USART 第一个字节发不出去的BUG 
	if(USART_GetFlagStatus(UART4, USART_IT_TXE) != RESET)
	{
		USART_ITConfig(UART4, USART_IT_TXE, DISABLE);    //禁止发缓冲器空中断， 
	}
} 
