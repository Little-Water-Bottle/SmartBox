#ifndef DEMO_DIO
#define DEMO_DIO

#include "DIO.h"
#include "demo_motor.h"

#define Gray1		PFin(6) //数字输入8 GPIO9
#define Gray2		PFin(5) //数字输入7 GPIO8
#define Gray3		PFin(4) //数字输入6 GPIO7
#define Gray4		PFin(2) //数字输入5 GPIO6

#define Gray5		PEin(5) //数字输入4 GPIO2
#define Gray6		PEin(6) //数字输入3 GPIO3
#define Gray7		PFin(0) //数字输入2 GPIO4
#define Gray8		PFin(1) //数字输入1 GPIO5

#define Gray88		PEin(2) //数字输入88 GPIO1
#define Gray77		PEin(1) //数字输入77 GPIO16
#define Gray66		PBin(9) //数字输入66 GPIO15
#define Gray55		PBin(8) //数字输入55 GPIO14

#define Gray44		PBin(4) //数字输入44 GPIO10
#define Gray33		PBin(5) //数字输入33 GPIO11
#define Gray22		PBin(6) //数字输入22 GPIO12
#define Gray11		PBin(7) //数字输入11 GPIO13



#define Infrared_DIO1  PDin(11)//前红外DIO1，低电平有效；顺时针选中增大距离
#define Infrared_DIO2  PDin(7) //后红外DIO2，低电平有效
#define L_DIO3 PFin(7)//左小灰度DIO3，低电平有效；顺时针选中增大距离
#define R_DIO4 PFin(8)//右小灰度DIO4，低电平有效
#define queue PDin(2)

#define ETR1 PEin(0)//左红外
#define ETR2 PAin(5)//右红外
#define ETR3 PDin(2)
#define ETR4 PAin(12)

void Gray_Go(u8 speed);//测试用

void Run1(void);//第一条路线
void Run2(void);//第二条路线
void Run_wwt_1(void);

int Gray(int number);//判断灰度第几个灯亮
int Gray_Count(void);//灰度亮灯计数

void Gray_Run(u8 speed);    //(已修改)2018-10-6
void Gray_Run_1(u8 speed);
void Gray_Run15(void);  //灰度15直线速度，下山用
void Gray_Run20(void);  //灰度控制直线程序  用于从第一个高台下坡用，禁止改
void Gray_Run20_20(void);//用于从五个平台下坡用，勿改
void Gray_Run25(void);  //灰度25直线速度，下台用
void Gray_Run25gai(void);//灰度25直线速度，下高台用
void Gray_Run35(void);//灰度35直线速度，下高台用
void Gray_Run_gaotai(void);//只走灰度巡线其它情况不会影响，减速度，下高台用
void Gray_Run30(void);  //灰度30直线速度，过刀山用,禁止改
void Gray_Run30_1(void);
void Gray_Run40(void);  //灰度40直线速度
void Gray_Run40gai(void);//下高台用
void Gray_Run40TaiJie(void);//过平台
void Gray_Run50(void);  //灰度50直线速度
void Gray_Run60(void);  //灰度60直线速度
void Gray_Run70(void);  //灰度70直线速度
void Gray_Run80(void);  //灰度80直线速度
void Gray_Run_Taijie(void);  //灰度过台阶(taijie)
void Gray_Run_Taijie1(void);  //灰度过台阶(taijie)
void Gray_Run_Jiansuban(void);  //灰度过减速板(Jiansuban)
void Gray_Run_Taijie_Speed(int speed);  //灰度过台阶(taijie)，数字代表速度
void run_c(void);//转圈
	
void run_gray(u16 i,u8 speed);//只走灰度巡线其它不受影响
void Gray_Down(u16 i);		  //灰度30/0直线速度交替使用，下第二个高台用
void Gray_Down2(u16 i); //灰度50/0直线速度交替使用，过五层阶梯用
void Gray_Delay_Run15(u16 i);//只走灰度巡线其它情况不会影响，15速度
void Gray_Delay_Run15_0(u16 i);//只走灰度巡线其它情况不会影响，15速度与减速交替使用
void Gray_Delay_Run20(u16 i);//只走灰度巡线其它情况不会影响，20速度
void Gray_Delay_Run20_20(u16 i);//只走灰度巡线其它情况不会影响，20速度
int Gray_Delay_Run25(u16 i);//只走灰度巡线其它情况不会影响，25速度
int Gray_Delay_Run30(u16 i);//只走灰度巡线其它情况不会影响，30速度

int Gray_Delay_Run40(u16 i);//只走灰度巡线其它情况不会影响，40速度
int Gray_Delay_Run50(u16 i);//只走灰度巡线其它情况不会影响，50速度
int Gray_Delay_Run60(u16 i);//只走灰度巡线其它情况不会影响，60速度
int Gray_Delay_Run70(u16 i);//只走灰度巡线其它情况不会影响，70速度
int Gray_Delay_Run25gai(u16 i);//只走灰度巡线其它情况不会影响，25速度
int Gray_Delay_Run35(u16 i);//只走灰度巡线其它情况不会影响，35速度
int Gray_Delay_Run_Taijie(u16 i);//只走灰度巡线其它情况不会影响，过台阶(taijie)速度
int Gray_Delay_Run_Taijie1(u16 i);//只走灰度巡线其它情况不会影响，过台阶(taijie)速度
void Gray_Delay_Run_Taijie2(u16 i);  //灰度过台阶(taijie),匀速，减速结合
int Gray_Delay_Run_Jiansuban(u16 i);//只走灰度巡线其它情况不会影响，过减速板(Jiansuban)速度
int Gray_Delay_Run_C(u16 i);//只走灰度巡线其它情况不会影响，转圈速度
void Gray_Delay(void (*a)(),u16 ms);
void Speed_Delay(u16 i,u16 j,u16 ms);
void stop1(void);

void Gray_Run2(u8 speed);//灰度走曲线
void Gray_curve(u8 speed);//灰度走曲线
void Gray_Curve0(u8 speed);//前灰度走曲线
void Front_Gray_Curve_L50_Turn(u8 speed);//前灰度曲线左转（待验证）
void Gray_Climb(u8 speed);//灰度爬坡
void Gray_Run4(u8 speed);//过减速带

void Gray_L37_Turn(void);//灰度左转弯，数字代表转的角度
void Gray_L_Turn(u8 speed,int angle);//灰度左转弯
void Gray_L1_Turn(u8 speed);//灰度左转弯
void Gray_L2_Turn(u8 speed);//灰度左转弯
void Gray_L3_Turn(u8 speed);//灰度左转弯
void Gray_L70_Turn(u8 speed);//灰度直线左转

void Gray_R37_Turn(void);//灰度右转弯，数字代表转的角度
void Gray_R_Turn(u8 speed,int angle);//灰度右转弯
void Gray_R1_Turn(u8 speed,int angle);//灰度右转弯
void Gray_R2_Turn(u8 speed,int angle);//灰度右转弯
void Gray_R3_Turn(u8 speed);//灰度右转弯
void Gray_R4_Turn(u8 speed);//灰度右转弯
void Gray_R50_Turn(u8 speed);//前灰度直线右转
void Gray_More90_R_Turn(u8 speed);//前灰度超过90度灰度直线右转（待验证）

void Gray_B1_Turn(u8 speed,int angle);//绿毯转向

void Speed_Down(void);//减速方法
void Brake_Stop(void);//刹车方法


void Detect_obstacles_front(void);//判断前方是否有障碍物
void Gray_scanf(void);//两个小灰度扫描

void star_gray(void); //开启扫描障碍物
void scanf_obstacles(void);//扫描障碍物
void back_scenic(void);//碰到景点返回

int gray_light_amount(void);
void infrared_35(void);
void zhuanwan_big_left(int time);
void zhuanwan_big_right(int time);

#endif

