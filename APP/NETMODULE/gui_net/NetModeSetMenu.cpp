/**
 @file  NetModeSetMenu.cpp
 @brief �����ļ�������ģʽ���ò˵�
*/
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"

#include "netManager.h"
#include "NetModeSetMenu.h"

CNetModeSetMenu::CNetModeSetMenu():CMultiBtnCommonWin(2)
{
}

int CNetModeSetMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,NET_MODE_SET_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.����ģʽ����");
	SetTitle(2,"B.����VPNר��");
	
	return 1;
}

void CNetModeSetMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(NETMODEL_EDIT_WIN);	
}

void CNetModeSetMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	int ret = 0;
	CNetConnection *p=NULL;
	string strErr("");
	
	if(g_netManager->GetConnectionModeL2() == NET_NONE)
	{
		CaMsgBox msgBox("����VPNר��ģʽ?", CaMsgBox::MB_YESNO);
		msgBox.ShowBox();
		if (msgBox.m_iStatus == OK_PRESSED)
		{
			ret = g_netManager->SetConnectionModeL2(NET_VPN, &p, strErr);
			if (ret != NET_SUCCESS)
			{
				DBG_PRINT(("ret = %d", ret))
				CaMsgBox::ShowMsg("����VPNģʽ����");
				return;
			}
			ret = CNetDBWork::saveNetModeL2(NET_VPN, strErr);
			if (ret != SQLITE_OK)
			{
				DBG_PRINT(("ret = %d", ret))
				CaMsgBox::ShowMsg(strErr);
				return;
			}
		}
		else
		{
			ReFresh();
			return;
		}
	}
	else if (g_netManager->GetConnectionModeL2() == NET_VPN)
	{
		CaMsgBox msgBox("VPNר���ѿ���,�Ƿ�ر�?", CaMsgBox::MB_YESNO);
		msgBox.ShowBox();
		if (msgBox.m_iStatus == OK_PRESSED)
		{
			ret = g_netManager->SetConnectionModeL2(NET_NONE, &p, strErr);
			if (ret != NET_SUCCESS)
			{
				DBG_PRINT(("ret = %d", ret))
				CaMsgBox::ShowMsg("����VPNģʽ����");
				return;
			}
			ret = CNetDBWork::saveNetModeL2(NET_NONE, strErr);
			if (ret != SQLITE_OK)
			{
				DBG_PRINT(("ret = %d", ret))
				CaMsgBox::ShowMsg(strErr);
				return;
			}
		}
		else
		{
			ReFresh();
			return;
		}
	}

	CaMsgBox::ShowMsg("�������");
}

int CNetModeSetMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	UINT8 ret;
	switch(iEvent) 
	{
	case RETURN_MAIN_MENU:
		ChangeWin(NET_MANAGE_MENU);
		return SUCCESS;
		break;	
		
	default: break;
	}

	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

