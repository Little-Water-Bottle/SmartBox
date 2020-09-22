#ifndef DIO_H
#define DIO_H

#include "sys.h"

void Gray_Init(void);
void Laser_Init(void);
void Infrared_sensor_Init(void);
void TIM2_Init(u16 arr);//定时器2初始化
void TIM3_Init(u16 arr);//定时器3初始化
void TIM6_Init(u16 arr,u16 psc);//定时器3初始化

#endif

