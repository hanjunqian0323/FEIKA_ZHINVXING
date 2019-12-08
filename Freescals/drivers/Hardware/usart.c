/***********************************************************************
*@Author: sola
*@Date: 2019-12-04 10:23:58
*@FilePath: \FEIKA_ZHINVXING\Freescals\drivers\Hardware\uart.c
*@Drscription: 
***********************************************************************/
#include "usart.h"

void UART_Pin_Init(void)
{
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(UART_CLK);
	
	PORT_SetPinMux(UART_PORT,UART_Pin_TX,kPORT_MuxAlt3);
	PORT_SetPinMux(UART_PORT,UART_Pin_RX,kPORT_MuxAlt3);
}

void BlueTooes_UART_Init(void)
{
	UART_Pin_Init();
	uart_config_t uart_config;
	
	UART_GetDefaultConfig(&uart_config);
	
	uart_config.baudRate_Bps = 115200U;
	uart_config.enableRx = true;
	uart_config.enableTx = true;
	
	UART_Init(UART_BASE,&uart_config,CLOCK_GetFreq(BUS_CLK));
}


int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ�����DEBUG_USART */
		UART_WriteByte(UART_BASE, (uint8_t) ch);
		/* �ȴ�������� */
		while ((kUART_TxDataRegEmptyFlag & UART_GetStatusFlags(UART_BASE) )== 0);		
	
		return (ch);
}

///�ض���c�⺯��scanf������DEBUG_USART����д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while ((kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART_BASE) )== 0);

		return (int)UART_ReadByte(UART_BASE);
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-12-08 02:31:20
*@Drscription: 
***********************************************************************/
void UART_WriteBuffer(uint8_t *data,uint16_t len)
{
	UART_WriteBlocking(UART_BASE,data,len);
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-12-08 02:31:23
*@Drscription: 
***********************************************************************/
void USART_SendData(uint16_t Data)
{
    UART_WriteByte(UART_BASE,(Data & (uint16_t)0x01FF));
}

