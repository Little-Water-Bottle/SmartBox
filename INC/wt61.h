#ifndef __WT61_H
#define __WT61_H
#include "stdio.h"	
#include "sys.h"

//struct SAngle
//{
//	short Angle[3];
//	short T;
//};


//void CopeSerial3Data(unsigned char ucData);
//float Get_Angle(void);
//int Get_Gesture(void);


//#define	WiT_6axle 	1				//ʹ��ά�ص����ᴮ��
#define	GY_25_0xAA 	0				//ʹ��GY25ģ�飬��ͷΪ0xAA


void blance_6axle_Usart6_Init(void);

void DMA_forUsart6IDLE_Init(void);

s16 Get_Angle(u8 axle);


#endif

