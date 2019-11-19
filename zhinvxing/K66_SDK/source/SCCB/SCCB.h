#ifndef _SCCB_H_
#define _SCCB_H_

#include "main.h"

//����
#define SCCB_PORT			PORTA
#define SCCB_GPIO			GPIOA
#define SCCB_SCL_PIN		26U
#define SCCB_SDA_PIN		25U

//OV7725��ַ
#define DEV_ADR  			ADDR_OV7725             /*�豸��ַ����*/
#define ADDR_OV7725 		0x42

//����
#define SCCB_DELAY()		SCCB_delay(400)//��ʱ

#define SDA_DDR_IN()		SDA_LOGIC_CHANGE(0)//�ı�SDAΪ����ģʽ
#define SDA_DDR_OUT()		SDA_LOGIC_CHANGE(1)//�ı�SDAΪ���ģʽ

#define SDA_H()				GPIO_PinWrite(SCCB_GPIO,SCCB_SDA_PIN,1)//SDA = 1
#define SDA_L()				GPIO_PinWrite(SCCB_GPIO,SCCB_SDA_PIN,0)//SDA = 0

#define SCL_H()				GPIO_PinWrite(SCCB_GPIO,SCCB_SCL_PIN,1)//SCL = 1
#define SCL_L()				GPIO_PinWrite(SCCB_GPIO,SCCB_SCL_PIN,0)//SCL = 0

#define SDA_IN()			GPIO_PinRead(SCCB_GPIO,SCCB_SDA_PIN)

static void SCCB_delay(volatile uint16_t time);
void SCCB_GPIO_init(void);
void SDA_LOGIC_CHANGE(uint8_t LOGIC);
static void SCCB_Ack(void);
static void SCCB_NoAck(void);
int SCCB_ReadByte(uint8_t *pBuffer,   uint16_t length,   uint8_t ReadAddress);
int SCCB_ReadByte_one(uint8_t *pBuffer,   uint16_t length,   uint8_t ReadAddress);
static int SCCB_ReceiveByte(void);
static void SCCB_SendByte(uint8_t SendByte);
static uint8_t SCCB_Start(void);
static void SCCB_Stop(void);
static int SCCB_WaitAck(void);
int SCCB_WriteByte( uint16_t WriteAddress , uint8_t SendByte )  ;
int SCCB_WriteByte_one( uint16_t WriteAddress , uint8_t SendByte );


#endif



