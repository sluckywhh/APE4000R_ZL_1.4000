/*! \file   rtc.h
   \brief   RTC����
   \author  
 */

#ifndef __RTC_I2C_H
#define __RTC_I2C_H


#ifdef __cplusplus
extern "C"
{
#endif

#define   M41T80_SLAVE	  0xD0              /* ����slave������ַ����Ĭ��Ϊtransmitģʽ */


/* define ioctl command */
#define I2C_IOC_MAGIC				'i'
#define I2C_IOC_MAXNR				 3

#define I2C_IOC_SET_DEV_ADDRESS			_IOW(I2C_IOC_MAGIC, 0, int)
#define I2C_IOC_SET_SUB_ADDRESS			_IOW(I2C_IOC_MAGIC, 1, int)
#define I2C_IOC_SET_SPEED			_IOW(I2C_IOC_MAGIC, 2, int)
#define I2C_IOC_GET_LAST_ERROR			_IOR(I2C_IOC_MAGIC, 3, int)

/* ioctl�����ڴ����ӵ�ַ�Ľṹ�� */
struct sub_address{
	char sub_addr_len;
	unsigned int sub_addr;
};

/*!
@brief      I2C��ʼ��
@details    ������ʼ�����ж�Ϊ����IRQ�ж� 
*/
void  I2C_Init(void);

/*!
@brief       ����������
@param[in]   data  ���year,month,data��ָ��
*/
unsigned char SetRTCData(unsigned char *data);//BCD FORMAT:YEAR_MONTH_DATA     EX:041105-->2004.11.05

/*!
@brief     ����ʱ��
@param[in] data  ���hour,minute,second��ָ�� 
*/
unsigned char SetRTCTime(unsigned char *data);//BCD FORMAT:HOUR_MINUTE_SECOND  EX:143002-->14:30:02

/*!
@brief		��ȡ��ǰʱ�� 
@param[out] data ���ش�������յ�ָ�� 
*/
unsigned char GetRTCData(unsigned char *data);

/*!
@brief		��ȡ��ǰʱ�� 
@param[out] data ���ش��Сʱ�ֵ�ָ��  
*/
unsigned char GetRTCTime(unsigned char *data);


#ifdef __cplusplus
}
#endif

#endif
