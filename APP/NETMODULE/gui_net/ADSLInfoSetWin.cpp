/**
 @file  ADSLInfoSetWin.cpp
 @brief �����ļ�������ADSL�ʻ���Ϣ
*/
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"

#include "netManager.h"
#include "ADSLConnection.h"
#include "ADSLInfoSetWin.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CADSLInfoSetWin::CADSLInfoSetWin():CaWindow()
{
	m_strUsrPwd = "";
}

CADSLInfoSetWin::~CADSLInfoSetWin()
{
}


int CADSLInfoSetWin::Create(int iX,int iY,int iW,int iH)
{
	int curH=0;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	int inputW = SCREEN_W - left_offset*2;

	m_iBtnW = (SCREEN_W/2 - 0) ; 
	m_iColW = m_iBtnW + 0;        
  
	m_pFrame->RegsiterWin(this,ADSLINFO_SET_WIN);
	CaWindow::Create(iX,iY,iW,iH); 

	//����һ��Input  ��һ��
	strcpy(title, "ADSL�ʺ�:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET+4;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(left_offset,curH,inputW+1,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(20);
	m_pInput1->m_InputType = m_pInput1->aCHAR; 
	m_pInput1->OnObject = S_OnInput1;

	//����һ��Input  �ڶ���
	strcpy(title, "��  ��:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H+4;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput2->Create(left_offset,curH,inputW+1,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(20);
	m_pInput2->m_InputType = m_pInput2->aCHAR; //�������ֻ�����ַ�
	m_pInput2->OnObject = S_OnInput2;

	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�

	//����һ��Button  ������
	strcpy(title, "ȷ��");
	m_pBtn1 = new CaButton();
	curH += LINE_H*2;
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

int CADSLInfoSetWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU: 
		ClearWin();
		ChangeWin(NETWORK_SET_MENU);						
		return SUCCESS;
		break;		
	default: 
		break;		
	}
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CADSLInfoSetWin::ReFresh()
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


void CADSLInfoSetWin::S_OnActive(CaWindow *obj)
{
	((CADSLInfoSetWin *)obj)->DoActive();
}


void CADSLInfoSetWin::DoActive()
{
	DispADSLInfo();
	ReFresh();
}

void CADSLInfoSetWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CADSLInfoSetWin *win=(CADSLInfoSetWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}
void CADSLInfoSetWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CADSLInfoSetWin *win=(CADSLInfoSetWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}

void CADSLInfoSetWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); 
	return;		
}
void CADSLInfoSetWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); 
	return;		
}

void CADSLInfoSetWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CADSLInfoSetWin *win=(CADSLInfoSetWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CADSLInfoSetWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CADSLInfoSetWin *win=(CADSLInfoSetWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void CADSLInfoSetWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	int ret=0;
	string strErr("");
	CaProgressBar proBar("");
	
	string username = (char *)m_pInput1->m_contentBuf;
	string userpwd  = (char *)m_pInput2->m_contentBuf;

	if (g_netManager->GetConnectionMode() != NET_ADSL)
	{
		CaMsgBox::ShowMsg("��ǰ��ADSLģʽ,�޷��޸�");
		return;
	}
	
	proBar.SetText("ADSL�û���Ϣ������...");
	proBar.Show();
	if( username.length() <= 0 )
	{
		CaMsgBox::ShowMsg("�û�������Ϊ��");
		m_pInput1->SetFocus();
		this->ReFresh();
		return;
	}
	if( userpwd.length() <= 0 )
	{
		CaMsgBox::ShowMsg("���벻��Ϊ��");
		m_pInput2->SetFocus();
		this->ReFresh();
		return;
	}
	if( userpwd == "********" )
	{
		userpwd = m_strUsrPwd;
	}

	CNetConnection *pADSL = g_netManager->GetConnectionHandle();
	ret = pADSL->setUserNamePwd(username, userpwd, strErr);
	if (ret != NET_SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return;
	}

 	CaMsgBox::ShowMsg("ADSL��Ϣ���óɹ�");
 	ClearWin();
 	ChangeWin(NETWORK_SET_MENU);
}

void CADSLInfoSetWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ClearWin();
	ChangeWin(NETWORK_SET_MENU);
}

void CADSLInfoSetWin::DispADSLInfo()
{
	INT32 ret=0;
	string name(""), pwd("");
	string strErr("");

	ret = CNetDBWork::loadADSLUserNamePwd(name, pwd, strErr);
	if (ret != SQLITE_OK)
	{
		DBG_PRINT(("ret = %d", ret))
		CaMsgBox::ShowMsg(strErr);
		return;
	}
	m_pInput1->SetContentBuf((UINT8 *)name.c_str(), name.length());
	if (pwd!="")
		m_pInput2->SetContentBuf((UINT8 *)"********", strlen("********"));
	else
		m_pInput2->SetContentBuf((UINT8 *)"", strlen(""));
	m_strUsrPwd = pwd;
}

void CADSLInfoSetWin::ClearWin()
{
	m_pInput1->Clear();
	m_pInput2->Clear();
}



