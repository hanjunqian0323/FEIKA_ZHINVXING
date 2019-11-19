#ifndef _ADC_H_
#define _ADC_H_


#include "main.h"


#define ADC0_INSTANCE				ADC0
#define ADC1_INSTANCE				ADC1
//ADCͨ��1��
#define ADC1_GPIO					GPIOA
#define ADC1_PORT					PORTA
#define ADC1_PIN					7U
#define ADC1_CHANNEL				10U	
#define ADC1_CHANNEL_GROUP			0U		//ͨ���飬���8����0-7��

//ADCͨ��2��
#define ADC2_GPIO					GPIOC
#define ADC2_PORT					PORTC
#define ADC2_PIN					0U
#define ADC2_CHANNEL				14U	
#define ADC2_CHANNEL_GROUP			0U		//ͨ���飬���8����0-7��


void ADC_PORT_INIT(void);//ADC�˿�ʱ�ӳ�ʼ����˿ڸ���
void ADC_GPIO_INIT(void);//ADC���ŵ�GPIO��ʼ��
void ADC_CONFIG(void);//ADC����
void ADC_CHANNEL_CONFIG(void);//ADCͨ������
void ADC_NVIC_INIT(void);//ADC���ж�����
void ADC_INIT(void);//ADC��ʼ��




#endif

