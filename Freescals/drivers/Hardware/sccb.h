/***********************************************************************
*@Author: sola
*@Date: 2019-12-03 22:48:08
*@FilePath: \FEIKA_ZHINVXING\Freescals\drivers\Hardware\sccb.h
*@Drscription: 
***********************************************************************/

#include "main.h"

#ifndef __sccb_h
#define __sccb_h

#define SCCB_SCL_PIN        26U
#define SCCB_SDA_PIN        25U

#define SCCB_SDA_PORT       PORTA
#define SCCB_SCL_PORT       PORTA

#define SCCB_SCL_GPIO       GPIOA
#define SCCB_SDA_GPIO       GPIOA

#define SCCB_SCL_CLK        kCLOCK_PortA
#define SCCB_SDA_CLK        kCLOCK_PortA

#define SCCB_SCL_OUT_H()    GPIO_PinWrite(SCCB_SCL_GPIO, SCCB_SCL_PIN, 1U)
#define SCCB_SCL_OUT_L()    GPIO_PinWrite(SCCB_SCL_GPIO, SCCB_SCL_PIN, 0U)
#define SCCB_SDA_OUT_H()    GPIO_PinWrite(SCCB_SDA_GPIO, SCCB_SDA_PIN, 1U)
#define SCCB_SDA_OUT_L()    GPIO_PinWrite(SCCB_SDA_GPIO, SCCB_SDA_PIN, 0U)

#define SCCB_SDA_IN()       GPIO_PinRead(SCCB_SDA_GPIO, SCCB_SDA_PIN)


#define ADDR_OV7725         0x42
#define DEV_ADR             ADDR_OV7725


void SCCB_Delay(__IO uint32_t tim);
bool SCCB_Init(void);
void SCCB_MODE_CHANGE(uint8_t mode);
bool SCCB_Start(void);
bool SCCB_Stop(void);
bool SCCB_Ack(void);
bool SCCB_NoAck(void);
bool SCCB_WaitAck(void);
bool SCCB_SendByte(uint8_t SendByte);
uint8_t SCCB_ReceiveByte(void);
int SCCB_WriteByte_one( uint16_t WriteAddress , uint8_t SendByte );
int SCCB_WriteByte( uint16_t WriteAddress , uint8_t SendByte );
int SCCB_ReadByte_one(uint8_t *pBuffer,   uint16_t length,   uint8_t ReadAddress);
int SCCB_ReadByte(uint8_t *pBuffer,uint16_t length,uint8_t ReadAddress);

#endif /* !__sccb_h */
