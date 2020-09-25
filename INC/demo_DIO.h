#ifndef DEMO_DIO
#define DEMO_DIO

#include "DIO.h"
#include "demo_motor.h"

#define Gray1		PFin(6) //��������8 GPIO9
#define Gray2		PFin(5) //��������7 GPIO8
#define Gray3		PFin(4) //��������6 GPIO7
#define Gray4		PFin(2) //��������5 GPIO6

#define Gray5		PEin(5) //��������4 GPIO2
#define Gray6		PEin(6) //��������3 GPIO3
#define Gray7		PFin(0) //��������2 GPIO4
#define Gray8		PFin(1) //��������1 GPIO5

#define Gray88		PEin(2) //��������88 GPIO1
#define Gray77		PEin(1) //��������77 GPIO16
#define Gray66		PBin(9) //��������66 GPIO15
#define Gray55		PBin(8) //��������55 GPIO14

#define Gray44		PBin(4) //��������44 GPIO10
#define Gray33		PBin(5) //��������33 GPIO11
#define Gray22		PBin(6) //��������22 GPIO12
#define Gray11		PBin(7) //��������11 GPIO13



#define Infrared_DIO1  PDin(11)//ǰ����DIO1���͵�ƽ��Ч��˳ʱ��ѡ���������
#define Infrared_DIO2  PDin(7) //�����DIO2���͵�ƽ��Ч
#define L_DIO3 PFin(7)//��С�Ҷ�DIO3���͵�ƽ��Ч��˳ʱ��ѡ���������
#define R_DIO4 PFin(8)//��С�Ҷ�DIO4���͵�ƽ��Ч
#define queue PDin(2)

#define ETR1 PEin(0)//�����
#define ETR2 PAin(5)//�Һ���
#define ETR3 PDin(2)
#define ETR4 PAin(12)

void Gray_Go(u8 speed);//������

void Run1(void);//��һ��·��
void Run2(void);//�ڶ���·��
void Run_wwt_1(void);

int Gray(int number);//�жϻҶȵڼ�������
int Gray_Count(void);//�Ҷ����Ƽ���

void Gray_Run(u8 speed);    //(���޸�)2018-10-6
void Gray_Run_1(u8 speed);
void Gray_Run15(void);  //�Ҷ�15ֱ���ٶȣ���ɽ��
void Gray_Run20(void);  //�Ҷȿ���ֱ�߳���  ���ڴӵ�һ����̨�����ã���ֹ��
void Gray_Run20_20(void);//���ڴ����ƽ̨�����ã����
void Gray_Run25(void);  //�Ҷ�25ֱ���ٶȣ���̨��
void Gray_Run25gai(void);//�Ҷ�25ֱ���ٶȣ��¸�̨��
void Gray_Run35(void);//�Ҷ�35ֱ���ٶȣ��¸�̨��
void Gray_Run_gaotai(void);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬���ٶȣ��¸�̨��
void Gray_Run30(void);  //�Ҷ�30ֱ���ٶȣ�����ɽ��,��ֹ��
void Gray_Run30_1(void);
void Gray_Run40(void);  //�Ҷ�40ֱ���ٶ�
void Gray_Run40gai(void);//�¸�̨��
void Gray_Run40TaiJie(void);//��ƽ̨
void Gray_Run50(void);  //�Ҷ�50ֱ���ٶ�
void Gray_Run60(void);  //�Ҷ�60ֱ���ٶ�
void Gray_Run70(void);  //�Ҷ�70ֱ���ٶ�
void Gray_Run80(void);  //�Ҷ�80ֱ���ٶ�
void Gray_Run_Taijie(void);  //�Ҷȹ�̨��(taijie)
void Gray_Run_Taijie1(void);  //�Ҷȹ�̨��(taijie)
void Gray_Run_Jiansuban(void);  //�Ҷȹ����ٰ�(Jiansuban)
void Gray_Run_Taijie_Speed(int speed);  //�Ҷȹ�̨��(taijie)�����ִ����ٶ�
void run_c(void);//תȦ
	
void run_gray(u16 i,u8 speed);//ֻ�߻Ҷ�Ѳ����������Ӱ��
void Gray_Down(u16 i);		  //�Ҷ�30/0ֱ���ٶȽ���ʹ�ã��µڶ�����̨��
void Gray_Down2(u16 i); //�Ҷ�50/0ֱ���ٶȽ���ʹ�ã�����������
void Gray_Delay_Run15(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬15�ٶ�
void Gray_Delay_Run15_0(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬15�ٶ�����ٽ���ʹ��
void Gray_Delay_Run20(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬20�ٶ�
void Gray_Delay_Run20_20(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬20�ٶ�
int Gray_Delay_Run25(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬25�ٶ�
int Gray_Delay_Run30(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬30�ٶ�

int Gray_Delay_Run40(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬40�ٶ�
int Gray_Delay_Run50(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬50�ٶ�
int Gray_Delay_Run60(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬60�ٶ�
int Gray_Delay_Run70(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬70�ٶ�
int Gray_Delay_Run25gai(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬25�ٶ�
int Gray_Delay_Run35(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬35�ٶ�
int Gray_Delay_Run_Taijie(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬��̨��(taijie)�ٶ�
int Gray_Delay_Run_Taijie1(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬��̨��(taijie)�ٶ�
void Gray_Delay_Run_Taijie2(u16 i);  //�Ҷȹ�̨��(taijie),���٣����ٽ��
int Gray_Delay_Run_Jiansuban(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬�����ٰ�(Jiansuban)�ٶ�
int Gray_Delay_Run_C(u16 i);//ֻ�߻Ҷ�Ѳ�������������Ӱ�죬תȦ�ٶ�
void Gray_Delay(void (*a)(),u16 ms);
void Speed_Delay(u16 i,u16 j,u16 ms);
void stop1(void);

void Gray_Run2(u8 speed);//�Ҷ�������
void Gray_curve(u8 speed);//�Ҷ�������
void Gray_Curve0(u8 speed);//ǰ�Ҷ�������
void Front_Gray_Curve_L50_Turn(u8 speed);//ǰ�Ҷ�������ת������֤��
void Gray_Climb(u8 speed);//�Ҷ�����
void Gray_Run4(u8 speed);//�����ٴ�

void Gray_L37_Turn(void);//�Ҷ���ת�䣬���ִ���ת�ĽǶ�
void Gray_L_Turn(u8 speed,int angle);//�Ҷ���ת��
void Gray_L1_Turn(u8 speed);//�Ҷ���ת��
void Gray_L2_Turn(u8 speed);//�Ҷ���ת��
void Gray_L3_Turn(u8 speed);//�Ҷ���ת��
void Gray_L70_Turn(u8 speed);//�Ҷ�ֱ����ת

void Gray_R37_Turn(void);//�Ҷ���ת�䣬���ִ���ת�ĽǶ�
void Gray_R_Turn(u8 speed,int angle);//�Ҷ���ת��
void Gray_R1_Turn(u8 speed,int angle);//�Ҷ���ת��
void Gray_R2_Turn(u8 speed,int angle);//�Ҷ���ת��
void Gray_R3_Turn(u8 speed);//�Ҷ���ת��
void Gray_R4_Turn(u8 speed);//�Ҷ���ת��
void Gray_R50_Turn(u8 speed);//ǰ�Ҷ�ֱ����ת
void Gray_More90_R_Turn(u8 speed);//ǰ�Ҷȳ���90�ȻҶ�ֱ����ת������֤��

void Gray_B1_Turn(u8 speed,int angle);//��̺ת��

void Speed_Down(void);//���ٷ���
void Brake_Stop(void);//ɲ������


void Detect_obstacles_front(void);//�ж�ǰ���Ƿ����ϰ���
void Gray_scanf(void);//����С�Ҷ�ɨ��

void star_gray(void); //����ɨ���ϰ���
void scanf_obstacles(void);//ɨ���ϰ���
void back_scenic(void);//�������㷵��

int gray_light_amount(void);
void infrared_35(void);
void zhuanwan_big_left(int time);
void zhuanwan_big_right(int time);

#endif

