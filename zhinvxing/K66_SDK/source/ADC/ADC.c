#include "ADC.h"

//uint32_t Valu = 0;
//float Valu_vo = 0;

void ADC_PORT_INIT(void)//ADC端口时钟初始化与端口复用
{
	CLOCK_EnableClock(kCLOCK_PortA);//使能端口时钟
	CLOCK_EnableClock(kCLOCK_PortC);//使能端口时钟
	PORT_SetPinMux(ADC1_PORT,ADC1_PIN,kPORT_PinDisabledOrAnalog);//端口复用为ADC模式
	PORT_SetPinMux(ADC2_PORT,ADC2_PIN,kPORT_PinDisabledOrAnalog);//端口复用为ADC模式
}

void ADC_CONFIG(void)//ADC配置
{
	adc16_config_t ADCconfig;//定义ADC初始化句柄
	
	ADC16_GetDefaultConfig(&ADCconfig);//配置重置
	
	ADCconfig.resolution = kADC16_ResolutionSE12Bit;//ADC分辨率为12位
	ADCconfig.enableContinuousConversion = true;//使能连续采样模式
	ADC16_Init(ADC0_INSTANCE,&ADCconfig);//初始化
	
	ADC16_EnableHardwareTrigger(ADC0_INSTANCE,false);//使能硬件流
	//ADC16_SetHardwareAverage(ADC_INSTANCE,kADC16_HardwareAverageCount32);//设置ADC硬件求平均值
}
	
void ADC_CHANNEL_CONFIG(void)//ADC通道配置
{
	adc16_channel_config_t ADCCHANNELconfig;//定义ADC通道初始化句柄
	ADCCHANNELconfig.channelNumber = ADC1_CHANNEL;	
	ADCCHANNELconfig.enableInterruptOnConversionCompleted = false;//使能转换完成中断
	ADC16_SetChannelConfig(ADC0_INSTANCE,ADC1_CHANNEL_GROUP,&ADCCHANNELconfig);//通道配置
	
	ADCCHANNELconfig.channelNumber = ADC2_CHANNEL;
	ADC16_SetChannelConfig(ADC0_INSTANCE,ADC2_CHANNEL_GROUP,&ADCCHANNELconfig);//通道配置
	/*if(ADC16_DoAutoCalibration(ADC_INSTANCE)==kStatus_Success)//硬件校准
	{
		PRINTF("HardWere Calibration sucessful!\n");
	}
	else
	{
		PRINTF("HardWere Calibration error!\n");
	}*/
}

/*void ADC_NVIC_INIT(void)//ADC的中断配置
{
	__NVIC_SetPriority(ADC0_IRQn,0);//设置中断优先级
	__NVIC_EnableIRQ(ADC0_IRQn);//使能中断
}*/

void ADC_INIT(void)//ADC初始化
{
	ADC_PORT_INIT();
	ADC_CONFIG();
	ADC_CHANNEL_CONFIG();
	//ADC_NVIC_INIT();
}


/*void ADC0_IRQHandler(void)//中断服务函数
{
	if(ADC16_GetStatusFlags(ADC_INSTANCE))
	{			
		Valu = ADC16_GetChannelConversionValue(ADC_INSTANCE,ADC_CHANNEL_GROUP);//获取ADC的值
		PRINTF(" Valu = %d",Valu);	
		Valu_vo = ((float)Valu)*(float)3.3/(float)4096;
		PRINTF("		Volote = %f\n",Valu_vo);
		ADC16_ClearStatusFlags(ADC_INSTANCE,kADC16_ChannelMuxA);
	}
}*/

