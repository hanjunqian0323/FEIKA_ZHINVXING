#ifndef _PWM_H_
#define _PWM_H_

#include "main.h"

//电机
#define	FTM_CLKSOURCE		kCLOCK_PortC
#define FTM_AF				kPORT_MuxAlt4	//复用功能
#define FTM_INSTANCE		FTM0	//FTM端口
#define FTM_CHANNAL0		0U		//FTM通道
#define FTM_CHANNAL1		1U		//FTM通道
#define FTM_CLKFREQ()		CLOCK_GetFreq(kCLOCK_BusClk)	//获取总线时钟频率
#define FTM_PORT			PORTC	//PORT端口
#define FTM_PIN1			1U		//PWM引脚
#define FTM_PIN2			2U		//PWM引脚

//舵机
#define DUOJI_CLKSOURCE		kCLOCK_PortC
#define DUOJI_AF			kPORT_MuxAlt3
#define DUOJI_INSTANCE		FTM3
#define DUOJI_CHANNAL		7U
#define DUOJI_CLKFREQ()		CLOCK_GetFreq(kCLOCK_BusClk)
#define DUOJI_PORT			PORTC
#define DUOJI_PIN			11U

//电机
void PWM_MOTOR_INIT(void);
void PWM_CHANNEL0_DUTY(uint16_t duty);	//PWM1
void PWM_CHANNEL1_DUTY(uint16_t duty);	//PWM2

//舵机		PTC1
void PWM_DUOJI_INIT(void);
void PWM_DUOJI_DUTY(uint16_t duty);	//舵机PWM



#endif



