#ifndef __IRCTROL_H_
#define __IRCTROL_H_
#include "stm32f10x.h" //STM32F10xϵ����Ҫͷ�ļ�
#include "interface.h" //IO�ڶ���ͷ�ļ�
extern unsigned char ir_rec_flag;//�������ݱ�־λ 1 �������� 0 û��
extern char IrDA;//����ֵ
extern unsigned char continue_time;//ͣ��ʱ��
extern unsigned char IRCOM[4];    //�������ң�ط�������
void IRCtrolInit(void);          //�ⲿ�ж����� ����ң������
void IRIntIsr(void);            //����ң�ط������ݽ���
#endif
