#include "main.h"
//extern uint32_t count;
uint8_t imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
uint8_t img[CAMERA_W*CAMERA_H];                           //定义存储解压后的图像数组（用于读取像素值，图像处理）

//函数声明
int main(void)
{
	Site_t site     = {0, 0};                           //显示图像左上角位置
    Size_t imgsize  = {CAMERA_W, CAMERA_H};             //图像大小
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
		//camera_get_img();                                   //摄像头获取图像
        //vcan_sendimg(imgbuff, sizeof(imgbuff));
		PRINTF("Hello World!");
	}
}

/*!
 *  @brief      PORTA中断服务函数
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8_t  n;    //引脚号
    uint32_t flag;

    while(!PORTA->ISFR);
    flag = PORTA->ISFR;
    PORTA->ISFR  = ~0;                                   //清中断标志位

    n = 29;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //使用行中断
    n = 28;
    if(flag & (1 << n))                                 //PTA28触发中断
    {
        camera_href();
    }
#endif


}

/*!
 *  @brief      DMA0中断服务函数
 *  @since      v5.0
 */
void DMA0_DMA16_IRQHandler()
{
    camera_dma();
}

