/***********************************************************************
*@Author: sola
*@Date: 2019-12-05 02:30:09
*@FilePath: \FEIKA_ZHINVXING\Freescals\drivers\Hardware\ov7725.c
*@Drscription: 
***********************************************************************/
#include "ov7725.h"

uint8_t   *ov7725_eagle_img_buff;


/*OV7725��ʼ�����ñ�*/
reg_s ov7725_eagle_reg[] =
{
    //�Ĵ������Ĵ���ֵ��
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

uint8_t ov7725_eagle_cfgnum = ARR_SIZE( ov7725_eagle_reg ) ; /*�ṹ�������Ա��Ŀ*/


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
    //DMAͨ��0��ʼ����PTA27����Դ(Ĭ��������)��Դ��ַΪPTB_B0_IN��Ŀ�ĵ�ַΪ��IMG_BUFF��ÿ�δ���1Byte
    dma_portx2buff_init(CAMERA_DMA_CH, (void *)&PTB_B0_IN, (void *)ov7725_eagle_img_buff, PTA27, DMA_BYTE1, CAMERA_DMA_NUM, DADDR_KEEPON);

    DMA_DIS(CAMERA_DMA_CH);
    disable_irq(PORTA_IRQn);                        //�ر�PTA���ж�
    DMA_IRQ_CLEAN(CAMERA_DMA_CH);                   //���ͨ�������жϱ�־λ
    DMA_IRQ_EN(CAMERA_DMA_CH);

    port_init(PTA27, ALT1 | DMA_FALLING | PULLDOWN );         //PCLK

    port_init(PTA29, ALT1 | IRQ_RISING  | PULLDOWN | PF);     //���жϣ��������Ͻ��ش����жϣ����˲�
#endif
/*<your code>*/

    DMA_INIT((uint32_t)((GPIOB->PDIR)&0xff),(uint32_t)ov7725_eagle_img_buff,60*80);
    set_irq_priority(DMA0_DMA16_IRQn,1);//�����ж����ȼ�Ϊ1
    disable_irq(PORTA_IRQn);  
    enable_irq(DMA0_DMA16_IRQn);//�������ж�
    DMA0->CINT = DMA_CINT_CINT(0);//����жϱ�־λ
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

    if( 0 == SCCB_WriteByte ( OV7725_COM7, 0x80 ) ) /*��λsensor */
    {
		//DEBUG_PRINTF("\n����:SCCBд���ݴ���\n");
        return 0 ;
    }

    OV7725_EAGLE_Delay_ms(50);

    if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, OV7725_VER ) )    /* ��ȡsensor ID��*/
    {
        //DEBUG_PRINTF("\n����:��ȡIDʧ��\n");
        return 0;
    }
   // DEBUG_PRINTF("\nGet ID success��SENSOR ID is 0x%x", Sensor_IDCode);
    //DEBUG_PRINTF("\nConfig Register Number is %d ", ov7725_eagle_cfgnum);
    if(Sensor_IDCode == OV7725_ID)
    {
        for( i = 0 ; i < ov7725_eagle_cfgnum ; i++ )
        {
            if( 0 == SCCB_WriteByte(ov7725_eagle_reg[i].addr, ov7725_eagle_reg[i].val) )
            {
                //DEBUG_PRINTF("\n����:д�Ĵ���0x%xʧ��", ov7725_eagle_reg[i].addr);
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

volatile IMG_STATUS_e      ov7725_eagle_img_flag = IMG_FINISH;   //ͼ��״̬

void ov7725_eagle_get_img(void)
{
    ov7725_eagle_img_flag = IMG_START;                   //��ʼ�ɼ�ͼ��

    DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(49);//ʹ��DMAͨ����ͨ��Դ,����DMA������ź�ԴΪ����ͷʱ���ź�PLCK��������

    PORTA->ISFR = 1;
    set_irq_priority(PORTA_IRQn,2);//�����ж����ȼ�Ϊ1
    enable_irq(PORTA_IRQn);                         //���жϴ򿪣�����PTA���ж�
    ov7725_eagle_img_flag = IMG_START;
	
	//DELAY_MS(50);
    while(ov7725_eagle_img_flag != IMG_FINISH)           //�ȴ�ͼ��ɼ����
    {
        if(ov7725_eagle_img_flag == IMG_FAIL)            //����ͼ��ɼ����������¿�ʼ�ɼ�
        {
            ov7725_eagle_img_flag = IMG_START;           //��ʼ�ɼ�ͼ��
            PORTA->ISFR = 1;
            enable_irq(PORTA_IRQn);                //���жϴ򿪣�����PTA���ж�
        }
    }
}

/*DMA�жϷ�����*/
void ov7725_eagle_dma()
{
    ov7725_eagle_img_flag = IMG_FINISH ;
    //DMAMUX->CHCFG[0] |= ~(1<<7);//ֹͣ����
    DMA0->CINT = DMA_CINT_CINT(0);//����жϱ�־λ
    DEBUG_PRINTF("DMA������Ϻ�����ж�\n");
    disable_irq(PORTA_IRQn); 
}

void ov7725_eagle_vsync(void)   //���ж�
{
    
    //���ж���Ҫ�ж��ǳ��������ǳ���ʼ
    if(ov7725_eagle_img_flag == IMG_START)                   //��Ҫ��ʼ�ɼ�ͼ��
    {
        ov7725_eagle_img_flag = IMG_GATHER;                  //���ͼ��ɼ���
        //disable_irq(PORTA_IRQn);

        //PORTA_ISFR = 1 <<  PT27;            //���PCLK��־λ
        PORTA->ISFR |= 1<<27U;

        //DMA_EN(CAMERA_DMA_CH);                  //ʹ��ͨ��CHn Ӳ������
        enable_irq(DMA0_DMA16_IRQn);//�����жϣ���δ��ʼ����
        DMA0->SERQ = DMA_SERQ_SAER(0);//DMA��ʼ����

        //PORTA_ISFR = 1 <<  PT27;            //���PCLK��־λ
        PORTA->ISFR |= 1<<27U;
        //DEBUG_PRINTF("���볡�ж�\n");
        //DMA_DADDR(CAMERA_DMA_CH) = (uint32)ov7725_eagle_img_buff;    //�ָ���ַ
    }
    else                                        //ͼ��ɼ�����
    {
        disable_irq(PORTA_IRQn);                        //�ر�PTA���ж�
        ov7725_eagle_img_flag = IMG_FAIL;                    //���ͼ��ɼ�ʧ��
        //DEBUG_PRINTF("���ͼ��ɼ�ʧ��\n");
    }
}

void Crmera_Pin_init(void)
{
    port_pin_config_t ov7725_port_config;
    /*
    *PTA27(����ͷPLCK���ų�ʼ��)
    * ����ǿ����ģʽ
    * ѡ��GPIO����
    * ʧ�ܿ�©���
    * �ر������˲���
    * �˿�����
    * ʹ�ܿ���ģʽ
    * �½��ش���DMA����
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
    *PTA29(����ͷ <���ж�> ���ų�ʼ��)
    * ����ǿ����ģʽ
    * ѡ��GPIO����
    * ʧ�ܿ�©���
    * ���������˲���
    * �˿�����
    * ʹ�ܿ���ģʽ
    * �����ش����ж�
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

