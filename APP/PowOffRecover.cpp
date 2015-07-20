/****************************************************************************
�ļ���           ��PowOffRecover.cpp
����             ��awe4000r�����е�Ӧ�ú�����
��ʼ����         ��2008-01-31
����             ��Yu Yan     
****************************************************************************/

#include "PowOffRecover.h"

#include "CaMsgBox.h"
#include "CaProgressBar.h"
//#include "CSystemInit.h"
//#include "CDeclareProc.h"
//#include "VolSumInfoWin.h"
#include "VersionConfig.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

UINT8 InvStuctToClass(struct TInvFullInfo *invFullInfo, CInvHead *smallInvInfo)
{
	DBG_ENTER("InvStuctToClass");

	DBG_ASSERT_EXIT((invFullInfo != NULL)&&(smallInvInfo != NULL), (" invFullInfo == NULL or smallInvInfo = NULL "));
		
//-----ת����Ʊ������Ϣ 
	
	/*��Ʊ��������� */
	smallInvInfo->m_codeNo = invFullInfo->head.TypeCodeNo;
	DBG_PRINT(("��Ʊ��������� : %u ", smallInvInfo->m_codeNo));

	/*��Ʊ����                      */
	smallInvInfo->m_InvNo = invFullInfo->head.InvNo; 
	DBG_PRINT(("��Ʊ����  : %u ", smallInvInfo->m_InvNo));

	/*��Ʊ����                      */
	smallInvInfo->m_issuetype = invFullInfo->head.Type;
	DBG_PRINT(("��Ʊ���� : %u ", smallInvInfo->m_issuetype));

	/*��Ʊ���� CCYYMMDD             */
	smallInvInfo->m_issueDate = invFullInfo->head.Date;
	DBG_PRINT(("��Ʊ����  : %u ", smallInvInfo->m_issueDate));

	smallInvInfo->m_issueTime = invFullInfo->head.Time;
    DBG_PRINT(("��Ʊʱ��  : %u ", smallInvInfo->m_issueTime));

	/*ԭ��Ʊ����                    */
	smallInvInfo->m_oldInv = invFullInfo->head.PosInvNo;
	DBG_PRINT(("ԭ��Ʊ����  : %u ", smallInvInfo->m_oldInv));

	/*������ 40 ASC                 */
	smallInvInfo->m_payer = (INT8*)(invFullInfo->head.ClientName);
	DBG_PRINT(("������ : %s ", smallInvInfo->m_payer.c_str()));
	
	/*��ƱԱ������10 ASC       */
	smallInvInfo->m_operator = (INT8*)(invFullInfo->head.OperatorName);
    DBG_PRINT(("��ƱԱ���� : %s ", smallInvInfo->m_operator.c_str()));

	/*��ƱԱID      */
	smallInvInfo->m_opId = invFullInfo->head.OpId;
    DBG_PRINT(("��ƱԱID : %u ", smallInvInfo->m_opId));

	/**<��Ʒ�и���        	*/ 
	smallInvInfo->m_goodsCount = invFullInfo->head.detailCount;
	DBG_PRINT(("��Ʒ�и��� = %u", smallInvInfo->m_goodsCount));

	/**<��Ʊ�ܽ�� ��λ����  */
	smallInvInfo->m_moneySum = invFullInfo->head.TotalSum;
	DBG_PRINT(("��Ʊ�ܽ�� Сд = %d", smallInvInfo->m_moneySum));

	/**<˰���� HEX            */
	memcpy((void *)smallInvInfo->m_fCode, (void *)invFullInfo->head.TaxCtrCode, INV_TAX_CTRL_CODE_LEN);
    DBG_PRINT(("˰����Hex : %s ", smallInvInfo->m_fCode));

	/**<���ʽ  */    
	smallInvInfo->m_payType = invFullInfo->head.PayMode;
	DBG_PRINT(("���ʽ  : %u ", smallInvInfo->m_payType));

//-----ת����Ʊ��ϸ��Ϣ

	CInvDet *p;
    //��Ϊ�ǿ�����
	for(UINT8 i=0; i<invFullInfo->head.detailCount; i++)
	{
//		p = new CInvDet;
		p = p->GetNewInvDet();//�Ӿ�̬�����ȡһ�����õ�CInvDet����
		DBG_ASSERT_EXIT((p != NULL), (" p == NULL"));

		p->m_property = invFullInfo->detail[i].Property;    /**< ��Ʒ������ */
		p->m_quantity = invFullInfo->detail[i].Amount;  /**< ��Ʒ���� */		   
		p->m_price = invFullInfo->detail[i].Price;	    /**< ��Ʒ���� */		
		p->m_moneySum = invFullInfo->detail[i].Sum;		/**< �ܽ�� */
		p->m_taxId = invFullInfo->detail[i].TaxItem;	/**< ˰Ŀ */
		p->m_code = (INT8*)(invFullInfo->detail[i].GoodsCode); /**< ��Ʒ���루PLU���룩 */
		p->m_name = (INT8*)(invFullInfo->detail[i].GoodsName); /**< ��Ʒ���� */
		
		p->m_opId = smallInvInfo->m_opId;
		p->m_codeNo = smallInvInfo->m_codeNo;
		p->m_InvNo = smallInvInfo->m_InvNo;
		p->m_issueDate = smallInvInfo->m_issueDate;
		p->m_issueTime = smallInvInfo->m_issueTime;
		p->m_issuetype = smallInvInfo->m_issuetype;
		DBG_PRINT(("��Ʒ������: %u ", p->m_property));
		DBG_PRINT(("��Ʒ����  : %f ", p->m_quantity));
		DBG_PRINT(("��Ʒ����  : %f ", p->m_price));
		DBG_PRINT(("��Ʒ���ܽ��  : %d ", p->m_moneySum));
		DBG_PRINT(("��Ʒ˰Ŀ  : %u ", p->m_taxId));
		DBG_PRINT(("��ƷPLU�� : %s ", p->m_code.c_str()));
		DBG_PRINT(("��Ʒ����  : %s ", p->m_name.c_str()));

		smallInvInfo->InsertNode(p);	//����ڵ�
	}
	DBG_RETURN(SUCCESS);
}


UINT8 InvSumPrn(void)
{
	UINT8 ret = SUCCESS;
	UINT32 nCodeNo = g_globalArg->m_curInvVol->m_codeNo;
	UINT32 nStartInvNo = g_globalArg->m_curInvVol->m_InvStartNo;
	UINT32 nEndInvNo = g_globalArg->m_curInvVol->m_InvEndNo;
	INT8 chValue[256];
	memset((void *)chValue, 0, sizeof(chValue));	
	sprintf(chValue,"where CODE_NO = %u and IS_NO = %u and IE_NO = %u",nCodeNo, nStartInvNo, nEndInvNo);

	CInvSum invSum;
	invSum.m_filter = chValue;
	invSum.Requery();
	invSum.LoadOneRecord();

    //�����⸳ֵ
//	sprintf(title_arr[0], "��ֹ����:%u--%u ", invSum.m_InvStartNo, invSum.m_InvEndNo);
//	sprintf(title_arr[1], "��Ʊ��:%u ��Ʊ��:%u ��Ʊ��:%u",invSum.m_normalInvSum, invSum.m_returnInvSum, invSum.m_wasteInvSum);
//	sprintf(title_arr[2], "��Ʊ���:%.2lf", (double)(invSum.m_nomalMoneySum)/100.0);
//	sprintf(title_arr[3], "��Ʊ���:%.2lf", (double)(invSum.m_returnMoneySum)/100.0);
//	sprintf(title_arr[4], "");
//	sprintf(title_arr[5], "");
//
//	ChangeTitle();
//	ReFresh();

//#ifndef WIN32
//	usleep(3000000);
//#endif
//	if (isPaper() != 0)
//	{	
//		CaMsgBox::ShowMsg("��ӡ��δ��⵽ֽ");
//	}
	CaProgressBar proBar("������ܴ�ӡ��.....");
	proBar.ReFresh();

	struct TVolSumPrnData volSumPrnData;
	ret = CVolSumInfoWin::PrnVolSumInfo(&volSumPrnData, &invSum);	

	DBG_PRINT(("InvSumPrn();��ʾ����ܲ���ӡ"));
#ifndef WIN32
	CommonSleep(9000);
#endif
	
	return ret;
}

UINT8 MakeInvRecover(struct TInvFullInfo *invFullInfo, UINT8 nChildId)
{
	DBG_ENTER("InvStuctToClass");
	DBG_ASSERT_EXIT((invFullInfo != NULL), (" invFullInfo == NULL "));
	DBG_PRINT(("begin MakeInvRecover"));
	
	UINT8 nIfPrn = 1;
	UINT8 ret;
	
	DBG_PRINT(("new SaleData"));
	if(pSaleData == NULL)
	{
		DBG_PRINT(("new SaleData"));
		pSaleData = new SaleData;
	}	
	DBG_ASSERT_EXIT((pSaleData != NULL), (" pSaleData == NULL "));
	CInvHead smallInvHead;
	pSaleData->m_smallInvInfo = &smallInvHead; //�洢��Ʊ����
	DBG_ASSERT_EXIT((pSaleData->m_smallInvInfo != NULL), (" pSaleData->m_smallInvInfo == NULL "));

	DBG_PRINT(("begin InvStuctToClass"));
	InvStuctToClass(invFullInfo, pSaleData->m_smallInvInfo);
	if (pSaleData->m_smallInvInfo->m_issuetype==WASTE_INV)
	{
		nIfPrn = 0;
	}

	DBG_PRINT(("begin MakeInvoiceHandle"));
	//���ÿ�Ʊ���
	ret = pSaleData->MakeInvoiceHandle(nIfPrn, nChildId);

	//----������ر�����λ
    pSaleData->m_tmpGoodsNum = 0;  //��ǰ����Ʒ��������
	pSaleData->InitSaleData(1);	//������Ϣ��ʼ��
	pSaleData->InitInvHead();		//���ŷ�Ʊ��Ϣ��ʼ��
	pSaleData->m_workState = WORK_COMPLETE;
	pSaleData->m_smallInvInfo = NULL;
	
	//�ж��Ƿ���о����
	if(g_globalArg->m_curInvVol->m_remain == 0)
	{
		UINT8 nIfSum = 0;
		POWOFF_DISABLE(); //���ε����ж�
		if(!pSaleData->InvSum(nIfSum))
		{
			delete pSaleData;
			pSaleData = NULL;
			DBG_PRINT(("Get volume Sum error !"));
			POWOFF_ENABLE(); //�������ж�
			DBG_RETURN(FAILURE);
		}
		POWOFF_ENABLE(); //�������ж�
		if (1==nIfSum) 
		{
			InvSumPrn();//��ʾ����ܲ���ӡ
		}
	}
    
//	if (pSaleData != NULL) 
//	{
//		DBG_PRINT(("delete pSaleData"));
//		delete pSaleData;
//		pSaleData = NULL;
//	}

	if (ret != SUCCESS)
	{
		CGlobalArg::SysLog(EVENT_POWEROFF_INV, FAILURE);//дϵͳ��־
		DBG_RETURN(FAILURE);
	}	

	DBG_PRINT(("end MakeInvRecover"));
	CGlobalArg::SysLog(EVENT_POWEROFF_INV, SUCCESS);//дϵͳ��־
	DBG_RETURN(SUCCESS);
}

UINT8 RollRecover(void)
{
	DBG_PRINT((" ****��������ָ�����ʼ***** "));
//	POWOFF_DISABLE(); //���ε����ж�
	POWOFF_ENABLE();//�������ж�
	SetPowerOffFlag();
	SetPowerOffProcID_M(INV_ROLL_PROC);//��������ID
	
	CInvHead curInvHead;
	CRtInv curRtInv;
	CInvSum curInvSum;

	UINT32 nInvDelDate = g_YW_PowerOffData->invRollPwOffData.invDatelimit;/**<InvHead�����ɾ���Ľ�ֹ����  */ 
	UINT32 nSumDelDate = g_YW_PowerOffData->invRollPwOffData.sumDatelimit;/**<InvSum�����ɾ���Ľ�ֹ����  */  
	UINT32 nRtDetNo = g_YW_PowerOffData->invRollPwOffData.rtNolimit;/**<RtInv�����ɾ���Ľ�ֹ����  */  
	UINT32 nRefDate = g_YW_PowerOffData->invRollPwOffData.nRefDate; /**<�ϴ��걨�Ľ�ֹ����  */ 
	//����
	curInvHead.Roll(nInvDelDate, nRefDate);
	curInvSum.Roll(nSumDelDate);
	curRtInv.Roll(nRtDetNo);

	CleanPowerOffFlag();
//	POWOFF_ENABLE();

	DBG_PRINT(("end RollRecover"));
	CGlobalArg::SysLog(EVENT_POWEROFF_ROLL, SUCCESS);//дϵͳ��־
	DBG_RETURN(SUCCESS);
}


UINT8 poweroff_recover()
{
	UINT8 fatherID;
	UINT8 childID;
	UINT8 ret = SUCCESS;
	/*�ڴ��˷� �޸� XPK*/
	CSystemInit systemInit;
//	CInvoiceDistribute invDistribute;
//	CUpdateTaxData updateTax;
	CDeclareProc declareProc;

	DBG_PRINT(("begin to poweroff data recover"));
	
	GetPowerOffProcID_M(fatherID);
	GetPowerOffProcID_C(childID);

	DBG_PRINT(("fatherID: %u", fatherID));
	DBG_PRINT(("childID: %u", childID));
	
	
	if(g_YW_PowerOffData == NULL )
	{
		DBG_PRINT(("g_PowerOffData no Init!"));
		return SUCCESS;
	}
	
	if( GetPowerOffFlag() != 1 )
	{
        DBG_PRINT(("power off flag is 0 !"));
		return FAILURE;
	}
	

	DBG_PRINT(("g_YW_PowerOffData->main_proc_id = %u", g_YW_PowerOffData->main_proc_id ));
	
	if ((g_globalArg->m_initFlag == 0) && (g_YW_PowerOffData->main_proc_id != INIT_PROC))
	{
		return SUCCESS;
	}
	
	CaProgressBar proBar("����ָ���.....");
    string strError;

	switch(g_YW_PowerOffData->main_proc_id)
	{
	case INIT_PROC:  //��ʼ������
		proBar.SetText("����ָ�����ʼ��...");
		proBar.ReFresh();
		ret = systemInit.InitPowerOffRecover(childID);
		break;
		
	case FPFF_PROC:  //��Ʊ�ַ�����
//		proBar.SetText("����ָ�����Ʊ�ַ�...");
//		proBar.ReFresh();
//		ret = invDistribute.InvPowerOffRecover(childID);
		break;
		
	case FPDR_PROC:  //��Ʊ�������
		break;
		
	case FPTK_NORMAL_PROC:  //��Ʊ�����
		proBar.SetText("����ָ�����Ʊ�...");
		proBar.ReFresh();
		ret = MakeInvRecover(&(g_YW_PowerOffData->ProcData.fptk_data.posInvInfo), childID);
		break;
		
	case FPTK_RETURN_PROC:  //��Ʊ�����
		break;
		
	case FPTK_WASTE_PROC:  //��Ʊ�����
		break;
		
	case SB_PROC:    //�걨����
		proBar.SetText("����ָ����걨����...");
		proBar.ReFresh();
		ret = declareProc.DecPowerOffRecover(childID);		
		break;
		
	case WS_PROC:    //��˰����
//		proBar.SetText("����ָ�����˰����...");
//		proBar.ReFresh();
//		ret = updateTax.UpdateTaxPowerOffRecover(childID);
		break;

	case INV_ROLL_PROC:    //��������
		proBar.SetText("����ָ������ݿ����...");
		proBar.ReFresh();
		ret = RollRecover();
		break;
		
	default:
		return 5;
	}
	
	if (ret == SUCCESS) 
	{
		DBG_PRINT(("����ָ��ɹ���"));
		ShowMsg("����ָ��ɹ���");
	}
	else
	{
		DBG_PRINT(("����ָ�ʧ�ܣ�"));
		ShowMsg("����ָ�ʧ�ܣ�");
	}

	return SUCCESS;	
}

void ShowMsg(string strInfo)
{
	CaMsgBox msgBox(strInfo.c_str(),CaMsgBox::MB_OK);
	msgBox.ShowBox();
	if (msgBox.m_iStatus == OK_PRESSED)
	{
//		ReFresh();
	}

}



