#include "pid.h"
#include "wt61.h"
#include "carBaseMoves.h"
#include "math.h"
#include "led.h"
#include "sys.h"
#include "lcd.h"
#include "beep.h"


struct pid1{
float SetAngle;//定义设定值
float ActualAngle;//定义实际值
float err;//定义偏差值
float err_next;//定义上一个偏差值
float err_last;//定义最上前的偏差值
float Kp,Ki,Kd;//定义比例、积分、微分系数
float add_angle;
float voltage;
float integral;	
}pid;


void PID_Init(void)
{
	pid.ActualAngle = 0;
	pid.err = 0;
	pid.err_last = 0;
	pid.err_next = 0;
	pid.Kd = 0;
	pid.Ki = 0.08;
	pid.Kp = 15;
	pid.SetAngle = 0.0;
	pid.add_angle = 0;
}


float PID_realize(float angle1)
{
//	u16 s1;
	float incrementAngle = 0.0;
	pid.SetAngle = angle1;
	pid.ActualAngle = Get_Angle(3);
	pid.err = pid.SetAngle - pid.add_angle;
	incrementAngle = pid.Kp*(pid.err - pid.err_next) + pid.Ki*pid.err + pid.Kd*(pid.err-2*pid.err_next+pid.err_last) + 80;
	
//	s1 = (1 * incrementAngle);
	
	pid.err_last = pid.err_next;	
	pid.err_next = pid.err;

	return incrementAngle;
	
}


void PID_LeftTrun(float angle)
{
	u16 s;
//	float a;
//	float l_angle;
	float now_angle,last_angle,difference;
	now_angle = 0;
	last_angle = 0;
	difference = 0;
	now_angle = Get_Angle(3);
	while(1)
	{
		s = PID_realize(angle);		
		if(s > 80)
		{
			s = 80;
		}
		if(s < 20)
		{
			s = 20;
		}
		SetLeftWhell(1,s);SetRightWhell(0,s);	
//		delay_ms(5);
		last_angle = now_angle;
		now_angle = Get_Angle(3);
		while(!(now_angle - last_angle > 1))//确实角度改变才进行下一次运算
		{
			now_angle = Get_Angle(3);
			SetLeftWhell(1,s);SetRightWhell(0,s);
		}
		difference = (float)fabs(now_angle - last_angle);
		if(difference > (float)180)
		{
			difference = (float)2;
		}
		pid.add_angle += difference;
		
		if(pid.add_angle > angle)
		{
			pid.add_angle  = 0;
		}
		
		if(pid.add_angle > (angle - 5.0) && pid.add_angle < (angle + 5.0))
		{
			SetLeftWhell(0,s);SetRightWhell(1,s);
			delay_ms(100);
			pid.add_angle = 0;
			break;
		}
	}
}

void PID_RightTrun(float angle)
{
	
}

