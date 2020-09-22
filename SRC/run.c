/*
*********************************************************************************************************
*本文件是用来写跑图的代码。
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
*规划路线：1坤-3艮-4离-02冰岛-8乾-05日喀则-06檀香山-07金字塔-5巽-1坤到家
分数————485分
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*第一段路线：1坤-3艮-4离-02冰岛
*********************************************************************************************************
*/
void Run2(void)
{	

	MoveHead();//摇头
//	MoveHand();//摆手
	
//	while(1)
//	{
//		if(ETR1 == 0)
//		{
//			Set_Motor(0,0);
//		}
//		else
//		{
//			Gray_Run25();//灰度走直线,数字代表速度
//			break;
//		}
//	}
	
	while(1)//下坡
	{
		Gray_Delay_Run25(800);//灰度走直线,数字代表速度(括号里代表时间)
		break;
	}
	
	while(1)//出门左转
	{
		Gray_Run40();//灰度走直线,数字代表速度
		if(Gray2 == 0)
		{	
			Set_Motor(0,0);
			delay_ms(100);
			break;
		}
	}

	zhuanwan_big_left(100);	//转弯
	
	Gray_Delay_Run50(250);	//直线
	
	while(1)//准备过减速板
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
	
	Gray_Delay_Run_Jiansuban(1000);//在减速板上待的时间，注意调整
	
	while(1)//下减速板
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

	while(1)//右转
	{
		Gray_Run40();  //灰度过减速板(Jiansuban)
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
*第一段路线：3艮-4离
*/
	
	Gray_Delay_Run50(200);//灰度走直线,数字代表速度(括号里代表时间)		
	Gray_Delay_Run60(200);//灰度走直线,数字代表速度(括号里代表时间)
	
	while(1)//缓冲,前往3艮
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
	
	Gray_Delay_Run70(600);//灰度走直线,数字代表速度(括号里代表时间)
	Gray_Delay_Run50(300);//灰度走直线,数字代表速度(括号里代表时间)
	
	
	while(1)//到达3艮平台
	{
		Gray_Run40();//灰度走直线,数字代表速度
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

	while(1)//停在3艮，摆手调头下坡
	{
		Set_Motor(25,25);//后退
		delay_ms(150);
		Set_Motor(0,0);
		delay_ms(100);
		Set_Motor(-25,-25);//后退
		delay_ms(140);
		Set_Motor(0,0);
		delay_ms(100);     //后退缓冲
		Turn_Angle_Big(90);//根据场地合适选择六轴转向函数
		delay_ms(50);
		MoveHand();
		Turn_Angle_Big(0);//根据场地合适选择六轴转向函数
		delay_ms(50);
		Turn_Angle_Big(-90);//根据场地合适选择六轴转向函数
		delay_ms(50);
		MoveHand();
		Turn_Angle_Big(-180);
		delay_ms(50);
		break;
	}
	
	Gray_Delay_Run25(500);
	
	while(1)//前往01梵蒂冈
	{
		Gray_Delay_Run40(300);//灰度走直线,数字代表速度(括号里代表时间)
		Gray_Delay_Run50(1300);//灰度走直线,数字代表速度(括号里代表时间)
		break;
	}
	
	while(1)//左转
	{
		Gray_Run40();//灰度走直线,数字代表速度
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
	
	while(1)//前往01梵蒂冈
	{
		Gray_Delay_Run50(300);//灰度走直线,数字代表速度(括号里代表时间)
		Gray_Delay_Run70(600);//灰度走直线,数字代表速度(括号里代表时间)
		break;
	}
	
	while(1)//准备到达01梵蒂冈
	{
		Gray_Delay_Run50(200);
		while(1)
		{
			Gray_Run40();//灰度走直线,数字代表速度
			if(Infrared_DIO1 == 0)
			{
				Set_Motor(0,0);//缓冲
				delay_ms(100);
				Set_Motor(-20,-20);//回退
				delay_ms(150);
				break;
			}
		}
		break;
	}
	zhuanwan_big_left(300);
	
	while(1)//离开01梵蒂冈
	{
		Gray_Delay_Run40(300);//灰度走直线,数字代表速度(括号里代表时间)
		Gray_Delay_Run60(1000);//灰度走直线,数字代表速度(括号里代表时间)
		break;
	}
	
	while(1)//左转
	{
		Gray_Run40();//灰度走直线,数字代表速度
		if(Gray11 == 0)
		{	
			Set_Motor(0,0);//缓冲
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
*第一段路线：4离-02冰岛
*/
	while(1)//前往4离平台
	{
		Gray_Delay_Run50(300);//灰度走直线,数字代表速度(括号里代表时间)
		Gray_Delay_Run70(1000);//灰度走直线,数字代表速度(括号里代表时间)
		Gray_Delay_Run60(600);//灰度走直线,数字代表速度(括号里代表时间)
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
		
	while(1)//前往02冰岛
	{
		Gray_Delay_Run50(800);//灰度走直线,数字代表速度(括号里代表时间)
		break;
	}
	
	while(1)//掉头，离开02冰岛
	{
		Gray_Run40();//灰度走直线,数字代表速度
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
	
	Gray_Delay_Run50(500);	//直线后退
	
	while(1)//转弯条件
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
	
	while(1)//到达4离
	{
	  Gray_Run40TaiJie();//灰度走直线,数字代表速度
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
	
	while(1)//停在4离，摆手弯腰调头下坡
	{
//		Set_Motor(25,25);
//		delay_ms(280);
//		Set_Motor(0,0);
//		delay_ms(150);
//		MoveHand();//摆手
//		LowerHead();//弯腰
		Set_Motor(-25,-25);//后退缓冲
		delay_ms(150);
		Set_Motor(0,0);
		delay_ms(150);     //后退缓冲
		Turn_Angle_Big(270);//根据场地合适选择六轴转向函数
		delay_ms(50);
		MoveHand();
		Turn_Angle_Big(180);//根据场地合适选择六轴转向函数
		delay_ms(50);
		Turn_Angle_Big(90);//根据场地合适选择六轴转向函数
		delay_ms(50);
		MoveHand();
		Turn_Angle_Big(0);//根据场地合适选择六轴转向函数
		delay_ms(50);
		break;
	}
	
	Gray_Delay_Run20_20(400);
	
	while(1)//下4离
	{
		Gray_Delay_Run30(200);//灰度走直线,数字代表速度(括号里代表时间)
		Gray_Delay_Run50(700);//灰度走直线,数字代表速度(括号里代表时间)
		break;
	}
	
	while(1)//右转
	{
		Gray_Run40();//灰度走直线,数字代表速度
		if(Gray1 == 0)
		{	
			delay_ms(150);
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_left(200);	//转弯
		
/*
*********************************************************************************************************
*第二段路线：02冰岛-（限高栏杆）-（5层阶梯）-减速板-7兑
*********************************************************************************************************
*/

	while(1)//直线
	{
		Gray_Delay_Run40(200);//灰度走直线,数字代表速度(括号里代表时间)
		Gray_Delay_Run60(800);//灰度走直线,数字代表速度(括号里代表时间)
		break;
	}
	
	while(1)//弧度路口
	{
		Gray_Run40();//灰度走直线,数字代表速度
		if(Gray_Count() == 0)
		{
			Set_Motor(10,10);
			delay_ms(100);
			break;
		}
	}
	zhuanwan_big_right(100);
	
	while(1)//弧度路口
	{
		Gray_Run30();//灰度走直线,数字代表速度
		if(Gray_Count() == 0)
		{
			Set_Motor(30,30);
			delay_ms(100);
			break;
		}
	}
	zhuanwan_big_right(100);
	
	while(1)//直线
	{
		Gray_Delay_Run30(300);
		Gray_Delay_Run60(600);
		break;
	}
	
	while(1)//左转
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
*第二段路线：（限高栏杆）-（5层阶梯）
*/
	while(1)//经过限高栏杆
	{
		Gray_Delay_Run20(200);
		Gray_Delay_Run50(200);
		Gray_Delay_Run60(700);//灰度走直线,数字代表速度(括号里代表时间)
		break;
	}
	
	while(1)//左转
	{
		Gray_Run50();
		if(Gray8 == 0)
		{	
			delay_ms(50);
			break;
		}
	}
	
	while(1)//左转
	{
		Gray_Run40();//灰度走直线,数字代表速度
		if(gray_light_amount()==8)
		{	
			Set_Motor(-10,-10);
			delay_ms(100);
			Set_Motor(40,-40);
			delay_ms(100);
			break;
		}
	}
	
	while(1)//退出左转
	{
		Set_Motor(30,-30);
		if(Gray6 == 0)
		{		
			delay_ms(10);
			if(Gray6 == 0)
			break;
		}
	}
	
	while(1)//直走
	{
		Gray_Delay_Run50(400);//灰度走直线,数字代表速度(括号里代表时间)
		break;
	}	

	while(1)//右转
	{
		Gray_Run40();//灰度走直线,数字代表速度
		if(Gray8 == 0)
		{	
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_right(200);	//转弯
	
	while(1)//直走
	{
		Gray_Delay_Run50(300);//灰度走直线,数字代表速度(括号里代表时间)
		Gray_Delay_Run60(300);//灰度走直线,数字代表速度(括号里代表时间)
		break;
	}
	
	while(1)	//过五层阶梯
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
	
	Gray_Delay_Run60(400);//灰度走直线,数字代表速度(括号里代表时间)
	Gray_Delay_Run50(200);//灰度走直线,数字代表速度(括号里代表时间)
	
	while(1)//准备左转
	{
		Gray_Run40();//灰度走直线,数字代表速度
		if(Gray1 == 0)
		{	
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_left(200);	//转弯
	Gray_Delay_Run50(200);	//防误判
	
	while(1)//左转
	{
		Gray_Run40();//灰度走直线,数字代表速度
		if(Gray1 == 0)
		{	
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_left(200);//转弯
	
	while(1)	//过减速板
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
	
	while(1)	//上高台
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
	
	while(1)//高台操作
	{
		Set_Motor(-25,-25);//后退缓冲
		delay_ms(100);
		Set_Motor(0,0);
		delay_ms(100);     //后退缓冲
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
	
	Gray_Delay_Run30(400);//下高台
	
	while(1)//下高台
	{
		Gray_Run30();
		if(ETR1 == 0 && ETR2 == 0)
			break;
	}	

	while(1)//过减速板
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
	
	while(1)//左转
	{
		Gray_Run40();//灰度走直线,数字代表速度
		if(Gray8 == 0)
		{	
			
			Set_Motor(0,0);
			delay_ms(150);
			break;
		}
	}
	
	zhuanwan_big_right(200);
	
	while(1)//左转
	{
		Gray_Run40();//灰度走直线,数字代表速度
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
	
	while(1)//上高台
	{
		Gray_Run50();
		if(ETR1 == 1 && ETR2 == 1)
			break;
	}
	while(1)//上高台
	{
		Gray_Run50();//灰度走直线,数字代表速度
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
	while(1)//上高台
	{
		Gray_Run50();//灰度走直线,数字代表速度
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
	
	while(1)//到达最高台8乾，摆手调头下坡
	{
//		GetUp();//起身程序
//		Set_Motor(25,25);
//		delay_ms(180);
//		Set_Motor(0,0);
//		delay_ms(150);
//		MoveHand();//摆手
//		LowerHead();//弯腰
		Set_Motor(-25,-25);//后退缓冲
		delay_ms(100);
		Set_Motor(0,0);
		delay_ms(100);     //后退缓冲
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
//		Turn_Angle_Big(270);//反向180;
//		delay_ms(200);  
//		Turn_Angle_Big(184);
//		Set_Motor(0,0);
//		delay_ms(100);     //缓冲
//		LowerHead();//往后弯腰程序
		break;
	}
	Set_Motor(25,25);
	delay_ms(150);
	Gray_Down(200);//根据场地更改括号里面的时间
	while(1)
	{
		Gray_Run30();
		if(Gray_Count() == 0)
		break;
	}
	
	Gray_Down(200);//根据场地更改括号里面的时间
	
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
	
//判断是否到达圆弧区
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
	
////沿着圆弧运动
//	while(1)
//	{
//		run_c();
//		if(ETR1 == 1 && ETR2 == 1)
//			break;
//	}
//	
////到达跷跷板，上跷跷板
//	while(1)
//	{
//		Set_Motor(5,30);
//		delay_ms(100);
//		break;
//	}
//	
////在跷跷板上行走
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
////沿弧行走
//	while(1)
//	{
//		run_c();
//		delay_ms(400);
//		break;
//	}
//	
////判断是否到达转弯处
//	while(1)
//	{
//		run_c();
//		if(Gray1||Gray2	== 0)
//		{
//			break;
//		}
//	}
//	
//	//转弯
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
//		Set_Motor(-25,-25);//后退缓冲
//		delay_ms(100);
//		Set_Motor(0,0);
//		delay_ms(100);     //后退缓冲
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
		Set_Motor(-25,-25);//后退缓冲
		delay_ms(100);
		Set_Motor(0,0);
		delay_ms(100);     //后退缓冲
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
		Turn_Angle_Big(90);//根据场地合适选择六轴转向函数
		delay_ms(50);
		Turn_Angle_Big(0);//根据场地合适选择六轴转向函数
		delay_ms(50);
		break;
	}
	while(1){Set_Motor(0,0);};
}






