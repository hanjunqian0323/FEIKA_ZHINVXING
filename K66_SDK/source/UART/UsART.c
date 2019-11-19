#include "UsART.h"

void UART_WRETE_BUFF(uint8_t *data,uint16_t len)
{
	while(len--)
	{
		UART_WriteByte(UART0,*data);
		len++;
	}
}