/*! \file  InvManageMainMenu.cpp
\brief    awe4000r��Ʊ��������˵�
\author   zcy
\version  1.0
\date     2015-05-07
*/

#include "InvManageMainMenu.h"
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "MultiBtnCommonWin.h"
#include "CGlobalArg.h"
#include "InvVolFunc.h" 


CInvManageMenu::CInvManageMenu():CMultiBtnCommonWin(8,2)
{
}

int CInvManageMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,INV_MANAGE_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	
	SetTitle(1,"A.����ѯ");
	SetTitle(2,"B.���繺Ʊ");
	SetTitle(3,"C.ƱԴ����");
	SetTitle(4,"D.��Ʊ����");
	SetTitle(5,"E.��Ʊ����");
	SetTitle(6,"F.��Ʊ���");
	SetTitle(7,"G.��Ʊ��ѯ");
	SetTitle(8,"H.Ʊ�ι���");
	
	return 1;
}

//------------------------------------------------------------------------------------
//�������ƣ�����ѯ
//�������ܣ�
//�������ߣ�zcy
//------------------------------------------------------------------------------------
void CInvManageMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}
	
	UINT32 nNum = 0;//��Ʊ�����
	string strErr("");
	UINT8 ret=SUCCESS;
	
	CaProgressBar proBar("����ѯ��.....");
    proBar.ReFresh();
	
	ret =INV_GetInvVol(nNum,strErr);
	if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return ;
	}
	DBG_PRINT(("����ѯret = %u, nNum = %u", ret, nNum));

	DBG_PRINT(("����ѯ�ɹ�"));
	
	if (nNum ==0)
	{
		CaMsgBox::ShowMsg("�����ƱԴ");
		return ;
	}
	
	ChangeWin(INV_DIST_QUERY_WIN);
}

//------------------------------------------------------------------------------------
//�������ƣ����繺Ʊ
//�������ܣ�
//�������ߣ�xsr
//------------------------------------------------------------------------------------
void CInvManageMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg( "����δ��ʼ��");
		return ;
	}

	if(g_globalArg->m_corpInfo->m_Kpjhm != 0)
	{
		CaMsgBox::ShowMsg("�ֻ��������繺Ʊ!");
		return;
	}
	
	string strErr("");
	UINT8 ret=SUCCESS;

	ChangeWin(INV_WLLQFP_WIN);

	return;
}


//------------------------------------------------------------------------------------
//ƱԴ����
//------------------------------------------------------------------------------------
void CInvManageMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg( "����δ��ʼ��");
		return ;
	}

	string strErr("");
	UINT8 ret=SUCCESS;

	UINT8 uJZlx=2;
	ret= INV_MediumType(uJZlx,strErr);
    if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return ;
	}

	ret= INV_ReadInvVol(uJZlx,strErr);
	if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return ;
	}
	CaMsgBox::ShowMsg( "ƱԴ����ɹ�!");
	return ;
}
//------------------------------------------------------------------------------------
//��Ʊ����
//------------------------------------------------------------------------------------
void CInvManageMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}
	
		
	ChangeWin(INV_RET_QUERY_WIN);
}


//------------------------------------------------------------------------------------
//��Ʊ����
//------------------------------------------------------------------------------------
void CInvManageMenu::OnButton5(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}
	
	
	ChangeWin(INV_WASTE_MENU);
}

//------------------------------------------------------------------------------------
//��Ʊ�����ѯ
//------------------------------------------------------------------------------------
void CInvManageMenu::OnButton6(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}
	ChangeWin(INV_STUB_WIN);
	
}


//��Ʊ��ѯ
//------------------------------------------------------------------------------------
void CInvManageMenu::OnButton7(int iEvent, unsigned char * pEventData, int iDataLen)
{
	
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}
	
	ChangeWin(INV_DOWNLOAD_MENU);	
	
}
//------------------------------------------------------------------------------------
//Ʊ�ι���
//------------------------------------------------------------------------------------
void CInvManageMenu::OnButton8(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}
	ChangeWin(INV_SEG_MENU);
}

int CInvManageMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	UINT8 ret;
	switch(iEvent) 
	{
	case RETURN_MAIN_MENU:
		ChangeWin(SYSTEM_MAIN_MENU);
		return SUCCESS;
		break;
		// 
		// 		case FORWARD_KEY:
		// 			return(ForwardKeyProc());
		// 			break;
		// 		
		// 		case BACKWARD_KEY:
		// 			ret = BackwardPaper();
		// 			if (ret != SUCCESS) 
		// 			{
		// 			   CaMsgBox::ShowMsg("��ֽ�ʷ�Ʊ!");
		// 			}
		// 			return SUCCESS;
		// 			break;
		
	default: break;
	}
	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

