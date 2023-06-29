#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "interface.h"//IO�ڶ���ͷ�ļ� ����Ҫ

extern int front_left_speed_duty;//��ǰ���PWM
extern int front_right_speed_duty;//��ǰ���PWM
extern int behind_left_speed_duty;//�����PWM
extern int behind_right_speed_duty;//�Һ���PWM
extern unsigned char move_rec_flag;//���������־λ
extern unsigned char stop_display_flag;//��ͣ��ʾ��־λ
extern unsigned char Time_10us_motor; //10us����������Ϊ��������Ļ���������
extern unsigned int speed_count;        //ռ�ձȼ����� 100��һ����

void CarMove(void);//�����������
void CarGo(void);//���ǰ��
void CarBack(void);//�������
void CarLeft(void);//�����ת
void CarRight(void);//�����ת
void CarStop(void);//�����ͣ
void motor_init(void);//���������ʼ��
void stop_display_execute(void);//�����ͣ��ʾִ�к���

#endif

