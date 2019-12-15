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
	SIM->SCGC6 = SIM_SCGC6_DMAMUX_MASK;//ʹ��DMAMUXʱ��
	SIM->SCGC7 = SIM_SCGC7_DMA_MASK;//ʹ��DMAʱ��
	
	DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(49);//ʹ��DMAͨ����ͨ��Դ,����DMA������ź�ԴΪ����ͷʱ���ź�PLCK��������
	
	//Դ�������ã�
	//Դ��ַ
	//ÿ�ΰ��˵��ֽ���Ϊ0λ��һ���ֽڣ�
	//��������ַƫ����
	//�����겻ƫ��
	DMA0->TCD[0].SADDR = srcAddr;
	DMA0->TCD[0].ATTR = DMA_ATTR_SSIZE(0);
	DMA0->TCD[0].SOFF = 1;
	DMA0->TCD[0].SLAST = 0;

	//Ŀ���������ã�
	//Ŀ�ĵ�ַ
	//ÿ�ΰ��˵��ֽ���Ϊ0λ��һ���ֽڣ�
	//��������ַƫ����
	//�����겻ƫ��
	DMA0->TCD[0].DADDR = destAddr;
	DMA0->TCD[0].ATTR = DMA_ATTR_DSIZE(0);
	DMA0->TCD[0].DOFF = 1;
	DMA0->TCD[0].DLAST_SGA = 0;
	
	//����BITER��CITER��
	//����ѭ����size��Сѭ��
	//����ѭ����size����ѭ��
	//ÿ�δ���һ���ֽ�
	DMA0->TCD[0].BITER_ELINKNO = size;
	DMA0->TCD[0].CITER_ELINKNO = size;
	DMA0->TCD[0].NBYTES_MLNO = 1;
	
	DMA0->TCD[0].CSR = DMA_CSR_DREQ_MASK;//ʹ�ܴ�����ɺ�ر�����λ
	
	DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK;//ʹ�ܴ�������ж�
	DMA0->CINT = DMA_CINT_CINT(0);//����жϱ�־λ
	
	//EnableIRQ(DMA0_DMA16_IRQn);//ʹ��DMA�ж�	
	//DMA0->SERQ = DMA_SERQ_SAER(0);//��ʼ����
}

/*void DMA0_DMA16_IRQHandler(void)
{
	Transfer_Done = true;
	DMA0->CINT = DMA_CINT_CINT(0);//����жϱ�־λ
}*/
