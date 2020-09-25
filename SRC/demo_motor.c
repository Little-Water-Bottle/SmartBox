/*
*********************************************************************************************************
*本文件是用来写驱动小车四个轮子的代码。
*********************************************************************************************************
*/

#include "demo_motor.h"
#include "carBaseMoves.h"
#include "demo_dio.h"
#include "math.h"

//M1为左车轮使能端，低电平有效
//M2为左车轮转动方向，高电平和低电平反向
//M3为右车轮使能端，低电平有效
//M4为右车轮转动方向，高电平和低电平反向
/*
*********************************************************************************************************
*	函 数 名: motor_configuration
*	功能说明: 电机驱动初始化
*	形    参: PWM_fre:PWM频率参数（单位KHZ）,输入范围1-840
*	返 回 值: 无
*********************************************************************************************************
*/
//4.14改


void motor_configuration(u8 PWM_fre)
{
//	u32 psc;
//	psc = 840/PWM_fre;
	TIM5_PWM_Init(200-1,16800-1);     	   					 
	TIM5->CCR1=0;  
	TIM5->CCR2=0;
	TIM5->CCR3=0;
	TIM5->CCR4=0;
	RCC->AHB1ENR|=1<<6;    		//使能PORTG时钟
	RCC->AHB1ENR|=1<<5;				//使能F
	GPIO_Set(GPIOF,PIN14|PIN15,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); //PF14,15设置,下拉
	GPIO_Set(GPIOG,PIN0|PIN1,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PG0,1设置下拉
	M1 = 1;
	M2 = 1;
	M3 = 1;
	M4 = 1;
	
}

/*
*********************************************************************************************************
*	函 数 名: CarAdvance
*	功能说明: 驱动小车前进
*	形    参: speed：小车速度，输入范围为0-100。（过小可能不工作）
*	返 回 值: 无
*********************************************************************************************************
*/

 void CarAdvance(u8 speed)
{
	M1 = 0; //01正  00反  左边
	M2 = 1;
	
	M3 = 0;  
	M4 = 1;	//01正  00反  右边
	TIM5->CCR1=speed;  
	TIM5->CCR2=speed;
	TIM5->CCR3=speed;
	TIM5->CCR4=speed;
}


/*
*********************************************************************************************************
*	函 数 名: CarRetreat
*	功能说明: 驱动小车后退
*	形    参: speed：小车速度，输入范围为0-100。（过小可能不工作）
*	返 回 值: 无
*********************************************************************************************************
*/
void CarRetreat(u8 speed)
{
	M1 = 0;
	M2 = 0;  //01正  00反  左边
	
	M3 = 0;
	M4 = 0;  //01正  00反  右边
	TIM5->CCR1=speed;  
	TIM5->CCR2=speed;
	TIM5->CCR3=speed;
	TIM5->CCR4=speed;
}

/*
*********************************************************************************************************
*	函 数 名: SetLeftWhell
*	功能说明: 驱动小车左边轮
*	形    参:left_direction控制电机正反转（0正或1负）/ speed：小车左边轮速度，输入范围为0-100。（过小可能不工作）
*	返 回 值: 无
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
*	函 数 名: SetRightWhell
*	功能说明: 驱动小车右边轮
*	形    参:right_direction控制电机正反转（0或1正）/ speed：小车右边轮速度，输入范围为0-100。（过小可能不工作） 
*	返 回 值: 无
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
