#include "sys.h"
#include "counterInit.h"
#include "led.h"
//计时器初值为零
int transport = 0;
int shi  = 0;	//时
int fen  = 0;	//分
int miao = 0;	//秒

void counterInit() 
{
		//实验分割线
	//////////////////////////////////////
	
	//声明一个GPIO结构体变量
	GPIO_InitTypeDef GPIO_InitStructure;
	//声明一个定时器结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructrue;
	//声明一个中断优先分组的结构体变量
	NVIC_InitTypeDef NVIC_InitStructure;

	//使能GPIO外设时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	//定义一个GPIO结构体变量
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3 |GPIO_Pin_4;//对应引脚分别接到Led0，led1
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;         //GPIO为输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;    //100MHZ
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;	    //推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;		    //上拉-
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	//设置定时器中断的优先分组
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;   //抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;		     //响应优先级为3
	TIM_TimeBaseInitStructrue.TIM_Period=19999;     //Tout=(ARR+1)(PSC+1)/Tclk   (4999+1)(8399+1)/(1/84M)		arr=4999 0.5秒	arr=19999 2秒
	TIM_TimeBaseInitStructrue.TIM_Prescaler=8399;
	TIM_TimeBaseInitStructrue.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructrue.TIM_ClockDivision=TIM_CKD_DIV1;
	//使能定时器2的外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//初始化定时器2
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructrue);
 
	//设置优先级分组  为组2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//初始化优先级分组
	NVIC_Init(&NVIC_InitStructure);
    //配置定时器的中断的中断源
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//使能定时器3
	TIM_Cmd(TIM2,ENABLE);
//	while(1)
//    {
//       //无限循环等待中断
//    }
	
	//////////////////////////////////////
}


//时钟计时函数
//transport 在定时器中断中以两秒加一
void TimerCount() 
{
	miao = transport*2;
	if(miao == 60)
	{
		fen++;
		miao = 0;
	}
	if(fen == 60) 
	{
		shi++;
		fen = 0;
	}
	if(shi == 24) 
	{
		shi  = 0;
		fen  = 0;
		miao = 0;
	}
	if(miao%10==0)
	{
//		LED0=!LED0;
//		LED1=!LED1;
	}


}


