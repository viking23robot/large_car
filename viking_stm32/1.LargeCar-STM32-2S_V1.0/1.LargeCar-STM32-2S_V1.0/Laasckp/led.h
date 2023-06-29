#ifndef __LED_H_
#define __LED_H_

#include "interface.h"//IO口定义头文件 很重要

void led_init(void);//led灯的初始化
void led_toggle(uint16_t Led);//LED点亮

extern unsigned char tick_200ms ;        //LED闪烁时间

#endif
