#include "SCCB.h"

static void SCCB_delay(volatile uint16_t time)//400
{
    while(time)
    {
        time--;
    }
}

void SDA_LOGIC_CHANGE(uint8_t LOGIC)//1：输出	0：输入
{
	gpio_pin_config_t SCCBconfig;//GPIO初始化句柄
	if(LOGIC == 1)
	{
		SCCBconfig.pinDirection = kGPIO_DigitalOutput;//配置为输出模式
		GPIO_PinInit(SCCB_GPIO,SCCB_SDA_PIN,&SCCBconfig); //GPIO初始化
	}
	else if(LOGIC == 0)
	{
		SCCBconfig.pinDirection = kGPIO_DigitalInput;//配置为输出模式
		GPIO_PinInit(SCCB_GPIO,SCCB_SDA_PIN,&SCCBconfig); //GPIO初始化
	}
}


void SCCB_GPIO_init(void)
{
	gpio_pin_config_t SCCBconfig;//GPIO初始化句柄
	port_pin_config_t SCCBPORTconfig;//PORT初始化句柄
	
	SCCBPORTconfig.openDrainEnable = 1;//开漏
	SCCBPORTconfig.pullSelect = 2;//上拉
	PORT_SetMultiplePinsConfig(SCCB_PORT,SCCB_SCL_PIN,&SCCBPORTconfig);//PORT初始化
	PORT_SetMultiplePinsConfig(SCCB_PORT,SCCB_SDA_PIN,&SCCBPORTconfig);//PORT初始化
	PORT_SetPinMux(SCCB_PORT,SCCB_SCL_PIN,kPORT_MuxAsGpio);//SCL引脚复用
	PORT_SetPinMux(SCCB_PORT,SCCB_SDA_PIN,kPORT_MuxAsGpio);//SDA引脚复用
	
	SCCBconfig.pinDirection = kGPIO_DigitalOutput;//配置为输出模式
    SCCBconfig.outputLogic = 1;//输出1
    
    GPIO_PinInit(SCCB_GPIO,SCCB_SCL_PIN,&SCCBconfig); //GPIO初始化
    GPIO_PinInit(SCCB_GPIO,SCCB_SDA_PIN,&SCCBconfig); //GPIO初始化
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
        return 0;   /* SDA线为低电平则总线忙,退出 */
    }
    SDA_DDR_OUT();
    SDA_L();

    SCCB_DELAY();
    SCL_L();

    if(SDA_IN())
    {
        SDA_DDR_OUT();
        return 0;   /* SDA线为高电平则总线出错,退出 */
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
 *  @brief      SCCB应答信号
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
 *  @brief      SCCB无应答信号
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
 *  @brief      SCCB 等待应答
 *  @return     应答结果（0表示无应答，1表示有应答）
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

    if(SDA_IN())           //应答为高电平，异常，通信失败
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
 *  @brief      SCCB 发送的数据
 *  @param      SendByte    需要发送的数据
 *  @since      v5.0
 */
static void SCCB_SendByte(uint8_t SendByte)
{
    uint8_t i = 8;
    while(i--)
    {

        if(SendByte & 0x80)     //SDA 输出数据
        {
            SDA_H();
        }
        else
        {
            SDA_L();
        }
        SendByte <<= 1;
        SCCB_DELAY();
        SCL_H();                //SCL 拉高，采集信号
        SCCB_DELAY();
        SCL_L();                //SCL 时钟线拉低
        //SCCB_DELAY();
    }
    //SCL_L();
}

/*!
 *  @brief      接收SCCB总线的数据
 *  @return     接收到的数据
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
* 函数名：SCCB_WriteByte
* 描述  ：写一字节数据
* 输入  ：- WriteAddress: 待写入地址    - SendByte: 待写入数据  - DeviceAddress: 器件类型
* 输出  ：返回为:=1成功写入,=0失败
* 注意  ：无
*****************************************************************************************/
static int SCCB_WriteByte_one( uint16_t WriteAddress , uint8_t SendByte );


int SCCB_WriteByte( uint16_t WriteAddress , uint8_t SendByte )            //考虑到用sccb的管脚模拟，比较容易失败，因此多试几次
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
    SCCB_SendByte( DEV_ADR );                    /* 器件地址 */
    if( !SCCB_WaitAck() )
    {
        SCCB_Stop();
        return 0;
    }
    SCCB_SendByte((uint8_t)(WriteAddress & 0x00FF));   /* 设置低起始地址 */
    SCCB_WaitAck();
    SCCB_SendByte(SendByte);
    SCCB_WaitAck();
    SCCB_Stop();
    return 1;
}




/******************************************************************************************************************
 * 函数名：SCCB_ReadByte
 * 描述  ：读取一串数据
 * 输入  ：- pBuffer: 存放读出数据  - length: 待读出长度    - ReadAddress: 待读出地址        - DeviceAddress: 器件类型
 * 输出  ：返回为:=1成功读入,=0失败
 * 注意  ：无
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
    SCCB_SendByte( DEV_ADR );         /* 器件地址 */
    if( !SCCB_WaitAck() )
    {
        SCCB_Stop();
        return 0;
    }
    SCCB_SendByte( ReadAddress );           /* 设置低起始地址 */
    SCCB_WaitAck();
    SCCB_Stop();

    if(!SCCB_Start())
    {
        return 0;
    }
    SCCB_SendByte( DEV_ADR + 1 );               /* 器件地址 */

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

