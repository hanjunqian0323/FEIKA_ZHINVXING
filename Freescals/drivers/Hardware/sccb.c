/***********************************************************************
*@Author: sola
*@Date: 2019-12-03 22:48:02
*@FilePath: \FEIKA_ZHINVXING\Freescals\drivers\Hardware\sccb.c
*@Drscription: 
***********************************************************************/
#include "sccb.h"

#define DELAY_TIME			5 
/***********************************************************************
*@Function: SCCB_Delay
*@Input: tim(0-65535)
*@Return: none
*@Author: sola
*@Date: 2019-12-03 23:59:24
*@Drscription: ��ʱ����������׼����Ҫ400us��
***********************************************************************/
void SCCB_Delay(__IO uint32_t tim)
{
    while (tim)
    {
        tim--;
    }
}

/***********************************************************************
*@Function: SCCB_Init
*@Input: void
*@Return: none
*@Author: sola
*@Date: 2019-12-03 23:59:20
*@Drscription: SCCBģ��ʱ������ų�ʼ������ʼ��ΪGPIOģʽ��PORT����Ϊ��©
***********************************************************************/
bool SCCB_Init(void)
{
    gpio_pin_config_t sccb_gpio_config;
    port_pin_config_t sccb_port_config;

    /* Start GPIO CLOCK */
    CLOCK_EnableClock(SCCB_SCL_CLK);
    CLOCK_EnableClock(SCCB_SDA_CLK);

    /* Configure GPIO MUX */
    PORT_SetPinMux(SCCB_SDA_PORT, SCCB_SCL_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(SCCB_SDA_PORT, SCCB_SDA_PIN, kPORT_MuxAsGpio);
    
#if 1   //��֪�����������û���ã�������
    /*
    * �ر�ǿ����ģʽ
    * ѡ��GPIO����
    * ʹ�ܿ�©���
    * �ر������˲���
    * �˿�����
    * ʹ�ܿ���ģʽ
    */
    sccb_port_config.driveStrength = kPORT_LowDriveStrength;
    sccb_port_config.lockRegister = 0U;
    sccb_port_config.mux = kPORT_MuxAsGpio;
    sccb_port_config.openDrainEnable = kPORT_OpenDrainEnable;
    sccb_port_config.passiveFilterEnable = kPORT_PassiveFilterDisable;
    sccb_port_config.pullSelect = kPORT_PullUp;
    sccb_port_config.slewRate = kPORT_FastSlewRate;
    PORT_SetPinConfig(SCCB_SCL_PORT, SCCB_SCL_PIN, &sccb_port_config);
#endif
    /*
    * ����Ϊ�߼����
    * ��������ߵ�ƽ
    */
    sccb_gpio_config.pinDirection = kGPIO_DigitalOutput; 
    sccb_gpio_config.outputLogic = 1U; 
    GPIO_PinInit(SCCB_SDA_GPIO, SCCB_SDA_PIN, &sccb_gpio_config);
	GPIO_PinInit(SCCB_SCL_GPIO, SCCB_SCL_PIN, &sccb_gpio_config);
    return true;
}

/***********************************************************************
*@Function: SCCB_MODE_CHANGE
*@Input: mode��0,1��
*@Return: none
*@Author: sola
*@Date: 2019-12-03 23:59:15
*@Drscription: ѡ��SDA���������ģʽ��0λ���룬1Ϊ���
***********************************************************************/
void SCCB_MODE_CHANGE(uint8_t mode)
{
    gpio_pin_config_t sccb_gpio_config;

    if(mode)
    {
        sccb_gpio_config.pinDirection = kGPIO_DigitalOutput; 
        sccb_gpio_config.outputLogic = 1U; 
        GPIO_PinInit(SCCB_SDA_GPIO, SCCB_SDA_PIN, &sccb_gpio_config);
    }
    else
    {
        sccb_gpio_config.pinDirection = kGPIO_DigitalInput;
        GPIO_PinInit(SCCB_SDA_GPIO, SCCB_SDA_PIN, &sccb_gpio_config);
    }
}

/***********************************************************************
*@Function: SCCB_Start
*@Input: void
*@Return: none
*@Author: sola
*@Date: 2019-12-03 23:59:31
*@Drscription: SCCB����ʼ�ź�
***********************************************************************/
bool SCCB_Start(void)
{
    SCCB_SDA_OUT_H();
    SCCB_SCL_OUT_H();
    DELAY_US(DELAY_TIME);

    SCCB_MODE_CHANGE(0);
    if(!SCCB_SDA_IN())
    {
        SCCB_MODE_CHANGE(1); 
        DEBUG_PRINTF("SDA Ϊ�͵�ƽ������\n");
        return 0;
    }
    SCCB_MODE_CHANGE(1);
    SCCB_SDA_OUT_L();

    DELAY_US(DELAY_TIME);
    SCCB_SCL_OUT_L();

    //SCCB_MODE_CHANGE(0);
    if(SCCB_SDA_IN())
    {
        SCCB_MODE_CHANGE(1); 
		DEBUG_PRINTF("SDA Ϊ�ߵ�ƽ������\n");
        return 0;
    }

	//printf("start sucess\n");
    return true;
}

/***********************************************************************
*@Function: SCCB_Stop
*@Input: void
*@Return: none
*@Author: sola
*@Date: 2019-12-04 00:05:26
*@Drscription: SCCB��ֹͣ�ź�
***********************************************************************/
bool SCCB_Stop(void)
{
    SCCB_SCL_OUT_L();
	DELAY_US(DELAY_TIME);
    SCCB_SDA_OUT_L();
    DELAY_US(DELAY_TIME);

    SCCB_SCL_OUT_H();
    DELAY_US(DELAY_TIME);
    SCCB_SDA_OUT_H();
    DELAY_US(DELAY_TIME);

    return true;
}

/***********************************************************************
*@Function: SCCB_Ack
*@Input: void
*@Return: none
*@Author: sola
*@Date: 2019-12-04 00:05:30
*@Drscription: SCCB��Ӧ���ź�
***********************************************************************/
bool SCCB_Ack(void)
{
    SCCB_SCL_OUT_L();
    DELAY_US(DELAY_TIME);
    SCCB_SDA_OUT_L();
    DELAY_US(DELAY_TIME);
    SCCB_SCL_OUT_H();
    DELAY_US(DELAY_TIME);
    SCCB_SCL_OUT_L();
    DELAY_US(DELAY_TIME);

    return true;
}

/***********************************************************************
*@Function: SCCB_NoAck
*@Input: void
*@Return: none
*@Author: sola
*@Date: 2019-12-04 00:07:04
*@Drscription: SCCB�ķ�Ӧ���ź�
***********************************************************************/
bool SCCB_NoAck(void)
{
    SCCB_SCL_OUT_L();
    DELAY_US(DELAY_TIME);
    SCCB_SDA_OUT_H();
    DELAY_US(DELAY_TIME);
    SCCB_SCL_OUT_H();
    DELAY_US(DELAY_TIME);
    SCCB_SCL_OUT_L();
    DELAY_US(DELAY_TIME);

    return true;
}

/***********************************************************************
*@Function: SCCB_WaitAck
*@Input: void
*@Return: none
*@Author: sola
*@Date: 2019-12-04 00:08:30
*@Drscription: SCCBӦ��ȴ��ź�
***********************************************************************/
bool SCCB_WaitAck(void)
{
    SCCB_SCL_OUT_L();
    SCCB_SDA_OUT_L();
    SCCB_MODE_CHANGE(0);
	
    DELAY_US(DELAY_TIME);
    SCCB_SCL_OUT_H();

    DELAY_US(DELAY_TIME);

    if(SCCB_SDA_IN())           //Ӧ��Ϊ�ߵ�ƽ���쳣��ͨ��ʧ��
    {
        SCCB_MODE_CHANGE(1);
        SCCB_SCL_OUT_L();
        return 0;
    }
    SCCB_MODE_CHANGE(1);
    SCCB_SCL_OUT_L();
    return true;
}

/***********************************************************************
*@Function: SCCB_SendByte
*@Input: SendByte ��uint8_t���͵����ݣ�
*@Return: none
*@Author: sola
*@Date: 2019-12-04 00:13:47
*@Drscription: ����һ���ֽ�
***********************************************************************/
bool SCCB_SendByte(uint8_t SendByte)
{
    uint8_t i = 8;
	SCCB_MODE_CHANGE(1);
	SCCB_SCL_OUT_L();
    while(i--)
    {
        if(SendByte & 0x80)     //SDA �������
        {
            SCCB_SDA_OUT_H();
        }
        else
        {
            SCCB_SDA_OUT_L();;
        }
        SendByte <<= 1;
        DELAY_US(DELAY_TIME);
        SCCB_SCL_OUT_H();                //SCL ���ߣ��ɼ��ź�
        DELAY_US(DELAY_TIME);
        SCCB_SCL_OUT_L();                //SCL ʱ��������
        //SCCB_DELAY();
    }
    return true;
}

/***********************************************************************
*@Function: SCCB_ReceiveByte
*@Input: void
*@Return: none
*@Author: sola
*@Date: 2019-12-04 00:14:01
*@Drscription: ����һ���ֽڵ�����
***********************************************************************/
uint8_t SCCB_ReceiveByte(void)
{
    uint8_t i = 8;
    uint8_t ReceiveByte = 0;

    //SDA_H();
    //SCCB_DELAY();
    SCCB_MODE_CHANGE(0);
    while(i--)
    {
        ReceiveByte <<= 1;
        SCCB_SCL_OUT_L();
        DELAY_US(DELAY_TIME);
        SCCB_SCL_OUT_H();
        DELAY_US(DELAY_TIME);

        if(SCCB_SDA_IN())
        {
            ReceiveByte |= 0x01;
        }


    }
    SCCB_MODE_CHANGE(1);
    SCCB_SCL_OUT_L();
    return ReceiveByte;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-12-05 02:24:11
*@Drscription: 
***********************************************************************/
int SCCB_WriteByte_one( uint16_t WriteAddress , uint8_t SendByte )
{
    if(!SCCB_Start())
    {
        return 0;
    }
	
    SCCB_SendByte( DEV_ADR );                    /* ������ַ */
	
    if( SCCB_WaitAck() != true)
    {
		DEBUG_PRINTF("\nSCCBд����Ӧ��ʧ��\n");
        SCCB_Stop();
        return 0;
    }
	
    SCCB_SendByte((uint8_t)(WriteAddress & 0x00FF));   /* ���õ���ʼ��ַ */
	
	SCCB_WaitAck();
	
    SCCB_SendByte(SendByte);
	
    SCCB_WaitAck();

    SCCB_Stop();
    return 1;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-12-05 02:24:14
*@Drscription: 
***********************************************************************/
int SCCB_WriteByte( uint16_t WriteAddress , uint8_t SendByte )//���ǵ���sccb�Ĺܽ�ģ�⣬�Ƚ�����ʧ�ܣ���˶��Լ���
{
    uint8_t i = 0;
    while( 0 == SCCB_WriteByte_one ( WriteAddress, SendByte ) )
    {
        i++;
        if(i == 20)
        {
            return 0 ;
        }
    }
    return 1;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-12-05 02:24:59
*@Drscription: 
***********************************************************************/
int SCCB_ReadByte_one(uint8_t *pBuffer,   uint16_t length,   uint8_t ReadAddress)
{
    if(!SCCB_Start())
    {
        return 0;
    }
    SCCB_SendByte( DEV_ADR );         /* ������ַ */
    if( !SCCB_WaitAck() )
    {
        SCCB_Stop();
        return 0;
    }
    SCCB_SendByte( ReadAddress );           /* ���õ���ʼ��ַ */
    SCCB_WaitAck();
    SCCB_Stop();

    if(!SCCB_Start())
    {
        return 0;
    }
    SCCB_SendByte( DEV_ADR + 1 );               /* ������ַ */

    if(!SCCB_WaitAck())
    {
        SCCB_Stop();
        return 0;
    }
    while(length)
    {
        *pBuffer = SCCB_ReceiveByte();
        if(length == 1)
        {
            SCCB_NoAck();
        }
        else
        {
            SCCB_Ack();
        }
        pBuffer++;
        length--;
    }
    SCCB_Stop();
    return 1;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-12-05 02:25:53
*@Drscription: 
***********************************************************************/
int SCCB_ReadByte(uint8_t *pBuffer,uint16_t length,uint8_t ReadAddress)
{
    uint8_t i = 0;
    while( 0 == SCCB_ReadByte_one(pBuffer, length, ReadAddress) )
    {
        i++;
        if(i == 30)
        {
            return 0 ;
        }
    }
    return 1;
}
