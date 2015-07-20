/*! \file    CommerceReportMenu.cpp
   \brief    awe4000r�����ӡ����ҵͳ�Ʋ˵�
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */

#include "CommerceReportMenu.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "CGlobalArg.h"
#include "ReportFunc.h"
#include "PrintDriver.h"

#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"

CCommerceReportMenu::CCommerceReportMenu():CMultiBtnCommonWin(3)
{
}

int CCommerceReportMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,COMMERCE_REPORT_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.��Ʒ��Ϣ");
	SetTitle(2,"B.�ͻ���Ϣ");
	SetTitle(3,"C.����Ա��Ϣ");

	return 1;
}

void CCommerceReportMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
 	string strErr;
	if (g_globalArg->m_initFlag == 0)
	{
		strErr = "����δ��ʼ��";
		CaMsgBox::ShowMsg(strErr);
		return ;
	}
	PrnDept();
}

void CCommerceReportMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strErr;

	if (g_globalArg->m_initFlag == 0)
	{
		strErr = "����δ��ʼ��";
		CaMsgBox::ShowMsg(strErr);
		return ;
	}
	PrnClient();
}

void CCommerceReportMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strErr;

	if (g_globalArg->m_initFlag == 0)
	{
		strErr = "����δ��ʼ��";
		CaMsgBox::ShowMsg(strErr);
		return ;
	}
	PrnOperator();
}


int CCommerceReportMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (RETURN_MAIN_MENU == iEvent)
	 {	
		ChangeWin(REPORT_MAIN_MENU);
		return SUCCESS;
	 }
		
	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

UINT8 CCommerceReportMenu::PrnClient()
{
	UINT8 ret;

	//��ѯ�Ƿ��пͻ���¼
	CClient client;
	client.Requery();
	INT32 errorcode = client.LoadOneRecord();
	if (errorcode == SQLITE_DONE) 
	{
		CaMsgBox::ShowMsg("û�пͻ���Ϣ");
		return SUCCESS;
	}
	else if (errorcode != SQLITE_OK) 
	{
		CaMsgBox::ShowMsg("��ѯ�ͻ���Ϣʧ��");
		return FAILURE;
	}
	
	//��ֽ���
	ret = YesNoMsgBox("������ֽ���Ƿ��ӡ��");
	if (ret==FAILURE)
	{
		return SUCCESS;//����ӡ
	}
	if (isPaper() != 0)
	{	
		CaMsgBox::ShowMsg("��ӡ��δ��⵽ֽ");
		return FAILURE;
	}

	CaProgressBar proBar("�ͻ���Ϣ��ӡ��.....");

	//��ӡ����ͷ
	PrnClientHead();

	//�����¼��ӡ��ϸ
	client.Requery();
	errorcode = client.MoveFirst();
	while (errorcode == SQLITE_ROW)
	{
		PrnClientDetail(&client);			    	     
		errorcode = client.MoveNext();
	}
	client.MoveEnd(); 
	ForwardNLine(FORWARD_LINES);

	if (errorcode==SQLITE_DONE) 
	{		
		return SUCCESS;
	}
	DBG_PRINT(("��ѯ�ͻ���Ϣ����errorcode = %d", errorcode));	
	return FAILURE;	
}

UINT8 CCommerceReportMenu::PrnDept()
{
	UINT8 ret;

	//��ѯ�Ƿ���PLU��¼
	CDept dept;
	dept.Requery();
	INT32 errorcode = dept.LoadOneRecord();
	if (errorcode == SQLITE_DONE) 
	{
		CaMsgBox::ShowMsg("û����Ʒ��Ϣ");
		return SUCCESS;
	}
	else if (errorcode != SQLITE_OK) 
	{
		CaMsgBox::ShowMsg("��ѯ��Ʒ��Ϣʧ��");
		return FAILURE;
	}
	
	//��ֽ���
	ret = YesNoMsgBox("������ֽ���Ƿ��ӡ��");
	if (ret==FAILURE)
	{
		return SUCCESS;//����ӡ
	}
	if (isPaper() != 0)
	{	
		CaMsgBox::ShowMsg("��ӡ��δ��⵽ֽ");
		return FAILURE;
	}

	CaProgressBar proBar("��Ʒ��Ϣ��ӡ��.....");

	//��ӡ����ͷ
	PrnDeptHead();

	//�����¼��ӡ��ϸ
	dept.Requery();
	errorcode = dept.MoveFirst();
	while (errorcode == SQLITE_ROW)
	{
		PrnDeptDetail(&dept);			    	     
		errorcode = dept.MoveNext();
	}
	dept.MoveEnd(); 
	ForwardNLine(FORWARD_LINES);

	if (errorcode==SQLITE_DONE) 
	{		
		return SUCCESS;
	}
	DBG_PRINT(("��ѯ��Ʒ��Ϣ����errorcode = %d", errorcode));	
	return FAILURE;	
}

UINT8 CCommerceReportMenu::PrnOperator()
{
	UINT8 ret;

	//��ѯ�Ƿ��в���Ա��¼
	COperator oper;
	oper.Requery();
	INT32 errorcode = oper.LoadOneRecord();
	if (errorcode == SQLITE_DONE) 
	{
		CaMsgBox::ShowMsg("û��Ա����Ϣ");
		return SUCCESS;
	}
	else if (errorcode != SQLITE_OK) 
	{
		CaMsgBox::ShowMsg("��ѯԱ����Ϣʧ��");
		return FAILURE;
	}
	
	//��ֽ���
	ret = YesNoMsgBox("������ֽ���Ƿ��ӡ��");
	if (ret==FAILURE)
	{
		return SUCCESS;//����ӡ
	}
	if (isPaper() != 0)
	{	
		CaMsgBox::ShowMsg("��ӡ��δ��⵽ֽ");
		return FAILURE;
	}

	CaProgressBar proBar("Ա����Ϣ��ӡ��.....");

	//��ӡ����ͷ
	PrnOperatorHead();

	//�����¼��ӡ��ϸ
	oper.Requery();
	errorcode = oper.MoveFirst();
	while (errorcode == SQLITE_ROW)
	{
		//����ϵͳ����Ա�����ӡ
		if (SYSTEM_ADMINISTRATOR != oper.m_role) 
		{
			PrnOperatorDetail(&oper);	

		}			    	     
		errorcode = oper.MoveNext();
	}
	oper.MoveEnd(); 
	ForwardNLine(FORWARD_LINES);

	if (errorcode==SQLITE_DONE) 
	{		
		return SUCCESS;
	}
	DBG_PRINT(("��ѯԱ����Ϣ����errorcode = %d", errorcode));	
	return FAILURE;	 
}
