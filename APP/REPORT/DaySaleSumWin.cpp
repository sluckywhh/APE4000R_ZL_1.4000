/*! \file    DaySaleSumWin.cpp
   \brief    awe4000r�����ӡ��������ͳ��ʱ���������
   \author   Yu Yan
   \version  1.0
   \date     2008-9-19 
 */


#include "DaySaleSumWin.h"
#include "ReportFunc.h"
#include "sqlite3.h"
#include "CGlobalArg.h"
#include "CaProgressBar.h"
#include "CInvHead.h"
#include "PrintDriver.h"

#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CDaySaleSumWin::CDaySaleSumWin():CaWindow()
{
	m_StartDate = 0;
	m_EndDate = 0;
	m_StartTime = 0;
	m_EndTime = 0;

}

CDaySaleSumWin::~CDaySaleSumWin()
{
	
}


int CDaySaleSumWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,DAY_SALE_SUM_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	
	//����һ��Input  ��һ��
	strcpy(title, "������ʼ����:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(8);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;

	//����һ��Input  ��һ��
	strcpy(title, "������ʼʱ��:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(6);
	m_pInput2->m_InputType = m_pInput2->aINT; //�������ֻ�����ַ�
	m_pInput2->OnObject = S_OnInput2;

	//����һ��Input  ��һ��
	strcpy(title, "�����ֹ����:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput3=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput3->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput3->SetTitle(title,titleLen / CHAR_W);	
	m_pInput3->SetMaxLen(8);
	m_pInput3->m_InputType = m_pInput3->aINT; //�������ֻ�����ַ�
	m_pInput3->OnObject = S_OnInput3;

	//����һ��Input  ��һ��
	strcpy(title, "�����ֹʱ��:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput4=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput4->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput4->SetTitle(title,titleLen / CHAR_W);	
	m_pInput4->SetMaxLen(6);
	m_pInput4->m_InputType = m_pInput4->aINT; //�������ֻ�����ַ�
	m_pInput4->OnObject = S_OnInput4;

	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�
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

int CDaySaleSumWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
			ChangeWin(COMMERCE_REPORT_MENU);			
			return SUCCESS;
		  break;		
	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}



int CDaySaleSumWin::ReFresh()
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

void CDaySaleSumWin::S_OnActive(CaWindow *obj)
{
	((CDaySaleSumWin *)obj)->DoActive();
}


void CDaySaleSumWin::DoActive()
{
	DBG_PRINT((" CDaySaleSumWin::DoActive()!"));
	
	m_pInput1->Clear();//���Input�������
	m_pInput2->Clear();//���Input�������
	m_pInput3->Clear();//���Input�������
	m_pInput4->Clear();//���Input�������

	m_pInput2->SetContentBuf((UINT8 *)"000000", 6);
	m_pInput4->SetContentBuf((UINT8 *)"235959", 6);

	m_StartDate = 0;
	m_EndDate = 0;
	m_StartTime = 0;
	m_EndTime = 0;
	ReFresh();	
}



void CDaySaleSumWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CDaySaleSumWin *win=(CDaySaleSumWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CDaySaleSumWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CDaySaleSumWin *win=(CDaySaleSumWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}

void CDaySaleSumWin::S_OnInput3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CDaySaleSumWin *win=(CDaySaleSumWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CDaySaleSumWin::S_OnInput4(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CDaySaleSumWin *win=(CDaySaleSumWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}


void CDaySaleSumWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CDaySaleSumWin *win=(CDaySaleSumWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}


void CDaySaleSumWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CDaySaleSumWin *win=(CDaySaleSumWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CDaySaleSumWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CDaySaleSumWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CDaySaleSumWin::OnInput3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CDaySaleSumWin::OnInput4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CDaySaleSumWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 retCode;
	UINT8 ret = CheckInput();
	DBG_PRINT(("CheckInput() = %u", ret));
	if(ret == SUCCESS)
	{
		CaProgressBar proBar("��Ϣ��ȡ��.....");
		proBar.ReFresh();
		retCode = PrnDaySaleSumProc();	 //��ӡ�����۱���
		if (SUCCESS == retCode) 
		{
			ChangeWin(COMMERCE_REPORT_MENU);	 //������ҵͳ�ƽ���
		}		
	}
	
}


void CDaySaleSumWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(COMMERCE_REPORT_MENU);	 //������ҵͳ�ƽ���		
}



UINT8 CDaySaleSumWin::CheckInput(void)
{
	DBG_PRINT(("CheckInput begin"));
	
	char *content1, *content2, *content3, *content4;
	UINT32 nNum = 0;

	content1 = (char*)(m_pInput1->m_contentBuf); 
	content2 = (char*)(m_pInput2->m_contentBuf); 
	content3 = (char*)(m_pInput3->m_contentBuf); 
	content4 = (char*)(m_pInput4->m_contentBuf); 
	DBG_PRINT(("CheckInput content1 = %s", content1));
	DBG_PRINT(("CheckInput content2 = %s", content2));


	//δ����
	if ((strlen(content1)==0)||(strlen(content2)==0))
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��������ʼ����/ʱ��");
		return FAILURE;
	}
	if ((strlen(content3)==0)||(strlen(content4)==0))
	{
		m_pInput3->SetFocus();
		CaMsgBox::ShowMsg("�������ֹ����/ʱ��");
		return FAILURE;
	}

	//�������ڱ�����8λ��
	if ((strlen(content1)!=8)||(strlen(content3)!=8))
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("�������ڱ�����8λ��");
		return FAILURE;
	}

	//����ʱ�������6λ��
	if ((strlen(content2)!=6)||(strlen(content4)!=6))
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("����ʱ�������6λ��");
		return FAILURE;
	}
	m_StartDate = atoi(content1);
	m_StartTime = atoi(content2);
	m_EndDate = atoi(content3);
	m_EndTime = atoi(content4);

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
		m_pInput3->SetFocus();
		CaMsgBox::ShowMsg("��ֹ������Ч");
		return FAILURE;
	}
    //����ʱ�������Ч��
	if (IsTimeValid(m_StartTime) != SUCCESS)
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��ʼʱ����Ч!");
		return FAILURE;
	}
	if (IsTimeValid(m_EndTime) != SUCCESS)
	{
		m_pInput4->SetFocus();
		CaMsgBox::ShowMsg("��ֹʱ����Ч!");
		return FAILURE;
	}

	if (m_StartDate>m_EndDate) 
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ʼ����\n���ڽ�ֹ����!");
		return FAILURE;
	}
	else if ((m_StartDate==m_EndDate)&&(m_StartTime>m_EndTime)) 
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��ʼʱ��\n���ڽ�ֹʱ��!");
		return FAILURE;
	}

	UINT32 nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	UINT32 nCurTime = TDateTime::CurrentDateTime().FormatInt(HHMMSS);
	if (m_StartDate>nCurDate) 
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ʼ���ڴ��ڵ�ǰ����!");
		return FAILURE;		
	}
	else if((m_StartDate==nCurDate)&&(m_StartTime>nCurTime))
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��ʼʱ����ڵ�ǰʱ��!");
		return FAILURE;	
	}

	if (m_StartDate<g_globalArg->m_initDate) //��ʼ����С�ڳ�ʼ������
	{
		//��ʼ�������ʼ���������ж�
// 		m_StartDate = g_globalArg->m_initDate;//��ʼ������
// 		m_StartTime = 0;
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ʼ����\nС�ڳ�ʼ������!");
		return FAILURE;	
	}


	if (m_EndDate<g_globalArg->m_initDate) 
	{
		m_pInput3->SetFocus();
		CaMsgBox::ShowMsg("��ֹ����\nС�ڳ�ʼ������!");
		return FAILURE;		
	}
	if (m_EndDate>nCurDate) 
	{
		m_pInput3->SetFocus();
		CaMsgBox::ShowMsg("��ֹ����\n���ڵ�ǰ����!");
		return FAILURE;		
	}
	else if((m_EndDate==nCurDate)&&(m_EndTime>nCurTime))//���ڵ�ǰʱ��
	{
		m_EndTime = nCurTime;
	}
	

	//����Ƿ��з����������ջ���
//	CInvHead invHead;
//	INT8 chValue[256];
//	memset((void*)chValue, 0, sizeof(chValue));
//	sprintf(chValue, " where I_DATE >= %u and I_DATE <= %u",m_StartDate,m_EndDate);
//	invHead.m_filter = chValue;
//	invHead.Requery();
//	INT32 errorcode = invHead.LoadOneRecord();
////	nNum = GetDaySumCount(m_StartDate, m_EndDate);
//	if ((errorcode == SQLITE_OK)||(errorcode == SQLITE_DONE))
//	{
//		DBG_PRINT(("errorcode == SQLITE_OK or errorcode == SQLITE_DONE"));
//		return SUCCESS;
//	}
//	else if(errorcode == SQLITE_DONE)
//	{
//		DBG_PRINT(("��ʱ���޽��׼�¼"));
//		CaMsgBox::ShowMsg("��ʱ���޽��׼�¼!");
//		return FAILURE;
// 	}
//	else
//	{
//		DBG_PRINT(("��ѯ���׼�¼ʧ��"));
//		CaMsgBox::ShowMsg("��ѯ���׼�¼ʧ��!");
//		return FAILURE;
//	}

	return SUCCESS;
}

UINT8 CDaySaleSumWin::PrnDaySaleSumProc()
{
	DBG_PRINT(("PrnDaySaleSumProc()"));

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
	PrnSaleSumHead(m_StartDate, m_StartTime, m_EndDate, m_EndTime, 1);

	DaySaleSumHandle();


	return SUCCESS;
}



UINT8 CDaySaleSumWin::DaySaleSumHandle()
{
	DBG_PRINT(("DaySaleSumHandle()"));

//	INT32 retCode;
	INT64 norMoney = 0;//ĳ������Ʊ���
//	INT64 retMoney = 0;//ĳ�����Ʊ���
	INT64 SumMoney = 0;//ĳ�յ������۽��
	INT32 ninvCount = 0;//ĳ�յĿ�Ʊ����
	INT64 allSumMoney = 0;//��ʱ�ε������۽��
	INT32 allInvCount = 0;//��ʱ�εĿ�Ʊ����
	
	INT32 nInvNum = 0;
	string strTimeFilter = "";
	string strTimeFilter2 = "";
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
	UINT32 nDate = m_StartDate;
	TDateTime sDate(nDate, 0);
	sprintf(chTimeValue, " and KPSJ >= %u ",m_StartTime);
	strTimeFilter = chTimeValue; //��ʼ��
	sprintf(chTimeValue, " and KPSJ <= %u",m_EndTime);
	strTimeFilter2 = chTimeValue; //��ֹ��
	nCount = 1;//ƽ����ֻͳ�Ƹ��յĲ������۽��
	while (nDate<=m_EndDate)
	{
		ninvCount = 0; //ĳ����Ա�Ŀ�Ʊ��������
		SumMoney = 0; //ĳ����Ա�������ܽ������
			
		DBG_PRINT(("*******һ��*******************"));
		sprintf(chDayValue, "where KPRQ = %u ", nDate);
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
		//ninvCount = invHead.GetInvHeadNum();//ĳ�յĿ�Ʊ����
		ninvCount = invHead.GetInvNumByDate();
		if (ninvCount<0)
		{
			CaMsgBox::ShowMsg("ͳ�Ʒ�Ʊ����ʧ��");
			DBG_PRINT(("ͳ�Ʒ�Ʊ����ʧ��"));
			return FAILURE;
		}
		allInvCount += ninvCount;//��ʱ���ܵĿ�Ʊ����	

		PrnDate(&(sDate.FormatString(YYYYMMDD)));//��ӡ����				

		DBG_PRINT(("*******PrnDeptMoney*******************"));		
		//���������ͳ��
		if(PrnDeptMoney(SumMoney, &strDayFilter)!=SUCCESS)
		{
			return FAILURE;
		}
		DBG_PRINT(("*******PrnDaySaleSum*******************"));	
		PrnDaySaleSum(ninvCount, SumMoney); //��ӡ�����ۼ������ͽ��	
							    	     
		allSumMoney += SumMoney;//����ʱ��ε��ۼƽ��
		(sDate)++;	//��һ��
		nDate = sDate.FormatInt(YYYYMMDD);
	}
	PrnAllDaySaleSum(allInvCount, allSumMoney); //��ӡ��ʱ���ۼ������ͽ��

	if (PrnPeriodDeptMoney(SumMoney, m_StartDate, m_StartTime, m_EndDate, m_EndTime)!=SUCCESS) //��ӡ�ܼƵĲ���������Ϣ
	{
		return FAILURE;
	}

	ForwardNLine(FORWARD_LINES);
	return SUCCESS;

}