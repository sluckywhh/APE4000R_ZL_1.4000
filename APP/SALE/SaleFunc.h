/*! \file    SaleFunc.h
   \brief    awe4000r�����е�Ӧ�ú���
   \author   Yu Yan
   \version  1.0
   \date     2008-01-31
 */


#ifndef SALE_FUNC_H
#define SALE_FUNC_H

#include "IncludeMe.h"
#include "SysMacDef.h"

#include "CMachine.h"
//#include "CPlu.h"
#include "CDept.h"
//#include "CInvSum.h"
#include "CInvHead.h"
#include "CInvDet.h"
#include "CInvVol.h"
#include "CUserInfo.h"
//#include "CInvcodeLink.h"

#include "TemplateDataDesign.h"
#include "TemplateGeneralFuc.h"
#include "TemplateIndep.h"
#include "TemplateInterface.h"
#include "TemplateMacro.h"
#include "TemplatePrintInv.h"
#include "arithmetic.h"
#include "commonFunc.h"

#include "PrintDriver.h"
#include "TDateTime.h"
#include "CGlobalArg.h"


/*!
@brief ��ȡ��ǰ��Ʊ��
@param[out] CInvVol *pInvVol ��ǰ��Ʊ���룬��������ͣ�ʣ�෢Ʊ����
@param[out] string &strErr ������Ϣ
@return  1�� �ɹ��� ������ʧ��
*/
UINT8 SALE_GetCurInv(CInvVol *pInvVol,string &strErr);


/*!
@brief ��Ʊ���� (��Ʊ����Ʊ,�հ�����)
@param[in] CInvHead *pInvHead ��Ʊ������Ϣ 
@param[out] CInvHead *pInvHead ��Ʊ˰����
@param[out] string &strErr ������Ϣ
@return  1�� �ɹ��� ������ʧ��
*/
UINT8 SALE_MakeInvHand(CInvHead *pInvHead,string &strErr);

//----��Ʊ��ӡ

/*!
@brief ����ӡ��Ʊ�ṹ��ķ�Ʊͷ
@param[out] pPrnInvInfo ��Ʊ��ӡ���ݽṹ��ָ��
@param[in] smallInvInfo ��Ʊ������Ϣָ��
@return  1�� �ɹ��� ������ʧ��
*/
UINT8 FillPrnInvHead(TPrnInvoiceInfo *pPrnInvInfo, CInvHead *smallInvInfo);

/*!
@brief ����ӡ��Ʊ�ṹ��ķ�Ʊ��ϸ
@param[out] pPrnInvInfo ��Ʊ��ӡ���ݽṹ��ָ��
@param[in] smallInvInfo ��Ʊ������Ϣָ��
@return  1�� �ɹ��� ������ʧ��
*/
UINT8 FillPrnInvDetail(TPrnInvoiceInfo *pPrnInvInfo, CInvHead *smallInvInfo);

/*!
@brief ����ӡ��Ʊ�ṹ��ķ�Ʊβ
@param[out] pPrnInvInfo ��Ʊ��ӡ���ݽṹ��ָ��
@param[in] smallInvInfo ��Ʊ������Ϣָ��
@return  1�� �ɹ��� ������ʧ��
*/			
UINT8 FillPrnInvTail(TPrnInvoiceInfo *pPrnInvInfo, CInvHead *smallInvInfo);


/*!
@brief ����Ҫ����������Ƿ��¼δ�걨�������޷�����
@param[in] nInvHeadNum INV_HEAD��ļ�¼����
@param[in] nInvSumNum INV_SUM��ļ�¼����
@return  0�� ���Թ����� 1���޷����������걨
*/
UINT8 CheckIfFull(INT32 nInvHeadNum, INT32 nInvSumNum);

/*!
@brief ��ֽ
@return  1 �ɹ���0  ûֽ��
*/
UINT8 ForwardPaper(void);

/*!
@brief ���Һڱ��ֽ
@return  1 �ɹ���0  ûֽ��
*/
UINT8 NoMarkForwardPaper(void);

/*!
@brief ��ֽ
@return  1 �ɹ���0  ûֽ��
*/
UINT8 BackwardPaper(void);	


/**
 * brief ��ӿ�Ʊ��ϵͳ��־��¼
 * @param[in]  nInvType ��Ʊ����
 * @param[in]  EventResult  �¼����
 * @param[in]  Backup ��ע��Ϣ
 * @return 1: SUCCESS, 0: FAILURE
 */
UINT8 MakeInvLog(UINT8 nInvType, UINT32 EventResult, string Backup = "");

/**
 * brief ��ѯδ�ϴ�����
 * @param[in]  uNum δ�ϴ�����
 * @param[in]  strErr  ������Ϣ
 * @return 1: SUCCESS, 0: FAILURE
 */
UINT8 GetServNum(UINT32 &uNum,string &strErr);

#ifndef WIN32
//------�߳����--------//
void * NetCommunicate(void *arg);

//�ϴ����ĺ���
UINT8 UploadInvProc();
#endif

#endif
