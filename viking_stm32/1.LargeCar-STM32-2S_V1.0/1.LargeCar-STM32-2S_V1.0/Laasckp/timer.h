#ifndef __TIMER_H_
#define __TIMER_H_


#include "interface.h"//IO口定义头文件 重要

void TIM2_Init(void);       //定时器2初始化
void TIM2_IRQHandler(void);//TIM2中断处理函数，每10us中断一次 
static void NVIC_TIM2Configuration(void); //定时器2的中断配置

extern unsigned char Time_10us_sum ;    //10us计数器，作为主函数的基本周期
extern unsigned char Time_1ms ;        //1ms计数器，作为部分函数的基本周期
extern unsigned char Time_5ms ;        //5ms计数器，作为部分函数的基本周期
#endif
