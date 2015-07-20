/*! \file    FiscalFun.h
   \brief    ����˰��ͨ�ú���
   \author   zl
   \version  1.0
   \date     2008-01-01
 */

#ifndef _FISCAL_FUNC_H_
#define _FISCAL_FUNC_H_

#include "IncludeMe.h"
#include "SysMacDef.h"
#include "comdatatype.h"
#include "arithmetic.h"


/**
 * @brief  ������ʱ��ת��Ϊhex��ʽ
 */
void FSC_InvDateHex(UINT32 date, UINT32 time, UINT8 *hexInvDate);

/*!
@brief ��ʼ����ں���
@param[in]  strOldPsw  ԭ����
@param[in]  strNewPsw  �¿���
@param[out] strErr ������Ϣ���Ȱ�������ҵ����ӿڷ��ص���ϢҲ�����ú�������ʱ��������Ĵ�����Ϣ
@return  1�� �ɹ��� ������ʧ��
*/
UINT8 FSC_InitProc(const string &strOldPsw, const string &strNewPsw, string &strErr);


/*!
@brief �ӽ�˰�̻�ȡ��˰�˻�����Ϣ������
@param[out]  strErr  ������Ϣ
@return 1  �ɹ��� 0  ʧ��
*/
UINT8 FSC_GetNsrInfo(string &strErr);

/*!
@brief �ӽ�˰�̻�ȡ��Ȩ˰�ʲ�����
@param[out]  strErr  ������Ϣ
@return 1  �ɹ��� 0  ʧ��
*/
UINT8 FSC_GetTaxInfo(string &strErr);

/*!
@brief �ӽ�˰�̻�ȡ���߿�����Ϣ������
@param[out]  strErr  ������Ϣ
@return 1  �ɹ��� 0  ʧ��
*/
UINT8 FSC_GetInvKindInfo(string &strErr);

/*!
@brief ��ȡ˰�̺ͱ�˰�̲�����Ϣ������ͬ����˰��ʱ�ӣ��������
@param[out]  strErr  ������Ϣ
@return 1  �ɹ��� 0  ʧ��
*/
UINT8 FSC_GetJSKInfo(string &strErr);

/*!
@brief ��¼ʱ������˰����Ϣ�����߿�����Ϣ�������������ݿ�
@param[out]  strErr  ������Ϣ
@return 1  �ɹ��� 0  ʧ��
*/
UINT8 FSC_InfoUpdate(string &strErr);


/*!
@brief �����걨
@return 
*/
void FSC_NetDeclare();

/*!
@brief �������걨����
@1.���е��ղ�����˰
@2.���ղ�����������
@return 1  �ɹ��� 0  ʧ��
*/
// UINT8 FSC_CheckDeclare(string &strErr);

/*!
@brief �����걨
@return 
*/
void FSC_DiskDeclare(UINT8 uJZlx);

/*!
@brief �����忨
@return 
*/
void FSC_NetUpdateTax();

/*!
@brief �����������˰�̣�
@return 
*/
void  FSC_DiskUpdateTax();

/*!
@brief �޸Ľ�˰�̿���
@param[in]  strOldPsw  �ɿ���
@param[in]  strNewPsw  �¿���
@return 1  �ɹ��� 0  ʧ��
*/
UINT8 FSC_ChangeDiskPsw(string strOldPsw, string strNewPsw,string  &strErr);

/*!
@brief ��Ʊ��¼
@param[in]  SDate  ��ʼ����
@param[in]  EDate  ��������
@return 1  �ɹ��� 0  ʧ��
*/
UINT8 FSC_FpblProc(UINT32 SDate, UINT32 EDate, string &strErr);

#endif //_COMMON_H_
