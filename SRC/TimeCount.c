//时钟计时函数
//transport 在定时器中断中以两秒加一

#include "sys.h"
#include "TimeCount.h"
#include "lcd.h"
#include "counterinit.h"

//计时器初值为零
extern int transport;
extern int shi;	//时
extern int fen;	//分
extern int miao;	//秒

u8 s_shi;
u8 s_fen;
u8 s_miao;

//时间计数
void TimerCountPrint(void) 
{
	

	
	//绘制 秒 固定栏
//	LCD_Fill(0,0,lcddev.width,40,BLUE);
//	Gui_StrCenter(0,2,WHITE,BLUE,miao,20,1);
//	LCD_ShowNum2(10,20,60,2,32);
//	GUI_DrawNum32(10,20,lcddev.width,lcddev.height,60+" ",1);
//	GUI_DrawFont32(10,20,lcddev.width,lcddev.height,"字体测试",1);
//	Show_Str(10,70,lcddev.width,lcddev.height,"字体测试智能药箱",32,1);
//	Show_Str(10,120,lcddev.width,lcddev.height,60+"",32,1);
//	LCD_Fill(0,0,lcddev.width,80,BLUE);
//	LCD_ShowNum(0,40,60,2,32);

////	LCD_ShowString(10,200,lcddev.width,lcddev.height,32,"智能药箱");
//	while(1);
	
	
	miao = transport;
	
	LCD_ShowNum(3*lcddev.width/4,60,miao,2,16);
	if(miao == 60)
	{
		fen++;
		miao = 0;
		//绘制 分 固定栏
//		LCD_Fill(0,0,lcddev.width,80,BLUE);
		LCD_ShowNum(2*lcddev.width/4,60,fen,2,16);
//		Gui_StrCenter(0,2,WHITE,BLUE,fen,20,1);
		
	}
	if(fen == 60) 
	{
		shi++;
		fen = 0;
		//绘制 时 固定栏
//		LCD_Fill(0,0,lcddev.width,120,BLUE);
		LCD_ShowNum(1*lcddev.width/4,60,shi,2,16);
//		Gui_StrCenter(0,2,WHITE,BLUE,shi,20,1);
	}
	if(shi == 24) 
	{
		shi  = 0;
		fen  = 0;
		miao = 0;
	}
	if(miao%10==0)
	{
//		LED0=!LED0;
//		LED1=!LED1;
	}


}

void timeInit(void)
{
	//绘制 秒 固定栏
	LCD_Fill(0,0,lcddev.width,40,BLUE);
	Gui_StrCenter(0,2,WHITE,BLUE,0,20,1);
//	LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
	
	//绘制 分 固定栏
	LCD_Fill(0,40,lcddev.width,80,GREEN);
	Gui_StrCenter(0,42,WHITE,GREEN,0,20,1);
	
	//绘制 时 固定栏
	LCD_Fill(0,80,lcddev.width,120,BLUE);
	Gui_StrCenter(0,82,WHITE,BLUE,0,20,1);
	
}


