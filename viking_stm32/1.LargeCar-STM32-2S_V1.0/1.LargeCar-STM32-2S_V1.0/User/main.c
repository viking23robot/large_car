
//���ߣ�Laasckp
//ʱ�䣺2023.06.20
//�汾��LargeCar-STM32-2S_V1.0

//���ܣ�����ң�أ���ʾ����������ʵ�顣

//���ܳ�����ο�interface.c
//�ӿڶ��壺��ο�interface.h

//˵��������Դ����Դ����--������24Сʱ��ɾ��

#include "interface.h" //ģ��ӿڶ���ͷ�ļ�

    int main(void)
 { 	 
	 all_init();//������Ҫ��ʼ���ĺ���	
	
    while(1)
  {	 
		 
	 stop_choice();//������ʱִ�У�LED��˸�����ֹͣѡ������
		
	 stop_display_execute(); //�����ͣ��ʾ����
		
	 speed_set_display_execute();//�ٶ�����ִ����ʾ����  
	    		  	  
	 decode_choice();//����ң�أ��������ƣ�ѡ���ܺ���
    			
  }	
 
 }


	
	

