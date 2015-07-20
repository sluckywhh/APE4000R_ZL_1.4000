/*! \file    SysLogDateWin.cpp
   \brief    awe4000r�����ӡ��ϵͳ��־����
   \author   Yu Yan
   \version  1.0
   \date    2008-7-17  
 */


#include "SysLogDateWin.h"
#include "ReportFunc.h"
#include "sqlite3.h"
#include "CSysLog.h"
#include "CGlobalArg.h"
#include "CaProgressBar.h"
#include "printer.h"
#include "PrintDriver.h"

#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"

CSysLogDateWin::CSysLogDateWin():CaWindow()
{
	m_StartDate = 0;
	m_EndDate = 0;

}

CSysLogDateWin::~CSysLogDateWin()
{
	
}


int CSysLogDateWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,SYS_LOG_DATE_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	
	//����һ��Input  ��һ��
	strcpy(title, "������ʼ����:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET;
	curH += LINE_H;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(8);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;

	//����һ��Input  ��һ��
	strcpy(title, "�����ֹ����:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(8);
	m_pInput2->m_InputType = m_pInput2->aINT; //�������ֻ�����ַ�
	m_pInput2->OnObject = S_OnInput2;
	
	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	
	//����һ��Button  ������
	strcpy(title, "��ӡ");
	m_pBtn1 = new CaButton();
	curH += 2*LINE_H;
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

int CSysLogDateWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
			ChangeWin(REPORT_MAIN_MENU);			
			return SUCCESS;
		  break;		
	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}



int CSysLogDateWin::ReFresh()
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

void CSysLogDateWin::S_OnActive(CaWindow *obj)
{
	((CSysLogDateWin *)obj)->DoActive();
}


void CSysLogDateWin::DoActive()
{
	DBG_PRINT((" CSysLogDateWin::DoActive()!"));
	
	m_pInput1->Clear();//���Input�������
	m_pInput2->Clear();//���Input�������
	m_StartDate = 0;
	m_EndDate = 0;
	ReFresh();	
}



void CSysLogDateWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CSysLogDateWin *win=(CSysLogDateWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CSysLogDateWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CSysLogDateWin *win=(CSysLogDateWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}


void CSysLogDateWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CSysLogDateWin *win=(CSysLogDateWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}


void CSysLogDateWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CSysLogDateWin *win=(CSysLogDateWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CSysLogDateWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CSysLogDateWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}


void CSysLogDateWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 ret = CheckInput();
	if (SUCCESS==ret)
	{
		PrnSysLog(m_StartDate, m_EndDate);
		ChangeWin(REPORT_MAIN_MENU);	 //��ѯ��ӡ����	
	}

}

void CSysLogDateWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(REPORT_MAIN_MENU);	 //���ط�Ʊ�������		
}



UINT8 CSysLogDateWin::CheckInput(void)
{
	DBG_PRINT(("CheckInput begin"));
	
	char *content1, *content2;
	INT32 nNum = 0;

	content1 = (char*)(m_pInput1->m_contentBuf); 
	content2 = (char*)(m_pInput2->m_contentBuf); 
	DBG_PRINT(("CheckInput content1 = %s", content1));
	DBG_PRINT(("CheckInput content2 = %s", content2));


	//δ��������
	if ((strlen(content1)==0)||(strlen(content2)==0))
	{
		CaMsgBox::ShowMsg("��������ʼ/��ֹ����");
		return FAILURE;
	}
	//�������ڱ�����8λ��
	if ((strlen(content1)!=8)||(strlen(content2)!=8))
	{
		CaMsgBox::ShowMsg("�������ڱ�����8λ��");
		return FAILURE;
	}
	m_StartDate = atoi(content1);
	m_EndDate = atoi(content2);

	if (m_StartDate>m_EndDate) 
	{
		CaMsgBox::ShowMsg("��ʼ����\n���ڽ�������!");
		return FAILURE;
	}

	UINT32 nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	if(m_EndDate>nCurDate)
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��ֹ���ڴ��ڵ�ǰ����");
		return FAILURE;
	}

	//����Ƿ��з����������ջ���
	CSysLog sysLog;
    INT8 chValue[128];
	sprintf(chValue, "where I_DATE >= %u and I_DATE <= %u", m_StartDate, m_EndDate);
	sysLog.m_filter = chValue;
	nNum = sysLog.GetRecordNum();
	if(nNum == 0)
	{
		CaMsgBox::ShowMsg("�޸�ʱ�ε�ϵͳ��־");
		return FAILURE;
	}
	else if(nNum < 0)
	{
		CaMsgBox::ShowMsg("ϵͳ��־��ѯʧ��");
		return FAILURE;
	}

	return SUCCESS;
}

UINT8 CSysLogDateWin::PrnSysLog(UINT32 nStartDate, UINT32 nEndDate)
{
	UINT8 ret;
	
	ret = YesNoMsgBox("������ֽ���Ƿ��ӡ��");
	if (ret==FAILURE)
	{
		return SUCCESS;//����ӡ
	}
	if (isPaper() != 0)
	{	
		CaMsgBox::ShowMsg("��ӡ��δ��⵽ֽ");
		return FAILURE;
	}

	CaProgressBar proBar("��־��ӡ��.....");

	//��ӡϵͳ��־ͷ
	PrnSysLogHead(nStartDate, nEndDate);

	//�����¼��ӡ��־��ϸ
	CSysLog sysLog;
	INT8 chValue[128];
	sprintf(chValue, "where I_DATE >= %u and I_DATE <= %u", m_StartDate, m_EndDate);
	sysLog.m_filter = chValue;
	sysLog.Requery();

	INT32 errorcode = sysLog.MoveFirst();
	while (errorcode == SQLITE_ROW)
	{
		PrnSysLogDetail(&sysLog);			    	     
		errorcode = sysLog.MoveNext();
	}

	ForwardNLine(FORWARD_LINES);

	if (errorcode==SQLITE_DONE) 
	{		
		return SUCCESS;
	}
	DBG_PRINT(("��ѯSYSLOG����errorcode = %d", errorcode));	
	return FAILURE;	
}