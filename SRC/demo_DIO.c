/*
*********************************************************************************************************
*���ļ�������д��ͼ�ļ��е�һЩ�����Ĵ��롣
*********************************************************************************************************
*/


#include "demo_dio.h"
#include "beep.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "delay.h"
#include "wt61.h"
#include "lcd.h"
#include "carBaseMoves.h"
#include "pid.h"
#include "api.h"
#include "demo_motor.h"
#include "math.h"

int set_speed;
int flag_turn = 0;
int flag_obstacles_front = 0;
int flag_obstacles_behind;
int queue1;
int flag_line;//�Ƿ�ر�PIDֱ�߹���
int flag_gray = 1;//�Ƿ�رջҶ�ɨ�蹦��
int flag_obstacles = 1;//�Ƿ�ر�ǰ���ϰ���⹦��;
int flag_queue;
int stop;
int door;
extern struct SAngle 	stcAngle;
extern int site[8];
int i,act_angle;
static u8 DIR = 0;

//extern u8 half_s;

/*
*********************************************************************************************************
*	�� �� ��: Gray_Go
*	����˵��: �������ӽ����Ƿ���ȷ
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Go(u8 speed)//1234 5678
{
	while(1)
	{
		CarAdvance(speed);//������ת
		delay_ms(3000);
		
//		CarRetreat(speed);//���ַ�ת
//		delay_ms(3000);
//		
//		SetLeftWhell(0,speed);SetRightWhell(1,0);
//		delay_ms(3000);   //������ת�����ֲ�ת
//		
//		SetLeftWhell(1,speed);SetRightWhell(1,0);
//		delay_ms(3000);   //���ַ�ת�����ֲ�ת
//		
//		SetRightWhell(0,speed);SetLeftWhell(1,0);
//		delay_ms(3000);   //���ֲ�ת��������ת
//		 
//		SetRightWhell(1,speed);SetLeftWhell(1,0);
//		delay_ms(3000);   //���ֲ�ת�����ַ�ת
	}
}
/*
*********************************************************************************************************
*	�� �� ��: Brake_Stop
*	����˵��: ɲ������
*	��    ��: speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Brake_Stop()//����Ϊ0
{
	if((Gray1 == 1 && Gray2 == 1 && Gray3 == 1 && 
		Gray4 == 1 && Gray5 == 1 && Gray6 == 1 && Gray7 == 1 && Gray8 == 1))
	{
		CarAdvance(0);//ɲ��
		delay_ms(100);
	}
}

/*
********************************************************************
*	�� �� ��: Gray
*	����˵��: �жϻҶȵڼ�������
*	��    ��: number 	�ж��ĸ��ĵ���
*	�� �� ֵ: 0��1
**********************************************************************/
int Gray(int number)
{
	u8 value;
	switch(number)
	{
		case 1 :if(Gray1==1) value=1; else value=0;break;
		case 2 :if(Gray2==1) value=1; else value=0;break;
		case 3 :if(Gray3==1) value=1; else value=0;break;
		case 4 :if(Gray4==1) value=1; else value=0;break;
		case 5 :if(Gray5==1) value=1; else value=0;break;
		case 6 :if(Gray6==1) value=1; else value=0;break;
		case 7 :if(Gray7==1) value=1; else value=0;break;
		case 8 :if(Gray8==1) value=1; else value=0;break;

	}
	if(value==1)
		return 0;
	else
		return 1;	
}

/*
********************************************************************
*	�� �� ��: Gray_Count
*	����˵��: ����Ҷ����ĸ���
*	��    ��: ��
*	�� �� ֵ: ��������
**********************************************************************/
int Gray_Count()
{
	return(Gray(1)+Gray(2)+Gray(3)+Gray(4)+Gray(5)+Gray(6)+Gray(7)+Gray(8));
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Run
*	����˵��: �Ҷȿ���ֱ�߳���
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run(u8 speed)//1234 5678
{
	if((Gray4 == 0) || (Gray5 == 0))
		{
			SetLeftWhell(0,speed);SetRightWhell(0,speed);
		}	
	else if(Gray2 == 0 && Gray3 == 0)
		{
			SetLeftWhell(0,0);SetRightWhell(0,speed);
		}
	else if(Gray7 == 0 && Gray6 == 0)
		{
			SetLeftWhell(0,speed);SetRightWhell(0,0);
		}		
	else if((Gray5 == 0) && (Gray6 == 0))
		{	
			SetLeftWhell(0,speed);SetRightWhell(0,0);
		}
	else if((Gray3 == 0) && (Gray4 == 0))
		{	
			SetLeftWhell(0,0);SetRightWhell(0,speed);
		}
	else if(Gray1 == 0)
		{
			SetLeftWhell(1,20);SetRightWhell(0,speed);
		}
	else if(Gray8 == 0)
		{
			SetLeftWhell(0,speed);SetRightWhell(1,20);
		}
		else 		
		{
			CarAdvance(speed);
		}
}


void Gray_Run_1(u8 speed)//1234 5678
{
	if((Gray4 == 0) || (Gray5 == 0))
		{
			SetLeftWhell(0,speed);SetRightWhell(0,speed);
		}	
	else if(Gray2 == 0 && Gray3 == 0)
		{
			SetLeftWhell(0,0);SetRightWhell(0,speed);
		}
	else if(Gray7 == 0 && Gray6 == 0)
		{
			SetLeftWhell(0,speed);SetRightWhell(0,0);
		}		
	else if((Gray5 == 0) && (Gray6 == 0))
		{	
			SetLeftWhell(0,speed);SetRightWhell(0,0);
		}
	else if((Gray3 == 0) && (Gray4 == 0))
		{	
			SetLeftWhell(0,0);SetRightWhell(0,speed);
		}
	else if(Gray1 == 0)
		{
			SetLeftWhell(1,20);SetRightWhell(0,speed);
		}
	else if(Gray8 == 0)
		{
			SetLeftWhell(0,speed);SetRightWhell(1,20);
		}
		else 		
		{
			CarAdvance(speed);
		}
}


 /*
*********************************************************************************************************
*	�� �� ��: Gray_Run15
*	����˵��: �Ҷȿ���ֱ�߳���  ���ڴӸ�̨������
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run15()//������
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(14,15); }
	
	if(Gray4 == 0)       { Set_Motor(8,15); }
	if(Gray5 == 0)       { Set_Motor(14,9); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(3,25); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(14,3); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(6,25); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(14,7); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(1,30); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(14,1); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(-5,25); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(14,-3); }
	
	else    	{ Set_Motor(14,15); }	
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Run20_20
*	����˵��: �Ҷȿ���ֱ�߳���  ���ڴ����ƽ̨������
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run20_20()//���ڴ����ƽ̨������
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(20,20); }
	
	if(Gray4 == 0)       { Set_Motor(12,20); }
	if(Gray5 == 0)       { Set_Motor(20,12); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(8,20); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(20,8); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(10,20); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(20,10); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(5,20); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(20,5); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(0,20); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(20,0); }
	
	else    	{ Set_Motor(20,20); }	
}



/*
*********************************************************************************************************
*	�� �� ��: Gray_Run20
*	����˵��: �Ҷȿ���ֱ�߳���  ���ڴӵ�һ����̨�����ã���ֹ��
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run20()//������
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(15,25); }
	
	if(Gray4 == 0)       { Set_Motor(20,25); }
	if(Gray5 == 0)       { Set_Motor(25,18); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(6,25); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(16,11); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(8,25); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(16,13); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(3,25); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(16,8); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(0,25); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(16,4); }
	
	else    	{ Set_Motor(15,40); }	
}
void  Gray_Run25gai()
{
    if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(12,10); }
	if(Gray4 == 0)       { Set_Motor(14,10); }
	if(Gray5 == 0)       { Set_Motor(14,10); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(10,50); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(20,7); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(10,30); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(20,10); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(5,40); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(25,5); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(0,45); }
	else if(Gray1 == 0 && Gray2 == 0&&Gray3 == 0)  { Set_Motor(0,60); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(25,0); }
	else    	{ Set_Motor(21,26); }	

}
void  Gray_Run35()
{
     if(Gray4==0&&Gray5==0) Set_Motor(48,48);
	else if(Gray5==0&&Gray6==0) Set_Motor(45,20);
	else if(Gray3==0&&Gray4==0) Set_Motor(20,45);
	else if(Gray6==0&&Gray7==0) Set_Motor(45,0);
	else if(Gray2==0&&Gray3==0) Set_Motor(-10,55);
	else if(Gray7==0&&Gray8==0) Set_Motor(60,-30);
	else if(Gray1==0&&Gray2==0) Set_Motor(-45,60);	
	else if(Gray3==0) Set_Motor(10,45);
	else if(Gray2==0) Set_Motor(-10,45);
	else if(Gray1==0) Set_Motor(-45,60);
	else if(Gray4==0) Set_Motor(45,40);
	else if(Gray5==0) Set_Motor(40,45);
	else if(Gray6==0) Set_Motor(45,-10);
	else if(Gray7==0) Set_Motor(45,10);
	else if(Gray8==0) Set_Motor(60,-45);
	else	
		Set_Motor(48,48);
}
void  Gray_Run_gaotai()//�����¸�̨
{
     if(Gray4==0&&Gray5==0) Set_Motor(0,0);
	else if(Gray5==0&&Gray6==0) Set_Motor(35,10);
	else if(Gray3==0&&Gray4==0) Set_Motor(10,35);
	else if(Gray6==0&&Gray7==0) Set_Motor(35,-10);
	else if(Gray2==0&&Gray3==0) Set_Motor(-10,35);
	else if(Gray7==0&&Gray8==0) Set_Motor(35,-35);
	else if(Gray1==0&&Gray2==0) Set_Motor(-35,35);	
	else if(Gray3==0) Set_Motor(35,10);
	else if(Gray2==0) Set_Motor(35,-10);
	else if(Gray1==0) Set_Motor(35,-35);
	else if(Gray4==0) Set_Motor(0,0);
	else if(Gray5==0) Set_Motor(0,0);
	else Set_Motor(0,0);

}





/*
*********************************************************************************************************
*	�� �� ��: Gray_Run25
*	����˵��: �Ҷȿ���ֱ�߳���  ���ڴӸ�̨������
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run25()//������
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(23,25); }
	
	if(Gray4 == 0)       { Set_Motor(14,25); }
	if(Gray5 == 0)       { Set_Motor(23,15); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(6,25); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(23,7); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(9,25); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(23,10); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(4,25); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(23,5); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(0,25); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(23,0); }
	
	else    	{ Set_Motor(23,25); }	
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Run30
*	����˵��: �Ҷȿ���ֱ�߳���  ���ڴӸ�̨������
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run30()//����ɽ��,��ֹ��
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(28,30); }
	
	if(Gray4 == 0)       { Set_Motor(18,30); }
	if(Gray5 == 0)       { Set_Motor(30,20); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(15,30); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(30,15); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(8,30); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(30,10); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(5,30); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(30,5); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(0,30); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(30,0); }
	
	else    	{ Set_Motor(28,30); }	
}


/*
*********************************************************************************************************
*	�� �� ��: Gray_Run40
*	����˵��: �Ҷȿ���ֱ�߳���
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run40()//�ұ����ٶȽ��������貹��
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(40,43); }
	
	if(Gray4 == 0)       { Set_Motor(35,42); }
	if(Gray5 == 0)       { Set_Motor(40,35); }
	if(Gray3 == 0)       { Set_Motor(30,42); }
	if(Gray2 == 0)       { Set_Motor(40,30); }
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(25,43); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(40,27); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(30,43); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(40,32); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(20,40); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(40,20); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(10,41); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(40,10); }
	
	else if(Gray1 == 0)        { Set_Motor(-20,30); }
	else if(Gray8 == 0)        { Set_Motor(30,-20); }
	
	else    	{ Set_Motor(40,43); }	
}
void Gray_Run40gai()//�ұ����ٶȽ��������貹��
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(40,43); }
	
	if(Gray4 == 0)       { Set_Motor(30,43); }
	if(Gray5 == 0)       { Set_Motor(40,32); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(15,43); }
//	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(40,17); }
	else if(Gray6 == 0 || Gray7 == 0 || Gray8 == 0)  { Set_Motor(60,20); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(25,43); }
//	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(60,10); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(10,40); }
//	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(60,-25); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(-10,41); }
//	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(60,-40); }
	
//	else if(Gray1 == 0)        { Set_Motor(-20,30); }
//	else if(Gray8 == 0)        { Set_Motor(30,-20); }
	
	else    	{ Set_Motor(40,43); }	
}
void Gray_Run40TaiJie()//��ƽ̨
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(40,35); }
	
	if(Gray4 == 0)       { Set_Motor(30,43); }
	if(Gray5 == 0)       { Set_Motor(40,32); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(15,43); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(40,17); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(25,43); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(40,27); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(10,40); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(40,11); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(-10,41); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(40,-10); }
	
//	else if(Gray1 == 0)        { Set_Motor(-20,30); }
//	else if(Gray8 == 0)        { Set_Motor(30,-20); }
	
	else    	{ Set_Motor(40,35); }	
}
/*
*********************************************************************************************************
*	�� �� ��: Gray_Run50
*	����˵��: �Ҷȿ���ֱ�߳���
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
//�����ٶ�����������
void Gray_Run50()//1234 5678
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(50,53); }
	
	if(Gray4 == 0)       { Set_Motor(40,52); }
	if(Gray5 == 0)       { Set_Motor(50,40); }
	if(Gray3 == 0)       { Set_Motor(35,52); }
	if(Gray6 == 0)       { Set_Motor(50,35); }
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(35,52); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(50,35); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(32,52); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(50,32); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(20,52); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(50,20); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(-10,43); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(40,-10); }
	
	else if((Gray1 == 0 || Gray8 == 0) && (Gray4 == 0 || Gray5 == 0))   { Set_Motor(50,53); }
	
	else if(Gray1 == 0)        { Set_Motor(-30,33); }
	else if(Gray8 == 0)        { Set_Motor(30,-30); }
	
	else    	{ Set_Motor(50,50); }	
}


/*
*********************************************************************************************************
*	�� �� ��: Gray_Run60
*	����˵��: �Ҷȿ���ֱ�߳���
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run60()//1234 5678
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(60,63); }
	
	if(Gray4 == 0)       { Set_Motor(50,62); }
	if(Gray5 == 0)       { Set_Motor(60,50); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(45,63); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(60,45); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(40,62); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(60,40); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(30,62); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(60,30); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(10,40); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(40,10); }
	
	else if(Gray1 == 0)        { Set_Motor(-30,30); }
	else if(Gray8 == 0)        { Set_Motor(30,-30); }
	
	else    	{ Set_Motor(60,63); }	
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Run70
*	����˵��: �Ҷȿ���ֱ�߳���
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 void Gray_Run70()//1234 5678
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(70,74); }
	
	if(Gray4 == 0)       { Set_Motor(62,73); }
	if(Gray5 == 0)       { Set_Motor(70,62); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(52,67); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(65,52); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(52,65); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(65,52); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(40,60); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(60,40); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(20,50); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(50,20); }
	
	else if(Gray1 == 0)        { Set_Motor(-10,40); }
	else if(Gray8 == 0)        { Set_Motor(40,-10); }
	
	else    	{ Set_Motor(70,74); }	
}


/*
*********************************************************************************************************
*	�� �� ��: Gray_Run80
*	����˵��: �Ҷȿ���ֱ�߳���
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run80()//1234 5678
{

	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(80,80); }
	
	if(Gray4 == 0)       { Set_Motor(65,80); }
	if(Gray5 == 0)       { Set_Motor(80,65); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(45,75); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(75,45); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(55,75); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(75,55); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(30,70); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(70,30); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(0,60); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(60,0); }
	
	else if(Gray1 == 0)        { Set_Motor(-20,50); }
	else if(Gray8 == 0)        { Set_Motor(50,-20); }
	
	else    	{ Set_Motor(80,80); }	
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Run_Taijie
*	����˵��: �Ҷȿ���ֱ�߳���
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run_Taijie()//�����ٶ�ƫС�����貹��
{
	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(35,29); }
	
	if(Gray4 == 0)       { Set_Motor(25,29); }
	if(Gray5 == 0)       { Set_Motor(35,20); }
	
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(20,29); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(35,15); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(15,29); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(35,10); }
	
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(8,29); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(35,5); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(-10,29); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(35,-10); }
	
	else if(Gray1 == 0)        { Set_Motor(-20,29); }
	else if(Gray8 == 0)        { Set_Motor(35,-20); }
	
	else    	{ Set_Motor(35,29); }		
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Run_Taijie1
*	����˵��: �Ҷȿ���ֱ�߳���
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run_Taijie1()//�����ٶ�ƫС�����貹��
{
	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(35,29); }
	
	if(Gray4 == 0)       { Set_Motor(25,29); }
	if(Gray5 == 0)       { Set_Motor(35,20); }
	
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(20,29); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(35,15); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(15,29); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(35,10); }
	
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(8,29); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(35,5); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(-10,29); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(35,-10); }
	
	else if(Gray1 == 0)        { Set_Motor(-20,29); }
	else if(Gray8 == 0)        { Set_Motor(35,-20); }
	
	else    	{ Set_Motor(35,29); }		
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Run_Taijie_Speed
*	����˵��: �Ҷȿ���ֱ�߳���
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run_Taijie_Speed(int speed)//�����ٶ�ƫС�����貹��
{
	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(speed + 5,speed); }
	
	if(Gray4 == 0)       { Set_Motor(speed - 5,speed); }
	if(Gray5 == 0)       { Set_Motor(speed + 5,speed - 10); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(speed - 20,speed); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(speed + 5,speed - 15); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(speed - 15,speed); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(speed + 5,speed - 20); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(speed - 22,speed); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(speed + 5,speed - 25); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(speed - 40,speed); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(speed + 5,speed - 40); }
	
	else if(Gray1 == 0)        { Set_Motor(speed - 50,speed); }
	else if(Gray8 == 0)        { Set_Motor(speed + 4,speed - 50); }
	
	else    	{ Set_Motor(speed + 5,speed); }		
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Run_Jiansuban
*	����˵��: �Ҷȿ���ֱ�߳���
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run_Jiansuban()//�����ٶ�ƫС�����貹��
{
	if(Gray4 == 0 || Gray5 == 0)       { Set_Motor(32,30); }
	
	if(Gray4 == 0)       { Set_Motor(27,30); }
	if(Gray5 == 0)       { Set_Motor(30,25); }
	
	else if(Gray2 == 0 && Gray3 == 0 && Gray4 == 0)  { Set_Motor(24,30); }
	else if(Gray5 == 0 && Gray6 == 0 && Gray7 == 0)  { Set_Motor(30,21); }
	else if(Gray3 == 0 && Gray4 == 0)  { Set_Motor(16,30); }
	else if(Gray5 == 0 && Gray6 == 0)  { Set_Motor(29,14); }
	else if(Gray2 == 0 && Gray3 == 0)  { Set_Motor(10,30); }
	else if(Gray6 == 0 && Gray7 == 0)  { Set_Motor(29,7); }
	else if(Gray1 == 0 && Gray2 == 0)  { Set_Motor(-10,30); }
	else if(Gray7 == 0 && Gray8 == 0)  { Set_Motor(29,-10); }
	
	else if(Gray1 == 0)        { Set_Motor(-20,30); }
	else if(Gray8 == 0)        { Set_Motor(29,-20); }
	
	else    	{ Set_Motor(32,30); }		
}

/*
*********************************************************************************************************
*	�� �� ��: run_gray
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ��
*	��    ��: i ����		speed �ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void run_gray(u16 i,u8 speed)
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run50();//ֱ��
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Down
*	����˵��: �Ҷȿ���ֱ�߳���  ���ڴӸ�̨������
*	��    ��: direction	����0��1���� 	speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Down(u16 i)
{
	while(i--)
	{
		Gray_Run30();
		delay_ms(8);
		CarRetreat(5);
		delay_ms(4);
	}
}
void Gray_Down2(u16 i)
{
	while(i--)
	{
		Gray_Run35();
		delay_ms(8);
		CarRetreat(0);
		delay_ms(4);
	}
}
/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run15
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Delay_Run15(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run15();//�Ҷ���ֱ��,���ִ����ٶ�
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run15_0
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬15�ٶ�����ٽ���ʹ��
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Delay_Run15_0(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬15�ٶ�����ٽ���ʹ��
{
	while(i -- )
	{
		Gray_Run15();//�Ҷ���ֱ��,���ִ����ٶ�
		delay_ms(7);
		CarRetreat(5);//����
		delay_ms(3);
	
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run20
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Delay_Run20(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run20();//�Ҷ���ֱ��,���ִ����ٶ�
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run20
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Delay_Run20_20(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run20_20();//�Ҷ���ֱ��,���ִ����ٶ�
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run25
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int Gray_Delay_Run25(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run25();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}
int Gray_Delay_Run25gai(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run25gai();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}
int Gray_Delay_Run35(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run35();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run30
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int Gray_Delay_Run30(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run30();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run40
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int Gray_Delay_Run40(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run40();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run50
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int Gray_Delay_Run50(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run50();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run60
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int Gray_Delay_Run60(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run60();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run70
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int Gray_Delay_Run70(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ִ����ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run70();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run_Taijie
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬��̨��(taijie)�ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int Gray_Delay_Run_Taijie(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬��̨��(taijie)�ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run_Taijie();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run_Taijie1
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬��̨��(taijie)�ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int Gray_Delay_Run_Taijie1(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬��̨��(taijie)�ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run_Taijie1();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run_Taijie2
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬��̨��(taijie)�ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Delay_Run_Taijie2(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬��̨��(taijie)�ٶ�
{
	while(i -- )
	{
		Gray_Run_Taijie1();//�Ҷ���ֱ��,���ִ����ٶ�
		delay_ms(9);
		Set_Motor(0,0);//������ת
		delay_ms(1);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run_Jiansuban
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬�����ٰ�(Jiansuban)�ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int Gray_Delay_Run_Jiansuban(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬�����ٰ�(Jiansuban)�ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run_Jiansuban();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Delay_Run_C
*	����˵��: ֻ�߻Ҷ�Ѳ�������������Ӱ�죬תȦ�ٶ�
*	��    ��: i ����	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int Gray_Delay_Run_C(u16 i)//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬תȦ�ٶ�
{
	while(i -- )
	{
		delay_ms(1);
		run_c();//�Ҷ���ֱ��,���ִ����ٶ�
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_curve
*	����˵��: �Ҷ������߳���
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_curve(u8 speed)
{
	if(DIR == 0 )
	{
		if(Gray4 == 0)        { Set_Motor(speed + 10,speed); }	
		else if(Gray5 == 0)        { Set_Motor(speed + 10,speed); }
		else if(Gray3 == 0)        { Set_Motor(speed - 10,speed); } 
		else if(Gray6 == 0)        { Set_Motor(speed + 20,speed); }
		else if(Gray2 == 0)        { Set_Motor(speed - 30,speed); }
		else if(Gray7 == 0)        { Set_Motor(speed + 20,speed - 20); }
		else if(Gray1 == 0)        { Set_Motor(speed - 20,speed + 20); }
		else if(Gray8 == 0)        { Set_Motor(speed + 30,speed - 30); }
	}
	else
	{
		if(Gray44 == 0)        { Set_Motor(speed,speed); }	
		else if(Gray55 == 0)        { Set_Motor(speed + 10,speed); }
		else if(Gray33 == 0)        { Set_Motor(speed - 10,speed); } 
		else if(Gray66 == 0)        { Set_Motor(speed + 20,speed); }
		else if(Gray22 == 0)        { Set_Motor(speed - 30,speed); }
		else if(Gray77 == 0)        { Set_Motor(speed + 20,speed - 20); }
		else if(Gray11 == 0)        { Set_Motor(speed - 20,speed + 20); }
		else if(Gray88 == 0)        { Set_Motor(speed + 30,speed - 30); }
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Curve0
*	����˵��: ǰ�Ҷ������߳���
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Curve0(u8 speed)//ǰ�Ҷ�������
{

	if(Gray4 == 0 && Gray5 == 0) Set_Motor(20,50);
	else if(Gray5 == 0 && Gray6 == 0) Set_Motor(50,35);
	else if(Gray3 == 0 && Gray4 == 0) Set_Motor(10,50);
	else if(Gray6 == 0 && Gray7 == 0) Set_Motor(50,-10);
	else if(Gray2 == 0 && Gray3 == 0) Set_Motor(-35,50);
	else if(Gray7 == 0 && Gray8 == 0) Set_Motor(50,-50);
	else if(Gray1 == 0 && Gray2 == 0) Set_Motor(-50,50);
	else if(Gray4 == 0) Set_Motor(18,50);
	else if(Gray5 == 0) Set_Motor(27,50);	
	else if(Gray3 == 0) Set_Motor(0,50);
	else if(Gray6 == 0) Set_Motor(50,15);
	else if(Gray2 == 0) Set_Motor(-25,50);
	else if(Gray7 == 0) Set_Motor(50,-25);
	else if(Gray1 == 0) Set_Motor(-50,50);
	else if(Gray8 == 0) Set_Motor(50,-50);
	else Set_Motor(30,40);
}


/*
*********************************************************************************************************
*	�� �� ��: Front_Gray_Curve_L50_Turn
*	����˵��: ǰ�Ҷ�������ת������֤��
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void Front_Gray_Curve_L50_Turn(u8 speed)
{
	while(1)
	{
		SetLeftWhell(1,speed); SetRightWhell(0,speed);//ԭ40
		if(Gray8 == 0 || Gray1 == 0)
		{
			break;
		}
	}
	while(1)
	{
		SetLeftWhell(1,speed - 10); SetRightWhell(0,speed - 10);
		if(Gray5 == 0 || Gray4 == 0)
		{
			break;
		}
	}
}

/*
*********************************************************************************************************
*	�� �� ��: run_c
*	����˵��: תȦ
*	��    ��: speed �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void run_c()//תȦ
{
	if(	Gray4 == 0 && Gray5 == 0) Set_Motor(20,45);
	else if(Gray5 == 0 && Gray6 == 0) Set_Motor(40,25);
	else if(Gray3 == 0 && Gray4 == 0) Set_Motor(20,45);
	else if(Gray6 == 0 && Gray7 == 0) Set_Motor(40,-25);
	else if(Gray6 == 0 && Gray7 == 0) Set_Motor(-25,40);
	else if(Gray7 == 0 && Gray8 == 0) Set_Motor(40,-40);
	else if(Gray1 == 0 && Gray2 == 0) Set_Motor(-40,40);
	else if(Gray4 == 0) Set_Motor(18,45);
	else if(Gray5 == 0) Set_Motor(25,45);	
	else if(Gray3 == 0) Set_Motor(22,45);
	else if(Gray6 == 0) Set_Motor(42,25);
	else if(Gray2 == 0) Set_Motor(-25,40);
	else if(Gray7 == 0) Set_Motor(40,-25);
	else if(Gray1 == 0) Set_Motor(-40,40);
	else if(Gray8 == 0) Set_Motor(40,-40);

	else Set_Motor(18,20);
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Run2
*	����˵��: �Ҷ������߳���
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run2(u8 speed)
{
	if((Gray3 == 0) || (Gray5 == 0))
		{
			SetLeftWhell(1,speed + 5);SetRightWhell(0,speed);
		}	
	else if(Gray2 == 0)
		{
			SetLeftWhell(1,0);SetRightWhell(0,speed);
		}
	else if(Gray7 == 0 || Gray6 == 0)
		{
			SetLeftWhell(1,speed+6);SetRightWhell(0,0);
		}		
	else if((Gray5 == 0) && (Gray6 == 0))
		{	
			SetLeftWhell(1,speed);SetRightWhell(0,0);
		}
	else if((Gray3 == 0) && (Gray4 == 0))
		{	
			SetLeftWhell(1,0);SetRightWhell(0,speed);
		}
	else{
			CarAdvance(speed);
		}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_Run3
*	����˵��: ����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void Gray_Climb(u8 speed)
{
	if((Gray4 == 0) && (Gray5 == 0))
				{
					SetLeftWhell(1,speed);SetRightWhell(0,speed);
				}	
		else if(Gray2 == 0 || Gray3 == 0)
					{
						SetLeftWhell(1,speed - 15);SetRightWhell(0,speed + 25);
					}
		else if((Gray3 == 0) && (Gray4 == 0))
					{	
						SetLeftWhell(1,speed - 10);SetRightWhell(0,speed + 20);
					}
		else if((Gray5 == 0) && (Gray6 == 0))
					{	
						SetLeftWhell(1,speed + 20);SetRightWhell(0,speed - 10);
					}
		else if(Gray7 == 0 || Gray6 == 0)
					{
						SetLeftWhell(1,speed + 25);SetRightWhell(0,speed - 15);
					}
		else if(Gray1 == 0 )
					{
						SetLeftWhell(1,0);SetRightWhell(0,speed + 20);
					}
		else if(Gray8 == 0)
					{
						SetLeftWhell(1,speed + 20);SetRightWhell(0,0);
					}
					
		else {
						SetLeftWhell(1,speed);SetRightWhell(0,speed);
					}
}


/*
*********************************************************************************************************
*	�� �� ��: Gray_Run4
*	����˵��: �����ٴ�
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Run4(u8 speed)//1234 5678
{
		if((Gray4 == 0) || (Gray5 == 0))
				{
					CarAdvance(speed);
				}
				
		else if(Gray2 == 0 || Gray3 == 0)
					{
						SetLeftWhell(1,0);SetRightWhell(0,speed + 20);
					}
		else if(Gray7 == 0 || Gray6 == 0)
					{
						SetLeftWhell(1,speed + 20);SetRightWhell(0,0);
					}		
		else if((Gray5 == 0) && (Gray6 == 0))
					{	
						SetLeftWhell(1,speed);SetRightWhell(0,speed-10);
					}
		else if((Gray3 == 0) && (Gray4 == 0))
					{	
						SetLeftWhell(1,speed-10);SetRightWhell(0,speed);
					}
		else if(Gray1 == 0 || Gray2 == 0)
					{
						SetLeftWhell(0,35);SetRightWhell(0,speed + 15);
					}
		else if(Gray7 == 0 || Gray8 == 0)
					{
						SetLeftWhell(1,speed + 15);SetRightWhell(1,35);
					}
		else {
						CarAdvance(speed);
					}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_L37_Turn
*	����˵��: �Ҷ���ת��������ִ���ת�ĽǶ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void Gray_L37_Turn()
{
	while(1)
	{
		if(Gray1 == 0)
		{	
			Set_Motor(-50,70);
			delay_ms(50);
			break;
		}
	}
	while(1)
	{
		Set_Motor(-50,50);
		if(Gray4 == 0 || Gray5 == 0)
		{		
			delay_ms(10);
			if(Gray4 == 0 || Gray5 == 0)
			break;
		}
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_L_Turn
*	����˵��: �Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_L_Turn(u8 speed,int angle)
{
	while(1)
	{
		float a;
		a = Get_Angle(3);  
		SetLeftWhell(1,speed + 10); SetRightWhell(0,speed);
		
		if((angle - (float)2 < a ) && ( a < angle + (float)2))
		{
			break;
		}
	}
}
	
/*
*********************************************************************************************************
*	�� �� ��: Gray_L1_Turn
*	����˵��: �Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_L1_Turn(u8 speed)
{
	if(DIR == 0)
	{
		while(1)
		{
			SetLeftWhell(1,speed + 5); SetRightWhell(0,speed);//ԭ40
			if(Gray8 == 0 || Gray1 == 0)
			{
				break;
			}
		}
		while(1)
		{
			SetLeftWhell(1,speed - 10); SetRightWhell(0,speed - 10);
			if(Gray5 == 0 || Gray4 == 0)
			{
				break;
			}
		}
	}else
	{
		while(1)
		{
			SetLeftWhell(1,speed + 5); SetRightWhell(0,speed);//ԭ40
			if(Gray88 == 0 || Gray11 == 0)
			{
				break;
			}
		}
		while(1)
		{
			SetLeftWhell(1,speed - 10); SetRightWhell(0,speed - 10);
			if(Gray55 == 0 || Gray44 == 0)
			{
				break;
			}
		}
	}	
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_L3_Turn
*	����˵��: �Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void Gray_L3_Turn(u8 speed)
{
	u8 a = 0;
	while(1)
	{
		flag_line = 1;
		if(a == 0)
		{
			SetLeftWhell(0,speed/2); SetRightWhell(0,speed);
			delay_ms(150);
			a ++;
		}
		else
		{
			SetLeftWhell(0,speed); SetRightWhell(0,speed);
			if(Gray5 == 0 || Gray6 == 0)
			{
				break;
			}
		}

	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_L2_Turn
*	����˵��: �Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void Gray_L2_Turn(u8 speed)
{
	while(1)
	{
		SetLeftWhell(1,speed); SetRightWhell(0,speed);//ԭ40
		if(Gray8 == 0)
		{
			break;
		}
	}
	while(1)
	{
		SetLeftWhell(1,speed - 10); SetRightWhell(0,speed - 10);
		if(Gray5 == 0 || Gray4 == 0)
		{
			break;
		}
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_L4_Turn
*	����˵��: �Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void Gray_L4_Turn(u8 speed)
{
	u8 a = 0;
	while(1)
	{
		flag_line = 1;
		if(a == 0)
		{
			SetLeftWhell(0,speed/2); SetRightWhell(0,speed);
			delay_ms(150);
			a ++;
		}
		else
		{
			SetLeftWhell(0,speed); SetRightWhell(0,speed);
			if(Gray5 == 0 || Gray6 == 0)
			{
				break;
			}
		}

	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_L70_Turn
*	����˵��: �Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void Gray_L70_Turn(u8 speed)
{
	while(1)
	{
		Set_Motor(-speed,speed);
		if(Gray8 == 0 || Gray1 == 0)
		{
			break;
		}
	}
	while(1)
	{
		Set_Motor(-speed + 20,speed - 20);
		if(Gray6 == 0 || Gray3 == 0)
		{
			break;
		}
	}
	while(1)
	{
		Set_Motor(-speed + 40,speed - 40);
		if(Gray5 == 0 || Gray4 == 0)
		{
			break;
		}
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_R37_Turn
*	����˵��: �Ҷ���ת�䣬���ִ���ת�ĽǶ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_R37_Turn()
{
	while(1)
	{
		if(Gray_Count() == 0)
		{
			delay_ms(10);
			if(Gray_Count() == 0)
			break;
		}
	}
	Set_Motor(-10,-10);
	delay_ms(50);
	Set_Motor(50,-50);
	delay_ms(50);
	while(1)
	{
		Set_Motor(50,-50);
		if(Gray5 == 0 && Gray6 == 0)
		{		
			delay_ms(10);
			if(Gray5 == 0 && Gray6 == 0)
			break;
		}
	}
}
/*
*********************************************************************************************************
*	�� �� ��: Gray_R_Turn
*	����˵��: �Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void Gray_R_Turn(u8 speed,int angle)
{
	while(1)
	{
		float a;
		a = Get_Angle(3);
		SetLeftWhell(1,speed); SetRightWhell(1,speed);
		flag_line = 1;
		
//		if(a < angle + (float)2)//350     
//		{
//			if(a < angle - (float)4)
//			{
//				SetLeftWhell(1,speed); SetRightWhell(1,speed);
//			}
//			if(a > angle + (float)4)
//			{
//				SetLeftWhell(0,speed); SetRightWhell(0,speed);
//			}
		if((angle - (float)2 < a) && (a < angle + (float)2))
		{
			break;
		}	
	}
}


/*
*********************************************************************************************************
*	�� �� ��: Gray_R1_Turn
*	����˵��: �Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_R1_Turn(u8 speed,int angle)
{
	int ang = Get_Angle(3);
	while(1)
	{
		SetLeftWhell(0,speed); SetRightWhell(1,speed);
		flag_line = 1;
		if((angle-2 < ang - Get_Angle(3)) && (Get_Angle(3) < angle+2))
		{
			break;
		}
	}
}


/*
*********************************************************************************************************
*	�� �� ��: Gray_R2_Turn
*	����˵��: �Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_R2_Turn(u8 speed,int angle)
{
	while(1)
	{
		SetLeftWhell(0,speed); SetRightWhell(1,speed);
		if((angle-3 < Get_Angle(3)) && (Get_Angle(3) < angle+3))
		{
			break;
		}
	}
}


/*
*********************************************************************************************************
*	�� �� ��: Gray_R3_Turn
*	����˵��: �Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_R3_Turn(u8 speed)
{
	if(DIR == 0)
	{
		while(1)
		{
			SetLeftWhell(0,speed ); SetRightWhell(1,speed);//ԭ40
			if(Gray8 == 0 || Gray1 == 0)
			{
				break;
			}
		}
		while(1)
		{
			SetLeftWhell(0,speed - 10); SetRightWhell(1,speed - 10);
			if(Gray5 == 0 || Gray4 == 0)
			{
				break;
			}
		}
	}else
	{
		while(1)
		{
			SetLeftWhell(0,speed ); SetRightWhell(1,speed);//ԭ40
			if(Gray88 == 0 || Gray11 == 0)
			{
				break;
			}
		}
		while(1)
		{
			SetLeftWhell(0,speed - 10); SetRightWhell(1,speed - 10);
			if(Gray55 == 0 || Gray44 == 0)
			{
				break;
			}
		}
	}
	
}


/*
*********************************************************************************************************
*	�� �� ��: Gray_R4_Turn
*	����˵��: �Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_R4_Turn(u8 speed)
{	
	if(DIR == 0)
	{
		while(1)
		{
			SetLeftWhell(0,speed / 2); SetRightWhell(1,speed);//ԭ40
			if(Gray8 == 0 || Gray1 == 0)
			{
				break;
			}
		}
		while(1)
		{
			SetLeftWhell(0,speed - 10); SetRightWhell(1,speed - 10);
			if(Gray5 == 0 || Gray4 == 0)
			{
				break;
			}
		}
	}
	else
	{
		while(1)
		{
			SetLeftWhell(0,speed ); SetRightWhell(1,speed / 2);//ԭ40
			if(Gray88 == 0 || Gray11 == 0)
			{
				break;
			}
		}
		while(1)
		{
			SetLeftWhell(0,speed - 10); SetRightWhell(1,speed - 10);
			if(Gray55 == 0 || Gray44 == 0)
			{
				break;
			}
		}
	}
}


/*
*********************************************************************************************************
*	�� �� ��: Gray_R50_Turn
*	����˵��: ǰ�Ҷ���ת�����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_R50_Turn(u8 speed)
{
	while(1)
	{
		Set_Motor(speed,-speed);
		if(Gray8 == 0 || Gray1 == 0)
		{	
			break;
		}
	}	
	while(1)
	{
		Set_Motor(speed - 20,-speed + 20);
		if(Gray6 == 0 || Gray3 == 0)
		{	
			break;
		}
	}
	while(1)
	{
		Set_Motor(speed - 40,-speed + 40);
		if(Gray4 == 0 || Gray5 == 0)
		{	
			break;
		}
	}
}


/*
*********************************************************************************************************
*	�� �� ��: Gray_More90_R_Turn
*	����˵��: ǰ�Ҷȳ���90�ȻҶ�ֱ����ת
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_More90_R_Turn(u8 speed)
{
	while(1)
	{
		SetLeftWhell(0,speed); SetRightWhell(1,speed);//ԭ40
		if(Gray7 == 0 || Gray2 == 0)
		{	
			break;
		}
	}	
	while(1)
	{
		SetLeftWhell(0,speed - 10); SetRightWhell(1,speed - 10);
		if(Gray5 == 0 || Gray4 == 0)
		{	
			break;
		}
	}
}


///*
//*********************************************************************************************************
//*	�� �� ��: Gray_B_Turn
//*	����˵��: ƽ̨�ϵ�ͷ
//*	��    ��: speed�����ٶ�
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/

//void Gray_B_Turn(u8 speed,int angle)
//{
//	int a = Get_Angle(3);
//	int b = (a + angle + 360) % 360;
////	int c = (a - 50 + angle + 360) % 360;
//	int c = b  / 2;
//	while(1)
//	{
//		SetLeftWhell(0,55); SetRightWhell(0,55);
//		if((c < Get_Angle(3)) && (Get_Angle(3) < c + 5))
//		{ 
//			break;
//		}
//	}
//	while(1)
//	{
//		SetLeftWhell(0,25); SetRightWhell(0,25);
//		if((b - 3 < Get_Angle(3)) && (Get_Angle(3) < b + 3))
//		{
//			CarAdvance(0);
//			delay_ms(250);
//			break;
//		}
//	}
//	if(Get_Angle(3) >= b + 3)
//	{
//		while(1)
//		{
//			SetLeftWhell(1,28); SetRightWhell(1,30);
//			if((b - 2 < Get_Angle(3)) && (Get_Angle(3) < b + 2))
//			{
//				break;
//			}
//		}
//	}
//	CarAdvance(0);
//}

/*
*********************************************************************************************************
*	�� �� ��: Gray__Turn
*	����˵��: �Ҷȵ�ͷ����
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_B1_Turn(u8 speed,int angle)
{
	/*
	u8 a = 0;
	flag_line = 1;
	while(1)
	{
		if(a == 0)
		{
			SetLeftWhell(0,speed + 15); SetRightWhell(0,speed);
			delay_ms(300);
			a ++;
		}else
		{
			SetLeftWhell(0,speed+15); SetRightWhell(0,speed);
			if(Gray5 == 0 || Gray4 == 0)
			{
				flag_gray = 0;
				break;
			}
		}	
	}
	*/
	
	int a = Get_Angle(3);
	int b = (a + angle + 360) % 360;
	int c = (a - 50 + angle + 360) % 360;
	while(1)
	{
		SetLeftWhell(0,58); SetRightWhell(0,55);
		if((c < Get_Angle(3)) && (Get_Angle(3) < c + 7))
		{ 
			break;
		}
	}
	while(1)
	{
		SetLeftWhell(0,35); SetRightWhell(0,30);
		if((b - 3 < Get_Angle(3)) && (Get_Angle(3) < b + 3))
		{
			CarAdvance(0);
			delay_ms(250);
			break;
		}
	}
	if(Get_Angle(3) >= b + 3)
	{
		while(1)
		{
			SetLeftWhell(1,30); SetRightWhell(1,35);
			if((b - 2 < Get_Angle(3)) && (Get_Angle(3) < b + 2))
			{
				break;
			}
		}
	}
	CarAdvance(0);
}



/*
*********************************************************************************************************
*	�� �� ��: Detect_obstacles_front
*	����˵��: ���ǰ���Ƿ��ϰ���
*	��    ��: speed�����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 void Detect_obstacles_front()
{
	if(flag_obstacles == 0)
	{
	 if(Infrared_DIO2 == 0)
	 {
			flag_obstacles_front++;
			flag_obstacles = 1;
	 }
 }
}

/*
*********************************************************************************************************
*	�� �� ��: Gray_scanf
*	����˵��: С�Ҷ�ɨ���ϰ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void Gray_scanf()
{
	if(flag_gray == 0)
	{
		if(L_DIO3 == 0 || R_DIO4 == 1)
		{
			flag_turn++;
			flag_gray = 1;
		}
	}
}

/*
*********************************************************************************************************
*	�� �� ��: scanf__obstacles
*	����˵��: ɨ���ϰ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void scanf_obstacles(void)
{
	G_Scan(site);
}

/*
*********************************************************************************************************
*	�� �� ��: star_gray
*	����˵��: ����ɨ���ϰ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void star_gray()
{
	if(Gray1 == 0 || Gray8 == 0)
	{
		flag_gray = 0;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: back_scenic
*	����˵��: �������㷵��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void back_scenic()
{
	DIR = !DIR;
}
void stop1()
{
	
	while(1)
	{
	Set_Motor(0,0);
	}
}

int gray_light_amount()
{
	return (Gray1+Gray2+Gray3+Gray4+Gray5+Gray6+Gray7+Gray8);
}


/*
*********************************************************************************************************
*	�� �� ��: infrared
*	����˵��: ���⴫�������ֲ��̨
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void infrared_35(void)
{
	if(ETR1 == 1 && ETR2 == 1)
	{
		Set_Motor(25,33);
	}
	else if(ETR1 == 1 && ETR2 == 0)
	{
		Set_Motor(20,30);
	}
	else if(ETR1 == 0 && ETR2 == 1)
	{
		Set_Motor(30,20);
	}
}

void zhuanwan_big_left(int time)
{
	Set_Motor(-40,40);
	delay_ms(time);
	while(1)
	{
		Set_Motor(-35,35);
		if(Gray1 == 0)
		{
			Set_Motor(-32,32);
		}
		if(Gray2 == 0)
		{
			Set_Motor(-28,28);
		}
		if(Gray3 == 0)
		{
			Set_Motor(0,0);
			delay_ms(100);
			break;
		}
	}
}

void zhuanwan_big_right(int time)
{
	Set_Motor(40,-40);
	delay_ms(time);
	while(1)
	{
		Set_Motor(35,-35);
		if(Gray8 == 0)
		{
			Set_Motor(32,-32);
		}
		if(Gray7 == 0)
		{
			Set_Motor(28,-28);
		}
		if(Gray6 == 0)
		{
			Set_Motor(0,0);
			delay_ms(100);
			break;
		}
	}
}

//void zhuanwan_big_right(int time)
//{
//	Set_Motor(0,0);
//	delay_ms(100);
//	Set_Motor(35,-35);
//	delay_ms(time);
//	while(1)
//	{
//		Set_Motor(30,-25);
//		if(Gray8 == 0)
//		{
//			Set_Motor(25,-10);
//		}
//		if(Gray7 == 0)
//		{
//			Set_Motor(25,5);
//		}
//		if(Gray6 == 0)
//		{
//			Set_Motor(20,10);
//		}
//		if(Gray5 == 0)
//		{
//			Set_Motor(25,15);
//			delay_ms(100);
//			break;
//		}
//	}
//}

