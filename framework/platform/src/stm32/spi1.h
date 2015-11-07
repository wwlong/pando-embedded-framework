/******************************************************* 
* File name： spi1.h
* Author   :  wfq
* Versions :  1.0
* Description: spi setting
* History: 
*   1.Date:    2015-1-10 
*     Author:  wfq
*     Action:  create
*********************************************************/ 

#ifndef __SPI1_H_
#define __SPI1_H_

#include <stdint.h>
 				  	    													  
void SPI1_Init(void);			 //初始化SPI口
void SPI1_SetSpeed(uint8_t SpeedSet); //设置SPI速度   
uint8_t SPI1_ReadWriteByte(uint8_t TxData);//SPI总线读写一个字节
		 
#endif
