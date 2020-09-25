#ifndef DEMO_DIO_HOU
#define DEMO_DIO_HOU

#include "DIO.h"
#include "demo_motor.h"




//void Gray_Run(u8 speed);    //(已修改)2018-10-6
//void Gray_Run_1(u8 speed);
//void Gray_Run15(void);  //灰度15直线速度，下山用
//void Gray_Run20(void);  //灰度控制直线程序  用于从第一个高台下坡用，禁止改
void Gray_Run20_20_hou(void);//用于从五个平台下坡用，勿改
//void Gray_Run25(void);  //灰度25直线速度，下台用
//void Gray_Run25gai(void);//灰度25直线速度，下高台用
//void Gray_Run35(void);//灰度35直线速度，下高台用
//void Gray_Run_gaotai(void);//只走灰度巡线其它情况不会影响，减速度，下高台用
void Gray_Run30_hou(void);  //灰度30直线速度，过刀山用,禁止改
//void Gray_Run30_1(void);
void Gray_Run40_hou(void);  //灰度40直线速度
//void Gray_Run40gai(void);//下高台用
//void Gray_Run40TaiJie(void);//过平台
void Gray_Run50_hou(void);  //灰度50直线速度
void Gray_Run60_hou(void);  //灰度60直线速度
void Gray_Run70_hou(void);  //灰度70直线速度
//void Gray_Run80(void);  //灰度80直线速度
//void Gray_Run_Taijie(void);  //灰度过台阶(taijie)
//void Gray_Run_Taijie1(void);  //灰度过台阶(taijie)
//void Gray_Run_Jiansuban(void);  //灰度过减速板(Jiansuban)
//void Gray_Run_Taijie_Speed(int speed);  //灰度过台阶(taijie)，数字代表速度
//void run_c(void);//转圈
//	
//void run_gray(u16 i,u8 speed);//只走灰度巡线其它不受影响
//void Gray_Down(u16 i);		  //灰度30/0直线速度交替使用，下第二个高台用
//void Gray_Down2(u16 i); //灰度50/0直线速度交替使用，过五层阶梯用
//void Gray_Delay_Run15(u16 i);//只走灰度巡线其它情况不会影响，15速度
//void Gray_Delay_Run15_0(u16 i);//只走灰度巡线其它情况不会影响，15速度与减速交替使用
//void Gray_Delay_Run20(u16 i);//只走灰度巡线其它情况不会影响，20速度
void Gray_Delay_Run20_20_hou(u16 i);//只走灰度巡线其它情况不会影响，20速度
//int Gray_Delay_Run25(u16 i);//只走灰度巡线其它情况不会影响，25速度
int Gray_Delay_Run30_hou(u16 i);//只走灰度巡线其它情况不会影响，30速度

int Gray_Delay_Run40_hou(u16 i);//只走灰度巡线其它情况不会影响，40速度
int Gray_Delay_Run50_hou(u16 i);//只走灰度巡线其它情况不会影响，50速度
int Gray_Delay_Run60_hou(u16 i);//只走灰度巡线其它情况不会影响，60速度
int Gray_Delay_Run70_hou(u16 i);//只走灰度巡线其它情况不会影响，70速度
//int Gray_Delay_Run25gai(u16 i);//只走灰度巡线其它情况不会影响，25速度
//int Gray_Delay_Run35(u16 i);//只走灰度巡线其它情况不会影响，35速度
//int Gray_Delay_Run_Taijie(u16 i);//只走灰度巡线其它情况不会影响，过台阶(taijie)速度
//int Gray_Delay_Run_Taijie1(u16 i);//只走灰度巡线其它情况不会影响，过台阶(taijie)速度
//void Gray_Delay_Run_Taijie2(u16 i);  //灰度过台阶(taijie),匀速，减速结合
//int Gray_Delay_Run_Jiansuban(u16 i);//只走灰度巡线其它情况不会影响，过减速板(Jiansuban)速度
//int Gray_Delay_Run_C(u16 i);//只走灰度巡线其它情况不会影响，转圈速度
//void Gray_Delay(void (*a)(),u16 ms);
//void Speed_Delay(u16 i,u16 j,u16 ms);
//void stop1(void);

#endif

