#include "sendMedicine.h"
#include "key.h"
#include "pwm.h"
#include "delay.h"
#include "Greay_Init2.h"
#include "lcd.h"
extern int pill1;
extern int pill2;
extern int pill3;


void  sendProcess(u8 pill);

//送药过程，送完药物，结束函数
u8 sendMedicine() 
{
	//舵机送药
	while(1) 
	{
		while(pill1>0) 
		{
			sendProcess('1');
		}
		while(pill2>0) 
		{
			sendProcess('2');
		}
		while(pill3>0) 
		{
			sendProcess('3');
		}
		
		if(pill1+pill2+pill3<=0)
		{
			return '0';
		}
		
	}
}

//三个完整送药过程
void  sendProcess(u8 pill)
{
	switch(pill)
	{
		case '1':
			//pwm6
			Angle_Adjust2(5);	//向后移出，进行取药
			delay_ms(500);
			Angle_Adjust2(17);	//步入中心，灰度检测
			delay_ms(500);
			
			//灰度1检查是否装入了药片
			if(Gray111==0)
			{
				pill1--;
				LCD_ShowNum(82,180,pill1,2,12);
				Angle_Adjust2(25);	//向外移动，送出药片
		    delay_ms(500);
			}
			
			break;
		
		case '2':
			//pwm7
			Angle_Adjust3(5);
			delay_ms(500);
			Angle_Adjust3(17);
			delay_ms(500);
		
			if(Gray222==0)
			{
				pill2--;
				LCD_ShowNum(82,200,pill1,2,12);
				Angle_Adjust3(25);
			  delay_ms(500);
			}
			
			break;
		
		case '3':
			//pwm8
			Angle_Adjust4(5);
			delay_ms(500);
			Angle_Adjust4(17);
			delay_ms(500);
		
			if(Gray333==0)
			{
				pill3--;
				LCD_ShowNum(82,220,pill1,2,12);
				Angle_Adjust4(25);
			  delay_ms(500);
			}
			
			break;
		
		default: break;
			
	}
}

//单个舵机的送药过程
void singleSendProcess() 
{
	
}

