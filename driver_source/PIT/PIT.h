#ifndef _PIT_H_
#define _PIT_H_


#include "main.h"

#define PIT_CHANNAL0             kPIT_Chnl_0 //ͨ��0
#define PIT_DELAY0               750000      //500MS
#define PIT_SOURCE_CLOCK         CLOCK_GetFreq(kCLOCK_BusClk)//��ȡ��ʱ��ʱ��ԴƵ��

#define PIT_INTERRUPT_CHANNEL0   PIT0_IRQn       //�ж�������
#define PIT_INTERRUPTHANDLE0     PIT0_IRQHandler //�жϷ�����

#define PIT_CHANNAL1             kPIT_Chnl_1 //ͨ��0
#define PIT_DELAY1               500000      //<500MS
#define PIT_INTERRUPT_CHANNEL1   PIT1_IRQn       //�ж�������
#define PIT_INTERRUPTHANDLE1     PIT1_IRQHandler //�жϷ�����


void PIT_INIT(void);

#endif






