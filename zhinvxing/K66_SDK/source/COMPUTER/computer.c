#include "computer.h"


/*!
 *  @brief      ɽ��๦�ܵ���������λ��������ͷ��ʾ����
 *  @param      imgaddr    ͼ����ʼ��ַ
 *  @param      imgsize    ͼ��ռ�ÿռ�Ĵ�С
 *  @since      v5.0
*  Sample usage:
             �����÷��ο�������:
            ��ɽ������ͷ��ӥ����λ�����̺�΢��Ч�� - ���ܳ�������
             http://vcan123.com/forum.php?mod=viewthread&tid=6242&ctid=27
 */
void vcan_sendimg(void *imgaddr, uint32_t imgsize)
{
#define CMD_IMG     1
    uint8_t cmdf[2] = {CMD_IMG, ~CMD_IMG};    //ɽ����λ�� ʹ�õ�����
    uint8_t cmdr[2] = {~CMD_IMG, CMD_IMG};    //ɽ����λ�� ʹ�õ�����

    UART_WRETE_BUFF(cmdf, sizeof(cmdf));    //�ȷ�������

    UART_WRETE_BUFF((uint8_t *)imgaddr, imgsize); //�ٷ���ͼ��

    UART_WRETE_BUFF(cmdr, sizeof(cmdr));    //�ȷ�������
}


/*!
 *  @brief      ɽ��๦�ܵ���������λ��������CCD��ʾ����
 *  @param      ccdaddr    CCDͼ����ʼ��ַ
 *  @param      ccdsize    CCDͼ��ռ�ÿռ�Ĵ�С
 *  @since      v5.0
*  Sample usage:
             �����÷��ο�������:
            ��ɽ������CCD����λ����ʾ���̺ͳ���ǲɼ�Ч�� - ���ܳ�������
             http://vcan123.com/forum.php?mod=viewthread&tid=6340&ctid=27
 */
void vcan_sendccd(void *ccdaddr, uint32_t ccdsize)
{
#define CMD_CCD     2
    uint8_t cmdf[2] = {CMD_CCD, ~CMD_CCD};    //��ͷ����
    uint8_t cmdr[2] = {~CMD_CCD, CMD_CCD};    //��β����

    UART_WRETE_BUFF(cmdf, sizeof(cmdf));    //�ȷ�������

    UART_WRETE_BUFF((uint8_t *)ccdaddr, ccdsize); //�ٷ���ͼ��

    UART_WRETE_BUFF(cmdr, sizeof(cmdr));    //�ٷ�������
}


/*!
 *  @brief      ɽ��๦�ܵ���������λ��������ʾ������ʾ����
 *  @param      wareaddr    ����������ʼ��ַ
 *  @param      waresize    ��������ռ�ÿռ�Ĵ�С
 *  @since      v5.0
*  Sample usage:
             �����÷��ο�������:
            ��ɽ�����ϡ������Ǻͼ��ٶ� ��λ����ʾ���� - ���ܳ�������
             http://vcan123.com/forum.php?mod=viewthread&tid=6253&ctid=27
 */
void vcan_sendware(void *wareaddr, uint32_t waresize)
{
#define CMD_WARE     3
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};    //���ڵ��� ʹ�õ�ǰ����
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};    //���ڵ��� ʹ�õĺ�����

    UART_WRETE_BUFF(cmdf, sizeof(cmdf));    //�ȷ���ǰ����
    UART_WRETE_BUFF((uint8_t *)wareaddr, waresize);    //��������
    UART_WRETE_BUFF(cmdr, sizeof(cmdr));    //���ͺ�����
}



