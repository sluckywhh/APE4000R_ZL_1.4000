/**
 @file  ZhqParaSetMenu.cpp
 @brief �����ļ���ת���������������˵�
 @author  lzh
 @date  20150608
*/
#include "APIBase.h"
#include "ZhqParaSetMenu.h"
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"


CZhqParaSetMenu::CZhqParaSetMenu():CMultiBtnCommonWin(2)
{
	m_ComNetpara = &m_Netpara;
}
CZhqParaSetMenu::~CZhqParaSetMenu()
{
}

int CZhqParaSetMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this, ZHQ_PARA_SET_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);

	SetTitle(1,  "A.��������");
	SetTitle(2,  "B.��������");

	return 1;
}

void CZhqParaSetMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (TYPE_MODE != ZHQ_MODE)
	{
		CaMsgBox::ShowMsg("��ת��������ģʽ");
		return;
	}
	ChangeWin(ZHQ_BTL_SET_WIN);
}

void CZhqParaSetMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (TYPE_MODE != ZHQ_MODE)
	{
		CaMsgBox::ShowMsg("��ת��������ģʽ");
		return;
	}
	INT32 errorcode = 0;
	m_ComNetpara->Requery();
	errorcode = m_ComNetpara->LoadOneRecord();
	DBG_PRINT(("errorcode = %d", errorcode));
	if ((errorcode!=SQLITE_DONE)&&(errorcode!=SQLITE_OK))
	{
		CaMsgBox::ShowMsg("���ݿ��ѯ����");
}
	DBG_PRINT(("m_ComNetpara: m_IDDHCP = %u", m_ComNetpara->m_IsDhcp));
	DBG_PRINT(("m_ComNetpara: m_LocalIP = %s", m_ComNetpara->m_LocalIP.c_str()));
	DBG_PRINT(("m_ComNetpara: m_ServIP = %s", m_ComNetpara->m_ServIP.c_str()));

	ChangeWin(ZHQ_IPADDR_SET_WIN);
}

// void CZhqParaSetMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
// {
// 	if (API_TYPE_MODE != ZHQ_MODE)
// 	{
// 		CaMsgBox::ShowMsg("��ת��������ģʽ");
// 		return;
// 	}
// 	ChangeWin(ZHQ_SERVERIP_SET_WIN);
// }
// 
// void CZhqParaSetMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
// {
// 	if (API_TYPE_MODE != ZHQ_MODE)
// 	{
// 		CaMsgBox::ShowMsg("��ת��������ģʽ");
// 		return;
// 	}
// 	ChangeWin(ZHQ_FTP_SET_WIN);
// }

int CZhqParaSetMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (RETURN_MAIN_MENU == iEvent)
	{
		ChangeWin(PROGRAM_CTRL_MAIN_MENU);
		return SUCCESS;
	}

	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}
