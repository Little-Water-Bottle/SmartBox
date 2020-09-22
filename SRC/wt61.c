#include "wt61.h"
#include <string.h>
#include <stdio.h>
#include "led.h"


//struct SAngle 	stcAngle;



//void CopeSerial3Data(unsigned char ucData)
//{
//	static unsigned char ucRxBuffer[250];
//	static unsigned char ucRxCnt = 0;	

//	ucRxBuffer[ucRxCnt++]=ucData;	//���յ������ݴ��뻺������
//	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
//	{
//		ucRxCnt=0;
//		return;
//	}
//	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
//	else
//	{
//		switch(ucRxBuffer[1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
//		{
////			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);break;//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ�����
////			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
////			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
//			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;	
//		}
//		
//		ucRxCnt=0;//��ջ�����
//	}

//}


///*
//*********************************************************************************************************
//*	�� �� ��: Get_Angle
//*	����˵��: ���ת��ĽǶ�
//*	��    ��: 
//*	�� �� ֵ: ��
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
//*	�� �� ��: Get_Gesture
//*	����˵��: Before and after the gesture
//*	��    ��: 
//*	�� �� ֵ: ��
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


//ȫ�ֱ���

u8 bufferAngle[33];
/****************************************************************************
������				��blance_6axle_Usart6_Init	��ʼ������6
����				��void			
����				��void
����				����ʼ���������жϵȡ���
������				��ragne
��������			��2018��3��26��14:07:54
���¸���ʱ��	��2018��3��26��14:09:24
****************************************************************************/
void blance_6axle_Usart6_Init()
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//������
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//ʹ�ܷ��ͽ���
	USART_InitStructure.USART_Parity=USART_Parity_No;					//У��λ
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//ֹͣλ
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//8����λ
	
	USART_Init(USART3,&USART_InitStructure);
//	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);//ʹ�ܽ���DMA
	
	USART_Cmd(USART3,ENABLE);
  
	
	DMA_forUsart6IDLE_Init();


	//�ж����
	USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;			//�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	
	DMA_ITConfig(DMA1_Stream1,DMA_IT_TC,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;			//�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	
}

///*
//*********************************************************************************************************
//*	�� �� ��: Get_Angle
//*	����˵��: ���ת��ĽǶ�
//*	��    ��: 
//*	�� �� ֵ: ��
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
//*	�� �� ��: Get_Gesture
//*	����˵��: Before and after the gesture
//*	��    ��: 
//*	�� �� ֵ: ��
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
������				��get_balance_Angle	�������Ǻ���б�ǡ�ƫ���
����				��void				
����				��void
����				������Ƕ����� �����������ݿ�working_Data.�ļ���
������				��ragne
��������			��2018��3��26��14:07:54
���¸���ʱ��	��2018��4��20��13:24:17
��ע���������ã�ʹ��dma���棬�����ݱ�Ϊ����
****************************************************************************/
//void get_balance_6axle_Angle()
//{	
//	if(		1)		//У��λУ��
//	{	
//					
//		working_Blance_Angle_X=(u16)(((BUF_6axle[3]<<8)|BUF_6axle[2])/182);//(32768/180=182.04)
//														//��ת�ǣ�x �ᣩ Roll=((RollH<<8)|RollL)/32768*180(��)
//		working_Blance_Angle_Y=(u16)(((BUF_6axle[5]<<8)|BUF_6axle[4])/182);
//														//�����ǣ�y �ᣩ Pitch=((PitchH<<8)|PitchL)/32768*180(��)
//		working_Blance_Angle_Z=(u16)(((BUF_6axle[7]<<8)|BUF_6axle[6])/182);
//														//ƫ���ǣ�z �ᣩ Yaw=((YawH<<8)|YawL)/32768*180(��)
//		
//	}
//}

/****************************************************************************
������				��			����6�жϷ�����
����				��void				
����				��void
����				�������ݷ�������ʱУ׼
������				��ragne
��������			��2018��3��26��14:07:41
���¸���ʱ��	��2018��4��20��13:21:09
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
������				��			����6�жϷ�����
����				��void				
����				��void
����				�������ݷ�������ʱУ׼
������				��ragne
��������			��2018��3��26��14:07:41
���¸���ʱ��	��2018��4��20��13:21:09
****************************************************************************/
void DMA_forUsart6IDLE_Init()
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA2 ʱ��ʹ��
	while (DMA_GetCmdStatus(DMA1_Stream1) != DISABLE){}//�ȴ� DMA ������
	
	DMA_InitStructure.DMA_Channel=DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART3->DR;//DMA �����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)bufferAngle;//DMA �洢�� 0 ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//�洢��������ģʽ
	DMA_InitStructure.DMA_BufferSize = 33;//���ݴ�����
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8 λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8 λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// ʹ����ͨģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//���δ���
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
	
	DMA_Init(DMA1_Stream1,&DMA_InitStructure);
	
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);
		
	DMA_Cmd(DMA1_Stream1, ENABLE);
		
//���ö�Ӧ�� DMA �������������������С,����Ϊ��
//void DMA_SetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx, uint16_t Counter);

//FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
//��������Ҫ��ѯ DMA ������ 7 �����Ƿ���ɣ������ǣ�

//��ȡ��ǰʣ����������С�ĺ�����
//uint16_t DMA_GetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx);
//��������Ҫ��ȡ DMA ������ 7 ���ж��ٸ�����û�д��䣬�����ǣ�
//DMA_GetCurrDataCounter(DMA1_Channel4);

}

int ax,ay,az;
s16 Get_Angle(u8 axle)
{
	if(bufferAngle[0]==0x55&&bufferAngle[11]==0x55&&bufferAngle[22]==0x55)//������ȷ
	{	
		switch(axle)//�������ݣ����ص�ǰ�Ƕ�ֵ
		{
			case 1:{
			ax=(u16)(((bufferAngle[25]<<8)|bufferAngle[24])/182);//(32768/180=182.04)
														//��ת�ǣ�x �ᣩ Roll=((RollH<<8)|RollL)/32768*180(��)
			return ax;
			}
			case 2:{
			ay=(u16)(((bufferAngle[27]<<8)|bufferAngle[26])/182);
														//�����ǣ�y �ᣩ Pitch=((PitchH<<8)|PitchL)/32768*180(��)
			return ay;
			}
			case 3:{
			az=(u16)(((bufferAngle[29]<<8)|bufferAngle[28])/182);
			return az;
			}
		}
	}
	else//���ݴ���
	{
		USART_ITConfig(USART6,USART_IT_IDLE,ENABLE);//���жϺ�����У׼
		switch(axle)//����֮ǰ׼������
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
	return az;//û�÷�ֹ����
}



