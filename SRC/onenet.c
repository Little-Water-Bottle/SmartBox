//单片机头文件
#include "stm32f4xx.h"

//网络设备
#include "esp8266.h"

//协议文件
#include "onenet.h"
#include "mqttkit.h"
#include "delay.h"
//硬件驱动
#include "usart.h"
#include "DHT11.h"
//C库
#include <string.h>
#include <stdio.h>


#define PROID		"372739"   //产品ID

#define AUTH_INFO	"12345"		//鉴权信息

#define DEVID		"630680477"	//设备ID

extern unsigned char esp8266_buf[128];

//==========================================================
//	函数名称：	OneNet_DevLink
//
//	函数功能：	与onenet创建连接
//
//	入口参数：	无
//
//	返回参数：	1-成功	0-失败
//
//	说明：		与onenet平台建立连接
//==========================================================
_Bool OneNet_DevLink(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};					//协议包

	unsigned char *dataPtr;
	
	_Bool status = 1;
	
	printf("OneNet_DevLink\r\nPROID: %s,	AUIF: %s,	DEVID:%s\r\n", PROID, AUTH_INFO, DEVID);
	
	if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 256, 0, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
	{
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//上传平台
		
		dataPtr = ESP8266_GetIPD(250);									//等待平台响应
		if(dataPtr != NULL)
		{
			if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
			{
				switch(MQTT_UnPacketConnectAck(dataPtr))
				{
					case 0:printf("Tips:	连接成功\r\n");status = 0;break;
					
					case 1:printf("WARN:	连接失败：协议错误\r\n");break;
					case 2:printf("WARN:	连接失败：非法的clientid\r\n");break;
					case 3:printf("WARN:	连接失败：服务器失败\r\n");break;
					case 4:printf("WARN:	连接失败：用户名或密码错误\r\n");break;
					case 5:printf("WARN:	连接失败：非法链接(比如token非法)\r\n");break;
					
					default:printf("ERR:	连接失败：未知错误\r\n");break;
				}
			}
		}
		
		MQTT_DeleteBuffer(&mqttPacket);								//删包
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

u8 p1=0;//药品种类
u8 p2=0;
u8 p3=0;
u8 p4=0;
u8 pi1=0;//药品时间
u8 pi2=0;
u8 pi3=0;
u8 pi4=0;
u8 pil1=0;//药品数量
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
//	函数名称：	OneNet_SendData
//
//	函数功能：	上传数据到平台
//
//	入口参数：	type：发送数据的格式
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_SendData(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};												//协议包
	
	char buf[256];
	
	short body_len = 0, i = 0;
	
//	printf("Tips:	OneNet_SendData-MQTT\r\n");
	
	memset(buf, 0, sizeof(buf));
	
	body_len = OneNet_FillBuf(buf);																	//获取当前需要发送的数据流的总长度
	
	if(body_len)
	{
		if(MQTT_PacketSaveData(DEVID, body_len, NULL, 5, &mqttPacket) == 0)							//封包
		{
			for(; i < body_len; i++)
				mqttPacket._data[mqttPacket._len++] = buf[i];
			
			ESP8266_SendData(mqttPacket._data, mqttPacket._len);									//上传数据到平台
//			printf("Send %d Bytes\r\n", mqttPacket._len);
			
			MQTT_DeleteBuffer(&mqttPacket);															//删包
		}
		else
			printf("WARN:	EDP_NewBuffer Failed\r\n");
	}
	
}

//==========================================================
//	函数名称：	OneNet_RevPro
//
//	函数功能：	平台返回数据检测
//
//	入口参数：	dataPtr：平台返回的数据
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};								//协议包
	
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
		case MQTT_PKT_CMD:															//命令下发
			
			result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len);	//解出topic和消息体
			if(result == 0)
			{
				printf("cmdid: %s, req: %s, req_len: %d\r\n", cmdid_topic, req_payload, req_len);
				
				if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)	//命令回复组包
				{
					printf("Tips:	Send CmdResp\r\n");
					
					ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//回复命令
					MQTT_DeleteBuffer(&mqttPacket);									//删包
				}
			}
		
		break;
			
		case MQTT_PKT_PUBACK:														//发送Publish消息，平台回复的Ack
		
			if(MQTT_UnPacketPublishAck(cmd) == 0)
//				printf("Tips:	MQTT Publish Send OK\r\n");
			
		break;
		
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();									//清空缓存
	
	if(result == -1)
		return;
	
	dataPtr = strchr(req_payload, ':');					//搜索'}'

	if(dataPtr != NULL && result != -1)					//如果找到了
	{
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//判断是否是下发的命令控制数据
		{
			numBuf[num++] = *dataPtr++;
		}
		numBuf[num] = 0;
		
		num = atoi((const char *)numBuf);				//转为数值形式
		
		if(strstr((char *)req_payload, "way1onoff"))		//搜索"onoff"
		{
			printf("way1onoff = %d", num);
			way1 = num;
			
		}
		else if(strstr((char *)req_payload, "way2onoff"))		//搜索"switch"
		{
			printf("way2onoff = %d", num);
			way2 = num;
			
		}
		else if(strstr((char *)req_payload, "way3onoff"))		//搜索"switch"
		{
			printf("way3onoff = %d", num);
			way3 = num;
			
		}
		else if(strstr((char *)req_payload, "p1onoff"))		//搜索"switch"
		{
			printf("p1onoff = %d", num);
			p1 = num;
		}
		else if(strstr((char *)req_payload, "p2onoff"))		//搜索"switch"
		{
			printf("p2onoff = %d", num);
			p2 = num;
		}
		else if(strstr((char *)req_payload, "p3onoff"))		//搜索"switch"
		{
			printf("p3onoff = %d", num);
			p3 = num;
		}
		else if(strstr((char *)req_payload, "p4onoff"))		//搜索"switch"
		{
			printf("p4onoff = %d", num);
			p4 = num;
		}
		else if(strstr((char *)req_payload, "pi1onoff"))		//搜索"switch"
		{
			printf("pi1onoff = %d", num);
			pi1 = num;
		}
		else if(strstr((char *)req_payload, "pi2onoff"))		//搜索"switch"
		{
			printf("pi2onoff = %d", num);
			pi2 = num;
		}
		else if(strstr((char *)req_payload, "pi3onoff"))		//搜索"switch"
		{
			printf("pi3onoff = %d", num);
			pi3 = num;
		}
		else if(strstr((char *)req_payload, "pi4onoff"))		//搜索"switch"
		{
			printf("pi4onoff = %d", num);
			pi4 = num;
		}
		else if(strstr((char *)req_payload, "pil1onoff"))		//搜索"switch"
		{
			printf("pil1onoff = %d", num);
			pil1 = num;
		}
		else if(strstr((char *)req_payload, "pil2onoff"))		//搜索"switch"
		{
			printf("pil2onoff = %d", num);
			pil2 = num;
		}
		else if(strstr((char *)req_payload, "pil3onoff"))		//搜索"switch"
		{
			printf("pil3onoff = %d", num);
			pil3 = num;
		}
		else if(strstr((char *)req_payload, "pil4onoff"))		//搜索"switch"
		{
			printf("pil4onoff = %d", num);
			pil4 = num;
		}
		else if(strstr((char *)req_payload, "confirmonoff"))		//搜索"switch"
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
						p1=0;//药品种类
						p2=0;
						p3=0;
						p4=0;
						pi1=0;//药品时间
						pi2=0;
						pi3=0;
						pi4=0;
						pil1=0;//药品数量
						pil2=0;
						pil3=0;
						pil4=0;
						
				
					
			
			}
		}
		else if(strstr((char *)req_payload, "resetonoff"))		//搜索"switch"
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
						p1=0;//药品种类
						p2=0;
						p3=0;
						p4=0;
						pi1=0;//药品时间
						pi2=0;
						pi3=0;
						pi4=0;
						pil1=0;//药品数量
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
