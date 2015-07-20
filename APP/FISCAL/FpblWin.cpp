// InvInfoDownloadWin.cpp: implementation of the CFpblWin class.
//
//////////////////////////////////////////////////////////////////////

#include "FpblWin.h"
#include "FiscalFun.h"
#include "TDateTime.h"
#include "CMainFrame.h"
#include "LOGCTRL.h"
#include "pos_debug.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFpblWin::CFpblWin() : CaWindow()
{

	m_StartDate=0;
	m_EndDate=0;
}

CFpblWin::~CFpblWin()
{

}

int CFpblWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;
	
    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
	
	m_pFrame->RegsiterWin(this, FPBL_WIN);
	
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	
	//����һ��Input  ��һ��
	strcpy(title, "��˰��ʼ����:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET;
	curH += LINE_H;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(8);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;
	
	//����һ��Input  �ڶ���
	strcpy(title, "��˰��ֹ����:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(8);
	m_pInput2->m_InputType = m_pInput2->aINT; //�������ֻ��������ֵ
	m_pInput2->OnObject = S_OnInput2;
	
	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
	m_iColW = (SCREEN_W - 40)/2; //Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	
	//����һ��Button  ������
	strcpy(title, "ȷ��");
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
	m_pBtn2->Create(leftoffset_btn+m_iColW,curH,m_iBtnW,WORD_H); 
	m_pBtn2->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn2->SetTitle(title, strlen(title));
	m_pBtn2->BoxType(CaObject::BOX_NO);
	m_pBtn2->OnObject = S_OnButton2;
	
	OnActive = S_OnActive;
	
	this->End();  
	return 0;
}

int CFpblWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
		ChangeWin(FISCAL_MAIN_MENU);					
		return SUCCESS;
		break;
		
	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}

int CFpblWin::ReFresh()
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

void CFpblWin::S_OnActive(CaWindow *obj)
{
	((CFpblWin *)obj)->DoActive();
}


void CFpblWin::DoActive()
{
	DBG_PRINT((" CFpblWin::DoActive()!"));
	m_pInput1->Clear();
	m_pInput2->Clear();
	ReFresh();	
}


void CFpblWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CFpblWin *win=(CFpblWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CFpblWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CFpblWin *win=(CFpblWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}


void CFpblWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CFpblWin *win=(CFpblWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}


void CFpblWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CFpblWin *win=(CFpblWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CFpblWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}


void CFpblWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}


void CFpblWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 ret = 0;
	string strErr("");

	ret = CheckInput(strErr);	
	if (ret != SUCCESS)
	{
		//CaMsgBox::ShowMsg(strErr);
		return;
	}

	CaProgressBar proBar("��Ʊ��¼��...");
	proBar.Show();

	DBG_PRINT(("���뱨˰��ʼ���� = %u", m_StartDate));
	DBG_PRINT(("���뱨˰��ֹ���� = %u", m_EndDate));

	ret = FSC_FpblProc(m_StartDate, m_EndDate, strErr);

	if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return;
	}
	else
	{
		CaMsgBox::ShowMsg("��Ʊ��¼�ɹ�");	
	}

	ChangeWin(FISCAL_MAIN_MENU);	 //���ط�Ʊ�������	
	
}


void CFpblWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(FISCAL_MAIN_MENU);	 //���ط�Ʊ�������		
}

UINT8 CFpblWin::CheckInput(string& strErr)
{

	DBG_PRINT(("CheckInput begin"));
	
	char *content1, *content2;

	content1 = (char*)(m_pInput1->m_contentBuf); //��˰��ʼ����
	content2 = (char*)(m_pInput2->m_contentBuf); //��˰��ֹ����

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
 /*
	UINT32 nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	if (m_StartDate>nCurDate) 
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ʼ���ڴ��ڵ�ǰ����!");
		return FAILURE;		
	}


	if (m_StartDate<g_globalArg->m_initDate) //��ʼ����С�ڳ�ʼ������
	{
		//��ʼ�������ʼ���������ж�
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
	if (m_EndDate>nCurDate) 
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��ֹ����\n���ڵ�ǰ����!");
		return FAILURE;		
	}
	*/

	if (m_EndDate < m_StartDate) 
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��ʼ���ڴ��ڽ�ֹ����!");
		return FAILURE;		
	}

	return SUCCESS;
}