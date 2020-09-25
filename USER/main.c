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
//自行添加
#include "counterInit.h"
#include "Greay_Init2.h"
#include "sendMedicine.h"
#include "DHT11.h"
#include "esp8266.h"
#include "onenet.h"
#include "lcd.h"
#include "TimeCount.h"



//任务优先级
#define START_TASK_PRIO		3
//任务堆栈大小	
#define START_STK_SIZE 		128
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//任务优先级
#define RUN_TASK_PRIO		4
//任务堆栈大小	
#define RUN_STK_SIZE 		512
//任务控制块
OS_TCB RUN_TaskTCB;
//任务堆栈	
CPU_STK RUN_TASK_STK[RUN_STK_SIZE];
void run_task(void *p_arg);

//任务优先级
#define SCANF_TASK_PRIO		4
//任务堆栈大小	
#define SCANF_STK_SIZE 		128
//任务控制块
OS_TCB ScanfTaskTCB;
//任务堆栈	
CPU_STK SCANF_TASK_STK[SCANF_STK_SIZE];
//任务函数
void scanf_task(void *p_arg);

//任务优先级
#define SHOW_TASK_PRIO		4
//任务堆栈大小	
#define SHOW_STK_SIZE 		512
//任务控制块
OS_TCB ShowTaskTCB;
//任务堆栈	
CPU_STK SHOW_TASK_STK[SHOW_STK_SIZE];
//任务函数
void show_task(void *p_arg);

//OS_TMR 	tmr1;		//定时器1
//OS_TMR	tmr2;		//定时器2
//void tmr1_callback(void *p_tmr, void *p_arg); 	//定时器1回调函数
//void tmr2_callback(void *p_tmr, void *p_arg);	//定时器2回调函数

extern int set_speed;
extern int flag_turn;
extern int flag_obstacles;
extern int stop;
extern int flag_obstacles_front;
extern struct pid1	pid;
extern int transport;	//给时钟计时传递数值
extern u8 temp;   	    
extern u8 hum; 
extern u8 reset;//重置
extern u8 way1;//确认
extern int pill1;//函数内药片数量
extern int pill2;
extern int pill3;
extern int pill4;

extern u8 way1;//选药模式模式
extern u8 way2;
extern u8 way3;
extern u8 p1;//上传数据药品种类
extern u8 p2;
extern u8 p3;
extern u8 p4;
extern u8 pi1;//上传数据药品时间
extern u8 pi2;
extern u8 pi3;
extern u8 pi4;
extern u8 pil1;//上传数据药品数量
extern u8 pil2;
extern u8 pil3;
extern u8 pil4;

u8 sendOver;	//送药结束标志
u8 keyConfirm;	//确认键按下标志
int main(void)
{
	u8 temperature=0;  	    
	u8 humidity=0; 

unsigned char *dataPtr = NULL;
	unsigned short timeCount = 300;	//发送间隔变量
//	unsigned short timeCount = 300;	//发送间隔变量
//	Stm32_Clock_Init(336,8,2,7); //系统时钟设置
	delay_init(168);	  //延时函数初始化
// 	motor_configuration(0);//电机初始化函数一个舵机初始化
	TIM5_PWM_Init(200-1,16800-1);
	LED_Init ();//小灯初始化函数
	BEEP_Init();//蜂鸣器初始化函数
//	noise_Init();//声音模块初始化函数
	uart_init(115200);//串口1初始化函数
//	counterInit();	//计数器初始化
//	TIM2_Init(65535);
//	TIM3_Init(65535);
// 	TIM6_Init(5000-1,8400-1);
	TIM8_PWM_Init(200-1,16800-1);
//	fan_Init(5);//风扇电机初始化函数	
	Infrared_sensor_Init();//红外传感初始化函数
	usart3_init(42,115200);		//串口3初始化
	delay_ms(3000);
	
	LCD_Init();
	DHT11_Init();
	Greay_Init2();
	KEY_Init();
	POINT_COLOR=RED;  
	Angle_Adjust_Init(5);	//所有舵机初始位置初始化
	delay_ms(500);
//	ESP8266_Init();					//初始化ESP8266
//	while(OneNet_DevLink())			//接入OneNET
		delay_ms(500);
//	LED0=0;  //LED0开
//	LED1=0;  //LED1开
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
////		//选药过程
////		while(1)
////		{	
////			if(KEY_Scan2() == '0') break;	//按键扫描 判断药片数量
////			LCD_ShowNum(82,180,pill1,2,12);
////	   	LCD_ShowNum(82,200,pill2,2,12);
////	  	LCD_ShowNum(82,220,pill3,2,12);
////		}

////		//送药过程
////		i=sendMedicine();
////		if(i=='0')
////		{
////			Angle_Adjust_Init(5);
////		}
////		
//		
//		}


//药包割药测试
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

	
//中文字符测试

//时钟打印测试
//LCD_Fill(0,0,20,20,BLACK);
//TimerCountPrint();
//while(1);


//固定打印
printFixedPart();
//打印活动部分
printActivePart();




while(1)
	{		
		delay_ms(10);
		timeCount ++;
//		if(KEY_Scan2() == '0') break;	//按键扫描 判断药片数量
		 keyConfirm = KEY_Scan2();
		
		//打印活动部分
		printActivePart();
		
		
		if(keyConfirm == '0')
		{

			sendOver = sendMedicine();
			if(sendOver=='0')
			{
				//送完药片，舵机归位
				Angle_Adjust_Init(5);
				
				
				//送粉剂药
				sendPowderMedicine();
			}
		}
		if(timeCount >= 100)	//发送间隔
		{	
			
			
			DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值	
//		  LCD_ShowNum(82,240,temperature,2,12);	//显示温度	  大米存储bai温度在10℃以下，湿度在du12%以下。 		   
//		  LCD_ShowNum(82,260,humidity,2,12);		//显示湿度
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
			OneNet_SendData();	//发送数据
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
//		//选药过程
//		while(1)
//		{	
//			if(KEY_Scan2() == '0') break;	//按键扫描 判断药片数量
//		}

//		//送药过程
//		sendMedicine();
//	}
//	

	
	
//	delay_ms(3000);
////	MoveHead();
//	OSInit(&err);		//初始化UCOSIII
//	OS_CRITICAL_ENTER();//进入临界区
//	//创建开始任务
//	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
//				(CPU_CHAR	* )"start task", 		//任务名字
//		   (OS_TASK_PTR )start_task, 			//任务函数
//		   (void		* )0,					//传递给任务函数的参数
//		   (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
//		   (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
//		   (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
//		   (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
//		   (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
//		   (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度
//		   (void   	* )0,					//用户补充的存储区
//		   (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
//		   (OS_ERR 	* )&err);				//存放该函数错误时的返回值
//	OS_CRITICAL_EXIT();	//退出临界区	 
//	OSStart(&err);  //开启UCOSIII
//	while(1);
//}


////实验分割线
////////////////////////////////////////////////////////


////定时器2的中断函数
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

////定时器5的中断函数
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


////开始任务函数
//void start_task(void *p_arg)
//{
//	OS_ERR err;
//	CPU_SR_ALLOC();
//	p_arg = p_arg;

//	CPU_Init();
//#if OS_CFG_STAT_TASK_EN > 0u
//   OSStatTaskCPUUsageInit(&err);  	//统计任务                
//#endif
//	
//#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
//    CPU_IntDisMeasMaxCurReset();	
//#endif

//#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
//	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
//	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
//#endif		
//	
////		//创建定时器1
////	OSTmrCreate((OS_TMR		*)&tmr1,		//定时器1
////                (CPU_CHAR	*)"tmr1",		//定时器名字
////                (OS_TICK	 )200,			//20*10=200ms
////                (OS_TICK	 )0,          //0*10=0
////                (OS_OPT		 )OS_OPT_TMR_ONE_SHOT, //单次定时器
////                (OS_TMR_CALLBACK_PTR)tmr1_callback,//定时器1回调函数
////                (void	    *)0,			//参数为0
////                (OS_ERR	    *)&err);		//返回的错误码					
////	//创建定时器2
////	OSTmrCreate((OS_TMR		*)&tmr2,		
////                (CPU_CHAR	*)"tmr2",		
////                (OS_TICK	 )200,			//200*10=2000ms	
////                (OS_TICK	 )0,   					
////                (OS_OPT		 )OS_OPT_TMR_ONE_SHOT, 	//单次定时器
////                (OS_TMR_CALLBACK_PTR)tmr2_callback,	//定时器2回调函数
////                (void	    *)0,			
////                (OS_ERR	    *)&err);	
//	
//								
//	OS_CRITICAL_ENTER();	//进入临界区
//	//创建跑图任务
//	OSTaskCreate((OS_TCB 	* )&RUN_TaskTCB,		
//							 (CPU_CHAR	* )"run task", 		
//               (OS_TASK_PTR )run_task, 			
//               (void		* )0,					
//               (OS_PRIO	  )RUN_TASK_PRIO,     
//               (CPU_STK   * )&RUN_TASK_STK[0],	
//               (CPU_STK_SIZE)RUN_STK_SIZE/10,	
//               (CPU_STK_SIZE)RUN_STK_SIZE,		
//               (OS_MSG_QTY  )0,					
//               (OS_TICK	  )2,  //3个时间片，既3*5=15ms					
//               (void   	* )0,					
//               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
//               (OS_ERR 	* )&err);				
//				 
//	//创建灰度扫描任务
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
//	//创建显示数据任务
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
//	OS_CRITICAL_EXIT();	//临界区
//	OSTaskDel((OS_TCB*)0,&err);	//删除start_task任务自身
//}


////跑图任务函数
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
////		Gray_Delay_Run_Taijie2(300);//灰度走直线,数字代表速度
//		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_HMSM_STRICT,&err); //延时
//	}
//}


////灰度扫描任务函数
//void scanf_task(void *p_arg)
//{
//	
////	OS_ERR err;  
//	p_arg = p_arg;

//	
////	while(1)
////	{
//////		LED1 = ~LED1;
//////		scanf_obstacles();//障碍检测，路口检测
////		OSTimeDlyHMSM(0,0,0,15,OS_OPT_TIME_HMSM_STRICT,&err); //延时
////	}
//}


////LCD显示数据任务函数
//void show_task(void *p_arg)
//{
////	OS_ERR err;
//	p_arg = p_arg;

////	while(1)
////	{
////		KEY_Scan(0);
////		API_showLCD();
////		scanf_obstacles();
////		OSTimeDlyHMSM(0,0,0,15,OS_OPT_TIME_HMSM_STRICT,&err); //延时
////	}
//}

//////定时器1的回调函数
////void tmr1_callback(void *p_tmr, void *p_arg)
////{
////	set_speed = 60;
////}

//////定时器2的回调函数
////void tmr2_callback(void *p_tmr,void *p_arg)
////{
////	static u8 tmr2_num = 0;
////	tmr2_num++;		//定时器2执行次数加1
////	LED1 = ~LED1;
////}

