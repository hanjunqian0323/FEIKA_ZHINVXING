#include "ADC.h"

//uint32_t Valu = 0;
//float Valu_vo = 0;

void ADC_PORT_INIT(void)//ADC�˿�ʱ�ӳ�ʼ����˿ڸ���
{
	CLOCK_EnableClock(kCLOCK_PortA);//ʹ�ܶ˿�ʱ��
	CLOCK_EnableClock(kCLOCK_PortC);//ʹ�ܶ˿�ʱ��
	PORT_SetPinMux(ADC1_PORT,ADC1_PIN,kPORT_PinDisabledOrAnalog);//�˿ڸ���ΪADCģʽ
	PORT_SetPinMux(ADC2_PORT,ADC2_PIN,kPORT_PinDisabledOrAnalog);//�˿ڸ���ΪADCģʽ
}

void ADC_CONFIG(void)//ADC����
{
	adc16_config_t ADCconfig;//����ADC��ʼ�����
	
	ADC16_GetDefaultConfig(&ADCconfig);//��������
	
	ADCconfig.resolution = kADC16_ResolutionSE12Bit;//ADC�ֱ���Ϊ12λ
	ADCconfig.enableContinuousConversion = true;//ʹ����������ģʽ
	ADC16_Init(ADC0_INSTANCE,&ADCconfig);//��ʼ��
	
	ADC16_EnableHardwareTrigger(ADC0_INSTANCE,false);//ʹ��Ӳ����
	//ADC16_SetHardwareAverage(ADC_INSTANCE,kADC16_HardwareAverageCount32);//����ADCӲ����ƽ��ֵ
}
	
void ADC_CHANNEL_CONFIG(void)//ADCͨ������
{
	adc16_channel_config_t ADCCHANNELconfig;//����ADCͨ����ʼ�����
	ADCCHANNELconfig.channelNumber = ADC1_CHANNEL;	
	ADCCHANNELconfig.enableInterruptOnConversionCompleted = false;//ʹ��ת������ж�
	ADC16_SetChannelConfig(ADC0_INSTANCE,ADC1_CHANNEL_GROUP,&ADCCHANNELconfig);//ͨ������
	
	ADCCHANNELconfig.channelNumber = ADC2_CHANNEL;
	ADC16_SetChannelConfig(ADC0_INSTANCE,ADC2_CHANNEL_GROUP,&ADCCHANNELconfig);//ͨ������
	/*if(ADC16_DoAutoCalibration(ADC_INSTANCE)==kStatus_Success)//Ӳ��У׼
	{
		PRINTF("HardWere Calibration sucessful!\n");
	}
	else
	{
		PRINTF("HardWere Calibration error!\n");
	}*/
}

/*void ADC_NVIC_INIT(void)//ADC���ж�����
{
	__NVIC_SetPriority(ADC0_IRQn,0);//�����ж����ȼ�
	__NVIC_EnableIRQ(ADC0_IRQn);//ʹ���ж�
}*/

void ADC_INIT(void)//ADC��ʼ��
{
	ADC_PORT_INIT();
	ADC_CONFIG();
	ADC_CHANNEL_CONFIG();
	//ADC_NVIC_INIT();
}


/*void ADC0_IRQHandler(void)//�жϷ�����
{
	if(ADC16_GetStatusFlags(ADC_INSTANCE))
	{			
		Valu = ADC16_GetChannelConversionValue(ADC_INSTANCE,ADC_CHANNEL_GROUP);//��ȡADC��ֵ
		PRINTF(" Valu = %d",Valu);	
		Valu_vo = ((float)Valu)*(float)3.3/(float)4096;
		PRINTF("		Volote = %f\n",Valu_vo);
		ADC16_ClearStatusFlags(ADC_INSTANCE,kADC16_ChannelMuxA);
	}
}*/

