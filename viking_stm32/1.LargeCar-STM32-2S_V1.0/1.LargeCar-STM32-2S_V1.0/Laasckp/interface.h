#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include "stm32f10x.h"                    //STM32F10xϵ����Ҫͷ�ļ�
#include "IRCtrol.h"                     //����ң��ͷ�ļ�
#include "motor.h"                      //�������ͷ�ļ�
#include "oled_iic.h"                  //OLED��ʾ������ͷ�ļ�
#include "speed_set.h"                //�ٶ�����ͷ�ļ�
#include "Delay.h"                //��ʱ����ͷ�ļ�
#include "uart.h"                //����ͷ�ļ�
#include "led.h"                //ledͷ�ļ�
#include "timer.h"             //��ʱ��ͷ�ļ�

extern unsigned int speed_count;     //ռ�ձȼ����� 100��һ����

void GPIOCLK_Init(void);//����GPIOʱ�ӳ�ʼ��
void all_init(void);//������Ҫ��ʼ���ĺ���	
void decode_choice(void);//���⣬����������ѡ����
void stop_choice(void); ///���ֹͣ��led��˸����

//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO�ڵ�ַӳ��
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
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

//����OLED��ʾ��
//����IIC�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�������뼴������ı�SCL��SDA������
#define OLED_SCL PBout(7)  //SCL����
#define OLED_SDA PBout(6)  //SDA����

#define OLED_SCL_GPIO_PORT	  GPIOB			/* GPIO�˿� */
#define OLED_SCL_RCC 	      RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define OLED_SCL_PIN		  GPIO_Pin_7			/* ���ӵ�SCLʱ���ߵ�GPIO */

#define OLED_SDA_GPIO_PORT	  GPIOB			/* GPIO�˿� */
#define OLED_SDA_RCC 	      RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define OLED_SDA_PIN		  GPIO_Pin_6			/* ���ӵ�SDA�����ߵ�GPIO */

// LED PB9 ��ɫ
#define LED_PIN_0         GPIO_Pin_9
#define LED_GPIO_0        GPIOB
#define LED_SET_0         GPIO_SetBits(LED_GPIO_0 , LED_PIN_0)
#define LED_RESET_0       GPIO_ResetBits(LED_GPIO_0 , LED_PIN_0)

//����ң�� ���������������,�ⲿ�ж� PB12
#define IRIN_PIN         GPIO_Pin_12
#define IRIN_GPIO        GPIOB
#define IRIN_PORTSOURCE  GPIO_PortSourceGPIOB
#define IRIN_PINSOURCE   GPIO_PinSource12
#define IRIN_EXITLINE    EXTI_Line12
#define IRIN_IRQCH       EXTI15_10_IRQn
#define IRIN             GPIO_ReadInputDataBit(IRIN_GPIO, IRIN_PIN)



//�������IO���� 
/* 
FRONT_LEFT_F_PIN	  PA0	 ��ǰǰ��IO
FRONT_LEFT_B_PIN	  PA1	 ��ǰ����IO

FRONT_RIGHT_F_PIN	  PA4	 ��ǰǰ��IO
FRONT_RIGHT_B_PIN	  PA5	 ��ǰ����IO

BEHIND_LEFT_F_PIN	  PA6	 ���ǰ��IO
BEHIND_LEFT_B_PIN	  PA7	 ������IO

BEHIND_RIGHT_F_PIN	PB0	 �Һ�ǰ��IO
BEHIND_RIGHT_B_PIN	PB1	 �Һ����IO
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


//��ǰ
#define FRONT_LEFT_GO    FRONT_LEFT_F_SET; FRONT_LEFT_B_RESET//ǰ��
#define FRONT_LEFT_BACK  FRONT_LEFT_F_RESET; FRONT_LEFT_B_SET//����
#define FRONT_LEFT_STOP  FRONT_LEFT_F_RESET; FRONT_LEFT_B_RESET//ֹͣ

//��ǰ
#define FRONT_RIGHT_GO     FRONT_RIGHT_F_SET;  FRONT_RIGHT_B_RESET
#define FRONT_RIGHT_BACK   FRONT_RIGHT_F_RESET;FRONT_RIGHT_B_SET
#define FRONT_RIGHT_STOP   FRONT_RIGHT_F_RESET;FRONT_RIGHT_B_RESET

//���
#define BEHIND_LEFT_GO     BEHIND_LEFT_F_SET;BEHIND_LEFT_B_RESET
#define BEHIND_LEFT_BACK   BEHIND_LEFT_F_RESET;BEHIND_LEFT_B_SET
#define BEHIND_LEFT_STOP   BEHIND_LEFT_F_RESET;BEHIND_LEFT_B_RESET

//�Һ�
#define BEHIND_RIGHT_GO    BEHIND_RIGHT_F_SET;BEHIND_RIGHT_B_RESET
#define BEHIND_RIGHT_BACK  BEHIND_RIGHT_F_RESET;BEHIND_RIGHT_B_SET
#define BEHIND_RIGHT_STOP  BEHIND_RIGHT_F_RESET;BEHIND_RIGHT_B_RESET
#define BEHIND_RIGHT_EN   BEHIND_RIGHT_F_SET;BEHIND_RIGHT_B_SET     


//ָ���
#define Car_Go   0x18 //ǰ��
#define Car_Back 0x52//����
#define Car_Left  'B'//��ת
#define Car_Right  'C'//����
#define Car_Stop 'D'//��ͣ
				
#endif

