#include "PWM.h"


void PWM_MOTOR_INIT(void)
{
	ftm_config_t FTMconfig;//��ʼ���ṹ����
	
	CLOCK_EnableClock(FTM_CLKSOURCE);//GPIOB�˿�ʱ�ӳ�ʼ��
	PORT_SetPinMux(FTM_PORT,FTM_PIN1,FTM_AF);//�˿ڸ���ΪFTMģʽ
	PORT_SetPinMux(FTM_PORT,FTM_PIN2,FTM_AF);//�˿ڸ���ΪFTMģʽ

	ftm_chnl_pwm_signal_param_t FTM_PARAM[2];	//��ʼ��������������
	FTM_PARAM[0].chnlNumber = (ftm_chnl_t)FTM_CHANNAL0;		//����ͨ��
	FTM_PARAM[0].dutyCyclePercent = 0U;			//��ʼ����ռ�ձ�
	FTM_PARAM[0].firstEdgeDelayPercent = 10U;	//����ʱ��
	FTM_PARAM[0].level = kFTM_HighTrue;			//����Ϊ�ߵ�ƽ
	
	FTM_PARAM[1].chnlNumber = (ftm_chnl_t)FTM_CHANNAL1;		//����ͨ��
	FTM_PARAM[1].dutyCyclePercent = 0U;			//��ʼ����ռ�ձ�
	FTM_PARAM[1].firstEdgeDelayPercent = 10U;	//����ʱ��
	FTM_PARAM[1].level = kFTM_HighTrue;			//����Ϊ�ߵ�ƽ
	
	FTM_GetDefaultConfig(&FTMconfig);			//��������
	
	FTM_Init(FTM_INSTANCE,&FTMconfig);			//��ʼ������
	
	FTM_SetupPwm(FTM_INSTANCE,FTM_PARAM,2U,kFTM_EdgeAlignedPwm,20000,FTM_CLKFREQ());//����PWM
	
	FTM_StartTimer(FTM_INSTANCE,kFTM_SystemClock);//������ʱ����ʱ��Դ����Ϊϵͳʱ��	
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
	ftm_config_t DUOJIconfig;//��ʼ���ṹ����
	
	CLOCK_EnableClock(DUOJI_CLKSOURCE);//GPIOC�˿�ʱ�ӳ�ʼ��
	PORT_SetPinMux(DUOJI_PORT,DUOJI_PIN,DUOJI_AF);//�˿ڸ���ΪFTMģʽ

	ftm_chnl_pwm_signal_param_t DUOJI_PARAM[1];	//��ʼ��������������
	DUOJI_PARAM[0].chnlNumber = (ftm_chnl_t)DUOJI_CHANNAL;		//����ͨ��
	DUOJI_PARAM[0].dutyCyclePercent = 0U;			//��ʼ����ռ�ձ�
	DUOJI_PARAM[0].firstEdgeDelayPercent = 10U;	//����ʱ��
	DUOJI_PARAM[0].level = kFTM_HighTrue;			//����Ϊ�ߵ�ƽ
	
	FTM_GetDefaultConfig(&DUOJIconfig);			//��������
	
	FTM_Init(DUOJI_INSTANCE,&DUOJIconfig);		//��ʼ������
	
	//11728=50HZ			70345=300HZ
	FTM_SetupPwm(DUOJI_INSTANCE,DUOJI_PARAM,1U,kFTM_EdgeAlignedPwm,70345,DUOJI_CLKFREQ());//����PWM
			
	FTM_StartTimer(DUOJI_INSTANCE,kFTM_FixedClock);//������ʱ����ʱ��Դ����Ϊϵͳʱ��
}

void PWM_DUOJI_DUTY(uint16_t duty)
{
	FTM_UpdatePwmDutycycle(DUOJI_INSTANCE,(ftm_chnl_t)DUOJI_CHANNAL,kFTM_EdgeAlignedPwm,duty);
	FTM_SetSoftwareTrigger(DUOJI_INSTANCE,1);
}


