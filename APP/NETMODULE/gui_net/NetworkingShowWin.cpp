/**
 @file  NetworkingShowWin.cpp
 @brief �����ļ���IP��Ϣ��ʾ
*/
#include "arithmetic.h"
#include "CMainFrame.h"
#include "CaProgressBar.h"

#include "netHeaderDef.h"
#include "netManager.h"
#include "NetworkingShowWin.h"

#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"

CNetworkingShowWin::CNetworkingShowWin():CaWindow()
{
	memset((void *)&m_ipInfo, 0, sizeof(IPinfo));
}

CNetworkingShowWin::~CNetworkingShowWin()
{
}


int CNetworkingShowWin::Create(int iX,int iY,int iW,int iH)
{
	int curH, left_offset;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

	left_offset = SCREEN_LEFT_OFFSET+8;

    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,NETWORKING_SHOW_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window

	//����һ����ǩ  ��һ��	
	label[0] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH = SCREEN_TOP_OFFSET;
	label[0]->Create(left_offset,curH, SCREEN_W, CHAR_H); //����������
	label[0]->SetTitle(title_array[0], strlen(title_array[0]));
  
	//����һ����ǩ  �ڶ���
	label[1] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[1]->Create(left_offset,curH, SCREEN_W, CHAR_H); //����������
	label[1]->SetTitle(title_array[1], strlen(title_array[1]));
	
	//����һ����ǩ  ������
	label[2] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[2]->Create(left_offset,curH, SCREEN_W, CHAR_H);
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));

	//����һ����ǩ  ������
	label[3] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[3]->Create(left_offset,curH, SCREEN_W, CHAR_H);
	label[3]->SetTitle(title_array[3], strlen(title_array[3]));

	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�
	INT32 leftoffset_btn = left_offset + 14;

	//����һ��Button  ������
	strcpy(title, "����");
	m_pBtn1 = new CaButton();
	curH += LINE_H;
	m_pBtn1->Create(leftoffset_btn + m_iColW,curH,m_iBtnW,WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;


	OnActive = S_OnActive;
	
	this->End();  
	return 0;
}

int CNetworkingShowWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:
		ChangeWin(NETWORK_SET_MENU); //��������������
		return SUCCESS;
		break;
	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}

int CNetworkingShowWin::ReFresh()
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

UINT8 CNetworkingShowWin::ChangeTitle()
{
	label[0]->SetTitle(title_array[0], strlen(title_array[0]));
	label[1]->SetTitle(title_array[1], strlen(title_array[1]));
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));
	label[3]->SetTitle(title_array[3], strlen(title_array[3]));

	return SUCCESS;
}


void CNetworkingShowWin::GetNetworkingInfo()
{
	INT32 ret=0;
	string strErr("");
	
	ret = g_netManager->getIPinfo(&m_ipInfo, strErr);
	if (ret != NET_SUCCESS)
	{
		DBG_PRINT(("ret = %d", ret))
		CaMsgBox::ShowMsg(strErr);
		memset((void *)&m_ipInfo, 0, sizeof(IPinfo));
		ClearNetworkingInfo();
	}
	else
	{
		DispNetworkingInfo();
	}
	return ;
}

void CNetworkingShowWin::DispNetworkingInfo()
{	
	sprintf(title_array[0], "�� �� IP: %s", m_ipInfo.IP);
	sprintf(title_array[1], "��������: %s", m_ipInfo.Mask);
	sprintf(title_array[2], "Ĭ������: %s", m_ipInfo.GeteWay);
	sprintf(title_array[3], "Ĭ�� DNS: %s", m_ipInfo.DNS);

	return;
}

void CNetworkingShowWin::ClearNetworkingInfo()
{	
	sprintf(title_array[0], "�� �� IP: %s", "");
	sprintf(title_array[1], "��������: %s", "");
	sprintf(title_array[2], "Ĭ������: %s", "");
	sprintf(title_array[3], "Ĭ�� DNS: %s", "");
	
	return;
}

void CNetworkingShowWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CNetworkingShowWin *win=(CNetworkingShowWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
} 
void CNetworkingShowWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(NETWORK_SET_MENU); //��������������
}


void CNetworkingShowWin::S_OnActive(CaWindow *obj)
{
	((CNetworkingShowWin *)obj)->DoActive();
}

void CNetworkingShowWin::DoActive()
{
	CaProgressBar ProgressBar("������Ϣ��ȡ��...");
	ProgressBar.Show();

	GetNetworkingInfo();
	ChangeTitle();
	ReFresh();
}

