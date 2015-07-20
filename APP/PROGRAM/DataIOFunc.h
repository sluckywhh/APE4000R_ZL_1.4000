 /*! \file    DataIOFunc.h
   \brief    awe4000r���ݵ��뵼����Ӧ�ú�����
   \author   Yu Yan
   \version  1.0
   \date     2008-8-13
 */


#ifndef DATA_IO_FUNC_H
#define DATA_IO_FUNC_H

#include "IncludeMe.h"
#include "SysMacDef.h"
#include "CaMsgBox.h"
#include "CClient.h"
#include "CDept.h"



/*!
@brief �������ݵ������
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 DeptImportProc();

/*!
@brief ���������ݵ������
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 ClientImportProc();

/*!
@brief ���ݵ�����Ĳ���(����sql�ű��ļ�)
@param[in] nKind   ��������ݱ�  1��PLU�� 2��DEPT�� 3��Client��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 ImportHandle(UINT8 nKind);

/*!
@brief ���ݵ�����Ĳ���(����TXT�ı��ļ�)
@param[in] nKind   ��������ݱ�  1��PLU�� 2��DEPT�� 3��Client��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 ImportTxtHandle(UINT8 nKind);

/*!
@brief ��TXT�ı��ļ�����������¼����PLU��
@param[in] fp   �ı��ļ�ָ��
@param[in] pchToken   �ı��ļ��и��������ֶεı�Ƿ�
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 InsertOnePlu(FILE *fp, const INT8 *pchToken);

/*!
@brief ��TXT�ı��ļ�����������¼����Dept��
@param[in] fp   �ı��ļ�ָ��
@param[in] pchToken   �ı��ļ��и��������ֶεı�Ƿ�
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 InsertOneDept(FILE *fp, const INT8 *pchToken);

/*!
@brief ��TXT�ı��ļ�����������¼����Client��
@param[in] fp   �ı��ļ�ָ��
@param[in] pchToken   �ı��ļ��и��������ֶεı�Ƿ�
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 InsertOneClient(FILE *fp, const INT8 *pchToken);

/*!
@brief �������ݵ�������
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 DeptExportProc();

/*!
@brief ���������ݵ�������
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 ClientExportProc();

/*!
@brief ���ݵ������Ĳ���(����sql�ű��ļ�)
@param[in] strCmd   ����PLU��U���ļ���shellָ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 ExportSqlHandle(string strCmd);

/*!
@brief ���ݵ�����Ĳ���(����TXT�ı��ļ�)
@param[in] nKind   ���������ݱ�  1��PLU�� 2��DEPT�� 3��Client��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 ExportTxtHandle(UINT8 nKind);

/*!
@brief ��װ���һ��Client��¼��TXT���
@param[in]  pClient    ��������Ϣ
@param[out] strTxt  ��װ�õ��ı����
@return  1�� SUCCESS�� 0��FAILURE
*/
INT8 ComposeClientTxt(const CClient *pClient, string &strTxt);

/*!
@brief ��װ���һ��Dept��¼��TXT���
@param[in]  pDept    ������Ϣ
@param[out] strTxt  ��װ�õ��ı����
@return  1�� SUCCESS�� 0��FAILURE
*/
INT8 ComposeDeptTxt(const CDept *pDept, string &strTxt);

/*!
@brief �����ݿ����һ�������¼��Ȼ��д���ļ�
@param[in]  fp    �ļ����
@return  1�� SUCCESS�� 0��FAILURE
*/
UINT8 OutputOneDept(FILE *fp);

/*!
@brief �����ݿ����һ�������˼�¼��Ȼ��д���ļ�
@param[in]  fp    �ļ����
@return  1�� SUCCESS�� 0��FAILURE
*/
UINT8 OutputOneClient(FILE *fp);



#endif

