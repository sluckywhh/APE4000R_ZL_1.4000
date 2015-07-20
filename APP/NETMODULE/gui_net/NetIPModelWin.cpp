/**
 @file  NetIPModelWin.cpp
 @brief �����ļ���ѡ��IPģʽ
*/
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"

#include "netManager.h"
#include "LANConnection.h"
#include "NetIPModelWin.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"



CNetIPModelWin::CNetIPModelWin():CaWindow()
{
}

CNetIPModelWin::~CNetIPModelWin()
{
}


int CNetIPModelWin::Create(int iX,int iY,int iW,int iH)
{
	int curH=0;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	int inputW = SCREEN_W - left_offset*4;


	m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,NET_IP_MODEL_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window

	//����һ��Input  ��һ��
	curH = SCREEN_TOP_OFFSET+2;
	strcpy(title, "ԭ ֵ: ");
	m_pLbl1 = new CaLabel(false,CaObject::ALIGN_LEFT);
	m_pLbl1->Create(left_offset,curH, SCREEN_W, CHAR_H);
	m_pLbl1->SetTitle(title, strlen(title));

	//����һ��Input  ��һ��
	strcpy(title, "�� ֵ: ");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H+2;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(left_offset,curH,inputW+1,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(1);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;

	strcpy(title, "0:�ֹ�����IP 1:��̬��ȡIP");
	m_pLbl2 = new CaLabel(false,CaObject::ALIGN_CENTER);
	curH += LINE_H+2;
	m_pLbl2->Create(0,curH, SCREEN_W, CHAR_H);
	m_pLbl2->SetTitle(title, strlen(title));
	
	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�

	//����һ��Button  ������
	strcpy(title, "�޸�");
	m_pBtn1 = new CaButton();
	curH += LINE_H+6;
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

int CNetIPModelWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU: 
		ChangeWin(LOCAL_NETWORK_MENU);						
		return SUCCESS;
		break;		
	default: 
		break;		
	}
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CNetIPModelWin::ReFresh()
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


void CNetIPModelWin::S_OnActive(CaWindow *obj)
{
	((CNetIPModelWin *)obj)->DoActive();
}


void CNetIPModelWin::DoActive()
{
	DispCurInfo();
	ReFresh();
}

void CNetIPModelWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CNetIPModelWin *win=(CNetIPModelWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CNetIPModelWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); 
	return;		
}

void CNetIPModelWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CNetIPModelWin *win=(CNetIPModelWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CNetIPModelWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CNetIPModelWin *win=(CNetIPModelWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void CNetIPModelWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeNetIPModel();
}

void CNetIPModelWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(LOCAL_NETWORK_MENU);
}

void CNetIPModelWin::DispCurInfo()
{
	char chValue[32];
	
	LANConnection *pLan = (LANConnection *)g_netManager->GetConnectionHandle();	
	memset(chValue, 0, sizeof(chValue));
	sprintf(chValue, "ԭ ֵ: %d", pLan->m_dhcpMode);
	m_pLbl1->SetTitle(chValue, strlen(chValue));

	m_pInput1->Clear();
}

void CNetIPModelWin::ChangeNetIPModel()
{
	INT32 ret = 0;
	string strErr("");
	string tmpMsg("");
	CaProgressBar proBar("����������...");	

	int ipModel = atoi((char*)(m_pInput1->m_contentBuf));
	LANConnection *pLan = (LANConnection *)g_netManager->GetConnectionHandle();	

	if( CheckInputValid(strErr) != SUCCESS )
	{
		CaMsgBox::ShowMsg(strErr);
		return;
	}

	if (ipModel==LAN_DHCP_ON)
		tmpMsg = "�л�Ϊ��̬IPģʽ?";
	else 
		tmpMsg = "�л�Ϊ�ֶ�����IPģʽ?";

	CaMsgBox msgBox(tmpMsg.c_str(), CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if (msgBox.m_iStatus == OK_PRESSED)
	{
		proBar.Show();
		ret = pLan->setDhcpMode(ipModel, strErr);
		if (ret != NET_SUCCESS)
		{
			DBG_PRINT(("ret = %d", ret))
			CaMsgBox::ShowMsg(strErr);
		}				
		CaMsgBox::ShowMsg("�������");
	}
	else
	{
		ReFresh();
		return;
	}

	return;
}

UINT8 CNetIPModelWin::CheckInputValid(string &strErr)
{
	int ipModel = atoi((char*)(m_pInput1->m_contentBuf));
	LANConnection *pLan = (LANConnection *)g_netManager->GetConnectionHandle();	

	if( ipModel != LAN_DHCP_ON && ipModel != LAN_DHCP_OFF )
	{
		strErr = "��֧�ִ�IPģʽ";
		return FAILURE;
	}

	if( ipModel == pLan->m_dhcpMode )
	{
		strErr = "��ǰģʽ,�����޸�";
		return FAILURE;
	}

	return SUCCESS;
}

