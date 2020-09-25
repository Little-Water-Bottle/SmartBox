#ifndef _ONENET_H_
#define _ONENET_H_


extern u8 temp;   	    
extern u8 hum; 


_Bool OneNet_DevLink(void);

void OneNet_SendData(void);
void OneNet_SendCmd(void);
void OneNet_RevPro(unsigned char *cmd);

#endif
