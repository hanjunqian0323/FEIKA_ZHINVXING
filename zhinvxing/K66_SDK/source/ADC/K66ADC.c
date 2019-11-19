#include "K66ADC.h"

ADC_MemMapPtr ADCN[2] = {ADC0_BASE_PTR, ADC1_BASE_PTR}; //定义两个指针数组保存 ADCN 的地址

static void  adc_start   (ADCn_Ch_e, ADC_nbit);    //开始adc转换

void adc_init(void)
{
	//开启时钟：
    CLOCK_EnableClock(kCLOCK_Adc0);
	CLOCK_EnableClock(kCLOCK_Adc1);
	
	PORT_SetPinMux(ADC1_PORT,ADC1_PIN,kPORT_PinDisabledOrAnalog);	//PTA7		ADC0_SE10
	PORT_SetPinMux(ADC2_PORT,ADC2_PIN,kPORT_PinDisabledOrAnalog);	//PTC0		ADC0_SE14
	PORT_SetPinMux(PORTE,25U,kPORT_PinDisabledOrAnalog);			//PTE25		ADC0_SE18
	PORT_SetPinMux(PORTE,0U,kPORT_PinDisabledOrAnalog);				//PTE0		ADC1_SE4a
	PORT_SetPinMux(PORTE,24U,kPORT_PinDisabledOrAnalog);			//PTE24		ADC0_SE17
	PORT_SetPinMux(PORTA,17U,kPORT_PinDisabledOrAnalog);			//PTA17		ADC1_SE17
}

/*!
 *  @brief      获取ADC采样值(不支持B通道)
 *  @param      ADCn_Ch_e    ADC通道
 *  @param      ADC_nbit     ADC精度（ ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ）
 *  @return     采样值
 *  @since      v5.0
 *  Sample usage:       uint16 var = adc_once(ADC0_SE10, ADC_8bit);
 */
uint16_t adc_once(ADCn_Ch_e adcn_ch, ADC_nbit bit) //采集某路模拟量的AD值
{
    ADCn_e adcn = (ADCn_e)(adcn_ch >> 5) ;

    uint16_t result = 0;

    adc_start(adcn_ch, bit);      //启动ADC转换

    while (( ADC_SC1_REG(ADCN[adcn], 0 ) & ADC_SC1_COCO_MASK ) != ADC_SC1_COCO_MASK);   //只支持 A通道
    result = ADC_R_REG(ADCN[adcn], 0);
    ADC_SC1_REG(ADCN[adcn], 0) &= ~ADC_SC1_COCO_MASK;
    return result;
}

/*!
 *  @brief      启动ADC软件采样(不支持B通道)
 *  @param      ADCn_Ch_e    ADC通道
 *  @param      ADC_nbit     ADC精度（ ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ）
 *  @since      v5.0
 *  @note       此函数内部调用，启动后即可等待数据采集完成
 *  Sample usage:       adc_start(ADC0_SE10, ADC_8bit);
 */
void adc_start(ADCn_Ch_e adcn_ch, ADC_nbit bit)
{
    ADCn_e adcn = (ADCn_e)(adcn_ch >> 5) ;
    uint8_t ch = (uint8_t)(adcn_ch & 0x1F);

    //初始化ADC默认配置
    ADC_CFG1_REG(ADCN[adcn]) = (0
                                //| ADC_CFG1_ADLPC_MASK         //ADC功耗配置，0为正常功耗，1为低功耗
                                | ADC_CFG1_ADIV(2)              //时钟分频选择,分频系数为 2^n,2bit
                                | ADC_CFG1_ADLSMP_MASK          //采样时间配置，0为短采样时间，1 为长采样时间
                                | ADC_CFG1_MODE(bit)
                                | ADC_CFG1_ADICLK(0)            //0为总线时钟,1为总线时钟/2,2为交替时钟（ALTCLK），3为 异步时钟（ADACK）。
                               );


    ADC_CFG2_REG(ADCN[adcn])  = (0
                                 //| ADC_CFG2_MUXSEL_MASK       //ADC复用选择,0为a通道，1为b通道。
                                 //| ADC_CFG2_ADACKEN_MASK      //异步时钟输出使能,0为禁止，1为使能。
                                 | ADC_CFG2_ADHSC_MASK          //高速配置,0为正常转换序列，1为高速转换序列
                                 | ADC_CFG2_ADLSTS(0)           //长采样时间选择，ADCK为4+n个额外循环，额外循环，0为20，1为12，2为6，3为2
                                );

    //写入 SC1A 启动转换
    ADC_SC1_REG(ADCN[adcn], 0 ) = (0
                                   | ADC_SC1_AIEN_MASK          // 转换完成中断,0为禁止，1为使能
                                   //| ADC_SC1_DIFF_MASK        // 差分模式使能,0为单端，1为差分
                                   | ADC_SC1_ADCH( ch )
                                  );

}

/*!
 *  @brief      停止ADC软件采样
 *  @param      ADCn_e       ADC模块号（ ADC0、 ADC1）
 *  @since      v5.0
 *  Sample usage:       adc_stop(ADC0);
 */
void adc_stop(ADCn_e adcn)
{
    ADC_SC1_REG(ADCN[adcn], 0) = (0
                                  | ADC_SC1_AIEN_MASK                       // 转换完成中断,0为禁止，1为使能
                                  //| ADC_SC1_DIFF_MASK                     // 差分模式使能,0为单端，1为差分
                                  | ADC_SC1_ADCH(Module0_Dis)               //输入通道选择,此处选择禁止通道
                                 );
}


/*
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
*/


