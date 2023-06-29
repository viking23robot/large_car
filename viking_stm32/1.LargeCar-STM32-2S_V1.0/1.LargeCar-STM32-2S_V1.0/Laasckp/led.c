#include "led.h"//led头文件

unsigned char tick_200ms = 0;        //LED闪烁时间

//led灯初始化
 void led_init(void)
 {
    GPIO_InitTypeDef  GPIO_InitStructure;
	 		 
	GPIO_InitStructure.GPIO_Pin = LED_PIN_0;          //配置使能GPIO管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//配置GPIO端口速度
	GPIO_Init(LED_GPIO_0 , &GPIO_InitStructure); 
	LED_SET_0;//默认给高电平
	 
	
	   
 }

//LED点亮
void led_toggle(uint16_t Led)
{
	 
	
    /* 指定管脚输出异或 1，实现对应的LED指示灯状态取反目的 */
		  	  
	  LED_GPIO_0->ODR ^=Led;
	  
	 
	
}
