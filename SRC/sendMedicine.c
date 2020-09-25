#include "sendMedicine.h"
#include "key.h"
#include "pwm.h"
#include "delay.h"
#include "Greay_Init2.h"
#include "lcd.h"
extern int pill1;
extern int pill2;
extern int pill3;
extern int pill4;


int mark1 = 0;	//防止药片长时间未填入，超出则跳出
int mark2 = 0;
int mark3 = 0;
//int mark4 = 0;


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
			mark1++;
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
				mark1 = 0;
			}
			
			//超出循环次数自动跳出
			if(mark1==10) 
			{
				break;
			}
			break;
		
		case '2':
			//pwm7
			mark2++;
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
				mark2 = 0;
			}
			
			//超出循环次数自动跳出
			if(mark2==10) 
			{
				break;
			}
			break;
		
		case '3':
			//pwm8
			mark3++;
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
				mark3 = 0;
			}
			
			//超出循环次数自动跳出
			if(mark3==10) 
			{
				break;
			}
			break;
		
		default: break;
			
	}
}

//粉剂药包送药
void sendPowderMedicine() 
{
	while(pill4)
	{
		//延时5秒后左舵机开始转动
		delay_ms(3000);
		Angle_Adjust1(18);
		Angle1_Adjust1(3);
		
		delay_ms(28000);	//送药时间
		delay_ms(15000);	//收药时间
		//左右舵机停，右舵机开
		
		Angle_Adjust1(15);
		Angle1_Adjust1(7);	//7停下
		
		//pill4 粉剂药包减一
		pill4--;
		LCD_ShowNum(100,295,pill4,1,16);
	}

}

