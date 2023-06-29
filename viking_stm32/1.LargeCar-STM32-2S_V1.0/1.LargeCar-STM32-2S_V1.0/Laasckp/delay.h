#ifndef __Delay_H_
#define __Delay_H_

#include "interface.h"//IO口定义头文件 很重要

void delay_init(void);    // 延时函数初始化             
void delay_ms(u32 Nms);   //毫秒延时函数
void delay_us(u32 Nus); //微秒延时函数

#endif

