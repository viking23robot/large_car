#ifndef __Delay_H_
#define __Delay_H_

#include "interface.h"//IO�ڶ���ͷ�ļ� ����Ҫ

void delay_init(void);    // ��ʱ������ʼ��             
void delay_ms(u32 Nms);   //������ʱ����
void delay_us(u32 Nus); //΢����ʱ����

#endif

