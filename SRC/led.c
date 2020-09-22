#include "led.h" 

    
//LED IO初始化
void LED_Init(void)
{    	 
	RCC->AHB1ENR|=1<<4;//使能PORTE时钟 
	GPIO_Set(GPIOE,PIN3|PIN4,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); //PE3,PE4设置
	LED0=1;//蓝色，LED0关闭
	LED1=1;//白色，LED1关闭
}






