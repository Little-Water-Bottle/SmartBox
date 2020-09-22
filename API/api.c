#include "api.h" 
#include "lcd.h"
#include "demo_dio.h"
#include "wt61.h"
#include "dio.h"


extern int flag_turn;
extern int flag_obstacles_front;
extern int set_speed;
extern struct pid1 	pid;
int site[8] = {0,0,0,0,0,0,0,0};
extern int az;
int b;
int c,d,e;

/*
*********************************************************************************************************
*	函 数 名: API_showLCD()
*	功能说明: lcd显示信息
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void API_showLCD()
{
	int i = 0;
	LCD_ShowString(30,25,200,16,16,"Flag_turn:");
	LCD_ShowxNum(120,25,flag_turn,4,16,0x80);
	
	LCD_ShowString(0,50,200,16,16,"Flag_obstacles_front:");
	LCD_ShowxNum(200,50,flag_obstacles_front,4,16,0x80);
	
	b = Get_Angle(3);	
	LCD_ShowString(30,75,200,16,16,"Angle:");
	LCD_ShowxNum(120,75,b,3,16,0x80);
	
	LCD_ShowString(30,100,200,16,16,"Speed:");
	LCD_ShowxNum(120,100,set_speed,3,16,0x80);
	
	c = Get_Angle(1);
	LCD_ShowString(30,125,200,16,16,"H_B_Angle:");
	LCD_ShowxNum(120,125,c,3,16,0x80);
	
	d = Get_Angle(2);
	LCD_ShowString(30,150,200,16,16,"ce_Angle:");
	LCD_ShowxNum(120,150,d,3,16,0x80);
	
	
//	int *b = G_Scan(site);
	for(i =0;i < 8; i ++)
	{
		LCD_ShowxNum(0 + (i * 20),250,site[i],1,16,0x80);
	}
	
	
}

/*
*********************************************************************************************************
*	函 数 名: G_Scan()
*	功能说明: 灰度扫描返回数组
*	形    参: 无
*	返 回 值: 八位数组
*********************************************************************************************************
*/

int *G_Scan(int site[])
{
	if(Gray1 == 0)
	{
		site[0] = 1;
	}
	if(Gray2 == 0)
	{
		site[1] = 1;
	}
	if(Gray3 == 0)
	{
		site[2] = 1;
	}
	if(Gray4 == 0)
	{
		site[3] = 1;
	}
	if(Gray5 == 0)
	{
		site[4] = 1;
	}
	if(Gray6 == 0)
	{
		site[5] = 1;
	}
	if(Gray7 == 0)
	{
		site[6] = 1;
	}
	if(Gray8 == 0)
	{
		site[7] = 1;
	}
	
	return site;
	
}
