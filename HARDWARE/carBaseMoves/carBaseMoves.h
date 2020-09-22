#ifndef _carbasemoves_h
#define _carbasemoves_h


/***********************引用文件*************************/
#include "sys.h"
#include "delay.h"
#include "demo_motor.h"

/***********************宏定义**************************/

#define CAR_FLAT 		((ANGLE_X<=6)||(ANGLE_X>=354))
#define CAR_UP			((ANGLE_X>12)&&(ANGLE_X<=60))
#define CAR_DOWN		((ANGLE_X<=348)&&(ANGLE_X>=300))
#define	The_CAR_UP(num)			((ANGLE_X>num)&&(ANGLE_X<=80))
#define	The_CAR_FLAT(num)	((ANGLE_X<=num)||(ANGLE_X>=(360-num)))
#define	The_CAR_DOWN(num)		((ANGLE_X<=(360-num))&&(ANGLE_X>=300))

#define	The_CAR_LEFT(num)			((ANGLE_Y>num)&&(ANGLE_Y<=80))
#define	The_CAR_FLAT_Y(num)	((ANGLE_Y<=num)||(ANGLE_Y>=(360-num)))
#define	The_CAR_RIGHT(num)		((ANGLE_Y<=(360-num))&&(ANGLE_Y>=300))


#define ANGLE_X (Get_Angle(1))
#define ANGLE_Y (Get_Angle(2))
#define ANGLE_Z (Get_Angle(3))

/***********************函数声明************************/


void Turn_Node(s16 Angle,u16 LowNum,u16 LowTim,u32 InLength,s32 OutLength);

void Turn_Angle_Big(s32 goal_Angle);  //小车原地转向——大灰度做标志
void Turn_Angle_Small(s32 goal_Angle);//小车原地转向——小灰度做标志
void car_TurnToAngle(s32 goal_Angle); //小车原地转向至指定角度值
void car_TurnToAngle1(s32 goal_Angle);//小车原地转向至指定角度值
void car_TurnToAngle2(s32 goal_Angle);//小车原地转向至指定角度值


void car_turnAvgle(s16 angle);	//当前为止旋转一定角度（负数参数向左，正右）
void car_turnAvgle1(s16 angle);	//当前为止旋转一定角度（负数参数向左，正右）
void car_turnAvgle2(s16 angle);	//当前为止旋转一定角度（负数参数向左，正右）

void go_To_Angle(s16 angle);
void Green_Turn180(void);
void Corrective_Angle(s16 angle);
void turn_L90(s16 angle);
void turn_R90(s16 angle);

void WITE_DOWN(u8 x);
void WITE_UP(u8 x);
void WITE_FLAT(u8 x);

u8 car_wait_flat(u8 nature);		//等待...	水平
u8 car_wait_up(u8 nature);			//等待...	抬头
u8 car_wait_down(u8 nature);		//等待...	低头
u8 car_wait_length(u32 nature);		//等待	:	行驶距离

u8 FUNC_wait_length(void (*funcName)(),u32 nature);
u8 FUNC_wait_flat(void (*funcName)(),u8 nature);
u8 FUNC_wait_up(void (*funcName)(),u8 nature);
u8 FUNC_wait_down(void (*funcName)(),u8 nature);

u8 ture_Angle(u16 goal_Angle);	//判断当前角度正确性			   

void Set_Motor31(void);
void Set_Motor32(void);

#endif





