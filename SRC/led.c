#include "led.h" 

    
//LED IO��ʼ��
void LED_Init(void)
{    	 
	RCC->AHB1ENR|=1<<4;//ʹ��PORTEʱ�� 
	GPIO_Set(GPIOE,PIN3|PIN4,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); //PE3,PE4����
	LED0=1;//��ɫ��LED0�ر�
	LED1=1;//��ɫ��LED1�ر�
}






