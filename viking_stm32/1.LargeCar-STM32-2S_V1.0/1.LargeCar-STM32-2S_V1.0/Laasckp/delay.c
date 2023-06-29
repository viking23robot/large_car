#include "delay.h"    //延时函数头文件

  void delay_init(void)//延时函数初始化头文件
	   
   {
	   
        SysTick->CTRL&=0xfffffffb;//控制寄存器，选择外部时钟即系统时钟的八分之一（HCLK/8；72M/8=9M）
	   
    }

 
   void delay_us(u32 Nus)   //1us 延时函数
	   
  {   
	  
       SysTick->LOAD=Nus*9;                 //时间加载    72M主频     
       SysTick->CTRL|=0x01;                //开始倒数      
       while(!(SysTick->CTRL&(1<<16)));   //等待时间到达   
       SysTick->CTRL=0X00000000;         //关闭计数器   
       SysTick->VAL=0X00000000;         //清空计数器   
 }


   void delay_ms(u32 Nms)//1ms 延时函数
		 
  { 
	while(Nms--)
	{
		delay_us(1000);
	}
	
  }
