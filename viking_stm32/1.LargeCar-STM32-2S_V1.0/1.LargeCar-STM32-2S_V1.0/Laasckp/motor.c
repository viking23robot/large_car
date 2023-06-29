#include "motor.h"      //电机驱动头文件

unsigned int speed_count=0;       //占空比计数器 100次一周期
unsigned char move_rec_flag=0;   //电机标志位 1 有新数据 0 没有
unsigned char stop_display_flag=0;   //暂停显示标志位
unsigned char Time_10us_motor = 0;    //10us计数器，作为电机驱动的基本计数器
int front_left_speed_duty= 0;//左前电机PWM
int front_right_speed_duty= 0;//右前电机PWM
int behind_left_speed_duty= 0;//左后电机PWM
int behind_right_speed_duty= 0;//右后电机PWM



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

void MotorGPIO_Configuration(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_F_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(FRONT_LEFT_F_GPIO, &GPIO_InitStructure);    
	
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_B_PIN;	
	GPIO_Init(FRONT_LEFT_B_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_F_PIN;	
	GPIO_Init(FRONT_RIGHT_F_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_B_PIN;	
	GPIO_Init(FRONT_RIGHT_B_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_F_PIN;	
	GPIO_Init(BEHIND_LEFT_F_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_B_PIN;	
	GPIO_Init(BEHIND_LEFT_B_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_F_PIN;	
	GPIO_Init(BEHIND_RIGHT_F_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_B_PIN;	
	GPIO_Init(BEHIND_RIGHT_B_GPIO, &GPIO_InitStructure);  
	
}

//根据占空比驱动电机转动
void CarMove(void)
{   
	
  //左前轮
	if(front_left_speed_duty > 0)//向前
	{
		if(speed_count < front_left_speed_duty)
		{
			FRONT_LEFT_GO;
		}else
		{
			FRONT_LEFT_STOP;
		}
	}
	else if(front_left_speed_duty < 0)//向后
	{
		if(speed_count < (-1)*front_left_speed_duty)
		{
			FRONT_LEFT_BACK;
		}else
		{
			FRONT_LEFT_STOP;
		}
	}
	else                //停止
	{
		FRONT_LEFT_STOP;
	}
	
	
		//右前轮
	if(front_right_speed_duty > 0)//向前
	{
		if(speed_count < front_right_speed_duty)
		{
			FRONT_RIGHT_GO;
		}else                //停止
		{
			FRONT_RIGHT_STOP;
		}
	}
	else if(front_right_speed_duty < 0)//向后
	{
		if(speed_count < (-1)*front_right_speed_duty)
		{
			FRONT_RIGHT_BACK;
		}else                //停止
		{
			FRONT_RIGHT_STOP;
		}
	}
	else                //停止
	{
		FRONT_RIGHT_STOP;
	}
	
	
	//左后轮
	if(behind_left_speed_duty > 0)//向前
	{
		if(speed_count < behind_left_speed_duty)
		{
			BEHIND_LEFT_GO;
		}	else                //停止
		{
			BEHIND_LEFT_STOP;
		}
	}
	else if(behind_left_speed_duty < 0)//向后
	{
		if(speed_count < (-1)*behind_left_speed_duty)
		{
			BEHIND_LEFT_BACK;
		}	else                //停止
		{
			BEHIND_LEFT_STOP;
		}
	}
	else                //停止
	{
		BEHIND_LEFT_STOP;
	}
	
	
		//右后轮
	if(behind_right_speed_duty > 0)//向前
	{
		if(speed_count < behind_right_speed_duty)
		{
			BEHIND_RIGHT_GO;
		}	else                //停止
		{
			BEHIND_RIGHT_STOP;
		}
	}
	else if(behind_right_speed_duty < 0)//向后
	{
		if(speed_count < (-1)*behind_right_speed_duty)
		{
			BEHIND_RIGHT_BACK;
		}	else                //停止
		{
			BEHIND_RIGHT_STOP;
		}
	}
	else                //停止
	{
		BEHIND_RIGHT_STOP;
	}
}

//speed说明，这个变量的区间0-100
//sudu的正负是根据电机的安装情况来决定的，左边和右边的电机安装方向不一致哦。

//向前
void CarGo(void)
{
	front_left_speed_duty=-sudu;
	front_right_speed_duty=sudu;
  behind_left_speed_duty=-sudu;
  behind_right_speed_duty=sudu;
}

//后退
void CarBack(void)
{
	front_left_speed_duty=sudu;
	front_right_speed_duty=-sudu;
  behind_left_speed_duty=sudu;
  behind_right_speed_duty=-sudu;
}

//向左
void CarLeft(void)
{
	front_left_speed_duty=sudu;
	front_right_speed_duty=sudu;
  behind_left_speed_duty=sudu;
  behind_right_speed_duty=sudu;
}

//向右
void CarRight(void)
{
	front_left_speed_duty=-sudu;
	front_right_speed_duty=-sudu;
  behind_left_speed_duty=-sudu;
  behind_right_speed_duty=-sudu;
}

//停止
void CarStop(void)
{
	front_left_speed_duty=0;
	front_right_speed_duty=0;
  behind_left_speed_duty=0;
  behind_right_speed_duty=0;
}






//电机驱动初始化
void motor_init(void)
{
	MotorGPIO_Configuration();     ////GPIO配置函数
	CarStop();                     //暂停
	
	
	
}

		
 void stop_display_execute()//电机暂停显示执行函数
 {
	 
				if(stop_display_flag==1)//屏幕显示 暂停 标志位 ok键
		{
				        OLED_Clear();	//OLED屏幕清屏
			          sudu=10;//速度设置为10
                OLED_ShowCH(48,1,"暂停");		    //显示 暂停 文字
			          OLED_ShowCH(3,6,"设置速度:");	   //显示 设置速度 文字
                OLED_ShowNum(80,6,sudu,3,0);    //显示 当前设置速度 数值
			          stop_display_flag=0;//屏幕显示 暂停 标志位为零			        
			   	      IrDA=0;
		}

 }	


