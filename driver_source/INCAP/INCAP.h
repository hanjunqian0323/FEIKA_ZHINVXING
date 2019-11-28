#ifndef	_INCAP_H_
#define _INCAP_H_

#include "main.h"

#define INCAP_INSTANCE				FTM1			//端口号
#define INCAP_CHANNEL0				kFTM_Chnl_0		//通道号
#define INCAP_CHANNEL1				kFTM_Chnl_1		//通道号
#define INCAP_PORT					PORTA			//引脚端口号
#define INCAP_PIN1					8U				//引脚号
#define INCAP_PIN2					9U				//引脚号
#define INCAP_AF					kPORT_MuxAlt3	//复用为输入捕获
#define INCAP_CLKSOURCE				kCLOCK_PortA	//端口时钟
#define INCAP_IRQ					FTM1_IRQn		//中断向量号
#define INCAP_INTERRUPT_HANDLE		FTM1_IRQHandler	//中断服务函数
#define INCAP_CHANNEL_FLAG			kFTM_Chnl0Flag	//中断通道标志


void BMQ_INPUTCAP(void);





#endif





