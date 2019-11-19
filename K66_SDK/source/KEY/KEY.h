#ifndef _KEY_H_
#define _KEY_H_


#include "main.h"

#define KEY_PORT            PORTD   
#define KEY_GPIOINSTANCE    GPIOD
#define KEY_PIN             7U


void KEY_INIT(void);
uint8_t KEY_SCAN(void);
#endif

