#include "sys.h"
#include "usart3.h"	  
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"
//#include "timer.h"
#include "led.h"
#include "esp8266.h"
 
//初始化IO 串口3
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率 
void usart3_init(u32 pclk1,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;   
	temp=(float)(pclk1*1000000)/(bound*16);//得到USARTDIV,OVER8设置为0
	mantissa=temp;				 	//得到整数部分
	fraction=(temp-mantissa)*16; 	//得到小数部分,OVER8设置为0	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->AHB1ENR|=1<<1;   			//使能PORTB口时钟  
	RCC->APB1ENR|=1<<18;  			//使能串口3时钟 
	GPIO_Set(GPIOB,PIN10|PIN11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PB10,PB11,复用功能,上拉输出
 	GPIO_AF_Set(GPIOB,10,7);		//PB10,AF7
	GPIO_AF_Set(GPIOB,11,7);		//PB11,AF7  	   
	//波特率设置
 	USART3->BRR=mantissa; 			// 波特率设置	  

	USART3->CR1|=1<<3;  			//串口发送使能  
	USART3->CR1|=1<<2;  			//串口接收使能
	USART3->CR1|=1<<5;    			//接收缓冲区非空中断使能	
	USART3->CR1|=1<<13;  			//串口使能  
	MY_NVIC_Init(0,0,USART3_IRQn,2);//组2，优先级0,0,最高优先级 
	USART3_RX_STA=0;				//清零 
}



#ifdef USART3_RX_EN  

 u8  USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN字节
 u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节
 vu16 USART3_RX_STA=0;   						//接收数据状态

static unsigned char TxBuffer[256];
static unsigned char TxCounter=0;
static unsigned char count=0; 
extern void CopeSerial3Data(unsigned char ucData);



void USART3_printf (char *fmt, ...) 
{ 
	char buffer[USART_REC_LEN+1];  // CMD_BUFFER_LEN长度自己定义吧 
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
		USART_SendData(USART3, *str++);									//发送数据
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);		//等待发送完成
	}
	
}

void USART3_IRQHandler(void)
{
		if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收中断
	{
		if(esp8266_cnt >= sizeof(esp8266_buf))	esp8266_cnt = 0; //防止串口被刷爆
		esp8266_buf[esp8266_cnt++] = USART3->DR;
		
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}

} 

#endif


