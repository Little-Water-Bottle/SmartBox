#ifndef DEMO_DIO_HOU
#define DEMO_DIO_HOU

#include "DIO.h"
#include "demo_motor.h"




//void Gray_Run(u8 speed);    //(���޸�)2018-10-6
//void Gray_Run_1(u8 speed);
//void Gray_Run15(void);  //�Ҷ�15ֱ���ٶȣ���ɽ��
//void Gray_Run20(void);  //�Ҷȿ���ֱ�߳���  ���ڴӵ�һ����̨�����ã���ֹ��
void Gray_Run20_20_hou(void);//���ڴ����ƽ̨�����ã����
//void Gray_Run25(void);  //�Ҷ�25ֱ���ٶȣ���̨��
//void Gray_Run25gai(void);//�Ҷ�25ֱ���ٶȣ��¸�̨��
//void Gray_Run35(void);//�Ҷ�35ֱ���ٶȣ��¸�̨��
//void Gray_Run_gaotai(void);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ٶȣ��¸�̨��
void Gray_Run30_hou(void);  //�Ҷ�30ֱ���ٶȣ�����ɽ��,��ֹ��
//void Gray_Run30_1(void);
void Gray_Run40_hou(void);  //�Ҷ�40ֱ���ٶ�
//void Gray_Run40gai(void);//�¸�̨��
//void Gray_Run40TaiJie(void);//��ƽ̨
void Gray_Run50_hou(void);  //�Ҷ�50ֱ���ٶ�
void Gray_Run60_hou(void);  //�Ҷ�60ֱ���ٶ�
void Gray_Run70_hou(void);  //�Ҷ�70ֱ���ٶ�
//void Gray_Run80(void);  //�Ҷ�80ֱ���ٶ�
//void Gray_Run_Taijie(void);  //�Ҷȹ�̨��(taijie)
//void Gray_Run_Taijie1(void);  //�Ҷȹ�̨��(taijie)
//void Gray_Run_Jiansuban(void);  //�Ҷȹ����ٰ�(Jiansuban)
//void Gray_Run_Taijie_Speed(int speed);  //�Ҷȹ�̨��(taijie)�����ִ����ٶ�
//void run_c(void);//תȦ
//	
//void run_gray(u16 i,u8 speed);//ֻ�߻Ҷ�Ѳ����������Ӱ��
//void Gray_Down(u16 i);		  //�Ҷ�30/0ֱ���ٶȽ���ʹ�ã��µڶ�����̨��
//void Gray_Down2(u16 i); //�Ҷ�50/0ֱ���ٶȽ���ʹ�ã�����������
//void Gray_Delay_Run15(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬15�ٶ�
//void Gray_Delay_Run15_0(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬15�ٶ�����ٽ���ʹ��
//void Gray_Delay_Run20(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬20�ٶ�
void Gray_Delay_Run20_20_hou(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬20�ٶ�
//int Gray_Delay_Run25(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬25�ٶ�
int Gray_Delay_Run30_hou(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬30�ٶ�

int Gray_Delay_Run40_hou(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬40�ٶ�
int Gray_Delay_Run50_hou(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬50�ٶ�
int Gray_Delay_Run60_hou(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬60�ٶ�
int Gray_Delay_Run70_hou(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬70�ٶ�
//int Gray_Delay_Run25gai(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬25�ٶ�
//int Gray_Delay_Run35(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬35�ٶ�
//int Gray_Delay_Run_Taijie(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬��̨��(taijie)�ٶ�
//int Gray_Delay_Run_Taijie1(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬��̨��(taijie)�ٶ�
//void Gray_Delay_Run_Taijie2(u16 i);  //�Ҷȹ�̨��(taijie),���٣����ٽ��
//int Gray_Delay_Run_Jiansuban(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬�����ٰ�(Jiansuban)�ٶ�
//int Gray_Delay_Run_C(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬תȦ�ٶ�
//void Gray_Delay(void (*a)(),u16 ms);
//void Speed_Delay(u16 i,u16 j,u16 ms);
//void stop1(void);

#endif

