#include "uart.h"//����ͷ�ļ�

unsigned char BT_flag=0;//�������Ʊ�־λ
char BT = 0;//��������ָ��
//UART function
//UART3 TxD GPIOB10   RxD GPIOB11
void USART3Conf(u32 baudRate)//���ڳ�ʼ��
{
	NVIC_InitTypeDef 	NVIC_InitStruct;//����һ�������жϵĽṹ��	
	USART_InitTypeDef USART_InitSturct;//���崮�ڵĳ�ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;//���崮�ڶ�Ӧ�ܽŵĽṹ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);//�򿪴���3�ܽ�ʱ��
	//USART3_Tx_Pin Configure 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;//��������ٶ�50MHz
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//���츴�����
	GPIO_Init(GPIOB , &GPIO_InitStruct);//����ʼ���õĽṹ��װ��Ĵ���

//USART3_Rx_Pin Configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIOģʽ��������
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;//��������
  GPIO_Init(GPIOB, &GPIO_InitStruct);//����ʼ���õĽṹ��װ��Ĵ���

//USART3 Configure	
	USART_InitSturct.USART_BaudRate = baudRate;//������19200
	USART_InitSturct.USART_WordLength = USART_WordLength_8b;//���ݿ��8λ
	USART_InitSturct.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitSturct.USART_Parity = USART_Parity_No;//����żУ��
	USART_InitSturct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitSturct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//ʹ�ܷ��������
	USART_Init(USART3 , &USART_InitSturct);//����ʼ���õĽṹ��װ��Ĵ���	
	//USART3_INT Configure
	USART_ITConfig(USART3 , USART_IT_RXNE , ENABLE);//ʹ�ܽ����ж�
//	USART_ITConfig(USART3 , USART_IT_TXE , ENABLE);
	USART_Cmd(USART3 , ENABLE);//�򿪴���3
	USART_ClearFlag(USART3 , USART_FLAG_TC);//�����һ�����ݷ���ʧ�ܵ�����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//�򿪸��ж�
	NVIC_Init(&NVIC_InitStruct);
	
}

void PutChar(u8 Data)
{
	USART_SendData(USART3 , Data);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);//�ȴ��������
}
void PutStr(char *str)//����һ���ַ���
{
	while(*str != '\0')
	{
		USART_SendData(USART3 , *str++);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);//�ȴ��������
	}
}

void PutNChar(u8 *buf , u16 size)
{
  u8 i;
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET); //��ֹ��һ�ֽڶ�ʧ
	for(i=0;i<size;i++)
	{
		 USART_SendData(USART3 , buf[i]);
		 while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);//�ȴ��������
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
		//���⴮�ڸ���
if(rec_data == 0x18||rec_data == 0x52||rec_data == 0x08||rec_data == 0x5A|| 
	 rec_data == 0x1C||rec_data == 0x45||rec_data == 0x46||rec_data == 0x47||
   rec_data == 0x16||rec_data == 0x0D||rec_data == 0x44||rec_data == 0x40||
   rec_data == 0x43)
	{
			BT_flag = 1;
			IrDA = rec_data;
			continue_time = 40;	//�����źţ���ʾָ����� 40*5 = 200ms ��ָ��ͣ��	
		}
  }
}



//UART function
//UART2 TxD GPIOA2   RxD GPIOA3
void USART2Conf(u32 baudRate)//���ڳ�ʼ��
{
	NVIC_InitTypeDef 	NVIC_InitStruct;//����һ�������жϵĽṹ��	
	USART_InitTypeDef USART_InitSturct;//���崮�ڵĳ�ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;//���崮�ڶ�Ӧ�ܽŵĽṹ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);//�򿪴���2�ܽ�ʱ��
	//USART2_Tx_Pin Configure 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;//��������ٶ�50MHz
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//���츴�����
	GPIO_Init(GPIOA , &GPIO_InitStruct);//����ʼ���õĽṹ��װ��Ĵ���

//USART2_Rx_Pin Configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIOģʽ��������
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;//��������
  GPIO_Init(GPIOA, &GPIO_InitStruct);//����ʼ���õĽṹ��װ��Ĵ���

//USART2 Configure	
	USART_InitSturct.USART_BaudRate = baudRate;//������19200
	USART_InitSturct.USART_WordLength = USART_WordLength_8b;//���ݿ��8λ
	USART_InitSturct.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitSturct.USART_Parity = USART_Parity_No;//����żУ��
	USART_InitSturct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitSturct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//ʹ�ܷ��������
	USART_Init(USART2 , &USART_InitSturct);//����ʼ���õĽṹ��װ��Ĵ���	
	//USART2_INT Configure
	USART_ITConfig(USART2 , USART_IT_RXNE , ENABLE);//ʹ�ܽ����ж�
//	USART_ITConfig(USART2 , USART_IT_TXE , ENABLE);
	USART_Cmd(USART2 , ENABLE);//�򿪴���2
	USART_ClearFlag(USART2 , USART_FLAG_TC);//�����һ�����ݷ���ʧ�ܵ�����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//�򿪸��ж�
	NVIC_Init(&NVIC_InitStruct);
	
}

void PutChar2(u8 Data)
{
	USART_SendData(USART2 , Data);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);//�ȴ��������
}
void PutStr2(char *str)//����һ���ַ���
{
	while(*str != '\0')
	{
		USART_SendData(USART2 , *str++);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);//�ȴ��������
	}
}

void PutNChar2(u8 *buf , u16 size)
{
  u8 i;
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); //��ֹ��һ�ֽڶ�ʧ
	for(i=0;i<size;i++)
	{
		 USART_SendData(USART2 , buf[i]);
		 while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);//�ȴ��������
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
		//���⴮�ڸ���
if(rec_data == 0x18||rec_data == 0x52||rec_data == 0x08||rec_data == 0x5A|| 
	 rec_data == 0x1C||rec_data == 0x45||rec_data == 0x46||rec_data == 0x47||
   rec_data == 0x16||rec_data == 0x0D||rec_data == 0x44||rec_data == 0x40||
   rec_data == 0x43)
	{
			BT_flag = 1;
			IrDA = rec_data;
			continue_time = 40;	//�����źţ���ʾָ����� 40*5 = 200ms ��ָ��ͣ��	
		}
  }
}


