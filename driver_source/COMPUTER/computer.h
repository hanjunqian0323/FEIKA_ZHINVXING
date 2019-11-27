#ifndef _COMPUTER_H_
#define _COMPUTER_H_


#include "main.h"

#define VCAN_PORT				UART0

void vcan_sendimg(void *imgaddr, uint32_t imgsize);
void vcan_sendccd(void *ccdaddr, uint32_t ccdsize);
void vcan_sendware(void *wareaddr, uint32_t waresize);







#endif

