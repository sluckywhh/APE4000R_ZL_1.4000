/**
 @file  LocalNetworkMenu.cpp
 @brief �����ļ���IPģʽ�˵�
*/
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"

#include "netManager.h"
#include "LANConnection.h"
#include "LocalNetworkMenu.h" 

CLocalNetworkMenu::CLocalNetworkMenu():CMultiBtnCommonWin(2)
{
}

int CLocalNetworkMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,LOCAL_NETWORK_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.ѡ��IP��ȡģʽ");
	SetTitle(2,"B.�ֶ�����IP");
	
	return 1;
}

void CLocalNetworkMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if(g_netManager->GetConnectionMode() != NET_LAN)
	{
		CaMsgBox::ShowMsg("��ǰ�Ǿ�����ģʽ,�����޸�");
		return;
	}
	ChangeWin(NET_IP_MODEL_WIN);
}

void CLocalNetworkMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if(g_netManager->GetConnectionMode() != NET_LAN)
	{
		CaMsgBox::ShowMsg("��ǰ�Ǿ�����ģʽ,�����޸�");
		return;
	}
	LANConnection *p=(LANConnection *)g_netManager->GetConnectionHandle();
	if(p->m_dhcpMode == LAN_DHCP_ON)
	{
		CaMsgBox::ShowMsg("��ǰ�Զ���ȡIPģʽ,�����ֶ��޸�");
		return;
	}
		
	ChangeWin(NETWORKING_SET_WIN);	
}

int CLocalNetworkMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	UINT8 ret;
	switch(iEvent) 
	{
	case RETURN_MAIN_MENU:
		ChangeWin(NETWORK_SET_MENU);
		return SUCCESS;
		break;	
		
	default: break;
	}

	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

