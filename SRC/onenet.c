//��Ƭ��ͷ�ļ�
#include "stm32f4xx.h"

//�����豸
#include "esp8266.h"

//Э���ļ�
#include "onenet.h"
#include "mqttkit.h"
#include "delay.h"
//Ӳ������
#include "usart.h"
#include "DHT11.h"
//C��
#include <string.h>
#include <stdio.h>


#define PROID		"372739"   //��ƷID

#define AUTH_INFO	"12345"		//��Ȩ��Ϣ

#define DEVID		"630680477"	//�豸ID

extern unsigned char esp8266_buf[128];

//==========================================================
//	�������ƣ�	OneNet_DevLink
//
//	�������ܣ�	��onenet��������
//
//	��ڲ�����	��
//
//	���ز�����	1-�ɹ�	0-ʧ��
//
//	˵����		��onenetƽ̨��������
//==========================================================
_Bool OneNet_DevLink(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};					//Э���

	unsigned char *dataPtr;
	
	_Bool status = 1;
	
	printf("OneNet_DevLink\r\nPROID: %s,	AUIF: %s,	DEVID:%s\r\n", PROID, AUTH_INFO, DEVID);
	
	if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 256, 0, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
	{
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//�ϴ�ƽ̨
		
		dataPtr = ESP8266_GetIPD(250);									//�ȴ�ƽ̨��Ӧ
		if(dataPtr != NULL)
		{
			if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
			{
				switch(MQTT_UnPacketConnectAck(dataPtr))
				{
					case 0:printf("Tips:	���ӳɹ�\r\n");status = 0;break;
					
					case 1:printf("WARN:	����ʧ�ܣ�Э�����\r\n");break;
					case 2:printf("WARN:	����ʧ�ܣ��Ƿ���clientid\r\n");break;
					case 3:printf("WARN:	����ʧ�ܣ�������ʧ��\r\n");break;
					case 4:printf("WARN:	����ʧ�ܣ��û������������\r\n");break;
					case 5:printf("WARN:	����ʧ�ܣ��Ƿ�����(����token�Ƿ�)\r\n");break;
					
					default:printf("ERR:	����ʧ�ܣ�δ֪����\r\n");break;
				}
			}
		}
		
		MQTT_DeleteBuffer(&mqttPacket);								//ɾ��
	}
	else
		printf("WARN:	MQTT_PacketConnect Failed\r\n");
	
	return status;
	
}
u8 velue0 = 0;
u8 velue1 = 0;
u8 temp=2;   	    
u8 hum=3;
u8 confirm=0;
u8 reset=0;

u8 way1=0;
u8 way2=0;
u8 way3=0;

u8 mode=0;
u8 medicine1=0;
u8 medicine2=0;
u8 medicine3=0;
u8 medicine4=0;
u8 time=0;
u8 count=0;

u8 p1=0;//ҩƷ����
u8 p2=0;
u8 p3=0;
u8 p4=0;
u8 pi1=0;//ҩƷʱ��
u8 pi2=0;
u8 pi3=0;
u8 pi4=0;
u8 pil1=0;//ҩƷ����
u8 pil2=0;
u8 pil3=0;
u8 pil4=0;
u8 message[20]={0};

unsigned char OneNet_FillBuf(char *buf)
{
	
	char text[64];
	
	
	memset(text, 0, sizeof(text));
	
	strcpy(buf, ",;");
		
	memset(text, 0, sizeof(text));
	sprintf(text, "confirm,%d;", confirm);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "reset,%d;", reset);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "mode,%d;", mode);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "medicine1,%d;", medicine1);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "medicine2,%d;", medicine2);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "medicine3,%d;", medicine3);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "medicine4,%d;", medicine4);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "time,%d;", time);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "count,%d;", count);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "temp,%d;", temp);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "hum,%d;", hum);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "way1,%d;", way1);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "way2,%d;", way2);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "way3,%d;", way3);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "p1,%d;", p1);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "p2,%d;", p2);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "p3,%d;", p3);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "p4,%d;", p4);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "pi1,%d;", pi1);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "pi2,%d;", pi2);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "pi3,%d;", pi3);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "pi4,%d;",pi4);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "pil1,%d;",pil1);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "pil2,%d;",pil2);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "pil3,%d;",pil3);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "pil4,%d;",pil4);
	strcat(buf, text);
	

	
	
	return strlen(buf);
}

//==========================================================
//	�������ƣ�	OneNet_SendData
//
//	�������ܣ�	�ϴ����ݵ�ƽ̨
//
//	��ڲ�����	type���������ݵĸ�ʽ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_SendData(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};												//Э���
	
	char buf[256];
	
	short body_len = 0, i = 0;
	
//	printf("Tips:	OneNet_SendData-MQTT\r\n");
	
	memset(buf, 0, sizeof(buf));
	
	body_len = OneNet_FillBuf(buf);																	//��ȡ��ǰ��Ҫ���͵����������ܳ���
	
	if(body_len)
	{
		if(MQTT_PacketSaveData(DEVID, body_len, NULL, 5, &mqttPacket) == 0)							//���
		{
			for(; i < body_len; i++)
				mqttPacket._data[mqttPacket._len++] = buf[i];
			
			ESP8266_SendData(mqttPacket._data, mqttPacket._len);									//�ϴ����ݵ�ƽ̨
//			printf("Send %d Bytes\r\n", mqttPacket._len);
			
			MQTT_DeleteBuffer(&mqttPacket);															//ɾ��
		}
		else
			printf("WARN:	EDP_NewBuffer Failed\r\n");
	}
	
}

//==========================================================
//	�������ƣ�	OneNet_RevPro
//
//	�������ܣ�	ƽ̨�������ݼ��
//
//	��ڲ�����	dataPtr��ƽ̨���ص�����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};								//Э���
	
	char *req_payload = NULL;
	char *cmdid_topic = NULL;
	
	unsigned short req_len = 0;
	
	unsigned char type = 0;
	
	short result = 0;

	char *dataPtr = NULL;
	char numBuf[10];
	int num = 0;
	
	type = MQTT_UnPacketRecv(cmd);
	switch(type)
	{
		case MQTT_PKT_CMD:															//�����·�
			
			result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len);	//���topic����Ϣ��
			if(result == 0)
			{
				printf("cmdid: %s, req: %s, req_len: %d\r\n", cmdid_topic, req_payload, req_len);
				
				if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)	//����ظ����
				{
					printf("Tips:	Send CmdResp\r\n");
					
					ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//�ظ�����
					MQTT_DeleteBuffer(&mqttPacket);									//ɾ��
				}
			}
		
		break;
			
		case MQTT_PKT_PUBACK:														//����Publish��Ϣ��ƽ̨�ظ���Ack
		
			if(MQTT_UnPacketPublishAck(cmd) == 0)
//				printf("Tips:	MQTT Publish Send OK\r\n");
			
		break;
		
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();									//��ջ���
	
	if(result == -1)
		return;
	
	dataPtr = strchr(req_payload, ':');					//����'}'

	if(dataPtr != NULL && result != -1)					//����ҵ���
	{
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//�ж��Ƿ����·��������������
		{
			numBuf[num++] = *dataPtr++;
		}
		numBuf[num] = 0;
		
		num = atoi((const char *)numBuf);				//תΪ��ֵ��ʽ
		
		if(strstr((char *)req_payload, "way1onoff"))		//����"onoff"
		{
			printf("way1onoff = %d", num);
			way1 = num;
			
		}
		else if(strstr((char *)req_payload, "way2onoff"))		//����"switch"
		{
			printf("way2onoff = %d", num);
			way2 = num;
			
		}
		else if(strstr((char *)req_payload, "way3onoff"))		//����"switch"
		{
			printf("way3onoff = %d", num);
			way3 = num;
			
		}
		else if(strstr((char *)req_payload, "p1onoff"))		//����"switch"
		{
			printf("p1onoff = %d", num);
			p1 = num;
		}
		else if(strstr((char *)req_payload, "p2onoff"))		//����"switch"
		{
			printf("p2onoff = %d", num);
			p2 = num;
		}
		else if(strstr((char *)req_payload, "p3onoff"))		//����"switch"
		{
			printf("p3onoff = %d", num);
			p3 = num;
		}
		else if(strstr((char *)req_payload, "p4onoff"))		//����"switch"
		{
			printf("p4onoff = %d", num);
			p4 = num;
		}
		else if(strstr((char *)req_payload, "pi1onoff"))		//����"switch"
		{
			printf("pi1onoff = %d", num);
			pi1 = num;
		}
		else if(strstr((char *)req_payload, "pi2onoff"))		//����"switch"
		{
			printf("pi2onoff = %d", num);
			pi2 = num;
		}
		else if(strstr((char *)req_payload, "pi3onoff"))		//����"switch"
		{
			printf("pi3onoff = %d", num);
			pi3 = num;
		}
		else if(strstr((char *)req_payload, "pi4onoff"))		//����"switch"
		{
			printf("pi4onoff = %d", num);
			pi4 = num;
		}
		else if(strstr((char *)req_payload, "pil1onoff"))		//����"switch"
		{
			printf("pil1onoff = %d", num);
			pil1 = num;
		}
		else if(strstr((char *)req_payload, "pil2onoff"))		//����"switch"
		{
			printf("pil2onoff = %d", num);
			pil2 = num;
		}
		else if(strstr((char *)req_payload, "pil3onoff"))		//����"switch"
		{
			printf("pil3onoff = %d", num);
			pil3 = num;
		}
		else if(strstr((char *)req_payload, "pil4onoff"))		//����"switch"
		{
			printf("pil4onoff = %d", num);
			pil4 = num;
		}
		else if(strstr((char *)req_payload, "confirmonoff"))		//����"switch"
		{
			printf("confirmonoff = %d", num);
			confirm = num;
			if(confirm==1)
			{
				
				message[0]=way1;
				message[1]=way2;
				message[2]=way3;
				message[3]=p1;
				message[4]=p2;
				message[5]=p3;
				message[6]=p4;
				message[7]=pi1;
				message[8]=pi2;
				message[9]=pi3;
				message[10]=pi4;
				message[11]=pil1;
				message[12]=pil1;
				message[13]=pil1;
				message[14]=pil1;
				if(way1==1)
				{
					mode=1;
				}
				if(way2==2)
				{
					mode=2;
				}
				if(way3==3)
				{
					mode=3;
				}
				medicine1=p1;
				medicine2=p2;
				medicine3=p3;
				medicine4=p4;
						reset=0;
						confirm=0;
						way1=0;
						way2=0;
						way3=0;
						p1=0;//ҩƷ����
						p2=0;
						p3=0;
						p4=0;
						pi1=0;//ҩƷʱ��
						pi2=0;
						pi3=0;
						pi4=0;
						pil1=0;//ҩƷ����
						pil2=0;
						pil3=0;
						pil4=0;
						
				
					
			
			}
		}
		else if(strstr((char *)req_payload, "resetonoff"))		//����"switch"
		{
			printf("resetonoff = %d", num);
			reset = num;
			if(reset==1)
			{
				u8 temp=2;   	    
						confirm=0;
						way1=0;
						way2=0;
						way3=0;
						p1=0;//ҩƷ����
						p2=0;
						p3=0;
						p4=0;
						pi1=0;//ҩƷʱ��
						pi2=0;
						pi3=0;
						pi4=0;
						pil1=0;//ҩƷ����
						pil2=0;
						pil3=0;
						pil4=0;
			}
		}
		

		
	}

	if(type == MQTT_PKT_CMD || type == MQTT_PKT_PUBLISH)
	{
		MQTT_FreeBuffer(cmdid_topic);
		MQTT_FreeBuffer(req_payload);
	}

}
