#include "PIT.h"

uint16_t PIT_COUNT0 = 0;
uint16_t PIT_COUNT1 = 0;
void PIT_INIT(void)
{
    pit_config_t config;//�����ʼ�����
    
    CLOCK_EnableClock(kCLOCK_Pit0);//PITʱ�ӳ�ʼ��
    
    config.enableRunInDebug = true;//����ʱPIT��������
    PIT_Init(PIT,&config);//��ʼ��
    
    PIT_SetTimerPeriod(PIT,PIT_CHANNAL0,USEC_TO_COUNT(PIT_DELAY0,PIT_SOURCE_CLOCK));//���ö�ʱʱ��
    PIT_EnableInterrupts(PIT,PIT_CHANNAL0,kPIT_TimerInterruptEnable);//ʹ���ж�
    
    EnableIRQ(PIT_INTERRUPT_CHANNEL0);//ʹ�ܶ�ʱ���ж�
    PIT_StartTimer(PIT, PIT_CHANNAL0);//������ʱ��
    
    PIT_SetTimerPeriod(PIT,PIT_CHANNAL1,USEC_TO_COUNT(PIT_DELAY1,PIT_SOURCE_CLOCK));//���ö�ʱʱ��
    PIT_EnableInterrupts(PIT,PIT_CHANNAL1,kPIT_TimerInterruptEnable);//ʹ���ж�
    EnableIRQ(PIT_INTERRUPT_CHANNEL1);//ʹ�ܶ�ʱ���ж�
    PIT_StartTimer(PIT, PIT_CHANNAL1);//������ʱ��
    
}

void PIT_INTERRUPTHANDLE0(void)//�жϷ�����0
{
    PIT_ClearStatusFlags(PIT, PIT_CHANNAL0, kPIT_TimerFlag);//����жϱ�־λ
    if(PIT_COUNT0>50000)PIT_COUNT0 = 0;
    PIT_COUNT0++;
    if(PIT_COUNT0%2)GPIO_PinWrite(LED_GPIOINSTANCE,LED1,OFF);
    else GPIO_PinWrite(LED_GPIOINSTANCE,LED1,ON);   
}

void PIT_INTERRUPTHANDLE1(void)//�жϷ�����1
{
    PIT_ClearStatusFlags(PIT, PIT_CHANNAL1, kPIT_TimerFlag);//����жϱ�־λ
    if(PIT_COUNT1>50000)PIT_COUNT1 = 0;
    PIT_COUNT1++;
    if(PIT_COUNT1%2)GPIO_PinWrite(LED_GPIOINSTANCE,LED2,OFF);
    else GPIO_PinWrite(LED_GPIOINSTANCE,LED2,ON);   
}


