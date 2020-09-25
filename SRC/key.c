#include "key.h"
#include "delay.h" 
#include "demo_DIO.h" 
#include "led.h"

extern int flag_obstacles_front;
extern int flag_turn;
extern int flag_obstacles;

int pill1=0;	//ҩƬ
int pill2=0;
int pill3=0;
int pill4=0;	//�ۼ�ҩ

void KEY_Init(void)
{
	RCC->AHB1ENR|=1<<1;     //ʹ��PORTBʱ�� 
	RCC->AHB1ENR|=1<<6;     //ʹ��PORTGʱ��abcdefg
	GPIO_Set(GPIOG,PIN13|PIN10|PIN15,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);	
	GPIO_Set(GPIOB,PIN3,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); 

	//��ʼ��KEY5
	RCC->AHB1ENR|=1<<5; //ʹ��PORTFʱ��	
	GPIO_Set(GPIOF,PIN8,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); 
} 



u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_ms(10);//ȥ���� 
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
 	return 0;// �ް�������
}


u8 KEY_Scan2()
{	 
	static u8 key_up=1;//�������ɿ���־		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0))
	{
		delay_ms(10);//ȥ���� 
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
			//ҩƬ��������
//			pill1=0;
//			pill2=0;
//			pill3=0;
			return '0';
		}
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1)key_up=1;

// 	return '0';// �ް�������
}


















