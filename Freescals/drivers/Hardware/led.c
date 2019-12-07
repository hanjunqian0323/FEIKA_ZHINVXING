/***********************************************************************
*@Author: sola
*@Date: 2019-11-28 02:08:15
*@FilePath: \FEIKA_ZHINVXING\Freescals\drivers\Hardware\led.c
*@Drscription: 
***********************************************************************/
#include "led.h"
#include "fsl_gpio.h"

#define NewLed()    {            \
  LED_GPIOInit,                 \
  LED_SetStatus,                     \
  0,                             \
  0,                              \
  LED_ON\
} 

LED_InitStruct  LED0 = NewLed();
LED_InitStruct  LED1 = NewLed();
LED_InitStruct  LED2 = NewLed();
LED_InitStruct  LED3 = NewLed();
/***********************************************************************
*@Function: LED_GPIOInit
*@Input: *p,*base,pin
*@Return: none
*@Author: sola
*@Date: 2019-11-28 02:39:05
*@Drscription: 
***********************************************************************/
void LED_GPIOInit(struct _led *p,GPIO_Type *base,uint32_t pin)
{
    gpio_pin_config_t config ={
        kGPIO_DigitalOutput,
        0,
    };
    PORT_Type *PORT_base;

    if      (base == GPIOA)
    {
        CLOCK_EnableClock(kCLOCK_PortA);  PORT_base = PORTA;
    }
    else if (base == GPIOB)
    {
        CLOCK_EnableClock(kCLOCK_PortB); PORT_base = PORTB;
    } 
    else if (base == GPIOC) 
    {
        CLOCK_EnableClock(kCLOCK_PortC); PORT_base = PORTC;
    }
    else if (base == GPIOD)
    {
        CLOCK_EnableClock(kCLOCK_PortD); PORT_base = PORTD;
    } 
    else if (base == GPIOE) 
    {
        CLOCK_EnableClock(kCLOCK_PortE); PORT_base = PORTE;
    }
    else 
    {
        Error_Handle(); 
    }

    PORT_SetPinMux(PORT_base,pin, kPORT_MuxAsGpio);

    GPIO_PinInit(base,pin,&config);

    p->_GPIOx = base;
    p->_GPIO_Pin = pin;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-28 02:50:07
*@Drscription: 
***********************************************************************/
void LED_SetStatus(struct _led *p,LED_Status led_status)
{
    if(led_status == LED_ON)
    {
        GPIO_PinWrite(p->_GPIOx,p->_GPIO_Pin,0u);
    }
    else if (led_status == LED_OFF)
    {
        GPIO_PinWrite(p->_GPIOx,p->_GPIO_Pin,1u);
    }
    else if (led_status == LED_TOGGLE)
    {
        GPIO_PortToggle(p->_GPIOx, 1U << p->_GPIO_Pin);
    }
    else 
    {
        Error_Handle();
    }
}

/***********************************************************************
*@Function: LED_Init
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-28 03:29:18
*@Drscription: 
***********************************************************************/
void LED_Init(void)
{
    LED0.LED_GPIOInit(&LED0,GPIOB,20U);
    LED1.LED_GPIOInit(&LED1,GPIOB,21U);
    LED2.LED_GPIOInit(&LED2,GPIOB,22U);
    LED3.LED_GPIOInit(&LED3,GPIOB,23U);
}

/***********************************************************************
*@Function: LED_On
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-28 03:32:08
*@Drscription: 
***********************************************************************/
void LED_On(LED_InitStruct LEDx)
{
    LEDx.LED_SetStatus(&LEDx,LED_ON);
}

/***********************************************************************
*@Function: LED_Off
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-28 03:32:41
*@Drscription: 
***********************************************************************/
void LED_Off(LED_InitStruct LEDx)
{
    LEDx.LED_SetStatus(&LEDx,LED_OFF);
}

