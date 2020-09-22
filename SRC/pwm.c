#include "sys.h"
#include "pwm.h"
#include "delay.h"
void TIM5_PWM_Init(u32 arr,u32 psc)
{

	RCC->APB1ENR|=1<<3; 	//TIM5ʱ��ʹ��    
	RCC->AHB1ENR|=1<<0;   	//ʹ��PORTAʱ��	
	GPIO_Set(GPIOA,PIN0|PIN1|PIN2|PIN3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,����
	GPIO_AF_Set(GPIOA,0,2);	//PA0,AF2
	GPIO_AF_Set(GPIOA,1,2);	
	GPIO_AF_Set(GPIOA,2,2);
	GPIO_AF_Set(GPIOA,3,2);
	TIM5->ARR=arr;//�趨�������Զ���װֵ
	TIM5->PSC=psc;//Ԥ��Ƶ������Ƶ
	TIM5->CCMR1|=13<<3; //���벶�� 1 �˲� //1101�� fSAMPLING=fDTS/32�� N=5
	TIM5->CCMR1|=13<<11;//���벶�� 2 �˲�
	TIM5->CCMR2|=13<<3; //���벶�� 3 �˲�
	TIM5->CCMR2|=13<<11;//���벶�� 4 �˲�
	TIM5->CCER|=1<<0;   //CH1���ʹ��
	TIM5->CCER|=1<<4;   //CH2���ʹ��	
	TIM5->CCER|=1<<8;   //CH3���ʹ��	
	TIM5->CCER|=1<<12;  //CH4���ʹ��	
	TIM5->CR1|=1<<7;    //�Զ�����Ԥװ��ʹ��
	TIM5->CR1|=1<<0;    //ʹ��TIM5
	TIM5->CR1&=~(1<<4); //��������������
}

void TIM8_PWM_Init(u32 arr,u32 psc)
{
	RCC->APB2ENR|=1<<1;//TIM8ʱ��ʹ��
	RCC->AHB1ENR|=1<<2;//ʹ��PORTCʱ��
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
	TIM8->BDTR|=1<<15;//�����ʹ��
	
//	Angle_Adjust1(15);
//	Angle_Adjust2(25);
//	Angle_Adjust3(15);
//	Angle_Adjust4(9);
}

//count= 5��0��
//count=10��45��
//count=15��90��
//count=20��135��
//count=25��180��
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


void Angle_Adjust_Init(u16 x) 	//���ж����ʼλ�� ����
{

	Angle_Adjust2(x);
	Angle_Adjust3(x);
	Angle_Adjust4(x);
}
void Angle1_Adjust_Init(u16 x) 	//���ж����ʼλ�� ����
{
	Angle1_Adjust1(x);
	
}

/*CCR1��ҡͷ���pwm5
ͷ����ǰ����11,����ת90��Ϊ25����ת90��Ϊ5*/
void MoveHead(void)//ҡͷ����
{
	TIM8->CCR1=11;//����ǰ��
	delay_ms(250);
	TIM8->CCR1=19;//��ת70��
	delay_ms(250);
	TIM8->CCR1=11;
	delay_ms(250);
	TIM8->CCR1=19;
	delay_ms(250);
	TIM8->CCR1=11;
}

/*CCR2����߶��pwm6
  CCR3���ұ߶��pwm7*/
void MoveHand(void)//���ֳ���
{
	TIM8->CCR2=23;//���ڵͶȣ�����Խ�󣬵Ͷ�Խ��
	delay_ms(200);
	TIM8->CCR2=15; //���ڸ߶ȣ�����ԽС���߶�Խ��
	delay_ms(200);
	TIM8->CCR2=23;

	
	TIM8->CCR3=23;//���ڵͶȣ�����ԽС���Ͷ�Խ��	
	delay_ms(200);
	TIM8->CCR3=15;//���ڸ߶ȣ�����Խ�󣬸߶�Խ��
	delay_ms(200);
	TIM8->CCR3=23;
}


/*CCR4�Ǳ��ζ��pwm8*/
void LowerHead(void)//������������
{
	TIM8->CCR4=12;//������11���ᱻ�赲���޷�����ָ���ʹ�
}

void GetUp(void)//�������
{
	TIM8->CCR4=17;
}
