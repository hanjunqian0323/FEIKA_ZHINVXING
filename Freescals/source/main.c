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
	/*
	*@初始化系统时钟
	*@初始化IO引脚（UART0--A1,UART0--A2），开启PORT时钟
	*@初始化调试串口----UART0,115200,8,None,1
	*/
    BOARD_InitBootClocks();
    BOARD_InitPins();
    BOARD_InitDebugConsole();
    
	PRINTF("\r\n");
	PRINTF("/***********************************/\n");
    PRINTF("CORE:            %d MHz\r\n", CLOCK_GetFreq(kCLOCK_CoreSysClk)/1000000);
    PRINTF("BUS:             %d MHz\r\n", CLOCK_GetFreq(kCLOCK_BusClk)/1000000);
    PRINTF("FlexBus:         %d MHz\r\n", CLOCK_GetFreq(kCLOCK_FlexBusClk)/1000000);
	PRINTF("/***********************************/\n");

	SYSTICK_INIT(CLOCK_GetFreq(kCLOCK_CoreSysClk)/1000000);

	LED_Init();
	ov7725_eagle_reg_init();

	while(1)
	{
		LED_On(LED0);
		DELAY_MS(500);
		LED_Off(LED0);
		DELAY_MS(500);
	}
}

void Error_Handle(void)
{
	while(1);
}

