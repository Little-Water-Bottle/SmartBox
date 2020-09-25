#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 



#define KEY1 		PGin(13)   	//PE4
#define KEY2 		PGin(10)		//PE3 
#define KEY3 		PGin(15)		//P32
#define KEY4 		PBin(3)		//PA0 
#define KEY5 		PFin(8)		//PF8

void KEY_Init(void);	//IO初始化
u8 KEY_Scan(u8);  		//按键扫描函数	
u8 KEY_Scan2();
#endif
