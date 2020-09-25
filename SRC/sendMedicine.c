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


int mark1 = 0;	//��ֹҩƬ��ʱ��δ���룬����������
int mark2 = 0;
int mark3 = 0;
//int mark4 = 0;


void  sendProcess(u8 pill);

//��ҩ���̣�����ҩ���������
u8 sendMedicine() 
{
	//�����ҩ
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

//����������ҩ����
void  sendProcess(u8 pill)
{
	switch(pill)
	{
		case '1':
			//pwm6
			mark1++;
			Angle_Adjust2(5);	//����Ƴ�������ȡҩ
			delay_ms(500);
			Angle_Adjust2(17);	//�������ģ��Ҷȼ��
			delay_ms(500);
			
			//�Ҷ�1����Ƿ�װ����ҩƬ
			if(Gray111==0)
			{
				pill1--;
				LCD_ShowNum(82,180,pill1,2,12);
				Angle_Adjust2(25);	//�����ƶ����ͳ�ҩƬ
				delay_ms(500);
				mark1 = 0;
			}
			
			//����ѭ�������Զ�����
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
			
			//����ѭ�������Զ�����
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
			
			//����ѭ�������Զ�����
			if(mark3==10) 
			{
				break;
			}
			break;
		
		default: break;
			
	}
}

//�ۼ�ҩ����ҩ
void sendPowderMedicine() 
{
	while(pill4)
	{
		//��ʱ5���������ʼת��
		delay_ms(3000);
		Angle_Adjust1(18);
		Angle1_Adjust1(3);
		
		delay_ms(28000);	//��ҩʱ��
		delay_ms(15000);	//��ҩʱ��
		//���Ҷ��ͣ���Ҷ����
		
		Angle_Adjust1(15);
		Angle1_Adjust1(7);	//7ͣ��
		
		//pill4 �ۼ�ҩ����һ
		pill4--;
		LCD_ShowNum(100,295,pill4,1,16);
	}

}

