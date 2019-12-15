/*
 * @Author: your name
 * @Date: 2019-12-10 20:12:41
 * @LastEditTime: 2019-12-15 09:51:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \FEIKA_ZHINVXING\Freescals\drivers\Hardware\DMA.c
 */
#include "DMA.h"

void DMA_INIT(uint32_t srcAddr,uint32_t destAddr,uint16_t size)
{
	SIM->SCGC6 = SIM_SCGC6_DMAMUX_MASK;//使能DMAMUX时钟
	SIM->SCGC7 = SIM_SCGC7_DMA_MASK;//使能DMA时钟
	
	DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(49);//使能DMA通道和通道源,触发DMA传输的信号源为摄像头时钟信号PLCK的上升沿
	
	//源数据配置：
	//源地址
	//每次搬运的字节数为0位（一个字节）
	//传输完后地址偏移量
	//传输完不偏移
	DMA0->TCD[0].SADDR = srcAddr;
	DMA0->TCD[0].ATTR = DMA_ATTR_SSIZE(0);
	DMA0->TCD[0].SOFF = 1;
	DMA0->TCD[0].SLAST = 0;

	//目的数据配置：
	//目的地址
	//每次搬运的字节数为0位（一个字节）
	//传输完后地址偏移量
	//传输完不偏移
	DMA0->TCD[0].DADDR = destAddr;
	DMA0->TCD[0].ATTR = DMA_ATTR_DSIZE(0);
	DMA0->TCD[0].DOFF = 1;
	DMA0->TCD[0].DLAST_SGA = 0;
	
	//设置BITER和CITER：
	//本次循环有size个小循环
	//本次循环有size个大循环
	//每次传输一个字节
	DMA0->TCD[0].BITER_ELINKNO = size;
	DMA0->TCD[0].CITER_ELINKNO = size;
	DMA0->TCD[0].NBYTES_MLNO = 1;
	
	DMA0->TCD[0].CSR = DMA_CSR_DREQ_MASK;//使能传输完成后关闭请求位
	
	DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK;//使能传输完成中断
	DMA0->CINT = DMA_CINT_CINT(0);//清除中断标志位
	
	//EnableIRQ(DMA0_DMA16_IRQn);//使能DMA中断	
	//DMA0->SERQ = DMA_SERQ_SAER(0);//开始传输
}

/*void DMA0_DMA16_IRQHandler(void)
{
	Transfer_Done = true;
	DMA0->CINT = DMA_CINT_CINT(0);//清除中断标志位
}*/
