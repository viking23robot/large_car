#ifndef __UART_H_
#define __UART_H_


#include "interface.h"//IO�ڶ���ͷ�ļ� ����Ҫ

extern char BT ;//��������ָ��
extern unsigned char BT_flag;//�������Ʊ�־λ

void USART3Conf(u32 baudRate);
void PutChar(u8 Data);
void PutNChar(u8 *buf , u16 size);
void PutStr(char *str);

void USART2Conf(u32 baudRate);
void PutChar2(u8 Data);
void PutNChar2(u8 *buf , u16 size);
void PutStr2(char *str);

#endif
