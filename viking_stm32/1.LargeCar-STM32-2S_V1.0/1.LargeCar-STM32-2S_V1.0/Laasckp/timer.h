#ifndef __TIMER_H_
#define __TIMER_H_


#include "interface.h"//IO�ڶ���ͷ�ļ� ��Ҫ

void TIM2_Init(void);       //��ʱ��2��ʼ��
void TIM2_IRQHandler(void);//TIM2�жϴ�������ÿ10us�ж�һ�� 
static void NVIC_TIM2Configuration(void); //��ʱ��2���ж�����

extern unsigned char Time_10us_sum ;    //10us����������Ϊ�������Ļ�������
extern unsigned char Time_1ms ;        //1ms����������Ϊ���ֺ����Ļ�������
extern unsigned char Time_5ms ;        //5ms����������Ϊ���ֺ����Ļ�������
#endif
