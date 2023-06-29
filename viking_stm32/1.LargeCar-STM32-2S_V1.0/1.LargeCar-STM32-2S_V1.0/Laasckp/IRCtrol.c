#include "IRCtrol.h"    //����ң��ͷ�ļ�

unsigned char ir_rec_flag=0;   //����ͷ�������ݱ�־λ 1 �������� 0 û��
unsigned char IRCOM[4];        //�������ң�ط�������
unsigned char continue_time=0; //ͣ��ʱ��
char IrDA = 0;//�������ָ��

//use time3 realize delay systick�Ѿ���main������ʹ���ˣ����ж��в����ظ�ʹ��

void Time3Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 1;
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);//72M / 72 = 1us
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
}

//1us ��ʱ
void DelayUs(vu32 nCount)
{
  u16 TIMCounter = nCount;
  TIM_Cmd(TIM3, ENABLE);//ʹ�ܼ�����
  TIM_SetCounter(TIM3, TIMCounter);
  while (TIMCounter>1)
  {
    TIMCounter = TIM_GetCounter(TIM3);
  }
  TIM_Cmd(TIM3, DISABLE);
}

//�ⲿ�ж����� ����ң������
void IRCtrolInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef 	EXTI_InitStructure;//����һ���ⲿ�ж���صĽṹ��
	NVIC_InitTypeDef NVIC_InitStructure; //����һ���жϵĽṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);
	GPIO_InitStructure.GPIO_Pin = IRIN_PIN;//����ʹ��GPIO�ܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//����GPIOģʽ,��������
	GPIO_Init(IRIN_GPIO , &GPIO_InitStructure);
		
	GPIO_EXTILineConfig(IRIN_PORTSOURCE , IRIN_PINSOURCE);
	EXTI_InitStructure.EXTI_Line = IRIN_EXITLINE;//����Ӧ��GPIO�����ӵ��ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�ж��¼����ͣ��½���
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//ѡ��ģʽ���ж���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ�ܸ��ж�
	EXTI_Init(&EXTI_InitStructure);//�����úõĲ���д��Ĵ���
			
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	 //�׼�Ϊ0������Ƕ��
	NVIC_InitStructure.NVIC_IRQChannel = 	IRIN_IRQCH;//��PINA_8���ⲿ�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//�����ȼ�0�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	//�����ȼ������
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ�ܸ�ģ���ж�
	NVIC_Init(&NVIC_InitStructure);	//�жϳ�ʼ�������ṹ�嶨�������ִ��
	
	Time3Init(); //��ʱ��3��ʼ��
}

/*******************************************************************************
* �� �� �� ��DelayIr
* �������� ��0.14MS ��ʱ
* ��    �� ����
* ��    �� ����
*******************************************************************************/
void DelayIr(unsigned char x)  
{
  while(x--)
 {
  DelayUs(140);
 }
}

void IRIntIsr(void)//����ң�ط������ݽ���
{
  unsigned char j,k,N=0;
	 DelayIr(15);
	 if (IRIN==1) 
     { 
	   return;
	  } 
		 continue_time = 30;//�����źţ���ʾָ����� 30*5 =150ms ��ָ��ͣ��
                           //ȷ��IR�źų���
  while (!IRIN)            //��IR��Ϊ�ߵ�ƽ������9ms��ǰ���͵�ƽ�źš�
    {DelayIr(1);}

 for (j=0;j<4;j++)         //�ռ���������
 { 
  for (k=0;k<8;k++)        //ÿ��������8λ
  {
   while (IRIN)            //�� IR ��Ϊ�͵�ƽ������4.5ms��ǰ���ߵ�ƽ�źš�
     {DelayIr(1);}
    while (!IRIN)          //�� IR ��Ϊ�ߵ�ƽ
     {DelayIr(1);}
     while (IRIN)           //����IR�ߵ�ƽʱ��
      {
    DelayIr(1);
    N++;           
    if (N>=30)
	 { 
	 return;}                  //0.14ms���������Զ��뿪��
      }                        //�ߵ�ƽ�������                
     IRCOM[j]=IRCOM[j] >> 1;                  //�������λ����0��
     if (N>=8) {IRCOM[j] = IRCOM[j] | 0x80;}  //�������λ����1��
     N=0;
  }//end for k
 }//end for j
   
	k = ~IRCOM[3];
   if (IRCOM[2] != k)
   { 
     return; }
	 
   IrDA=IRCOM[2];//��ֵ
	 
	 
	 
		
	
}

