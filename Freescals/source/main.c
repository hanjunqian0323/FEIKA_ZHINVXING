/***********************************************************************
*@Author: sola
*@Date: 2019-11-28 01:33:47
*@FilePath: \FEIKA_ZHINVXING\Freescals\source\main.c
*@Drscription: 
***********************************************************************/
#include "main.h"
extern LED_InitStruct  LED0;
extern LED_InitStruct  LED1;
extern LED_InitStruct  LED2;
extern LED_InitStruct  LED3; 
/***********************************************************************
*@Function: main
*@Input: void
*@Return: none
*@Author: sola
*@Date: 2019-11-28 02:05:44
*@Drscription: 这是main函数，不用多说了吧
***********************************************************************/
int main(void)
{	
	SYSTICK_INIT(176);
	BOARD_InitPins();
	board_clock_init();
	BOARD_InitDebugConsole();
	LED_Init();
	LED_Off(LED0);
	UART_INIT();
	//SCCB_Init();
	ov7725_eagle_reg_init();
	while(1)
	{
		printf("hello");
	}
}

void Error_Handle(void)
{
	while(1);
}
