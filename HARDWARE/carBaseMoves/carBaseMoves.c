#include "carBaseMoves.h"
#include "math.h"
#include "usart.h"
#include "wt61.h"
#include "led.h"
#include "demo_dio.h"
#include "demo_motor.h"
extern u16 i;

s16 Motor_V_left;


/**********************************************************************待完善
**函 数 名		：Turn_Angle_Big	原地转弯——大灰度做标志
**参    数		：goal_Angle
**返    回		：void
**描    述		：原地转弯，通过多扫描角度值直到为指定角度为止
**创建时间		：2018年3月20日21:16:58
**创 建 者		：range
**更改时间		：2018年5月2日11:31:56
***********************************************************************/
void Turn_Angle_Big(s32 goal_Angle)
{
//	s32 a =	50;
//	s32 c =	30; 
	s32 b =	goal_Angle - 2;
	while(cos((b - ANGLE_Z) / 57.3) < cos(60 / 57.3))
	{
		if(sin((ANGLE_Z - b) / 57.3) >= 0)
		{
			Set_Motor(50,-50);//原a，-10
		}
		else
		{
			Set_Motor(-50,50);//原-10，a
		}
	}
	Set_Motor(0,0);
	delay_ms(50);
	while(cos((b - ANGLE_Z) / 57.3) < cos(30 / 57.3))
	{
		if(sin((ANGLE_Z - b) / 57.3) >= 0)
		{
			Set_Motor(40,-40);//原a，-10
		}
		else
		{
			Set_Motor(-40,40);//原-10，a
		}
	}
	Set_Motor(0,0);
	delay_ms(50);
	while(cos((b - ANGLE_Z) / 57.3) < cos(15 / 57.3))
	{
		if(sin((ANGLE_Z - b) / 57.3) >= 0)
		{
			Set_Motor(30,-30);//原30，-35
		}
		else
		{
			Set_Motor(-30,30);//原-35，30
		}		
	}
	while(cos((b - ANGLE_Z) / 57.3) < cos(2 / 57.3))
	{
		if(sin((ANGLE_Z - b) / 57.3) >= 0)
		{
			Set_Motor(-30,30);//原30，-35
			delay_ms(50);
			break;
		}
		else
		{
			Set_Motor(30,-30);//原-35，30
			delay_ms(50);
			break;
		}		
	}
	Set_Motor(0,0);
	delay_ms(50);
}


/**********************************************************************待完善
**函 数 名		：Turn_Angle_Small	原地转弯——小灰度做标志
**参    数		：goal_Angle
**返    回		：void
**描    述		：原地转弯，通过多扫描角度值直到为指定角度为止
**创建时间		：2018年3月20日21:16:58
**创 建 者		：range
**更改时间		：2018年5月2日11:31:56
***********************************************************************/
void Turn_Angle_Small(s32 goal_Angle)
{
	s32 a1 =	40; 
	s32 a2 =	40; 
	s32 c1 =	25; 
	s32 c2 =	25; 
	s32 b =	goal_Angle - 2;
	while(cos((b - ANGLE_Z) / 57.3) < cos(45 / 57.3))
	{
		if(sin((ANGLE_Z - b) / 57.3) >= 0)
		{
			Set_Motor(a1,-a2);//原a，-10
		}
		else
		{
			Set_Motor(-a1,a2);//原-10，a
		}
	}
	
	Set_Motor(0,0);
	delay_ms(50);	
	while(cos((b - ANGLE_Z) / 57.3) < cos(30 / 57.3))
	{
		if(sin((ANGLE_Z - b) / 57.3) >= 0)
		{
			Set_Motor(c1,-c2);//原30，-35
		}
		else
		{
			Set_Motor(-c1,c2);//原-35，30
		}		
	}
	Set_Motor(0,0);
	delay_ms(50);
}













/**********************************************************************待完善
**函数名			：car_TurnToAngle	原地转弯
**参数			：目标角度
**返回			：void
**描述			：原地转弯，通过多扫描角度值直到为指定角度为止
**创建时间		：2018年3月20日21:16:58
**创建者			：range
**更改时间		：2018年4月12日20:31:02
bug？
***********************************************************************/
void car_TurnToAngle(s32 goal_Angle)
{
	s32 a = 50;
	s32 b = goal_Angle - 2;
	while(cos((b - ANGLE_Z) / 57.3) < cos(20 / 57.3))
	{
		if(sin((ANGLE_Z - b) / 57.3) >= 0)
		{
			Set_Motor(a,-a);//+3-2
		}
		else
		{
			Set_Motor(-a,a);
		}
	}

	CarAdvance(0);	
	delay_ms(200);
	while(cos((b - ANGLE_Z) / 57.3) < cos(3 / 57.3))
	{
		if(sin((ANGLE_Z-b) / 57.3) >= 0)
		{
			Set_Motor(35,-35);
		}
		else
		{
			Set_Motor(-35,35);
		}		
	}
	SetLeftWhell(0,0);SetRightWhell(0,0);
}



void car_TurnToAngle1(s32 goal_Angle)
{

	s32 a = 50;
	s32 b =	goal_Angle - 2;
	while(cos((b - ANGLE_Z)/57.3) < cos(20 / 57.3))
	{
		if(sin((ANGLE_Z - b) / 57.3) >= 0)
		{
			Set_Motor(a,-a - 5);
		}
		else
		{
			Set_Motor(-a - 5,a);
		}
	}
	SetLeftWhell(0,0);SetRightWhell(0,0);
	delay_ms(200);
	while(cos((b - ANGLE_Z) / 57.3) < cos(3 / 57.3))
	{
		if(sin((ANGLE_Z - b) / 57.3) >= 0)
		{
			Set_Motor(30,-35);
		}
		else
		{
			Set_Motor(-35,30);
		}		
	}
	SetLeftWhell(0,0);SetRightWhell(0,0);
}



void car_TurnToAngle2(s32 goal_Angle)
{

	s32 a =	50;
	s32 b =	goal_Angle - 2;
	while(cos((b - ANGLE_Z) / 57.3) < cos(20 / 57.3))
	{
		if(sin((ANGLE_Z - b) / 57.3) >= 0)
		{
			Set_Motor(a,-50);//原a，-10
		}
		else
		{
			Set_Motor(-50,a);//原-10，a
		}
	}
	SetLeftWhell(0,0);SetRightWhell(0,0);
	delay_ms(100);
	while(cos((b - ANGLE_Z) / 57.3) < cos(3 / 57.3))
	{
		if(sin((ANGLE_Z - b) / 57.3) >= 0)
		{
			Set_Motor(30,-35);
		}
		else
		{
			Set_Motor(-35,30);
		}		
	}
	SetLeftWhell(0,0);SetRightWhell(0,0);
}


/**********************************************************************待完善
**函数名		：判断角度是否正确
**参数			：目标角度
**返回			：1/0
**描述			：在误差值 范围内角度是否匹配匹配则反会1
**创建时间		：2018年3月21日12:54:09
**创建者		：range
**更改时间		：2018年3月21日18:49:23
***********************************************************************/
u8 ture_Angle(u16 goal_Angle)//不是很重要的函数，
{

	if(cos((goal_Angle - ANGLE_Z) / 57.3) > cos(3 / 57.3))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void go_To_Angle(s16 angle)
{
//	s32 a = 35;
	s32 s = 0;
	s32 c = 0;
	while(cos((angle - ANGLE_Z) / 57.3) < cos(5 / 57.3))
	{
		if(cos(ANGLE_Z - angle) < cos(45))
		{
			car_TurnToAngle(angle);
		}
		Set_Motor(s,c);
	}
}



void car_turnAvgle(s16 angle)
{
//	u16 a = 45;
	u16 b;
	b=((s16)ANGLE_Z + 360-angle) % 360;
	
		car_TurnToAngle(b);
}



void car_turnAvgle1(s16 angle)
{
//	u16 a=45;
	u16 b;
	b= ((s16)ANGLE_Z + 360-angle) % 360;
	car_TurnToAngle1(b);
}



void car_turnAvgle2(s16 angle)
{
//	u16 a=45;
	u16 b;
	b = ((s16)ANGLE_Z + 360 - angle) % 360;
	car_TurnToAngle2(b);
}



void WITE_DOWN(u8 x)
{
	while(1)
	{
		if((ANGLE_X <= (360-x)) && (ANGLE_X >= 300))
		{
			delay_ms(5);
			if((ANGLE_X <= (360-x)) && (ANGLE_X >= 300))
			{
				break;
			}
		}
	}
}



void WITE_UP(u8 x)
{
	while(1)
	{
		if((ANGLE_X<=60) && (ANGLE_X>=x))
		{
			delay_ms(5);
			if((ANGLE_X <= 60) &&	(ANGLE_X >= x))
			{
				break;
			}
		}
	}
}



void WITE_FLAT(u8 x)
{
	while(1)
	{
		if((ANGLE_X <= x) ||	(ANGLE_X >= (360 - x)))
		{
			delay_us(100);
			if((ANGLE_X <=x ) ||	(ANGLE_X >= (360 - x)))
			{
				break;
			}
		}
	}
}




u8 FUNC_wait_flat(void (*funcName)(),u8 nature)		//等待	:	水平
{
		u32 add=0;
		while(add<100)
		{
				(*funcName)();
			
				if((ANGLE_X<=nature)||(ANGLE_X>=(360-nature)))
						{
							add++;
						}
				else
						{
							add=0;
						}
				delay_us(5);
		}
		Set_Motor(0,0);
		return 0;
}
u8 FUNC_wait_down(void (*funcName)(),u8 nature)			//等待	:	抬头
{
			u32 add=0;
		while(add<100)
		{
				(*funcName)();
			
				if((ANGLE_X<=(360-nature))&&(ANGLE_X>=310))
						{
							add++;
						}
				else
						{
							add=0;
						}
				delay_us(5);
		}
		Set_Motor(0,0);
		return 0;
}

u8 FUNC_wait_up(void (*funcName)(),u8 nature)		//等待	:	低头
{
			u32 add=0;
		while(add<100)
		{
		
				(*funcName)();
			
				if((ANGLE_X>nature)&&(ANGLE_X<=50))
						{
							add++;
						}
				else
						{
							add=0;
						}
				delay_us(5);
		}
		Set_Motor(0,0);
		return 0;
}

//void Turn_Node(s16 Angle,u16 LowNum,u16 LowTim,u32 InLength,s32 OutLength)
//{
//		while(!DIright&&!DIleft)
//					{
//						car_find_line_40();
//					}
//		if(cos((ANGLE_Z-Angle)/57.3)<cos(12/57.3))
//		{
//					FUNC_wait_length(car_find_line_40,InLength);
//					Set_Motor(-LowNum,-LowNum);
//					TIM_delay_ms(LowTim);
//			car_TurnToAngle(Angle);
//		}
//		FUNC_wait_length(Set_Motor30,OutLength);
//		
//		if(!DIall)
//		{
//			Set_Motor(-12,-12);
//			TIM_delay_ms(300);
//			Set_Motor(-23,-23);
//			TIM_delay_ms(320);
//		}
//}

/**********************************************************************
**函数名			：Green_Turn180
**参数			：
**返回			：
**描述			：绿毯转180
**创建时间		：2018年7月29日09:41:53
**创建者			：lt
**更改时间		：
***********************************************************************/
void Green_Turn180(void)
{
	car_turnAvgle(180);
}

/**********************************************************************
**函数名			：Corrective_Angle
**参数			：
**返回			：
**描述			：矫正角度
**创建时间		：2018年7月29日09:41:53
**创建者			：lt
**更改时间		：
***********************************************************************/
void Corrective_Angle(s16 angle)
{
	int act;
	act = Get_Angle(3);
	if(act > angle + 1)
	{
		while(1)
		{
			act = Get_Angle(3);
			Set_Motor(25,-35);
			if((act >= angle - 2) && (act <= angle + 2))
			{
				CarAdvance(0);
				break;
			}
		}
	}else if(act < angle - 1)
				{
					while(1)
					{
						act = Get_Angle(3);
						Set_Motor(-35,25);
						if((act >= angle - 2) && (act <= angle + 2))
						{
							CarAdvance(0);
							break;
						}
					}
				}
}


void turn_L90(s16 angle)
{
	while(1)
	{
		int act;
		act = Get_Angle(3);
		Set_Motor(-30,40);
		if((act>= angle - 2) && (act <= angle + 2))
		{
			CarAdvance(0);
			break;
		}
	}
}

void turn_R90(s16 angle)
{
	while(1)
	{
		int act;
		act = Get_Angle(3);
		Set_Motor(40,-25);
		if((act>= angle - 2) && (act <= angle + 2))
		{
			CarAdvance(0);
			break;
		}
	}
}
