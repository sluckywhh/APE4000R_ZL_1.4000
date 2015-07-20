/*! \file    ReportFunc.h
   \brief    awe4000r�����ӡ��Ӧ�ú�����
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */


#ifndef REPORT_FUNC_H
#define REPORT_FUNC_H

#include "IncludeMe.h"
#include "SysMacDef.h"
#include "CaMsgBox.h"
#include "CSysLog.h"
#include "printer.h"
//#include "CPlu.h"
#include "CClient.h"
#include "CDept.h"
#include "COperator.h"
#include "CTjxxhz.h"

extern INT8 *pGeneralPrnBuff;

/*!****************************************************************************
<PRE>
�ṹ����  : _TCheckOld
��������  : ��Ʊ��ɽṹ
����	  : zcy
����	  : 2011-06-28
</PRE>
*******************************************************************************/
typedef struct _TCheckOld 
{
	string taxPayerFileNo;			//��˰�˵����˵���
	string taxPayerID;				//��˰��ʶ���
	string invKindCode;            	//��Ʊ�������
	string invKindName;				//��Ʊ��������
	string invCode;					//��Ʊ����
	string invName;					//��Ʊ����
	string invSNo;					//��Ʊ��ʼ��
	string invENo;					//��Ʊ��ֹ��
	int	   num;				    	//����
	string checkDate;				//��������
	string searchNo;				//��ѯ��
}TCheckOld;

/*!****************************************************************************
<PRE>
�ṹ����  : _TCheckOldInfo
��������  : ��Ʊ��ɽṹ����
����	  : zcy
����	  : 2011-06-30
</PRE>
*******************************************************************************/
typedef struct _TCheckOldInfo 
{
	string taxPayerFileNo;			//��˰�˵����˵���
	string taxPayerID;				//��˰��ʶ���
	string invKindCode;				//��Ʊ�������
	string invCode;					//��Ʊ����
	string checkDate;				//��������
	int	   num;				    	//����
	string invSNo;					//��Ʊ��ʼ��
	string invENo;					//��Ʊ��ֹ��
	string makeDate;                 //��Ʊ����
	string money;                    //����
	string taxMoney;				//�˰��
   	string remarks;					//��ע
    string resCode;					//��ɽ������
	string resContent;				//��ɽ������
	string makeSDate;				//��Ʊ��ʼ����
	string makeEDate;				//��Ʊ��ֹ����
	string inDate;					//¼������
	string modifyDate;				//�޸�����
	string searchNo;				//��ѯ��

}TCheckOldInfo;

/*!
@brief yes/no��Ϣ��ʾ��	
@param[in] strInfo   ��ʾ����ʾ���ַ���
@return  1: SUCCESS���ǣ�; 0: FAILURE����
*/
UINT8 YesNoMsgBox(string strInfo);

/*!
@brief ��ȡ�ջ��ܱ�ĳʱ��εļ�¼��	
@param[in] nStartDate   ��ʼ����
@param[in] nStartDate   ��ֹ����
@param[out] nNum   ��¼��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 GetDaySumCount(UINT32 nStartDate, UINT32 nEndDate, UINT32 &nNum);

/*!
@brief ��ȡ�»��ܱ�ĳʱ��εļ�¼��	
@param[in] pTjxxhz   ͳ�ƻ��ܱ�
@param[out] pInvsum  ���ݿ��
@param[out] strErr   ��¼��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 GetMonthSumCount(CTjxxhz *pTjxxhz, string &strErr);

/*!
@brief �жϸ���ʱ���Ƿ�Ϸ��� ��ʱ����֯�ɸ�ʽΪHHMMSS�޷���������Ϊ
@param[in] hhmmss �� ��ʽΪhhmmss���޷�������
@return  1: SUCCESS���ǣ�; 0: FAILURE����
*/
UINT8 IsTimeValid(UINT32 hhmmss);

/*!
@brief ��ӡĳʱ��ε�ϵͳ��־�ı���ͷ��
@param[in] nStartDate ʱ��ε���ʼ����
@param[in] nEndDate   ʱ��εĽ�������
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnSysLogHead(UINT32 nStartDate, UINT32 nEndDate);

/*!
@brief ��ӡϵͳ��־��ĳ����¼
@param[in] pSysLog ϵͳ��־��¼��ϸ��ָ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnSysLogDetail(const CSysLog *pSysLog);

/*!
@brief ��ӡPLU�ı���ͷ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnPLUHead();

/*!
@brief ��ӡĳ��PLU��Ϣ
@param[in] pPlu PLU��Ϣ��ָ��
@return  1: SUCCESS; 0: FAILURE
*/
//UINT8 PrnPLUDetail(const CPlu *pPlu);

/*!
@brief ��ӡ�ͻ��ı���ͷ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnClientHead();

/*!
@brief ��ӡĳ���ͻ���Ϣ
@param[in] pClient �ͻ���Ϣ��ָ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnClientDetail(const CClient *pClient);

/*!
@brief ��ӡ����ı���ͷ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnDeptHead();

/*!
@brief ��ӡ������Ϣ
@param[in] pDept ������Ϣ��ָ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnDeptDetail(const CDept *pDept);

/*!
@brief ��ӡ����Ա�ı���ͷ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnOperatorHead();

/*!
@brief ��ӡ����Ա��Ϣ
@param[in] pOperator ����Ա��Ϣ��ָ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnOperatorDetail(const COperator *pOperator);

/*!
@brief ��ӡĳʱ�������Ա����ͳ�Ʊ���ͷ��
@param[in] nStartDate ��ʼ����
@param[in] nStartTime ��ʼʱ��
@param[in] nEndDate ��ֹ����
@param[in] nEndTime ��ֹʱ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnSalerSumHead(UINT32 nStartDate, UINT32 nStartTime, UINT32 nEndDate, UINT32 nEndTime);

/*!
@brief ��ӡ����Ա����
@param[in] pSaler ����Ա����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnSaler(const string *pSaler);

/*!
@brief ��ӡ����Ա���۵Ĳ�����Ʒ��Ϣ
@param[in] pDeptName ��������
@param[in] nSum �������۽��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnSalerDeptSum(const string *pDeptName, INT64 nSum);

/*!
@brief ��ӡ����Ա������������Ϣ
@param[in] nInvCount ������Ա�Ŀ�Ʊ����
@param[in] nSum ������Ա�����۽��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnSalerSum(UINT32 nInvCount, INT64 nSum);

/*!
@brief ��ӡĳʱ�������ͳ�Ʊ���ͷ��
@param[in] nStartDate ��ʼ����
@param[in] nStartTime ��ʼʱ��
@param[in] nEndDate ��ֹ����
@param[in] nEndTime ��ֹʱ��
@param[in] nIfDay ���ջ�������ͳ�ƣ�1��������ͳ�ƣ� 0��������ͳ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnSaleSumHead(UINT32 nStartDate, UINT32 nStartTime, UINT32 nEndDate, UINT32 nEndTime, UINT8 nIfDay);

/*!
@brief ��ӡ��ͳ�Ƶ�����
@param[in] strIssueDate ���ڣ��ַ�����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnDate(const string *strIssueDate);

/*!
@brief ��ӡĳ�����۵Ĳ�����Ʒ��Ϣ
@param[in] pDeptName ��������
@param[in] nSum �������۽��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnDayDeptSum(const string *pDeptName, INT64 nSum);

/*!
@brief ��ӡĳ�յ�����������Ϣ
@param[in] nInvCount ���տ�Ʊ����
@param[in] nSum ���յ����۽��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnDaySaleSum(UINT32 nInvCount, INT64 nSum);

/*!
@brief ��ӡ������ͳ�Ƶ��ܼ�
@param[in] nInvCount �ܼƿ�Ʊ����
@param[in] nSum �ܼ����۽��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnAllDaySaleSum(UINT32 nInvCount, INT64 nSum);

/*!
@brief ͳ�Ʋ���ӡĳʱ��εĲ���������Ϣ
@param[out] sumMoney �����ۼ����۽��
@param[in] strFilter ĳʱ���������sql��䣩
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnDeptMoney(INT64 &sumMoney, const string *strFilter);

/*!
@brief ��ӡĳʱ��β������۽��
@param[out] sumMoney �����ۼ����۽��
@param[in] nStartDate ��ʼ����
@param[in] nStartTime ��ʼʱ��
@param[in] nEndDate ��ֹ����
@param[in] nEndTime ��ֹʱ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnPeriodDeptMoney(INT64 &sumMoney, UINT32 nStartDate, UINT32 nStartTime, UINT32 nEndDate, UINT32 nEndTime);

//������ͳ��
/*!
@brief ��ӡͳ�������������·�
@param[in] sumDate ����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnMonth(UINT32 sumDate);

/*!
@brief ��ӡĳ�����۵Ĳ�����Ʒ��Ϣ
@param[in] pDeptName ��������
@param[in] nSum �������۽��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnMonthSaleSum(UINT32 nInvCount, INT64 nSum);

/*!
@brief ��ӡĳʱ��ο�Ʊͳ�Ʊ���ͷ��
@param[in] nStartDate ��ʼ����
@param[in] nStartTime ��ʼʱ��
@param[in] nEndDate ��ֹ����
@param[in] nEndTime ��ֹʱ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnIssueSumHead(UINT32 nStartDate, UINT32 nStartTime, UINT32 nEndDate, UINT32 nEndTime);

/*!
@brief ��ӡĳʱ��ο�Ʊ��Ϣ
@param[in] nInvNo ��Ʊ��
@param[in] nInvType ��Ʊ����
@param[in] nInvMoney ��Ʊ���
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnIssueSumCode(string fpdm);
UINT8 PrnIssueSumBody(UINT32 nInvNo, UINT8 nInvType, INT64 nInvMoney);

/*!
@brief ��ӡĳʱ��ο�Ʊͳ�Ʊ���β��
@param[in] nNormalNum ��Ʊ����
@param[in] nReturnNum ��Ʊ����
@param[in] nWasteNum  ��Ʊ����
@param[in] nNormalNum ��Ʊ���
@param[in] nReturnNum ��Ʊ���
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnIssueSumEnd(UINT32 nNormalNum, UINT32 nReturnNum, UINT32 nWasteNum, INT64 norMoney, INT64 retMoney);

/*!
@brief ��ӡ�ۼƽ���
@param[in] normalSum �걨����Ʊ�ۼƽ��
@param[in] returnSum �걨�ں�Ʊ�ۼƽ��
@param[in] normalVolSum  ��Ʊ����Ʊ�ۼƽ��
@param[in] returnVolSum ��Ʊ���Ʊ�ۼƽ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnMoneyInfo(INT64  normalSum, INT64  returnSum, INT64  normalVolSum, INT64  returnVolSum);

/*!
@brief ��ӡĳ��Ʊ�Ŷ�����ͳ�Ʊ���ͷ��
@param[in] nStartDate ��ʼ��Ʊ��
@param[in] nStartTime ��ֹ��Ʊ��
@param[in] strpCode ��Ʊ����ָ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnInvSaleSumHead(UINT32 nStartNo, UINT32 nEndNo, const string *strpCode);

/*!
@brief ��ӡĳ��Ʊ�Ŷ�����ͳ�Ʊ���β��
@param[in] nInvCount �ܼƿ�Ʊ����
@param[in] nSum �ܼ����۽��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnInvSaleSumEnd(UINT32 nInvCount, INT64 nSum);

/*!
@brief ��ӡ��Ʊ���ͳ�Ʊ���ͷ
@param[in] nsrmc ��˰������
@param[in] swdjzh ˰��Ǽ�֤��
@param[in] checkoldHead ��Ʊ���ṹ��ָ��
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnInvCheckOldHead(string nsrmc, string swdjzh, TCheckOld* checkoldHead);
/*!
@brief ��ӡ��Ʊ���ͳ�Ʊ���ʵ��
@param[in] checkoldHead ��Ʊ���ṹ��ָ��
@param[in] &nHeadNum ��Ʊ�������
@param[in] checkoldInfo ��Ʊ��ɽṹ��ָ��
@param[in] &nInfoNum ��Ʊ�������
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnInvCheckOldBody(TCheckOld* checkoldHead, int &nHeadNum, TCheckOldInfo* checkoldInfo, int &nInfoNum);

/*!
@brief ��ӡ��ƱƱ����Ϣ����
@param[in] bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ��ʼ��ӡ
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 print_invkindifo(/*struct TInvKindInfoPrnData *invkindData, */ UINT8 bFindBlackMark);

INT8 print_taxiteminfo(UINT8 bFindBlackMark);

/*!
@brief ͳ�Ʋ���ӡĳʱ��εĲ������۽��
@param[out] sumMoney �����ۼ����۽��
@param[in] strFilter ĳʱ���������sql��䣩
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrnTimeDeptMoney(INT64 &sumMoney,INT64 &norMoney,INT64 &retMoney, const string *strFilter);


//��ӡϵͳ��Ϣ
//UINT8 PrnMessageDetail(const CMessage *message);

//��ӡһ������
INT8 PrintSeparator();
INT8 PrintDoubleSeparator();

//��ӡ̧ͷ
INT8 PrintTitle();

void DivideCNStr(string &str1, INT32 len, string &str2);
int GetHalfHZCount(unsigned char *str,int len);

#endif