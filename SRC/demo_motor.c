/*
*********************************************************************************************************
*���ļ�������д����С���ĸ����ӵĴ��롣
*********************************************************************************************************
*/

#include "demo_motor.h"
#include "carBaseMoves.h"
#include "demo_dio.h"
#include "math.h"

//M1Ϊ����ʹ�ܶˣ��͵�ƽ��Ч
//M2Ϊ����ת�����򣬸ߵ�ƽ�͵͵�ƽ����
//M3Ϊ�ҳ���ʹ�ܶˣ��͵�ƽ��Ч
//M4Ϊ�ҳ���ת�����򣬸ߵ�ƽ�͵͵�ƽ����
/*
*********************************************************************************************************
*	�� �� ��: motor_configuration
*	����˵��: ���������ʼ��
*	��    ��: PWM_fre:PWMƵ�ʲ�������λKHZ��,���뷶Χ1-840
*	�� �� ֵ: ��
*********************************************************************************************************
*/
//4.14��


void motor_configuration(u8 PWM_fre)
{
//	u32 psc;
//	psc = 840/PWM_fre;
	TIM5_PWM_Init(200-1,16800-1);     	   					 
	TIM5->CCR1=0;  
	TIM5->CCR2=0;
	TIM5->CCR3=0;
	TIM5->CCR4=0;
	RCC->AHB1ENR|=1<<6;    		//ʹ��PORTGʱ��
	RCC->AHB1ENR|=1<<5;				//ʹ��F
	GPIO_Set(GPIOF,PIN14|PIN15,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); //PF14,15����,����
	GPIO_Set(GPIOG,PIN0|PIN1,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PG0,1��������
	M1 = 1;
	M2 = 1;
	M3 = 1;
	M4 = 1;
	
}

/*
*********************************************************************************************************
*	�� �� ��: CarAdvance
*	����˵��: ����С��ǰ��
*	��    ��: speed��С���ٶȣ����뷶ΧΪ0-100������С���ܲ�������
*	�� �� ֵ: ��
*********************************************************************************************************
*/

 void CarAdvance(u8 speed)
{
	M1 = 0; //01��  00��  ���
	M2 = 1;
	
	M3 = 0;  
	M4 = 1;	//01��  00��  �ұ�
	TIM5->CCR1=speed;  
	TIM5->CCR2=speed;
	TIM5->CCR3=speed;
	TIM5->CCR4=speed;
}


/*
*********************************************************************************************************
*	�� �� ��: CarRetreat
*	����˵��: ����С������
*	��    ��: speed��С���ٶȣ����뷶ΧΪ0-100������С���ܲ�������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void CarRetreat(u8 speed)
{
	M1 = 0;
	M2 = 0;  //01��  00��  ���
	
	M3 = 0;
	M4 = 0;  //01��  00��  �ұ�
	TIM5->CCR1=speed;  
	TIM5->CCR2=speed;
	TIM5->CCR3=speed;
	TIM5->CCR4=speed;
}

/*
*********************************************************************************************************
*	�� �� ��: SetLeftWhell
*	����˵��: ����С�������
*	��    ��:left_direction���Ƶ������ת��0����1����/ speed��С��������ٶȣ����뷶ΧΪ0-100������С���ܲ�������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void SetLeftWhell(u8 right_direction,u8 speed)
{
	M1 = 0;
	M2 = !right_direction;
	TIM5->CCR1=speed;
	TIM5->CCR2=speed;

}

/*
*********************************************************************************************************
*	�� �� ��: SetRightWhell
*	����˵��: ����С���ұ���
*	��    ��:right_direction���Ƶ������ת��0��1����/ speed��С���ұ����ٶȣ����뷶ΧΪ0-100������С���ܲ������� 
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void SetRightWhell(u8 left_direction,u8 speed)
{
	M3 = 0;
	M4 = !left_direction;
	TIM5->CCR3=speed;
	TIM5->CCR4=speed;                                                             
}

//extern u8 DIR;
void Set_Motor(int left_speed,int right_speed)
{
		if(left_speed >= 0)
		{
			SetLeftWhell(0,left_speed);
		}else
		{
			left_speed = fabs(left_speed);
			SetLeftWhell(1,left_speed);
		}
		
		if(right_speed >= 0)
		{
			SetRightWhell(0,right_speed);
		}else
		{
			right_speed = fabs(right_speed);
			SetRightWhell(1,right_speed);
		}
	
}

void Set_Motor_1(int right_speed,int left_speed)
{
		if(left_speed >= 0)
		{
			SetLeftWhell(1,left_speed);
		}else
		{
			left_speed = fabs(left_speed);
			SetLeftWhell(0,left_speed);
		}
		
		if(right_speed >= 0)
		{
			SetRightWhell(1,right_speed);
		}else
		{
			right_speed = fabs(right_speed);
			SetRightWhell(0,right_speed);
		}
	
}
