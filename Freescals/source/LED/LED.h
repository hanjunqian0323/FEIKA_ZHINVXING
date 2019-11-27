#ifndef _LED_H_
#define _LED_H_

#include "main.h"

#define ON                      0
#define OFF                     1


#define LED_PORT                PORTB
#define LED_GPIOINSTANCE        GPIOB
#define LED0                    20U
#define LED1                    21U
#define LED2                    22U
#define LED3                    23U


void LED_INIT(void);
void LED0_TURN(uint8_t status);
void LED1_TURN(uint8_t status);
void LED2_TURN(uint8_t status);
void LED3_TURN(uint8_t status);

#endif


