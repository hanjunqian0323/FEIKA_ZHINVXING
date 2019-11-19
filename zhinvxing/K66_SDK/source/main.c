#include "main.h"
//extern uint32_t count;
uint8_t imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
uint8_t img[CAMERA_W*CAMERA_H];                           //����洢��ѹ���ͼ�����飨���ڶ�ȡ����ֵ��ͼ����

//��������
int main(void)
{
	Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��
    Size_t imgsize  = {CAMERA_W, CAMERA_H};             //ͼ���С
    Size_t size;
	//uint32_t Valu1 = 0,Valu2 = 0,Valu3 = 0,Valu4 = 0,Valu5 = 0,Valu6 = 0;
    /* Init board hardware. */
    BOARD_InitPins();
    //BOARD_BootClockRUN();
    board_clock_init();
    BOARD_InitDebugConsole();
	SYSTICK_INIT(176);	
	//ADC_INIT();
	adc_init();
	ov7725_eagle_init(imgbuff);
	
	EnableIRQ(PORTA_IRQn);
	EnableIRQ(DMA0_DMA16_IRQn);
    /*while(1)
    {		
		Valu1 = adc_once(ADC0_SE10, ADC_12bit);//ADC0_SE10
		Valu2 = adc_once(ADC0_SE14, ADC_12bit);//ADC0_SE14
		Valu3 = adc_once(ADC0_SE18, ADC_12bit);//ADC0_SE18
		Valu4 = adc_once(ADC1_SE4a, ADC_12bit);//ADC1_SE4a
		Valu5 = adc_once(ADC0_SE17, ADC_12bit);//ADC0_SE17
		Valu6 = adc_once(ADC1_SE17, ADC_12bit);//ADC1_SE17
		PRINTF("A7 =%d",Valu1);
		PRINTF("	C0 =%d",Valu2);
		PRINTF("	E25 =%d",Valu3);
		PRINTF("	E0 =%d",Valu4);
		PRINTF("	E24 =%d",Valu5);
		PRINTF("	A17 =%d\n",Valu6);
		DELAY_MS(50);

    }*/
	while(1)
	{
		//camera_get_img();                                   //����ͷ��ȡͼ��
        //vcan_sendimg(imgbuff, sizeof(imgbuff));
		PRINTF("Hello World!");
	}
}

/*!
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8_t  n;    //���ź�
    uint32_t flag;

    while(!PORTA->ISFR);
    flag = PORTA->ISFR;
    PORTA->ISFR  = ~0;                                   //���жϱ�־λ

    n = 29;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //ʹ�����ж�
    n = 28;
    if(flag & (1 << n))                                 //PTA28�����ж�
    {
        camera_href();
    }
#endif


}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v5.0
 */
void DMA0_DMA16_IRQHandler()
{
    camera_dma();
}

