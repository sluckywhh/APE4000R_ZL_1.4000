/*! \file    SaleFunc.cpp
\brief    awe4000r�����е�Ӧ�ú���
\author   zcy
\version  1.0
\date     2015-05-13
*/



#include "SaleFunc.h"
//#include "CUserMore.h"
#include "CInvServ.h"
#include "CInvSum.h"
#include "APIBase.h"
#include "powoff_protect.h"
#include "SaleBusinessFunc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"




UINT8 SALE_GetCurInv(CInvVol *pInvVol,string &strErr)
{
	
	INT32 ret=SUCCESS;

	ret=g_pAPIBase->GetCurInvInfo_API(*g_YwXmlArg, pInvVol, strErr);

	if (ret !=SUCCESS)
	{
		return FAILURE;
	}
	g_YwXmlArg->m_fplxdm = pInvVol->m_fplxdm;
	DBG_PRINT(("g_YwXmlArg->m_fplxdm = %s", g_YwXmlArg->m_fplxdm.c_str()));
  

	return SUCCESS;
}

UINT8 SALE_MakeInvHand(CInvHead *pInvHead,string &strErr)
{

	INT32 ret=SUCCESS;

	DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
	if((pInvHead->m_kplx == NORMAL_INV)||(pInvHead->m_kplx ==RETURN_INV))
	{	
		ret= g_pAPIBase->MakeNormalInv_API(*g_YwXmlArg, pInvHead, strErr);
	}
	else if (pInvHead->m_kplx == WASTE_INV)
	{	
		//ִ���̵ķ�Ʊ����
		UINT8 zflx= 0; //�հ�����
		ret= g_pAPIBase->MakeWasteInv_API(*g_YwXmlArg, pInvHead, zflx, strErr);
	}
				
	DBG_PRINT(("ret= %d",ret));
	if (ret !=SUCCESS)
	{
		return FAILURE;
	}
		
	return SUCCESS;
}


//---------------------------------------------------------------------------
//����ӡ��Ʊ�ṹ��ķ�Ʊͷ
//---------------------------------------------------------------------------
UINT8 FillPrnInvHead(TPrnInvoiceInfo *pPrnInvInfo, CInvHead *smallInvInfo)
{
	DBG_ENTER("SaleData::FillPrnInvHead");
	DBG_PRINT(("����FillPrnInvHead����"));
	UINT8 N;
	INT32 nLen, errorcode;
	
	DBG_ASSERT_EXIT((smallInvInfo != NULL), (" smallInvInfo == NULL!"));
	DBG_ASSERT_EXIT((pPrnInvInfo != NULL), (" pPrnInvInfo == NULL!"));
	
	//��Ʊ������ 20 ASC
	memset((void *)pPrnInvInfo->chTypeCode, 0, sizeof(pPrnInvInfo->chTypeCode));
	memcpy((void *)pPrnInvInfo->chTypeCode, (void *)(smallInvInfo->m_fpdm.c_str()), smallInvInfo->m_fpdm.length());
	DBG_PRINT(("��Ʊ����  : %s ", pPrnInvInfo->chTypeCode));
	
	//��Ʊ����
	pPrnInvInfo->InvNo = smallInvInfo->m_fphm; 
	DBG_PRINT(("��Ʊ����  : %d ", pPrnInvInfo->InvNo));
	
	//��Ʊ���� CCYYMMDD
	pPrnInvInfo->m_Date = smallInvInfo->m_kprq;
	DBG_PRINT(("��Ʊ����  : %u ", pPrnInvInfo->m_Date));
	
	//��Ʊʱ��
	pPrnInvInfo->m_Time = smallInvInfo->m_kpsj;
    DBG_PRINT(("��Ʊʱ��  : %u ", pPrnInvInfo->m_Time));
	
	//��Ʊ����
	pPrnInvInfo->InvType = smallInvInfo->m_kplx;
	DBG_PRINT(("��Ʊ����  : %d ", pPrnInvInfo->InvType));
	
	//ԭ��Ʊ����
	pPrnInvInfo->PosInvNo = smallInvInfo->m_yfphm;
	DBG_PRINT(("ԭ��Ʊ����: %u ", pPrnInvInfo->PosInvNo));
	
	//���λ
	nLen = smallInvInfo->m_fkdw.length() + 1;
	// 	if (smallInvInfo->m_kplx == RETURN_INV)
	// 	{
	// 		sprintf(pPrnInvInfo->chClientName, "%08lu", pPrnInvInfo->PosInvNo);
	// 	}
	// 	else
	//	{
	memcpy((void *)pPrnInvInfo->chClientName, (void *)smallInvInfo->m_fkdw.c_str(), nLen);
	//	}	
	N = strlen((INT8 *)pPrnInvInfo->chClientName);
	DBG_PRINT(("������  : %s ", pPrnInvInfo->chClientName));
	// ע��������Ϊ�˲����ո�
	
	if (N > 0)
	{
		if (N <= 40)
		{
			memset((void *)&pPrnInvInfo->chClientName[N], ' ', 40 - N);
			pPrnInvInfo->chClientName[40] = '\0';
		}
		else
		{
			for(;;)
			{
				if (pPrnInvInfo->chClientName[--N] == ' ')
				{
					pPrnInvInfo->chClientName[N] = 0x0;
					if (N == 0 || N == 40)
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	
	//�տ�Ա
	nLen = smallInvInfo->m_sky.length() + 1;
	memcpy((void *)pPrnInvInfo->chOperatorName, (void *)smallInvInfo->m_sky.c_str(), nLen);
    DBG_PRINT(("�տ�Ա  : %s ", pPrnInvInfo->chOperatorName));
	
	//�տ�ԱID
	
	//���ʽ
	
	//��Ʒ������
	
	//˰��
	
	//������
	
	//Ʊ�����
	
	
	
	//��α˰����
	nLen = smallInvInfo->m_fwm.length();
	memset((void *)pPrnInvInfo->chTaxCtrCode, 0, sizeof(pPrnInvInfo->chTaxCtrCode));
	memcpy((void *)pPrnInvInfo->chTaxCtrCode, (void *)smallInvInfo->m_fwm.c_str(), nLen);
    DBG_PRINT(("��α˰����  : %s ", pPrnInvInfo->chTaxCtrCode));
	
	//��ӡ����
		
	//��˰������ 40 ASC
	nLen = g_globalArg->m_corpInfo->m_Nsrmc.length() + 1;
	memcpy((void *)pPrnInvInfo->chCorpName, (void *)g_globalArg->m_corpInfo->m_Nsrmc.c_str(), nLen);
	N = strlen((INT8 *)pPrnInvInfo->chCorpName);
    DBG_PRINT(("��˰������  : %s ", pPrnInvInfo->chCorpName));
	// ��˰�����ƣ��տλ��ע��������Ϊ�˲����ո�
	
	if (N > 0)
	{
		if (N <= 40)
		{
			memset((void *)&pPrnInvInfo->chCorpName[N], ' ', 40 - N);
			pPrnInvInfo->chCorpName[40] = '\0';
		}
		else
		{
			for(;;)
			{
				if (pPrnInvInfo->chCorpName[--N] == ' ')
				{
					pPrnInvInfo->chCorpName[N] = 0x0;
					if (N == 0 || N == 40)
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	
	
	//��˰��ʶ��� 16ASC
	memset(pPrnInvInfo->chCorpCode, 0, sizeof(pPrnInvInfo->chCorpCode));
	memcpy((void *)pPrnInvInfo->chCorpCode, (void *)g_globalArg->m_corpInfo->m_Nsrsbh.c_str(), g_globalArg->m_corpInfo->m_Nsrsbh.length());
	DBG_PRINT(("��˰��ʶ���  : %s ", pPrnInvInfo->chCorpCode));	
	
	//�������� 16 ASC
	memset(pPrnInvInfo->chMachineNo, 0, sizeof(pPrnInvInfo->chMachineNo));
	memcpy((void *)pPrnInvInfo->chMachineNo, (void *)g_globalArg->m_machine->m_machineNo.c_str(), g_globalArg->m_machine->m_machineNo.length());
	DBG_PRINT(("��������  : %s ", pPrnInvInfo->chMachineNo));	
	
	
	//���ʶ��� 16ASC
	if (smallInvInfo->m_fkdwsh == PAYER_NAME_DEF)
	{
		smallInvInfo->m_fkdwsh = "";
	}
	memset(pPrnInvInfo->chClientCode, 0, sizeof(pPrnInvInfo->chClientCode));
	memcpy((void *)pPrnInvInfo->chClientCode, (void *)smallInvInfo->m_fkdwsh.c_str(), smallInvInfo->m_fkdwsh.length());
	DBG_PRINT(("���ʶ���  : %s ", pPrnInvInfo->chClientCode));	
	
	//�����ֶ�
	if( smallInvInfo->m_kplx == RET_SPECIAL_INV )
	{
		smallInvInfo->m_backup1 = "�����Ʊ  " + smallInvInfo->m_backup1;
	}
	memset(pPrnInvInfo->chRemarks, 0, sizeof(pPrnInvInfo->chRemarks));
	memcpy((void *)pPrnInvInfo->chRemarks, (void *)smallInvInfo->m_backup1.c_str(), smallInvInfo->m_backup1.length());
	if ((smallInvInfo->m_kplx==RETURN_INV)||(smallInvInfo->m_kplx==RET_SPECIAL_INV)||(smallInvInfo->m_kplx==RET_MANUAL_INV))
	{
		memset(pPrnInvInfo->chClientName, 0, sizeof(pPrnInvInfo->chClientName));
		memcpy((void *)pPrnInvInfo->chClientName, (void *)smallInvInfo->m_backup1.c_str(), smallInvInfo->m_backup1.length());
	}
	DBG_PRINT(("���λ  : %s ", pPrnInvInfo->chClientName));	
	
	//�Զ����ǩ1
	string strZdy("");
	if("" != g_globalArg->m_prnInfo->m_zdyTab1)
	{
		strZdy = g_globalArg->m_prnInfo->m_zdyTab1;
		strZdy += " : ";
		
	}
	strZdy += g_globalArg->m_prnInfo->m_zdyCont1;
	
	memset(pPrnInvInfo->chSelfDefTab1, 0, sizeof(pPrnInvInfo->chSelfDefTab1));
	memcpy((void *)pPrnInvInfo->chSelfDefTab1, (void *)strZdy.c_str(), strZdy.length());
	DBG_PRINT(("�Զ����ǩ1  : %s ", pPrnInvInfo->chSelfDefTab1));
	
	
	
	//�Զ�������1
	// 	memset(pPrnInvInfo->chSelfDefCont1, 0, sizeof(pPrnInvInfo->chSelfDefCont1));
	// 	memcpy((void *)pPrnInvInfo->chSelfDefCont1, (void *)g_globalArg->m_prnInfo->m_zdyCont1.c_str(),g_globalArg->m_prnInfo->m_zdyCont1.length());
	// 	DBG_PRINT(("�Զ����ǩ1  : %s ", pPrnInvInfo->chSelfDefCont1));	
	
	strZdy = "";
	if("" != g_globalArg->m_prnInfo->m_zdyTab2)
	{
		strZdy = g_globalArg->m_prnInfo->m_zdyTab2;
		strZdy += " : ";
	}
	strZdy += g_globalArg->m_prnInfo->m_zdyCont2;
	//�Զ����ǩ2
	
	memset(pPrnInvInfo->chSelfDefTab2, 0, sizeof(pPrnInvInfo->chSelfDefTab2));
	memcpy((void *)pPrnInvInfo->chSelfDefTab2, (void *)strZdy.c_str(), strZdy.length());
	DBG_PRINT(("�Զ����ǩ2  : %s ", pPrnInvInfo->chSelfDefTab2));	
	
	
	//�Զ�������2
	// 	memset(pPrnInvInfo->chSelfDefCont2, 0, sizeof(pPrnInvInfo->chSelfDefCont2));
	// 	memcpy((void *)pPrnInvInfo->chSelfDefCont2, (void *)g_globalArg->m_prnInfo->m_zdyCont2.c_str(),g_globalArg->m_prnInfo->m_zdyCont2.length());
	// 	DBG_PRINT(("�Զ����ǩ2  : %s ", pPrnInvInfo->chSelfDefCont2));	
	
	
	DBG_PRINT(("�˳�FillPrnInvHead����"));
    DBG_RETURN(SUCCESS);	
}

//---------------------------------------------------------------------------
//����ӡ��Ʊ�ṹ��ķ�Ʊ��ϸ
//---------------------------------------------------------------------------
UINT8 FillPrnInvDetail(TPrnInvoiceInfo *pPrnInvInfo, CInvHead *smallInvInfo)
{
	DBG_PRINT(("����FillPrnInvDetail����"));
	DBG_ENTER("FillPrnInvDetail");
	
	UINT32 detailCount;
	UINT8 j=0;
	UINT8 i;
	UINT8 k = 0; //���ŷ�Ʊ��ӡ����
	INT32 nLen;
	
	//���ŷ�Ʊ��ӡ����Ŀ
	detailCount = smallInvInfo->m_sphsl;
	DBG_PRINT(("���ŷ�Ʊ��ϸ���� == %u", detailCount));
	
	
	CInvDet *p = smallInvInfo->pHead;
	
    //��Ϊ������
	if (p == NULL)
	{
		DBG_PRINT((" smallInvInfo->pHead = NULL !"));
		DBG_RETURN(SUCCESS);		
	}
	
    //��Ϊ�ǿ�����
	for( i=0; i<detailCount; i++, p = p->pNext )
	{
		//�������ۿ��ʵ���Ʒ�зֳ���������
		pPrnInvInfo->GoodsLines[j].Type = p->m_property;							//��Ʒ������
	
		DBG_PRINT(("m_spsl= %f",p->m_spsl));
		p->m_dotNum = AmountRound(&(p->m_spsl));									//��Ʒ������������
         DBG_PRINT(("m_dotNum= %d",p->m_dotNum));

		pPrnInvInfo->GoodsLines[j].Amount = FormatAmount(p->m_dotNum, p->m_spsl);	//��Ʒ����
		DBG_PRINT(("��Ʒ����          : %u ", pPrnInvInfo->GoodsLines[j].Amount));

		pPrnInvInfo->GoodsLines[j].Price = double2int(p->m_spdj*PRICE_EXTENSION);	//��Ʒ����
		if( (p->m_property==DETAIL_DISCOUNT) || (p->m_property==DETAIL_REDUCTION_TEMPLATE) ) 
		{
			pPrnInvInfo->GoodsLines[j].Sum = 0 - p->m_spje;  //����Ʒ���ܽ��
		}
		else
		{
			pPrnInvInfo->GoodsLines[j].Sum = p->m_spje;		 //����Ʒ���ܽ��
		}
		pPrnInvInfo->GoodsLines[j].TaxSum = p->m_spse;	 //˰��
		pPrnInvInfo->GoodsLines[j].TaxItemIndex = p->m_sl;	 //˰��
		
		memcpy((void *)pPrnInvInfo->GoodsLines[j].chProductPLUCode, (void *)p->m_spbm.c_str(), p->m_spbm.length()); //��Ʒ����
		
		nLen = p->m_spmc.length() + 1;
		memcpy((void *)pPrnInvInfo->GoodsLines[j].chProductName, (void *)p->m_spmc.c_str(), nLen);				/**< ��Ʒ���� */
		
		DBG_PRINT(("-----------------------------"));
		DBG_PRINT(("��Ʒ������        : %u ", pPrnInvInfo->GoodsLines[j].Type));
		DBG_PRINT(("��Ʒ����          : %u ", pPrnInvInfo->GoodsLines[j].Amount));
		DBG_PRINT(("��Ʒ����С��λ��  : %d ", p->m_dotNum));
		DBG_PRINT(("��Ʒ����		  : %lld ", pPrnInvInfo->GoodsLines[j].Price));
		DBG_PRINT(("��Ʒ���ܽ��      : %lld ", pPrnInvInfo->GoodsLines[j].Sum));
		DBG_PRINT(("��Ʒ����˰��      : %lld ", pPrnInvInfo->GoodsLines[j].TaxSum));
		DBG_PRINT(("��Ʒ˰��          : %f ", pPrnInvInfo->GoodsLines[j].TaxItemIndex));
		DBG_PRINT(("��Ʒ����          : %s ", pPrnInvInfo->GoodsLines[j].chProductPLUCode));
		DBG_PRINT(("��Ʒ����          : %s ", pPrnInvInfo->GoodsLines[j].chProductName));
		
		j++;
		k++;
		
        //��Ʒ���Ƴ���
		if ((nLen-1) > g_globalArg->pSaveTemplateInfo->MaxSPMCCharacter)//xsr��ʱע������Ϊû��ģ�塣
			//	if ((nLen-1) > 10)
		{
			k++;
			DBG_PRINT(("��Ʒ���Ƴ���"));
			DBG_PRINT(("��Ʒ����� == %u", g_globalArg->pSaveTemplateInfo->MaxSPMCCharacter));
		}
	}
	
	//��ӡ��Ʒ����
	pPrnInvInfo->GoodsLineCount =  k;
	DBG_PRINT(("���ŷ�Ʊ��ӡ��Ʒ����Ŀ == %u��k == %u", pPrnInvInfo->GoodsLineCount,k));
	
	DBG_PRINT(("�˳�FillPrnInvDetail����"));
	DBG_RETURN(SUCCESS);
}


UINT8 FillPrnInvTail(TPrnInvoiceInfo *pPrnInvInfo, CInvHead *smallInvInfo)
{
	DBG_PRINT(("����FillPrnInvTail����"));
	DBG_ENTER("FillPrnInvTail");
	
	//��Ʊ��˰�ϼ� ��λ����
	pPrnInvInfo->InvSumLowcase = smallInvInfo->m_kphjje;
	DBG_PRINT(("��Ʊ��˰�ϼ� Сд == %lld", pPrnInvInfo->InvSumLowcase));
	
	//��Ʊ��˰�ϼ� ��λ����  ��д
	if (smallInvInfo->m_kphjje != 0)
	{
		ChineseAmount((INT64)smallInvInfo->m_kphjje, (INT8 *)pPrnInvInfo->chInvSumUppercase, 64);
		DBG_PRINT(("��Ʊ��˰�ϼ� ��д = %s", pPrnInvInfo->chInvSumUppercase));
	}
	else
	{
		sprintf(pPrnInvInfo->chInvSumUppercase, "��Բ��");
	}
	
	//��Ʊ�ϼ�˰�� ��λ����
	pPrnInvInfo->InvTaxLowcase = smallInvInfo->m_kpse;
	DBG_PRINT(("��Ʊ�ϼ�˰�� Сд == %lld", pPrnInvInfo->InvTaxLowcase));
	
	
	//��Ʊ�ϼƽ�� ��λ����
	pPrnInvInfo->InvMoneyLowcase = smallInvInfo->m_kphjje - smallInvInfo->m_kpse;
	DBG_PRINT(("��Ʊ�ϼƽ�� Сд == %lld", pPrnInvInfo->InvMoneyLowcase));
	
	//һά���� 20ASC
	memset(pPrnInvInfo->chYWTM, 0, sizeof(pPrnInvInfo->chYWTM));
	memcpy((void *)pPrnInvInfo->chYWTM, (void *)smallInvInfo->m_fwm.c_str(), smallInvInfo->m_fwm.length());
	DBG_PRINT(("һά����  : %s ", pPrnInvInfo->chYWTM));
	
	
	DBG_PRINT(("�˳�FillPrnInvTail����"));
	DBG_RETURN(SUCCESS);
}

UINT8 CheckIfFull(INT32 nInvHeadNum, INT32 nInvSumNum)
{
	CInvHead curInvHead;
// 	CInvSum curInvSum;
	
	INT32 errcode;
	
	//��Ҫ����
	if (nInvHeadNum>=INV_HEAD_MAX) 
	{
		curInvHead.Requery();
		errcode = curInvHead.LoadOneRecord();
		if (errcode==SQLITE_OK)
		{
			DBG_PRINT(("curInvHead.m_kprq = %u ", curInvHead.m_kprq));
			DBG_PRINT(("g_globalArg->m_startDecDate = %u ", g_globalArg->m_startDecDate));
			//��һ����¼����δ�걨��
			if( curInvHead.m_kprq >= g_globalArg->m_startDecDate ) 
			{
				DBG_PRINT(("INV_HEAD�������������걨! "));
				DBG_RETURN(SUCCESS);
			}
		}
	}
	
// 	if (nInvSumNum>=INV_SUM_MAX) 
// 	{
// 		curInvSum.Requery();
// 		errcode = curInvSum.LoadOneRecord();
// 		if (errcode==SQLITE_OK)
// 		{
// 			DBG_PRINT(("curInvSum.m_issueEndDate = %u ", curInvSum.m_issueEndDate));
// 			DBG_PRINT(("g_globalArg->m_startDecDate = %u ", g_globalArg->m_startDecDate));
// 			if (curInvSum.m_issueEndDate>=g_globalArg->m_startDecDate) 
// 			{
// 				DBG_PRINT(("INV_SUM�������������걨! "));
// 				DBG_RETURN(SUCCESS);
// 			}
// 		}
// 	}
	
	DBG_RETURN(FAILURE);
}


UINT8 ForwardPaper(void)
{
	DBG_ENTER("SaleData::ForwardPaper");
	if (isPaper() != 0)
	{
		DBG_RETURN(FAILURE);
	}
	
	if(g_globalArg->pSaveTemplateInfo->markFlag == 1)
	{
#if VOL_INV_PRN
		SeekBackBorderBlackMark();
#endif
		ForwardNPoint(g_globalArg->pSaveTemplateInfo->EndForwardPoint);	
		//	BackwardNPoint(g_globalArg->pSaveTemplateInfo->EndForwardPoint);
	}
	else
	{
		ForwardNPoint(5);
	}

	DBG_RETURN(SUCCESS);
}

UINT8 BackwardPaper(void)
{
	DBG_ENTER("SaleData::BackwardPaper");
	if (isPaper() != 0)
	{
		DBG_RETURN(FAILURE);
	}
	BackwardNPoint(10);

	DBG_RETURN(SUCCESS);
}

UINT8 NoMarkForwardPaper(void)
{
	DBG_ENTER("SaleData::NoMarkForwardPaper");
	if (isPaper() != 0)
	{
		DBG_RETURN(FAILURE);
	}
	
    ForwardNLine(2);
	
	DBG_RETURN(SUCCESS);
}

UINT8 MakeInvLog(UINT8 nInvType, UINT32 EventResult, string Backup)
{
	UINT8 Eventtype;
	
	switch(nInvType)
	{
	case NORMAL_INV:
		Eventtype = EVENT_MAKE_INVOICE;
		break;
	case RET_MANUAL_INV:
	case RETURN_INV:
	case RET_SPECIAL_INV:
		Eventtype = EVENT_MAKE_RET_INVOICE;
		break;
	case WASTE_INV:
	case WASTE_NOR:
	case WASTE_RET:
		Eventtype = EVENT_MAKE_WAS_INVOICE;
		break;
	default:;
	}
	
	if ((SUCCESS==EventResult)&&(EVENT_MAKE_INVOICE==Eventtype))
	{
		return SUCCESS;//����Ʊ�ɹ�������ϵͳ��־
	}
	CGlobalArg::SysLog(Eventtype , EventResult, Backup);//дϵͳ��־
	return SUCCESS;
}

UINT8 GetServNum(UINT32 &uNum,string &strErr)
{
	CInvServ curInvServ;
    uNum = curInvServ.GetRecordNum();
	DBG_PRINT(("�������� uNum= %u", uNum));
	
	if (uNum <0)
	{
		strErr="��ѯδ�ϴ���Ʊʧ�ܣ�";
		return FAILURE;
	}
	
	return SUCCESS;
	
}

#ifndef WIN32
void * NetCommunicate(void *arg)
{
// 	CSaleBusinessFunc saleFunc;
// 	CYWXML_GY ywXml_Gy;
// 	INT32 ret = SUCCESS;
// 	string strErr;
// 	UINT32 nTime = 10000;
// 	
// 	while(1)
// 	{
// 		if( (g_globalArg->m_pthreadFlag == 1) )
// 		{
// 		ywXml_Gy.m_nsrsbh = g_globalArg->m_pthreadNsrsbh;
// 		ywXml_Gy.m_sksbbh = g_globalArg->m_pthreadSksbbh;
// 		ywXml_Gy.m_sksbkl = g_globalArg->m_pthreadSksbkl;
// 		ywXml_Gy.m_fplxdm = g_globalArg->m_pthreadFplxdm;
// 		ywXml_Gy.m_jqbh = g_globalArg->m_pthreadJqbh;
// 		ywXml_Gy.m_kpjh = g_globalArg->m_pthreadKpjh;
//			ywXml_Gy.m_zskl = g_globalArg->m_pthreadZskl;
// 			ret = saleFunc.InvoiceUpload(ywXml_Gy, strErr);
// 			if (SUCCESS != ret)
// 			{
// 				DBG_PRINT(("strErr = %s", strErr.c_str()));
// 				g_globalArg->m_pthreadFlag = 0;
// 				g_globalArg->m_pthreadErr = strErr;
// 				CommonSleep(nTime);
// 			}
// 		}
// 		else
// 		{
// 			CommonSleep(nTime);
// 		}
// 	}
}

UINT8 UploadInvProc()
{
/*
DBG_PRINT(("UploadInvProc()"));
UINT32 nLIndex = 0;//����ʧ�ܼ���������
UINT32 nLmt = 3;
INT32 errorcode = 0;
UINT32 nTime = 10000;
INT8 chValue[128];
CInvServ invServ;
CInvHead curInv;
//	CInvcodeLink codeLink;	
string strErr = "";	
string strCode = "";
UINT8 nLinkFlag = 0;//������ͨ��־ 0����ͨ��1����ͨ
int ii=0;
UINT32 nMinute = 0;
int i;
CInvDet *p;
UINT8 ret, TransRet;
XmlFpsc FpscSend;
CNetTrans tmpTrans;
string strRet = "";

	DBG_PRINT(("thread in "));
	DBG_PRINT(("g_globalArg->m_netOn = %u",g_globalArg->m_netOn));
	DBG_PRINT(("m_initFlag = %u, m_threadIn = %u",g_globalArg->m_initFlag, g_globalArg->m_threadIn));
	DBG_PRINT(("m_InvServNum = %u",g_globalArg->m_InvServNum));
	while(1)
	{
	//		if ((g_globalArg->m_InvServNum>0)&&(0==g_globalArg->m_threadIn))
	//		{
	//			nMinute = TDateTime::CurrentDateTime().Minute();
	//			if ((30<= nMinute)&&(nMinute<=35)) //ʱ��ָ��30�ֵ�35��֮��ʱ
	//			{
	//				DBG_PRINT(("ʱ��ָ��30�ֵ�35��֮��ʱ "));
	//				g_globalArg->m_threadIn = 1;//�������ߣ������ٴ��ϴ�
	//			}
	//		}
	
	 //����ʼ�� ��¼�ɹ��ſ����ϴ���Ʊ
	 if ((1==g_globalArg->m_initFlag)&&(1==g_globalArg->m_threadIn))
	 {
	 //DBG_PRINT(("in "));
	 //��������
	 if (1 == nLinkFlag)//���粻ͨ,����ѭ�����
	 {
	 DBG_PRINT(("���粻ͨ,����ѭ����� begin "));
	 CommonSleep(10*nTime);
	 DBG_PRINT(("���粻ͨ,����ѭ����� end "));
	 //		continue;
	 }
	 
	  if (0 >= g_globalArg->m_InvServNum) //InvServ����������
	  {
	  //		DBG_PRINT(("InvServ���������� "));
	  CommonSleep(nTime);
	  continue;
	  }
	  
	   //һ��һ�Ŷ�ȡ�����ദ��
	   invServ.Requery();
	   errorcode = invServ.LoadOneRecord();
	   while (SQLITE_OK == errorcode)
	   {
	   DBG_PRINT(("InvServ����һ����¼ "));
	   //				if (0 == invServ.m_upFlag)//δ�ϴ�
	   //				{
	   DBG_PRINT(("��Ʊ�����ϴ�"));
	   //��CInvHead�в���÷�Ʊ
	   memset((void*)chValue, 0, sizeof(chValue));
	   sprintf(chValue, "where FPDM = '%s' and FPHM = %u ", invServ.m_code.c_str(), invServ.m_InvNo);
	   DBG_PRINT(("invServ.m_code = %s",invServ.m_code.c_str()));
	   DBG_PRINT(("invServ.m_InvNo = %d",invServ.m_InvNo));
	   curInv.m_filter = chValue;
	   errorcode = curInv.Load();
	   DBG_PRINT(("errorcode= %d",errorcode));
	   if (SQLITE_OK != errorcode) 
	   {
	   g_globalArg->m_strMsg = "�ϴ���Ʊ����ʧ��";
	   g_globalArg->m_ifMsg = 1;
	   break;				
	   }
	   
		//�ж�INV_SERV��INV_HEAD�еķ�Ʊ�����Ƿ�һ��
		
		 DBG_PRINT(("curInv.m_fphm = %d",curInv.m_fphm));
		 DBG_PRINT(("invServ.m_InvNo = %d",invServ.m_InvNo));
		 
		  // 				if(curInv.m_fphm == invServ.m_InvNo)
		  // 				{
		  // 					if(curInv.m_kplx != invServ.m_issuetype)
		  // 					{
		  // 				    	curInv.m_kplx=invServ.m_issuetype;
		  // 					DBG_PRINT(("curInv.m_kplx = %d",curInv.m_kplx));
		  // 			       	DBG_PRINT(("invServ.m_issuetype = %d",invServ.m_issuetype));
		  // 					}    	
		  // 				}
		  // 				DBG_PRINT(("curInv.m_kplx = %d",curInv.m_kplx));
		  // 			    DBG_PRINT(("invServ.m_issuetype = %d",invServ.m_issuetype));
		  DBG_PRINT(("��ʼ�ϴ���Ʊ "));
		  string resCode("");
		  FpscSend.m_invHead = &curInv;
		  
		   FpscSend.XmlFpscRequest( strErr);
		   
			tmpTrans.NetTransMutexLock();
			g_globalArg->m_sendInvFlag = 1;
			TransRet = tmpTrans.TransToSever(NULL, strErr);	//22��������Ϣ����
			g_globalArg->m_sendInvFlag = 0;
			tmpTrans.NetTransMutexUnlock();
			if (TransRet != SUCCESS)//���罻��ʧ��
			{
			DBG_PRINT(("strErr = %s", strErr.c_str()));
			g_globalArg->m_strMsg = strErr;
			g_globalArg->m_ifMsg = 1;
			nLIndex++;
			if (nLIndex >= nLmt) 
			{
			nLinkFlag = 1;
			nLIndex=0;
			g_globalArg->m_threadIn =0;//��������״̬�������������������ϴ�
			break;
			}
			break;						
			}
			
			 DBG_PRINT(("ret = %d", ret));
			 errorcode = FpscSend.XmlFpscRespond( DEF_RSP_FILE, strRet, strErr);
			 
			  DBG_PRINT(("strRet = %s", strRet.c_str()));
			  
			   if (strRet != "Y")
			   {
			   DBG_PRINT(("strErr = %s", strErr.c_str()));
			   g_globalArg->m_strMsg = strErr;
			   g_globalArg->m_ifMsg = 1;
			   nLIndex++;
			   if (nLIndex >= nLmt) 
			   {
			   nLinkFlag = 1;
			   nLIndex=0;
			   g_globalArg->m_threadIn =0;//��������״̬�������������������ϴ�
			   break;
			   }
			   break;			
			   }
			   else
			   {
			   
				DBG_PRINT(("*****�����ϴ��ɹ�***** "));
				POWOFF_DISABLE(); //���ε����ж�
				
				 //�ϴ��ɹ�
				 //ɾ��InvServ������¼
				 nLIndex = 0;
				 nLinkFlag = 0;
				 sprintf(chValue, "where NO = %u", invServ.m_no);
				 invServ.m_filter = chValue;
				 invServ.Delete();
				 
				  //������������
				  if(0 != g_globalArg->m_InvServNum)
				  {
				  g_globalArg->m_InvServNum--;
				  }
				  //					if ((NORMAL_INV == curInv.m_kplx)||(RETURN_INV ==curInv.m_kplx ))//��Ʊ
				  if ((NORMAL_INV == curInv.m_kplx ))//��Ʊ
				  {
				  g_globalArg->m_InvServSum -= invServ.m_moneySum;//���������
				  }
				  POWOFF_ENABLE();  //�������ж�
				  DBG_PRINT(("ɾ���ɹ�  g_globalArg->m_InvServNum =%u", g_globalArg->m_InvServNum));
				  
				   //ȡInvServ����һ����¼
				   sprintf(chValue, "where NO > %u limit 1", invServ.m_no);
				   invServ.m_filter = chValue;
				   invServ.Requery();
				   errorcode = invServ.LoadOneRecord();
				   }
				   }										
				   CommonSleep(nTime);
				   }
				   CommonSleep(1000);
				   }
*/
}
#endif