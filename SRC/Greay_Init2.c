/*
*********************************************************************************************************
*	��������˵�����Ҷȹ��ܳ�ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#include "Greay_Init2.h"
#include "sys.h"
void Greay_Init2()
{
	RCC->AHB1ENR|=1<<0; //ʹ��PORTAʱ��
	RCC->AHB1ENR|=1<<4;//ʹ��PORTEʱ��
	GPIO_Set(GPIOA,PIN5|PIN12,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); //PA5,PA12������������
	GPIO_Set(GPIOE,PIN0,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PE0��������
	Gray111=1;
	Gray222=1;
	Gray333=1;
}