/******************************************************* 
* File name： pwr_ctrl.c
* Author   :  wfq
* Versions :  1.0
* Description: power control driver: control power of oed, gd_tf, and wifi module.
* History: 
*   1.Date:    2015-5-20 
*     Author:  wfq
*     Action:  create
*********************************************************/ 

#include "pwr_ctrl.h"
#include "stm32f10x.h"

#include "cm3_bitband.h"


#define PWR_CTRL_OED    PDout(15)
#define PWR_CTRL_GD_TF  PCout(8)
#define PWR_CTRL_WIFI   PAout(1)


void init_pwr_ctrl(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //
    
	//GPIO_SetBits(GPIOA,GPIO_Pin_1);	
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);	

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //
    
	//GPIO_SetBits(GPIOC,GPIO_Pin_8);	
    GPIO_ResetBits(GPIOC,GPIO_Pin_8);	
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //
    
	GPIO_SetBits(GPIOD,GPIO_Pin_15);		
    
    set_pwr_all();
}

void set_pwr_oed(void)
{
    PWR_CTRL_OED = 1;
}

void reset_pwr_ode(void)
{
    PWR_CTRL_OED = 0;
}

void set_pwr_gd_tf(void)
{
    PWR_CTRL_GD_TF = 1;
}

void reset_pwr_gd_tf(void)
{
    PWR_CTRL_GD_TF = 0;
}

void set_pwr_wifi(void)
{
    PWR_CTRL_WIFI = 1;
}

void reset_pwr_wifi(void)
{
    PWR_CTRL_WIFI = 0;
}

void set_pwr_all(void)
{
    PWR_CTRL_OED = 1;
    PWR_CTRL_GD_TF = 1;
    PWR_CTRL_WIFI = 1;
}

void reset_pwr_all(void)
{
    PWR_CTRL_OED = 0;
    PWR_CTRL_GD_TF = 0;
    PWR_CTRL_WIFI = 0;
}
