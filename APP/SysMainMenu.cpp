#include "SysMainMenu.h"
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "MultiBtnCommonWin.h"
#include "CGlobalArg.h"
#include "TDateTime.h"
#include "SaleData.h"

//////////////////////////////////////////////////////
#include "ManageBusinessFunc.h"
#include "InvBusinessFunc.h"
#include "DeclareBusinessFunc.h"
#include "SaleBusinessFunc.h"
#include "YWXMLGY.h"
//////////////////////////////////////////////////////

CSysMainMenu::CSysMainMenu():CMultiBtnCommonWin(5)
{
}

int CSysMainMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,SYSTEM_MAIN_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.��Ʊ����");
	SetTitle(2,"B.��Ʊ����");
	SetTitle(3,"C.ϵͳ����");
	SetTitle(4,"D.�����ӡ");
	SetTitle(5,"E.˰�����");
	
	return 1;
}

void CSysMainMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
 	if (g_globalArg->m_operator->m_role!=DEMO_ROLE) 
 	{
 		//�ж�ϵͳ�������Ƿ������һ������
 		if (g_globalArg->m_initFlag == 0)//&&(g_globalArg->m_operator->m_role!=DEMO_ROLE))
 		{
 			DBG_PRINT(("����δ��ʼ��"));
 			CaMsgBox::ShowMsg("����δ��ʼ��");
 			return ;
 		}
		g_globalArg->m_curInvVol->ResetVol();
	
 	}
 	DBG_PRINT(("---****m_remain = %u", g_globalArg->m_curInvVol->m_remain));

	ChangeWin(PRODUCT_SALE_MAIN_MENU);	
	
}

void CSysMainMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_operator->m_role == DEMO_ROLE) 
	{
		CaMsgBox::ShowMsg("�޲���Ȩ��!");
		return;
	}
	ChangeWin(INV_MANAGE_MENU);	
}

void CSysMainMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_operator->m_role == DEMO_ROLE) 
	{
		CaMsgBox::ShowMsg("�޲���Ȩ��!");
		return;
	}
//	if (g_globalArg->m_operator->m_role == NORMAL_ROLE) 
//	{
//		CaMsgBox::ShowMsg("�޲���Ȩ��!");
//		return;
//	}
	ChangeWin(PROGRAM_CTRL_MAIN_MENU);		
}
void CSysMainMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_operator->m_role == DEMO_ROLE) 
	{
		CaMsgBox::ShowMsg("�޲���Ȩ��!");
		return;
	}
	if (g_globalArg->m_operator->m_role == NORMAL_ROLE) 
	{
		CaMsgBox::ShowMsg("�޲���Ȩ��!");
		return;
	}
	ChangeWin(REPORT_MAIN_MENU);
	
	
}
void CSysMainMenu::OnButton5(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_operator->m_role == DEMO_ROLE) 
	{
		CaMsgBox::ShowMsg("�޲���Ȩ��!");
		return;
	}
	ChangeWin(FISCAL_MAIN_MENU);	
}


int CSysMainMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{

	INT8 chValue[64];
	memset((void *)chValue,0x00,sizeof(chValue));
	UINT32 uServNum;
	string strErr("");

	if (ESC_KEY == iEvent || LOCKED_KEY == iEvent )
	{
		CaMsgBox msgBox("�˳���ǰ����Ա?",CaMsgBox::MB_YESNO);
		msgBox.ShowBox();	
		if (msgBox.m_iStatus == OK_PRESSED)
		{	
			g_globalArg->m_threadIn = 0;//�رմ��̵߳Ĵ��ϴ���Ʊ����
			ChangeWin(LOGIN_WIN);
			return SUCCESS;
		}
	}

	if(FIND_KEY == iEvent)
	{
		UINT8 ret= GetServNum(uServNum,strErr);
		if ( ret !=SUCCESS)
		{
			CaMsgBox::ShowMsg(strErr);
		}
		else
		{
			DBG_PRINT(("�������� uServNum= %u", uServNum));
			if (uServNum ==0)
			{
				sprintf(chValue, "�޴��ϴ���Ʊ��");
			}
			else
			{
				sprintf(chValue, " δ�ϴ���Ʊ����: %u", uServNum);
			}
			CaMsgBox::ShowMsg(chValue);
		}

		return SUCCESS;
	}
	

	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}


