#include "speed_set.h"//�ٶ�����ͷ�ļ�

 unsigned char sudu=10;                    //С����ʼ�ٶ�����Ϊ5
 unsigned char speed_and_flag;            //С���ٶ����üӱ�־λ
 unsigned char speed_subtract_flag;     //С���ٶ����ü���־λ
 
 
 void speed_and()//С���ٶȼ����㺯��
 {
	
	sudu+=1;   //�����ٶ�ÿ�μ�1     
	
	if(sudu>=10)//�����ٶ����Ϊ10
	{
		sudu=10;   
	}
	
 }


 void speed_subtract()//С���ٶȼ����㺯��
 {
	
	sudu-=1;     //�����ٶ�ÿ�μ�1     
	
	if(sudu<=0)//�����ٶ���СΪ0
	{
		sudu=0; 
	}
	
	if(sudu>=10)
	{
		sudu=0; 
	}
 }
 
 void speed_set_display_execute()//�ٶ�����ִ�к���ʾ����
 {
	 
		if(speed_and_flag==1) //�ٶȼӱ�־λ��1
							
			{					
				speed_and();                   //С���ٶȼ����㺯��
				OLED_ShowNum(80,6,sudu,3,0);  //��ʾ��ǰ�����ٶ�
				speed_and_flag=0;            //С���ٶȼӱ�־λ ��0		
			  IrDA=0;
			}
			
			if(speed_subtract_flag==1)//�ٶȼ���־λ��1
							
			{				
				speed_subtract();              //С���ٶȼ����㺯��
				OLED_ShowNum(80,6,sudu,3,0);  //��ʾ��ǰ�����ٶ�
				speed_subtract_flag=0;	     //С���ٶȼ���־λ ��0	
       	IrDA=0;
			}		
			 
 }
       


