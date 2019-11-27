#ifndef _DELAY_H_
#define _DELAY_H_


#include "main.h"

void SYSTICK_INIT(uint16_t freq);	//滴答初始化配置
void DELAY_MS(uint32_t MS);			//MS延时函数
void DELAY_US(uint32_t US);			//US延时函数








#endif

