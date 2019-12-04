/***********************************************************************
*@Author: sola
*@Date: 2019-12-03 22:48:08
*@FilePath: \FEIKA_ZHINVXING\Freescals\drivers\Hardware\sccb.h
*@Drscription: 
***********************************************************************/

#include "main.h"

#ifndef __sccb_h
#define __sccb_h

#define SCCB_SCL_PIN        26U
#define SCCB_SDA_PIN        25U

#define SCCB_SDA_PORT       PORTA
#define SCCB_SCL_PORT       PORTA

#define SCCB_SCL_GPIO       GPIOA
#define SCCB_SDA_GPIO       GPIOA

#define SCCB_SCL_CLK        kCLOCK_PortA
#define SCCB_SDA_CLK        kCLOCK_PortA

#define SCCB_SCL_OUT_H()    GPIO_PinWrite(SCCB_SCL_GPIO, SCCB_SCL_PIN, 1U)
#define SCCB_SCL_OUT_L()    GPIO_PinWrite(SCCB_SCL_GPIO, SCCB_SCL_PIN, 0U)
#define SCCB_SDA_OUT_H()    GPIO_PinWrite(SCCB_SDA_GPIO, SCCB_SDA_PIN, 1U)
#define SCCB_SDA_OUT_L()    GPIO_PinWrite(SCCB_SDA_GPIO, SCCB_SDA_PIN, 0U)

#define SCCB_SDA_IN()       GPIO_PinRead(SCCB_SDA_GPIO, SCCB_SDA_PIN)





#endif /* !__sccb_h */
