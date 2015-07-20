/*! \file    InvManageFun.h
   \brief    awe4000r��Ʊ�����Ӧ�ú���
   \author   Yu Yan 
   \version  1.0
   \date     2008-01-31
 */

#ifndef INV_MANAGE_FUNC_H
#define INV_MANAGE_FUNC_H

#include "IncludeMe.h"
#include "SysMacDef.h"
#include "SaleData.h"
#include "CRtInv.h"


//----��Ʊ����
/*!
@brief ��Ʊ����������	
@return  1 �ɹ��� ��1 �������
*/
UINT8 INVM_InvWasteProc();
/*!
@brief ��Ʊ����	
@param[in] nNum      ���Ϸ�Ʊ���� 
@param[in] pSaleData      �������������ָ�� 
@param[out] nIfInvSum  �Ƿ�ִ���˾���ܲ�����1���ǣ�0����
@return  1 �ɹ��� 0 ʧ��
*/
UINT8 INVM_InvWaste(UINT32 nNum, SaleData *pSaleData, UINT8 &nIfInvSum);

/*!
@brief ��Ʊ���Ͼ������	
@param[in] pSaleData      �������������ָ�� 
@return  1 �ɹ��� 0 ʧ��
*/
UINT8 INVM_InvWasteHandle(SaleData *pSaleData);

/*!
@brief �������Ϸ�Ʊ	
@param[in] pInvHead      ���Ϸ�Ʊ�Ķ���ָ�� 
@return  
*/
void INVM_BuildWasteInv(CInvHead *pInvHead);


/*!
@brief ���ѿ���Ʊ(���Ĺ���)	
@param[in] strInvCode     ���Ϸ�Ʊ�Ķ���ָ�� 
@param[in] invNo     ��Ʊ���� 
@param[out] strErr     ������Ϣ
@return  1 �ɹ��� 0 ʧ��
*/
//UINT8	WasteHasMakeInv(string& strInvCode, UINT32 invNo, string& strErr);

/*!
@brief �����ѿ���Ʊ	
@param[in] pInvHead     ���Ϸ�Ʊ�Ķ���ָ�� 
@param[out] strErr     ������Ϣ
@return  1 �ɹ��� 0 ʧ��
*/
UINT8 INVM_WstInv(CInvHead* pInvHead, string &strErr);

//-----��Ʊ�˻�

/*!
@brief ���鷢Ʊ�Ƿ����
@param[in]  ��Ʊ���룬��Ʊ����
@param[out] pInvHead ��ѯ��Ʊ��Ϣ
@return  1 �ɹ��� ��1  ����ID
*/
UINT8 INVM_CheckIsNoDB(string invCode,UINT32 invNo,CInvHead *pInvHead);

/*!
@brief ���鷢Ʊ�Ƿ����	
@param[in] pInvHead   ���˷�Ʊ������Ϣָ��
@return  1 �ɹ��� ��1  �������
*/
UINT8 INVM_CheckIsNoRet(CInvHead *pInvHead);


/*!
@brief ��Ʊ�˻ع���(�˱�����Ʊ)
@param[in] pInvHead   ���˷�Ʊ������Ϣָ��
@return  1: SUCCESS; ��1  �������
*/
UINT8 INVM_InvRetProc(CInvHead *pInvHead);

/*!
@brief �˱�����Ʊ
@param[in] pInvHead   ���˷�Ʊ������Ϣָ��
@param[out] 
@return  1 �ɹ��� ��1  �������
*/
UINT8  INVM_InvReturn(SaleData *pSale, CInvHead *pInvHead);

/*!
@brief �˷Ǳ�����Ʊ
@param[out] pInvHead   ���˷�Ʊ������Ϣָ��
@param[in] codeNo      ���˷�Ʊ�ķ�Ʊ���� 
@param[in] invNo       ���˷�Ʊ�ķ�Ʊ����  
@return  1 �ɹ��� ��1  �������
*/
// UINT8 ReturnGoods(SaleData *pSale, string codeNo, UINT32 invNo);

// UINT8 InvReturnSpe(SaleData *pSale);

/*!
@brief ��ѯ��Ʊ�����Ӧ�ķ�Ʊ���������
@param[in] code      ��Ʊ���� 
@return  0  ���󣻷�0 ��Ʊ���������
*/
// UINT8 CheckInvCode(INT8 *code);

//--------�ַ���ѯ
/*!
@brief yes/no��Ϣ��ʾ��	
@param[in] nNum   δ����ķ�Ʊ���� 
@return  1: SUCCESS���ǣ�; 0: FAILURE����
*/
//UINT8 YesNoBox(UINT32 nNum);
UINT8 YesNoBox(string strMsg);

/*!
@brief ͳ��δ����ķ�Ʊ�����������浽nNum�	
@param[out] nNum   δ����ķ�Ʊ���� 
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 INVM_GetVolNum(UINT32 &nNum);

/*!
@brief ͳ�Ʒ�Ʊ�����	
@param[in] nCodeNo   ��Ʊ���������
@param[in] nStartNo   ��Ʊ��ʼ����
@param[in] nEndNo   ��Ʊ��ֹ����
@param[out] nNum   ��Ʊ����� 
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 INVM_GetInvNum(string nCode, UINT32 nStartNo, UINT32 nEndNo, UINT32 &nNum);

/*!
@brief ��ӡ��Ʊ���	
@param[in] smallInvInfo   ��Ʊ���������
@param[in] IfPrnChar   �Ƿ��ӡ�����Ӵ�������֣�1����ӡ��0������ӡ
@return  1: SUCCESS; ��1: �������
*/
UINT8 PrnInvStub(CInvHead *smallInvInfo, UINT8 IfPrnChar);

/*!
@brief ��Ʊ��������	
@return  1: SUCCESS; 0: FAILURE
*/
//UINT8 WasteInvVol(void);

/*!
@brief �Ƿ���	
@return  1: SUCCESS; 0: FAILURE
*/
INT32 CmpCurMonth(UINT32 nDate, UINT32 nTime);

/*!
@brief ������β�ѯ��Ʊ��ϸ
@param[in] ��Ʊ���룬��Ʊ����	
@return  1: SUCCESS; ��1: ������ϢID
*/
UINT8 INVM_InvDetailNOQuery(string invCode,UINT32 invNO);

/*!
@brief ʱ��η�Ʊ��ѯ
@param[in] ��Ʊ����	����
@return  1: SUCCESS; 0: FAILURE
*/
//UINT8 INVM_DownLoadInvDate(string invDate);
/*!
@brief ������Ϣ����
@param[in] ret ����ID	
@return  1: SUCCESS; 0: FAILURE
*/
void INVM_ErrMsgBox(UINT8 ret);



#endif
