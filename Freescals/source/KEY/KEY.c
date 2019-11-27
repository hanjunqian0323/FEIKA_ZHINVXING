#include "KEY.h"

/***************************************************
�������ܣ�������ʼ��
���ز�������
***************************************************/
void KEY_INIT(void)
{
    gpio_pin_config_t keyconfig;//GPIO��ʼ�����
    
    CLOCK_EnableClock(kCLOCK_PortD);//GPIOD�˿�ʱ�ӳ�ʼ��
    
    PORT_SetPinMux(KEY_PORT,KEY_PIN,kPORT_MuxAsGpio);//�˿ڸ���ΪGPIOģʽ
    
    keyconfig.pinDirection = kGPIO_DigitalInput;
    GPIO_PinInit(KEY_GPIOINSTANCE,KEY_PIN,&keyconfig);
}

/***************************************************
�������ܣ�����ɨ��
���ز�����ɨ�谴�·���1���ް��·���0
***************************************************/
uint8_t KEY_SCAN(void)
{
	if(GPIO_PinRead(KEY_GPIOINSTANCE,KEY_PIN)==0)
	{
		DELAY_MS(100);//����
		return 1;
	}
	else	return 0;
}






