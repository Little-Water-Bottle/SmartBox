#ifndef PID_H
#define PID_H

#include "sys.h" 



void PID_Init(void);

float PID_realize(float angle);

void PID_LeftTurn(float angle);
void PID_RightTurn(float angle);

#endif

