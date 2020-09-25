#include "wt61.h"
#include <string.h>
#include <stdio.h>
#include "led.h"


//struct SAngle 	stcAngle;



//void CopeSerial3Data(unsigned char ucData)
//{
//	static unsigned char ucRxBuffer[250];
//	static unsigned char ucRxCnt = 0;	

//	ucRxBuffer[ucRxCnt++]=ucData;	//将收到的数据存入缓冲区中
//	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
//	{
//		ucRxCnt=0;
//		return;
//	}
//	if (ucRxCnt<11) {return;}//数据不满11个，则返回
//	else
//	{
//		switch(ucRxBuffer[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
//		{
////			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);break;//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析。
////			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
////			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
//			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;	
//		}
//		
//		ucRxCnt=0;//清空缓存区
//	}

//}


///*
//*********************************************************************************************************
//*	函 数 名: Get_Angle
//*	功能说明: 获得转弯的角度
//*	形    参: 
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//float Get_Angle(void)
//{
//	float a;
//	
//	a = (float)stcAngle.Angle[2]/32768*180;
//	
////	a = ((a + 360) % 360);
////	printf("Angle:%.3f %.3f %.3f\r \n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
////	USART3->CR1&=~(1<<5);
//	return a;
//}



///*
//*********************************************************************************************************
//*	函 数 名: Get_Gesture
//*	功能说明: Before and after the gesture
//*	形    参: 
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//int Get_Gesture(void)
//{
//	int a;
//	a = (int)Get_Angle();
//	if(a < 0)
//	{
//		a = a -120;
//	}else
//	{
//		
//	}
////	printf("Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
//	return a;
//	
//}

#include "sys.h"
#include "delay.h"
#include "usart.h"


//全局变量

u8 bufferAngle[33];
/****************************************************************************
函数名				：blance_6axle_Usart6_Init	初始化串口6
参数				：void			
返回				：void
描述				：初始化波特率中断等。。
创建人				：ragne
创建日期			：2018年3月26日14:07:54
最新更改时间	：2018年3月26日14:09:24
****************************************************************************/
void blance_6axle_Usart6_Init()
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//数据流
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//使能发送接收
	USART_InitStructure.USART_Parity=USART_Parity_No;					//校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//8数据位
	
	USART_Init(USART3,&USART_InitStructure);
//	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);//使能接收DMA
	
	USART_Cmd(USART3,ENABLE);
  
	
	DMA_forUsart6IDLE_Init();


	//中断相关
	USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;			//中断优先级设置
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	
	DMA_ITConfig(DMA1_Stream1,DMA_IT_TC,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;			//中断优先级设置
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	
}

///*
//*********************************************************************************************************
//*	函 数 名: Get_Angle
//*	功能说明: 获得转弯的角度
//*	形    参: 
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//float Get_Angle(void)
//{
//	float a;
//	
//	a = (float)stcAngle.Angle[2]/32768*180;
//	
////	a = ((a + 360) % 360);
////	printf("Angle:%.3f %.3f %.3f\r \n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
////	USART3->CR1&=~(1<<5);
//	return a;
//}



///*
//*********************************************************************************************************
//*	函 数 名: Get_Gesture
//*	功能说明: Before and after the gesture
//*	形    参: 
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//int Get_Gesture(void)
//{
//	int a;
//	a = (int)Get_Angle();
//	if(a < 0)
//	{
//		a = a -120;
//	}else
//	{
//		
//	}
////	printf("Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
//	return a;
//	
//}


/****************************************************************************
函数名				：get_balance_Angle	更新仰角和倾斜角、偏向角
参数				：void				
返回				：void
描述				：处理角度数据 并更新至数据库working_Data.文件内
创建人				：ragne
创建日期			：2018年3月26日14:07:54
最新更改时间	：2018年4月20日13:24:17
备注：摒弃不用；使用dma代替，，数据变为函数
****************************************************************************/
//void get_balance_6axle_Angle()
//{	
//	if(		1)		//校验位校验
//	{	
//					
//		working_Blance_Angle_X=(u16)(((BUF_6axle[3]<<8)|BUF_6axle[2])/182);//(32768/180=182.04)
//														//滚转角（x 轴） Roll=((RollH<<8)|RollL)/32768*180(°)
//		working_Blance_Angle_Y=(u16)(((BUF_6axle[5]<<8)|BUF_6axle[4])/182);
//														//俯仰角（y 轴） Pitch=((PitchH<<8)|PitchL)/32768*180(°)
//		working_Blance_Angle_Z=(u16)(((BUF_6axle[7]<<8)|BUF_6axle[6])/182);
//														//偏航角（z 轴） Yaw=((YawH<<8)|YawL)/32768*180(°)
//		
//	}
//}

/****************************************************************************
函数名				：			串口6中断服务函数
参数				：void				
返回				：void
描述				：当数据发生错误时校准
创建人				：ragne
创建日期			：2018年3月26日14:07:41
最新更改时间	：2018年4月20日13:21:09
****************************************************************************/
//extern u16 i,p;
//void USART3_IRQHandler(void)
//{
//	int i;
//	if(USART_GetITStatus(USART3,USART_IT_IDLE))
//	{
//		DMA_Cmd(DMA1_Stream1, DISABLE);
//		DMA_forUsart6IDLE_Init();
//		USART_ITConfig(USART3,USART_IT_IDLE,DISABLE);
//		i++;
//	}
//}


/****************************************************************************
函数名				：			串口6中断服务函数
参数				：void				
返回				：void
描述				：当数据发生错误时校准
创建人				：ragne
创建日期			：2018年3月26日14:07:41
最新更改时间	：2018年4月20日13:21:09
****************************************************************************/
void DMA_forUsart6IDLE_Init()
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA2 时钟使能
	while (DMA_GetCmdStatus(DMA1_Stream1) != DISABLE){}//等待 DMA 可配置
	
	DMA_InitStructure.DMA_Channel=DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART3->DR;//DMA 外设地址
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)bufferAngle;//DMA 存储器 0 地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//存储器到外设模式
	DMA_InitStructure.DMA_BufferSize = 33;//数据传输量
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8 位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度:8 位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// 使用普通模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//单次传输
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输
	
	DMA_Init(DMA1_Stream1,&DMA_InitStructure);
	
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);
		
	DMA_Cmd(DMA1_Stream1, ENABLE);
		
//设置对应的 DMA 数据流传输的数据量大小,函数为：
//void DMA_SetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx, uint16_t Counter);

//FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
//比如我们要查询 DMA 数据流 7 传输是否完成，方法是：

//获取当前剩余数据量大小的函数：
//uint16_t DMA_GetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx);
//比如我们要获取 DMA 数据流 7 还有多少个数据没有传输，方法是：
//DMA_GetCurrDataCounter(DMA1_Channel4);

}

int ax,ay,az;
s16 Get_Angle(u8 axle)
{
	if(bufferAngle[0]==0x55&&bufferAngle[11]==0x55&&bufferAngle[22]==0x55)//数据正确
	{	
		switch(axle)//更新数据，返回当前角度值
		{
			case 1:{
			ax=(u16)(((bufferAngle[25]<<8)|bufferAngle[24])/182);//(32768/180=182.04)
														//滚转角（x 轴） Roll=((RollH<<8)|RollL)/32768*180(°)
			return ax;
			}
			case 2:{
			ay=(u16)(((bufferAngle[27]<<8)|bufferAngle[26])/182);
														//俯仰角（y 轴） Pitch=((PitchH<<8)|PitchL)/32768*180(°)
			return ay;
			}
			case 3:{
			az=(u16)(((bufferAngle[29]<<8)|bufferAngle[28])/182);
			return az;
			}
		}
	}
	else//数据错误
	{
		USART_ITConfig(USART6,USART_IT_IDLE,ENABLE);//在中断函数中校准
		switch(axle)//返回之前准的数据
		{
			case 1:{
			return ax;
			}
			case 2:{
			return ay;
			}
			case 3:{
			return az;
			}
		}				
	}
	return az;//没用防止报错
}



