#include "timer.h"//定时器头文件

unsigned char Time_10us_sum = 0;        //10us计数器，作为主函数的基本周期
unsigned char Time_1ms = 0;            //1ms计数器，作为部分函数的基本周期
unsigned char Time_5ms = 0;            //5ms计数器，作为部分函数的基本周期
/**-------------------------------------------------------
  * @函数名 NVIC_TIM2Configuration
  * @功能   2
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
static void NVIC_TIM2Configuration(void)//定时器2的中断配置
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

void TIM2_Init(void)//定时器2初始化
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* Time base configuration */
    //这个就是自动装载的计数值，由于计数是从0开始的，周期为10us
    TIM_TimeBaseStructure.TIM_Period = (10- 1);//100kHz
    // 这个就是预分频系数，当由于为0时表示不分频所以要减1
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);//1MHz
    // 高级应用本次不涉及。定义在定时器时钟(CK_INT)频率与数字滤波器(ETR,TIx)
    // 使用的采样频率之间的分频比例
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    //向上计数
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //初始化定时器2
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* Clear TIM2 update pending flag[清除TIM2溢出中断标志] */
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

    /* TIM IT enable */ //打开溢出中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);  //计数器使能，开始工作

    /* 中断参数配置 */
    NVIC_TIM2Configuration();
}


/**-------------------------------------------------------
  * @函数名 TIM2_IRQHandler
  * @功能   TIM2中断处理函数，每10us中断一次 
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void TIM2_IRQHandler(void)
{
    /* www.armjishu.com ARM技术论坛 */

    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
			
				    Time_10us_sum++;   //10us加一
		        Time_10us_motor++; //10us加一
		        
							
		if(Time_10us_sum >= 100)//1ms
		{
			Time_10us_sum = 0;         
			Time_1ms++;                // 1ms加一         
			
						 
		}
		
		if(Time_10us_motor >= 1)//0.01ms
		{
				   
					Time_10us_motor = 0;
			
					speed_count++;   //10us加一
					
					if(speed_count >=10)
					{
						speed_count = 0;
					}
					    
	             CarMove();  //电机驱动函数
	 
				}
		
		
			   
    }
}


