#include "UsART.h"

void UART_Pin_Init(void)
{
//	port_pin_config_t uart_port_config;
//	gpio_pin_config_t gpio_pin_config;
	
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(UART_CLK);
	
	PORT_SetPinMux(UART_PORT,UART_Pin_TX,kPORT_MuxAlt3);
	PORT_SetPinMux(UART_PORT,UART_Pin_RX,kPORT_MuxAlt3);
	
//	uart_port_config.pullSelect = kPORT_PullUp;	
//	uart_port_config.slewRate =kPORT_FastSlewRate;
//	
//	PORT_SetPinConfig(UART_PORT,UART_Pin_RX,&uart_port_config);
//	PORT_SetPinConfig(UART_PORT,UART_Pin_TX,&uart_port_config);
	
//	gpio_pin_config.pinDirection = kGPIO_DigitalOutput;
//	
//	GPIO_PinInit(UART_GPIO,UART_Pin_TX,&gpio_pin_config);
//	GPIO_PinInit(UART_GPIO,UART_Pin_RX,&gpio_pin_config);
}

void UART_INIT(void)
{
	UART_Pin_Init();
	uart_config_t uart_config;
	
	UART_GetDefaultConfig(&uart_config);
	
	uart_config.baudRate_Bps = 115200U;
//	uart_config.parityMode = kUART_ParityDisabled;
//	uart_config.stopBitCount = kUART_OneStopBit;
//	uart_config.txFifoWatermark = 0;
//    uart_config.rxFifoWatermark = 0;
	uart_config.enableRx = true;
	uart_config.enableTx = true;
	
	UART_Init(UART_BASE,&uart_config,CLOCK_GetFreq(BUS_CLK));
	
//	UART_EnableTx(UART_BASE,true);
//	UART_EnableRx(UART_BASE,true);
}


int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口DEBUG_USART */
		UART_WriteByte(UART_BASE, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while ((kUART_TxDataRegEmptyFlag & UART_GetStatusFlags(UART_BASE) )== 0);		
	
		return (ch);
}

///重定向c库函数scanf到串口DEBUG_USART，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while ((kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART_BASE) )== 0);

		return (int)UART_ReadByte(UART_BASE);
}





void UART_WRETE_BUFF(uint8_t *data,uint16_t len)
{
	UART_WriteBlocking(UART_BASE,data,len);
}

void USART_SendData(uint16_t Data)
{
    UART_WriteByte(UART_BASE,(Data & (uint16_t)0x01FF));
}

