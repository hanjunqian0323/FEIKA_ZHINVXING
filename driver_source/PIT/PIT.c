#include "PIT.h"

uint16_t PIT_COUNT0 = 0;
uint16_t PIT_COUNT1 = 0;
void PIT_INIT(void)
{
    pit_config_t config;//定义初始化句柄
    
    CLOCK_EnableClock(kCLOCK_Pit0);//PIT时钟初始化
    
    config.enableRunInDebug = true;//调试时PIT正常运行
    PIT_Init(PIT,&config);//初始化
    
    PIT_SetTimerPeriod(PIT,PIT_CHANNAL0,USEC_TO_COUNT(PIT_DELAY0,PIT_SOURCE_CLOCK));//设置定时时间
    PIT_EnableInterrupts(PIT,PIT_CHANNAL0,kPIT_TimerInterruptEnable);//使能中断
    
    EnableIRQ(PIT_INTERRUPT_CHANNEL0);//使能定时器中断
    PIT_StartTimer(PIT, PIT_CHANNAL0);//开启定时器
    
    PIT_SetTimerPeriod(PIT,PIT_CHANNAL1,USEC_TO_COUNT(PIT_DELAY1,PIT_SOURCE_CLOCK));//设置定时时间
    PIT_EnableInterrupts(PIT,PIT_CHANNAL1,kPIT_TimerInterruptEnable);//使能中断
    EnableIRQ(PIT_INTERRUPT_CHANNEL1);//使能定时器中断
    PIT_StartTimer(PIT, PIT_CHANNAL1);//开启定时器
    
}

void PIT_INTERRUPTHANDLE0(void)//中断服务函数0
{
    PIT_ClearStatusFlags(PIT, PIT_CHANNAL0, kPIT_TimerFlag);//清楚中断标志位
    if(PIT_COUNT0>50000)PIT_COUNT0 = 0;
    PIT_COUNT0++;
    if(PIT_COUNT0%2)GPIO_PinWrite(LED_GPIOINSTANCE,LED1,OFF);
    else GPIO_PinWrite(LED_GPIOINSTANCE,LED1,ON);   
}

void PIT_INTERRUPTHANDLE1(void)//中断服务函数1
{
    PIT_ClearStatusFlags(PIT, PIT_CHANNAL1, kPIT_TimerFlag);//清楚中断标志位
    if(PIT_COUNT1>50000)PIT_COUNT1 = 0;
    PIT_COUNT1++;
    if(PIT_COUNT1%2)GPIO_PinWrite(LED_GPIOINSTANCE,LED2,OFF);
    else GPIO_PinWrite(LED_GPIOINSTANCE,LED2,ON);   
}


