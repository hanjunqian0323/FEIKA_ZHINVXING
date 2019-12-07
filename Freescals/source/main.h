/***********************************************************************
*@Author: sola
*@Date: 2019-11-28 01:33:47
*@FilePath: \FEIKA_ZHINVXING\Freescals\source\main.h
*@Drscription: 
***********************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"

#include <stdio.h>

//SDK包
#include "fsl_pit.h"
#include "fsl_ftm.h"
#include "fsl_uart.h"
#include "fsl_adc16.h"
#include "MK66F18.h"
#include "fsl_edma.h"
#include "fsl_port.h"
//自己定义
#include "led.h"
#include "sccb.h"
#include "ov7725.h"
#include "UsART.h"
#include "DELAY.h"


#define enable_irq(irq)                 NVIC_EnableIRQ(irq)         //使能IRQ
#define disable_irq(irq)                NVIC_DisableIRQ(irq)        //禁止IRQ
#define set_irq_priority(irq,pri0)      NVIC_SetPriority(irq,pri0)  //设置优先级


void Error_Handle(void);




#endif



