/*
*********************************************************************************************************
*���ļ�������д��ͼ�Ĵ��롣
*********************************************************************************************************
*/

#include "delay.h"
#include "DIO.h"
#include "demo_motor.h"
#include "demo_dio.h"
#include "led.h"
#include "beep.h"
#include "carBaseMoves.h"


void Run_wwt_1(void)
{
	//	GetUp();//����
//	MoveHead();//ҡͷ
//	while(1)
//	{
//		if(ETR1 == 0)
//		{
//			Set_Motor(0,0);
//		}
//		else
//		{
//			Gray_Run25();//�Ҷ���ֱ��,���ִ����ٶ�
//			break;
//		}
//	}
	

		Gray_Delay_Run20_20(1500);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)

	
	while(1)
	{
		Gray_Run40();
		if(gray_light_amount() == 0)
		{
			break;
		}
	}
	while(1)
	{
		infrared_35();

		if(gray_light_amount() == 1)
		{
			break;
		}
	}
	while(1)
	{
		Gray_Run40();
		if(ETR1 == 1 && ETR2 == 1)
		{
			break;
		}
	}
	//��ƽ̨
	Gray_Delay_Run35(1500);
	while(1)
	{
		Gray_Run30();
		if(Infrared_DIO1 == 0)
		{
			Set_Motor(0,0);
			delay_ms(20);
			break;
		}
	}
	while(1)
	{
		Turn_Angle_Big(90);
		Turn_Angle_Big(-90);
		break;
	}
	while(1)
	{
		Set_Motor(0,0);
	}
}



