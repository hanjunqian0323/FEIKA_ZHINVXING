#ifndef _K66ADC_H_
#define _K66ADC_H_


#include "main.h"


/* ----------------------------------------------------------------------------
   -- ADC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Peripheral ADC
 * @{
 */

/** ADC - Peripheral register structure */
typedef struct ADC_MemMap {
  uint32_t SC1[2];                                 /**< ADC Status and Control Registers 1, array offset: 0x0, array step: 0x4 */
  uint32_t CFG1;                                   /**< ADC Configuration Register 1, offset: 0x8 */
  uint32_t CFG2;                                   /**< ADC Configuration Register 2, offset: 0xC */
  uint32_t R[2];                                   /**< ADC Data Result Register, array offset: 0x10, array step: 0x4 */
  uint32_t CV1;                                    /**< Compare Value Registers, offset: 0x18 */
  uint32_t CV2;                                    /**< Compare Value Registers, offset: 0x1C */
  uint32_t SC2;                                    /**< Status and Control Register 2, offset: 0x20 */
  uint32_t SC3;                                    /**< Status and Control Register 3, offset: 0x24 */
  uint32_t OFS;                                    /**< ADC Offset Correction Register, offset: 0x28 */
  uint32_t PG;                                     /**< ADC Plus-Side Gain Register, offset: 0x2C */
  uint32_t MG;                                     /**< ADC Minus-Side Gain Register, offset: 0x30 */
  uint32_t CLPD;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x34 */
  uint32_t CLPS;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x38 */
  uint32_t CLP4;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x3C */
  uint32_t CLP3;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x40 */
  uint32_t CLP2;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x44 */
  uint32_t CLP1;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x48 */
  uint32_t CLP0;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x4C */
  uint8_t RESERVED_0[4];
  uint32_t CLMD;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x54 */
  uint32_t CLMS;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x58 */
  uint32_t CLM4;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x5C */
  uint32_t CLM3;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x60 */
  uint32_t CLM2;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x64 */
  uint32_t CLM1;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x68 */
  uint32_t CLM0;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x6C */
} volatile *ADC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */

#define SIM_SCGC6                                SIM_SCGC6_REG(SIM_BASE_PTR)
#define SIM_SOPT7                                SIM_SOPT7_REG(SIM_BASE_PTR)
#define SIM_SCGC3                                SIM_SCGC3_REG(SIM_BASE_PTR)

/* ADC - Register accessors */
#define ADC_SC1_REG(base,index)                  ((base)->SC1[index])
#define ADC_CFG1_REG(base)                       ((base)->CFG1)
#define ADC_CFG2_REG(base)                       ((base)->CFG2)
#define ADC_R_REG(base,index)                    ((base)->R[index])
#define ADC_CV1_REG(base)                        ((base)->CV1)
#define ADC_CV2_REG(base)                        ((base)->CV2)
#define ADC_SC2_REG(base)                        ((base)->SC2)
#define ADC_SC3_REG(base)                        ((base)->SC3)
#define ADC_OFS_REG(base)                        ((base)->OFS)
#define ADC_PG_REG(base)                         ((base)->PG)
#define ADC_MG_REG(base)                         ((base)->MG)
#define ADC_CLPD_REG(base)                       ((base)->CLPD)
#define ADC_CLPS_REG(base)                       ((base)->CLPS)
#define ADC_CLP4_REG(base)                       ((base)->CLP4)
#define ADC_CLP3_REG(base)                       ((base)->CLP3)
#define ADC_CLP2_REG(base)                       ((base)->CLP2)
#define ADC_CLP1_REG(base)                       ((base)->CLP1)
#define ADC_CLP0_REG(base)                       ((base)->CLP0)
#define ADC_CLMD_REG(base)                       ((base)->CLMD)
#define ADC_CLMS_REG(base)                       ((base)->CLMS)
#define ADC_CLM4_REG(base)                       ((base)->CLM4)
#define ADC_CLM3_REG(base)                       ((base)->CLM3)
#define ADC_CLM2_REG(base)                       ((base)->CLM2)
#define ADC_CLM1_REG(base)                       ((base)->CLM1)
#define ADC_CLM0_REG(base)                       ((base)->CLM0)

/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/* SC1 Bit Fields */
//#define ADC_SC1_ADCH_MASK                        0x1Fu
//#define ADC_SC1_ADCH_SHIFT                       0
//#define ADC_SC1_ADCH(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_ADCH_SHIFT))&ADC_SC1_ADCH_MASK)
//#define ADC_SC1_DIFF_MASK                        0x20u
//#define ADC_SC1_DIFF_SHIFT                       5
//#define ADC_SC1_AIEN_MASK                        0x40u
//#define ADC_SC1_AIEN_SHIFT                       6
//#define ADC_SC1_COCO_MASK                        0x80u
//#define ADC_SC1_COCO_SHIFT                       7
///* CFG1 Bit Fields */
//#define ADC_CFG1_ADICLK_MASK                     0x3u
//#define ADC_CFG1_ADICLK_SHIFT                    0
//#define ADC_CFG1_ADICLK(x)                       (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_ADICLK_SHIFT))&ADC_CFG1_ADICLK_MASK)
//#define ADC_CFG1_MODE_MASK                       0xCu
//#define ADC_CFG1_MODE_SHIFT                      2
//#define ADC_CFG1_MODE(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_MODE_SHIFT))&ADC_CFG1_MODE_MASK)
//#define ADC_CFG1_ADLSMP_MASK                     0x10u
//#define ADC_CFG1_ADLSMP_SHIFT                    4
//#define ADC_CFG1_ADIV_MASK                       0x60u
//#define ADC_CFG1_ADIV_SHIFT                      5
//#define ADC_CFG1_ADIV(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_ADIV_SHIFT))&ADC_CFG1_ADIV_MASK)
//#define ADC_CFG1_ADLPC_MASK                      0x80u
//#define ADC_CFG1_ADLPC_SHIFT                     7
///* CFG2 Bit Fields */
//#define ADC_CFG2_ADLSTS_MASK                     0x3u
//#define ADC_CFG2_ADLSTS_SHIFT                    0
//#define ADC_CFG2_ADLSTS(x)                       (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_ADLSTS_SHIFT))&ADC_CFG2_ADLSTS_MASK)
//#define ADC_CFG2_ADHSC_MASK                      0x4u
//#define ADC_CFG2_ADHSC_SHIFT                     2
//#define ADC_CFG2_ADACKEN_MASK                    0x8u
//#define ADC_CFG2_ADACKEN_SHIFT                   3
//#define ADC_CFG2_MUXSEL_MASK                     0x10u
//#define ADC_CFG2_MUXSEL_SHIFT                    4
///* R Bit Fields */
//#define ADC_R_D_MASK                             0xFFFFu
//#define ADC_R_D_SHIFT                            0
//#define ADC_R_D(x)                               (((uint32_t)(((uint32_t)(x))<<ADC_R_D_SHIFT))&ADC_R_D_MASK)
///* CV1 Bit Fields */
//#define ADC_CV1_CV_MASK                          0xFFFFu
//#define ADC_CV1_CV_SHIFT                         0
//#define ADC_CV1_CV(x)                            (((uint32_t)(((uint32_t)(x))<<ADC_CV1_CV_SHIFT))&ADC_CV1_CV_MASK)
///* CV2 Bit Fields */
//#define ADC_CV2_CV_MASK                          0xFFFFu
//#define ADC_CV2_CV_SHIFT                         0
//#define ADC_CV2_CV(x)                            (((uint32_t)(((uint32_t)(x))<<ADC_CV2_CV_SHIFT))&ADC_CV2_CV_MASK)
///* SC2 Bit Fields */
//#define ADC_SC2_REFSEL_MASK                      0x3u
//#define ADC_SC2_REFSEL_SHIFT                     0
//#define ADC_SC2_REFSEL(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_SC2_REFSEL_SHIFT))&ADC_SC2_REFSEL_MASK)
//#define ADC_SC2_DMAEN_MASK                       0x4u
//#define ADC_SC2_DMAEN_SHIFT                      2
//#define ADC_SC2_ACREN_MASK                       0x8u
//#define ADC_SC2_ACREN_SHIFT                      3
//#define ADC_SC2_ACFGT_MASK                       0x10u
//#define ADC_SC2_ACFGT_SHIFT                      4
//#define ADC_SC2_ACFE_MASK                        0x20u
//#define ADC_SC2_ACFE_SHIFT                       5
//#define ADC_SC2_ADTRG_MASK                       0x40u
//#define ADC_SC2_ADTRG_SHIFT                      6
//#define ADC_SC2_ADACT_MASK                       0x80u
//#define ADC_SC2_ADACT_SHIFT                      7
///* SC3 Bit Fields */
//#define ADC_SC3_AVGS_MASK                        0x3u
//#define ADC_SC3_AVGS_SHIFT                       0
//#define ADC_SC3_AVGS(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_AVGS_SHIFT))&ADC_SC3_AVGS_MASK)
//#define ADC_SC3_AVGE_MASK                        0x4u
//#define ADC_SC3_AVGE_SHIFT                       2
//#define ADC_SC3_ADCO_MASK                        0x8u
//#define ADC_SC3_ADCO_SHIFT                       3
//#define ADC_SC3_CALF_MASK                        0x40u
//#define ADC_SC3_CALF_SHIFT                       6
//#define ADC_SC3_CAL_MASK                         0x80u
//#define ADC_SC3_CAL_SHIFT                        7
///* OFS Bit Fields */
//#define ADC_OFS_OFS_MASK                         0xFFFFu
//#define ADC_OFS_OFS_SHIFT                        0
//#define ADC_OFS_OFS(x)                           (((uint32_t)(((uint32_t)(x))<<ADC_OFS_OFS_SHIFT))&ADC_OFS_OFS_MASK)
///* PG Bit Fields */
//#define ADC_PG_PG_MASK                           0xFFFFu
//#define ADC_PG_PG_SHIFT                          0
//#define ADC_PG_PG(x)                             (((uint32_t)(((uint32_t)(x))<<ADC_PG_PG_SHIFT))&ADC_PG_PG_MASK)
///* MG Bit Fields */
//#define ADC_MG_MG_MASK                           0xFFFFu
//#define ADC_MG_MG_SHIFT                          0
//#define ADC_MG_MG(x)                             (((uint32_t)(((uint32_t)(x))<<ADC_MG_MG_SHIFT))&ADC_MG_MG_MASK)
///* CLPD Bit Fields */
//#define ADC_CLPD_CLPD_MASK                       0x3Fu
//#define ADC_CLPD_CLPD_SHIFT                      0
//#define ADC_CLPD_CLPD(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLPD_CLPD_SHIFT))&ADC_CLPD_CLPD_MASK)
///* CLPS Bit Fields */
//#define ADC_CLPS_CLPS_MASK                       0x3Fu
//#define ADC_CLPS_CLPS_SHIFT                      0
//#define ADC_CLPS_CLPS(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLPS_CLPS_SHIFT))&ADC_CLPS_CLPS_MASK)
///* CLP4 Bit Fields */
//#define ADC_CLP4_CLP4_MASK                       0x3FFu
//#define ADC_CLP4_CLP4_SHIFT                      0
//#define ADC_CLP4_CLP4(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP4_CLP4_SHIFT))&ADC_CLP4_CLP4_MASK)
///* CLP3 Bit Fields */
//#define ADC_CLP3_CLP3_MASK                       0x1FFu
//#define ADC_CLP3_CLP3_SHIFT                      0
//#define ADC_CLP3_CLP3(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP3_CLP3_SHIFT))&ADC_CLP3_CLP3_MASK)
///* CLP2 Bit Fields */
//#define ADC_CLP2_CLP2_MASK                       0xFFu
//#define ADC_CLP2_CLP2_SHIFT                      0
//#define ADC_CLP2_CLP2(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP2_CLP2_SHIFT))&ADC_CLP2_CLP2_MASK)
///* CLP1 Bit Fields */
//#define ADC_CLP1_CLP1_MASK                       0x7Fu
//#define ADC_CLP1_CLP1_SHIFT                      0
//#define ADC_CLP1_CLP1(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP1_CLP1_SHIFT))&ADC_CLP1_CLP1_MASK)
///* CLP0 Bit Fields */
//#define ADC_CLP0_CLP0_MASK                       0x3Fu
//#define ADC_CLP0_CLP0_SHIFT                      0
//#define ADC_CLP0_CLP0(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP0_CLP0_SHIFT))&ADC_CLP0_CLP0_MASK)
///* CLMD Bit Fields */
//#define ADC_CLMD_CLMD_MASK                       0x3Fu
//#define ADC_CLMD_CLMD_SHIFT                      0
//#define ADC_CLMD_CLMD(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLMD_CLMD_SHIFT))&ADC_CLMD_CLMD_MASK)
///* CLMS Bit Fields */
//#define ADC_CLMS_CLMS_MASK                       0x3Fu
//#define ADC_CLMS_CLMS_SHIFT                      0
//#define ADC_CLMS_CLMS(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLMS_CLMS_SHIFT))&ADC_CLMS_CLMS_MASK)
///* CLM4 Bit Fields */
//#define ADC_CLM4_CLM4_MASK                       0x3FFu
//#define ADC_CLM4_CLM4_SHIFT                      0
//#define ADC_CLM4_CLM4(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLM4_CLM4_SHIFT))&ADC_CLM4_CLM4_MASK)
///* CLM3 Bit Fields */
//#define ADC_CLM3_CLM3_MASK                       0x1FFu
//#define ADC_CLM3_CLM3_SHIFT                      0
//#define ADC_CLM3_CLM3(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLM3_CLM3_SHIFT))&ADC_CLM3_CLM3_MASK)
///* CLM2 Bit Fields */
//#define ADC_CLM2_CLM2_MASK                       0xFFu
//#define ADC_CLM2_CLM2_SHIFT                      0
//#define ADC_CLM2_CLM2(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLM2_CLM2_SHIFT))&ADC_CLM2_CLM2_MASK)
///* CLM1 Bit Fields */
//#define ADC_CLM1_CLM1_MASK                       0x7Fu
//#define ADC_CLM1_CLM1_SHIFT                      0
//#define ADC_CLM1_CLM1(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLM1_CLM1_SHIFT))&ADC_CLM1_CLM1_MASK)
///* CLM0 Bit Fields */
//#define ADC_CLM0_CLM0_MASK                       0x3Fu
//#define ADC_CLM0_CLM0_SHIFT                      0
//#define ADC_CLM0_CLM0(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLM0_CLM0_SHIFT))&ADC_CLM0_CLM0_MASK)

/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base pointer */
#define ADC0_BASE_PTR                            ((ADC_MemMapPtr)0x4003B000u)
/** Peripheral ADC1 base pointer */
#define ADC1_BASE_PTR                            ((ADC_MemMapPtr)0x400BB000u)
/** Array initializer of ADC peripheral base pointers */
//#define ADC_BASE_PTRS                            { ADC0_BASE_PTR, ADC1_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register instance definitions */
/* ADC0 */
#define ADC0_SC1A                                ADC_SC1_REG(ADC0_BASE_PTR,0)
#define ADC0_SC1B                                ADC_SC1_REG(ADC0_BASE_PTR,1)
#define ADC0_CFG1                                ADC_CFG1_REG(ADC0_BASE_PTR)
#define ADC0_CFG2                                ADC_CFG2_REG(ADC0_BASE_PTR)
#define ADC0_RA                                  ADC_R_REG(ADC0_BASE_PTR,0)
#define ADC0_RB                                  ADC_R_REG(ADC0_BASE_PTR,1)
#define ADC0_CV1                                 ADC_CV1_REG(ADC0_BASE_PTR)
#define ADC0_CV2                                 ADC_CV2_REG(ADC0_BASE_PTR)
#define ADC0_SC2                                 ADC_SC2_REG(ADC0_BASE_PTR)
#define ADC0_SC3                                 ADC_SC3_REG(ADC0_BASE_PTR)
#define ADC0_OFS                                 ADC_OFS_REG(ADC0_BASE_PTR)
#define ADC0_PG                                  ADC_PG_REG(ADC0_BASE_PTR)
#define ADC0_MG                                  ADC_MG_REG(ADC0_BASE_PTR)
#define ADC0_CLPD                                ADC_CLPD_REG(ADC0_BASE_PTR)
#define ADC0_CLPS                                ADC_CLPS_REG(ADC0_BASE_PTR)
#define ADC0_CLP4                                ADC_CLP4_REG(ADC0_BASE_PTR)
#define ADC0_CLP3                                ADC_CLP3_REG(ADC0_BASE_PTR)
#define ADC0_CLP2                                ADC_CLP2_REG(ADC0_BASE_PTR)
#define ADC0_CLP1                                ADC_CLP1_REG(ADC0_BASE_PTR)
#define ADC0_CLP0                                ADC_CLP0_REG(ADC0_BASE_PTR)
#define ADC0_CLMD                                ADC_CLMD_REG(ADC0_BASE_PTR)
#define ADC0_CLMS                                ADC_CLMS_REG(ADC0_BASE_PTR)
#define ADC0_CLM4                                ADC_CLM4_REG(ADC0_BASE_PTR)
#define ADC0_CLM3                                ADC_CLM3_REG(ADC0_BASE_PTR)
#define ADC0_CLM2                                ADC_CLM2_REG(ADC0_BASE_PTR)
#define ADC0_CLM1                                ADC_CLM1_REG(ADC0_BASE_PTR)
#define ADC0_CLM0                                ADC_CLM0_REG(ADC0_BASE_PTR)
/* ADC1 */
#define ADC1_SC1A                                ADC_SC1_REG(ADC1_BASE_PTR,0)
#define ADC1_SC1B                                ADC_SC1_REG(ADC1_BASE_PTR,1)
#define ADC1_CFG1                                ADC_CFG1_REG(ADC1_BASE_PTR)
#define ADC1_CFG2                                ADC_CFG2_REG(ADC1_BASE_PTR)
#define ADC1_RA                                  ADC_R_REG(ADC1_BASE_PTR,0)
#define ADC1_RB                                  ADC_R_REG(ADC1_BASE_PTR,1)
#define ADC1_CV1                                 ADC_CV1_REG(ADC1_BASE_PTR)
#define ADC1_CV2                                 ADC_CV2_REG(ADC1_BASE_PTR)
#define ADC1_SC2                                 ADC_SC2_REG(ADC1_BASE_PTR)
#define ADC1_SC3                                 ADC_SC3_REG(ADC1_BASE_PTR)
#define ADC1_OFS                                 ADC_OFS_REG(ADC1_BASE_PTR)
#define ADC1_PG                                  ADC_PG_REG(ADC1_BASE_PTR)
#define ADC1_MG                                  ADC_MG_REG(ADC1_BASE_PTR)
#define ADC1_CLPD                                ADC_CLPD_REG(ADC1_BASE_PTR)
#define ADC1_CLPS                                ADC_CLPS_REG(ADC1_BASE_PTR)
#define ADC1_CLP4                                ADC_CLP4_REG(ADC1_BASE_PTR)
#define ADC1_CLP3                                ADC_CLP3_REG(ADC1_BASE_PTR)
#define ADC1_CLP2                                ADC_CLP2_REG(ADC1_BASE_PTR)
#define ADC1_CLP1                                ADC_CLP1_REG(ADC1_BASE_PTR)
#define ADC1_CLP0                                ADC_CLP0_REG(ADC1_BASE_PTR)
#define ADC1_CLMD                                ADC_CLMD_REG(ADC1_BASE_PTR)
#define ADC1_CLMS                                ADC_CLMS_REG(ADC1_BASE_PTR)
#define ADC1_CLM4                                ADC_CLM4_REG(ADC1_BASE_PTR)
#define ADC1_CLM3                                ADC_CLM3_REG(ADC1_BASE_PTR)
#define ADC1_CLM2                                ADC_CLM2_REG(ADC1_BASE_PTR)
#define ADC1_CLM1                                ADC_CLM1_REG(ADC1_BASE_PTR)
#define ADC1_CLM0                                ADC_CLM0_REG(ADC1_BASE_PTR)

/* ADC - Register array accessors */
#define ADC0_SC1(index)                          ADC_SC1_REG(ADC0_BASE_PTR,index)
#define ADC1_SC1(index)                          ADC_SC1_REG(ADC1_BASE_PTR,index)
#define ADC0_R(index)                            ADC_R_REG(ADC0_BASE_PTR,index)
#define ADC1_R(index)                            ADC_R_REG(ADC1_BASE_PTR,index)

/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ADC_Peripheral */




typedef enum
{
    // ---------------------------------ADC0-------------------------
    RES60,
    RES61,
    PGA0_DP,        //不支持ADC，需要配置 ADC PGA register 设置放大增益
    ADC0_DP3,
    //软件触发不支持B通道
    ADC0_SE4b,      // PTC2     不支持软件ADC
    ADC0_SE5b,      // PTD1     不支持软件ADC
    ADC0_SE6b,      // PTD5     不支持软件ADC
    ADC0_SE7b,      // PTD6     不支持软件ADC

    ADC0_SE8,       // PTB0
    ADC0_SE9,       // PTB1
    ADC0_SE10,      // PTA7
    ADC0_SE11,      // PTA8
    ADC0_SE12,      // PTB2
    ADC0_SE13,      // PTB3
    ADC0_SE14,      // PTC0
    ADC0_SE15,      // PTC1
    ADC0_SE16,      // ADC0_SE16
    ADC0_SE17,      // PTE24
    ADC0_SE18,      // PTE25
    ADC0_DM0,       // ADC0_DM0
    RES62,          // 保留
    RES0,           // 保留
    RES1,           // 保留
    DAC0_OUT,       // DAC0输出 不支持ADC
    RES2,           // 保留
    RES3,           // 保留
    Temp0_Sensor,   // Temperature Sensor,内部温度测量，可用ADC函数
    Bandgap0,       // 温度补偿结构带隙基准源   不支持ADC
    RES4,           // 保留
    VREFH0,         // 参考高电压,可用ADC函数 ,结果恒为 2^n-1
    VREFL0,         // 参考低电压,可用ADC函数 ,结果恒为 0
    Module0_Dis,    // 不支持 ADC

    // ---------------------------------ADC1-------------------------
    ADC1_DP0,
    RES63,
    PGA1_DP,        // 不支持 ADC
    ADC1_DP3,
    ADC1_SE4a,      // PTE0
    ADC1_SE5a,      // PTE1
    ADC1_SE6a,      // PTE2
    ADC1_SE7a,      // PTE3

    ADC1_SE4b = ADC1_SE4a,  // PTC8     不支持软件ADC ,传递 ADC1_SE4b 到软件ADC函数里，会当作 ADC1_SE4a 处理。
    ADC1_SE5b = ADC1_SE5a,  // PTC9     不支持软件ADC
    ADC1_SE6b = ADC1_SE6a,  // PTC10    不支持软件ADC
    ADC1_SE7b = ADC1_SE7a,  // PTC11    不支持软件ADC

    ADC1_SE8,       // PTB0
    ADC1_SE9,       // PTB1
    ADC1_SE10,      // PTB4
    ADC1_SE11,      // PTB5
    ADC1_SE12,      // PTB6
    ADC1_SE13,      // PTB7
    ADC1_SE14,      // PTB10
    ADC1_SE15,      // PTB11
    ADC1_SE16,      // ADC1_SE16
    ADC1_SE17,      // PTA17
    VREF_OUTPUT,    // VREF Output
    ADC1_DM0,       // ADC1_DM0
    RES64,          //保留
    RES5,           //保留
    RES6,
    DAC1_OUT,
    RES7,           //保留
    RES8,
    Temp1_Sensor,
    Bandgap1,       // 温度补偿结构带隙基准源   不支持ADC
    RES9,
    VREFH1,         // 参考高电压,可用ADC函数 ,结果恒为 2^n-1
    VREFL1,         // 参考低电压,可用ADC函数 ,结果恒为 0
    Module1_Dis,    // 不支持 ADC

} ADCn_Ch_e;

typedef enum  //ADC模块
{
    ADC0,
    ADC1
} ADCn_e;

//精度位数
typedef enum ADC_nbit
{
    ADC_8bit   = 0x00,
    ADC_10bit  = 0x02,
    ADC_12bit  = 0x01,
    ADC_16bit  = 0x03
} ADC_nbit;


//外部函数接口声明
//extern void     adc_init    (ADCn_Ch_e);                //ADC初始化
void adc_init(void);                //ADC初始化
uint16_t adc_once(ADCn_Ch_e, ADC_nbit);      //采集一次一路模拟量的AD值
void adc_stop(ADCn_e);                   //停止ADC转换










#endif

