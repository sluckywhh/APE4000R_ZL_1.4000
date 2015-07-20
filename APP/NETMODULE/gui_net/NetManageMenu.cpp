/**
 @file  NetManageMenu.cpp
 @brief �����ļ�������ģ�����˵�
*/
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "MultiBtnCommonWin.h"

#include "NetServerSetWin.h"
#include "NetModelEditWin.h"
#include "ADSLInfoSetWin.h"

#include "netManager.h"
#include "NetManageMenu.h"


#if (TEST_CONNECT_TYPE==2)
#include "NetCommunication.h"
#endif

CNetManageMenu::CNetManageMenu():CMultiBtnCommonWin(9,2)
{
}

int CNetManageMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this, NET_MANAGE_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);

	SetTitle(1,  "A.��Ʊ������");
	SetTitle(2,  "B.���Ӳ���");
	SetTitle(3,  "C.����ģʽ");
	SetTitle(4,  "D.��������");
	SetTitle(5,  "E.ADSL����");	
	SetTitle(6,  "F. 3G ����");
	SetTitle(7,  "G.APN ����");
	SetTitle(8,  "H.VPN ר��");
	SetTitle(9,  "I.��������");

	
	return 1;
}

void CNetManageMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	((CNetServerSetWin *)m_pFrame->GetWin(NET_SERVER_SET_WIN))->m_servType = APP_SERV;
	ChangeWin(NET_SERVER_SET_WIN);
}

void CNetManageMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
//	string strErr;
	ConnectTest();
//	if( ret == SUCCESS )
//		CaMsgBox::ShowMsg(strErr);
}

void CNetManageMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	((CNetModelEditWin *)m_pFrame->GetWin(NETMODEL_EDIT_WIN))->m_pageFlag = 0;
	ChangeWin(NETMODEL_EDIT_WIN);
}

void CNetManageMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(NETWORK_SET_MENU);
}

void CNetManageMenu::OnButton5(int iEvent, unsigned char * pEventData, int iDataLen)
{
#if (_CONFIG_ADSL_MODULE != 0)
	CaProgressBar info("���ADSL״̬...");
	info.Show();
	if (g_netManager->GetConnectionMode() != NET_ADSL)
	{
		CaMsgBox::ShowMsg("��ǰ����ADSLģʽ");
		return;
	}
	CNetConnection *pNet=g_netManager->GetConnectionHandle();
	netConnectProc(pNet);

#else
	CaMsgBox::ShowMsg("��ǰ�汾��֧��");
#endif
}

void CNetManageMenu::OnButton6(int iEvent, unsigned char * pEventData, int iDataLen)
{
#if (_CONFIG_3G_MODULE != 0)
	CaProgressBar info("���3G״̬...");
	info.Show();
	if (g_netManager->GetConnectionMode() != NET_3G)
	{
		CaMsgBox::ShowMsg("��ǰ����3Gģʽ");
		return;
	}
	CNetConnection *pNet=g_netManager->GetConnectionHandle();
	netConnectProc(pNet);

#else
	CaMsgBox::ShowMsg("��ǰ�汾��֧��");
#endif
}

void CNetManageMenu::OnButton7(int iEvent, unsigned char * pEventData, int iDataLen)
{
#if (_CONFIG_M2M_MODULE != 0)
	CaProgressBar info("���M2M״̬...");
	info.Show();
	if (g_netManager->GetConnectionMode() != NET_M2M_APN)
	{
		CaMsgBox::ShowMsg("��ǰ����M2Mģʽ");
		return;
	}
	CNetConnection *pNet=g_netManager->GetConnectionHandle();
	netConnectProc(pNet);

#else
	CaMsgBox::ShowMsg("��ǰ�汾��֧��");
#endif
}

void CNetManageMenu::OnButton8(int iEvent, unsigned char * pEventData, int iDataLen)
{
#if (_CONFIG_VPN_MODULE != 0)
	CaProgressBar info("���VPN״̬...");
	info.Show();
	if (g_netManager->GetConnectionModeL2() != NET_VPN)
	{
		CaMsgBox::ShowMsg("��ǰδ����VPNģʽ");
		return;
	}
	CNetConnection *pNet=g_netManager->GetConnectionHandleL2();
	netConnectProc(pNet);
	
#else
	CaMsgBox::ShowMsg("��ǰ�汾��֧��");
#endif
}

void CNetManageMenu::OnButton9(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(NET_AUTO_DIAL_SET_WIN);
}


int CNetManageMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (RETURN_MAIN_MENU == iEvent)
	{
		ChangeWin(PROGRAM_CTRL_MAIN_MENU);
		return SUCCESS;
	}

	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

void CNetManageMenu::netConnectProc(CNetConnection *pNet)
{
	int ret=0;
	string strErr("");
	CaProgressBar info("");

	if (pNet->performCheck() != CHECK_OK)
	{
		CaMsgBox msgBox("�Ƿ�ʼ����?", CaMsgBox::MB_YESNO);
		msgBox.ShowBox();
		if (msgBox.m_iStatus == OK_PRESSED)
		{	
			info.SetText("����������,���Ժ�...");
			info.Show();
			ret = pNet->performConnect(strErr);
			if (ret != NET_SUCCESS)
			{
				DBG_PRINT(("ret = %d", ret))
				CaMsgBox::ShowMsg(strErr);
				return;
			}
			CaMsgBox::ShowMsg("�������ӳɹ�");
			return;
		}
	}
	else
	{
		CaMsgBox msgBox("�Ƿ�Ͽ�����?", CaMsgBox::MB_YESNO);
		msgBox.ShowBox();
		if (msgBox.m_iStatus == OK_PRESSED)
		{	
			info.SetText("����Ͽ���...");
			info.Show();
			ret = pNet->performDisConnect();
			if (ret != NET_SUCCESS)
			{
				DBG_PRINT(("ret = %d", ret))
				CaMsgBox::ShowMsg(strErr);
				return;
			}
			CaMsgBox::ShowMsg("����Ͽ����");
			return;
		}
	}
}

void CNetManageMenu::ConnectTest()
{
	//����Ƿ��ѽ�������
	if (g_netManager->checkConnect() == CONNECT_OFF)
	{
		CaMsgBox::ShowMsg("��δ������������");
		return ;
	}
	
	CaMsgBox msgBox("�Ƿ����Ӳ��ԣ�", CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
	{
		return; 
	}
	
	string strErr;
	CaProgressBar proBar("���Ӳ���......");
	proBar.Show();

	//����CheckServerLink���ԣ��ú���ֻ���Խ������ӣ��������ݴ��䡣
#if (TEST_CONNECT_TYPE==2)
	CNetTrans NetTrans;
	if( NetTrans.ConnectServerTest(strErr) != SUCCESS )
	{
		strErr = "���Ӳ���ʧ��";	   
	}
	else
	{
		strErr = "���Ӳ��Գɹ�";	   
	}
#endif

#if (TEST_CONNECT_TYPE==1)
	CNetTransfers *p=NULL;
	p=g_netManager->GetTransHandle();
	if (p->CheckServerLink(strErr) != NET_SUCCESS)
	{
		strErr = "���Ӳ���ʧ��";
	}	
	else
	{
		strErr = "���Ӳ��Գɹ�";	   
	}
	g_netManager->ReleaseTransHandle(p);
#endif

	CaMsgBox::ShowMsg(strErr);
	return;
}
