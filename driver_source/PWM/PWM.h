#ifndef _PWM_H_
#define _PWM_H_

#include "main.h"

//���
#define	FTM_CLKSOURCE		kCLOCK_PortC
#define FTM_AF				kPORT_MuxAlt4	//���ù���
#define FTM_INSTANCE		FTM0	//FTM�˿�
#define FTM_CHANNAL0		0U		//FTMͨ��
#define FTM_CHANNAL1		1U		//FTMͨ��
#define FTM_CLKFREQ()		CLOCK_GetFreq(kCLOCK_BusClk)	//��ȡ����ʱ��Ƶ��
#define FTM_PORT			PORTC	//PORT�˿�
#define FTM_PIN1			1U		//PWM����
#define FTM_PIN2			2U		//PWM����

//���
#define DUOJI_CLKSOURCE		kCLOCK_PortC
#define DUOJI_AF			kPORT_MuxAlt3
#define DUOJI_INSTANCE		FTM3
#define DUOJI_CHANNAL		7U
#define DUOJI_CLKFREQ()		CLOCK_GetFreq(kCLOCK_BusClk)
#define DUOJI_PORT			PORTC
#define DUOJI_PIN			11U

//���
void PWM_MOTOR_INIT(void);
void PWM_CHANNEL0_DUTY(uint16_t duty);	//PWM1
void PWM_CHANNEL1_DUTY(uint16_t duty);	//PWM2

//���		PTC1
void PWM_DUOJI_INIT(void);
void PWM_DUOJI_DUTY(uint16_t duty);	//���PWM



#endif



