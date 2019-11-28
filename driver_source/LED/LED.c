#include "led.h"

void LED_INIT(void)
{
    gpio_pin_config_t LEDconfig;//GPIO��ʼ�����
    
    CLOCK_EnableClock(kCLOCK_PortB);//GPIOB�˿�ʱ�ӳ�ʼ��
    
    PORT_SetPinMux(LED_PORT,LED0,kPORT_MuxAsGpio);//�˿ڸ���ΪGPIOģʽ
    PORT_SetPinMux(LED_PORT,LED1,kPORT_MuxAsGpio);//�˿ڸ���ΪGPIOģʽ
    PORT_SetPinMux(LED_PORT,LED2,kPORT_MuxAsGpio);//�˿ڸ���ΪGPIOģʽ
    PORT_SetPinMux(LED_PORT,LED3,kPORT_MuxAsGpio);//�˿ڸ���ΪGPIOģʽ
    
    
    LEDconfig.pinDirection = kGPIO_DigitalOutput;//����Ϊ���ģʽ
    LEDconfig.outputLogic = 0;      //���0  
    
    GPIO_PinInit(LED_GPIOINSTANCE,LED0,&LEDconfig); //GPIO��ʼ��
    GPIO_PinInit(LED_GPIOINSTANCE,LED1,&LEDconfig); //GPIO��ʼ��
    GPIO_PinInit(LED_GPIOINSTANCE,LED2,&LEDconfig); //GPIO��ʼ��
    GPIO_PinInit(LED_GPIOINSTANCE,LED3,&LEDconfig); //GPIO��ʼ��
}

void LED0_TURN(uint8_t status)	//ON����OFF
{
    GPIO_PinWrite(LED_GPIOINSTANCE,LED0,status);
}

void LED1_TURN(uint8_t status)	//ON����OFF
{
    GPIO_PinWrite(LED_GPIOINSTANCE,LED1,status);
}

void LED2_TURN(uint8_t status)	//ON����OFF
{
    GPIO_PinWrite(LED_GPIOINSTANCE,LED2,status);
}

void LED3_TURN(uint8_t status)	//ON����OFF
{
    GPIO_PinWrite(LED_GPIOINSTANCE,LED3,status);
}
