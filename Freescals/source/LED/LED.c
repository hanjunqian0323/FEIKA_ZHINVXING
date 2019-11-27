#include "led.h"

void LED_INIT(void)
{
    gpio_pin_config_t LEDconfig;//GPIO初始化句柄
    
    CLOCK_EnableClock(kCLOCK_PortB);//GPIOB端口时钟初始化
    
    PORT_SetPinMux(LED_PORT,LED0,kPORT_MuxAsGpio);//端口复用为GPIO模式
    PORT_SetPinMux(LED_PORT,LED1,kPORT_MuxAsGpio);//端口复用为GPIO模式
    PORT_SetPinMux(LED_PORT,LED2,kPORT_MuxAsGpio);//端口复用为GPIO模式
    PORT_SetPinMux(LED_PORT,LED3,kPORT_MuxAsGpio);//端口复用为GPIO模式
    
    
    LEDconfig.pinDirection = kGPIO_DigitalOutput;//配置为输出模式
    LEDconfig.outputLogic = 0;      //输出0  
    
    GPIO_PinInit(LED_GPIOINSTANCE,LED0,&LEDconfig); //GPIO初始化
    GPIO_PinInit(LED_GPIOINSTANCE,LED1,&LEDconfig); //GPIO初始化
    GPIO_PinInit(LED_GPIOINSTANCE,LED2,&LEDconfig); //GPIO初始化
    GPIO_PinInit(LED_GPIOINSTANCE,LED3,&LEDconfig); //GPIO初始化
}

void LED0_TURN(uint8_t status)	//ON或者OFF
{
    GPIO_PinWrite(LED_GPIOINSTANCE,LED0,status);
}

void LED1_TURN(uint8_t status)	//ON或者OFF
{
    GPIO_PinWrite(LED_GPIOINSTANCE,LED1,status);
}

void LED2_TURN(uint8_t status)	//ON或者OFF
{
    GPIO_PinWrite(LED_GPIOINSTANCE,LED2,status);
}

void LED3_TURN(uint8_t status)	//ON或者OFF
{
    GPIO_PinWrite(LED_GPIOINSTANCE,LED3,status);
}
