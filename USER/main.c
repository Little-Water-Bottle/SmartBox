#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "includes.h"
#include "os_app_hooks.h"
#include "beep.h"
#include "demo_dio.h"
#include "demo_motor.h"
#include "key.h"
#include "pwm.h"
#include "usart3.h"
#include "wt61.h"
#include "api.h"
#include "carBaseMoves.h"
#include "key.h"
#include "pid.h"
#include "math.h"
#include "demo_DIO_hou.h"
//�������
#include "counterInit.h"
#include "Greay_Init2.h"
#include "sendMedicine.h"
#include "DHT11.h"
#include "esp8266.h"
#include "onenet.h"
#include "lcd.h"
#include "TimeCount.h"



//�������ȼ�
#define START_TASK_PRIO		3
//�����ջ��С	
#define START_STK_SIZE 		128
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//�������ȼ�
#define RUN_TASK_PRIO		4
//�����ջ��С	
#define RUN_STK_SIZE 		512
//������ƿ�
OS_TCB RUN_TaskTCB;
//�����ջ	
CPU_STK RUN_TASK_STK[RUN_STK_SIZE];
void run_task(void *p_arg);

//�������ȼ�
#define SCANF_TASK_PRIO		4
//�����ջ��С	
#define SCANF_STK_SIZE 		128
//������ƿ�
OS_TCB ScanfTaskTCB;
//�����ջ	
CPU_STK SCANF_TASK_STK[SCANF_STK_SIZE];
//������
void scanf_task(void *p_arg);

//�������ȼ�
#define SHOW_TASK_PRIO		4
//�����ջ��С	
#define SHOW_STK_SIZE 		512
//������ƿ�
OS_TCB ShowTaskTCB;
//�����ջ	
CPU_STK SHOW_TASK_STK[SHOW_STK_SIZE];
//������
void show_task(void *p_arg);

//OS_TMR 	tmr1;		//��ʱ��1
//OS_TMR	tmr2;		//��ʱ��2
//void tmr1_callback(void *p_tmr, void *p_arg); 	//��ʱ��1�ص�����
//void tmr2_callback(void *p_tmr, void *p_arg);	//��ʱ��2�ص�����

extern int set_speed;
extern int flag_turn;
extern int flag_obstacles;
extern int stop;
extern int flag_obstacles_front;
extern struct pid1	pid;
extern int transport;	//��ʱ�Ӽ�ʱ������ֵ
extern u8 temp;   	    
extern u8 hum; 
extern u8 reset;//����
extern u8 way1;//ȷ��
extern int pill1;//������ҩƬ����
extern int pill2;
extern int pill3;
extern int pill4;

extern u8 way1;//ѡҩģʽģʽ
extern u8 way2;
extern u8 way3;
extern u8 p1;//�ϴ�����ҩƷ����
extern u8 p2;
extern u8 p3;
extern u8 p4;
extern u8 pi1;//�ϴ�����ҩƷʱ��
extern u8 pi2;
extern u8 pi3;
extern u8 pi4;
extern u8 pil1;//�ϴ�����ҩƷ����
extern u8 pil2;
extern u8 pil3;
extern u8 pil4;

u8 sendOver;	//��ҩ������־
u8 keyConfirm;	//ȷ�ϼ����±�־
int main(void)
{
	u8 temperature=0;  	    
	u8 humidity=0; 

unsigned char *dataPtr = NULL;
	unsigned short timeCount = 300;	//���ͼ������
//	unsigned short timeCount = 300;	//���ͼ������
//	Stm32_Clock_Init(336,8,2,7); //ϵͳʱ������
	delay_init(168);	  //��ʱ������ʼ��
// 	motor_configuration(0);//�����ʼ������һ�������ʼ��
	TIM5_PWM_Init(200-1,16800-1);
	LED_Init ();//С�Ƴ�ʼ������
	BEEP_Init();//��������ʼ������
//	noise_Init();//����ģ���ʼ������
	uart_init(115200);//����1��ʼ������
//	counterInit();	//��������ʼ��
//	TIM2_Init(65535);
//	TIM3_Init(65535);
// 	TIM6_Init(5000-1,8400-1);
	TIM8_PWM_Init(200-1,16800-1);
//	fan_Init(5);//���ȵ����ʼ������	
	Infrared_sensor_Init();//���⴫�г�ʼ������
	usart3_init(42,115200);		//����3��ʼ��
	delay_ms(3000);
	
	LCD_Init();
	DHT11_Init();
	Greay_Init2();
	KEY_Init();
	POINT_COLOR=RED;  
	Angle_Adjust_Init(5);	//���ж����ʼλ�ó�ʼ��
	delay_ms(500);
//	ESP8266_Init();					//��ʼ��ESP8266
//	while(OneNet_DevLink())			//����OneNET
		delay_ms(500);
//	LED0=0;  //LED0��
//	LED1=0;  //LED1��
//	LCD_ShowString(20,20,200,16,16,"OneNetOpen");

//	while(1)
//	{
////		Angle1_Adjust_Init(25);
////		delay_ms(500);
////		
//		
////		Angle1_Adjust_Init(3);
////		Angle_Adjust1(18);
////		delay_ms(1000);
//		
//		
////		Angle1_Adjust_Init(6);
////		Angle_Adjust1(11 );
////		delay_ms(1000);
////		break;
////		Angle1_Adjust1();//PWM5
////		//ѡҩ����
////		while(1)
////		{	
////			if(KEY_Scan2() == '0') break;	//����ɨ�� �ж�ҩƬ����
////			LCD_ShowNum(82,180,pill1,2,12);
////	   	LCD_ShowNum(82,200,pill2,2,12);
////	  	LCD_ShowNum(82,220,pill3,2,12);
////		}

////		//��ҩ����
////		i=sendMedicine();
////		if(i=='0')
////		{
////			Angle_Adjust_Init(5);
////		}
////		
//		
//		}


//ҩ����ҩ����
//while(1)
//{

//	sendPowderMedicine();	
//	while(1);
//	
//}
		
//		Angle1_Adjust_Init(25);
//		delay_ms(500);
		
		
//		Angle1_Adjust_Init(3);
//		Angle_Adjust1(18);
//		delay_ms(1000);
		
		
//		Angle1_Adjust_Init(6);
//		Angle_Adjust1(11 );
//		delay_ms(1000);
//		break;
	
	
//	Angle_Adjust1(10);

//	Angle1_Adjust4(20);
//	Angle1_Adjust2(20);
//	Angle1_Adjust3(20);
//	Angle1_Adjust1(3);

	
//�����ַ�����

//ʱ�Ӵ�ӡ����
//LCD_Fill(0,0,20,20,BLACK);
//TimerCountPrint();
//while(1);


//�̶���ӡ
printFixedPart();
//��ӡ�����
printActivePart();




while(1)
	{		
		delay_ms(10);
		timeCount ++;
//		if(KEY_Scan2() == '0') break;	//����ɨ�� �ж�ҩƬ����
		 keyConfirm = KEY_Scan2();
		
		//��ӡ�����
		printActivePart();
		
		
		if(keyConfirm == '0')
		{

			sendOver = sendMedicine();
			if(sendOver=='0')
			{
				//����ҩƬ�������λ
				Angle_Adjust_Init(5);
				
				
				//�ͷۼ�ҩ
				sendPowderMedicine();
			}
		}
		if(timeCount >= 100)	//���ͼ��
		{	
			
			
			DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ	
//		  LCD_ShowNum(82,240,temperature,2,12);	//��ʾ�¶�	  ���״洢bai�¶���10�����£�ʪ����du12%���¡� 		   
//		  LCD_ShowNum(82,260,humidity,2,12);		//��ʾʪ��
		  delay_ms(10);
			temp=temperature;
			hum=humidity;
			;
			
			if(KEY_Scan2() == '0')
		{
			pill4=0;
			sendOver=sendMedicine();
			if(sendOver=='0')
			{
			Angle_Adjust_Init(5);
			}
		}
//	  	p1=pill1;
//			p2=pill2;
//			p3=pill3;
//			p4=pill4;
			OneNet_SendData();	//��������
			timeCount = 0;
			ESP8266_Clear();
			
		}
		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
		{
			OneNet_RevPro(dataPtr);
		}	
			
	}
}	
	
	
	

//	while(1) 
//	{
//		//ѡҩ����
//		while(1)
//		{	
//			if(KEY_Scan2() == '0') break;	//����ɨ�� �ж�ҩƬ����
//		}

//		//��ҩ����
//		sendMedicine();
//	}
//	

	
	
//	delay_ms(3000);
////	MoveHead();
//	OSInit(&err);		//��ʼ��UCOSIII
//	OS_CRITICAL_ENTER();//�����ٽ���
//	//������ʼ����
//	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
//				(CPU_CHAR	* )"start task", 		//��������
//		   (OS_TASK_PTR )start_task, 			//������
//		   (void		* )0,					//���ݸ��������Ĳ���
//		   (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
//		   (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
//		   (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
//		   (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
//		   (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
//		   (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ���
//		   (void   	* )0,					//�û�����Ĵ洢��
//		   (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
//		   (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
//	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
//	OSStart(&err);  //����UCOSIII
//	while(1);
//}


////ʵ��ָ���
////////////////////////////////////////////////////////


////��ʱ��2���жϺ���
//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
//	{
////		LED0=!LED0;
////		LED1=!LED1;
//		transport = transport + 1;
//		if(transport == 6000)
//		{
//			transport = 0;
//		}
//		
//		TimerCount();
//		
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//}

////////////////////////////////////////////////////////

////��ʱ��5���жϺ���
//void TIM5_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM5,TIM_IT_Update)!=RESET)
//	{
//		LED0=!LED0;
//		LED1=!LED1;
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}

//}

////////////////////////////////////////////////////////


////��ʼ������
//void start_task(void *p_arg)
//{
//	OS_ERR err;
//	CPU_SR_ALLOC();
//	p_arg = p_arg;

//	CPU_Init();
//#if OS_CFG_STAT_TASK_EN > 0u
//   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
//#endif
//	
//#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
//    CPU_IntDisMeasMaxCurReset();	
//#endif

//#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
//	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
//	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
//#endif		
//	
////		//������ʱ��1
////	OSTmrCreate((OS_TMR		*)&tmr1,		//��ʱ��1
////                (CPU_CHAR	*)"tmr1",		//��ʱ������
////                (OS_TICK	 )200,			//20*10=200ms
////                (OS_TICK	 )0,          //0*10=0
////                (OS_OPT		 )OS_OPT_TMR_ONE_SHOT, //���ζ�ʱ��
////                (OS_TMR_CALLBACK_PTR)tmr1_callback,//��ʱ��1�ص�����
////                (void	    *)0,			//����Ϊ0
////                (OS_ERR	    *)&err);		//���صĴ�����					
////	//������ʱ��2
////	OSTmrCreate((OS_TMR		*)&tmr2,		
////                (CPU_CHAR	*)"tmr2",		
////                (OS_TICK	 )200,			//200*10=2000ms	
////                (OS_TICK	 )0,   					
////                (OS_OPT		 )OS_OPT_TMR_ONE_SHOT, 	//���ζ�ʱ��
////                (OS_TMR_CALLBACK_PTR)tmr2_callback,	//��ʱ��2�ص�����
////                (void	    *)0,			
////                (OS_ERR	    *)&err);	
//	
//								
//	OS_CRITICAL_ENTER();	//�����ٽ���
//	//������ͼ����
//	OSTaskCreate((OS_TCB 	* )&RUN_TaskTCB,		
//							 (CPU_CHAR	* )"run task", 		
//               (OS_TASK_PTR )run_task, 			
//               (void		* )0,					
//               (OS_PRIO	  )RUN_TASK_PRIO,     
//               (CPU_STK   * )&RUN_TASK_STK[0],	
//               (CPU_STK_SIZE)RUN_STK_SIZE/10,	
//               (CPU_STK_SIZE)RUN_STK_SIZE,		
//               (OS_MSG_QTY  )0,					
//               (OS_TICK	  )2,  //3��ʱ��Ƭ����3*5=15ms					
//               (void   	* )0,					
//               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
//               (OS_ERR 	* )&err);				
//				 
//	//�����Ҷ�ɨ������
//	OSTaskCreate((OS_TCB 	* )&ScanfTaskTCB,		
//				       (CPU_CHAR	* )"scanf task", 		
//               (OS_TASK_PTR )scanf_task, 			
//               (void		* )0,					
//               (OS_PRIO	  )SCANF_TASK_PRIO,     	
//               (CPU_STK   * )&SCANF_TASK_STK[0],	
//               (CPU_STK_SIZE)SCANF_STK_SIZE/10,	
//               (CPU_STK_SIZE)SCANF_STK_SIZE,		
//               (OS_MSG_QTY  )0,					
//               (OS_TICK	  )2,					
//               (void   	* )0,				
//               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
//               (OS_ERR 	* )&err);
//	
//			   
//	//������ʾ��������
//	OSTaskCreate((OS_TCB 	* )&ShowTaskTCB,		
//				       (CPU_CHAR	* )"show task", 		
//               (OS_TASK_PTR )show_task, 			
//               (void		* )0,					
//               (OS_PRIO	  )SHOW_TASK_PRIO,     	
//               (CPU_STK   * )&SHOW_TASK_STK[0],	
//               (CPU_STK_SIZE)SHOW_STK_SIZE/10,	
//               (CPU_STK_SIZE)SHOW_STK_SIZE,		
//               (OS_MSG_QTY  )0,					
//               (OS_TICK	  )2,					
//               (void   	* )0,				
//               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
//               (OS_ERR 	* )&err);				 
//	OS_CRITICAL_EXIT();	//�ٽ���
//	OSTaskDel((OS_TCB*)0,&err);	//ɾ��start_task��������
//}


////��ͼ������
//void run_task(void *p_arg)
//{
//	OS_ERR err;
//	p_arg = p_arg;
//	
//	
//	
//	while(1)
//	{
//		
////		while(1)
////		{
////			Turn_Angle_Big(90);
////			delay_ms(100);
////			Turn_Angle_Big(0);
////			delay_ms(100);
////			Turn_Angle_Big(270);
////			delay_ms(100);
////			Turn_Angle_Big(180);
////			delay_ms(100);
////			while(1){Set_Motor(0,0);}
//////			if(Gray8== 0)
//////			{
//////				zhuanwan_big_right(200);
//////				while(1){Set_Motor(0,0);}
//////			}
////		}
////		while(1)
////		{
//////			Gray_Run40_hou();
////////			Gray_Run60();
////		if(Gray8== 0)
////		{
////			Gray_Run40();
//////			while(1)
//////			{
//////				Gray_Run50();
////////				Turn_Angle_Big(90);		
////////				delay_ms(1000);
////////				Turn_Angle_Big(180);		
////////				delay_ms(1000);
////////				Turn_Angle_Big(270);		
////////				delay_ms(1000);
////////				Turn_Angle_Big(0);		
////////				delay_ms(1000);
//////			}
////		}
////	}
////		while(1)
////		{
////			MoveHand();
////			break;
////		}
////		
////		while(1)
////		{
////			LED0 = 0;
////		}
//		
//		Run2();
//		Set_Motor(0,0);
//		delay_ms(1000);
//		Run2();
//		stop1();
////		Gray_Delay_Run_Taijie2(300);//�Ҷ���ֱ��,���ִ����ٶ�
//		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
//	}
//}


////�Ҷ�ɨ��������
//void scanf_task(void *p_arg)
//{
//	
////	OS_ERR err;  
//	p_arg = p_arg;

//	
////	while(1)
////	{
//////		LED1 = ~LED1;
//////		scanf_obstacles();//�ϰ���⣬·�ڼ��
////		OSTimeDlyHMSM(0,0,0,15,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
////	}
//}


////LCD��ʾ����������
//void show_task(void *p_arg)
//{
////	OS_ERR err;
//	p_arg = p_arg;

////	while(1)
////	{
////		KEY_Scan(0);
////		API_showLCD();
////		scanf_obstacles();
////		OSTimeDlyHMSM(0,0,0,15,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ
////	}
//}

//////��ʱ��1�Ļص�����
////void tmr1_callback(void *p_tmr, void *p_arg)
////{
////	set_speed = 60;
////}

//////��ʱ��2�Ļص�����
////void tmr2_callback(void *p_tmr,void *p_arg)
////{
////	static u8 tmr2_num = 0;
////	tmr2_num++;		//��ʱ��2ִ�д�����1
////	LED1 = ~LED1;
////}

