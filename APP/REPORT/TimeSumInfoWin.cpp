/*! \file    TimeSumInfoWin.cpp
\brief    awe4000r�����ӡ��ʱ��λ��ܽ���
\author   Yu Yan
\version  1.0
\date     2008-02-14
*/


#include "TimeSumInfoWin.h"

#include "TDateTime.h"
#include "ReportFunc.h"
#include "CGlobalArg.h"
#include "CInvHead.h"
#include "CInvDet.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CTimeSumInfoWin::CTimeSumInfoWin():CaWindow()
{
	m_StartDate = 0;
	m_EndDate = 0;
	m_StartTime = 0;		
	m_EndTime = 0;	
	m_create = 0;
	
	m_pSegSumPrnData = &m_segSumPrnData;
}

CTimeSumInfoWin::~CTimeSumInfoWin()
{
	
}


int CTimeSumInfoWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;
	m_create = 1;
	
    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
	
	m_pFrame->RegsiterWin(this,TIME_SUM_INFO_WIN);
	
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	
	m_pDateWin = (CTimeSumDateWin*)m_pFrame->GetWin(TIME_SUM_DATE_WIN);
	
	//����һ����ǩ  ��һ��	
	label[0] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH = SCREEN_TOP_OFFSET;
	//	curH += LINE_H;
	label[0]->Create(0,curH, SCREEN_W, CHAR_H); //����������
	label[0]->SetTitle(title_array[0], strlen(title_array[0]));
	
	//����һ����ǩ  �ڶ���
	label[1] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[1]->Create(0,curH, SCREEN_W, CHAR_H); //����������
	label[1]->SetTitle(title_array[1], strlen(title_array[1]));
	
	//����һ����ǩ  ������
	label[2] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[2]->Create(0,curH, SCREEN_W, CHAR_H);
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));
	
	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
	m_iColW = (SCREEN_W - 40)/2; //Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	
	//����һ��Button  ������
	strcpy(title, "��ӡ");
	m_pBtn1 = new CaButton();
	curH += LINE_H;
	curH += LINE_H;
	m_pBtn1->Create(leftoffset_btn,curH,m_iBtnW,WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;
	
	
	//����һ��Button  ������
	strcpy(title, "����");
	m_pBtn2 = new CaButton();
	m_pBtn2->Create(leftoffset_btn + m_iColW,curH,m_iBtnW,WORD_H); 
	m_pBtn2->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn2->SetTitle(title, strlen(title));
	m_pBtn2->BoxType(CaObject::BOX_NO);
	m_pBtn2->OnObject = S_OnButton2;
	
	OnActive = S_OnActive;
	
	this->End();  
	return 0;
}

int CTimeSumInfoWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	UINT32 ii;
	char *content;
	
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
		ChangeWin(FISCAL_REPORT_MENU);	 			
		return SUCCESS;
		break;
		
		//	case PAGEUP_KEY:
		//		 DBG_PRINT(("PAGEUP_KEY"));
		//		 if ((m_pageIndex-1)<1)
		//		 {
		//			 return FAILURE;
		//		 }
		//		  m_workState = 0;
		//		 m_pageIndex--;
		//		 QueryShow(m_pDaySum, m_pDaySum->m_issueDate, m_pageIndex, m_pageNum, 1);
		//		 ChangeTitle();
		//	     ReFresh();	
		//		 DBG_PRINT(("PAGEUP_KEY"));
		//		 m_workState = 1;
		//		 return SUCCESS;
		//		 break;
		//
		//	case PAGEDOWN_KEY:
		//		 if ((m_pageIndex+1)>m_pageNum)
		//		 {
		//			 return FAILURE;
		//		 }
		//		 m_workState = 0;
		//		 m_pageIndex++;
		//		 QueryShow(m_pDaySum, m_pDaySum->m_issueDate, m_pageIndex, m_pageNum, 0);
		//		 ChangeTitle();
		//	     ReFresh();	
		//		 m_workState = 1;
		//		 return SUCCESS;
		//		 break;
		
	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CTimeSumInfoWin::ReFresh()
{
	ReFreshTitle();
	CaGroup::ReFresh();
	if(m_pCurObj != NULL )
	{
		m_pCurObj->SetFocusIn();
	}
	LCDRedraw();
	
	return 1;
}

void CTimeSumInfoWin::S_OnActive(CaWindow *obj)
{
	((CTimeSumInfoWin *)obj)->DoActive();
}


void CTimeSumInfoWin::DoActive()
{
	DBG_PRINT((" CTimeSumInfoWin::DoActive()!"));
	
	if(m_create == 1)
	{
		m_create = 0;
		return;
	}
	
	m_pDateWin = (CTimeSumDateWin*)m_pFrame->GetWin(TIME_SUM_DATE_WIN);
	m_StartDate = m_pDateWin->m_StartDate;
    m_EndDate = m_pDateWin->m_EndDate;
	m_StartTime = m_pDateWin->m_StartTime;
	m_EndTime = m_pDateWin->m_EndTime;
	DBG_PRINT((" m_StartDate = %u!", m_StartDate));
	DBG_PRINT((" m_EndDate = %u!", m_EndDate));
	DBG_PRINT((" m_StartTime = %u!", m_StartTime));
	DBG_PRINT((" m_EndTime = %u!", m_EndTime));
	
	QueryShow(m_pSegSumPrnData);//��֯��Ļ��ʾ��Ϣ
	ChangeTitle();
	ReFresh();
	
}

UINT8 CTimeSumInfoWin::ChangeTitle()
{
	label[0]->SetTitle(title_array[0], strlen(title_array[0]));
	label[1]->SetTitle(title_array[1], strlen(title_array[1]));
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));
	
	return SUCCESS;
}


UINT8 CTimeSumInfoWin::QueryShow(struct TDateSegSumPrnData *pSegSumPrnData)
{
	
	DBG_ASSERT_EXIT((pSegSumPrnData != NULL), (" pSegSumPrnData == NULL!"));
	
    DBG_PRINT(("DaySaleSumHandle()"));
	
	INT32 ninvCount=0;
	INT64 SumMoney = 0;//ĳ�յ������۽��
	INT64 norMoney = 0;//ĳ������Ʊ���
	INT64 retMoney = 0;//ĳ������Ʊ���
	
	INT64 allSumMoney = 0;//��ʱ�ε������۽��
	INT64 allnorMoney = 0;//��ʱ�ε���Ʊ�����۽��
	INT64 allretMoney = 0;//��ʱ�εĺ�Ʊ�����۽��
	
	//ʱ��λ��ܽṹ�岿�ָ�ֵ
	memset((void *)pSegSumPrnData, 0x00, sizeof(struct TDateSegSumPrnData));
	
	memcpy((void *)pSegSumPrnData->CorpName, 
		(void *)g_globalArg->m_corpInfo->m_Nsrmc.c_str(), CORP_NAME_LEN);
	memcpy((void *)pSegSumPrnData->MachineCode,
		(void *)g_globalArg->m_machine->m_machineNo.c_str(), MACHINE_NO_LEN);
	memcpy((void *)pSegSumPrnData->TaxCode,
		(void *)g_globalArg->m_corpInfo->m_Nsrsbh.c_str(), CORP_SBH_LEN);
	
	pSegSumPrnData->StartDate	= m_StartDate;
	pSegSumPrnData->EndDate	= m_EndDate;
	
	INT32 allInvCount = 0;//��ʱ�εĿ�Ʊ����
	
	UINT32 nInvNum =0;
	UINT32 rInvNum =0;
	UINT32 wInvNum=0; 
	
	UINT32 nallInvNum=0;
	UINT32 rallInvNum =0;
	UINT32 wallInvNum=0;//��ʱ�εĲ�ͬ���Ϳ�Ʊ����
	
	
	string strTimeFilter = "";
	string strTimeFilter2 = "";
	string strDayFilter = "";
	INT8 chDayValue[128];
	memset((void*)chDayValue, 0, sizeof(chDayValue));
	INT8 chTimeValue[128];
	memset((void*)chTimeValue, 0, sizeof(chTimeValue));
	
	UINT8 i = 0;
	CInvHead invHead;
	
	
	
	DBG_PRINT(("*******��ʼͳ��*******************"));
	
	//��ӡ
	UINT32 nDate = m_StartDate;
	
	TDateTime sDate(nDate, 0);
	sprintf(chTimeValue, " and KPSJ >= %u ",m_StartTime);
	strTimeFilter = chTimeValue; //��ʼ��
	sprintf(chTimeValue, " and KPSJ <= %u",m_EndTime);
	strTimeFilter2 = chTimeValue; //��ֹ��
	
	DBG_PRINT(("m_StartDate= %u",m_StartDate));
	DBG_PRINT(("m_EndDate= %u",m_EndDate));
	
	pSegSumPrnData->StartDate	= m_StartDate;
	pSegSumPrnData->EndDate	= m_EndDate;
	
	while (1)
	{
		ninvCount = 0; //ĳ����Ա�Ŀ�Ʊ��������
		nInvNum = 0; 
		rInvNum = 0; 
		wInvNum = 0;
		
		SumMoney = 0; //ĳ����Ա�������ܽ������
        norMoney = 0;
		retMoney = 0;
		
		DBG_PRINT(("*******һ��*******************"));
		sprintf(chDayValue, "where KPRQ = %u ",nDate);
		strDayFilter = chDayValue;
		
		if (m_StartDate==nDate) 
		{
			strDayFilter += strTimeFilter;			
		}
		
		if (m_EndDate == nDate) 
		{
			strDayFilter += strTimeFilter2;
		}
		
		
		//�ۼƷ�Ʊ��
		invHead.m_filter = strDayFilter;//ʱ������
		DBG_PRINT(("invHead.m_filter = %s", invHead.m_filter.c_str()));
		
		DBG_PRINT(("ninvCount = %u",ninvCount));
		ninvCount = invHead.GetInvNumByDate();
		DBG_PRINT(("ninvCount = %u",ninvCount));
		
		if (ninvCount<0)
		{
			CaMsgBox::ShowMsg("ͳ�Ʒ�Ʊ����ʧ��");
			DBG_PRINT(("ͳ�Ʒ�Ʊ����ʧ��"));
			return FAILURE;
		}
		
		DBG_PRINT(("invHead.m_filter = %s", invHead.m_filter.c_str()));
		invHead.m_filter = strDayFilter;//ʱ������
		DBG_PRINT(("invHead.m_filter = %s", invHead.m_filter.c_str()));
		
		invHead.GetInvoiceSum(nInvNum, rInvNum, wInvNum); //��ʼ�յ������ˡ��Ϸ�Ʊ���� 
		DBG_PRINT(("nInvNum = %u, rInvNum = %u, wInvNum = %u",nInvNum, rInvNum, wInvNum));
		
		allInvCount += ninvCount;//��ʱ���ܵĿ�Ʊ����
		nallInvNum +=nInvNum;   //��ʱ���ܵ���Ʊ����
		rallInvNum +=rInvNum;   //��ʱ���ܵĺ�Ʊ����
		wallInvNum +=wInvNum;   //��ʱ���ܵķ�Ʊ����
		
		DBG_PRINT(("allInvCount = %d",allInvCount));
		DBG_PRINT(("nallInvNum = %u",nallInvNum));
		DBG_PRINT(("rallInvNum = %u",rallInvNum))
			DBG_PRINT(("wallInvNum = %u",wallInvNum));
		
		//PrnDate(&(sDate.FormatString(YYYYMMDD)));//��ӡ����				
		
		//���������ͳ��
		if(PrnTimeDeptMoney(SumMoney,norMoney,retMoney, &strDayFilter)!=SUCCESS)
		{
			return FAILURE;
		}
		DBG_PRINT(("SumMoney = %d",SumMoney));
		DBG_PRINT(("norMoney = %d",norMoney));
		DBG_PRINT(("retMoney = %d",retMoney));
		
		//PrnDaySaleSum(ninvCount, SumMoney); //��ӡ�����ۼ������ͽ��	
		
		allSumMoney += SumMoney;//����ʱ��ε��ۼƽ��
		allnorMoney += norMoney;
		allretMoney += retMoney;
		
		(sDate)++;	//��һ��
		nDate = sDate.FormatInt(YYYYMMDD);
		DBG_PRINT(("nDate= %u",nDate));
		DBG_PRINT(("m_EndDate= %u",m_EndDate));
		
		if(nDate>m_EndDate)
		{
			break;
		}
		
	}
	
	pSegSumPrnData->PosInvCount  =nallInvNum;
    pSegSumPrnData->ReInvCount = rallInvNum;
    pSegSumPrnData->WasteInvCount = wallInvNum;
	
    pSegSumPrnData->PosInvSum= allnorMoney;
	pSegSumPrnData->ReInvSum = allretMoney;
	
    //�����⸳ֵ
	sprintf(title_array[0], "ͳ������: %u--%u ", m_StartDate, m_EndDate);
	sprintf(title_array[1], "��Ʊ��: %u ��Ʊ����%u ��Ʊ����%u",pSegSumPrnData->PosInvCount, pSegSumPrnData->ReInvCount, pSegSumPrnData->WasteInvCount);
	sprintf(title_array[2], "��/��Ʊ���: %.2lf/%.2lf ", (double)(pSegSumPrnData->PosInvSum)/100.0, (double)(pSegSumPrnData->ReInvSum)/100.0);
	DBG_PRINT(("title_array[2] = %s!", title_array[2]));	
	
	return SUCCESS;
}

void CTimeSumInfoWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CTimeSumInfoWin *win=(CTimeSumInfoWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
} 


void CTimeSumInfoWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CTimeSumInfoWin *win=(CTimeSumInfoWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CTimeSumInfoWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 ret = PrnTimeSumInfo(m_pSegSumPrnData);
	if (ret == SUCCESS)
	{
		ChangeWin(FISCAL_REPORT_MENU);	 //���ط�Ʊ�������	
	}
}


void CTimeSumInfoWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	
	ChangeWin(FISCAL_REPORT_MENU);	 //���ط�Ʊ�������		
	
}


UINT8 CTimeSumInfoWin::PrnTimeSumInfo(struct TDateSegSumPrnData *pSegSumPrnData)
{
	DBG_ASSERT_EXIT((pSegSumPrnData != NULL), (" pSegSumPrnData == NULL!"));
	UINT8 ret;
	if (isPaper() != 0)
	{	
		CaMsgBox::ShowMsg("��ӡ��δ��⵽ֽ");
		this->ReFresh();
		return FAILURE;
	}
	ret = YesNoMsgBox("������ֽ���Ƿ��ӡ��");
	if (ret==FAILURE)
	{
		return FAILURE;
	}
	
	if(print_dateseginvsuminfo(pSegSumPrnData, 1, m_StartTime, m_EndTime) != 0)
	{
		//prn_log("error ocured while printing");
		CaMsgBox::ShowMsg("��ӡʱ��λ�����Ϣʧ��");
		return FAILURE;		
	}
	return SUCCESS;
}





