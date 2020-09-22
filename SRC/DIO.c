#include "DIO.h"
#include "demo_DIO.h"
#include "led.h"

/*
*********************************************************************************************************
*	函数功能说明：灰度功能初始化
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void Gray_Init(void)
{
	RCC->AHB1ENR|=1<<1; //使能PORTB时钟
	RCC->AHB1ENR|=1<<4; //使能PORTE时钟
	RCC->AHB1ENR|=1<<5; //使能PORTF时钟
	GPIO_Set(GPIOF,PIN0|PIN1|PIN2|PIN4|PIN5|PIN6,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);  //PF(0,1,2,4,5,6)设置上拉输入
	GPIO_Set(GPIOE,PIN5|PIN6|PIN0|PIN1|PIN2,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); //PE(1,2,5,6)设置上拉输入
	GPIO_Set(GPIOB,PIN4|PIN5|PIN6|PIN7|PIN8|PIN9,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); //PB(4,5,6,7)设置上拉输入
	Gray1=1;
	Gray2=1;
	Gray3=1;
	Gray4=1;
	Gray5=1;
	Gray6=1;
	Gray7=1;
	Gray8=1;
	Gray11=1;
	Gray22=1;
	Gray33=1;
	Gray44=1;
	Gray55=1;
	Gray66=1;
	Gray77=1;
	Gray88=1;
	ETR1 = 1;
}

/*
*********************************************************************************************************
*	函数功能说明：激光初始化
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void Laser_Init(void)
{
	RCC->AHB1ENR|=1<<0;//使能PORTA时钟
	RCC->AHB1ENR|=1<<3;//使能PORTD时钟
	RCC->AHB1ENR|=1<<4;//使能PORTE时钟abcde
	GPIO_Set(GPIOD,PIN11|PIN2,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PD(11上拉输入
	GPIO_Set(GPIOE,PIN0,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PE(0)上拉输入
	GPIO_Set(GPIOA,PIN5|PIN12,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PA(5)上拉输入
	Infrared_DIO1 = 1;
	queue = 1;
	ETR3 = 1;
	ETR2 = 1;
	ETR4 = 1;
}

/*
*********************************************************************************************************
*	函数功能说明：红外传感器初始化
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void Infrared_sensor_Init(void)
{
	RCC->AHB1ENR|=1<<3;//使能PORTD时钟
	RCC->AHB1ENR|=1<<6;//使能PORTG时钟
	GPIO_Set(GPIOD,PIN7,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PD(7)上拉输入
	GPIO_Set(GPIOF,PIN7|PIN8,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PF(7,8)上拉输入
	Infrared_DIO2 = 1;
	L_DIO3 = 1;
	R_DIO4 = 1;
}

/*
*********************************************************************************************************
*	函 数 名: TIM2_Init
*	功能说明: 定时器2ETR计数初始化
*	形    参: arr（自动重装载值）
*	返 回 值: 无
*********************************************************************************************************
*/
void TIM2_Init(u16 arr)
{
	RCC->APB1ENR|=1<<0;
	RCC->AHB1ENR|=1<<0;
	GPIO_Set(GPIOA,PIN5,GPIO_MODE_AF,0,0,GPIO_PUPD_NONE);
	GPIO_AF_Set(GPIOA,5,1); 
	TIM2->ARR=arr;
	TIM2->PSC=0;
	TIM2->SMCR &= ~(0xf<<8);//无滤波
	TIM2->SMCR &= ~(3<<12);//关闭预分频
	TIM2->SMCR |= 0<<15;//ETR不反相，高电平或上升沿沿有效
	TIM2->SMCR |= 1<<14;//使能外部时钟模式2
	TIM2->CNT = 0x0;//清零计数器
	TIM2->CR1 |= 1<<0;//使能定时器，开启计数。
}

/*
*********************************************************************************************************
*	函 数 名: TIM3_Init
*	功能说明: 定时器3ETR计数初始化
*	形    参: arr（自动重装载值）
*	返 回 值: 无
*********************************************************************************************************
*/
void TIM3_Init(u16 arr)
{
	RCC->APB1ENR|=1<<1;
	RCC->AHB1ENR|=1<<3;
	GPIO_Set(GPIOD,PIN2,GPIO_MODE_AF,0,0,GPIO_PUPD_NONE);
	GPIO_AF_Set(GPIOD,2,2); 
	TIM3->ARR=arr;
	TIM3->PSC=0;
	TIM3->SMCR &= ~(0xf<<8);//无滤波
	TIM3->SMCR &= ~(3<<12);//关闭预分频
	TIM3->SMCR |= 0<<15;//ETR不反相，高电平或上升沿沿有效
	TIM3->SMCR |= 1<<14;//使能外部时钟模式2
	TIM3->CNT = 0x0;//清零计数器
	TIM3->CR1 |= 1<<0;//使能定时器，开启计数。
}

/*
*********************************************************************************************************
*	函 数 名: TIM6_Init
*	功能说明: 每0.5秒进入一次中断
*	形    参: arr（自动重装载值）
*	返 回 值: 无
*********************************************************************************************************
*/
void TIM6_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<4;	//TIM6时钟使能    
 	TIM6->ARR=arr;  	//设定计数器自动重装值   0.5s
	TIM6->PSC=psc;  	//预分频器	  
	TIM6->DIER|=1<<0;   //允许更新中断	  
	TIM6->CR1|=0x01;    //使能定时器3
	TIM6->CR1|=1<<6;
	TIM6->CNT=0;
	MY_NVIC_Init(1,3,TIM6_DAC_IRQn,2);	//抢占1，子优先级3，组2	
}

u16 l_circlenow;
u16 r_circlenow;

extern u16 set_speed;
extern u8 flag_line;
u16 half_s;
//定时器6中断服务程序	 
void TIM6_DAC_IRQHandler(void)
{ 		    		  			    
	if(TIM6->SR&0X0001)//溢出中断
	{
		half_s ++;
//		l_circlenow=TIM3->CNT;
//		TIM3->CNT = 0;
//		
//		r_circlenow=TIM2->CNT;
//		TIM2->CNT = 0;
//		if(flag_line == 0)
//		{
//			go_straight_line(set_speed);
//		}	
	}				   
	TIM6->SR&=~(1<<0);//清除中断标志位 	    
}

