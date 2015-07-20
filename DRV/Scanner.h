
/*! \file   Scanner.h
   \brief   ɨ��ǹ����
   \author  
 */
#ifndef _SCANNER_H
#define _SCANNER_H

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@brief     ��ʼ��ɨ��ǹ 
@return    SUCCESS ��ʼ����ȷ��FAILURE	��ʼ������
*/
int ScannerInit(void);

/*!
@brief      �ͷ�ɨ��ǹ�豸
@return     SUCCESS ��ȷ��FAILURE	����
*/
int ScannerRelease(void);

/*!
@brief      ���ɨ��ǹ�豸�Ƿ��ʼ�� 
@return   	SUCCESS	 �Ѿ���ʼ����FAILURE  δ��ʼ��
*/
int ScannerStateCheck(void);

/*!
@brief       ����ɨ��ǹ����ֵ������ָ�����볤�ȣ�
@param[in]   length	 ���볤��
@return      SUCCESS ��ɨ���룻FAILURE	��ɨ���룻 
*/
int ScannerPressed_mode1(char length);

/*!
@brief      ����ɨ��ǹ����ֵ������ָ�����볤�ȣ�����Ҫ���������ֽڰ��İ�β��ʶ��
@param[in]  str	�����β��ʶ
@return     SUCCESS	 ��ɨ���룻FAILURE	��ɨ���룻
*/
int ScannerPressed_mode2(char *str);

/*!
@brief   ���ؽ���BUFָ��
@return  ɨ�������bufָ��
*/
unsigned char *ScannerCode(void);

/*!
@brief   ���������
*/
void ClearScannerBuf();

#ifdef __cplusplus
}
#endif

#endif
