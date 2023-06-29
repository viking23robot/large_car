#include "interface.h"//ģ��ӿڶ���ͷ�ļ�


//ʹ��GPIOA B Cʱ��
void GPIOCLK_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);	
}


//������Ҫ��ʼ���ĺ���	
void all_init(void)
{
	
	 delay_init();                                     //��ʱ������ʼ������
	 GPIOCLK_Init();                                  //GPIOA B Cʱ�ӳ�ʼ������
	 led_init();                                     //LED��ʼ������
	 IRCtrolInit();                                 //�ⲿ�ж����ú�ң�����ú���
	 TIM2_Init();                                  //��ʱ��2��ʼ������
	 motor_init();                                //���������ʼ������
   OLED_Init();	                               //OLED��Ļ��ʼ������
	 OLED_Clear();	                            //OLED��Ļ��������
   USART3Conf(9600);                      //����3��ʼ������	
	 USART2Conf(115200);                      //����2��ʼ������	
   OLED_ShowCH(15,1,"ң��ѡ��ģʽ");     //��ʾ ң��ѡ��ģʽ ����
   OLED_ShowCH(3,6,"�����ٶ�:");	      //���� �ٶ� ����
   OLED_ShowNum(80,6,sudu,3,0);       //��ʾ Ĭ�������ٶ� ��ֵ
	
	 
	
}
	  //���ֹͣ��led��˸����
 void stop_choice(void)
 {
	    if(Time_1ms >= 5)  // 5ms������
	{
			Time_1ms = 0;
		  Time_5ms++;
			tick_200ms++;
			if(tick_200ms >= 40)//5x40=200ms
			{
				tick_200ms = 0;
				
				led_toggle(LED_PIN_0);  //LED��ɫ��˸
				
				
			}		
			
//			
//			if(IrDA==0x18||IrDA==0x52||IrDA==0x5A||IrDA==0x08) // ң�� ǰ�� ����  ��ת ��ת ����Ч
//			{
//			   continue_time--;// 5x150=750ms�޽���ָ���ͣ��
//				
//			if(continue_time == 0)
//			{
//				continue_time = 1;
//				CarStop();   //С��ֹͣ	
//				IrDA=0;
//			}	
//			
//		   }
		
      
	}
	 	if(Time_5ms>15)//5x15=75ms������
	 {
		 Time_5ms = 0;
		 
	 }
      	
	
}

  void decode_choice(void)//����ң�أ��������ƣ�ѡ���ܺ���
	  
   {
		 
	    if(ir_rec_flag == 1|BT_flag == 1 )//���յ������ź�,���յ������ź�
				
			  {
					
				  if(ir_rec_flag == 1) //���յ������ź�
				  {	
					 
				          IRIntIsr();       //����ң�ط������ݽ���
                  ir_rec_flag = 0;	//����ң�ر�־λ���0				 
			  			  
				  }
				  				 
                  BT_flag = 0;//������־λ���0		  	 
        
				 
			   switch(IrDA)  //����ң��ֵ��������ֵѡ��ִ�ж�Ӧ�Ĳ���
				   
				{
					case 0x18:     CarGo();     break;//С��ǰ�� �ϼ�ͷ��
					
					case 0x52:     CarBack();   break;//С������ �¼�ͷ��
					
					case 0x08:     CarLeft();   break;//С����ת ���ͷ��
					
					case 0x5A:     CarRight();  break;//С����ת �Ҽ�ͷ��
					
					case 0x1C:     CarStop(); stop_display_flag=1;break;//С����ͣ ok��	
														
					case 0x16:     speed_and_flag=1;       break;//�����ٶȼӲ���ʾ��ǰ�����ٶ� *��
					
					case 0x0d:     speed_subtract_flag=1;  break;//�����ٶȼ�����ʾ��ǰ�����ٶ� #��
																						
					default :      break;
				}
							 				
			}
	
    }

	
