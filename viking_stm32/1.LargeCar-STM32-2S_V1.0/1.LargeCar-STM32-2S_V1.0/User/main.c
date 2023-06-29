
//作者：Laasckp
//时间：2023.06.20
//版本：LargeCar-STM32-2S_V1.0

//功能：红外遥控，显示屏，蓝牙总实验。

//汇总程序：请参考interface.c
//接口定义：请参考interface.h

//说明：部份源码来源网络--请试用24小时后删除

#include "interface.h" //模块接口定义头文件

    int main(void)
 { 	 
	 all_init();//所有想要初始化的函数	
	
    while(1)
  {	 
		 
	 stop_choice();//函数定时执行，LED闪烁，电机停止选择函数。
		
	 stop_display_execute(); //电机暂停显示函数
		
	 speed_set_display_execute();//速度设置执行显示函数  
	    		  	  
	 decode_choice();//红外遥控，蓝牙控制，选择功能函数
    			
  }	
 
 }


	
	

