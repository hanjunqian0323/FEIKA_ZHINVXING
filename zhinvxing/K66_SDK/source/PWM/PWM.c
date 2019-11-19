#include "PWM.h"


void PWM_MOTOR_INIT(void)
{
	ftm_config_t FTMconfig;//初始化结构体句柄
	
	CLOCK_EnableClock(FTM_CLKSOURCE);//GPIOB端口时钟初始化
	PORT_SetPinMux(FTM_PORT,FTM_PIN1,FTM_AF);//端口复用为FTM模式
	PORT_SetPinMux(FTM_PORT,FTM_PIN2,FTM_AF);//端口复用为FTM模式

	ftm_chnl_pwm_signal_param_t FTM_PARAM[2];	//初始化参数配置数组
	FTM_PARAM[0].chnlNumber = (ftm_chnl_t)FTM_CHANNAL0;		//配置通道
	FTM_PARAM[0].dutyCyclePercent = 0U;			//初始化的占空比
	FTM_PARAM[0].firstEdgeDelayPercent = 10U;	//死区时间
	FTM_PARAM[0].level = kFTM_HighTrue;			//极性为高电平
	
	FTM_PARAM[1].chnlNumber = (ftm_chnl_t)FTM_CHANNAL1;		//配置通道
	FTM_PARAM[1].dutyCyclePercent = 0U;			//初始化的占空比
	FTM_PARAM[1].firstEdgeDelayPercent = 10U;	//死区时间
	FTM_PARAM[1].level = kFTM_HighTrue;			//极性为高电平
	
	FTM_GetDefaultConfig(&FTMconfig);			//配置重置
	
	FTM_Init(FTM_INSTANCE,&FTMconfig);			//初始化配置
	
	FTM_SetupPwm(FTM_INSTANCE,FTM_PARAM,2U,kFTM_EdgeAlignedPwm,20000,FTM_CLKFREQ());//配置PWM
	
	FTM_StartTimer(FTM_INSTANCE,kFTM_SystemClock);//开启定时器，时钟源配置为系统时钟	
}

void PWM_CHANNEL0_DUTY(uint16_t duty)
{
	FTM_UpdatePwmDutycycle(FTM_INSTANCE,(ftm_chnl_t)FTM_CHANNAL0,kFTM_EdgeAlignedPwm,duty);
	FTM_SetSoftwareTrigger(FTM_INSTANCE,1);
}

void PWM_CHANNEL1_DUTY(uint16_t duty)
{
	FTM_UpdatePwmDutycycle(FTM_INSTANCE,(ftm_chnl_t)FTM_CHANNAL1,kFTM_EdgeAlignedPwm,duty);
	FTM_SetSoftwareTrigger(FTM_INSTANCE,1);
}


void PWM_DUOJI_INIT(void)
{
	ftm_config_t DUOJIconfig;//初始化结构体句柄
	
	CLOCK_EnableClock(DUOJI_CLKSOURCE);//GPIOC端口时钟初始化
	PORT_SetPinMux(DUOJI_PORT,DUOJI_PIN,DUOJI_AF);//端口复用为FTM模式

	ftm_chnl_pwm_signal_param_t DUOJI_PARAM[1];	//初始化参数配置数组
	DUOJI_PARAM[0].chnlNumber = (ftm_chnl_t)DUOJI_CHANNAL;		//配置通道
	DUOJI_PARAM[0].dutyCyclePercent = 0U;			//初始化的占空比
	DUOJI_PARAM[0].firstEdgeDelayPercent = 10U;	//死区时间
	DUOJI_PARAM[0].level = kFTM_HighTrue;			//极性为高电平
	
	FTM_GetDefaultConfig(&DUOJIconfig);			//配置重置
	
	FTM_Init(DUOJI_INSTANCE,&DUOJIconfig);		//初始化配置
	
	//11728=50HZ			70345=300HZ
	FTM_SetupPwm(DUOJI_INSTANCE,DUOJI_PARAM,1U,kFTM_EdgeAlignedPwm,70345,DUOJI_CLKFREQ());//配置PWM
			
	FTM_StartTimer(DUOJI_INSTANCE,kFTM_FixedClock);//开启定时器，时钟源配置为系统时钟
}

void PWM_DUOJI_DUTY(uint16_t duty)
{
	FTM_UpdatePwmDutycycle(DUOJI_INSTANCE,(ftm_chnl_t)DUOJI_CHANNAL,kFTM_EdgeAlignedPwm,duty);
	FTM_SetSoftwareTrigger(DUOJI_INSTANCE,1);
}


