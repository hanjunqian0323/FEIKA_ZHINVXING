#ifndef _ADC_H_
#define _ADC_H_


#include "main.h"


#define ADC0_INSTANCE				ADC0
#define ADC1_INSTANCE				ADC1
//ADC通道1：
#define ADC1_GPIO					GPIOA
#define ADC1_PORT					PORTA
#define ADC1_PIN					7U
#define ADC1_CHANNEL				10U	
#define ADC1_CHANNEL_GROUP			0U		//通道组，最多8个（0-7）

//ADC通道2：
#define ADC2_GPIO					GPIOC
#define ADC2_PORT					PORTC
#define ADC2_PIN					0U
#define ADC2_CHANNEL				14U	
#define ADC2_CHANNEL_GROUP			0U		//通道组，最多8个（0-7）


void ADC_PORT_INIT(void);//ADC端口时钟初始化与端口复用
void ADC_GPIO_INIT(void);//ADC引脚的GPIO初始化
void ADC_CONFIG(void);//ADC配置
void ADC_CHANNEL_CONFIG(void);//ADC通道配置
void ADC_NVIC_INIT(void);//ADC的中断配置
void ADC_INIT(void);//ADC初始化




#endif

