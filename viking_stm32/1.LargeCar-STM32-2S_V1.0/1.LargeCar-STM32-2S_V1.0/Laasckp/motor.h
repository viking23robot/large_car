#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "interface.h"//IO口定义头文件 很重要

extern int front_left_speed_duty;//左前电机PWM
extern int front_right_speed_duty;//右前电机PWM
extern int behind_left_speed_duty;//左后电机PWM
extern int behind_right_speed_duty;//右后电机PWM
extern unsigned char move_rec_flag;//电机驱动标志位
extern unsigned char stop_display_flag;//暂停显示标志位
extern unsigned char Time_10us_motor; //10us计数器，作为电机驱动的基本计数器
extern unsigned int speed_count;        //占空比计数器 100次一周期

void CarMove(void);//电机驱动函数
void CarGo(void);//电机前进
void CarBack(void);//电机后退
void CarLeft(void);//电机左转
void CarRight(void);//电机右转
void CarStop(void);//电机暂停
void motor_init(void);//电机驱动初始化
void stop_display_execute(void);//电机暂停显示执行函数

#endif

