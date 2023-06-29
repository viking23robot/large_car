#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include "stm32f10x.h"                    //STM32F10x系列重要头文件
#include "IRCtrol.h"                     //红外遥控头文件
#include "motor.h"                      //电机驱动头文件
#include "oled_iic.h"                  //OLED显示屏驱动头文件
#include "speed_set.h"                //速度设置头文件
#include "Delay.h"                //延时函数头文件
#include "uart.h"                //串口头文件
#include "led.h"                //led头文件
#include "timer.h"             //定时器头文件

extern unsigned int speed_count;     //占空比计数器 100次一周期

void GPIOCLK_Init(void);//所以GPIO时钟初始化
void all_init(void);//所有想要初始化的函数	
void decode_choice(void);//红外，蓝牙，解码选择函数
void stop_choice(void); ///电机停止，led闪烁函数

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

//定义OLED显示屏
//定义IIC总线连接的GPIO端口, 用户只需要修改下面代码即可任意改变SCL和SDA的引脚
#define OLED_SCL PBout(7)  //SCL引脚
#define OLED_SDA PBout(6)  //SDA引脚

#define OLED_SCL_GPIO_PORT	  GPIOB			/* GPIO端口 */
#define OLED_SCL_RCC 	      RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define OLED_SCL_PIN		  GPIO_Pin_7			/* 连接到SCL时钟线的GPIO */

#define OLED_SDA_GPIO_PORT	  GPIOB			/* GPIO端口 */
#define OLED_SDA_RCC 	      RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define OLED_SDA_PIN		  GPIO_Pin_6			/* 连接到SDA数据线的GPIO */

// LED PB9 黄色
#define LED_PIN_0         GPIO_Pin_9
#define LED_GPIO_0        GPIOB
#define LED_SET_0         GPIO_SetBits(LED_GPIO_0 , LED_PIN_0)
#define LED_RESET_0       GPIO_ResetBits(LED_GPIO_0 , LED_PIN_0)

//红外遥控 红外接收器数据线,外部中断 PB12
#define IRIN_PIN         GPIO_Pin_12
#define IRIN_GPIO        GPIOB
#define IRIN_PORTSOURCE  GPIO_PortSourceGPIOB
#define IRIN_PINSOURCE   GPIO_PinSource12
#define IRIN_EXITLINE    EXTI_Line12
#define IRIN_IRQCH       EXTI15_10_IRQn
#define IRIN             GPIO_ReadInputDataBit(IRIN_GPIO, IRIN_PIN)



//电机驱动IO定义 
/* 
FRONT_LEFT_F_PIN	  PA0	 左前前进IO
FRONT_LEFT_B_PIN	  PA1	 左前后退IO

FRONT_RIGHT_F_PIN	  PA4	 右前前进IO
FRONT_RIGHT_B_PIN	  PA5	 右前后退IO

BEHIND_LEFT_F_PIN	  PA6	 左后前进IO
BEHIND_LEFT_B_PIN	  PA7	 左后后退IO

BEHIND_RIGHT_F_PIN	PB0	 右后前进IO
BEHIND_RIGHT_B_PIN	PB1	 右后后退IO
 */
#define FRONT_LEFT_F_PIN         GPIO_Pin_0
#define FRONT_LEFT_F_GPIO        GPIOA
#define FRONT_LEFT_F_SET         GPIO_SetBits(FRONT_LEFT_F_GPIO , FRONT_LEFT_F_PIN)
#define FRONT_LEFT_F_RESET       GPIO_ResetBits(FRONT_LEFT_F_GPIO , FRONT_LEFT_F_PIN)

#define FRONT_LEFT_B_PIN         GPIO_Pin_1
#define FRONT_LEFT_B_GPIO        GPIOA
#define FRONT_LEFT_B_SET         GPIO_SetBits(FRONT_LEFT_B_GPIO , FRONT_LEFT_B_PIN)
#define FRONT_LEFT_B_RESET       GPIO_ResetBits(FRONT_LEFT_B_GPIO , FRONT_LEFT_B_PIN)

#define FRONT_RIGHT_F_PIN        GPIO_Pin_4
#define FRONT_RIGHT_F_GPIO       GPIOA
#define FRONT_RIGHT_F_SET        GPIO_SetBits(FRONT_RIGHT_F_GPIO , FRONT_RIGHT_F_PIN)
#define FRONT_RIGHT_F_RESET      GPIO_ResetBits(FRONT_RIGHT_F_GPIO , FRONT_RIGHT_F_PIN)

#define FRONT_RIGHT_B_PIN        GPIO_Pin_5
#define FRONT_RIGHT_B_GPIO       GPIOA
#define FRONT_RIGHT_B_SET        GPIO_SetBits(FRONT_RIGHT_B_GPIO , FRONT_RIGHT_B_PIN)
#define FRONT_RIGHT_B_RESET      GPIO_ResetBits(FRONT_RIGHT_B_GPIO , FRONT_RIGHT_B_PIN)

#define BEHIND_LEFT_F_PIN        GPIO_Pin_6
#define BEHIND_LEFT_F_GPIO       GPIOA
#define BEHIND_LEFT_F_SET        GPIO_SetBits(BEHIND_LEFT_F_GPIO , BEHIND_LEFT_F_PIN)
#define BEHIND_LEFT_F_RESET      GPIO_ResetBits(BEHIND_LEFT_F_GPIO , BEHIND_LEFT_F_PIN)

#define BEHIND_LEFT_B_PIN        GPIO_Pin_7
#define BEHIND_LEFT_B_GPIO       GPIOA
#define BEHIND_LEFT_B_SET        GPIO_SetBits(BEHIND_LEFT_B_GPIO , BEHIND_LEFT_B_PIN)
#define BEHIND_LEFT_B_RESET      GPIO_ResetBits(BEHIND_LEFT_B_GPIO , BEHIND_LEFT_B_PIN)

#define BEHIND_RIGHT_F_PIN       GPIO_Pin_0
#define BEHIND_RIGHT_F_GPIO      GPIOB
#define BEHIND_RIGHT_F_SET       GPIO_SetBits(BEHIND_RIGHT_F_GPIO , BEHIND_RIGHT_F_PIN)
#define BEHIND_RIGHT_F_RESET     GPIO_ResetBits(BEHIND_RIGHT_F_GPIO , BEHIND_RIGHT_F_PIN)

#define BEHIND_RIGHT_B_PIN       GPIO_Pin_1
#define BEHIND_RIGHT_B_GPIO      GPIOB
#define BEHIND_RIGHT_B_SET       GPIO_SetBits(BEHIND_RIGHT_B_GPIO , BEHIND_RIGHT_B_PIN)
#define BEHIND_RIGHT_B_RESET     GPIO_ResetBits(BEHIND_RIGHT_B_GPIO , BEHIND_RIGHT_B_PIN)


//左前
#define FRONT_LEFT_GO    FRONT_LEFT_F_SET; FRONT_LEFT_B_RESET//前进
#define FRONT_LEFT_BACK  FRONT_LEFT_F_RESET; FRONT_LEFT_B_SET//后退
#define FRONT_LEFT_STOP  FRONT_LEFT_F_RESET; FRONT_LEFT_B_RESET//停止

//右前
#define FRONT_RIGHT_GO     FRONT_RIGHT_F_SET;  FRONT_RIGHT_B_RESET
#define FRONT_RIGHT_BACK   FRONT_RIGHT_F_RESET;FRONT_RIGHT_B_SET
#define FRONT_RIGHT_STOP   FRONT_RIGHT_F_RESET;FRONT_RIGHT_B_RESET

//左后
#define BEHIND_LEFT_GO     BEHIND_LEFT_F_SET;BEHIND_LEFT_B_RESET
#define BEHIND_LEFT_BACK   BEHIND_LEFT_F_RESET;BEHIND_LEFT_B_SET
#define BEHIND_LEFT_STOP   BEHIND_LEFT_F_RESET;BEHIND_LEFT_B_RESET

//右后
#define BEHIND_RIGHT_GO    BEHIND_RIGHT_F_SET;BEHIND_RIGHT_B_RESET
#define BEHIND_RIGHT_BACK  BEHIND_RIGHT_F_RESET;BEHIND_RIGHT_B_SET
#define BEHIND_RIGHT_STOP  BEHIND_RIGHT_F_RESET;BEHIND_RIGHT_B_RESET
#define BEHIND_RIGHT_EN   BEHIND_RIGHT_F_SET;BEHIND_RIGHT_B_SET     


//指令定义
#define Car_Go   0x18 //前进
#define Car_Back 0x52//后退
#define Car_Left  'B'//左转
#define Car_Right  'C'//后退
#define Car_Stop 'D'//暂停
				
#endif

