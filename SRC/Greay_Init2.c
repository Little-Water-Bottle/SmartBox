/*
*********************************************************************************************************
*	函数功能说明：灰度功能初始化
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
#include "Greay_Init2.h"
#include "sys.h"
void Greay_Init2()
{
	RCC->AHB1ENR|=1<<0; //使能PORTA时钟
	RCC->AHB1ENR|=1<<4;//使能PORTE时钟
	GPIO_Set(GPIOA,PIN5|PIN12,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); //PA5,PA12设置上拉输入
	GPIO_Set(GPIOE,PIN0,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PE0上拉输入
	Gray111=1;
	Gray222=1;
	Gray333=1;
}