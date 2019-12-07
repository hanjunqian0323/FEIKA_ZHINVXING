#include "DELAY.h"

//Global
__IO uint32_t SystickTimeCount;

void SYSTICK_INIT(uint16_t freq)		//176¶ÔÓ¦1us
{
	SysTick_Config(freq); 
}

void SysTick_Handler(void)
{
	if(SystickTimeCount != 0)
    SystickTimeCount --;
}

void DELAY_US(uint32_t US)
{
    SystickTimeCount = US;
    while(SystickTimeCount);
}

void DELAY_MS(uint32_t MS)
{
	for(;MS>0;MS--)DELAY_US(1000);
}

