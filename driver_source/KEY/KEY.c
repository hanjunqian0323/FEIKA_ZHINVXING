#include "KEY.h"

/***************************************************
函数功能：按键初始化
返回参数：无
***************************************************/
void KEY_INIT(void)
{
    gpio_pin_config_t keyconfig;//GPIO初始化句柄
    
    CLOCK_EnableClock(kCLOCK_PortD);//GPIOD端口时钟初始化
    
    PORT_SetPinMux(KEY_PORT,KEY_PIN,kPORT_MuxAsGpio);//端口复用为GPIO模式
    
    keyconfig.pinDirection = kGPIO_DigitalInput;
    GPIO_PinInit(KEY_GPIOINSTANCE,KEY_PIN,&keyconfig);
}

/***************************************************
函数功能：按键扫描
返回参数：扫描按下返回1，无按下返回0
***************************************************/
uint8_t KEY_SCAN(void)
{
	if(GPIO_PinRead(KEY_GPIOINSTANCE,KEY_PIN)==0)
	{
		DELAY_MS(100);//消抖
		return 1;
	}
	else	return 0;
}






