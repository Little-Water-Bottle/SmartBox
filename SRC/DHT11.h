#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//DHT11������ʪ�ȴ�������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
    
//IO��������
#define DHT11_IO_IN() GPIO_Set(GPIOD,PIN11,GPIO_MODE_IN,0,0,GPIO_PUPD_RES);  //PD(11)����
	
#define DHT11_IO_OUT() GPIO_Set(GPIOD,PIN11,GPIO_MODE_OUT,GPIO_OTYPE_PP,0,0);  //PD(11)���

////IO��������
//#define DHT11_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
//#define DHT11_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
////IO��������											   
#define	DHT11_DQ_OUT PDout(11) //���ݶ˿�	PD11 
#define	DHT11_DQ_IN  PDin(11)  //���ݶ˿�	PD11
extern u8 temperature;  	    
extern 	u8 humidity; 

u8 DHT11_Test(void);//DHT11����
u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif















