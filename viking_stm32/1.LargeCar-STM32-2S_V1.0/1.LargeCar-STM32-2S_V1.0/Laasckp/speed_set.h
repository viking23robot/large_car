#ifndef __SPEED_SET_H_
#define __SPEED_SET_H_

#include "interface.h"//IO口定义头文件 很重要

void speed_and(void);                           //小车速度加运算函数
void speed_subtract(void);                     //小车速度减运算函数
void speed_set_display_execute(void);         //小车速度设置显示和执行函数

extern unsigned char sudu;                  //小车设置速度变量
extern unsigned char speed_and_flag;       //小车速度加标志位
extern unsigned char speed_subtract_flag; //小车速度减标志位


#endif
