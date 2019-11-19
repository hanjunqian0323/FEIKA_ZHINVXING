#include "INCAP.h"

uint8_t i = 0;
uint32_t count = 0;

void BMQ_INPUTCAP(void)
{
	ftm_config_t INCAPconfig;//��ʼ���ṹ����
	
	CLOCK_EnableClock(INCAP_CLKSOURCE);//����ʱ�ӳ�ʼ��
	PORT_SetPinMux(INCAP_PORT,INCAP_PIN1,INCAP_AF);//�˿ڸ���Ϊ���벶��ģʽ
	PORT_SetPinMux(INCAP_PORT,INCAP_PIN2,INCAP_AF);//�˿ڸ���Ϊ���벶��ģʽ
	
	FTM_GetDefaultConfig(&INCAPconfig);//��ʼ������
	FTM_Init(INCAP_INSTANCE,&INCAPconfig);//��ʼ��
	
	FTM_SetupInputCapture(INCAP_INSTANCE,INCAP_CHANNEL0,kFTM_RisingEdge,0);//�������벶��
	FTM_SetupInputCapture(INCAP_INSTANCE,INCAP_CHANNEL1,kFTM_RisingEdge,0);//�������벶��
	
	INCAP_INSTANCE->MOD = 0xffff;//��������ģʽ
	
	FTM_EnableInterrupts(INCAP_INSTANCE,kFTM_Chnl0InterruptEnable);	//ѡ���ж�ͨ��Ϊͨ��0
	
	EnableIRQ(INCAP_IRQ);//ʹ���ж�
	
	FTM_StartTimer(INCAP_INSTANCE, kFTM_SystemClock);//������ʱ��������ʱ��ԴΪϵͳʱ��
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
		FTM_ClearStatusFlags(INCAP_INSTANCE,INCAP_CHANNEL_FLAG);//���ͨ���ı�־λ	
		//(INCAP_INSTANCE->STATUS & 0x01) = 0;
	}
	//__DSB();
}



