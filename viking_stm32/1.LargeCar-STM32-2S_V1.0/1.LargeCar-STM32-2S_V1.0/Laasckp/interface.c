#include "interface.h"//模块接口定义头文件


//使能GPIOA B C时钟
void GPIOCLK_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);	
}


//所有想要初始化的函数	
void all_init(void)
{
	
	 delay_init();                                     //延时函数初始化函数
	 GPIOCLK_Init();                                  //GPIOA B C时钟初始化函数
	 led_init();                                     //LED初始化函数
	 IRCtrolInit();                                 //外部中断配置和遥控配置函数
	 TIM2_Init();                                  //定时器2初始化函数
	 motor_init();                                //电机驱动初始化函数
   OLED_Init();	                               //OLED屏幕初始化函数
	 OLED_Clear();	                            //OLED屏幕清屏函数
   USART3Conf(9600);                      //串口3初始化函数	
	 USART2Conf(115200);                      //串口2初始化函数	
   OLED_ShowCH(15,1,"遥控选择模式");     //显示 遥控选择模式 文字
   OLED_ShowCH(3,6,"设置速度:");	      //设置 速度 文字
   OLED_ShowNum(80,6,sudu,3,0);       //显示 默认设置速度 数值
	
	 
	
}
	  //电机停止，led闪烁函数
 void stop_choice(void)
 {
	    if(Time_1ms >= 5)  // 5ms的周期
	{
			Time_1ms = 0;
		  Time_5ms++;
			tick_200ms++;
			if(tick_200ms >= 40)//5x40=200ms
			{
				tick_200ms = 0;
				
				led_toggle(LED_PIN_0);  //LED黄色闪烁
				
				
			}		
			
//			
//			if(IrDA==0x18||IrDA==0x52||IrDA==0x5A||IrDA==0x08) // 遥控 前进 后退  左转 右转 才有效
//			{
//			   continue_time--;// 5x150=750ms无接收指令就停车
//				
//			if(continue_time == 0)
//			{
//				continue_time = 1;
//				CarStop();   //小车停止	
//				IrDA=0;
//			}	
//			
//		   }
		
      
	}
	 	if(Time_5ms>15)//5x15=75ms的周期
	 {
		 Time_5ms = 0;
		 
	 }
      	
	
}

  void decode_choice(void)//红外遥控，蓝牙控制，选择功能函数
	  
   {
		 
	    if(ir_rec_flag == 1|BT_flag == 1 )//接收到红外信号,接收到蓝牙信号
				
			  {
					
				  if(ir_rec_flag == 1) //接收到红外信号
				  {	
					 
				          IRIntIsr();       //红外遥控发射数据解码
                  ir_rec_flag = 0;	//红外遥控标志位变成0				 
			  			  
				  }
				  				 
                  BT_flag = 0;//蓝牙标志位变成0		  	 
        
				 
			   switch(IrDA)  //红外遥控值或者蓝牙值选择执行对应的操作
				   
				{
					case 0x18:     CarGo();     break;//小车前进 上箭头键
					
					case 0x52:     CarBack();   break;//小车后退 下箭头键
					
					case 0x08:     CarLeft();   break;//小车左转 左箭头键
					
					case 0x5A:     CarRight();  break;//小车右转 右箭头键
					
					case 0x1C:     CarStop(); stop_display_flag=1;break;//小车暂停 ok键	
														
					case 0x16:     speed_and_flag=1;       break;//设置速度加并显示当前设置速度 *键
					
					case 0x0d:     speed_subtract_flag=1;  break;//设置速度减并显示当前设置速度 #键
																						
					default :      break;
				}
							 				
			}
	
    }

	
