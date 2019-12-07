#ifndef _UsART_H_
#define _UsART_H_

#include "main.h"

#define UART_CLK					kCLOCK_Uart4
#define UART_GPIO					GPIOC
#define UART_PORT					PORTC
#define UART_Pin_TX					15U
#define UART_Pin_RX					14U
#define UART_BASE					UART4


void UART_Pin_Init(void);
void UART_INIT(void);






//º¯ÊýÉùÃ÷
void UART_WRETE_BUFF(uint8_t *data,uint16_t len);
void USART_SendData(uint16_t Data);





#endif

