#include "K66ADC.h"

ADC_MemMapPtr ADCN[2] = {ADC0_BASE_PTR, ADC1_BASE_PTR}; //��������ָ�����鱣�� ADCN �ĵ�ַ

static void  adc_start   (ADCn_Ch_e, ADC_nbit);    //��ʼadcת��

void adc_init(void)
{
	//����ʱ�ӣ�
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
 *  @brief      ��ȡADC����ֵ(��֧��Bͨ��)
 *  @param      ADCn_Ch_e    ADCͨ��
 *  @param      ADC_nbit     ADC���ȣ� ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ��
 *  @return     ����ֵ
 *  @since      v5.0
 *  Sample usage:       uint16 var = adc_once(ADC0_SE10, ADC_8bit);
 */
uint16_t adc_once(ADCn_Ch_e adcn_ch, ADC_nbit bit) //�ɼ�ĳ·ģ������ADֵ
{
    ADCn_e adcn = (ADCn_e)(adcn_ch >> 5) ;

    uint16_t result = 0;

    adc_start(adcn_ch, bit);      //����ADCת��

    while (( ADC_SC1_REG(ADCN[adcn], 0 ) & ADC_SC1_COCO_MASK ) != ADC_SC1_COCO_MASK);   //ֻ֧�� Aͨ��
    result = ADC_R_REG(ADCN[adcn], 0);
    ADC_SC1_REG(ADCN[adcn], 0) &= ~ADC_SC1_COCO_MASK;
    return result;
}

/*!
 *  @brief      ����ADC�������(��֧��Bͨ��)
 *  @param      ADCn_Ch_e    ADCͨ��
 *  @param      ADC_nbit     ADC���ȣ� ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ��
 *  @since      v5.0
 *  @note       �˺����ڲ����ã������󼴿ɵȴ����ݲɼ����
 *  Sample usage:       adc_start(ADC0_SE10, ADC_8bit);
 */
void adc_start(ADCn_Ch_e adcn_ch, ADC_nbit bit)
{
    ADCn_e adcn = (ADCn_e)(adcn_ch >> 5) ;
    uint8_t ch = (uint8_t)(adcn_ch & 0x1F);

    //��ʼ��ADCĬ������
    ADC_CFG1_REG(ADCN[adcn]) = (0
                                //| ADC_CFG1_ADLPC_MASK         //ADC�������ã�0Ϊ�������ģ�1Ϊ�͹���
                                | ADC_CFG1_ADIV(2)              //ʱ�ӷ�Ƶѡ��,��Ƶϵ��Ϊ 2^n,2bit
                                | ADC_CFG1_ADLSMP_MASK          //����ʱ�����ã�0Ϊ�̲���ʱ�䣬1 Ϊ������ʱ��
                                | ADC_CFG1_MODE(bit)
                                | ADC_CFG1_ADICLK(0)            //0Ϊ����ʱ��,1Ϊ����ʱ��/2,2Ϊ����ʱ�ӣ�ALTCLK����3Ϊ �첽ʱ�ӣ�ADACK����
                               );


    ADC_CFG2_REG(ADCN[adcn])  = (0
                                 //| ADC_CFG2_MUXSEL_MASK       //ADC����ѡ��,0Ϊaͨ����1Ϊbͨ����
                                 //| ADC_CFG2_ADACKEN_MASK      //�첽ʱ�����ʹ��,0Ϊ��ֹ��1Ϊʹ�ܡ�
                                 | ADC_CFG2_ADHSC_MASK          //��������,0Ϊ����ת�����У�1Ϊ����ת������
                                 | ADC_CFG2_ADLSTS(0)           //������ʱ��ѡ��ADCKΪ4+n������ѭ��������ѭ����0Ϊ20��1Ϊ12��2Ϊ6��3Ϊ2
                                );

    //д�� SC1A ����ת��
    ADC_SC1_REG(ADCN[adcn], 0 ) = (0
                                   | ADC_SC1_AIEN_MASK          // ת������ж�,0Ϊ��ֹ��1Ϊʹ��
                                   //| ADC_SC1_DIFF_MASK        // ���ģʽʹ��,0Ϊ���ˣ�1Ϊ���
                                   | ADC_SC1_ADCH( ch )
                                  );

}

/*!
 *  @brief      ֹͣADC�������
 *  @param      ADCn_e       ADCģ��ţ� ADC0�� ADC1��
 *  @since      v5.0
 *  Sample usage:       adc_stop(ADC0);
 */
void adc_stop(ADCn_e adcn)
{
    ADC_SC1_REG(ADCN[adcn], 0) = (0
                                  | ADC_SC1_AIEN_MASK                       // ת������ж�,0Ϊ��ֹ��1Ϊʹ��
                                  //| ADC_SC1_DIFF_MASK                     // ���ģʽʹ��,0Ϊ���ˣ�1Ϊ���
                                  | ADC_SC1_ADCH(Module0_Dis)               //����ͨ��ѡ��,�˴�ѡ���ֹͨ��
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


