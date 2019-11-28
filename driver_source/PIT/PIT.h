#ifndef _PIT_H_
#define _PIT_H_


#include "main.h"

#define PIT_CHANNAL0             kPIT_Chnl_0 //通道0
#define PIT_DELAY0               750000      //500MS
#define PIT_SOURCE_CLOCK         CLOCK_GetFreq(kCLOCK_BusClk)//获取定时器时钟源频率

#define PIT_INTERRUPT_CHANNEL0   PIT0_IRQn       //中断向量号
#define PIT_INTERRUPTHANDLE0     PIT0_IRQHandler //中断服务函数

#define PIT_CHANNAL1             kPIT_Chnl_1 //通道0
#define PIT_DELAY1               500000      //<500MS
#define PIT_INTERRUPT_CHANNEL1   PIT1_IRQn       //中断向量号
#define PIT_INTERRUPTHANDLE1     PIT1_IRQHandler //中断服务函数


void PIT_INIT(void);

#endif






