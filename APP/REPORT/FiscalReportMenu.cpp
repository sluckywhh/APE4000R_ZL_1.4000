/*! \file    FiscalReportMenu.cpp
   \brief    awe4000r�����ӡ��˰����Ϣ�˵�
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */

#include "FiscalReportMenu.h"
#include "CaMsgBox.h"

CFiscalReportMenu::CFiscalReportMenu():CMultiBtnCommonWin(4)
{
}

int CFiscalReportMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,FISCAL_REPORT_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.ʱ��λ���");
	SetTitle(2,"B.��Ʊͳ��");
	SetTitle(3,"C.������ͳ��");
	SetTitle(4,"D.������ͳ��");

	return 1;
}

void CFiscalReportMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(TIME_SUM_DATE_WIN);
}


void CFiscalReportMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{

	ChangeWin(ISSUE_SUM_DATE_WIN);
}

void CFiscalReportMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{

	ChangeWin(DAY_SALE_SUM_WIN);
	
}

void CFiscalReportMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{

	ChangeWin(MONTH_SALE_SUM_WIN);
}


int CFiscalReportMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (RETURN_MAIN_MENU == iEvent)
	 {
		ChangeWin(REPORT_MAIN_MENU);
		return SUCCESS;
	 }
	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}




