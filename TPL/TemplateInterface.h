/*! \file    TemplateInterface.h
\brief    ģ��ӿ��ļ�
\author   Xiao Pengkun   2005-06-23
 */

#ifndef  TEMPLATE_INTERFACE_H
#define  TEMPLATE_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif


#include "TemplateDataDesign.h"


extern UINT8 SKYContinueFlag;//�տ�Ա���б�־


/*!
@brief ��ȡģ����������~֮������ݡ�
@param[in] tempLineBuf
@param[in] tempLineFieldBuf
@note ��ָ��ÿһ��ģ���ָ���ָ�봫�룬��ģ�����е�����~������ݿ�����
		 tempLineFieldBufָ��Ļ����У���ָ���ָ�뷵�أ��Ա��ס��һ�δ���
         ��λ�á�
@return  0 - �ɹ�
*/
UINT8  GetPtField(UINT8 **tempLineBuf,UINT8 *tempLineFieldBuf);


/*!
@brief ��ȡÿһ��ģ�����ݡ�
@param[in] prnTempFile
@param[in] tempLineBuf
@note ��ָ��������ӡģ�����ݵ�ָ���ָ�봫�룬�õ�ÿһ��ģ�����ݣ���'\n'��β����
		 ������'\n'�����ݿ�����tempLineBufָ��Ļ����С���ָ���ָ�뷵�أ���
         ���ס��һ�δ����λ�á�
@return  0 - �ɹ�
*/
UINT8  GetPtLine(UINT8 **prnTempFile, UINT8 *tempLineBuf);



/*!
@brief ����ģ����0
@param[in] tempLineBuf
@param[in] tempLine0
@note ͨ������GetPtField�����ģ����0�Ľ���������Ӧ���ݴ洢��ģ����0��
         �ṹ���С�
@return  0 - �ɹ�
*/
UINT8  ParsePtLine0(UINT8 *tempLineBuf, TPrnTempLine0 *tempLine0);



/*!
@brief ����ģ����1
@param[in] tempLineBuf
@param[in] tempLine1
@note ͨ������GetPtField�����ģ����1�Ľ���������Ӧ���ݴ洢��ģ����1��
         �ṹ����
@return  0 - �ɹ�
*/
UINT8  ParsePtLine1(UINT8 *tempLineBuf, TPrnTempLine1 *tempLine1);



/*!
@brief ����ģ����2
@param[in] tempLineBuf
@param[in] tempLine2
@param[in] prnLineInfo
@param[in] tempLine1
@note ͨ������GetPtField�����ģ����2�Ľ�����ģ����2Ϊ��ӡ���������ݣ�ͨ������
         ģ�壬����Ӧ��ҵ��������䵽���մ�ӡ���С�
@return  0 - �ɹ� 
*/
UINT8  ParsePtLine2(UINT8 *tempLineBuf, TPrnTempRow *tempLine2,TPrnLineInfo *prnLineInfo,TPrnTempLine1 *tempLine1);

/*!
@brief ��ȡ����ҵ�����ݣ��γɴ�ӡ�����С�
@param[in] tempLine2 ģ����2�ṹָ�룬tempLineBuf2->chDataBuf�洢��ӡģ������Ҫ��ӡ������
@param[in] tempLineBuf2 ���д���ʱ�Ĵ�ӡ�нṹ
@param[in] tempLine1 ģ����1�ṹ���洢����ַ����ȣ��������С�
@param[in] prnLineInfo ����Ĵ�ӡ�нṹ
@param[in] pInv ��Ʊ���ݽṹ
@note tempLine2�洢ģ���е����ݣ�������ǩ��������λ�ú����ݵ�λ�ã��Լ���ǩ�����ݵĸ�����
		 ͨ��ѭ����������tempLine2->chDataBuf�е����ݣ�����Ǳ�ǩ��ֱ�Ӵ�ӡ����������ݣ�ͨ��
		 �Ƚϣ���FPHM����Ʊ���룩��pInv����ط�Ʊ������ӵ���Ӧ��λ�ã�ѭ������������γ�����
         �Ĵ�ӡ�����ݣ���ʱָ��prnLineInfo��ָ��Ϊ�ʹ�ӡ���Ĵ�ӡ�С�
@return  0 - �ɹ� 
*/
UINT8 GetPrnLineData(TPrnTempRow *tempLine2, TPrnLineInfo *tempLineBuf2,TPrnTempLine1 *tempLine1,TPrnLineInfo *prnLineInfo,TPrnInvoiceInfo *pInv);

#ifdef __cplusplus
}
#endif

#endif



