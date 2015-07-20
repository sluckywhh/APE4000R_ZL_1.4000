/*! \file    TimeSumDateWin.cpp
\brief    awe4000r�����ӡ��ʱ��λ��� ʱ���������
\author   Yu Yan
\version  1.0
\date     2008-4-8
*/

#include "TimeSumDateWin.h"
#include "ReportFunc.h"
#include "sqlite3.h"
#include "CGlobalArg.h"
#include "CInvHead.h"
#include "CaProgressBar.h"
#include "PrintDriver.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CTimeSumDateWin::CTimeSumDateWin():CaWindow()
{
	m_StartDate = 0;
	m_EndDate = 0;
	m_StartTime = 0;
	m_EndTime = 0;
	
}

CTimeSumDateWin::~CTimeSumDateWin()
{
	
}


int CTimeSumDateWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;
	
    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
	
	m_pFrame->RegsiterWin(this,TIME_SUM_DATE_WIN);
	
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	
	//����һ��Input  ��һ��
	strcpy(title, "��ʼ����:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(8);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;
	
	//����һ��Input  �ڶ���
	strcpy(title, "��ʼʱ��:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(6);
	m_pInput2->m_InputType = m_pInput2->aINT; //�������ֻ�����ַ�
	m_pInput2->OnObject = S_OnInput2;
	
	//����һ��Input  ������
	strcpy(title, "��ֹ����:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput3=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput3->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput3->SetTitle(title,titleLen / CHAR_W);	
	m_pInput3->SetMaxLen(8);
	m_pInput3->m_InputType = m_pInput3->aINT; //�������ֻ�����ַ�
	m_pInput3->OnObject = S_OnInput3;
	
	//����һ��Input  ������
	strcpy(title, "��ֹʱ��:");
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
	strcpy(title, "ȷ��");
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

int CTimeSumDateWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
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


int CTimeSumDateWin::ReFresh()
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

void CTimeSumDateWin::S_OnActive(CaWindow *obj)
{
	((CTimeSumDateWin *)obj)->DoActive();
}


void CTimeSumDateWin::DoActive()
{
	DBG_PRINT((" CTimeSumDateWin::DoActive()!"));
	
	m_pInput1->Clear();//���Input�������
	m_pInput2->Clear();//���Input�������
	m_pInput3->Clear();//���Input�������
	m_pInput4->Clear();//���Input�������
	
	m_pInput2->SetContentBuf((UINT8 *)"000000", 6);
	m_pInput4->SetContentBuf((UINT8 *)"235959", 6);
	m_StartDate = 0;
	m_EndDate = 0;
	ReFresh();	
}



void CTimeSumDateWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CTimeSumDateWin *win=(CTimeSumDateWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CTimeSumDateWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CTimeSumDateWin *win=(CTimeSumDateWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}

void CTimeSumDateWin::S_OnInput3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CTimeSumDateWin *win=(CTimeSumDateWin *)obj->GetdWin();
	win->OnInput3(iEvent,pEventData,iDataLen);
}

void CTimeSumDateWin::S_OnInput4(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CTimeSumDateWin *win=(CTimeSumDateWin *)obj->GetdWin();
	win->OnInput4(iEvent,pEventData,iDataLen);
}


void CTimeSumDateWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CTimeSumDateWin *win=(CTimeSumDateWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CTimeSumDateWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CTimeSumDateWin *win=(CTimeSumDateWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CTimeSumDateWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CTimeSumDateWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CTimeSumDateWin::OnInput3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CTimeSumDateWin::OnInput4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}


void CTimeSumDateWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 retCode;
	UINT8 ret = CheckInput();
	if(ret == SUCCESS)
	{
		CaProgressBar proBar("��Ϣ��ȡ��.....");
		proBar.ReFresh();
		ChangeWin(TIME_SUM_INFO_WIN);	 //ʱ��λ��ܽ���
		
	//	      retCode = PrnTimeSaleSumProc();	 //��ӡʱ������۱���
	//	 		if (SUCCESS == retCode) 
	//	 		{
	//	 			ChangeWin(COMMERCE_REPORT_MENU);	 //������ҵͳ�ƽ���
	//			}		
		
	}
	
}


void CTimeSumDateWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(FISCAL_REPORT_MENU);	 //����˰����Ϣ����		
}


UINT8 CTimeSumDateWin::CheckInput(void)
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
		//zcy ��ʼ�������ʼ���������ж�
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
	
	
	return SUCCESS;
}
