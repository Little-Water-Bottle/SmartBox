#include "key.h"
#include "delay.h" 
#include "demo_DIO.h" 
#include "led.h"

extern int flag_obstacles_front;
extern int flag_turn;
extern int flag_obstacles;

int pill1=0;	//药片
int pill2=0;
int pill3=0;
int pill4=0;	//粉剂药

void KEY_Init(void)
{
	RCC->AHB1ENR|=1<<1;     //使能PORTB时钟 
	RCC->AHB1ENR|=1<<6;     //使能PORTG时钟abcdefg
	GPIO_Set(GPIOG,PIN13|PIN10|PIN15,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);	
	GPIO_Set(GPIOB,PIN3,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); 

	//初始化KEY5
	RCC->AHB1ENR|=1<<5; //使能PORTF时钟	
	GPIO_Set(GPIOF,PIN8,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); 
} 



u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1 == 0)
		{
			flag_obstacles_front = 2;
			flag_turn = 7;
			flag_obstacles = 1;
		}
		else if(KEY2 == 0)
		{
			flag_obstacles_front = 4;
			flag_turn = 35;
			flag_obstacles = 0;
		}
		else if(KEY3 == 0)
		{
			flag_obstacles_front = 6;
			flag_turn = 1004;
			
		}
		else if(KEY4 == 0)
		{
			flag_obstacles_front = 8;
			flag_turn = 50;
		}
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1; 	    
 	return 0;// 无按键按下
}


u8 KEY_Scan2()
{	 
	static u8 key_up=1;//按键按松开标志		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1 == 0)
		{
			pill1++;
			delay_ms(100);
			return '1';
		}
		if(KEY2 == 0)
		{
			pill2++;
			delay_ms(100);
			return '2';
		}
		 if(KEY3 == 0)
		{
			pill3++;
			delay_ms(100);
			return '3';
		}
		 if(KEY5 == 0)
		{
			pill4++;
			delay_ms(100);
			return '4';
		}
		else if(KEY4 == 0)
		{
//			pill4++;
//			delay_ms(100);
			//药片数量重置
//			pill1=0;
//			pill2=0;
//			pill3=0;
			return '0';
		}
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1)key_up=1;

// 	return '0';// 无按键按下
}


















