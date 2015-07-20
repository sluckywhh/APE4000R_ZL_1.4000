/*! \file    MonthSaleShowWin.CPP
   \brief    awe4000r������ͳ����ʾ����
   \author   Yu Yan
   \version  1.0
   \date     2015-06-15
 */

#include "MonthSaleShowWin.h"
#include "MonthSaleSumWin.h"
#include "CaProgressBar.h"
#include "CaMsgBox.h"
#include "ReportFunc.h"
#include "CInvHead.h"
#include "PrintDriver.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CMonthSaleShowWIn::CMonthSaleShowWIn():CaWindow()
{
	m_pageIndex = 1;
	m_pageNum = 2;

	m_ptrTjxxhz = new CTjxxhz;
	DBG_ASSERT_EXIT((m_ptrTjxxhz != NULL), (" m_ptrTjxxhz == NULL!"));	
}

CMonthSaleShowWIn::~CMonthSaleShowWIn()
{
	if(m_ptrTjxxhz != NULL)
	{
		delete m_ptrTjxxhz;
	    m_ptrTjxxhz = NULL;
	}	
}

int CMonthSaleShowWIn::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;
	

    m_iBtnW = (SCREEN_W/2 - 4) ; //�ؼ��Ŀ��
	m_iColW = SCREEN_W/2 + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,MONTH_SALE_SHOW_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window

	//����һ����ǩ  ��һ��	
	label[0] = new CaLabel(false,CaObject::ALIGN_RIGHT);
	curH = SCREEN_TOP_OFFSET;
	label[0]->Create(0,curH, SCREEN_W, CHAR_H); //����������,��ǰҳ/��ҳ��
	label[0]->SetTitle(title_array[0], strlen(title_array[0]));
  
	//����һ����ǩ  �ڶ���
	label[1] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[1]->Create(0, curH, m_iBtnW, CHAR_H); //����������
	label[1]->SetTitle(title_array[1], strlen(title_array[1]));

	label[2] = new CaLabel(false,CaObject::ALIGN_LEFT);
	label[2]->Create(m_iColW, curH, m_iBtnW, CHAR_H);
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));


	//����һ����ǩ  ������
	label[3] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[3]->Create(0, curH, m_iBtnW, CHAR_H); //����������
	label[3]->SetTitle(title_array[3], strlen(title_array[3]));
	
	label[4] = new CaLabel(false,CaObject::ALIGN_LEFT);
	label[4]->Create(m_iColW, curH, m_iBtnW, CHAR_H);
	label[4]->SetTitle(title_array[4], strlen(title_array[4]));

	//����һ����ǩ ������
	label[5] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[5]->Create(0, curH, m_iBtnW, CHAR_H); //����������
	label[5]->SetTitle(title_array[5], strlen(title_array[5]));
	
	label[6] = new CaLabel(false,CaObject::ALIGN_LEFT);
	label[6]->Create(m_iColW, curH, m_iBtnW, CHAR_H);
	label[6]->SetTitle(title_array[6], strlen(title_array[6]));
	m_iBtnW = (SCREEN_W - 40)/2 - 4;	//Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2;		//Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	
	//����һ��Button  ������
	strcpy(title, "��ӡ");
	m_pBtn1 = new CaButton();
	curH += LINE_H;
	m_pBtn1->Create(leftoffset_btn,curH,m_iBtnW,WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;
	m_pBtn1->Visible(true); //���ɼ�

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

int CMonthSaleShowWIn::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	UINT32 ii;
	char *content;

	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
		ChangeWin(MONTH_SALE_SUM_WIN);			
		 return SUCCESS;
	 	 break;

	case PAGEUP_KEY:

		 DBG_PRINT(("PAGEUP_KEY"));
		 if ((m_pageIndex-1)<1)
		 {
			 return FAILURE;
		 }
		 m_pageIndex--;
		 QueryShow(m_ptrTjxxhz, m_pageIndex);
		 ChangeTitle();
	     ReFresh();	
		 DBG_PRINT(("PAGEUP_KEY"));
		 return SUCCESS;
		 break;

	case PAGEDOWN_KEY:
		 if ((m_pageIndex+1)>m_pageNum)
		 {
			 return FAILURE;
		 }
		 m_pageIndex++;
		 QueryShow(m_ptrTjxxhz, m_pageIndex);
		 ChangeTitle();
	     ReFresh();	
		 return SUCCESS;
		 break;

	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}

int CMonthSaleShowWIn::ReFresh()
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

void CMonthSaleShowWIn::S_OnActive(CaWindow *obj)
{
	((CMonthSaleShowWIn *)obj)->DoActive();
}


void CMonthSaleShowWIn::DoActive()
{
	DBG_PRINT((" CMonthSaleShowWIn::DoActive()!"));
	m_ptrTjxxhz = ((CMonthSaleSumWIn *)m_pFrame->GetWin(MONTH_SALE_SUM_WIN))->m_pTjxxhz;
	m_iStartDate = ((CMonthSaleSumWIn *)m_pFrame->GetWin(MONTH_SALE_SUM_WIN))->m_StartDate;
	m_iEndDate = ((CMonthSaleSumWIn *)m_pFrame->GetWin(MONTH_SALE_SUM_WIN))->m_EndDate;

	m_pageIndex = 1;
	m_pageNum = 2;
	QueryShow(m_ptrTjxxhz, m_pageIndex);//��֯��Ļ��ʾ��Ϣ
	ChangeTitle();
	ReFresh();	
}

UINT8 CMonthSaleShowWIn::ChangeTitle()
{
	if (m_pageIndex == 1)
	{
		label[0]->SetTitle(title_array[0], strlen(title_array[0]));
		label[1]->SetTitle(title_array[1], strlen(title_array[1]));
		label[2]->SetTitle(title_array[2], strlen(title_array[2]));
		label[3]->SetTitle(title_array[3], strlen(title_array[3]));
		label[4]->SetTitle(title_array[4], strlen(title_array[4]));
		label[5]->SetTitle(title_array[5], strlen(title_array[5]));
		label[6]->SetTitle(title_array[6], strlen(title_array[6]));
		label[6]->Visible(true); //�ɼ�

	}
	else if (m_pageIndex == 2)
	{
		label[0]->SetTitle(title_array[0], strlen(title_array[0]));
		label[1]->SetTitle(title_array[1], strlen(title_array[1]));
		label[2]->SetTitle(title_array[2], strlen(title_array[2]));
		label[3]->SetTitle(title_array[3], strlen(title_array[3]));
		label[4]->SetTitle(title_array[4], strlen(title_array[4]));
		label[5]->SetTitle(title_array[5], strlen(title_array[5]));
		label[6]->SetTitle(title_array[6], strlen(title_array[6]));
		label[6]->Visible(false); //���ɼ�
	}

	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------------------------
//��ȡδ���뷢Ʊ����Ϣ�����޸���Ļ��ʾ
//--------------------------------------------------------------------------------------------------------------------
UINT8 CMonthSaleShowWIn::QueryShow(CTjxxhz *pTjxxhz, UINT32 nPageIndex)
{
	DBG_ASSERT_EXIT((pTjxxhz != NULL), (" pTjxxhz == NULL!"));
	
	UINT8 ret = SUCCESS;
	char value[256];
	INT32 errorcode=0;
	memset((void*)value, 0, sizeof(value));

	DBG_PRINT((" nPageIndex == %u", nPageIndex));
	//ҳ����ų���
	if( (nPageIndex<1) || (nPageIndex>m_pageNum) )
	{
		return FAILURE;
	}
	if (nPageIndex == 1)
	{
		UINT32 year=0, month=0, day=0;
		year = pTjxxhz->m_Qsrq/10000;
		month = (pTjxxhz->m_Qsrq%10000)/100;
		day = pTjxxhz->m_Qsrq%100;
		sprintf(title_array[1], "��ʼ����:%02u/%02u, ", month,day);

		year = pTjxxhz->m_Jzrq/10000;
		month = (pTjxxhz->m_Jzrq%10000)/100;
		day = pTjxxhz->m_Jzrq%100;
		sprintf(title_array[2], "��ֹ����:%02u/%02u", month,day);

		sprintf(title_array[3], "�ڳ����:%-5u, ", pTjxxhz->m_Qckcfs);
		sprintf(title_array[4], "�����¹�:%-5u", pTjxxhz->m_Lgfpfs);
		sprintf(title_array[5], "��ĩ���:%-5u, ", pTjxxhz->m_Qmkcfs);
		sprintf(title_array[6], "�����˻�:%-5u", pTjxxhz->m_Thfpfs);
	}
	else if (nPageIndex == 2)
	{
		sprintf(title_array[1], "��Ʊ����:%-5u, ", pTjxxhz->m_Zsfpfs);
		sprintf(title_array[2], "���Ϸ���:%-5u", pTjxxhz->m_Zffpfs);
		sprintf(title_array[3], "��Ʊ����:%-5u, ", pTjxxhz->m_Fsfpfs);
		sprintf(title_array[4], "���Ϸ���:%-5u", pTjxxhz->m_Fffpfs);
		sprintf(title_array[5], "�շϷ���:%-5u", pTjxxhz->m_Kffpfs);
		sprintf(title_array[6], "");
	}

	sprintf(title_array[0], "[ҳ%u/%u]", nPageIndex, m_pageNum);

	return ret;
}

void CMonthSaleShowWIn::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CMonthSaleShowWIn *win=(CMonthSaleShowWIn *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
} 


void CMonthSaleShowWIn::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CMonthSaleShowWIn *win=(CMonthSaleShowWIn *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CMonthSaleShowWIn::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 ret =SUCCESS;
	CaProgressBar proBar("��Ϣ��ȡ��.....");
	proBar.ReFresh();
	//ret = PrnMonthSaleSumProc();	 //��ӡ�����۱���
	if (SUCCESS == ret) 
	{
		ChangeWin(MONTH_SALE_SUM_WIN);	 //������ҵͳ�ƽ���
	}	
  		
}

void CMonthSaleShowWIn::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(MONTH_SALE_SUM_WIN);	 //���ط�Ʊ�������				
}


UINT8 CMonthSaleShowWIn::PrnMonthSaleSumProc()
{
	DBG_PRINT(("PrnMonthSaleSumProc()"));

	UINT8 ret;
	string strTime = "";
	INT8 chValue[256];
	memset((void*)chValue, 0, sizeof(chValue));

	//��ֽ���
	ret = YesNoMsgBox("������ֽ���Ƿ��ӡ��");
	if (ret==FAILURE)
	{
		return FAILURE;//����ӡ
	}
	if (isPaper() != 0)
	{	
		CaMsgBox::ShowMsg("��ӡ��δ��⵽ֽ");
		return FAILURE;
	}

	CaProgressBar proBar("������ͳ�ƴ�ӡ��.....");
	proBar.ReFresh();

	//��ӡ����ͷ
	PrnSaleSumHead(m_iStartDate, 0, m_iEndDate, 235959, 0);

	MonthSaleSumHandle();

	return SUCCESS;
}

UINT8 CMonthSaleShowWIn::MonthSaleSumHandle()
{
	DBG_PRINT(("MonthSaleSumHandle()"));

//	INT32 retCode;
	INT64 norMoney = 0;//ĳ������Ʊ���
//	INT64 retMoney = 0;//ĳ�����Ʊ���
	INT64 SumMoney = 0;//ĳ�µ������۽��
	INT32 ninvCount = 0;//ĳ�µĿ�Ʊ����
	INT64 allSumMoney = 0;//��ʱ�ε������۽��
	INT32 allInvCount = 0;//��ʱ�εĿ�Ʊ����
	
	INT32 nInvNum = 0;
	string strTimeFilter = "";
	string strDayFilter = "";
	INT8 chDayValue[128];
	memset((void*)chDayValue, 0, sizeof(chDayValue));
	INT8 chTimeValue[128];
	memset((void*)chTimeValue, 0, sizeof(chTimeValue));
	UINT8 nCount = 0;
	UINT8 i = 0;
	CInvHead invHead;

	DBG_PRINT(("*******��ʼͳ��*******************"));
		
	//�����ӡ
	UINT32 nStartDate = m_iStartDate;//ͳ��ʱ�ε���ʼ����
	TDateTime sDate(nStartDate, 0);
	TDateTime eDate = sDate.MonthEnd(sDate);//�������һ��
	UINT32 nDate = eDate.FormatInt(YYYYMMDD);
	UINT32 nEndDate = 0;

//	UINT32 nDate = m_StartDate;
//	TDateTime sDate(nDate, 0);
//	sprintf(chTimeValue, " where I_DATE >= %u and I_DATE <= %u",m_StartDate,m_EndDate);
//	strTimeFilter = chTimeValue;
//	nCount = 1;//ƽ����ֻͳ�Ƹ��յĲ������۽��
	
	while (1)
	{
		ninvCount = 0; //ĳ����Ա�Ŀ�Ʊ��������
		SumMoney = 0; //ĳ����Ա�������ܽ������
		
//		UINT32 nStartDate = m_StartDate;//ͳ��ʱ�ε���ʼ����
//	    sDate(nStartDate, 0);
//	TDateTime eDate = sDate.MonthEnd(sDate);//�������һ��
//	UINT32 nDate = eDate.FormatInt(YYYYMMDD);

		if (nDate>m_iEndDate)
		{
			nEndDate = m_iEndDate;
		}
		else
		{
			nEndDate = nDate;
		}
		DBG_PRINT(("*******һ��ͳ��ʱ��*******************"));
		sprintf(chDayValue, "where KPRQ >= %u and KPRQ <= %u ", nStartDate, nEndDate);
		DBG_PRINT(("һ��ͳ��ʱ��: %s", chDayValue));
		strDayFilter = chDayValue;

		//�ۼƷ�Ʊ��
		invHead.m_filter = chDayValue;//ʱ������
		DBG_PRINT(("invHead.m_filter = %s", invHead.m_filter.c_str()));
		//ninvCount = invHead.GetInvHeadNum();//ĳ�յĿ�Ʊ����
		ninvCount = invHead.GetInvNumByDate();
		if (ninvCount<0)
		{
			CaMsgBox::ShowMsg("ͳ�Ʒ�Ʊ����ʧ��");
			DBG_PRINT(("ͳ�Ʒ�Ʊ����ʧ��"));
			return FAILURE;
		}
		allInvCount += ninvCount;//�ܵĿ�Ʊ����	
//		if (ninvCount > 0)
//		{
			PrnMonth(nEndDate);//��ӡ����				
// 		}
				
		//���������ͳ�Ʋ���ӡ
		if(PrnDeptMoney(SumMoney, &strDayFilter)!=SUCCESS)
		{
			return FAILURE;
		}
	

//		if (ninvCount > 0)
//		{
			PrnMonthSaleSum(ninvCount, SumMoney); //��ӡ�����ۼ������ͽ��	
// 		}							    	     
		allSumMoney += SumMoney;//����ʱ��ε��ۼƽ��

		if (nEndDate == m_iEndDate) 
		{
			break;//�·�ͳ�ƽ���
		}
		
		(eDate)++;	//��һ��ͳ��ʱ�εĵ�һ��
		sDate = eDate;
		nStartDate = sDate.FormatInt(YYYYMMDD);
		eDate = sDate.MonthEnd(sDate);//�������һ��
		nDate = eDate.FormatInt(YYYYMMDD);
	}
	PrnAllDaySaleSum(allInvCount, allSumMoney); //��ӡ����ʱ���ۼ������ͽ��

	sprintf(chTimeValue, "where KPRQ >= %u and KPRQ <= %u ", m_iStartDate, m_iEndDate);
	DBG_PRINT(("����ͳ��ʱ��: %s", chDayValue));
	strTimeFilter = chTimeValue;
	if (PrnDeptMoney(SumMoney, &strTimeFilter)!=SUCCESS) //��ӡ�ܼƵĲ���������Ϣ
	{
		return FAILURE;
	}
	
	ForwardNLine(FORWARD_LINES);
	return SUCCESS;

}








