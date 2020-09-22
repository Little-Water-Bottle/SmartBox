#ifndef DEMO_MOTOR_H
#define DEMO_MOTOR_H

#include "pwm.h"

#define M1 PFout(14)
#define M2 PFout(15)
#define M3 PGout(0)
#define M4 PGout(1)

void CarAdvance(u8 speed);
void CarRetreat(u8 speed);
void motor_configuration(u8 PWM_fre);
void SetLeftWhell(u8 left_direction,u8 speed);                                           
void SetRightWhell(u8 right_direction,u8 speed);
void frontWhell(u8 front_direction,u8 speed);
void behindWhell(u8 behind_direction,u8 speed);
void Set_Motor(int left_speed,int right_speed);
void Set_Motor_1(int left_speed,int right_speed);

#endif




