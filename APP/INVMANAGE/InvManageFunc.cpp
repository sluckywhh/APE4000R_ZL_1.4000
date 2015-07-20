/*! \file  InvManageFunc.cpp
\brief    awe4000r��Ʊ�����Ӧ�ú���
\author   zcy
\version  1.0
\date     2015-05-11
*/

#include "InvManageFunc.h"
#include "SaleBusinessFunc.h"
#include "CGlobalArg.h"
#include "VersionConfig.h"
#include "CaProgressBar.h"
#include "CaMsgBox.h"
#include "APIBase.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

//----------------------------------------------------
//�հ׷�Ʊ����
//----------------------------------------------------
UINT8 INVM_InvWasteProc()
{
	DBG_PRINT(("����INVM_InvWasteProc����"));
	
	UINT8 ret;

	CaProgressBar proBar("�հ�������.....");
    proBar.ReFresh();

	if (NULL==pSaleData)
	{
		pSaleData = new SaleData;
	}
	
	DBG_ASSERT_EXIT((pSaleData != NULL), (" pSaleData == NULL!"));
	UINT8 nIfInvSum =0;
	ret = INVM_InvWaste(1,pSaleData,nIfInvSum); //�հ�����
	
	DBG_PRINT(("ret= %u",ret));
	if (ret != SUCCESS)
	{
		pSaleData=NULL;
		return ret;
	}
    
	pSaleData=NULL;

	return  SUCCESS;	
}

UINT8 INVM_InvWaste(UINT32 nNum, SaleData *pSaleData, UINT8 &nIfInvSum)
{
	DBG_ENTER("InvWaste");
	DBG_PRINT(("����InvWaste����"));
	DBG_PRINT(("���Ϸ�Ʊ���� == %u", nNum));
	UINT8 ret=SUCCESS;
	
	//��Ʊ����
	for(UINT8 i=0; i<nNum; i++)
	{
		ret = INVM_InvWasteHandle(pSaleData);
		DBG_PRINT(("ret= %u",ret));
		if(ret != SUCCESS)
		{
			//������ر�����λ
			pSaleData->m_tmpGoodsNum = 0;  //��ǰ����Ʒ��������
			pSaleData->InitSaleData(1);	//������Ϣ��ʼ��
			pSaleData->InitInvHead();		//���ŷ�Ʊ��Ϣ��ʼ��
			pSaleData->m_workState = WORK_COMPLETE;
			pSaleData->m_smallInvInfo = NULL;
			DBG_PRINT(("InvWaste error"));
			DBG_RETURN(ret);
		}
	}
	
	//������ر�����λ
	pSaleData->m_tmpGoodsNum = 0;  //��ǰ����Ʒ��������
	pSaleData->InitSaleData(1);	//������Ϣ��ʼ��
	pSaleData->InitInvHead();		//���ŷ�Ʊ��Ϣ��ʼ��
	pSaleData->m_workState = WORK_COMPLETE;
	pSaleData->m_smallInvInfo = NULL;
	
	DBG_PRINT(("�˳�InvWaste����"));
	DBG_RETURN(SUCCESS);
}

//-----------------------------------------------------------
//��Ʊ���Ͼ����������
//-----------------------------------------------------------
UINT8 INVM_InvWasteHandle(SaleData *pSaleData)
{
	DBG_ENTER("InvWasteHandle");
	DBG_PRINT(("����InvWasteHandle����"));
	DBG_ASSERT_EXIT((pSaleData != NULL), (" pSaleData == NULL!"));
	
	UINT8 ret;
	
	//������Ʊ
	CInvHead curInvHead;
    pSaleData->m_smallInvInfo = &curInvHead;
	DBG_ASSERT_EXIT((pSaleData->m_smallInvInfo != NULL), (" pSaleData->m_smallInvInfo == NULL!"));
	
	INVM_BuildWasteInv(pSaleData->m_smallInvInfo);
	
	//���ÿ�Ʊ���
	ret = pSaleData->MakeInvoiceHandle(0, INV_ROLL_PROC);
    DBG_PRINT(("ret= %u",ret));
	if (ret != SUCCESS)
	{
		DBG_RETURN(ret);
	}
	
	pSaleData->InitSaleData(1);
	pSaleData->m_smallInvInfo = NULL;
	DBG_PRINT(("�˳�InvWasteHandle����"));
	DBG_RETURN(SUCCESS);	
}

//-----------------------------------------------------------
//�������Ϸ�Ʊ
//-----------------------------------------------------------
void INVM_BuildWasteInv(CInvHead *pInvHead)
{
	DBG_ENTER("BuildWasteInv");	
	//DBG_ASSERT_EXIT((pInvHead != NULL), (" pInvHead == NULL!"));
	
	DBG_PRINT(("����BuildWasteInv����"));
	DBG_PRINT(("g_globalArg->m_curInvVol->m_code == %s", g_globalArg->m_curInvVol->m_code.c_str()));
	DBG_PRINT(("g_globalArg->m_curInvVol->m_ieno == %u", g_globalArg->m_curInvVol->m_ieno));
	DBG_PRINT(("g_globalArg->m_curInvVol->m_remain == %u", g_globalArg->m_curInvVol->m_remain));
	pInvHead->m_fpdm = g_globalArg->m_curInvVol->m_code;											//��Ʊ����
	//pInvHead->m_fphm = g_globalArg->m_curInvVol->m_ieno + 1 - g_globalArg->m_curInvVol->m_remain;	//��Ʊ����
	pInvHead->m_fphm = g_globalArg->m_curInvVol->m_curInvNo; //��Ʊ����
	DBG_PRINT(("pInvHead->m_fpdm == %s", pInvHead->m_fpdm.c_str()));
	DBG_PRINT(("pInvHead->m_fphm == %u", pInvHead->m_fphm));
    
	pInvHead->m_kplx = WASTE_INV;			//��Ʊ����	
	pInvHead->m_yfphm = 0;					//ԭ��Ʊ����
	pInvHead->m_kphjje = 0;					//��Ʊ�ܽ�� 
	pInvHead->m_sphsl = 0;					//��Ʒ�и���	
    DBG_PRINT(("pInvHead->m_kplx == %u", pInvHead->m_kplx));
    DBG_PRINT(("pInvHead->m_yfphm == %u", pInvHead->m_yfphm));
	
   	pInvHead->m_kprq = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);	//��Ʊ����
	pInvHead->m_kpsj = TDateTime::CurrentDateTime().FormatInt(HHMMSS);	//��Ʊʱ��
	
	
	pInvHead->m_fkdw = "";					//����������
	DBG_PRINT(("pInvHead->m_fkdw == %s", pInvHead->m_fkdw.c_str()));
	
	pInvHead->m_sky = g_globalArg->m_operator->m_name;			//����Ա����
	//	pInvHead->m_skyid = g_globalArg->m_operator->m_opid;		//����Աid	
	DBG_PRINT(("pInvHead->m_sky == %s", pInvHead->m_sky.c_str()));
	
	
	pInvHead->m_backup1 = "";		//�����ֶ�1
	pInvHead->m_bzkz = "";
	pInvHead->m_hczt = "";		    //�Ƿ���Ժ��״̬ 
	//	pInvHead->m_backup3 = "";		//�����ֶ�3
	
    pInvHead->DelList();			//�ͷ�����ռ�
	
	DBG_PRINT(("�˳�BuildWasteInv����"));
	return;
}

UINT8 INVM_CheckIsNoDB(string invCode,UINT32 invNo,CInvHead *pInvHead)
{
	//��ѯ��Ҫ�˵ķ�Ʊ��Ϣ
	INT8 value[256];
	memset((void*)value, 0, sizeof(value));
	INT32 errorcode=0;
	sprintf(value,"where FPDM = '%s' and FPHM = %u",invCode.c_str(), invNo);
//	errorcode = pInvHead->LoadOneRecordBySql(value);

	pInvHead->m_filter.append(value);
	errorcode = pInvHead->Load();
	
	DBG_PRINT(("errorcode= %d",errorcode));
	DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
	if (errorcode != SQLITE_OK)
	{
		if (errorcode == SQLITE_DONE)
		{
		return NO_INV; 	
	}
		else
		{
			return QUERY_ERROR; 
		}	
	}
	return SUCCESS;
}
//---------------------------------------------------------------------
//���鷢Ʊ�Ƿ����
//---------------------------------------------------------------------
UINT8 INVM_CheckIsNoRet(CInvHead *pInvHead)
{
	DBG_ENTER("MKINV_CheckIsNoRet");
	DBG_PRINT(("����MKINV_CheckIsNoRet����"));
	
	DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
	
	//��Ʊ�Ƿ��ڱ�����//debug
	
	DBG_PRINT(("pInvHead->m_kprq= %u",pInvHead->m_kprq));

	INT32 nReturn = CmpCurMonth(pInvHead->m_kprq, pInvHead->m_kpsj);
	DBG_PRINT(("nReturn= %d",nReturn));
	if (0 == nReturn) 
	{
		DBG_PRINT(("���·�Ʊ,���ó��%d", nReturn));
		// DBG_RETURN(BX_RET_MONTH_ERR);
	}
	
	INT8 value[256];
	memset((void*)value, 0, sizeof(value));
	INT32 errorcode;
	sprintf(value,"where FPDM = '%s' and FPHM = %u",pInvHead->m_fpdm.c_str(), pInvHead->m_fphm);
	
	//��Ϊ���˷�Ʊ������
	CRtInv rtInv;
	rtInv.m_filter = value;
	//��ѯ
	rtInv.Requery();
	DBG_PRINT(("pInvHead->m_bzkz = %s", pInvHead->m_bzkz.c_str()));	
	if ((rtInv.LoadOneRecord() == SQLITE_OK)||("1" == pInvHead->m_bzkz))
	{
		DBG_PRINT((" This invoice already has returned invoice!"));
		DBG_RETURN(HAVE_RT_INV);	
	}
		
	//��Ϊ��Ʊ������
	if ((pInvHead->m_kplx == RETURN_INV)||(pInvHead->m_kplx == RET_MANUAL_INV)||
		(pInvHead->m_kplx == RET_SPECIAL_INV)) 
	{
		DBG_RETURN(RT_INV);		
	}
	//��Ϊ��Ʊ������
	if( (pInvHead->m_kplx == WASTE_INV) || (pInvHead->m_kplx == WASTE_NOR) 
		|| (pInvHead->m_kplx == WASTE_RET))
	{
		DBG_RETURN(WT_INV);		
	}
	
	//���ܿ���Ʊ������
	DBG_PRINT(("pInvHead->m_hczt = %s", pInvHead->m_hczt.c_str()));	
	if ( "1" == pInvHead->m_hczt) 
	{		
		g_globalArg->m_strMsg =pInvHead->m_backup2;
		DBG_RETURN(INV_LIB_ERR);
	}
		
	DBG_PRINT(("�˳�CheckInvReturn����"));
	DBG_RETURN(SUCCESS);
}

//-----------------------------------------------------------
//�˱�����Ʊ
//-----------------------------------------------------------
UINT8 INVM_InvReturn(SaleData *pSale,CInvHead *pInvHead)
{
	DBG_ENTER("INVM_InvReturn");
	DBG_ASSERT_EXIT((pInvHead != NULL), (" pInvHead == NULL!"));
	
	INT8 value[128];
	memset((void*)value, 0, sizeof(value));
	
	pSale->m_singleInvInfo =pInvHead;
	
	DBG_PRINT(("pSale->m_singleInvInfo->m_fphm=%u",pSale->m_singleInvInfo->m_fphm));
	
	//��װ��Ʊ��Ϣ
	pSale->m_singleInvInfo->m_yfpdm = pSale->m_singleInvInfo->m_fpdm;
	pSale->m_singleInvInfo->m_yfphm = pSale->m_singleInvInfo->m_fphm;
    pSale->m_singleInvInfo->m_kplx = RETURN_INV;
	pSale->m_singleInvInfo->m_sky = g_globalArg->m_operator->m_name;//ȡ��ǰ����Ա
	sprintf(value, "��Ӧ������Ʊ����:%s����:%08lu",
		pSale->m_singleInvInfo->m_yfpdm.c_str(), pSale->m_singleInvInfo->m_yfphm);	
	pSale->m_singleInvInfo->m_backup1 = value;
	
	INT64 moneySum = pSale->m_singleInvInfo->m_kphjje;
	
	//�����Ʊ�ۼƽ���
//	if ((g_globalArg->m_returnVolSum + moneySum)>MAX_MONEY)
//	{
//		DBG_PRINT((" Warning: m_returnVolSum exceed the limit!"));
//		DBG_RETURN(RVM_SUM_EXCEED);
// 	}
	 	 
	UINT8 nIfInvSum; //�Ƿ�ִ���˾���ܲ��� 1���ǣ�0����
	UINT8 ret =pSale->PayByCash(nIfInvSum);

	DBG_PRINT(("ret= %u",ret));

	return ret; //��Ʊ
}

UINT8 INVM_InvRetProc(CInvHead *pInvHead)
{

    DBG_PRINT(("����INVM_InvRetProc����"));
	
	UINT8 ret;

	CaProgressBar proBar("��Ʊ��ӡ��.....");
    proBar.ReFresh();

	if (NULL==pSaleData)//extern SaleData *pSaleData; /**< ����������ָ��*/

	{
		pSaleData = new SaleData;
	}	
	DBG_ASSERT_EXIT((pSaleData != NULL), (" pSaleData == NULL!"));

	ret = INVM_InvReturn(pSaleData,pInvHead); //�˱�����Ʊ
	
	DBG_PRINT(("ret= %u",ret));
	if (ret != SUCCESS)
	{
		pSaleData=NULL;
		return ret;
	}
    
	pSaleData=NULL;

	return  SUCCESS;
}

//�˷Ǳ�����Ʊ���˻���
// UINT8 ReturnGoods(SaleData *pSale, string codeNo, UINT32 invNo)
// {
// 	DBG_ENTER("InvReturn");
// 	DBG_ASSERT_EXIT((pSale != NULL), (" pSale == NULL!"));
// 	
// 	pSale->m_invtype = RET_MANUAL_INV;//RETURN_INV; 
// 	pSale->m_oldInv = invNo;
// 	pSale->m_oldCodeNo = codeNo;
// 	pSale->m_returnOther = 1;
// 	
// 	DBG_RETURN(SUCCESS);
//
//-----------------------------------------------------------
//�����Ʊ
//-----------------------------------------------------------
// UINT8 InvReturnSpe(SaleData *pSale)
// {
// 	DBG_ENTER("InvReturn");
// 	DBG_ASSERT_EXIT((pSale != NULL), (" pSale == NULL!"));
// 	
// 	//	pSale->m_invtype = RETURN_INV; 
// 	//�˷Ǳ�����Ʊ��Ʊ����RETURN_MANUAL_INV
// 	pSale->m_invtype = RET_SPECIAL_INV; 
// 	pSale->m_oldInv = 0;
// 	pSale->m_oldCodeNo = "";
// 	pSale->m_returnOther = 1;
// 	
// 	DBG_RETURN(SUCCESS);	
// }

//-----------------------------------------------------------
//ͨ����Ʊ�����ѯ��Ʊ���������
//-----------------------------------------------------------
// UINT8 CheckInvCode(INT8 *code)
// {
// 	DBG_PRINT(("CheckInvCode"));
// 	
// 	char sqlbuf[128];
// 	CInvVol pInvVol;
// 	
// 	memset(sqlbuf, 0, sizeof(sqlbuf));
// 	sprintf(sqlbuf, "where CODE = '%s' ", code);
// 	pInvVol.m_filter.append(sqlbuf);
// 	
// 	pInvVol.Requery();
// 	int errcode = pInvVol.LoadOneRecord();
// 	if( errcode != SQLITE_OK )
// 		return FAILURE;
// 	
// 	return SUCCESS;
// }

//-------------------------------------------------------------
//��ȡ������ݿ��м�¼�ķ�Ʊ����
//-------------------------------------------------------------
UINT8 INVM_GetVolNum(UINT32 &nNum)
{
	DBG_ENTER("GetVolNum(UINT32 &nNum)");
	
	INT32 errorcode;
	nNum = 0;
	INT32 nTmpNum = 0;
	CInvVol curInvVol;
	CInvVol *pInvVol = &curInvVol;
	DBG_ASSERT_EXIT((pInvVol != NULL), (" pInvVol == NULL!"));
	
	//���ܼ�¼�����ѷַ�δ���룬��ֵpageNum
	pInvVol->m_filter = "where USED_FLAG = 1 and OVER_FLAG = 1";
	nTmpNum = pInvVol->GetRecordNum();
	if (nTmpNum <= 0)
	{
		pInvVol = NULL;
		DBG_RETURN(FAILURE); 
	}
	
	nNum = nTmpNum;
	pInvVol = NULL;
	DBG_PRINT((" GetVolNum!"));
	DBG_RETURN(SUCCESS);
}

//------------------------------------------------------------------
//
//------------------------------------------------------------------
UINT8 YesNoBox(string strMsg)
{
	DBG_ENTER("YesNoBox(string strMsg)");
	
	// 	INT8 value[256];
	// 	memset((void*)value, 0, sizeof(value));
	//	sprintf(value,"%u��Ʊδ����,�鿴��?",nNum);
	
	CaMsgBox msgBox(strMsg.c_str(),CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
	{
		DBG_PRINT((" YesNoBox(string strMsg)  FAILURE"));
		DBG_RETURN(FAILURE); 
	}
	
	if(msgBox.m_iStatus == OK_PRESSED)
	{
		DBG_PRINT((" YesNoBox(string strMsg)  SUCCESS"));
		DBG_RETURN(SUCCESS);		
	}
}
//------------------------------------------------------------------
//�����ӡ
//------------------------------------------------------------------
UINT8 INVM_GetInvNum(string nCode, UINT32 nStartNo, UINT32 nEndNo, UINT32 &nNum)
{
	DBG_ENTER("GetInvNum(UINT32 &nNum)");
	
	nNum = 0;
	INT32 errorcode;
	INT32 nTmpNum = 0;
	CInvHead curInvHead;
	CInvHead *pInvHead = &curInvHead;
	DBG_ASSERT_EXIT((pInvHead != NULL), (" pInvHead == NULL!"));
	
	//���ܼ�¼�����ѷַ�δ���룬��ֵpageNum
	
	INT8 value[256];
	memset((void*)value, 0, sizeof(value));
	pInvHead->m_filter = "where FPDM = ";
	sprintf(value,"'%s' and FPHM >= %u and FPHM <= %u",nCode.c_str(),nStartNo,nEndNo);
	pInvHead->m_filter.append(value);
	DBG_PRINT((" pInvHead->m_filter = %s", pInvHead->m_filter.c_str()));
	nTmpNum = pInvHead->GetRecordNum();
	
	pInvHead = NULL;
	
	if (nTmpNum<0)
	{
		DBG_RETURN(FAILURE); 
	}
    nNum = nTmpNum;
	DBG_RETURN(SUCCESS); 
}

//-----------------------------------------------------------
//��ӡ��Ʊ���
//-----------------------------------------------------------
UINT8 PrnInvStub(CInvHead *smallInvInfo, UINT8 IfPrnChar)
{

	DBG_ASSERT_EXIT((smallInvInfo != NULL), (" smallInvInfo == NULL!"));
	
	//�ж�װ��ֽ�ʷ�Ʊ	
	if (isPaper() != 0)
	{		
		DBG_RETURN(NO_PAPER);
	}	
	
	//���ٴ�ӡ���ݽṹ����ڴ�
	TPrnInvoiceInfo *pInvPrnData;
	pInvPrnData = &g_invPrnData;;
	if(pInvPrnData==NULL)
	{
		DBG_PRINT((" malloc(sizeof(pInvPrnData) error !"));
		DBG_RETURN(MALLOC_MEM_ERROR);		
	}
	memset((void *)pInvPrnData, 0, sizeof(TPrnInvoiceInfo));//��ӡ�ṹ����������
	if (1==IfPrnChar) 
	{
		pInvPrnData->PrintType = STUB_PRINT; //��ӡ����Ϊ�����ӡ
	}
	
	//������,���
	FillPrnInvHead(pInvPrnData, smallInvInfo);
	FillPrnInvDetail(pInvPrnData, smallInvInfo);			
	FillPrnInvTail(pInvPrnData, smallInvInfo);
	
	//�����棬��ӡ
	print_invoice_head(pInvPrnData);
	print_invoice_data_cycle(pInvPrnData, 0);				
	print_invoice_tail(pInvPrnData);
	
	pInvPrnData = NULL;
	
	DBG_RETURN(SUCCESS);
	
}

//------------------------------------------------------------------
//��������
//------------------------------------------------------------------
// UINT8 WasteInvVol(void)
// {
// 	UINT8 nRet = SUCCESS;
// 	INT32 nErrcode;
// 	CInvVol invVol;
// 	string sqlstr = "";
// 	
// 	sqlstr="update INV_VOL set USED_FLAG = 1 where USED_FLAG = 0 and OVER_FLAG = 1";
// 	invVol.SetSQL(sqlstr);
// 	if (invVol.ExecuteSQL() != SQLITE_OK)
// 	{
// 		nRet = FAILURE;//��������ʧ��
// 	}
// 	else
// 	{
// 		g_globalArg->m_curInvVol->m_isno = 0;	/**< ��Ʊ��ʼ���� */
// 		g_globalArg->m_curInvVol->m_ieno = 0;	/**< ��Ʊ��ֹ���� */
// 		g_globalArg->m_curInvVol->m_remain = 0;		/**< ��Ʊ��ʣ����� */	
// 		g_globalArg->m_curInvVol->m_usedflag = 1;	/**< ��Ʊ�����־ 1:δ���� 0:���� */
// 		g_globalArg->m_curInvVol->m_overflag = 1;	/**< ��Ʊ�������־ 1:δ���� 0:���� */
// 	}
// 	
// 	return nRet;
// }

//�Ƿ���
INT32 CmpCurMonth(UINT32 nDate, UINT32 nTime)
{
	INT32 nRet = 1;
	//��Ʊ�Ƿ��ڱ�����???????
	UINT32 curYear, curMonth, curDay;
	UINT32 tmpYear, tmpMonth, tmpDay;
	TDateTime::CurrentDateTime().DecodeDate(curYear, curMonth, curDay);
	DBG_PRINT(("curYear=%u, curMonth = %u, curDay = %u", curYear, curMonth, curDay));
	TDateTime invDate(nDate, nTime);
	invDate.DecodeDate(tmpYear, tmpMonth, tmpDay);
	DBG_PRINT(("tmpYear=%u, tmpMonth = %u, tmpDay = %u", tmpYear, tmpMonth, tmpDay));
	
	if (tmpYear < curYear) 
	{
		DBG_PRINT(("tmpYear < curYear"));
		nRet = -1;		
	}
	else if (tmpYear == curYear) 
	{
		if (tmpMonth < curMonth) 
		{
			DBG_PRINT(("tmpMonth < curMonth"));
			nRet = -1;			
		}
		else if (tmpMonth == curMonth) 
		{
			DBG_PRINT(("tmpMonth == curMonth"));
			nRet = 0;
		}		
	}
	
	return nRet;
}

//�ѿ���Ʊ����
UINT8 INVM_WstInv(CInvHead* pInvHead, string &strErr)
{
	DBG_ASSERT_EXIT((pInvHead != NULL), (" pInvHead == NULL!"));
	INT32 ret = SUCCESS;
    INT8 val[256];
	string strsql("");
	UINT8 waste_type = 0;
	UINT8 tmpType = pInvHead->m_kplx;
	
	switch(pInvHead->m_kplx) 
	{
	case NORMAL_INV:
		waste_type = WASTE_NOR;//��Ʊ�������ϣ���Ϊ����Ʊ
		break;
	case RETURN_INV:
	case RET_MANUAL_INV:
	case RET_SPECIAL_INV:
		waste_type = WASTE_RET;//��Ʊ(��Ʊ)Ҳ�������ϣ���Ϊ����Ʊ
		break;
	default:;
	}
	
	UINT8 zflx= 1; //�ѿ���Ʊ����
	ret= g_pAPIBase->MakeWasteInv_API(*g_YwXmlArg, pInvHead, zflx, strErr);
	
	if (SUCCESS != ret)
	{			
		DBG_PRINT(("strErr = %s", strErr.c_str()));
		return FAILURE;
	}


	POWOFF_DISABLE(); //���ε����ж�
	//����INV_HEAD��Ʊ����
	
	memset((void*)val, 0x00, sizeof(val));
	sprintf(val, "where FPDM='%s' AND FPHM=%u", pInvHead->m_fpdm.c_str(), pInvHead->m_fphm);
	strsql = val;
	
	pInvHead->m_kplx = waste_type;
	pInvHead->m_kprq = pInvHead->m_zfrq;
	pInvHead->m_kpsj = pInvHead->m_zfsj;

	ret = pInvHead->Update(strsql, &(pInvHead->m_kplx), &(pInvHead->m_kprq), &(pInvHead->m_kpsj), NULL);

	if ( ret!= SQLITE_OK)
	{
		strErr = "���·�Ʊ��Ϣ�����";
		return FAILURE;
	}

	DBG_PRINT(("����INV_HEAD��Ʊ����strsql = %s", strsql.c_str()));

	//����INV_DET��Ʊ����
	CInvDet pInvDet;

	pInvDet.m_kplx = waste_type;
	pInvDet.m_kprq = pInvHead->m_zfrq;
	pInvDet.m_kpsj = pInvHead->m_zfsj;

	ret = pInvDet.Update(strsql, &(pInvDet.m_kplx), &(pInvDet.m_kprq), &(pInvDet.m_kpsj), NULL);
	
	if ( ret!= SQLITE_OK)
	{
		strErr = "���·�Ʊ��Ϣ�����";
		return FAILURE;
	}

	DBG_PRINT(("����INV_DET��Ʊ����strsql = %s", strsql.c_str()));
	
	//ɾ��RT_INV���У���Ʊ��Ӧ��ԭ��Ʊ����ͺ���
	DBG_PRINT(("pInvHead->m_kplx = %d", pInvHead->m_kplx));//��Ʊ���Ͳ����ӽ�˰���з���
	if(tmpType == RETURN_INV)
	{
		CRtInv rtInv;
		memset(val, 0, sizeof(val));
		sprintf(val, "where FPDM = '%s' and FPHM = %u ", pInvHead->m_yfpdm.c_str(), pInvHead->m_yfphm);
		DBG_PRINT(("val = %s", val));
		rtInv.m_filter = val;
		if( rtInv.Delete() != SQLITE_OK )
		{
			DBG_PRINT(("Delete RT_INV info error"));
		}
		DBG_PRINT(("Delete RT_INV info succeed"));
	}
	
	POWOFF_ENABLE(); //�������ж�
	
	DBG_PRINT(("WstInv() SUCCESS"));
		
	return SUCCESS;
}	
	
//����Ʊ�����ѯ��Ʊ��ϸ
UINT8 INVM_InvDetailNOQuery(string invCode,UINT32 invNO)
{		
	INT32 Ret=SUCCESS;
	string strErr("");
	string strsql("");

	INT32 ret=0;

	CaProgressBar proBar("��Ʊ��Ϣ��ѯ��.....");
    proBar.ReFresh();
	
	//��Ʊ��ϸ��ѯ
	CInvHead Invhead;
	UINT32 invNum=0;//��Ʊ����
	UINT8 cxfs=0;  //0������Ʊ����β�ѯ
	string cxtj(""); // cxfsΪ0ʱ��12��Ʊ����+8λ��ʼ����+8λ��ֹ����
	cxtj =invCode;
	INT8 tmpChar[16];
    memset((void *)tmpChar,0x00,sizeof(tmpChar));
	sprintf(tmpChar,"%08u",invNO);
	cxtj.append(tmpChar); 
	cxtj.append(tmpChar);
	DBG_PRINT(("cxtj= %s",cxtj.c_str()));

	Ret=g_pAPIBase->GetInvHeadInfo_API(*g_YwXmlArg, cxfs, cxtj, invNum, &Invhead, strErr);
	DBG_PRINT(("Ret= %d",Ret));
	if (Ret !=SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return FAILURE;
	}

	//�鿴�����Ƿ��и÷�Ʊ��Ϣ
	CInvHead invheadtmp;
	INT8 sqlbuf[128];
	memset(sqlbuf, 0x00, sizeof(sqlbuf));
	sprintf(sqlbuf, "where FPDM = '%s' and FPHM = %u", invCode.c_str(), invNO);
	invheadtmp.m_filter = sqlbuf;
	invheadtmp.Requery();
	if (invheadtmp.LoadOneRecord() == SQLITE_OK)
	{
		// 		DBG_PRINT(("�������и÷�Ʊ!"));
		//CaMsgBox::ShowMsg("�������и÷�Ʊ!");
	   //	return FAILURE; 
      //�жϱ������ݿ�����������Ƿ���ת����һ��
		DBG_PRINT(("invheadtmp.m_kplx= %u",invheadtmp.m_kplx));
	    DBG_PRINT(("Invhead.m_kplx= %u",Invhead.m_kplx));
      if (invheadtmp.m_kplx != Invhead.m_kplx )
      {
		  strsql = sqlbuf;
		  invheadtmp.m_kplx = Invhead.m_kplx;
		  ret = invheadtmp.Update(strsql, &(invheadtmp.m_kplx), NULL);
		  DBG_PRINT(("ret= %d",ret));
		  if ( ret!= SQLITE_OK)
		  {
			  strErr = "���·�Ʊͷ��Ϣ�����";
			  return FAILURE;
		  }

		  //����INV_DET��Ʊ����
		  CInvDet invDet;
		  invDet.m_kplx =invheadtmp.m_kplx;
		  ret = invDet.Update(strsql, &(invDet.m_kplx), NULL);
		  DBG_PRINT(("ret= %d",ret));
		  if ( ret!= SQLITE_OK)
		  {
			  strErr = "���·�Ʊ��ϸ��Ϣ�����";
			  return FAILURE;
		  }

      }

	}
	else
	{
		//��Ʊ��Ϣ����
		if (SUCCESS != Invhead.Save())
		{
			CaMsgBox::ShowMsg("��ѯ��Ʊ�洢ʧ��!");
				 return FAILURE;
		  }
		DBG_PRINT(("Invhead.m_kplx= %u",Invhead.m_kplx));
		if(Invhead.m_kplx == RETURN_INV)
		{
			CRtInv rtInv;
		     rtInv.m_fpdm =Invhead.m_yfpdm;
			 rtInv.m_fphm =Invhead.m_yfphm;
			 ret = rtInv.AddNew();				//д���˷�Ʊ��Ϣ��
			 DBG_PRINT(("ret= %d",ret));
			 if ( ret!= SQLITE_OK)
			 {
				 strErr = "��ѯ��Ʊ���洢��Ʊ��Ϣ�����";
				 return FAILURE;
		  }
		
	}
	}

	CaMsgBox::ShowMsg("��ѯ��Ʊ�ɹ�");

	return SUCCESS;
}

void INVM_ErrMsgBox(UINT8 ret)
{
	string pText("");
	
	switch(ret)
	{
	case INV_SUM_ERROR:
		pText = "�����ʧ��";
		break;
	case PRN_INV_ERROR:
		pText = "��Ʊʧ��";
		break;
	case RETURN_NUM_ERROR:
		pText = "��Ʊ���벻����";
		break;
	case NO_INV:
		pText = "�Ǳ���������Ʊ";
		break;
	case RT_INV:
		pText = "��Ʊ���ܱ�����Ʊ";
		break;
	case WT_INV:
		pText = "��Ʊ���ܱ�����Ʊ";
		break;
	case BX_RET_MONTH_ERR:
		pText="���·�Ʊ���ܿ���Ʊ";
		break;
	case RM_SUM_EXCEED:
		pText = "��Ʊ�ۼƽ���";
		break;
	case RVM_SUM_EXCEED:
		pText = "�����Ʊ�ۼƽ���";
		break;
	case HAVE_RT_INV:
		pText = "�ѿ�����Ʊ";
		break;
	case CODE_NO_ERROR:
		pText = "��Ʊ����Ƿ�";
		break;
	case NO_PAPER:
		pText = "û��ֽ�ʷ�Ʊ";
		break;
	case NO_ISSUED_INV:
		pText = "����δ����Ʊ�����˻�";
		break;
	case DB_FULL:
		pText = "�洢�ռ�������\n�޷���Ʊ�뾡���걨";
		break;
	case HAVE_ROLLED:
		pText = "��Ϣ����ɹ�";
		break;
	case UPDATE_INV_VOL_ERROR:
		pText = "���·�Ʊ������Ϣ��ʧ��";
		break;
	   case GET_FISCAL_CODE_ERROR:
		   pText = "���ɷ�α��ʧ��";
		   break;
	   case DB_SAVE_ERROR:
		   pText = "�����ݿ�ʧ��";
		   break;
	   case MALLOC_MEM_ERROR:
		   pText = "���붯̬�ڴ�ʧ��";
		   break;
	   case INV_LIB_ERR:
		   pText = g_globalArg->m_strMsg;
		   g_globalArg->m_strMsg = "";
		   break; 
	   case INV_ZERO:
		   pText = "�޿��÷�Ʊ��";
		   break;
	   case GX_SV_NUM_EXCEED:
		   pText = "���߿�Ʊ��������";
		   break;
	   case GX_SV_SUM_EXCEED:
		   pText = "���߿�Ʊ����";
		   break;
	   case GX_SV_TIME_EXCEED:
		   pText = "���߿�Ʊʱ�䳬��";
		   break;
	   case NM_EXCEED_MIN:
		   pText =  "�ܽ�������С��Ʊ���";
	   case NO_ISSUED_VOL:
		   pText = "��Ʊδ����,���ܿ���Ʊ";
		   break;
	   case NM_EXCEED:
		   pText = "���ſ�Ʊ����";
		   break;
	   case DIF_PYCODE:
		   pText = "��Ʊ�뵱ǰ��ƱƱ����ͬ";
		   break;
	case WASTE_NUM_EXCEED:
		pText = "����ʣ�෢Ʊ����";
		break;
	case WASTE_NUM_ERROR:
		pText = "���Ϸ���������";
		break;
	case MUST_RE_LOGIN:
		pText = "��Ʊ�������꣬\n�����ص�¼";
		break;
	case PRE_INV_ERROR:
		pText = "��ѯ�ϱʽ���ʧ��";
		break;
	case NO_DIST_INV:
		pText = "��ǰ0��Ʊδ����";
		break;
	case QUERY_ERROR:
		pText = "���ݿ��ѯʧ��";
		break;
	   default:
		   pText="��������";
		   break;
	}  
	
	CaMsgBox::ShowMsg(pText);
	return ;
}