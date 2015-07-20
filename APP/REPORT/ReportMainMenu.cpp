/*! \file    ReportMainMenu.cpp
   \brief    awe4000r�����ӡ�����˵�
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */


#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "MultiBtnCommonWin.h"
#include "CMainFrame.h"
#include "CGlobalArg.h"
#include "SaleFunc.h"
#include "ReportMainMenu.h"

CReportMainMenu::CReportMainMenu():CMultiBtnCommonWin(4)
{
}

int CReportMainMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,REPORT_MAIN_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.������Ϣ");
	SetTitle(2,"B.��ҵͳ��");
    SetTitle(3,"C.˰��ͳ��");
	SetTitle(4,"D.ϵͳ��־");

	
	return 1;
}

void CReportMainMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(BASIC_REPORT_MENU);	

}

void CReportMainMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strErr;
	
	if (g_globalArg->m_initFlag == 0)
	{
		strErr = "����δ��ʼ��";
		CaMsgBox::ShowMsg(strErr);
		return ;
	}

	ChangeWin(COMMERCE_REPORT_MENU);	
}

void CReportMainMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}
   ChangeWin(FISCAL_REPORT_MENU);
}
void CReportMainMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{	
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}

	ChangeWin(SYS_LOG_DATE_WIN);		
}


int CReportMainMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	UINT8 ret;
	switch(iEvent) 
	{
	case RETURN_MAIN_MENU:
		ChangeWin(SYSTEM_MAIN_MENU);
		return SUCCESS;
		break;

	case FORWARD_KEY:
			return(ForwardKeyProc());
			break;
		
	case BACKWARD_KEY:
			ret = BackwardPaper();
			if (ret != SUCCESS) 
			{
			   CaMsgBox::ShowMsg("��ֽ�ʷ�Ʊ!");
			}
			return SUCCESS;
			break;

	default: break;
	}

	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}


UINT8 CReportMainMenu::ForwardKeyProc()
{
	UINT8 ret;
	
		ret = NoMarkForwardPaper();
		if (ret != SUCCESS) 
		{
		   CaMsgBox::ShowMsg("��ֽ�ʷ�Ʊ!");
			return FAILURE;
		}		

	ReFresh();
	return SUCCESS;
}

