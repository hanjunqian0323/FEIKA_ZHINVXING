/***********************************************************************
*@Author: sola
*@Date: 2019-12-05 02:30:09
*@FilePath: \FEIKA_ZHINVXING\Freescals\drivers\Hardware\ov7725.c
*@Drscription: 
***********************************************************************/
#include "ov7725.h"

uint8_t   *ov7725_eagle_img_buff;


/*OV7725初始化配置表*/
reg_s ov7725_eagle_reg[] =
{
    //寄存器，寄存器值次
    {OV7725_COM4         , 0xC1},
    {OV7725_CLKRC        , 0x00},
    {OV7725_COM2         , 0x03},
    {OV7725_COM3         , 0xD0},
    {OV7725_COM7         , 0x40},
    {OV7725_HSTART       , 0x3F},
    {OV7725_HSIZE        , 0x50},
    {OV7725_VSTRT        , 0x03},
    {OV7725_VSIZE        , 0x78},
    {OV7725_HREF         , 0x00},
    {OV7725_SCAL0        , 0x0A},
    {OV7725_AWB_Ctrl0    , 0xE0},
    {OV7725_DSPAuto      , 0xff},
    {OV7725_DSP_Ctrl2    , 0x0C},
    {OV7725_DSP_Ctrl3    , 0x00},
    {OV7725_DSP_Ctrl4    , 0x00},

#if (CAMERA_W == 80)
    {OV7725_HOutSize     , 0x14},
#elif (CAMERA_W == 160)
    {OV7725_HOutSize     , 0x28},
#elif (CAMERA_W == 240)
    {OV7725_HOutSize     , 0x3c},
#elif (CAMERA_W == 320)
    {OV7725_HOutSize     , 0x50},
#else

#endif

#if (CAMERA_H == 60 )
    {OV7725_VOutSize     , 0x1E},
#elif (CAMERA_H == 120 )
    {OV7725_VOutSize     , 0x3c},
#elif (CAMERA_H == 180 )
    {OV7725_VOutSize     , 0x5a},
#elif (CAMERA_H == 240 )
    {OV7725_VOutSize     , 0x78},
#else

#endif

    {OV7725_EXHCH        , 0x00},
    {OV7725_GAM1         , 0x0c},
    {OV7725_GAM2         , 0x16},
    {OV7725_GAM3         , 0x2a},
    {OV7725_GAM4         , 0x4e},
    {OV7725_GAM5         , 0x61},
    {OV7725_GAM6         , 0x6f},
    {OV7725_GAM7         , 0x7b},
    {OV7725_GAM8         , 0x86},
    {OV7725_GAM9         , 0x8e},
    {OV7725_GAM10        , 0x97},
    {OV7725_GAM11        , 0xa4},
    {OV7725_GAM12        , 0xaf},
    {OV7725_GAM13        , 0xc5},
    {OV7725_GAM14        , 0xd7},
    {OV7725_GAM15        , 0xe8},
    {OV7725_SLOP         , 0x20},
    {OV7725_LC_RADI      , 0x00},
    {OV7725_LC_COEF      , 0x13},
    {OV7725_LC_XC        , 0x08},
    {OV7725_LC_COEFB     , 0x14},
    {OV7725_LC_COEFR     , 0x17},
    {OV7725_LC_CTR       , 0x05},
    {OV7725_BDBase       , 0x99},
    {OV7725_BDMStep      , 0x03},
    {OV7725_SDE          , 0x04},
    {OV7725_BRIGHT       , 0x00},
    {OV7725_CNST         , 0xFF},
    {OV7725_SIGN         , 0x06},
    {OV7725_UVADJ0       , 0x11},
    {OV7725_UVADJ1       , 0x02},

};

uint8_t ov7725_eagle_cfgnum = ARR_SIZE( ov7725_eagle_reg ) ; /*结构体数组成员数目*/


/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-12-05 02:50:25
*@Drscription: 
***********************************************************************/
void ov7725_eagle_port_init(void)
{
#if 0
    //DMA通道0初始化，PTA27触发源(默认上升沿)，源地址为PTB_B0_IN，目的地址为：IMG_BUFF，每次传输1Byte
    dma_portx2buff_init(CAMERA_DMA_CH, (void *)&PTB_B0_IN, (void *)ov7725_eagle_img_buff, PTA27, DMA_BYTE1, CAMERA_DMA_NUM, DADDR_KEEPON);

    DMA_DIS(CAMERA_DMA_CH);
    disable_irq(PORTA_IRQn);                        //关闭PTA的中断
    DMA_IRQ_CLEAN(CAMERA_DMA_CH);                   //清除通道传输中断标志位
    DMA_IRQ_EN(CAMERA_DMA_CH);

    port_init(PTA27, ALT1 | DMA_FALLING | PULLDOWN );         //PCLK

    port_init(PTA29, ALT1 | IRQ_RISING  | PULLDOWN | PF);     //场中断，上拉，上降沿触发中断，带滤波
#endif
/*<your code>*/

    DMA_INIT((uint32_t)((GPIOB->PDIR)&0xff),(uint32_t)ov7725_eagle_img_buff,60*80);
    set_irq_priority(DMA0_DMA16_IRQn,1);//设置中断优先级为1
    disable_irq(PORTA_IRQn);  
    enable_irq(DMA0_DMA16_IRQn);//开启闭中断
    DMA0->CINT = DMA_CINT_CINT(0);//清除中断标志位
    Crmera_Pin_init();
}
/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-12-05 02:38:06
*@Drscription: 
***********************************************************************/
uint8_t ov7725_eagle_reg_init(void)
{
    uint16_t i = 0;
    uint8_t Sensor_IDCode = 0;

    SCCB_Init();
    //OV7725_Delay_ms(50);
    DELAY_MS(50);

    if( 0 == SCCB_WriteByte ( OV7725_COM7, 0x80 ) ) /*复位sensor */
    {
		//DEBUG_PRINTF("\n警告:SCCB写数据错误\n");
        return 0 ;
    }

    OV7725_EAGLE_Delay_ms(50);

    if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, OV7725_VER ) )    /* 读取sensor ID号*/
    {
        //DEBUG_PRINTF("\n警告:读取ID失败\n");
        return 0;
    }
   // DEBUG_PRINTF("\nGet ID success，SENSOR ID is 0x%x", Sensor_IDCode);
    //DEBUG_PRINTF("\nConfig Register Number is %d ", ov7725_eagle_cfgnum);
    if(Sensor_IDCode == OV7725_ID)
    {
        for( i = 0 ; i < ov7725_eagle_cfgnum ; i++ )
        {
            if( 0 == SCCB_WriteByte(ov7725_eagle_reg[i].addr, ov7725_eagle_reg[i].val) )
            {
                //DEBUG_PRINTF("\n警告:写寄存器0x%x失败", ov7725_eagle_reg[i].addr);
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    DEBUG_PRINTF("\nOV7725 Register Config Success!\n");
    return 1;
}

volatile IMG_STATUS_e      ov7725_eagle_img_flag = IMG_FINISH;   //图像状态

void ov7725_eagle_get_img(void)
{
    ov7725_eagle_img_flag = IMG_START;                   //开始采集图像

    DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(49);//使能DMA通道和通道源,触发DMA传输的信号源为摄像头时钟信号PLCK的上升沿

    PORTA->ISFR = 1;
    set_irq_priority(PORTA_IRQn,2);//设置中断优先级为1
    enable_irq(PORTA_IRQn);                         //场中断打开，允许PTA的中断
    ov7725_eagle_img_flag = IMG_START;
	
	//DELAY_MS(50);
    while(ov7725_eagle_img_flag != IMG_FINISH)           //等待图像采集完毕
    {
        if(ov7725_eagle_img_flag == IMG_FAIL)            //假如图像采集错误，则重新开始采集
        {
            ov7725_eagle_img_flag = IMG_START;           //开始采集图像
            PORTA->ISFR = 1;
            enable_irq(PORTA_IRQn);                //场中断打开，允许PTA的中断
        }
    }
}

/*DMA中断服务函数*/
void ov7725_eagle_dma()
{
    ov7725_eagle_img_flag = IMG_FINISH ;
    //DMAMUX->CHCFG[0] |= ~(1<<7);//停止传输
    DMA0->CINT = DMA_CINT_CINT(0);//清除中断标志位
    DEBUG_PRINTF("DMA传输完毕后进入中断\n");
    disable_irq(PORTA_IRQn); 
}

void ov7725_eagle_vsync(void)   //场中断
{
    
    //场中断需要判断是场结束还是场开始
    if(ov7725_eagle_img_flag == IMG_START)                   //需要开始采集图像
    {
        ov7725_eagle_img_flag = IMG_GATHER;                  //标记图像采集中
        //disable_irq(PORTA_IRQn);

        //PORTA_ISFR = 1 <<  PT27;            //清空PCLK标志位
        PORTA->ISFR |= 1<<27U;

        //DMA_EN(CAMERA_DMA_CH);                  //使能通道CHn 硬件请求
        enable_irq(DMA0_DMA16_IRQn);//开启中断，但未开始传输
        DMA0->SERQ = DMA_SERQ_SAER(0);//DMA开始传输

        //PORTA_ISFR = 1 <<  PT27;            //清空PCLK标志位
        PORTA->ISFR |= 1<<27U;
        //DEBUG_PRINTF("进入场中断\n");
        //DMA_DADDR(CAMERA_DMA_CH) = (uint32)ov7725_eagle_img_buff;    //恢复地址
    }
    else                                        //图像采集错误
    {
        disable_irq(PORTA_IRQn);                        //关闭PTA的中断
        ov7725_eagle_img_flag = IMG_FAIL;                    //标记图像采集失败
        //DEBUG_PRINTF("标记图像采集失败\n");
    }
}

void Crmera_Pin_init(void)
{
    port_pin_config_t ov7725_port_config;
    /*
    *PTA27(摄像头PLCK引脚初始化)
    * 开启强驱动模式
    * 选择GPIO复用
    * 失能开漏输出
    * 关闭数字滤波器
    * 端口下拉
    * 使能快速模式
    * 下降沿触发DMA传输
    */
    ov7725_port_config.driveStrength = kPORT_HighDriveStrength;
    ov7725_port_config.lockRegister = 0U;
    ov7725_port_config.mux = kPORT_MuxAsGpio;
    ov7725_port_config.openDrainEnable = kPORT_OpenDrainDisable;
    ov7725_port_config.passiveFilterEnable = kPORT_PassiveFilterDisable;
    ov7725_port_config.pullSelect = kPORT_PullDown;
    ov7725_port_config.slewRate = kPORT_FastSlewRate;
    PORT_SetPinConfig(PORTA, 27U, &ov7725_port_config);
    PORT_SetPinInterruptConfig(PORTA,27U,kPORT_DMAFallingEdge);
    /*
    *PTA29(摄像头 <场中断> 引脚初始化)
    * 开启强驱动模式
    * 选择GPIO复用
    * 失能开漏输出
    * 开启数字滤波器
    * 端口下拉
    * 使能快速模式
    * 上升沿触发中断
    */
    ov7725_port_config.driveStrength = kPORT_HighDriveStrength;
    ov7725_port_config.lockRegister = 0U;
    ov7725_port_config.mux = kPORT_MuxAsGpio;
    ov7725_port_config.openDrainEnable = kPORT_OpenDrainDisable;
    ov7725_port_config.passiveFilterEnable = kPORT_PassiveFilterEnable;
    ov7725_port_config.pullSelect = kPORT_PullDown;
    ov7725_port_config.slewRate = kPORT_FastSlewRate;
    PORT_SetPinConfig(PORTA, 29U, &ov7725_port_config);
    PORT_SetPinInterruptConfig(PORTA,29U,kPORT_InterruptRisingEdge);
}




uint8_t ov7725_eagle_init(uint8_t *imgaddr)
{
    ov7725_eagle_img_buff = imgaddr;
    while(ov7725_eagle_reg_init() == 0);
    ov7725_eagle_port_init();
    return 0;
}

