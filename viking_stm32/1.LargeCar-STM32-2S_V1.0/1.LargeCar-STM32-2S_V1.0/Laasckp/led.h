#ifndef __LED_H_
#define __LED_H_

#include "interface.h"//IO�ڶ���ͷ�ļ� ����Ҫ

void led_init(void);//led�Ƶĳ�ʼ��
void led_toggle(uint16_t Led);//LED����

extern unsigned char tick_200ms ;        //LED��˸ʱ��

#endif
