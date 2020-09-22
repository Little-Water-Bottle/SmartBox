#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

void TIM5_PWM_Init(u32 arr,u32 psc);
void TIM8_PWM_Init(u32 arr,u32 psc);


void Angle_Adjust1(int count);
void Angle_Adjust2(int count);
void Angle_Adjust3(int count);
void Angle_Adjust4(int count);
void Angle_Adjust_Init(u16 x);

void Angle1_Adjust1(int count);
void Angle1_Adjust2(int count);
void Angle1_Adjust3(int count);
void Angle1_Adjust4(int count);
void Angle1_Adjust_Init(u16 x);

void MoveHand(void);
void MoveHead(void);
void LowerHead(void);
void GetUp(void);

#endif

