#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//DHT11数字温湿度传感器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/16
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
    
//IO方向设置
#define DHT11_IO_IN() GPIO_Set(GPIOD,PIN11,GPIO_MODE_IN,0,0,GPIO_PUPD_RES);  //PD(11)输入
	
#define DHT11_IO_OUT() GPIO_Set(GPIOD,PIN11,GPIO_MODE_OUT,GPIO_OTYPE_PP,0,0);  //PD(11)输出

////IO方向设置
//#define DHT11_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
//#define DHT11_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
////IO操作函数											   
#define	DHT11_DQ_OUT PDout(11) //数据端口	PD11 
#define	DHT11_DQ_IN  PDin(11)  //数据端口	PD11
extern u8 temperature;  	    
extern 	u8 humidity; 

u8 DHT11_Test(void);//DHT11运行
u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    
#endif















