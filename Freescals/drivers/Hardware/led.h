/***********************************************************************
*@Author: sola
*@Date: 2019-11-28 02:08:19
*@FilePath: \FEIKA_ZHINVXING\Freescals\drivers\Hardware\led.h
*@Drscription: 
***********************************************************************/
#ifndef __LED_H
#define __LED_H

#include "fsl_common.h"
#include "main.h"

typedef enum 
{
    LED_ON,
    LED_OFF,
    LED_TOGGLE,
}LED_Status;


typedef struct _led
{
    /*
    * @配置LED相应的IO口
    * @设置LED状态
    * @LED端口
    * @LED引脚
    * @LED的状态
    */
    void (* const LED_GPIOInit)(struct _led *p,GPIO_Type *base,uint32_t pin);  
    void (* const LED_SetStatus)(struct _led *p,LED_Status led_status);
    GPIO_Type *_GPIOx;  
    uint32_t _GPIO_Pin; 
    LED_Status LED_STATUS;
}LED_InitStruct;

void LED_GPIOInit(struct _led *p,GPIO_Type *base,uint32_t pin);
void LED_SetStatus(struct _led *p,LED_Status led_status);
void LED_Init(void);
void LED_On(LED_InitStruct LEDx);
void LED_Off(LED_InitStruct LEDx);
#endif /*!__LED_H */
