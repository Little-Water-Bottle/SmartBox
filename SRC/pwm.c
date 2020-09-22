#include "sys.h"
#include "pwm.h"
#include "delay.h"
void TIM5_PWM_Init(u32 arr,u32 psc)
{

	RCC->APB1ENR|=1<<3; 	//TIM5时钟使能    
	RCC->AHB1ENR|=1<<0;   	//使能PORTA时钟	
	GPIO_Set(GPIOA,PIN0|PIN1|PIN2|PIN3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,下拉
	GPIO_AF_Set(GPIOA,0,2);	//PA0,AF2
	GPIO_AF_Set(GPIOA,1,2);	
	GPIO_AF_Set(GPIOA,2,2);
	GPIO_AF_Set(GPIOA,3,2);
	TIM5->ARR=arr;//设定计数器自动重装值
	TIM5->PSC=psc;//预分频器不分频
	TIM5->CCMR1|=13<<3; //输入捕获 1 滤波 //1101： fSAMPLING=fDTS/32， N=5
	TIM5->CCMR1|=13<<11;//输入捕获 2 滤波
	TIM5->CCMR2|=13<<3; //输入捕获 3 滤波
	TIM5->CCMR2|=13<<11;//输入捕获 4 滤波
	TIM5->CCER|=1<<0;   //CH1输出使能
	TIM5->CCER|=1<<4;   //CH2输出使能	
	TIM5->CCER|=1<<8;   //CH3输出使能	
	TIM5->CCER|=1<<12;  //CH4输出使能	
	TIM5->CR1|=1<<7;    //自动重载预装载使能
	TIM5->CR1|=1<<0;    //使能TIM5
	TIM5->CR1&=~(1<<4); //计数器递增计数
}

void TIM8_PWM_Init(u32 arr,u32 psc)
{
	RCC->APB2ENR|=1<<1;//TIM8时钟使能
	RCC->AHB1ENR|=1<<2;//使能PORTC时钟
	GPIO_Set(GPIOC,PIN6|PIN7|PIN8|PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);
	GPIO_AF_Set(GPIOC,6,3);	
	GPIO_AF_Set(GPIOC,7,3);	
	GPIO_AF_Set(GPIOC,8,3);
	GPIO_AF_Set(GPIOC,9,3);
	TIM8->ARR=arr;
	TIM8->PSC=psc;
	TIM8->CR1|=1<<0;
	TIM8->CR1|=1<<7;
	TIM8->CR1&=~(1<<4);
	TIM8->CCMR1|=13<<3;
	TIM8->CCMR1|=13<<11;
	TIM8->CCMR2|=13<<3;
	TIM8->CCMR2|=13<<11;
	TIM8->CCER|=1<<0;
	TIM8->CCER|=1<<4;	
	TIM8->CCER|=1<<8;	
	TIM8->CCER|=1<<12;
	TIM8->BDTR|=1<<15;//主输出使能
	
//	Angle_Adjust1(15);
//	Angle_Adjust2(25);
//	Angle_Adjust3(15);
//	Angle_Adjust4(9);
}

//count= 5：0度
//count=10：45度
//count=15：90度
//count=20：135度
//count=25：180度
//5=<count<=25
void Angle_Adjust1(int count)//PWM5
{
	TIM8->CCR1=count;
}

void Angle_Adjust2(int count)//PWM6
{
	TIM8->CCR2=count;
}

void Angle_Adjust3(int count)//PWM7
{
	TIM8->CCR3=count;
}

void Angle_Adjust4(int count)//PWM8
{
	TIM8->CCR4=count;
}

void Angle1_Adjust1(int count)//PWM5
{
	TIM5->CCR1=count;
}

void Angle1_Adjust2(int count)//PWM6
{
	TIM5->CCR2=count;
}

void Angle1_Adjust3(int count)//PWM7
{
	TIM5->CCR3=count;
}

void Angle1_Adjust4(int count)//PWM8
{
	TIM5->CCR4=count;
}


void Angle_Adjust_Init(u16 x) 	//所有舵机初始位置 置中
{

	Angle_Adjust2(x);
	Angle_Adjust3(x);
	Angle_Adjust4(x);
}
void Angle1_Adjust_Init(u16 x) 	//所有舵机初始位置 置中
{
	Angle1_Adjust1(x);
	
}

/*CCR1是摇头舵机pwm5
头处于前方是11,往左转90度为25，右转90度为5*/
void MoveHead(void)//摇头程序
{
	TIM8->CCR1=11;//处于前方
	delay_ms(250);
	TIM8->CCR1=19;//左转70度
	delay_ms(250);
	TIM8->CCR1=11;
	delay_ms(250);
	TIM8->CCR1=19;
	delay_ms(250);
	TIM8->CCR1=11;
}

/*CCR2是左边舵机pwm6
  CCR3是右边舵机pwm7*/
void MoveHand(void)//摆手程序
{
	TIM8->CCR2=23;//调节低度，数字越大，低度越低
	delay_ms(200);
	TIM8->CCR2=15; //调节高度，数字越小，高度越高
	delay_ms(200);
	TIM8->CCR2=23;

	
	TIM8->CCR3=23;//调节低度，数字越小，低度越低	
	delay_ms(200);
	TIM8->CCR3=15;//调节高度，数字越大，高度越高
	delay_ms(200);
	TIM8->CCR3=23;
}


/*CCR4是变形舵机pwm8*/
void LowerHead(void)//往后弯腰程序
{
	TIM8->CCR4=12;//不调到11，会被阻挡，无法到达指定低处
}

void GetUp(void)//起身程序
{
	TIM8->CCR4=17;
}
