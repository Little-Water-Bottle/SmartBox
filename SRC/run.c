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
#include "demo_DIO_hou.h"

/*
*********************************************************************************************************
*�滮·�ߣ�1��-3��-4��-02����-8Ǭ-05�տ���-06̴��ɽ-07������-5��-1������
������������485��
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*��һ��·�ߣ�1��-3��-4��-02����
*********************************************************************************************************
*/
void Run2(void)
{	

	MoveHead();//ҡͷ
//	MoveHand();//����
	
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
	
	while(1)//����
	{
		Gray_Delay_Run25(800);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		break;
	}
	
	while(1)//������ת
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray2 == 0)
		{	
			Set_Motor(0,0);
			delay_ms(100);
			break;
		}
	}

	zhuanwan_big_left(100);	//ת��
	
	Gray_Delay_Run50(250);	//ֱ��
	
	while(1)//׼�������ٰ�
	{
	  Gray_Run40();
		if(ETR1 == 1 && ETR2 == 1)
		{		
			delay_ms(10);
			if(ETR1 == 1 && ETR2 == 1)
			{
				Set_Motor(0,0);
				delay_ms(80);
				break;
			}
		}
	}
	
	Gray_Delay_Run_Jiansuban(1000);//�ڼ��ٰ��ϴ���ʱ�䣬ע�����
	
	while(1)//�¼��ٰ�
	{
	  Gray_Run_Jiansuban();
		if(ETR1 == 0 && ETR2 == 0)
		{		
			delay_ms(10);
			if(ETR1 == 0 && ETR2 == 0)
				break;
		}
	}

	Gray_Delay_Run_Jiansuban(400);

	while(1)//��ת
	{
		Gray_Run40();  //�Ҷȹ����ٰ�(Jiansuban)
		if(Gray1== 0)
		{	
			Set_Motor(30,30);
			delay_ms(200);
			Set_Motor(0,0);
			delay_ms(100);
			break;
		}
	}
	
	while(1)
	{
		Set_Motor(30,-30);
			delay_ms(100);
		break;
	}
	
	while(1)
	{
		Set_Motor(30,-30);
		if(Gray5 == 0)
		break;
	}

	
	while(1)
	{
		Set_Motor(30,30);
		delay_ms(200);
		break;
	}
	
/*
*��һ��·�ߣ�3��-4��
*/
	
	Gray_Delay_Run50(200);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)		
	Gray_Delay_Run60(200);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
	
	while(1)//����,ǰ��3��
	{
		while(1)
		{
			Gray_Run60();
			if(R_DIO4 == 0)
			{
				Set_Motor(60,60);
				delay_ms(150);
				break;
			}
		}
		break;
	}
	
	Gray_Delay_Run70(600);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
	Gray_Delay_Run50(300);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
	
	
	while(1)//����3��ƽ̨
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(ETR1 == 1 && ETR2 == 1)
		{
			Gray_Delay_Run30(200);
			while(1)
			{
				Gray_Run25();
				if(ETR1 == 0 || ETR2 == 0)
				{
					delay_ms(10);
					if(Infrared_DIO1 == 0)
					{
						break;
					}
				}
			}
			break;
		}
	}

	while(1)//ͣ��3�ޣ����ֵ�ͷ����
	{
		Set_Motor(25,25);//����
		delay_ms(150);
		Set_Motor(0,0);
		delay_ms(100);
		Set_Motor(-25,-25);//����
		delay_ms(140);
		Set_Motor(0,0);
		delay_ms(100);     //���˻���
		Turn_Angle_Big(90);//���ݳ��غ���ѡ������ת����
		delay_ms(50);
		MoveHand();
		Turn_Angle_Big(0);//���ݳ��غ���ѡ������ת����
		delay_ms(50);
		Turn_Angle_Big(-90);//���ݳ��غ���ѡ������ת����
		delay_ms(50);
		MoveHand();
		Turn_Angle_Big(-180);
		delay_ms(50);
		break;
	}
	
	Gray_Delay_Run25(500);
	
	while(1)//ǰ��01��ٸ�
	{
		Gray_Delay_Run40(300);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		Gray_Delay_Run50(1300);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		break;
	}
	
	while(1)//��ת
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray8 == 0)
		{	
			if(Gray8 == 0)
			{
				Set_Motor(0,0);
				delay_ms(150);
				break;
			}
		}
	}
	
	zhuanwan_big_left(300);
	
	while(1)
	{
		Set_Motor(30,30);
		delay_ms(300);
		break;
	}
	
	while(1)//ǰ��01��ٸ�
	{
		Gray_Delay_Run50(300);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		Gray_Delay_Run70(600);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		break;
	}
	
	while(1)//׼������01��ٸ�
	{
		Gray_Delay_Run50(200);
		while(1)
		{
			Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
			if(Infrared_DIO1 == 0)
			{
				Set_Motor(0,0);//����
				delay_ms(100);
				Set_Motor(-20,-20);//����
				delay_ms(150);
				break;
			}
		}
		break;
	}
	zhuanwan_big_left(300);
	
	while(1)//�뿪01��ٸ�
	{
		Gray_Delay_Run40(300);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		Gray_Delay_Run60(1000);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		break;
	}
	
	while(1)//��ת
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray11 == 0)
		{	
			Set_Motor(0,0);//����
			delay_ms(200);
			break;
		}
	}
	
	while(1){
	Set_Motor(-30,30);
	if(Gray4 == 0)
		break;
	}
	
/*
*��һ��·�ߣ�4��-02����
*/
	while(1)//ǰ��4��ƽ̨
	{
		Gray_Delay_Run50(300);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		Gray_Delay_Run70(1000);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		Gray_Delay_Run60(600);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		break;
	}
	
	while(1)
	{	
		Gray_Run40();
		if(Gray1  == 0)
		{
			Set_Motor(0,0);
			delay_ms(100);
			break;
		}
	}
	
		while(1)
	{
		Set_Motor(-30,30);
		delay_ms(100);
		break;
	}
	
	while(1)
	{
		Set_Motor(-30,30);
		if(Gray3 == 0)
		{
			break;
		}
	}
		
	while(1)//ǰ��02����
	{
		Gray_Delay_Run50(800);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		break;
	}
	
	while(1)//��ͷ���뿪02����
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Infrared_DIO1 == 0)
		{
			Set_Motor(30,30);
			delay_ms(50);
			Set_Motor(0,0);
			delay_ms(150);
			Set_Motor(-20,-20);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_left(200);
	
	Gray_Delay_Run50(500);	//ֱ�ߺ���
	
	while(1)//ת������
	{
		Gray_Run40();
		if(Gray1 == 0)
		{
/*	delay_ms(100);*/
			break;
		}
	}

	zhuanwan_big_left(200);
	
	while(1)
	{
		Set_Motor(-40,40);
		delay_ms(100);
		break;
	}
	
	while(1)
	{
		Set_Motor(-30,30);
		if(Gray3 == 0)
			break;
	}
	
	while(1)
	{
		Set_Motor(30,30);
		delay_ms(150);
		break;
	}
	Gray_Delay_Run50(1000);
	
	while(1)//����4��
	{
	  Gray_Run40TaiJie();//�Ҷ���ֱ��,���ִ����ٶ�
		if(ETR1 == 1 && ETR2 == 1)
		{
			Gray_Delay_Run30(200);
			while(1)
			{
				Gray_Run30();
				if(ETR1 == 0 && ETR2 == 0)
				{
					while(1)
					{
						Gray_Run30();
						if(Infrared_DIO1 == 0)
						{
							delay_ms(10);
							if(Infrared_DIO1 == 0)
							{
								delay_ms(150);
								break;
							}
						}
					}
					break;
				}
			}
			break;
		}
	}
	
	while(1)//ͣ��4�룬����������ͷ����
	{
//		Set_Motor(25,25);
//		delay_ms(280);
//		Set_Motor(0,0);
//		delay_ms(150);
//		MoveHand();//����
//		LowerHead();//����
		Set_Motor(-25,-25);//���˻���
		delay_ms(150);
		Set_Motor(0,0);
		delay_ms(150);     //���˻���
		Turn_Angle_Big(270);//���ݳ��غ���ѡ������ת����
		delay_ms(50);
		MoveHand();
		Turn_Angle_Big(180);//���ݳ��غ���ѡ������ת����
		delay_ms(50);
		Turn_Angle_Big(90);//���ݳ��غ���ѡ������ת����
		delay_ms(50);
		MoveHand();
		Turn_Angle_Big(0);//���ݳ��غ���ѡ������ת����
		delay_ms(50);
		break;
	}
	
	Gray_Delay_Run20_20(400);
	
	while(1)//��4��
	{
		Gray_Delay_Run30(200);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		Gray_Delay_Run50(700);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		break;
	}
	
	while(1)//��ת
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray1 == 0)
		{	
			delay_ms(150);
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_left(200);	//ת��
		
/*
*********************************************************************************************************
*�ڶ���·�ߣ�02����-���޸����ˣ�-��5����ݣ�-���ٰ�-7��
*********************************************************************************************************
*/

	while(1)//ֱ��
	{
		Gray_Delay_Run40(200);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		Gray_Delay_Run60(800);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		break;
	}
	
	while(1)//����·��
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray_Count() == 0)
		{
			Set_Motor(10,10);
			delay_ms(100);
			break;
		}
	}
	zhuanwan_big_right(100);
	
	while(1)//����·��
	{
		Gray_Run30();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray_Count() == 0)
		{
			Set_Motor(30,30);
			delay_ms(100);
			break;
		}
	}
	zhuanwan_big_right(100);
	
	while(1)//ֱ��
	{
		Gray_Delay_Run30(300);
		Gray_Delay_Run60(600);
		break;
	}
	
	while(1)//��ת
	{
		Gray_Run50();
		if(Gray_Count() == 0)
		{	
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	zhuanwan_big_left(100);
	
/*
*�ڶ���·�ߣ����޸����ˣ�-��5����ݣ�
*/
	while(1)//�����޸�����
	{
		Gray_Delay_Run20(200);
		Gray_Delay_Run50(200);
		Gray_Delay_Run60(700);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		break;
	}
	
	while(1)//��ת
	{
		Gray_Run50();
		if(Gray8 == 0)
		{	
			delay_ms(50);
			break;
		}
	}
	
	while(1)//��ת
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(gray_light_amount()==8)
		{	
			Set_Motor(-10,-10);
			delay_ms(100);
			Set_Motor(40,-40);
			delay_ms(100);
			break;
		}
	}
	
	while(1)//�˳���ת
	{
		Set_Motor(30,-30);
		if(Gray6 == 0)
		{		
			delay_ms(10);
			if(Gray6 == 0)
			break;
		}
	}
	
	while(1)//ֱ��
	{
		Gray_Delay_Run50(400);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		break;
	}	

	while(1)//��ת
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray8 == 0)
		{	
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_right(200);	//ת��
	
	while(1)//ֱ��
	{
		Gray_Delay_Run50(300);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		Gray_Delay_Run60(300);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
		break;
	}
	
	while(1)	//��������
	{
		Gray_Run40();
		if(ETR1 == 1 && ETR2 == 1)
		{
			while(1)
			{
				Gray_Run30();
				if(ETR1 == 0 && ETR2 == 0)
				{
					break;
				}
			}
			break;
		}
	}
	
	Gray_Delay_Run60(400);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
	Gray_Delay_Run50(200);//�Ҷ���ֱ��,���ִ����ٶ�(���������ʱ��)
	
	while(1)//׼����ת
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray1 == 0)
		{	
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_left(200);	//ת��
	Gray_Delay_Run50(200);	//������
	
	while(1)//��ת
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray1 == 0)
		{	
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_left(200);//ת��
	
	while(1)	//�����ٰ�
	{
		Gray_Run40();
		if(ETR1 == 1 && ETR2 == 1)
		{
			Gray_Delay_Run_Jiansuban(2000);
			while(1)
			{
				Gray_Run_Jiansuban();
				if(ETR1 == 0 && ETR2 == 0)
				{
					break;
				}
			}
			break;
		}
	}
	
	Gray_Delay_Run50(300);
	
	while(1)	//�ϸ�̨
	{
		Gray_Run50();
		if(ETR1 == 1 && ETR2 == 1)
		{
			Gray_Delay_Run50(500);
			while(1)
			{
				Gray_Run50();
				if(gray_light_amount() == 8)
				{
					Gray_Delay_Run30(300);
					while(1)
					{
						Gray_Run30();
						if(Infrared_DIO1 == 0)
						{
							delay_ms(150);
							Set_Motor(0,0);
							delay_ms(100);
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
	
	while(1)//��̨����
	{
		Set_Motor(-25,-25);//���˻���
		delay_ms(100);
		Set_Motor(0,0);
		delay_ms(100);     //���˻���
		Turn_Angle_Big(270);
		delay_ms(50); 
		MoveHand();
		Turn_Angle_Big(180);
		delay_ms(50); 
		Turn_Angle_Big(90);
		delay_ms(50); 
		MoveHand();
		Turn_Angle_Big(0);
		delay_ms(50); 
		break;
	}
	
	Gray_Delay_Run30(400);//�¸�̨
	
	while(1)//�¸�̨
	{
		Gray_Run30();
		if(ETR1 == 0 && ETR2 == 0)
			break;
	}	

	while(1)//�����ٰ�
	{
		Gray_Run40();
		if(ETR1 == 1 && ETR2 == 1)
		{
			Gray_Delay_Run_Jiansuban(2000);
			while(1)
			{
				Gray_Run_Jiansuban();
				if(ETR1 == 0 && ETR2 == 0)
				{
					break;
				}
			}
			break;
		}
	}
	
	Gray_Delay_Run50(300);
	
	while(1)//��ת
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray8 == 0)
		{	
			
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_right(200);
	
	while(1)//��ת
	{
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray1 == 0)
		{	
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_left(200);
	
	while(1)
	{
		Gray_Run50();
		if(ETR1 == 1 && ETR2 == 1)
		{
			Gray_Delay_Run30(2000);
			while(1)
			{
				Gray_Run30();
				if(ETR1 == 0 && ETR2 == 0)
				{
					Gray_Delay_Run30(200);
					break;
				}
			}
			break;
		}
	}
	
	Gray_Delay_Run60(500);
	
	while(1)//�ϸ�̨
	{
		Gray_Run50();
		if(ETR1 == 1 && ETR2 == 1)
			break;
	}
	while(1)//�ϸ�̨
	{
		Gray_Run50();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray_Count() == 0)
		{		
			delay_ms(10);
			if(Gray_Count() == 0)
			{
				Set_Motor(30,30);
				delay_ms(100);
				Set_Motor(25,25);
				delay_ms(800);
				break;
			}
		}
	}
	while(1)//�ϸ�̨
	{
		Gray_Run50();//�Ҷ���ֱ��,���ִ����ٶ�
		if(Gray_Count() == 0)
		{
			Gray_Run30();
			if(Infrared_DIO1 == 0)
			{		
				delay_ms(10);
				if(Infrared_DIO1 == 0)
				{
					delay_ms(100);
					break;
				}
			}
		}
	}	
	
	while(1)//�������̨8Ǭ�����ֵ�ͷ����
	{
//		GetUp();//�������
//		Set_Motor(25,25);
//		delay_ms(180);
//		Set_Motor(0,0);
//		delay_ms(150);
//		MoveHand();//����
//		LowerHead();//����
		Set_Motor(-25,-25);//���˻���
		delay_ms(100);
		Set_Motor(0,0);
		delay_ms(100);     //���˻���
		Turn_Angle_Big(90);
		delay_ms(50); 
		MoveHand();
		Turn_Angle_Big(0);
		delay_ms(50); 
		Turn_Angle_Big(-90);
		delay_ms(50); 
		MoveHand();
		Turn_Angle_Big(-180);
		delay_ms(50); 
//		Turn_Angle_Big(270);//����180;
//		delay_ms(200);  
//		Turn_Angle_Big(184);
//		Set_Motor(0,0);
//		delay_ms(100);     //����
//		LowerHead();//������������
		break;
	}
	Set_Motor(25,25);
	delay_ms(150);
	Gray_Down(200);//���ݳ��ظ������������ʱ��
	while(1)
	{
		Gray_Run30();
		if(Gray_Count() == 0)
		break;
	}
	
	Gray_Down(200);//���ݳ��ظ������������ʱ��
	
	while(1)
	{
		Gray_Run30();
		if(ETR1 == 0 || ETR2 == 0)
		{
			break;
		}
	}
	
	while(1)
	{
		Gray_Run40();
		if(L_DIO3 == 0)
		{
			Set_Motor(30,30);
			delay_ms(100);
			Set_Motor(0,0);
			delay_ms(100); 
			break;
		}
	}
	while(1)
	{
		Set_Motor(-45,45);
		delay_ms(200);
		while(1)
		{
			Set_Motor(-35,35);
			if(Gray3 == 0)
				break;
		}
		break;
	}

	Gray_Delay_Run50(1000);
	
	while(1)
	{
		Gray_Run40();
		if(Gray1 == 0)
			break;
	}
	zhuanwan_big_left(200);
	
	Gray_Delay_Run50(1000);
	
	while(1)
	{
		Gray_Run40();
		if(Gray8 == 0)
			break;
	}
	
	zhuanwan_big_right(150);
	
	Gray_Delay_Run50(600);
	
	while(1)
	{
		Gray_Run40();
		if(Gray8 == 0)
			break;
	}
	
	zhuanwan_big_right(150);
	
	Gray_Delay_Run50(1300);
	
	while(1)
	{
		Gray_Run40();
		if(Gray8 == 0)
			break;
	}
	
	zhuanwan_big_right(150);
	
	while(1)
	{
		Gray_Run30();
		if(Infrared_DIO1 == 0)
		{
			delay_ms(100);
			break;
		}
	}
	
	while(1)
	{
		Gray_Run30_hou();
		if(Gray88 == 0)
		{
			delay_ms(100);
			break;
		}
	}
	
	zhuanwan_big_left(150);
	
	while(1)
	{
		Gray_Run40();
		if(Gray8 == 0)
			break;
	}
	
	zhuanwan_big_right(150);
	
//�ж��Ƿ񵽴�Բ����
	while(1)
	{
		Gray_Run60();
		if(Gray1 == 0)
		{
			if(Gray1 == 1)
			{
				if(Gray1 == 0)
				{
					while(1)
					{
//						Set_Motor(40,40);
//						delay_ms(200);
						break;
					}
				}
			}
			break;
		}
	}
	
////����Բ���˶�
//	while(1)
//	{
//		run_c();
//		if(ETR1 == 1 && ETR2 == 1)
//			break;
//	}
//	
////�������ΰ壬�����ΰ�
//	while(1)
//	{
//		Set_Motor(5,30);
//		delay_ms(100);
//		break;
//	}
//	
////�����ΰ�������
//	while(1)
//	{
//		infrared_35();
//		if(ETR1 == 0 && ETR2 == 0)
//		{
//			Set_Motor(15,30);
//			delay_ms(200);
//			break;
//		}
//	}
//	
////�ػ�����
//	while(1)
//	{
//		run_c();
//		delay_ms(400);
//		break;
//	}
//	
////�ж��Ƿ񵽴�ת�䴦
//	while(1)
//	{
//		run_c();
//		if(Gray1||Gray2	== 0)
//		{
//			break;
//		}
//	}
//	
//	//ת��
//	zhuanwan_big_left(150);
//	
//	while(1)
//	{
//		Gray_Run40();
//		if(ETR1 == 1 && ETR2 == 1)
//		{
//			while(1)
//			{
//				Gray_Run30();
//				if(ETR1 == 0 && ETR2 == 0)
//					break;
//			}
//			break;
//		}
//	}
//	
//	while(1)
//	{
//		Gray_Run30();
//		{
//			if(Infrared_DIO1 == 0)
//			{
//				delay_ms(100);
//				Set_Motor(-30,-30);
//				delay_ms(150);
//				break;
//			}
//		}
//	}
//	
//	while(1)
//	{
//		Set_Motor(-25,-25);//���˻���
//		delay_ms(100);
//		Set_Motor(0,0);
//		delay_ms(100);     //���˻���
//		Turn_Angle_Big(180);
//		delay_ms(50); 
//		Turn_Angle_Big(90);
//		delay_ms(50); 
//		Turn_Angle_Big(0);
//		delay_ms(50); 
//		Turn_Angle_Big(90);
//		delay_ms(50); 
//		break;
//	}
//	
//	while(1)
//	{
//		Gray_Run30_hou();
//		if(Gray88 == 0)
//		{
//			Set_Motor(-40,40);
//			delay_ms(100);
//			break;
//		}
//	}
//	
//	while(1)
//	{
//		Set_Motor(-30,30);
//		if(Gray55 == 0)
//			break;
//	}
//	
//	while(1)
//	{
//		run_c();
//		if(ETR1 == 1 && ETR2 == 1)
//			break;
//	}
//	
//	while(1)
//	{
//		Set_Motor(-20,30);
//		delay_ms(100);
//		break;
//	}
//	
//	while(1)
//	{
//		infrared_35();
//		if(ETR1 == 0 && ETR2 == 0)
//		{
//			Set_Motor(-20,30);
//			delay_ms(200);
//			break;
//		}
//	}
//	
//	while(1)
//	{
//		run_c();
//		delay_ms(400);
//		break;
//	}
//	
//	while(1)
//	{
//		run_c();
//		if(Gray8 == 0)
//		{
//			break;
//		}
//	}

//	while(1)
//	{
//		Set_Motor(30,30);
//		delay_ms(200);
//		break;
//	}
	
	Gray_Delay_Run50(500);
	
	while(1)
	{
		Gray_Run40();
		if(Gray8 == 0)
		{
			break;
		}
	}
	
	zhuanwan_big_right(200);
	Gray_Delay_Run50(200);
	
	while(1)
	{
		Gray_Run40();
		if(Gray8 == 0)
		{
			break;
		}
	}
	
	zhuanwan_big_right(200);
	
	while(1)
	{
		Gray_Run30();
		if(Infrared_DIO1  == 0)
		{
			delay_ms(100);
			break;
		}
	}
	
	while(1)
	{
		Gray_Run30_hou();
		if(Gray88 == 0)
		{
			delay_ms(100);
			break;
		}
	}
	
	zhuanwan_big_left(200);
	
	while(1)
	{
		Gray_Run40();
		if(Gray1 == 0)
		{
			break;
		}
	}
	
	zhuanwan_big_left(200);
	Gray_Delay_Run60(1000);
	Gray_Delay_Run50(300);
	
	while(1)
	{
		Gray_Run40();
		if(Gray1 == 0)
		{
			break;
		}
	}
	
	zhuanwan_big_left(200);
	Gray_Delay_Run50(200);
	
	while(1)
	{
		Gray_Run40();
		if(Gray1 == 0)
		{
			break;
		}
	}
	
	zhuanwan_big_left(200);
	Gray_Delay_Run50(100);
	
	while(1)
	{
		Gray_Run30();
		if(Infrared_DIO1  == 0)
		{
			delay_ms(100);
			break;
		}
	}
	
	while(1)
	{
		Gray_Run30_hou();
		if(Gray88 == 0)
		{
			delay_ms(100);
			break;
		}
	}
	
	zhuanwan_big_right(200);
	Gray_Delay_Run50(100);
	
	while(1)
	{
		Gray_Run40();
		if(Gray1 == 0)
		{
			break;
		}
	}
	
	zhuanwan_big_right(200);
	Gray_Delay_Run60(1500);
	
	while(1)
	{
		Gray_Run40();
		if(ETR1 == 1 && ETR2 == 1)
		{
			break;
		}
	}
	
	while(1)
	{
		Gray_Run40();
		if(ETR1 == 0 && ETR2 == 0)
		{
			while(1)
			{
				Gray_Run30();
				if(Infrared_DIO1 == 0)
					break;
			}
			break;
		}
	}
	
	while(1)
	{
		Set_Motor(-25,-25);//���˻���
		delay_ms(100);
		Set_Motor(0,0);
		delay_ms(100);     //���˻���
		Turn_Angle_Big(90);
		delay_ms(50); 
		MoveHand();
		Turn_Angle_Big(180);
		delay_ms(50); 
		Turn_Angle_Big(270);
		delay_ms(50); 
		MoveHand();
		Turn_Angle_Big(0);
		delay_ms(50); 
		break;
	}
	
	while(1)
	{
		Set_Motor(25,25);
		delay_ms(100);
		Gray_Delay_Run30(200);
		Gray_Delay_Run50(500);
		while(1)
		{
			Gray_Run30();
			if(Gray8 == 0)
			{
				delay_ms(100);
				break;
			}
		}
		break;
	}
	
	zhuanwan_big_right(200);
	Gray_Delay_Run50(500);
	
	while(1)
	{
		Gray_Run40();
		if(gray_light_amount() == 8)
		{
			Set_Motor(30,30);
			delay_ms(100);
			Set_Motor(0,0);
			delay_ms(100);
			break;
		}
	}
	
	zhuanwan_big_right(200);
	Gray_Delay_Run30(300);
	Gray_Delay_Run50(500);
	
	while(1)
	{
		Gray_Run40();
		if(gray_light_amount() == 8)
		{
			Set_Motor(30,30);
			delay_ms(100);
			Set_Motor(0,0);
			delay_ms(100);
			break;
		}
	}
	
	zhuanwan_big_left(100);
	
	while(1)
	{
		Gray_Run30();
		if(gray_light_amount() == 8)
		{
			Set_Motor_1(0,0);
			delay_ms(100);
			break;
		}
	}
	
	zhuanwan_big_left(100);
	
	Gray_Delay_Run50(800);
	
	while(1)
	{
		Gray_Run40();
		if(Gray8 == 0)
		{
			delay_ms(100);
			break;
		}
	}
	
	Gray_Delay_Run60(800);
	Gray_Delay_Run50(500);
	
	while(1)
	{
		Gray_Run40();
		if(Gray8 == 0)
		{
			while(1)
			{
				Gray_Run40();
				if(Gray8 == 1)
				{
					while(1)
					{
						Gray_Run40();
						if(Gray8 == 0)
							break;
					}
					break;
				}
			}
			break;
		}
	}
	
	zhuanwan_big_right(300);
	Gray_Delay_Run50(200);
	
	while(1)
	{
		Gray_Run40();
		if(ETR1 == 1 && ETR2 == 1)
		{
			while(1)
			{
				Gray_Run_Jiansuban(); 
				if(ETR1 == 0 && ETR2 == 0)
				{
					delay_ms(100);
					break;
				}
			}
			break;
		}
	}
	
	Gray_Delay_Run50(400);
	
	while(1)
	{
		Gray_Run40();
		if(Gray8 ==0)
		{
			zhuanwan_big_right(50);
			break;
		}
	}
		
	while(1)
	{
		Gray_Run40();
		if(ETR1 == 1 && ETR2 == 1)
		{
			while(1)
			{
				Gray_Run30();
				if(ETR1 == 0 && ETR2 == 0)
				{
					delay_ms(100);
					break;
				}
			}
			break;
		}
	}
	while(1)
	{
		Turn_Angle_Big(90);//���ݳ��غ���ѡ������ת����
		delay_ms(50);
		Turn_Angle_Big(0);//���ݳ��غ���ѡ������ת����
		delay_ms(50);
		break;
	}
	while(1){Set_Motor(0,0);};
}






