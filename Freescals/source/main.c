/*
 * @Author: your name
 * @Date: 2019-11-28 17:35:28
 * @LastEditTime: 2019-12-10 21:03:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \FEIKA_ZHINVXING\Freescals\source\main.c
 */
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


#define OV7725_SIZE				(80 * 60/8 )
uint8_t imgbuffer[OV7725_SIZE];

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
	uint8_t i = 0;
	/*
	*@初始化系统时钟
	*@初始化IO引脚（UART0--A1,UART0--A2），开启PORT时钟
	*@初始化调试串口----UART0,115200,8,None,1
	*/
    BOARD_InitBootClocks();
    BOARD_InitPins();
    BOARD_InitDebugConsole();

    BlueTooes_UART_Init();
	

	SYSTICK_INIT(CLOCK_GetFreq(kCLOCK_CoreSysClk)/1000000);

	LED_Init();
	//ov7725_eagle_reg_init();
	ov7725_eagle_init(imgbuffer);//摄像头初始化
	ov7725_eagle_get_img();//获取图像
	for(i=0;i<80*60;i++)
	DEBUG_PRINTF("%c",imgbuffer[i]);
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

#if 0
#if defined(USA_Fire_DAP)
	PRINTF("\r\n");
	PRINTF("/***********************************/\n");
    PRINTF("CORE:            %d MHz\r\n", CLOCK_GetFreq(kCLOCK_CoreSysClk)/1000000);
    PRINTF("BUS:             %d MHz\r\n", CLOCK_GetFreq(kCLOCK_BusClk)/1000000);
    PRINTF("FlexBus:         %d MHz\r\n", CLOCK_GetFreq(kCLOCK_FlexBusClk)/1000000);
	PRINTF("/***********************************/\n");
	#elif defined(USA_Jlink)
	printf("\r\n");
	printf("/***********************************/\n");
    printf("CORE:            %d MHz\r\n", CLOCK_GetFreq(kCLOCK_CoreSysClk)/1000000);
    printf("BUS:             %d MHz\r\n", CLOCK_GetFreq(kCLOCK_BusClk)/1000000);
    printf("FlexBus:         %d MHz\r\n", CLOCK_GetFreq(kCLOCK_FlexBusClk)/1000000);
	printf("/***********************************/\n");
	#endif
#endif
