
/*! \file   handwrite.h 
   \brief   ��д������
   \author   
 */

#ifndef HAND_WRITER_H
#define HAND_WRITER_H


#define	MAX_WAIT_TIME	1000000

#define HW_SUCCESS						1
#define HW_FAILURE						0

#define SCREEN_HW_TYPE		1	/**< 0:ʤ��ͨ���� 1:Aisino���� */

#ifdef __cplusplus
extern "C"
{
#endif

enum RESOLVE_STATUS
{
	STATE_RESET = 0,
	STATE_PACKHEAD,
	STATE_CMDNO,
	STATE_LENGTH,
	STATE_PARA_END,
	STATE_CRC_OK
};

struct RevCmdData
{
	unsigned char CmdNo;
	unsigned char CmdParaLen;
	unsigned char CmdPara[30];
	unsigned char CmdCRC;
	
};

/*!
@brief ��ʼ��ʤ��ͨ������д��
@return  HW_SUCCESS	�� ��ʼ����ȷ��HW_FAILURE�� ��ʼ������
*/
int HwInit(void);

/*!
@brief ��ʼ������ʤ��ͨ��д��
@return  HW_SUCCESS	�� ��ʼ����ȷ��HW_FAILURE�� ��ʼ������
*/
int ScreenHwInit(void);

/*!
@brief �ͷ�ͨѶ�豸
@return  HW_SUCCESS	�� ��ʼ����ȷ��HW_FAILURE�� ��ʼ������
*/
int HwRelease(void);

/*!
@brief �ȴ����պ���
@param[out] hz_buf����ѡ����
@param[out] num��	���ָ���
@return  HW_SUCCESS	�� ��ʼ����ȷ��HW_FAILURE�� ��ʼ������
*/
int HwRevHANZI(unsigned char *hz_buf, unsigned char *num);

/*!
@brief ѯ�ʽ����豸��ǰ�յ����ֽ���
@param[in] HwPort���˿ں�
@return  �ֽڸ���
*/
int get_rev_count(int HwPort);

/*!
@brief ��ȡ��������д����
@param[in] chHWbuf  ���յ�buf
@param[in] nHwBufLen ���յ�buf����
@return  ������д���ݴ�С
*/
int HwDataAdjust(unsigned char *chHWbuf, int nHwBufLen);

#ifdef __cplusplus
}
#endif

#endif
