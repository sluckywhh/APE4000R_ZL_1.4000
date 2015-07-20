/**
 @file  M2MManageMenu.cpp
 @brief �����ļ���M2M����˵�
*/
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "MultiBtnCommonWin.h"

#include "CGlobalArg.h"
#include "netManager.h"
#include "NetServerSetWin.h"
#include "NetModelEditWin.h"

#include "M2MManageMenu.h"

CM2MManageMenu::CM2MManageMenu():CMultiBtnCommonWin(2)
{
}

int CM2MManageMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this, M2M_MANAGE_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,  "A.ģ����Ϣ");
	SetTitle(2,  "B.APN ר��");
//	SetTitle(2,  "B.���߼��");
	
	return 1;
}

void CM2MManageMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_netManager->GetConnectionMode()!=NET_M2M_WMMP &&
		g_netManager->GetConnectionMode()!=NET_M2M_APN )
	{
		CaMsgBox::ShowMsg("��ǰ������ͨѶģʽ");
		return;
	}
	else if (g_netManager->GetConnectionMode()==NET_M2M_APN &&
			g_netManager->checkConnect()==CONNECT_ON_L1 )
	{
		CaMsgBox::ShowMsg("APN������,�޷���ȡģ����Ϣ");
		return;
	}
	
	if( g_globalArg->m_sendInvFlag == 1 )
	{
		CaMsgBox::ShowMsg("��Ʊ�ϴ���,���Ժ��ٲ�");
	}
	else
	{
		ChangeWin(WIRELESS_INFO_WIN);
	}
}

void CM2MManageMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_netManager->GetConnectionMode()!=NET_M2M_WMMP &&
		g_netManager->GetConnectionMode()!=NET_M2M_APN )
	{
		CaMsgBox::ShowMsg("��M2M����ģʽ");
		return;
	}
	ChangeWin(APN_ACCPOINT_SET_WIN);
}

//void CM2MManageMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
//{
//	if (g_netManager->GetConnectionMode()!=NET_M2M_WMMP &&
//		g_netManager->GetConnectionMode()!=NET_M2M_APN )
//	{
//		CaMsgBox::ShowMsg("��ǰ������ͨѶģʽ");
//	}
//	else
//	{
//		DBG_PRINT(("m_sendInvFlag = %d", g_globalArg->m_sendInvFlag));
//		if( g_globalArg->m_sendInvFlag == 1 )
//		{
//			CaMsgBox::ShowMsg("��Ʊ�ϴ���,���Ժ��ٲ�");
//		}
//		else
//		{
//			ChangeWin(WIRELESS_VIEW_WIN);
//		}
//	}
//}

int CM2MManageMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (RETURN_MAIN_MENU == iEvent)
	{
		ChangeWin(NETWORK_SET_MENU);
		return SUCCESS;
	}
	
	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

