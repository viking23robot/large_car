#include "uart.h"//串口头文件

unsigned char BT_flag=0;//蓝牙控制标志位
char BT = 0;//蓝牙控制指令
//UART function
//UART3 TxD GPIOB10   RxD GPIOB11
void USART3Conf(u32 baudRate)//串口初始化
{
	NVIC_InitTypeDef 	NVIC_InitStruct;//定义一个设置中断的结构体	
	USART_InitTypeDef USART_InitSturct;//定义串口的初始化结构体
	GPIO_InitTypeDef GPIO_InitStruct;//定义串口对应管脚的结构体

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);//打开串口3管脚时钟
	//USART3_Tx_Pin Configure 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;//输出引脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;//设置最高速度50MHz
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//推挽复用输出
	GPIO_Init(GPIOB , &GPIO_InitStruct);//将初始化好的结构体装入寄存器

//USART3_Rx_Pin Configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO模式悬浮输入
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;//输入引脚
  GPIO_Init(GPIOB, &GPIO_InitStruct);//将初始化好的结构体装入寄存器

//USART3 Configure	
	USART_InitSturct.USART_BaudRate = baudRate;//波特率19200
	USART_InitSturct.USART_WordLength = USART_WordLength_8b;//数据宽度8位
	USART_InitSturct.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitSturct.USART_Parity = USART_Parity_No;//无奇偶校验
	USART_InitSturct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitSturct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//使能发送与接收
	USART_Init(USART3 , &USART_InitSturct);//将初始化好的结构体装入寄存器	
	//USART3_INT Configure
	USART_ITConfig(USART3 , USART_IT_RXNE , ENABLE);//使能接收中断
//	USART_ITConfig(USART3 , USART_IT_TXE , ENABLE);
	USART_Cmd(USART3 , ENABLE);//打开串口3
	USART_ClearFlag(USART3 , USART_FLAG_TC);//解决第一个数据发送失败的问题
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//打开该中断
	NVIC_Init(&NVIC_InitStruct);
	
}

void PutChar(u8 Data)
{
	USART_SendData(USART3 , Data);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);//等待发送完毕
}
void PutStr(char *str)//发送一个字符串
{
	while(*str != '\0')
	{
		USART_SendData(USART3 , *str++);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);//等待发送完毕
	}
}

void PutNChar(u8 *buf , u16 size)
{
  u8 i;
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET); //防止第一字节丢失
	for(i=0;i<size;i++)
	{
		 USART_SendData(USART3 , buf[i]);
		 while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);//等待发送完毕
	}
}


/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
	unsigned char rec_data;
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    /* Read one byte from the receive data register */
    rec_data = USART_ReceiveData(USART3);
		//避免串口干扰
if(rec_data == 0x18||rec_data == 0x52||rec_data == 0x08||rec_data == 0x5A|| 
	 rec_data == 0x1C||rec_data == 0x45||rec_data == 0x46||rec_data == 0x47||
   rec_data == 0x16||rec_data == 0x0D||rec_data == 0x44||rec_data == 0x40||
   rec_data == 0x43)
	{
			BT_flag = 1;
			IrDA = rec_data;
			continue_time = 40;	//连发信号，表示指令持续 40*5 = 200ms 无指令停车	
		}
  }
}



//UART function
//UART2 TxD GPIOA2   RxD GPIOA3
void USART2Conf(u32 baudRate)//串口初始化
{
	NVIC_InitTypeDef 	NVIC_InitStruct;//定义一个设置中断的结构体	
	USART_InitTypeDef USART_InitSturct;//定义串口的初始化结构体
	GPIO_InitTypeDef GPIO_InitStruct;//定义串口对应管脚的结构体

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);//打开串口2管脚时钟
	//USART2_Tx_Pin Configure 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;//输出引脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;//设置最高速度50MHz
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//推挽复用输出
	GPIO_Init(GPIOA , &GPIO_InitStruct);//将初始化好的结构体装入寄存器

//USART2_Rx_Pin Configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO模式悬浮输入
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;//输入引脚
  GPIO_Init(GPIOA, &GPIO_InitStruct);//将初始化好的结构体装入寄存器

//USART2 Configure	
	USART_InitSturct.USART_BaudRate = baudRate;//波特率19200
	USART_InitSturct.USART_WordLength = USART_WordLength_8b;//数据宽度8位
	USART_InitSturct.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitSturct.USART_Parity = USART_Parity_No;//无奇偶校验
	USART_InitSturct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitSturct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//使能发送与接收
	USART_Init(USART2 , &USART_InitSturct);//将初始化好的结构体装入寄存器	
	//USART2_INT Configure
	USART_ITConfig(USART2 , USART_IT_RXNE , ENABLE);//使能接收中断
//	USART_ITConfig(USART2 , USART_IT_TXE , ENABLE);
	USART_Cmd(USART2 , ENABLE);//打开串口2
	USART_ClearFlag(USART2 , USART_FLAG_TC);//解决第一个数据发送失败的问题
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//打开该中断
	NVIC_Init(&NVIC_InitStruct);
	
}

void PutChar2(u8 Data)
{
	USART_SendData(USART2 , Data);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);//等待发送完毕
}
void PutStr2(char *str)//发送一个字符串
{
	while(*str != '\0')
	{
		USART_SendData(USART2 , *str++);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);//等待发送完毕
	}
}

void PutNChar2(u8 *buf , u16 size)
{
  u8 i;
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); //防止第一字节丢失
	for(i=0;i<size;i++)
	{
		 USART_SendData(USART2 , buf[i]);
		 while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);//等待发送完毕
	}
}


/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
	unsigned char rec_data;
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    /* Read one byte from the receive data register */
    rec_data = USART_ReceiveData(USART2);
		//避免串口干扰
if(rec_data == 0x18||rec_data == 0x52||rec_data == 0x08||rec_data == 0x5A|| 
	 rec_data == 0x1C||rec_data == 0x45||rec_data == 0x46||rec_data == 0x47||
   rec_data == 0x16||rec_data == 0x0D||rec_data == 0x44||rec_data == 0x40||
   rec_data == 0x43)
	{
			BT_flag = 1;
			IrDA = rec_data;
			continue_time = 40;	//连发信号，表示指令持续 40*5 = 200ms 无指令停车	
		}
  }
}


