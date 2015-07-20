/*! \file    TemplateIndep.h
\brief    ��ӡģ��ӿڡ�
\author   Xiao Pengkun   2005-07-20
 */


#ifndef   TEMPLATE_INDEP_H
#define   TEMPLATE_INDEP_H

#include "TemplateDataDesign.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern UINT8  templateBuffer[PRINT_TEMPLATE_BUF_LEN];
extern TPrnInvoiceInfo g_invPrnData;



#include "TemplateDataDesign.h"


/*!
@brief ��ɶ�ģ���еĽ�����������մ�ӡ�����ݡ�
@param[in] pInv  ָ��Ʊ���ݽṹ��ָ��
@param[out] pPrnLine  ����ֵΪָ���ӡ�нṹ��ָ��
@note ���뷢Ʊ���ݽṹ��ͨ������ģ���У�����Ӧ������������ӵ���Ӧ�Ľṹ
		 ���У����Ϊָ�����մ�ӡ�����е�ָ�룬ѭ�����ô˺�������ɶԴ�ӡģ��Ľ�����
		 ҵ�����ݵ���ӣ�ÿ����һ�����ģ���к�ҵ�����ݽ�����ɵ����մ�ӡ�С�
@return  0 - �ɹ�
*/
UINT8  ParseTempLine(TPrnInvoiceInfo *pInv,TPrnLineInfo **pPrnLine);


/*!
@brief ����ģ�����Ч��
@note ���ý���ģ���к������������0��ɹ���������������û�����
*/
UINT8  CheckTempValid(void);


/*!
@brief ��ɶԴ�ӡģ�����軺����������,��֤��һ�ε���ʱ����ȷ��
@note ��Ҫ��ɶԴ�ӡģ��ָ��prnTempBuf�����ã��������ģ������κδ���
		 ��������ô˺�����������
*/
void ResetTempBuf(void );


/*!
@brief ����ģ������
@note ��ģ���е�������Դ洢���ṹ��ΪSaveTemplateInfo
@return  ģ������
*/
TSaveTemplateInfo * SaveTemplate(void);

/**
 * brief ��ȡ��ӡģ��
 * @param UINT8 TemplateNo ģ���
 * @param UINT32 len ģ�峤��
 * @return static UINT8 
 */
UINT8 ReadPrintTemplate(UINT8 TemplateNo);

/**
 * brief ���ش�ӡģ��
 * @param UINT8 TemplateNo ģ���
 * @param UINT32 len ģ�峤��
 * @return static UINT8 
 */
UINT8 LoadPrintTemplate(UINT8 TemplateNo);

/**
 * brief ���ÿ�������ģʽ
* @param workMode    WORK_MODE-��������  TRAINING_MODE-ѵ��ģʽ
 */
void  SetTplInfoWorkMode(UINT8 workMode);
/**
 * brief ��ȡ��������ģʽ
* @return ����ģʽ
 */
UINT8 GetTplInfoWorkMode();
/**
 * brief ��ȡģ��ڱ귽ʽ
* @return 
 */
UINT8 GetTplInfoMarkFlag();
/**
 * brief ��ȡ�����Ʒ��ϸ����
* @return 
 */
UINT8 GetTplInfoMaxGoodsCount();
/**
 * brief ��ȡ�����Ʒ������
* @return 
 */
UINT8 GetTplInfoMaxSPMCCharacter();
/**
 * brief ��ȡ��ӡ��������ֽ����
* @return 
 */
UINT16 GetTplInfoEndForwardPoint();


#ifdef __cplusplus
}
#endif

#endif







