#include "DIO.h"
#include "demo_DIO.h"
#include "led.h"

/*
*********************************************************************************************************
*	��������˵�����Ҷȹ��ܳ�ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Gray_Init(void)
{
	RCC->AHB1ENR|=1<<1; //ʹ��PORTBʱ��
	RCC->AHB1ENR|=1<<4; //ʹ��PORTEʱ��
	RCC->AHB1ENR|=1<<5; //ʹ��PORTFʱ��
	GPIO_Set(GPIOF,PIN0|PIN1|PIN2|PIN4|PIN5|PIN6,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);  //PF(0,1,2,4,5,6)������������
	GPIO_Set(GPIOE,PIN5|PIN6|PIN0|PIN1|PIN2,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); //PE(1,2,5,6)������������
	GPIO_Set(GPIOB,PIN4|PIN5|PIN6|PIN7|PIN8|PIN9,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); //PB(4,5,6,7)������������
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
*	��������˵���������ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Laser_Init(void)
{
	RCC->AHB1ENR|=1<<0;//ʹ��PORTAʱ��
	RCC->AHB1ENR|=1<<3;//ʹ��PORTDʱ��
	RCC->AHB1ENR|=1<<4;//ʹ��PORTEʱ��abcde
	GPIO_Set(GPIOD,PIN11|PIN2,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PD(11��������
	GPIO_Set(GPIOE,PIN0,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PE(0)��������
	GPIO_Set(GPIOA,PIN5|PIN12,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PA(5)��������
	Infrared_DIO1 = 1;
	queue = 1;
	ETR3 = 1;
	ETR2 = 1;
	ETR4 = 1;
}

/*
*********************************************************************************************************
*	��������˵�������⴫������ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Infrared_sensor_Init(void)
{
	RCC->AHB1ENR|=1<<3;//ʹ��PORTDʱ��
	RCC->AHB1ENR|=1<<6;//ʹ��PORTGʱ��
	GPIO_Set(GPIOD,PIN7,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PD(7)��������
	GPIO_Set(GPIOF,PIN7|PIN8,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);//PF(7,8)��������
	Infrared_DIO2 = 1;
	L_DIO3 = 1;
	R_DIO4 = 1;
}

/*
*********************************************************************************************************
*	�� �� ��: TIM2_Init
*	����˵��: ��ʱ��2ETR������ʼ��
*	��    ��: arr���Զ���װ��ֵ��
*	�� �� ֵ: ��
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
	TIM2->SMCR &= ~(0xf<<8);//���˲�
	TIM2->SMCR &= ~(3<<12);//�ر�Ԥ��Ƶ
	TIM2->SMCR |= 0<<15;//ETR�����࣬�ߵ�ƽ������������Ч
	TIM2->SMCR |= 1<<14;//ʹ���ⲿʱ��ģʽ2
	TIM2->CNT = 0x0;//���������
	TIM2->CR1 |= 1<<0;//ʹ�ܶ�ʱ��������������
}

/*
*********************************************************************************************************
*	�� �� ��: TIM3_Init
*	����˵��: ��ʱ��3ETR������ʼ��
*	��    ��: arr���Զ���װ��ֵ��
*	�� �� ֵ: ��
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
	TIM3->SMCR &= ~(0xf<<8);//���˲�
	TIM3->SMCR &= ~(3<<12);//�ر�Ԥ��Ƶ
	TIM3->SMCR |= 0<<15;//ETR�����࣬�ߵ�ƽ������������Ч
	TIM3->SMCR |= 1<<14;//ʹ���ⲿʱ��ģʽ2
	TIM3->CNT = 0x0;//���������
	TIM3->CR1 |= 1<<0;//ʹ�ܶ�ʱ��������������
}

/*
*********************************************************************************************************
*	�� �� ��: TIM6_Init
*	����˵��: ÿ0.5�����һ���ж�
*	��    ��: arr���Զ���װ��ֵ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void TIM6_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<4;	//TIM6ʱ��ʹ��    
 	TIM6->ARR=arr;  	//�趨�������Զ���װֵ   0.5s
	TIM6->PSC=psc;  	//Ԥ��Ƶ��	  
	TIM6->DIER|=1<<0;   //��������ж�	  
	TIM6->CR1|=0x01;    //ʹ�ܶ�ʱ��3
	TIM6->CR1|=1<<6;
	TIM6->CNT=0;
	MY_NVIC_Init(1,3,TIM6_DAC_IRQn,2);	//��ռ1�������ȼ�3����2	
}

u16 l_circlenow;
u16 r_circlenow;

extern u16 set_speed;
extern u8 flag_line;
u16 half_s;
//��ʱ��6�жϷ������	 
void TIM6_DAC_IRQHandler(void)
{ 		    		  			    
	if(TIM6->SR&0X0001)//����ж�
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
	TIM6->SR&=~(1<<0);//����жϱ�־λ 	    
}

