#include "delay.h"    //��ʱ����ͷ�ļ�

  void delay_init(void)//��ʱ������ʼ��ͷ�ļ�
	   
   {
	   
        SysTick->CTRL&=0xfffffffb;//���ƼĴ�����ѡ���ⲿʱ�Ӽ�ϵͳʱ�ӵİ˷�֮һ��HCLK/8��72M/8=9M��
	   
    }

 
   void delay_us(u32 Nus)   //1us ��ʱ����
	   
  {   
	  
       SysTick->LOAD=Nus*9;                 //ʱ�����    72M��Ƶ     
       SysTick->CTRL|=0x01;                //��ʼ����      
       while(!(SysTick->CTRL&(1<<16)));   //�ȴ�ʱ�䵽��   
       SysTick->CTRL=0X00000000;         //�رռ�����   
       SysTick->VAL=0X00000000;         //��ռ�����   
 }


   void delay_ms(u32 Nms)//1ms ��ʱ����
		 
  { 
	while(Nms--)
	{
		delay_us(1000);
	}
	
  }
