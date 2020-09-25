#ifndef _LED_H
#define _LED_H
#include "sys.h"


//LED端口定义
#define LED0 PEout(3)
#define LED1 PEout(4)

void LED_Init(void);  //初始化
#endif
