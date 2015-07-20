/*! \file    TemplatePrintInv.h
\brief    ��Ʊ��ӡ�ӿ��ļ�
\author   zfj
 */

#ifndef TEMPLATE_PRINT_INV_H
#define TEMPLATE_PRINT_INV_H


#include "comdatatype.h"
#include "TemplateDataDesign.h"
#include "TPLModuleHeader.h"



#ifdef __cplusplus
extern "C"
{
#endif

#define QR_CODE 2
#define DM_CODE 3
#define HX_CODE 1

extern UINT8 bidirection ;
extern UINT8  *m_RemainLineCount;             /**< ����ʣ���ӡ�и��� */
extern UINT8  *m_BeginPrintFlag;              /**< ��ǵ���ʱ�Ƿ��Ѿ���ʼ��ӡ���� */

/*!
@brief ��ӡ��Ʊ��ͷ
@param[in] invData  ��Ʊ��Ϣ
@return  SUCCESS-�ɹ���FAILURE-���� 
*/
INT8 print_invoice_head( TPrnInvoiceInfo *invData);

/*!
@brief ��ӡ��Ʒ��ϸ,��������
@param[in] invData  ��Ʊ��Ϣ
@return  SUCCESS-�ɹ���FAILURE-���� 
*/
INT8 print_invoice_data(TPrnInvoiceInfo *invData);

/*!
@brief ѭ����ӡ��Ʒ��ϸ��
@param[in] invData  ��Ʊ��Ϣ
@param[in] unfixedFlag  ��������־����Ҫ�����ڴ򲻶����������Ʊ
@return  SUCCESS-�ɹ���FAILURE-���� 
*/
INT8 print_invoice_data_cycle(TPrnInvoiceInfo *invData,UINT8 unfixedFlag);

/*!
@brief ��ӡ��ƱƱβ
@param[in] invData  ��Ʊ��Ϣ
@return  SUCCESS-�ɹ���FAILURE-���� 
*/
INT8 print_invoice_tail(TPrnInvoiceInfo *invData);

/*!
@brief �����Ĵ�ӡ����
@param[in] pPrnLineInfo  ��ӡ�����ݽṹ
@return  SUCCESS-�ɹ���FAILURE-���� 
*/
INT8 print_invoice_content(TPrnLineInfo *pPrnLineInfo);


/*!
@brief ��ӡ��ά��
@param[in] bufbiznfo  ��ά���ַ���
@return  SUCCESS-�ɹ���FAILURE-���� 
*/
#if (PRINT_BIZNFO!=0)
INT8 print_biznfo(UINT8 *bufbiznfo);
#endif


/*!
@brief ���õ��籣������ʵ��
@param[in] remanCount  ����ʣ���ӡ�и���
@param[in] beginFlag  ��ǵ���ʱ�Ƿ��Ѿ���ʼ��ӡ����
@return  SUCCESS-�ɹ���FAILURE-���� 
*/
void set_power_pointer(UINT8 *remanCount, UINT8 *beginFlag);

/*!
@brief ���õ���ʣ���ӡ�и���
@param[in] count  ����ʣ���ӡ�и���
@return  SUCCESS-�ɹ���FAILURE-���� 
*/
INT8 set_power_count(UINT8 count);

/*!
@brief ���õ���ʱ�Ƿ��Ѿ���ʼ��ӡ����
@param[in] flag  ��ǵ���ʱ�Ƿ��Ѿ���ʼ��ӡ����
@return  SUCCESS-�ɹ���FAILURE-���� 
*/
INT8 set_power_flag(UINT8 flag);

/*!
@brief �жϴ�ӡ����ǰ�з���ֽ
@return  -1����ʧ�ܣ�0�����ɹ�
*/
INT8 isPaper(void);


#ifdef __cplusplus
}
#endif

#endif
