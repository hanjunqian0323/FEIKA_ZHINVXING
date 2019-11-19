#ifndef	_INCAP_H_
#define _INCAP_H_

#include "main.h"

#define INCAP_INSTANCE				FTM1			//�˿ں�
#define INCAP_CHANNEL0				kFTM_Chnl_0		//ͨ����
#define INCAP_CHANNEL1				kFTM_Chnl_1		//ͨ����
#define INCAP_PORT					PORTA			//���Ŷ˿ں�
#define INCAP_PIN1					8U				//���ź�
#define INCAP_PIN2					9U				//���ź�
#define INCAP_AF					kPORT_MuxAlt3	//����Ϊ���벶��
#define INCAP_CLKSOURCE				kCLOCK_PortA	//�˿�ʱ��
#define INCAP_IRQ					FTM1_IRQn		//�ж�������
#define INCAP_INTERRUPT_HANDLE		FTM1_IRQHandler	//�жϷ�����
#define INCAP_CHANNEL_FLAG			kFTM_Chnl0Flag	//�ж�ͨ����־


void BMQ_INPUTCAP(void);





#endif





