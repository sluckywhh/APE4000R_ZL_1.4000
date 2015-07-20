/*! \file    MonthSaleSumWin.cpp
   \brief    awe4000r�����ӡ��������ͳ��ʱ���������
   \author   Yu Yan
   \version  1.0
   \date     2008-9-19 
 */
#include "MonthSaleSumWin.h"
#include "ReportFunc.h"
#include "CGlobalArg.h"


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CMonthSaleSumWIn::CMonthSaleSumWIn():CaWindow()
{
	m_StartDate = 0;
	m_EndDate = 0;
	m_pTjxxhz = &m_Tjxxhz;
}

CMonthSaleSumWIn::~CMonthSaleSumWIn()
{
	
}

int CMonthSaleSumWIn::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
  
	m_pFrame->RegsiterWin(this,MONTH_SALE_SUM_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	
	//����һ��Input  ��һ��
	strcpy(title, "�����ѯ�·�:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET+6;
	//curH += LINE_H;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(left_offset,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(6);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ��������
	m_pInput1->OnObject = S_OnInput1;

	strcpy(title, "����ʾ��: ���ѯ2015��1��");
	curH += LINE_H;
	m_pLabel1 = new CaLabel(false,CaObject::ALIGN_LEFT);
	m_pLabel1->Create(left_offset,curH, SCREEN_W, CHAR_H);
	m_pLabel1->SetTitle(title, strlen(title));
	
	strcpy(title, "����ͳ��, ������201501");
	curH += LINE_H;
	m_pLabel2 = new CaLabel(false,CaObject::ALIGN_LEFT);
	m_pLabel2->Create(left_offset,curH, SCREEN_W, CHAR_H);
	m_pLabel2->SetTitle(title, strlen(title));

	// 	//����һ��Input  ��һ��
// 	strcpy(title, "�����ֹ����:");
// 	titleLen = strlen(title) * CHAR_W;
// 	curH += LINE_H;
// 	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
// 	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);
// 	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
// 	m_pInput2->SetMaxLen(8);
// 	m_pInput2->m_InputType = m_pInput2->aINT; //�������ֻ�����ַ�
// 	m_pInput2->OnObject = S_OnInput2;

	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�

	
	//����һ��Button  ������
	strcpy(title, "ȷ��");
	m_pBtn1 = new CaButton();
	curH += (6+LINE_H);
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

int CMonthSaleSumWIn::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
			ChangeWin(FISCAL_REPORT_MENU);			
			return SUCCESS;
		  break;		
	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}

int CMonthSaleSumWIn::ReFresh()
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

void CMonthSaleSumWIn::S_OnActive(CaWindow *obj)
{
	((CMonthSaleSumWIn *)obj)->DoActive();
}


void CMonthSaleSumWIn::DoActive()
{
	DBG_PRINT((" CMonthSaleSumWIn::DoActive()!"));
	
	m_pInput1->Clear();//���Input�������
	m_StartDate = 0;
	m_EndDate = 0;
	ReFresh();	
}

void CMonthSaleSumWIn::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CMonthSaleSumWIn *win=(CMonthSaleSumWIn *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CMonthSaleSumWIn::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CMonthSaleSumWIn *win=(CMonthSaleSumWIn *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}


void CMonthSaleSumWIn::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CMonthSaleSumWIn *win=(CMonthSaleSumWIn *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}


void CMonthSaleSumWIn::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CMonthSaleSumWIn *win=(CMonthSaleSumWIn *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CMonthSaleSumWIn::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CMonthSaleSumWIn::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}


void CMonthSaleSumWIn::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 ret = 0 ;
	string strErr("");
	ret = CheckInput();
	if(ret != SUCCESS)
	{
		return;
	}
	ret = GetMonthSumCount(m_pTjxxhz, strErr);

	if ( ret !=SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return;
	}
	ChangeWin(MONTH_SALE_SHOW_WIN);	 //������ҵͳ�ƽ���
}

void CMonthSaleSumWIn::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(FISCAL_REPORT_MENU);	 //������ҵͳ�ƽ���		
}

UINT8 CMonthSaleSumWIn::CheckInput(void)
{
	DBG_PRINT(("CheckInput begin"));
	
	char *content1;
	UINT32 nNum = 0;

	content1 = (char*)(m_pInput1->m_contentBuf); 
	DBG_PRINT(("CheckInput content1 = %s", content1));

	//δ�����ѯ�·�
	if (strlen(content1)==0)
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("�������ѯ����");
		return FAILURE;
	}
	//�������ڱ�����6λ��
	if (strlen(content1)!=6)
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("�������ڱ�����6λ��");
		return FAILURE;
	}
	m_StartDate = atoi(content1);
	m_EndDate = m_StartDate;

	unsigned int year, month, day;
	year = m_StartDate/100;
	month = m_StartDate%100;
	day = 1;
	if( TDateTime::DateIsValid(year, month, day) != 1 )
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("����������Ч");
		return FAILURE;
	}

	UINT32 nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	year = nCurDate/10000;
	month = (nCurDate%10000)/100;
	day = nCurDate%100;
	nCurDate = year*100+month;
	if (m_StartDate>nCurDate) 
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ѯ�·ݴ��ڵ�ǰ�·�!");
		return FAILURE;		
	}

	UINT32 nInitDate = g_globalArg->m_initDate;
	year = nInitDate/10000;
	month = (nInitDate%10000)/100;
	day = nInitDate%100;
	nInitDate = year*100+month;

	if (m_StartDate < nInitDate) 
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ѯ�·�С�ڳ�ʼ���·�!");
		return FAILURE;		
	}

	if (m_StartDate == nInitDate)
	{
		m_pTjxxhz->m_Qsrq = g_globalArg->m_initDate;
	}
	else
	{
		m_pTjxxhz->m_Qsrq = m_StartDate*100+1;//��ʼ��������8λ
	}

	m_pTjxxhz->m_Jzrq = m_pTjxxhz->m_Qsrq;//��ʼ��������8λ

	DBG_PRINT(("m_pTjxxhz->m_Qsrq = %u",m_pTjxxhz->m_Qsrq));
	DBG_PRINT(("m_pTjxxhz->m_Jzrq = %u",m_pTjxxhz->m_Jzrq));

	return SUCCESS;
}




















#if 0
UINT8 CMonthSaleSumWIn::CheckInput(void)
{
	DBG_PRINT(("CheckInput begin"));
	
	char *content1, *content2;
	UINT32 nNum = 0;

	content1 = (char*)(m_pInput1->m_contentBuf); 
	DBG_PRINT(("CheckInput content1 = %s", content1));
	DBG_PRINT(("CheckInput content2 = %s", content2));

	//δ������ֹ����
	if ((strlen(content1)==0)||(strlen(content2)==0))
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��������ʼ/��ֹ����");
		return FAILURE;
	}
	//�������ڱ�����8λ��
	if ((strlen(content1)!=8)||(strlen(content2)!=8))
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("�������ڱ�����8λ��");
		return FAILURE;
	}
	m_StartDate = atoi(content1);
	m_EndDate = atoi(content2);

	unsigned int year, month, day;
	year = m_StartDate/10000;
	month = (m_StartDate%10000)/100;
	day = m_StartDate%100;
	if( TDateTime::DateIsValid(year, month, day) != 1 )
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ʼ������Ч");
		return FAILURE;
	}
	year = m_EndDate/10000;
	month = (m_EndDate%10000)/100;
	day = m_EndDate%100;
	if( TDateTime::DateIsValid(year, month, day) != 1 )
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��ֹ������Ч");
		return FAILURE;
	}

	if (m_StartDate>m_EndDate) 
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ʼ����\n���ڽ�ֹ����!");
		return FAILURE;
	}

	UINT32 nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	if (m_StartDate>nCurDate) 
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ʼ���ڴ��ڵ�ǰ����!");
		return FAILURE;		
	}
	if(m_EndDate>nCurDate)
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��ֹ���ڴ��ڵ�ǰ����");
		return FAILURE;
	}

	if (m_StartDate<g_globalArg->m_initDate) 
	{
		// �������ʼ�������ʼ�����������ж�
		//m_StartDate = g_globalArg->m_initDate;//��ʼ������
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ʼ����\nС�ڳ�ʼ������!");
		return FAILURE;		
	}

	if (m_EndDate<g_globalArg->m_initDate) 
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��ֹ����\nС�ڳ�ʼ������!");
		return FAILURE;		
	}
	if (m_EndDate > nCurDate) //��ֹ���ڴ��ڵ�ǰ����
	{
		m_EndDate = nCurDate;	
	}


	//����Ƿ��з����������ջ���
// 	CInvHead invHead;
//	INT8 chValue[256];
//	memset((void*)chValue, 0, sizeof(chValue));
//	sprintf(chValue, " where I_DATE >= %u and I_DATE <= %u",m_StartDate,m_EndDate);
//	invHead.m_filter = chValue;
//	invHead.Requery();
//	INT32 errorcode = invHead.LoadOneRecord();
//	nNum = GetDaySumCount(m_StartDate, m_EndDate);
//	if (errorcode == SQLITE_OK)
//	{
//		return SUCCESS;
//	}
//	else if(errorcode == SQLITE_DONE)
//	{
//		DBG_PRINT(("��ʱ���޽��׼�¼"));
//		CaMsgBox::ShowMsg("��ʱ���޽��׼�¼");
//		return FAILURE;
//	}
//	else
//	{
//		DBG_PRINT(("��ѯ���׼�¼ʧ��"));
//		CaMsgBox::ShowMsg("��ѯ���׼�¼ʧ��");
//		return FAILURE;
//	}

	return SUCCESS;
}

UINT8 CMonthSaleSumWIn::PrnMonthSaleSumProc()
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
	PrnSaleSumHead(m_StartDate, 0, m_EndDate, 235959, 0);

	MonthSaleSumHandle();


	return SUCCESS;
}



UINT8 CMonthSaleSumWIn::MonthSaleSumHandle()
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
	UINT32 nStartDate = m_StartDate;//ͳ��ʱ�ε���ʼ����
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

		if (nDate>m_EndDate)
		{
			nEndDate = m_EndDate;
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

		if (nEndDate == m_EndDate) 
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

	sprintf(chTimeValue, "where KPRQ >= %u and KPRQ <= %u ", m_StartDate, m_EndDate);
	DBG_PRINT(("����ͳ��ʱ��: %s", chDayValue));
	strTimeFilter = chTimeValue;
	if (PrnDeptMoney(SumMoney, &strTimeFilter)!=SUCCESS) //��ӡ�ܼƵĲ���������Ϣ
	{
		return FAILURE;
	}
	
	ForwardNLine(FORWARD_LINES);
	return SUCCESS;

}
#endif