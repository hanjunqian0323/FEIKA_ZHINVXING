#include "INCAP.h"

uint8_t i = 0;
uint32_t count = 0;

void BMQ_INPUTCAP(void)
{
	ftm_config_t INCAPconfig;//初始化结构体句柄
	
	CLOCK_EnableClock(INCAP_CLKSOURCE);//引脚时钟初始化
	PORT_SetPinMux(INCAP_PORT,INCAP_PIN1,INCAP_AF);//端口复用为输入捕获模式
	PORT_SetPinMux(INCAP_PORT,INCAP_PIN2,INCAP_AF);//端口复用为输入捕获模式
	
	FTM_GetDefaultConfig(&INCAPconfig);//初始化配置
	FTM_Init(INCAP_INSTANCE,&INCAPconfig);//初始化
	
	FTM_SetupInputCapture(INCAP_INSTANCE,INCAP_CHANNEL0,kFTM_RisingEdge,0);//配置输入捕获
	FTM_SetupInputCapture(INCAP_INSTANCE,INCAP_CHANNEL1,kFTM_RisingEdge,0);//配置输入捕获
	
	INCAP_INSTANCE->MOD = 0xffff;//空闲运行模式
	
	FTM_EnableInterrupts(INCAP_INSTANCE,kFTM_Chnl0InterruptEnable);	//选择中断通道为通道0
	
	EnableIRQ(INCAP_IRQ);//使能中断
	
	FTM_StartTimer(INCAP_INSTANCE, kFTM_SystemClock);//开启定时器，配置时钟源为系统时钟
}

void INCAP_INTERRUPT_HANDLE(void)
{
	//if((FTM_GetStatusFlags(INCAP_INSTANCE) & INCAP_CHANNEL_FLAG) == INCAP_CHANNEL_FLAG)
	if((INCAP_INSTANCE->STATUS & 0x01)==1)
	{		
//		i++;
		//count = INCAP_INSTANCE->CONTROLS[INCAP_CHANNEL0].CnV;
	    count++;
		//count += FTM_GetCurrentTimerCount(INCAP_INSTANCE);
//		if(i>=5)
//		{

//			i=0;
//		}
		FTM_ClearStatusFlags(INCAP_INSTANCE,INCAP_CHANNEL_FLAG);//清除通道的标志位	
		//(INCAP_INSTANCE->STATUS & 0x01) = 0;
	}
	//__DSB();
}



