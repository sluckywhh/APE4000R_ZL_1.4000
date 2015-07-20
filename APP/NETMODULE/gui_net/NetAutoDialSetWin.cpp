/**
 @file  NetAutoDialSetWin.cpp
 @brief �����ļ��������Զ���������
*/
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"

#include "netManager.h"
#include "NetAutoDialSetWin.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CNetAutoDialSetWin::CNetAutoDialSetWin():CaWindow()
{
}

CNetAutoDialSetWin::~CNetAutoDialSetWin()
{
}


int CNetAutoDialSetWin::Create(int iX,int iY,int iW,int iH)
{
	int curH=0;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	int inputW = SCREEN_W - left_offset*4;


	m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,NET_AUTO_DIAL_SET_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window

	//����һ��Input  ��һ��
	curH = SCREEN_TOP_OFFSET;
	strcpy(title, "ԭ ֵ: ");
	m_pLbl1 = new CaLabel(false,CaObject::ALIGN_LEFT);
	m_pLbl1->Create(left_offset,curH, SCREEN_W, CHAR_H);
	m_pLbl1->SetTitle(title, strlen(title));

	//����һ��Input  ��һ��
	strcpy(title, "�� ֵ: ");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(left_offset,curH,inputW+1,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(1);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;

	strcpy(title, "0-VPN�Զ����� 1-��VPN�Զ����� ");
	m_pLbl2 = new CaLabel(false,CaObject::ALIGN_CENTER);
	curH += LINE_H;
	m_pLbl2->Create(0,curH, SCREEN_W, CHAR_H);
	m_pLbl2->SetTitle(title, strlen(title));
	
	strcpy(title, "2-�ֶ�����");
	m_pLbl3 = new CaLabel(false,CaObject::ALIGN_CENTER);
	curH += LINE_H;
	m_pLbl3->Create(0,curH, SCREEN_W, CHAR_H);
	m_pLbl3->SetTitle(title, strlen(title));
	
	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�

	//����һ��Button  ������
	strcpy(title, "�޸�");
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

int CNetAutoDialSetWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU: 
		if( m_pageFlag == 1 )
			ChangeWin(NET_SERV_MENU);
		else
			ChangeWin(NET_MANAGE_MENU);						
		return SUCCESS;
		break;		
	default: 
		break;		
	}
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CNetAutoDialSetWin::ReFresh()
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


void CNetAutoDialSetWin::S_OnActive(CaWindow *obj)
{
	((CNetAutoDialSetWin *)obj)->DoActive();
}


void CNetAutoDialSetWin::DoActive()
{
	DispParalInfo();
	ReFresh();
}

void CNetAutoDialSetWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CNetAutoDialSetWin *win=(CNetAutoDialSetWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CNetAutoDialSetWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); 
	return;		
}

void CNetAutoDialSetWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CNetAutoDialSetWin *win=(CNetAutoDialSetWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CNetAutoDialSetWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CNetAutoDialSetWin *win=(CNetAutoDialSetWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void CNetAutoDialSetWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangePara();
}

void CNetAutoDialSetWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if( m_pageFlag == 1 )
		ChangeWin(NET_SERV_MENU);
	else
		ChangeWin(NET_MANAGE_MENU);
}

void CNetAutoDialSetWin::DispParalInfo()
{
	char chValue[32];
	INT32 autoDialType=0;
	string strErr("");

	CNetDBWork::loadAutoDialType(&autoDialType, strErr);
	memset(chValue, 0, sizeof(chValue));
	sprintf(chValue, "ԭ ֵ: %d", autoDialType);
	m_pLbl1->SetTitle(chValue, strlen(chValue));

	m_pInput1->Clear();
}

void CNetAutoDialSetWin::ChangePara()
{
	int ret=0, flag=0;
	INT8 tmpChar[64];
	string strErr("");
	CaProgressBar proBar("�����޸���...");	
	CNetConnection *pnet=NULL;

	INT32 autoDialType = atoi((char*)(m_pInput1->m_contentBuf));

	proBar.Show();
	if( CheckInputValid(strErr) != SUCCESS )
	{
		CaMsgBox::ShowMsg(strErr);
		return;
	}

	ret = CNetDBWork::saveAutoDialType(autoDialType, strErr);
	if (ret != SQLITE_OK)
	{
		DBG_PRINT(("ret = %d", ret))
		CaMsgBox::ShowMsg(strErr);
		return;
	}
	
	CaMsgBox::ShowMsg("���óɹ�");
	ChangeWin(NET_MANAGE_MENU);
	return;
}

UINT8 CNetAutoDialSetWin::CheckInputValid(string &strErr)
{
	int type = atoi((char*)(m_pInput1->m_contentBuf));
	
	if( type < 0 || type > 2 )
	{
		strErr = "�޴�ģʽ";
		return FAILURE;
	}

#if (_CONFIG_VPN_MODULE == 0)	
	if (type == 0)		
	{
		strErr = "��ǰ��֧��VPN�Զ�����";
		return FAILURE;
	}
#endif

	return SUCCESS;
}





