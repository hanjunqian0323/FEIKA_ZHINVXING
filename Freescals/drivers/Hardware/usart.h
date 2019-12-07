/***********************************************************************
*@Author: sola
*@Date: 2019-12-04 10:23:58
*@FilePath: \FEIKA_ZHINVXING\driver_source\UART\UsART.h
*@Drscription: 
***********************************************************************/
#ifndef _USART_H_
#define _USART_H_

#include "main.h"

#define UART_CLK					kCLOCK_Uart4
#define UART_GPIO					GPIOC
#define UART_PORT					PORTC
#define UART_Pin_TX					15U
#define UART_Pin_RX					14U
#define UART_BASE					UART4




//º¯ÊýÉùÃ÷
void UART_Pin_Init(void);
void BlueTooes_UART_Init(void);
void UART_WriteBuffer(uint8_t *data,uint16_t len);
void USART_SendData(uint16_t Data);





#endif /* ! _USART_H_ */

