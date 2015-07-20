/*! \file    NetServMenu.cpp
   \brief    awe4000rϵͳά��������ά���˵�
   \author   Yu Yan
   \version  1.0
   \date     2010-10-9 16:53
 */

#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "NetModelEditWin.h"

#include "netManager.h"
#include "M2M_Common.h"
#include "NetServMenu.h"

CNetServMenu::CNetServMenu():CMultiBtnCommonWin(2)
{
}

int CNetServMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,NET_SERV_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.ģ�鼤��");
	SetTitle(2,"B.MAC����");
//	SetTitle(3,"C.ģ��ر�");
	return 1;
}


void CNetServMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{	
	CaMsgBox msgBox("�Ƿ񼤻", CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if(msgBox.m_iStatus == OK_PRESSED)
	{
		EnableM2M();	
	}
	return;
}



void CNetServMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(DOWNLOAD_MAC_WIN);
	return;
}

int CNetServMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (RETURN_MAIN_MENU == iEvent)
	 {	
		ChangeWin(MAINTENANCE_MENU);
		return SUCCESS;
	 }
//
//#if (0 == RELEASE_VER)
//	if (DISCOUNT_KEY == iEvent)
//	{
//		CaMsgBox msgBox("�Ƿ�ر�ģ�飿", CaMsgBox::MB_YESNO);
//		msgBox.ShowBox();
//		if(msgBox.m_iStatus == OK_PRESSED)
//		{
//			DisableM2M();	
//		}
//		return SUCCESS;
//	}
//#endif
		
	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

INT8 CNetServMenu::EnableM2M(void)
{
	//���۵�ǰΪ��������ģʽ������ִ��M2M�������
	if (M2MCommon::setM2MState(M2M_ACT_ON) != NET_SUCCESS)
	{
		CaMsgBox::ShowMsg("M2Mģ�鼤�����");
		return FAILURE;		
	}

	CaMsgBox::ShowMsg("M2Mģ�鼤��ɹ�");
	return SUCCESS;

}

INT8 CNetServMenu::DisableM2M(void)
{
	int netMode = g_netManager->GetConnectionMode();

	if (netMode == NET_M2M_APN || netMode == NET_M2M_WMMP)
	{
		CaMsgBox::ShowMsg("��ǰ��������ͨѶģʽ,�޷��ر�");
		return SUCCESS;
	}
	
	CaProgressBar proBar("M2Mģ��ر���.....");
	proBar.ReFresh();

	if (M2MCommon::setM2MState(M2M_ACT_OFF) != NET_SUCCESS)
	{
		CaMsgBox::ShowMsg("M2Mģ��رճ���");
		return FAILURE;		
	}

	CaMsgBox::ShowMsg("M2Mģ��رճɹ�");
	return SUCCESS;

}

