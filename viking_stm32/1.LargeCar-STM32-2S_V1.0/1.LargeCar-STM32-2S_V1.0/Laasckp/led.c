#include "led.h"//ledͷ�ļ�

unsigned char tick_200ms = 0;        //LED��˸ʱ��

//led�Ƴ�ʼ��
 void led_init(void)
 {
    GPIO_InitTypeDef  GPIO_InitStructure;
	 		 
	GPIO_InitStructure.GPIO_Pin = LED_PIN_0;          //����ʹ��GPIO�ܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//����GPIO�˿��ٶ�
	GPIO_Init(LED_GPIO_0 , &GPIO_InitStructure); 
	LED_SET_0;//Ĭ�ϸ��ߵ�ƽ
	 
	
	   
 }

//LED����
void led_toggle(uint16_t Led)
{
	 
	
    /* ָ���ܽ������� 1��ʵ�ֶ�Ӧ��LEDָʾ��״̬ȡ��Ŀ�� */
		  	  
	  LED_GPIO_0->ODR ^=Led;
	  
	 
	
}
