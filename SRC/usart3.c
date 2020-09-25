#include "sys.h"
#include "usart3.h"	  
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"
//#include "timer.h"
#include "led.h"
#include "esp8266.h"
 
//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������ 
void usart3_init(u32 pclk1,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;   
	temp=(float)(pclk1*1000000)/(bound*16);//�õ�USARTDIV,OVER8����Ϊ0
	mantissa=temp;				 	//�õ���������
	fraction=(temp-mantissa)*16; 	//�õ�С������,OVER8����Ϊ0	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->AHB1ENR|=1<<1;   			//ʹ��PORTB��ʱ��  
	RCC->APB1ENR|=1<<18;  			//ʹ�ܴ���3ʱ�� 
	GPIO_Set(GPIOB,PIN10|PIN11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PB10,PB11,���ù���,�������
 	GPIO_AF_Set(GPIOB,10,7);		//PB10,AF7
	GPIO_AF_Set(GPIOB,11,7);		//PB11,AF7  	   
	//����������
 	USART3->BRR=mantissa; 			// ����������	  

	USART3->CR1|=1<<3;  			//���ڷ���ʹ��  
	USART3->CR1|=1<<2;  			//���ڽ���ʹ��
	USART3->CR1|=1<<5;    			//���ջ������ǿ��ж�ʹ��	
	USART3->CR1|=1<<13;  			//����ʹ��  
	MY_NVIC_Init(0,0,USART3_IRQn,2);//��2�����ȼ�0,0,������ȼ� 
	USART3_RX_STA=0;				//���� 
}



#ifdef USART3_RX_EN  

 u8  USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
 u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
 vu16 USART3_RX_STA=0;   						//��������״̬

static unsigned char TxBuffer[256];
static unsigned char TxCounter=0;
static unsigned char count=0; 
extern void CopeSerial3Data(unsigned char ucData);



void USART3_printf (char *fmt, ...) 
{ 
	char buffer[USART_REC_LEN+1];  // CMD_BUFFER_LEN�����Լ������ 
	u8 i = 0; 

	va_list arg_ptr; 
	va_start(arg_ptr, fmt);   
	vsnprintf(buffer, USART_REC_LEN+1, fmt, arg_ptr); 
	while ((i < USART_REC_LEN) && buffer[i]) 
	{ 
		  USART_SendData(USART3, (u8) buffer[i++]); 
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);  
	} 
	va_end(arg_ptr); 
}

void Usart3_SendString(unsigned char *str, unsigned short len)
{
unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USART3, *str++);									//��������
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);		//�ȴ��������
	}
	
}

void USART3_IRQHandler(void)
{
		if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //�����ж�
	{
		if(esp8266_cnt >= sizeof(esp8266_buf))	esp8266_cnt = 0; //��ֹ���ڱ�ˢ��
		esp8266_buf[esp8266_cnt++] = USART3->DR;
		
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}

} 

#endif


