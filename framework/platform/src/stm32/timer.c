#include <stdlib.h>
#include "platform/include/pando_timer.h"
#include "stm32f10x.h"

struct pd_timer g_timer1_config;

void timer1_init(struct pd_timer timer_cfg)
{
    TIM_TimeBaseInitTypeDef time_structure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //enable clock
    time_structure.TIM_Period = 2 * timer_cfg.interval - 1;
    time_structure.TIM_Prescaler = 35999;
    time_structure.TIM_ClockDivision = TIM_CKD_DIV1;
    time_structure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &time_structure);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitTypeDef nvic_structure;
    nvic_structure.NVIC_IRQChannel = TIM2_IRQn; //TIM2 interrupt
    nvic_structure.NVIC_IRQChannelPreemptionPriority = 2;
    nvic_structure.NVIC_IRQChannelSubPriority = 3;
    nvic_structure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_structure);

    timer1_stop();
    g_timer1_config = timer_cfg;
}

void timer1_start(void)
{
    TIM_Cmd(TIM2, ENABLE);
}

void timer1_stop(void)
{
    TIM_Cmd(TIM2, DISABLE);
}

void TIM2_IRQHandler(void)
{
    //Checks whether the TIM interrupt has occurred or not
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //Clears the TIMx's interrupt pending bits
        if(NULL != g_timer1_config.expiry_cb)
        {
            g_timer1_config.expiry_cb();
        }

        if(0 == g_timer1_config.repeated)
        {
            timer1_stop();
        }
    }
}
