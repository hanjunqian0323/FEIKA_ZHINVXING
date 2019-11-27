#include "DMA.h"

static void dma_gpio_input_init()//摄像头8个传输引脚初始化
{
    /*uint8_t n, tmp;
    uint8_t ptxn;

    //SADDR 实际上就是 GPIO的 输入寄存器 PDIR 的地址
    //GPIOA、GPIOB、GPIOC、GPIOD、GPIOE 的地址 分别是 0x400FF000u 、0x400FF040u 、0x400FF080u、 0x400FF0C0u、0x400FF100u
    //sizeof(GPIO_MemMap) = 0x18
    //每个GPIO地址 &0x1C0 后，得到 0x000 , 0x040 , 0x080 ,0x0C0 ,0x100
    //再 /0x40 后得到 0 、 1 、 2、 3、4 ，刚好就是 PTA、PTB、PTC 、PTD 、PTE
    //再 *32 就等于 PTA0、PTB0、PTC0 、PTD0 、PTE0
    uint8_t ptx0 = ((((uint32_t)SADDR) & 0x1C0) / 0x40 ) * 32;

    //每个GPIO 对应的寄存器地址， &0x 3F 后得到的值都是相同的。
    //PTA_B0_IN 即 GPIOA 的 输入寄存器 PDIR 的 地址
    // (SADDR & 0x3f - PTA_B0_IN & 0x3f) 等效于 (SADDR - PTA_B0_IN) & 0x3f
    //假设需要采集的位 为 0~7、8~15、16~23、24~31 ，则 上面式子对应的值 为 0、1、2、3
    //刚好是  0~7、8~15、16~23、24~31 位的地址偏移，再 * 8 就变成 0、8、16、24

    n = (uint8_t)(((uint32_t)SADDR - ((uint32_t)(&PTA_B0_IN))) & 0x3f) * 8;       //最小的引脚号

    ptxn = ptx0 + n;
    tmp = ptxn + (BYTEs * 8 ) - 1;                                          //最大的引脚号
    while(ptxn <= tmp)
    {
        //这里加入 GPIO 初始化为输入
        gpio_init((PTXn_e )ptxn, GPI, 0);               //设置为输入
        port_init((PTXn_e )ptxn , ALT1 | PULLDOWN );    //输入源默认配置为下拉，默认读取到的是0
        ptxn ++;
    }*/
	uint16_t i = 0;
	gpio_pin_config_t DMAconfig;//GPIO初始化句柄
	port_pin_config_t DMAPORTconfig;//PORT初始化句柄
	
	DMAPORTconfig.pullSelect = 1;//下拉
	DMAconfig.pinDirection = kGPIO_DigitalInput;//GPIO配置为输入模式
	
	for(i=0;i<8;i++)//y0-y7共8个引脚
	{
		PORT_SetMultiplePinsConfig(PORTB,i,&DMAPORTconfig);//PORT初始化
		PORT_SetPinMux(PORTB,i,kPORT_MuxAsGpio);//SCL引脚复用
		GPIO_PinInit(GPIOB,i,&DMAconfig); //GPIO初始化
    }
}

/*!
 *  @brief      DMA初始化，由IO口请求传输输入端口的数据到内存
 *  @param      DMA_CHn         通道号（DMA_CH0 ~ DMA_CH15）
 *  @param      SADDR           源地址( (void * )&PTx_Bn_IN 或 (void * )&PTx_Wn_IN 或 (void * )&PTx_IN  )
 *  @param      DADDR           目的地址
 *  @param      PTxn            触发端口
 *  @param      DMA_BYTEn       每次DMA传输字节数
 *  @param      count           一个主循环传输字节数
 *  @param      cfg             DMA传输配置，从DMA_cfg里选择
 *  @since      v5.0
 *  @note       DMA PTXn触发源默认上升沿触发传输，若需修改，则初始化后调用 port_init 配置DMA 触发方式
                初始化后，需要调用 DMA_EN 来实现
 *  Sample usage:   uint8 buff[10];
                    dma_portx2buff_init(DMA_CH0, PTB_B0_IN, buff, PTA7, DMA_BYTE1, 10, DADDR_RECOVER);
                    //DMA初始化，源地址：PTB_B0_IN，目的地址：buff,PTA7触发(默认上升沿)，每次传输1字节，共传输 10次 ，传输结束后恢复地址

                    port_init(PTA7,ALT1 | DMA_FALLING);             //默认触发源是上升沿，此处改为 下降沿触发

                    DMA_EN(DMA_CH0);                //需要使能 DMA 后才能传输数据
 */
void dma_portx2buff_init(DMA_CHn CHn,uint32_t SADDR, void *DADDR, DMA_BYTEn byten, uint32_t count, uint32_t cfg)
{

    uint8_t BYTEs = (byten == DMA_BYTE1 ? 1 : (byten == DMA_BYTE2 ? 2 : (byten == DMA_BYTE4 ? 4 : 16 ) ) ); //计算传输字节数

    //断言，检测传递进来参数是否正确
    /*ASSERT(                                             //用断言检测 源地址和每次传输字节数是否正确
        (   (byten == DMA_BYTE1)                    //传输一个字节
            && ( (SADDR >= &PTA_B0_IN) && (SADDR <= ( &PTE_B3_IN )))
        )

        || (   (byten == DMA_BYTE2)                   //传输两个字节(注意，不能跨端口)
               && ( (SADDR >= &PTA_B0_IN)
                    && (SADDR <= ( &PTE_W1_IN ))
                    && (((uint32_t)SADDR & 0x03) != 0x03) )         //保证不跨端口
           )

        || (   (byten == DMA_BYTE4)                   //传输四个字节
               && ((SADDR >= &PTA_B0_IN) && (SADDR <= ( &PTE_B0_IN )))
               && (((uint32_t)SADDR & 0x03) == 0x00)           //保证不跨端口
           )
    );

    ASSERT(count < 0x8000); //断言，最大只支持0x7FFF*/

    //DMA 寄存器 配置

    /* 开启时钟已经在BOARD_InitPins中使能 */
    /*SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //打开DMA模块时钟*/

#if  defined(MK66F18)
    SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                    //打开DMA多路复用器时钟
#endif

    /* 配置 DMA 通道 的 传输控制块 TCD ( Transfer Control Descriptor ) */
    DMA_SADDR_SADDR((uint32_t)SADDR);                      // 设置  源地址
    DMA_DADDR_DADDR((uint32_t)DADDR);                      // 设置目的地址
    DMA_SOFF_SOFF(0x00u);                              // 设置源地址偏移 = 0x0, 即不变
    DMA_DOFF_DOFF(BYTEs);                              // 每次传输后，目的地址加 BYTEs
	DMA0->TCD->ATTR  =    (0
						   | DMA_ATTR_SMOD(0x0)               // 源地址模数禁止  Source address modulo feature is disabled
						   | DMA_ATTR_SSIZE(byten)            // 源数据位宽 ：DMA_BYTEn  。    SSIZE = 0 -> 8-bit ，SSIZE = 1 -> 16-bit ，SSIZE = 2 -> 32-bit ，SSIZE = 4 -> 16-byte
						   | DMA_ATTR_DMOD(0x0)               // 目标地址模数禁止
						   | DMA_ATTR_DSIZE(byten)            // 目标数据位宽 ：DMA_BYTEn  。  设置参考  SSIZE
						   );

   

    DMA0->TCD->CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(count);   //当前主循环次数
	DMA0->TCD->BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(count);   //起始主循环次数

    DMA0->CR &= ~DMA_CR_EMLM_MASK;                                // CR[EMLM] = 0

    //当CR[EMLM] = 0 时:
    DMA_NBYTES_MLNO_NBYTES(BYTEs); // 通道每次传输字节数，这里设置为BYTEs个字节。注：值为0表示传输4GB */

    /* 配置 DMA 传输结束后的操作 */
    DMA_SLAST_SLAST(0);                              //调整  源地址的附加值,主循环结束后恢复  源地址
    DMA_DLAST_SGA_DLASTSGA((uint32_t)( (cfg & DADDR_KEEPON ) == 0 ? (-count)  : 0 )); //调整目的地址的附加值,主循环结束后恢复目的地址或者保持地址
//    DMA_CSR(CHn)        =   (0
//                             | DMA_CSR_BWC(3)               //带宽控制,每读一次，eDMA 引擎停止 8 个周期（0不停止；1保留；2停止4周期；3停止8周期）
//                             | DMA_CSR_DREQ_MASK            //主循环结束后停止硬件请求
//                             | DMA_CSR_INTMAJOR_MASK        //主循环结束后产生中断
//                            );
	DMA0->TCD->CSR      =   (0
                             | DMA_CSR_BWC(3)               //带宽控制,每读一次，eDMA 引擎停止 8 个周期（0不停止；1保留；2停止4周期；3停止8周期）
                             | DMA_CSR_DREQ_MASK            //主循环结束后停止硬件请求
                             | DMA_CSR_INTMAJOR_MASK        //主循环结束后产生中断
                            );


    /* 配置 DMA 触发源 */
//#if defined(MK66F18)
//    DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR, CHn) = (0
//#endif
DMAMUX->CHCFG[0]= (0
            | DMAMUX_CHCFG_ENBL_MASK                        /* Enable routing of DMA request */
            //| DMAMUX_CHCFG_TRIG_MASK                        /* Trigger Mode: Periodic   PIT周期触发传输模式   通道1对应PIT1，必须使能PIT1，且配置相应的PIT定时触发 */
            | DMAMUX_CHCFG_SOURCE(DMA_PORTA) /* 通道触发传输源:     */
                                             );


    //DMA_DIS(CHn);                                    //禁止通道CHn 硬件请求
    //DMA_IRQ_CLEAN(CHn);

    DMA_DIS(CHn);                                    //禁止通道CHn 硬件请求
	
    EDMA_ClearChannelStatusFlags(DMA0,0,kEDMA_InterruptFlag); //清除通道传输中断标志位
	
    //配置触发源（默认是 上升沿触发）			A27
    //port_init(ptxn, ALT1 | DMA_RISING);

    /*  配置输入源   */
    dma_gpio_input_init();


    /* 开启中断 */
    //DMA_EN(CHn);                                    //使能通道CHn 硬件请求
    //DMA_IRQ_EN(CHn);                                //允许DMA通道传输
}
