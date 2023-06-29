#include "timer.h"//��ʱ��ͷ�ļ�

unsigned char Time_10us_sum = 0;        //10us����������Ϊ�������Ļ�������
unsigned char Time_1ms = 0;            //1ms����������Ϊ���ֺ����Ļ�������
unsigned char Time_5ms = 0;            //5ms����������Ϊ���ֺ����Ļ�������
/**-------------------------------------------------------
  * @������ NVIC_TIM2Configuration
  * @����   2
  * @����   ��
  * @����ֵ ��
***------------------------------------------------------*/
static void NVIC_TIM2Configuration(void)//��ʱ��2���ж�����
{ 
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Set the Vector Table base address at 0x08000000 */
    //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);

    /* Enable the TIM2 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

void TIM2_Init(void)//��ʱ��2��ʼ��
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* Time base configuration */
    //��������Զ�װ�صļ���ֵ�����ڼ����Ǵ�0��ʼ�ģ�����Ϊ10us
    TIM_TimeBaseStructure.TIM_Period = (10- 1);//100kHz
    // �������Ԥ��Ƶϵ����������Ϊ0ʱ��ʾ����Ƶ����Ҫ��1
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);//1MHz
    // �߼�Ӧ�ñ��β��漰�������ڶ�ʱ��ʱ��(CK_INT)Ƶ���������˲���(ETR,TIx)
    // ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    //���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //��ʼ����ʱ��2
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* Clear TIM2 update pending flag[���TIM2����жϱ�־] */
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

    /* TIM IT enable */ //������ж�
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);  //������ʹ�ܣ���ʼ����

    /* �жϲ������� */
    NVIC_TIM2Configuration();
}


/**-------------------------------------------------------
  * @������ TIM2_IRQHandler
  * @����   TIM2�жϴ�������ÿ10us�ж�һ�� 
  * @����   ��
  * @����ֵ ��
***------------------------------------------------------*/
void TIM2_IRQHandler(void)
{
    /* www.armjishu.com ARM������̳ */

    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
			
				    Time_10us_sum++;   //10us��һ
		        Time_10us_motor++; //10us��һ
		        
							
		if(Time_10us_sum >= 100)//1ms
		{
			Time_10us_sum = 0;         
			Time_1ms++;                // 1ms��һ         
			
						 
		}
		
		if(Time_10us_motor >= 1)//0.01ms
		{
				   
					Time_10us_motor = 0;
			
					speed_count++;   //10us��һ
					
					if(speed_count >=10)
					{
						speed_count = 0;
					}
					    
	             CarMove();  //�����������
	 
				}
		
		
			   
    }
}


