///*
//*********************************************************************************************************
//*本文件是用来写跑图文件中的一些方法的代码。
//*********************************************************************************************************
//*/

#include "demo_DIO_hou.h"
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

//int set_speed;
//int flag_turn = 0;
//int flag_obstacles_front = 0;
//int flag_obstacles_behind;
//int queue1;
//int flag_line;//是否关闭PID直线功能
//int flag_gray = 1;//是否关闭灰度扫描功能
//int flag_obstacles = 1;//是否关闭前方障碍检测功能;
//int flag_queue;
//int stop;
//int door;
//extern struct SAngle 	stcAngle;
//extern int site[8];
//int i,act_angle;
//static u8 DIR = 0;

////extern u8 half_s;

//*********************************************************************************************************
//*	函 数 名: Gray_Run50
//*	功能说明: 灰度控制直线程序
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
void Gray_Run50_hou()//1234 5678
{

	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(50,50); }
	
	if(Gray44 == 0)       { Set_Motor_1(30,50); }
	if(Gray55 == 0)       { Set_Motor_1(50,30); }
	
	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(20,50); }
	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(50,20); }
	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(20,50); }
	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(50,20); }
	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(0,50); }
	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(50,0); }
	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-25,40); }
	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(40,-25); }
	
	else if((Gray11 == 0 || Gray88 == 0) && (Gray44 == 0 || Gray55 == 0))   { Set_Motor_1(50,50); }
	
	else if(Gray11 == 0)        { Set_Motor_1(-30,30); }
	else if(Gray88 == 0)        { Set_Motor_1(30,-30); }
	
	else    	{ Set_Motor_1(50,50); }	
}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Go
//*	功能说明: 测试轮子接线是否正确
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Go(u8 speed)//1234 5678
//{
//	while(1)
//	{
//		CarAdvance(speed);//四轮正转
//		delay_ms(3000);
//		
////		CarRetreat(speed);//四轮反转
////		delay_ms(3000);
////		
////		SetLeftWhell(0,speed);SetRightWhell(1,0);
////		delay_ms(3000);   //左轮正转，右轮不转
////		
////		SetLeftWhell(1,speed);SetRightWhell(1,0);
////		delay_ms(3000);   //左轮反转，右轮不转
////		
////		SetRightWhell(0,speed);SetLeftWhell(1,0);
////		delay_ms(3000);   //左轮不转，右轮正转
////		 
////		SetRightWhell(1,speed);SetLeftWhell(1,0);
////		delay_ms(3000);   //左轮不转，右轮反转
//	}
//}
///*
//*********************************************************************************************************
//*	函 数 名: Brake_Stop
//*	功能说明: 刹车方法
//*	形    参: speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Brake_Stop()//减速为0
//{
//	if((Gray11 == 1 && Gray22 == 1 && Gray33 == 1 && 
//		Gray44 == 1 && Gray55 == 1 && Gray66 == 1 && Gray77 == 1 && Gray88 == 1))
//	{
//		CarAdvance(0);//刹车
//		delay_ms(100);
//	}
//}

///*
//********************************************************************
//*	函 数 名: Gray
//*	功能说明: 判断灰度第几个灯亮
//*	形    参: number 	判断哪个的灯亮
//*	返 回 值: 0或1
//**********************************************************************/
//int Gray(int number)
//{
//	u8 value;
//	switch(number)
//	{
//		case 1 :if(Gray11==1) value=1; else value=0;break;
//		case 2 :if(Gray22==1) value=1; else value=0;break;
//		case 3 :if(Gray33==1) value=1; else value=0;break;
//		case 4 :if(Gray44==1) value=1; else value=0;break;
//		case 5 :if(Gray55==1) value=1; else value=0;break;
//		case 6 :if(Gray66==1) value=1; else value=0;break;
//		case 7 :if(Gray77==1) value=1; else value=0;break;
//		case 8 :if(Gray88==1) value=1; else value=0;break;

//	}
//	if(value==1)
//		return 0;
//	else
//		return 1;	
//}

///*
//********************************************************************
//*	函 数 名: Gray_Count
//*	功能说明: 计算灰度亮的个数
//*	形    参: 无
//*	返 回 值: 亮灯数量
//**********************************************************************/
//int Gray_Count()
//{
//	return(Gray(1)+Gray(2)+Gray(3)+Gray(4)+Gray(5)+Gray(6)+Gray(7)+Gray(8));
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run
//*	功能说明: 灰度控制直线程序
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Run(u8 speed)//1234 5678
//{
//	if((Gray44 == 0) || (Gray55 == 0))
//		{
//			SetLeftWhell(0,speed);SetRightWhell(0,speed);
//		}	
//	else if(Gray22 == 0 && Gray33 == 0)
//		{
//			SetLeftWhell(0,0);SetRightWhell(0,speed);
//		}
//	else if(Gray77 == 0 && Gray66 == 0)
//		{
//			SetLeftWhell(0,speed);SetRightWhell(0,0);
//		}		
//	else if((Gray55 == 0) && (Gray66 == 0))
//		{	
//			SetLeftWhell(0,speed);SetRightWhell(0,0);
//		}
//	else if((Gray33 == 0) && (Gray44 == 0))
//		{	
//			SetLeftWhell(0,0);SetRightWhell(0,speed);
//		}
//	else if(Gray11 == 0)
//		{
//			SetLeftWhell(1,20);SetRightWhell(0,speed);
//		}
//	else if(Gray88 == 0)
//		{
//			SetLeftWhell(0,speed);SetRightWhell(1,20);
//		}
//		else 		
//		{
//			CarAdvance(speed);
//		}
//}


//void Gray_Run_1(u8 speed)//1234 5678
//{
//	if((Gray44 == 0) || (Gray55 == 0))
//		{
//			SetLeftWhell(0,speed);SetRightWhell(0,speed);
//		}	
//	else if(Gray22 == 0 && Gray33 == 0)
//		{
//			SetLeftWhell(0,0);SetRightWhell(0,speed);
//		}
//	else if(Gray77 == 0 && Gray66 == 0)
//		{
//			SetLeftWhell(0,speed);SetRightWhell(0,0);
//		}		
//	else if((Gray55 == 0) && (Gray66 == 0))
//		{	
//			SetLeftWhell(0,speed);SetRightWhell(0,0);
//		}
//	else if((Gray33 == 0) && (Gray44 == 0))
//		{	
//			SetLeftWhell(0,0);SetRightWhell(0,speed);
//		}
//	else if(Gray11 == 0)
//		{
//			SetLeftWhell(1,20);SetRightWhell(0,speed);
//		}
//	else if(Gray88 == 0)
//		{
//			SetLeftWhell(0,speed);SetRightWhell(1,20);
//		}
//		else 		
//		{
//			CarAdvance(speed);
//		}
//}


// /*
//*********************************************************************************************************
//*	函 数 名: Gray_Run15
//*	功能说明: 灰度控制直线程序  用于从高台下坡用
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Run15()//下坡用
//{

//	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(14,15); }
//	
//	if(Gray44 == 0)       { Set_Motor_1(8,15); }
//	if(Gray55 == 0)       { Set_Motor_1(14,9); }
//	
//	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(3,25); }
//	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(14,3); }
//	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(6,25); }
//	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(14,7); }
//	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(1,30); }
//	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(14,1); }
//	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-5,25); }
//	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(14,-3); }
//	
//	else    	{ Set_Motor_1(14,15); }	
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run20_20
//*	功能说明: 灰度控制直线程序  用于从五个平台下坡用
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
void Gray_Run20_20_hou()//用于从五个平台下坡用
{

	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(23,20); }
	
	if(Gray44 == 0)       { Set_Motor_1(12,20); }
	if(Gray55 == 0)       { Set_Motor_1(20,12); }
	
	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(8,20); }
	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(20,8); }
	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(5,20); }
	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(20,5); }
	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(0,20); }
	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(20,0); }
	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-10,20); }
	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(20,-10); }
	
	else if(Gray88 == 0){ Set_Motor_1(20,-20); }
	
	else    	{ Set_Motor_1(23,20); }	
}



///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run20
//*	功能说明: 灰度控制直线程序  用于从第一个高台下坡用，禁止改
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Run20()//下坡用
//{

//	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(15,25); }
//	
//	if(Gray44 == 0)       { Set_Motor_1(20,25); }
//	if(Gray55 == 0)       { Set_Motor_1(25,18); }
//	
//	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(6,25); }
//	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(16,11); }
//	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(8,25); }
//	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(16,13); }
//	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(3,25); }
//	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(16,8); }
//	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(0,25); }
//	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(16,4); }
//	
//	else    	{ Set_Motor_1(15,40); }	
//}
//void  Gray_Run25gai()
//{
//    if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(12,10); }
//	if(Gray44 == 0)       { Set_Motor_1(14,10); }
//	if(Gray55 == 0)       { Set_Motor_1(14,10); }
//	
//	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(10,50); }
//	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(20,7); }
//	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(10,30); }
//	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(20,10); }
//	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(5,40); }
//	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(25,5); }
//	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(0,45); }
//	else if(Gray11 == 0 && Gray22 == 0&&Gray33 == 0)  { Set_Motor_1(0,60); }
//	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(25,0); }
//	else    	{ Set_Motor_1(21,26); }	

//}
//void  Gray_Run35()
//{
//     if(Gray44==0&&Gray55==0) Set_Motor_1(48,48);
//	else if(Gray55==0&&Gray66==0) Set_Motor_1(45,20);
//	else if(Gray33==0&&Gray44==0) Set_Motor_1(20,45);
//	else if(Gray66==0&&Gray77==0) Set_Motor_1(45,0);
//	else if(Gray22==0&&Gray33==0) Set_Motor_1(-10,55);
//	else if(Gray77==0&&Gray88==0) Set_Motor_1(60,-30);
//	else if(Gray11==0&&Gray22==0) Set_Motor_1(-45,60);	
//	else if(Gray33==0) Set_Motor_1(10,45);
//	else if(Gray22==0) Set_Motor_1(-10,45);
//	else if(Gray11==0) Set_Motor_1(-45,60);
//	else if(Gray44==0) Set_Motor_1(45,40);
//	else if(Gray55==0) Set_Motor_1(40,45);
//	else if(Gray66==0) Set_Motor_1(45,-10);
//	else if(Gray77==0) Set_Motor_1(45,10);
//	else if(Gray88==0) Set_Motor_1(60,-45);
//	else	
//		Set_Motor_1(48,48);
//}
//void  Gray_Run_gaotai()//减速下高台
//{
//     if(Gray44==0&&Gray55==0) Set_Motor_1(0,0);
//	else if(Gray55==0&&Gray66==0) Set_Motor_1(35,10);
//	else if(Gray33==0&&Gray44==0) Set_Motor_1(10,35);
//	else if(Gray66==0&&Gray77==0) Set_Motor_1(35,-10);
//	else if(Gray22==0&&Gray33==0) Set_Motor_1(-10,35);
//	else if(Gray77==0&&Gray88==0) Set_Motor_1(35,-35);
//	else if(Gray11==0&&Gray22==0) Set_Motor_1(-35,35);	
//	else if(Gray33==0) Set_Motor_1(35,10);
//	else if(Gray22==0) Set_Motor_1(35,-10);
//	else if(Gray11==0) Set_Motor_1(35,-35);
//	else if(Gray44==0) Set_Motor_1(0,0);
//	else if(Gray55==0) Set_Motor_1(0,0);
//	else Set_Motor_1(0,0);

//}





///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run25
//*	功能说明: 灰度控制直线程序  用于从高台下坡用
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Run25()//下坡用
//{

//	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(23,25); }
//	
//	if(Gray44 == 0)       { Set_Motor_1(14,25); }
//	if(Gray55 == 0)       { Set_Motor_1(23,15); }
//	
//	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(6,25); }
//	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(23,7); }
//	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(9,25); }
//	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(23,10); }
//	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(4,25); }
//	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(23,5); }
//	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(0,25); }
//	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(23,0); }
//	
//	else    	{ Set_Motor_1(23,25); }	
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run30
//*	功能说明: 灰度控制直线程序  用于从高台下坡用
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
void Gray_Run30_hou()//过刀山用,禁止改
{

	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(30,30); }
	
	if(Gray55 == 0)       { Set_Motor_1(15,30); }
	if(Gray44 == 0)       { Set_Motor_1(30,15); }
	
	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(10,30); }
	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(30,10); }
	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(0,30); }
	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(30,0); }
	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(-15,30); }
	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(30,-15); }
	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-30,30); }
	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(30,-30); }
	
	else    	{ Set_Motor_1(28,30); }	
}


///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run40
//*	功能说明: 灰度控制直线程序
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
void Gray_Run40_hou()//右边轮速度较慢，给予补偿
{

	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(40,40); }
	
	if(Gray44 == 0)       { Set_Motor_1(15,40); }
	if(Gray55 == 0)       { Set_Motor_1(40,15); }
	
	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(0,43); }
	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(40,0); }
	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(0,43); }
	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(40,0); }
	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(-20,40); }
	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(40,-20); }
	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-30,41); }
	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(40,-30); }
	
	else if(Gray11 == 0)        { Set_Motor_1(-30,30); }
	else if(Gray88 == 0)        { Set_Motor_1(30,-30); }
	
	else    	{ Set_Motor_1(40,40); }	
}
//void Gray_Run40gai()//右边轮速度较慢，给予补偿
//{

//	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(40,43); }
//	
//	if(Gray44 == 0)       { Set_Motor_1(30,43); }
//	if(Gray55 == 0)       { Set_Motor_1(40,32); }
//	
//	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(15,43); }
////	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(40,17); }
//	else if(Gray66 == 0 || Gray77 == 0 || Gray88 == 0)  { Set_Motor_1(60,20); }
//	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(25,43); }
////	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(60,10); }
//	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(10,40); }
////	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(60,-25); }
//	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-10,41); }
////	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(60,-40); }
//	
////	else if(Gray11 == 0)        { Set_Motor_1(-20,30); }
////	else if(Gray88 == 0)        { Set_Motor_1(30,-20); }
//	
//	else    	{ Set_Motor_1(40,43); }	
//}
//void Gray_Run40TaiJie()//过平台
//{

//	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(40,35); }
//	
//	if(Gray44 == 0)       { Set_Motor_1(30,43); }
//	if(Gray55 == 0)       { Set_Motor_1(40,32); }
//	
//	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(15,43); }
//	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(40,17); }
//	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(25,43); }
//	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(40,27); }
//	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(10,40); }
//	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(40,11); }
//	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-10,41); }
//	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(40,-10); }
//	
////	else if(Gray11 == 0)        { Set_Motor_1(-20,30); }
////	else if(Gray88 == 0)        { Set_Motor_1(30,-20); }
//	
//	else    	{ Set_Motor_1(40,35); }	
//}
///*



///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run60
//*	功能说明: 灰度控制直线程序
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
void Gray_Run60_hou()//1234 5678
{

	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(60,60); }
	
	if(Gray44 == 0)       { Set_Motor_1(30,60); }
	if(Gray55 == 0)       { Set_Motor_1(60,40); }
	
	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(30,60); }
	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(60,30); }
	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(30,60); }
	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(60,30); }
	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(10,60); }
	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(60,10); }
	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-10,40); }
	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(40,-10); }
	
	else if(Gray11 == 0)        { Set_Motor_1(-30,30); }
	else if(Gray88 == 0)        { Set_Motor_1(30,-30); }
	
	else    	{ Set_Motor_1(60,60); }	
}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run70
//*	功能说明: 灰度控制直线程序
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
 void Gray_Run70_hou()//1234 5678
{

	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(70,70); }
	
	if(Gray44 == 0)       { Set_Motor_1(60,70); }
	if(Gray55 == 0)       { Set_Motor_1(70,60); }
	
	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(40,65); }
	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(65,40); }
	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(45,65); }
	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(65,45); }
	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(20,60); }
	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(60,20); }
	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-10,50); }
	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(50,-10); }
	
	else if(Gray11 == 0)        { Set_Motor_1(-30,40); }
	else if(Gray88 == 0)        { Set_Motor_1(40,-30); }
	
	else    	{ Set_Motor_1(70,70); }	
}


///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run80
//*	功能说明: 灰度控制直线程序
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Run80()//1234 5678
//{

//	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(80,80); }
//	
//	if(Gray44 == 0)       { Set_Motor_1(65,80); }
//	if(Gray55 == 0)       { Set_Motor_1(80,65); }
//	
//	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(45,75); }
//	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(75,45); }
//	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(55,75); }
//	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(75,55); }
//	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(30,70); }
//	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(70,30); }
//	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(0,60); }
//	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(60,0); }
//	
//	else if(Gray11 == 0)        { Set_Motor_1(-20,50); }
//	else if(Gray88 == 0)        { Set_Motor_1(50,-20); }
//	
//	else    	{ Set_Motor_1(80,80); }	
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run_Taijie
//*	功能说明: 灰度控制直线程序
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Run_Taijie()//左轮速度偏小，给予补偿
//{
//	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(35,29); }
//	
//	if(Gray44 == 0)       { Set_Motor_1(25,29); }
//	if(Gray55 == 0)       { Set_Motor_1(35,20); }
//	
//	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(20,29); }
//	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(35,15); }
//	
//	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(15,29); }
//	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(35,10); }
//	
//	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(8,29); }
//	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(35,5); }
//	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-10,29); }
//	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(35,-10); }
//	
//	else if(Gray11 == 0)        { Set_Motor_1(-20,29); }
//	else if(Gray88 == 0)        { Set_Motor_1(35,-20); }
//	
//	else    	{ Set_Motor_1(35,29); }		
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run_Taijie1
//*	功能说明: 灰度控制直线程序
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Run_Taijie1()//左轮速度偏小，给予补偿
//{
//	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(35,29); }
//	
//	if(Gray44 == 0)       { Set_Motor_1(25,29); }
//	if(Gray55 == 0)       { Set_Motor_1(35,20); }
//	
//	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(20,29); }
//	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(35,15); }
//	
//	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(15,29); }
//	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(35,10); }
//	
//	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(8,29); }
//	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(35,5); }
//	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-10,29); }
//	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(35,-10); }
//	
//	else if(Gray11 == 0)        { Set_Motor_1(-20,29); }
//	else if(Gray88 == 0)        { Set_Motor_1(35,-20); }
//	
//	else    	{ Set_Motor_1(35,29); }		
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run_Taijie_Speed
//*	功能说明: 灰度控制直线程序
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Run_Taijie_Speed(int speed)//左轮速度偏小，给予补偿
//{
//	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(speed + 5,speed); }
//	
//	if(Gray44 == 0)       { Set_Motor_1(speed - 5,speed); }
//	if(Gray55 == 0)       { Set_Motor_1(speed + 5,speed - 10); }
//	
//	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(speed - 20,speed); }
//	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(speed + 5,speed - 15); }
//	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(speed - 15,speed); }
//	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(speed + 5,speed - 20); }
//	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(speed - 22,speed); }
//	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(speed + 5,speed - 25); }
//	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(speed - 40,speed); }
//	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(speed + 5,speed - 40); }
//	
//	else if(Gray11 == 0)        { Set_Motor_1(speed - 50,speed); }
//	else if(Gray88 == 0)        { Set_Motor_1(speed + 4,speed - 50); }
//	
//	else    	{ Set_Motor_1(speed + 5,speed); }		
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run_Jiansuban
//*	功能说明: 灰度控制直线程序
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Run_Jiansuban()//左轮速度偏小，给予补偿
//{
//	if(Gray44 == 0 || Gray55 == 0)       { Set_Motor_1(33,29); }
//	
//	if(Gray44 == 0)       { Set_Motor_1(24,29); }
//	if(Gray55 == 0)       { Set_Motor_1(33,20); }
//	
//	else if(Gray22 == 0 && Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(19,29); }
//	else if(Gray55 == 0 && Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(33,15); }
//	else if(Gray33 == 0 && Gray44 == 0)  { Set_Motor_1(14,29); }
//	else if(Gray55 == 0 && Gray66 == 0)  { Set_Motor_1(33,10); }
//	else if(Gray22 == 0 && Gray33 == 0)  { Set_Motor_1(7,29); }
//	else if(Gray66 == 0 && Gray77 == 0)  { Set_Motor_1(33,5); }
//	else if(Gray11 == 0 && Gray22 == 0)  { Set_Motor_1(-10,29); }
//	else if(Gray77 == 0 && Gray88 == 0)  { Set_Motor_1(33,-10); }
//	
//	else if(Gray11 == 0)        { Set_Motor_1(-20,29); }
//	else if(Gray88 == 0)        { Set_Motor_1(33,-20); }
//	
//	else    	{ Set_Motor_1(33,29); }		
//}

///*
//*********************************************************************************************************
//*	函 数 名: run_gray
//*	功能说明: 只走灰度巡线其它情况不会影响
//*	形    参: i 毫秒		speed 速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void run_gray(u16 i,u8 speed)
//{
//	while(i -- )
//	{
//		delay_ms(1);
//		Gray_Run50();//直线
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Down
//*	功能说明: 灰度控制直线程序  用于从高台下坡用
//*	形    参: direction	方向（0正1反） 	speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Down(u16 i)
//{
//	while(i--)
//	{
//		Gray_Run25gai();
//		delay_ms(8);
//		CarRetreat(5);
//		delay_ms(4);
//	}
//}
//void Gray_Down2(u16 i)
//{
//	while(i--)
//	{
//		Gray_Run35();
//		delay_ms(8);
//		CarRetreat(0);
//		delay_ms(4);
//	}
//}
///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run15
//*	功能说明: 只走灰度巡线其它情况不会影响，数字代表速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Delay_Run15(u16 i)//只走灰度巡线其它情况不会影响，数字代表速度
//{
//	while(i -- )
//	{
//		delay_ms(1);
//		Gray_Run15();//灰度走直线,数字代表速度
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run15_0
//*	功能说明: 只走灰度巡线其它情况不会影响，15速度与减速交替使用
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Delay_Run15_0(u16 i)//只走灰度巡线其它情况不会影响，15速度与减速交替使用
//{
//	while(i -- )
//	{
//		Gray_Run15();//灰度走直线,数字代表速度
//		delay_ms(7);
//		CarRetreat(5);//后退
//		delay_ms(3);
//	
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run20
//*	功能说明: 只走灰度巡线其它情况不会影响，数字代表速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Delay_Run20(u16 i)//只走灰度巡线其它情况不会影响，数字代表速度
//{
//	while(i -- )
//	{
//		delay_ms(1);
//		Gray_Run20();//灰度走直线,数字代表速度
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run20
//*	功能说明: 只走灰度巡线其它情况不会影响，数字代表速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
void Gray_Delay_Run20_20_hou(u16 i)//只走灰度巡线其它情况不会影响，数字代表速度
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run20_20_hou();//灰度走直线,数字代表速度
	}
}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run25
//*	功能说明: 只走灰度巡线其它情况不会影响，数字代表速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//int Gray_Delay_Run25(u16 i)//只走灰度巡线其它情况不会影响，数字代表速度
//{
//	while(i -- )
//	{
//		delay_ms(1);
//		Gray_Run25();//灰度走直线,数字代表速度
//	}
//	return 0;
//}
//int Gray_Delay_Run25gai(u16 i)//只走灰度巡线其它情况不会影响，数字代表速度
//{
//	while(i -- )
//	{
//		delay_ms(1);
//		Gray_Run25gai();//灰度走直线,数字代表速度
//	}
//	return 0;
//}
//int Gray_Delay_Run35(u16 i)//只走灰度巡线其它情况不会影响，数字代表速度
//{
//	while(i -- )
//	{
//		delay_ms(1);
//		Gray_Run35();//灰度走直线,数字代表速度
//	}
//	return 0;
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run30
//*	功能说明: 只走灰度巡线其它情况不会影响，数字代表速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
int Gray_Delay_Run30_hou(u16 i)//只走灰度巡线其它情况不会影响，数字代表速度
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run30_hou();//灰度走直线,数字代表速度
	}
	return 0;
}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run40
//*	功能说明: 只走灰度巡线其它情况不会影响，数字代表速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
int Gray_Delay_Run40_hou(u16 i)//只走灰度巡线其它情况不会影响，数字代表速度
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run40_hou();//灰度走直线,数字代表速度
	}
	return 0;
}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run50
//*	功能说明: 只走灰度巡线其它情况不会影响，数字代表速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
int Gray_Delay_Run50_hou(u16 i)//只走灰度巡线其它情况不会影响，数字代表速度
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run50_hou();//灰度走直线,数字代表速度
	}
	return 0;
}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run60
//*	功能说明: 只走灰度巡线其它情况不会影响，数字代表速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
int Gray_Delay_Run60_hou(u16 i)//只走灰度巡线其它情况不会影响，数字代表速度
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run60_hou();//灰度走直线,数字代表速度
	}
	return 0;
}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run70
//*	功能说明: 只走灰度巡线其它情况不会影响，数字代表速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
int Gray_Delay_Run70_hou(u16 i)//只走灰度巡线其它情况不会影响，数字代表速度
{
	while(i -- )
	{
		delay_ms(1);
		Gray_Run70();//灰度走直线,数字代表速度
	}
	return 0;
}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run_Taijie
//*	功能说明: 只走灰度巡线其它情况不会影响，过台阶(taijie)速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//int Gray_Delay_Run_Taijie(u16 i)//只走灰度巡线其它情况不会影响，过台阶(taijie)速度
//{
//	while(i -- )
//	{
//		delay_ms(1);
//		Gray_Run_Taijie();//灰度走直线,数字代表速度
//	}
//	return 0;
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run_Taijie1
//*	功能说明: 只走灰度巡线其它情况不会影响，过台阶(taijie)速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//int Gray_Delay_Run_Taijie1(u16 i)//只走灰度巡线其它情况不会影响，过台阶(taijie)速度
//{
//	while(i -- )
//	{
//		delay_ms(1);
//		Gray_Run_Taijie1();//灰度走直线,数字代表速度
//	}
//	return 0;
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run_Taijie2
//*	功能说明: 只走灰度巡线其它情况不会影响，过台阶(taijie)速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Delay_Run_Taijie2(u16 i)//只走灰度巡线其它情况不会影响，过台阶(taijie)速度
//{
//	while(i -- )
//	{
//		Gray_Run_Taijie1();//灰度走直线,数字代表速度
//		delay_ms(9);
//		Set_Motor_1(0,0);//四轮正转
//		delay_ms(1);
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run_Jiansuban
//*	功能说明: 只走灰度巡线其它情况不会影响，过减速板(Jiansuban)速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//int Gray_Delay_Run_Jiansuban(u16 i)//只走灰度巡线其它情况不会影响，过减速板(Jiansuban)速度
//{
//	while(i -- )
//	{
//		delay_ms(1);
//		Gray_Run_Jiansuban();//灰度走直线,数字代表速度
//	}
//	return 0;
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Delay_Run_C
//*	功能说明: 只走灰度巡线其它情况不会影响，转圈速度
//*	形    参: i 毫秒	
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//int Gray_Delay_Run_C(u16 i)//只走灰度巡线其它情况不会影响，转圈速度
//{
//	while(i -- )
//	{
//		delay_ms(1);
//		run_c();//灰度走直线,数字代表速度
//	}
//	return 0;
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_curve
//*	功能说明: 灰度走曲线程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_curve(u8 speed)
//{
//	if(DIR == 0 )
//	{
//		if(Gray44 == 0)        { Set_Motor_1(speed + 10,speed); }	
//		else if(Gray55 == 0)        { Set_Motor_1(speed + 10,speed); }
//		else if(Gray33 == 0)        { Set_Motor_1(speed - 10,speed); } 
//		else if(Gray66 == 0)        { Set_Motor_1(speed + 20,speed); }
//		else if(Gray22 == 0)        { Set_Motor_1(speed - 30,speed); }
//		else if(Gray77 == 0)        { Set_Motor_1(speed + 20,speed - 20); }
//		else if(Gray11 == 0)        { Set_Motor_1(speed - 20,speed + 20); }
//		else if(Gray88 == 0)        { Set_Motor_1(speed + 30,speed - 30); }
//	}
//	else
//	{
//		if(Gray444 == 0)        { Set_Motor_1(speed,speed); }	
//		else if(Gray555 == 0)        { Set_Motor_1(speed + 10,speed); }
//		else if(Gray333 == 0)        { Set_Motor_1(speed - 10,speed); } 
//		else if(Gray666 == 0)        { Set_Motor_1(speed + 20,speed); }
//		else if(Gray222 == 0)        { Set_Motor_1(speed - 30,speed); }
//		else if(Gray777 == 0)        { Set_Motor_1(speed + 20,speed - 20); }
//		else if(Gray111 == 0)        { Set_Motor_1(speed - 20,speed + 20); }
//		else if(Gray888 == 0)        { Set_Motor_1(speed + 30,speed - 30); }
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Curve0
//*	功能说明: 前灰度走曲线程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Curve0(u8 speed)//前灰度走曲线
//{

//	if(Gray44 == 0 && Gray55 == 0) Set_Motor_1(20,50);
//	else if(Gray55 == 0 && Gray66 == 0) Set_Motor_1(50,35);
//	else if(Gray33 == 0 && Gray44 == 0) Set_Motor_1(10,50);
//	else if(Gray66 == 0 && Gray77 == 0) Set_Motor_1(50,-10);
//	else if(Gray22 == 0 && Gray33 == 0) Set_Motor_1(-35,50);
//	else if(Gray77 == 0 && Gray88 == 0) Set_Motor_1(50,-50);
//	else if(Gray11 == 0 && Gray22 == 0) Set_Motor_1(-50,50);
//	else if(Gray44 == 0) Set_Motor_1(18,50);
//	else if(Gray55 == 0) Set_Motor_1(27,50);	
//	else if(Gray33 == 0) Set_Motor_1(0,50);
//	else if(Gray66 == 0) Set_Motor_1(50,15);
//	else if(Gray22 == 0) Set_Motor_1(-25,50);
//	else if(Gray77 == 0) Set_Motor_1(50,-25);
//	else if(Gray11 == 0) Set_Motor_1(-50,50);
//	else if(Gray88 == 0) Set_Motor_1(50,-50);
//	else Set_Motor_1(30,40);
//}


///*
//*********************************************************************************************************
//*	函 数 名: Front_Gray_Curve_L50_Turn
//*	功能说明: 前灰度曲线左转（待验证）
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/

//void Front_Gray_Curve_L50_Turn(u8 speed)
//{
//	while(1)
//	{
//		SetLeftWhell(1,speed); SetRightWhell(0,speed);//原40
//		if(Gray88 == 0 || Gray11 == 0)
//		{
//			break;
//		}
//	}
//	while(1)
//	{
//		SetLeftWhell(1,speed - 10); SetRightWhell(0,speed - 10);
//		if(Gray55 == 0 || Gray44 == 0)
//		{
//			break;
//		}
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: run_c
//*	功能说明: 转圈
//*	形    参: speed 控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void run_c()//转圈
//{
//	if(	Gray44 == 0 && Gray55 == 0) Set_Motor_1(20,45);
//	else if(Gray55 == 0 && Gray66 == 0) Set_Motor_1(40,25);
//	else if(Gray33 == 0 && Gray44 == 0) Set_Motor_1(20,45);
//	else if(Gray66 == 0 && Gray77 == 0) Set_Motor_1(40,-25);
//	else if(Gray66 == 0 && Gray77 == 0) Set_Motor_1(-25,40);
//	else if(Gray77 == 0 && Gray88 == 0) Set_Motor_1(40,-40);
//	else if(Gray11 == 0 && Gray22 == 0) Set_Motor_1(-40,40);
//	else if(Gray44 == 0) Set_Motor_1(18,45);
//	else if(Gray55 == 0) Set_Motor_1(25,45);	
//	else if(Gray33 == 0) Set_Motor_1(22,45);
//	else if(Gray66 == 0) Set_Motor_1(42,25);
//	else if(Gray22 == 0) Set_Motor_1(-25,40);
//	else if(Gray77 == 0) Set_Motor_1(40,-25);
//	else if(Gray11 == 0) Set_Motor_1(-40,40);
//	else if(Gray88 == 0) Set_Motor_1(40,-40);

//	else Set_Motor_1(18,20);
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run2
//*	功能说明: 灰度走曲线程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Run2(u8 speed)
//{
//	if((Gray33 == 0) || (Gray55 == 0))
//		{
//			SetLeftWhell(1,speed + 5);SetRightWhell(0,speed);
//		}	
//	else if(Gray22 == 0)
//		{
//			SetLeftWhell(1,0);SetRightWhell(0,speed);
//		}
//	else if(Gray77 == 0 || Gray66 == 0)
//		{
//			SetLeftWhell(1,speed+6);SetRightWhell(0,0);
//		}		
//	else if((Gray55 == 0) && (Gray66 == 0))
//		{	
//			SetLeftWhell(1,speed);SetRightWhell(0,0);
//		}
//	else if((Gray33 == 0) && (Gray44 == 0))
//		{	
//			SetLeftWhell(1,0);SetRightWhell(0,speed);
//		}
//	else{
//			CarAdvance(speed);
//		}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run3
//*	功能说明: 爬坡
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/

//void Gray_Climb(u8 speed)
//{
//	if((Gray44 == 0) && (Gray55 == 0))
//				{
//					SetLeftWhell(1,speed);SetRightWhell(0,speed);
//				}	
//		else if(Gray22 == 0 || Gray33 == 0)
//					{
//						SetLeftWhell(1,speed - 15);SetRightWhell(0,speed + 25);
//					}
//		else if((Gray33 == 0) && (Gray44 == 0))
//					{	
//						SetLeftWhell(1,speed - 10);SetRightWhell(0,speed + 20);
//					}
//		else if((Gray55 == 0) && (Gray66 == 0))
//					{	
//						SetLeftWhell(1,speed + 20);SetRightWhell(0,speed - 10);
//					}
//		else if(Gray77 == 0 || Gray66 == 0)
//					{
//						SetLeftWhell(1,speed + 25);SetRightWhell(0,speed - 15);
//					}
//		else if(Gray11 == 0 )
//					{
//						SetLeftWhell(1,0);SetRightWhell(0,speed + 20);
//					}
//		else if(Gray88 == 0)
//					{
//						SetLeftWhell(1,speed + 20);SetRightWhell(0,0);
//					}
//					
//		else {
//						SetLeftWhell(1,speed);SetRightWhell(0,speed);
//					}
//}


///*
//*********************************************************************************************************
//*	函 数 名: Gray_Run4
//*	功能说明: 过减速带
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_Run4(u8 speed)//1234 5678
//{
//		if((Gray44 == 0) || (Gray55 == 0))
//				{
//					CarAdvance(speed);
//				}
//				
//		else if(Gray22 == 0 || Gray33 == 0)
//					{
//						SetLeftWhell(1,0);SetRightWhell(0,speed + 20);
//					}
//		else if(Gray77 == 0 || Gray66 == 0)
//					{
//						SetLeftWhell(1,speed + 20);SetRightWhell(0,0);
//					}		
//		else if((Gray55 == 0) && (Gray66 == 0))
//					{	
//						SetLeftWhell(1,speed);SetRightWhell(0,speed-10);
//					}
//		else if((Gray33 == 0) && (Gray44 == 0))
//					{	
//						SetLeftWhell(1,speed-10);SetRightWhell(0,speed);
//					}
//		else if(Gray11 == 0 || Gray22 == 0)
//					{
//						SetLeftWhell(0,35);SetRightWhell(0,speed + 15);
//					}
//		else if(Gray77 == 0 || Gray88 == 0)
//					{
//						SetLeftWhell(1,speed + 15);SetRightWhell(1,35);
//					}
//		else {
//						CarAdvance(speed);
//					}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_L37_Turn
//*	功能说明: 灰度左转弯程序，数字代表转的角度
//*	形    参: 无
//*	返 回 值: 无
//*********************************************************************************************************
//*/

//void Gray_L37_Turn()
//{
//	while(1)
//	{
//		if(Gray11 == 0)
//		{	
//			Set_Motor_1(-50,70);
//			delay_ms(50);
//			break;
//		}
//	}
//	while(1)
//	{
//		Set_Motor_1(-50,50);
//		if(Gray44 == 0 || Gray55 == 0)
//		{		
//			delay_ms(10);
//			if(Gray44 == 0 || Gray55 == 0)
//			break;
//		}
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_L_Turn
//*	功能说明: 灰度左转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_L_Turn(u8 speed,int angle)
//{
//	while(1)
//	{
//		float a;
//		a = Get_Angle(3);  
//		SetLeftWhell(1,speed + 10); SetRightWhell(0,speed);
//		
//		if((angle - (float)2 < a ) && ( a < angle + (float)2))
//		{
//			break;
//		}
//	}
//}
//	
///*
//*********************************************************************************************************
//*	函 数 名: Gray_L1_Turn
//*	功能说明: 灰度左转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_L1_Turn(u8 speed)
//{
//	if(DIR == 0)
//	{
//		while(1)
//		{
//			SetLeftWhell(1,speed + 5); SetRightWhell(0,speed);//原40
//			if(Gray88 == 0 || Gray11 == 0)
//			{
//				break;
//			}
//		}
//		while(1)
//		{
//			SetLeftWhell(1,speed - 10); SetRightWhell(0,speed - 10);
//			if(Gray55 == 0 || Gray44 == 0)
//			{
//				break;
//			}
//		}
//	}else
//	{
//		while(1)
//		{
//			SetLeftWhell(1,speed + 5); SetRightWhell(0,speed);//原40
//			if(Gray888 == 0 || Gray111 == 0)
//			{
//				break;
//			}
//		}
//		while(1)
//		{
//			SetLeftWhell(1,speed - 10); SetRightWhell(0,speed - 10);
//			if(Gray555 == 0 || Gray444 == 0)
//			{
//				break;
//			}
//		}
//	}	
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_L3_Turn
//*	功能说明: 灰度左转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/

//void Gray_L3_Turn(u8 speed)
//{
//	u8 a = 0;
//	while(1)
//	{
//		flag_line = 1;
//		if(a == 0)
//		{
//			SetLeftWhell(0,speed/2); SetRightWhell(0,speed);
//			delay_ms(150);
//			a ++;
//		}
//		else
//		{
//			SetLeftWhell(0,speed); SetRightWhell(0,speed);
//			if(Gray55 == 0 || Gray66 == 0)
//			{
//				break;
//			}
//		}

//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_L2_Turn
//*	功能说明: 灰度左转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/

//void Gray_L2_Turn(u8 speed)
//{
//	while(1)
//	{
//		SetLeftWhell(1,speed); SetRightWhell(0,speed);//原40
//		if(Gray88 == 0)
//		{
//			break;
//		}
//	}
//	while(1)
//	{
//		SetLeftWhell(1,speed - 10); SetRightWhell(0,speed - 10);
//		if(Gray55 == 0 || Gray44 == 0)
//		{
//			break;
//		}
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_L4_Turn
//*	功能说明: 灰度左转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/

//void Gray_L4_Turn(u8 speed)
//{
//	u8 a = 0;
//	while(1)
//	{
//		flag_line = 1;
//		if(a == 0)
//		{
//			SetLeftWhell(0,speed/2); SetRightWhell(0,speed);
//			delay_ms(150);
//			a ++;
//		}
//		else
//		{
//			SetLeftWhell(0,speed); SetRightWhell(0,speed);
//			if(Gray55 == 0 || Gray66 == 0)
//			{
//				break;
//			}
//		}

//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_L70_Turn
//*	功能说明: 灰度左转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/

//void Gray_L70_Turn(u8 speed)
//{
//	while(1)
//	{
//		Set_Motor_1(-speed,speed);
//		if(Gray88 == 0 || Gray11 == 0)
//		{
//			break;
//		}
//	}
//	while(1)
//	{
//		Set_Motor_1(-speed + 20,speed - 20);
//		if(Gray66 == 0 || Gray33 == 0)
//		{
//			break;
//		}
//	}
//	while(1)
//	{
//		Set_Motor_1(-speed + 40,speed - 40);
//		if(Gray55 == 0 || Gray44 == 0)
//		{
//			break;
//		}
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_R37_Turn
//*	功能说明: 灰度右转弯，数字代表转的角度
//*	形    参: 无
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_R37_Turn()
//{
//	while(1)
//	{
//		if(Gray_Count() == 0)
//		{
//			delay_ms(10);
//			if(Gray_Count() == 0)
//			break;
//		}
//	}
//	Set_Motor_1(-10,-10);
//	delay_ms(50);
//	Set_Motor_1(50,-50);
//	delay_ms(50);
//	while(1)
//	{
//		Set_Motor_1(50,-50);
//		if(Gray55 == 0 && Gray66 == 0)
//		{		
//			delay_ms(10);
//			if(Gray55 == 0 && Gray66 == 0)
//			break;
//		}
//	}
//}
///*
//*********************************************************************************************************
//*	函 数 名: Gray_R_Turn
//*	功能说明: 灰度右转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/

//void Gray_R_Turn(u8 speed,int angle)
//{
//	while(1)
//	{
//		float a;
//		a = Get_Angle(3);
//		SetLeftWhell(1,speed); SetRightWhell(1,speed);
//		flag_line = 1;
//		
////		if(a < angle + (float)2)//350     
////		{
////			if(a < angle - (float)4)
////			{
////				SetLeftWhell(1,speed); SetRightWhell(1,speed);
////			}
////			if(a > angle + (float)4)
////			{
////				SetLeftWhell(0,speed); SetRightWhell(0,speed);
////			}
//		if((angle - (float)2 < a) && (a < angle + (float)2))
//		{
//			break;
//		}	
//	}
//}


///*
//*********************************************************************************************************
//*	函 数 名: Gray_R1_Turn
//*	功能说明: 灰度右转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_R1_Turn(u8 speed,int angle)
//{
//	int ang = Get_Angle(3);
//	while(1)
//	{
//		SetLeftWhell(0,speed); SetRightWhell(1,speed);
//		flag_line = 1;
//		if((angle-2 < ang - Get_Angle(3)) && (Get_Angle(3) < angle+2))
//		{
//			break;
//		}
//	}
//}


///*
//*********************************************************************************************************
//*	函 数 名: Gray_R2_Turn
//*	功能说明: 灰度右转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_R2_Turn(u8 speed,int angle)
//{
//	while(1)
//	{
//		SetLeftWhell(0,speed); SetRightWhell(1,speed);
//		if((angle-3 < Get_Angle(3)) && (Get_Angle(3) < angle+3))
//		{
//			break;
//		}
//	}
//}


///*
//*********************************************************************************************************
//*	函 数 名: Gray_R3_Turn
//*	功能说明: 灰度右转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_R3_Turn(u8 speed)
//{
//	if(DIR == 0)
//	{
//		while(1)
//		{
//			SetLeftWhell(0,speed ); SetRightWhell(1,speed);//原40
//			if(Gray88 == 0 || Gray11 == 0)
//			{
//				break;
//			}
//		}
//		while(1)
//		{
//			SetLeftWhell(0,speed - 10); SetRightWhell(1,speed - 10);
//			if(Gray55 == 0 || Gray44 == 0)
//			{
//				break;
//			}
//		}
//	}else
//	{
//		while(1)
//		{
//			SetLeftWhell(0,speed ); SetRightWhell(1,speed);//原40
//			if(Gray888 == 0 || Gray111 == 0)
//			{
//				break;
//			}
//		}
//		while(1)
//		{
//			SetLeftWhell(0,speed - 10); SetRightWhell(1,speed - 10);
//			if(Gray555 == 0 || Gray444 == 0)
//			{
//				break;
//			}
//		}
//	}
//	
//}


///*
//*********************************************************************************************************
//*	函 数 名: Gray_R4_Turn
//*	功能说明: 灰度右转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_R4_Turn(u8 speed)
//{	
//	if(DIR == 0)
//	{
//		while(1)
//		{
//			SetLeftWhell(0,speed / 2); SetRightWhell(1,speed);//原40
//			if(Gray88 == 0 || Gray11 == 0)
//			{
//				break;
//			}
//		}
//		while(1)
//		{
//			SetLeftWhell(0,speed - 10); SetRightWhell(1,speed - 10);
//			if(Gray55 == 0 || Gray44 == 0)
//			{
//				break;
//			}
//		}
//	}
//	else
//	{
//		while(1)
//		{
//			SetLeftWhell(0,speed ); SetRightWhell(1,speed / 2);//原40
//			if(Gray888 == 0 || Gray111 == 0)
//			{
//				break;
//			}
//		}
//		while(1)
//		{
//			SetLeftWhell(0,speed - 10); SetRightWhell(1,speed - 10);
//			if(Gray555 == 0 || Gray444 == 0)
//			{
//				break;
//			}
//		}
//	}
//}


///*
//*********************************************************************************************************
//*	函 数 名: Gray_R50_Turn
//*	功能说明: 前灰度右转弯程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_R50_Turn(u8 speed)
//{
//	while(1)
//	{
//		Set_Motor_1(speed,-speed);
//		if(Gray88 == 0 || Gray11 == 0)
//		{	
//			break;
//		}
//	}	
//	while(1)
//	{
//		Set_Motor_1(speed - 20,-speed + 20);
//		if(Gray66 == 0 || Gray33 == 0)
//		{	
//			break;
//		}
//	}
//	while(1)
//	{
//		Set_Motor_1(speed - 40,-speed + 40);
//		if(Gray44 == 0 || Gray55 == 0)
//		{	
//			break;
//		}
//	}
//}


///*
//*********************************************************************************************************
//*	函 数 名: Gray_More90_R_Turn
//*	功能说明: 前灰度超过90度灰度直线右转
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_More90_R_Turn(u8 speed)
//{
//	while(1)
//	{
//		SetLeftWhell(0,speed); SetRightWhell(1,speed);//原40
//		if(Gray77 == 0 || Gray22 == 0)
//		{	
//			break;
//		}
//	}	
//	while(1)
//	{
//		SetLeftWhell(0,speed - 10); SetRightWhell(1,speed - 10);
//		if(Gray55 == 0 || Gray44 == 0)
//		{	
//			break;
//		}
//	}
//}


/////*
////*********************************************************************************************************
////*	函 数 名: Gray_B_Turn
////*	功能说明: 平台上调头
////*	形    参: speed控制速度
////*	返 回 值: 无
////*********************************************************************************************************
////*/

////void Gray_B_Turn(u8 speed,int angle)
////{
////	int a = Get_Angle(3);
////	int b = (a + angle + 360) % 360;
//////	int c = (a - 50 + angle + 360) % 360;
////	int c = b  / 2;
////	while(1)
////	{
////		SetLeftWhell(0,55); SetRightWhell(0,55);
////		if((c < Get_Angle(3)) && (Get_Angle(3) < c + 5))
////		{ 
////			break;
////		}
////	}
////	while(1)
////	{
////		SetLeftWhell(0,25); SetRightWhell(0,25);
////		if((b - 3 < Get_Angle(3)) && (Get_Angle(3) < b + 3))
////		{
////			CarAdvance(0);
////			delay_ms(250);
////			break;
////		}
////	}
////	if(Get_Angle(3) >= b + 3)
////	{
////		while(1)
////		{
////			SetLeftWhell(1,28); SetRightWhell(1,30);
////			if((b - 2 < Get_Angle(3)) && (Get_Angle(3) < b + 2))
////			{
////				break;
////			}
////		}
////	}
////	CarAdvance(0);
////}

///*
//*********************************************************************************************************
//*	函 数 名: Gray__Turn
//*	功能说明: 灰度调头程序
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void Gray_B1_Turn(u8 speed,int angle)
//{
//	/*
//	u8 a = 0;
//	flag_line = 1;
//	while(1)
//	{
//		if(a == 0)
//		{
//			SetLeftWhell(0,speed + 15); SetRightWhell(0,speed);
//			delay_ms(300);
//			a ++;
//		}else
//		{
//			SetLeftWhell(0,speed+15); SetRightWhell(0,speed);
//			if(Gray55 == 0 || Gray44 == 0)
//			{
//				flag_gray = 0;
//				break;
//			}
//		}	
//	}
//	*/
//	
//	int a = Get_Angle(3);
//	int b = (a + angle + 360) % 360;
//	int c = (a - 50 + angle + 360) % 360;
//	while(1)
//	{
//		SetLeftWhell(0,58); SetRightWhell(0,55);
//		if((c < Get_Angle(3)) && (Get_Angle(3) < c + 7))
//		{ 
//			break;
//		}
//	}
//	while(1)
//	{
//		SetLeftWhell(0,35); SetRightWhell(0,30);
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
//			SetLeftWhell(1,30); SetRightWhell(1,35);
//			if((b - 2 < Get_Angle(3)) && (Get_Angle(3) < b + 2))
//			{
//				break;
//			}
//		}
//	}
//	CarAdvance(0);
//}



///*
//*********************************************************************************************************
//*	函 数 名: Detect_obstacles_front
//*	功能说明: 检测前方是否障碍物
//*	形    参: speed控制速度
//*	返 回 值: 无
//*********************************************************************************************************
//*/
// void Detect_obstacles_front()
//{
//	if(flag_obstacles == 0)
//	{
//	 if(Infrared_DIO2 == 0)
//	 {
//			flag_obstacles_front++;
//			flag_obstacles = 1;
//	 }
// }
//}

///*
//*********************************************************************************************************
//*	函 数 名: Gray_scanf
//*	功能说明: 小灰度扫描障碍物
//*	形    参: 无
//*	返 回 值: 无
//*********************************************************************************************************
//*/

//void Gray_scanf()
//{
//	if(flag_gray == 0)
//	{
//		if(L_DIO3 == 0 || R_DIO4 == 1)
//		{
//			flag_turn++;
//			flag_gray = 1;
//		}
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: scanf__obstacles
//*	功能说明: 扫描障碍物
//*	形    参: 无
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void scanf_obstacles(void)
//{
//	G_Scan(site);
//}

///*
//*********************************************************************************************************
//*	函 数 名: star_gray
//*	功能说明: 开启扫描障碍物
//*	形    参: 无
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void star_gray()
//{
//	if(Gray11 == 0 || Gray88 == 0)
//	{
//		flag_gray = 0;
//	}
//}

///*
//*********************************************************************************************************
//*	函 数 名: back_scenic
//*	功能说明: 碰到景点返回
//*	形    参: 无
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void back_scenic()
//{
//	DIR = !DIR;
//}
//void stop1()
//{
//	
//	while(1)
//	{
//	Set_Motor_1(0,0);
//	}
//}

