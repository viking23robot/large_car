#ifndef __SPEED_SET_H_
#define __SPEED_SET_H_

#include "interface.h"//IO�ڶ���ͷ�ļ� ����Ҫ

void speed_and(void);                           //С���ٶȼ����㺯��
void speed_subtract(void);                     //С���ٶȼ����㺯��
void speed_set_display_execute(void);         //С���ٶ�������ʾ��ִ�к���

extern unsigned char sudu;                  //С�������ٶȱ���
extern unsigned char speed_and_flag;       //С���ٶȼӱ�־λ
extern unsigned char speed_subtract_flag; //С���ٶȼ���־λ


#endif
