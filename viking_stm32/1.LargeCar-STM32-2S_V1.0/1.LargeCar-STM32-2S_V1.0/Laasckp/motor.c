#include "motor.h"      //�������ͷ�ļ�

unsigned int speed_count=0;       //ռ�ձȼ����� 100��һ����
unsigned char move_rec_flag=0;   //�����־λ 1 �������� 0 û��
unsigned char stop_display_flag=0;   //��ͣ��ʾ��־λ
unsigned char Time_10us_motor = 0;    //10us����������Ϊ��������Ļ���������
int front_left_speed_duty= 0;//��ǰ���PWM
int front_right_speed_duty= 0;//��ǰ���PWM
int behind_left_speed_duty= 0;//�����PWM
int behind_right_speed_duty= 0;//�Һ���PWM



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

//����ռ�ձ��������ת��
void CarMove(void)
{   
	
  //��ǰ��
	if(front_left_speed_duty > 0)//��ǰ
	{
		if(speed_count < front_left_speed_duty)
		{
			FRONT_LEFT_GO;
		}else
		{
			FRONT_LEFT_STOP;
		}
	}
	else if(front_left_speed_duty < 0)//���
	{
		if(speed_count < (-1)*front_left_speed_duty)
		{
			FRONT_LEFT_BACK;
		}else
		{
			FRONT_LEFT_STOP;
		}
	}
	else                //ֹͣ
	{
		FRONT_LEFT_STOP;
	}
	
	
		//��ǰ��
	if(front_right_speed_duty > 0)//��ǰ
	{
		if(speed_count < front_right_speed_duty)
		{
			FRONT_RIGHT_GO;
		}else                //ֹͣ
		{
			FRONT_RIGHT_STOP;
		}
	}
	else if(front_right_speed_duty < 0)//���
	{
		if(speed_count < (-1)*front_right_speed_duty)
		{
			FRONT_RIGHT_BACK;
		}else                //ֹͣ
		{
			FRONT_RIGHT_STOP;
		}
	}
	else                //ֹͣ
	{
		FRONT_RIGHT_STOP;
	}
	
	
	//�����
	if(behind_left_speed_duty > 0)//��ǰ
	{
		if(speed_count < behind_left_speed_duty)
		{
			BEHIND_LEFT_GO;
		}	else                //ֹͣ
		{
			BEHIND_LEFT_STOP;
		}
	}
	else if(behind_left_speed_duty < 0)//���
	{
		if(speed_count < (-1)*behind_left_speed_duty)
		{
			BEHIND_LEFT_BACK;
		}	else                //ֹͣ
		{
			BEHIND_LEFT_STOP;
		}
	}
	else                //ֹͣ
	{
		BEHIND_LEFT_STOP;
	}
	
	
		//�Һ���
	if(behind_right_speed_duty > 0)//��ǰ
	{
		if(speed_count < behind_right_speed_duty)
		{
			BEHIND_RIGHT_GO;
		}	else                //ֹͣ
		{
			BEHIND_RIGHT_STOP;
		}
	}
	else if(behind_right_speed_duty < 0)//���
	{
		if(speed_count < (-1)*behind_right_speed_duty)
		{
			BEHIND_RIGHT_BACK;
		}	else                //ֹͣ
		{
			BEHIND_RIGHT_STOP;
		}
	}
	else                //ֹͣ
	{
		BEHIND_RIGHT_STOP;
	}
}

//speed˵�����������������0-100
//sudu�������Ǹ��ݵ���İ�װ����������ģ���ߺ��ұߵĵ����װ����һ��Ŷ��

//��ǰ
void CarGo(void)
{
	front_left_speed_duty=-sudu;
	front_right_speed_duty=sudu;
  behind_left_speed_duty=-sudu;
  behind_right_speed_duty=sudu;
}

//����
void CarBack(void)
{
	front_left_speed_duty=sudu;
	front_right_speed_duty=-sudu;
  behind_left_speed_duty=sudu;
  behind_right_speed_duty=-sudu;
}

//����
void CarLeft(void)
{
	front_left_speed_duty=sudu;
	front_right_speed_duty=sudu;
  behind_left_speed_duty=sudu;
  behind_right_speed_duty=sudu;
}

//����
void CarRight(void)
{
	front_left_speed_duty=-sudu;
	front_right_speed_duty=-sudu;
  behind_left_speed_duty=-sudu;
  behind_right_speed_duty=-sudu;
}

//ֹͣ
void CarStop(void)
{
	front_left_speed_duty=0;
	front_right_speed_duty=0;
  behind_left_speed_duty=0;
  behind_right_speed_duty=0;
}






//���������ʼ��
void motor_init(void)
{
	MotorGPIO_Configuration();     ////GPIO���ú���
	CarStop();                     //��ͣ
	
	
	
}

		
 void stop_display_execute()//�����ͣ��ʾִ�к���
 {
	 
				if(stop_display_flag==1)//��Ļ��ʾ ��ͣ ��־λ ok��
		{
				        OLED_Clear();	//OLED��Ļ����
			          sudu=10;//�ٶ�����Ϊ10
                OLED_ShowCH(48,1,"��ͣ");		    //��ʾ ��ͣ ����
			          OLED_ShowCH(3,6,"�����ٶ�:");	   //��ʾ �����ٶ� ����
                OLED_ShowNum(80,6,sudu,3,0);    //��ʾ ��ǰ�����ٶ� ��ֵ
			          stop_display_flag=0;//��Ļ��ʾ ��ͣ ��־λΪ��			        
			   	      IrDA=0;
		}

 }	


