/*! \file    BasicReportMenu.cpp
   \brief    awe4000r�����ӡ�Ļ�����Ϣ�˵�
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */

#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "CMainFrame.h"
#include "CGlobalArg.h"
#include "BasicReportMenu.h"

CBasicReportMenu::CBasicReportMenu():CMultiBtnCommonWin(4)
{
}

int CBasicReportMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,BASIC_REPORT_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.������Ϣ");
	SetTitle(2,"B.��ҵ��Ϣ");
	SetTitle(3,"C.Ʊ����Ϣ");
	SetTitle(4,"D.˰����Ϣ");
	
	return 1;
}

void CBasicReportMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(MACHINE_INFO_WIN);	
}

void CBasicReportMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}
	ChangeWin(CORP_INFO_WIN);	
}

void CBasicReportMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strErr;

	if (g_globalArg->m_initFlag == 0)
	{
		strErr = "����δ��ʼ��";
		CaMsgBox::ShowMsg(strErr);
		return ;
	}
	ChangeWin(INV_KIND_INFO_WIN);		
}

void CBasicReportMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{

	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}
	ChangeWin(TAX_INFO_WIN);		
}


int CBasicReportMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (RETURN_MAIN_MENU == iEvent)
	 {	
		ChangeWin(REPORT_MAIN_MENU);
		return SUCCESS;
	 }
		
	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}




