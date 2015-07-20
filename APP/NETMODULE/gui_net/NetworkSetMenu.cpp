/**
 @file  NetworkSetMenu.cpp
 @brief �����ļ����������ò˵�
*/
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "MultiBtnCommonWin.h"
#include "CGlobalArg.h"

#include "netHeaderDef.h"
#include "netManager.h"
#include "NetworkSetMenu.h"


CNetworkSetMenu::CNetworkSetMenu():CMultiBtnCommonWin(7,2)
{
}

int CNetworkSetMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this, NETWORK_SET_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);

	SetTitle(1,  "A.�� �� ��");
	SetTitle(2,  "B.ADSL���");
	SetTitle(3,  "C. 3G ����");
	SetTitle(4,  "D.M2M ����");
	SetTitle(5,  "E.VPN ר��");	
	SetTitle(6,  "F.����IP��ѯ");
	SetTitle(7,  "G.���߼��");

	return 1;
}

void CNetworkSetMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
#if (_CONFIG_LAN_MODULE != 0)
	if (g_netManager->GetConnectionMode() != NET_LAN)
	{
		CaMsgBox::ShowMsg("��ǰ�Ǿ�����ģʽ");
		return;
	}
	ChangeWin(LOCAL_NETWORK_MENU);

#else
	CaMsgBox::ShowMsg("��ǰ�汾��֧��");
#endif
}

void CNetworkSetMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
#if (_CONFIG_ADSL_MODULE != 0)
	if (g_netManager->GetConnectionMode() != NET_ADSL)
	{
		CaMsgBox::ShowMsg("��ǰ��ADSLģʽ");
		return;
	}
	ChangeWin(ADSLINFO_SET_WIN);

#else
	CaMsgBox::ShowMsg("��ǰ�汾��֧��");
#endif
}

void CNetworkSetMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
#if (_CONFIG_3G_MODULE != 0)
	if (g_netManager->GetConnectionMode() != NET_3G)
	{
		CaMsgBox::ShowMsg("��ǰ��3Gģʽ");
		return;
	}
	ChangeWin(NET_3G_WLEN_MENU);

#else
	CaMsgBox::ShowMsg("��ǰ�汾��֧��");
#endif
}

void CNetworkSetMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{
#if (_CONFIG_M2M_MODULE != 0)
	if (g_netManager->GetConnectionMode() != NET_M2M_APN &&
		g_netManager->GetConnectionMode() != NET_M2M_WMMP)
	{
		CaMsgBox::ShowMsg("��ǰ��M2Mģʽ");
		return;
	}
	ChangeWin(M2M_MANAGE_MENU);

#else
	CaMsgBox::ShowMsg("��ǰ�汾��֧��");
#endif
}

void CNetworkSetMenu::OnButton5(int iEvent, unsigned char * pEventData, int iDataLen)
{
#if (_CONFIG_VPN_MODULE != 0)
	if (g_netManager->GetConnectionModeL2() != NET_VPN)
	{
		CaMsgBox::ShowMsg("��ǰδ����VPN");
		return;
	}
	ChangeWin(VPN_INFO_SET_WIN);

#else
	CaMsgBox::ShowMsg("��ǰ�汾��֧��");
#endif
}

void CNetworkSetMenu::OnButton6(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(NETWORKING_SHOW_WIN);
}

void CNetworkSetMenu::OnButton7(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_netManager->GetConnectionMode()!=NET_M2M_WMMP &&
		g_netManager->GetConnectionMode()!=NET_M2M_APN &&
		g_netManager->GetConnectionMode()!=NET_3G )
	{
		CaMsgBox::ShowMsg("��ǰ������ͨѶģʽ");
		return;
	}
	else if (g_netManager->GetConnectionMode()==NET_M2M_APN &&
			g_netManager->checkConnect()==CONNECT_ON_L1 )
	{
		CaMsgBox::ShowMsg("APN������,�޷���ȡ������Ϣ");
		return;
	}
	else
	{
		DBG_PRINT(("m_sendInvFlag = %d", g_globalArg->m_sendInvFlag));
		if( g_globalArg->m_sendInvFlag == 1 )
		{
			CaMsgBox::ShowMsg("��Ʊ�ϴ���,���Ժ��ٲ�");
		}
		else
		{
			ChangeWin(WIRELESS_VIEW_WIN);
		}
	}
}

int CNetworkSetMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (RETURN_MAIN_MENU == iEvent)
	{
		ChangeWin(NET_MANAGE_MENU);
		return SUCCESS;
	}

	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

