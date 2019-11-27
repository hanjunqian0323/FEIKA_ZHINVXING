#include "SCCB.h"

static void SCCB_delay(volatile uint16_t time)//400
{
    while(time)
    {
        time--;
    }
}

void SDA_LOGIC_CHANGE(uint8_t LOGIC)//1�����	0������
{
	gpio_pin_config_t SCCBconfig;//GPIO��ʼ�����
	if(LOGIC == 1)
	{
		SCCBconfig.pinDirection = kGPIO_DigitalOutput;//����Ϊ���ģʽ
		GPIO_PinInit(SCCB_GPIO,SCCB_SDA_PIN,&SCCBconfig); //GPIO��ʼ��
	}
	else if(LOGIC == 0)
	{
		SCCBconfig.pinDirection = kGPIO_DigitalInput;//����Ϊ���ģʽ
		GPIO_PinInit(SCCB_GPIO,SCCB_SDA_PIN,&SCCBconfig); //GPIO��ʼ��
	}
}


void SCCB_GPIO_init(void)
{
	gpio_pin_config_t SCCBconfig;//GPIO��ʼ�����
	port_pin_config_t SCCBPORTconfig;//PORT��ʼ�����
	
	SCCBPORTconfig.openDrainEnable = 1;//��©
	SCCBPORTconfig.pullSelect = 2;//����
	PORT_SetMultiplePinsConfig(SCCB_PORT,SCCB_SCL_PIN,&SCCBPORTconfig);//PORT��ʼ��
	PORT_SetMultiplePinsConfig(SCCB_PORT,SCCB_SDA_PIN,&SCCBPORTconfig);//PORT��ʼ��
	PORT_SetPinMux(SCCB_PORT,SCCB_SCL_PIN,kPORT_MuxAsGpio);//SCL���Ÿ���
	PORT_SetPinMux(SCCB_PORT,SCCB_SDA_PIN,kPORT_MuxAsGpio);//SDA���Ÿ���
	
	SCCBconfig.pinDirection = kGPIO_DigitalOutput;//����Ϊ���ģʽ
    SCCBconfig.outputLogic = 1;//���1
    
    GPIO_PinInit(SCCB_GPIO,SCCB_SCL_PIN,&SCCBconfig); //GPIO��ʼ��
    GPIO_PinInit(SCCB_GPIO,SCCB_SDA_PIN,&SCCBconfig); //GPIO��ʼ��
}

static uint8_t SCCB_Start(void)
{
    SDA_H();
    SCL_H();
    SCCB_DELAY();

    SDA_DDR_IN();
    if(!SDA_IN())
    {
        SDA_DDR_OUT();
        return 0;   /* SDA��Ϊ�͵�ƽ������æ,�˳� */
    }
    SDA_DDR_OUT();
    SDA_L();

    SCCB_DELAY();
    SCL_L();

    if(SDA_IN())
    {
        SDA_DDR_OUT();
        return 0;   /* SDA��Ϊ�ߵ�ƽ�����߳���,�˳� */
    }
    //SDA_DDR_OUT();
    //SDA_L();
    //SCCB_delay();
    return 1;
}

static void SCCB_Stop(void)
{
    SCL_L();
    //SCCB_DELAY();
    SDA_L();
    SCCB_DELAY();
    SCL_H();
    SCCB_DELAY();
    SDA_H();
    SCCB_DELAY();
}

/*!
 *  @brief      SCCBӦ���ź�
 *  @since      v5.0
 */
static void SCCB_Ack(void)
{
    SCL_L();
    SCCB_DELAY();
    SDA_L();
    SCCB_DELAY();
    SCL_H();
    SCCB_DELAY();
    SCL_L();
    SCCB_DELAY();
}

/*!
 *  @brief      SCCB��Ӧ���ź�
 *  @since      v5.0
 */
static void SCCB_NoAck(void)
{
    SCL_L();
    SCCB_DELAY();
    SDA_H();
    SCCB_DELAY();
    SCL_H();
    SCCB_DELAY();
    SCL_L();
    SCCB_DELAY();
}

/*!
 *  @brief      SCCB �ȴ�Ӧ��
 *  @return     Ӧ������0��ʾ��Ӧ��1��ʾ��Ӧ��
 *  @since      v5.0
 */
static int SCCB_WaitAck(void)
{
    SCL_L();
    //SDA_H();
    SDA_DDR_IN();

    SCCB_DELAY();
    SCL_H();

    SCCB_DELAY();

    if(SDA_IN())           //Ӧ��Ϊ�ߵ�ƽ���쳣��ͨ��ʧ��
    {
        SDA_DDR_OUT();
        SCL_L();
        return 0;
    }
    SDA_DDR_OUT();
    SCL_L();
    return 1;
}

/*!
 *  @brief      SCCB ���͵�����
 *  @param      SendByte    ��Ҫ���͵�����
 *  @since      v5.0
 */
static void SCCB_SendByte(uint8_t SendByte)
{
    uint8_t i = 8;
    while(i--)
    {

        if(SendByte & 0x80)     //SDA �������
        {
            SDA_H();
        }
        else
        {
            SDA_L();
        }
        SendByte <<= 1;
        SCCB_DELAY();
        SCL_H();                //SCL ���ߣ��ɼ��ź�
        SCCB_DELAY();
        SCL_L();                //SCL ʱ��������
        //SCCB_DELAY();
    }
    //SCL_L();
}

/*!
 *  @brief      ����SCCB���ߵ�����
 *  @return     ���յ�������
 *  @since      v5.0
 */
static int SCCB_ReceiveByte(void)
{
    uint8_t i = 8;
    uint8_t ReceiveByte = 0;

    //SDA_H();
    //SCCB_DELAY();
    SDA_DDR_IN();

    while(i--)
    {
        ReceiveByte <<= 1;
        SCL_L();
        SCCB_DELAY();
        SCL_H();
        SCCB_DELAY();

        if(SDA_IN())
        {
            ReceiveByte |= 0x01;
        }


    }
    SDA_DDR_OUT();
    SCL_L();
    return ReceiveByte;
}

/*****************************************************************************************
* ��������SCCB_WriteByte
* ����  ��дһ�ֽ�����
* ����  ��- WriteAddress: ��д���ַ    - SendByte: ��д������  - DeviceAddress: ��������
* ���  ������Ϊ:=1�ɹ�д��,=0ʧ��
* ע��  ����
*****************************************************************************************/
static int SCCB_WriteByte_one( uint16_t WriteAddress , uint8_t SendByte );


int SCCB_WriteByte( uint16_t WriteAddress , uint8_t SendByte )            //���ǵ���sccb�Ĺܽ�ģ�⣬�Ƚ�����ʧ�ܣ���˶��Լ���
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

int SCCB_WriteByte_one( uint16_t WriteAddress , uint8_t SendByte )
{
    if(!SCCB_Start())
    {
        return 0;
    }
    SCCB_SendByte( DEV_ADR );                    /* ������ַ */
    if( !SCCB_WaitAck() )
    {
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




/******************************************************************************************************************
 * ��������SCCB_ReadByte
 * ����  ����ȡһ������
 * ����  ��- pBuffer: ��Ŷ�������  - length: ����������    - ReadAddress: ��������ַ        - DeviceAddress: ��������
 * ���  ������Ϊ:=1�ɹ�����,=0ʧ��
 * ע��  ����
 **********************************************************************************************************************/
static int SCCB_ReadByte_one(uint8_t *pBuffer,   uint16_t length,   uint8_t ReadAddress);

int SCCB_ReadByte(uint8_t *pBuffer,   uint16_t length,   uint8_t ReadAddress)
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

