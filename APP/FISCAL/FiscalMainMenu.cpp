/*! \file    FiscalMainMenu.cpp
   \brief    ˰�ع������˵�
   \author   zl
   \version  1.0
   \date     2008-01-01
 */


#include "FiscalMainMenu.h"
#include "FiscalFun.h"
#include "CaProgressBar.h"
#include "CaMsgBox.h"
#include "InvVolFunc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "APIBase.h"
#include "YWXmlBase.h"

#if (TYPE_MODE == ZHQ_MODE)
CFiscalMenu::CFiscalMenu():CMultiBtnCommonWin(8, 2)
{

}
#else
CFiscalMenu::CFiscalMenu():CMultiBtnCommonWin(7,2)
{

}
#endif


int CFiscalMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,FISCAL_MAIN_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.�� ʼ ��");
	SetTitle(2,"B.Ȩ�޸���");
	SetTitle(3,"C.���ʳ���");
	SetTitle(4,"D.���糭��");
	SetTitle(5,"E.��˰�̿���");
	SetTitle(6,"F.��Ʊ�ϴ�");
	SetTitle(7,"G.��Ʊ��¼");
#if TYPE_MODE == ZHQ_MODE
	SetTitle(8,  "H.��������");
#endif

	return 1;
}

//��ʼ����ť
void CFiscalMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	DBG_PRINT(("����FiscalMainMenu::OnButton1����"));

	//linzihao edit
	if (g_globalArg->m_initFlag == 1)
	{
		CaMsgBox::ShowMsg("�����Ѿ���ʼ��");
		DBG_PRINT(("�˳�FiscalMainMenu::OnButton1����"));

		return ;
	}
	
	ChangeWin(INIT_EDIT_WIN);

	DBG_PRINT(("�˳�FiscalMainMenu::OnButton1����"));
	
	return;
}

//��Ϣ����
void CFiscalMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{	
	string strErr("");

	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		DBG_PRINT(("�˳�FiscalMainMenu::OnButton2����"));
		
		return ;
	}

	CaProgressBar proBar("Ȩ�޸�����...");
	proBar.Show();

	INT32 ret = g_pAPIBase->LXXXUpdatePro_API(*g_YwXmlArg, strErr);

	if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
	}
	else
	{
		ret =FSC_GetInvKindInfo(strErr);
		if (ret != SUCCESS)
		{
			CaMsgBox::ShowMsg(strErr);
			return;
		}

		CaMsgBox::ShowMsg("Ȩ�޸��³ɹ�");
	}
	DBG_PRINT(("�˳�FiscalMainMenu::OnButton2����"));
		return;

}

//���ʳ���
void CFiscalMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		DBG_PRINT(("�˳�FiscalMainMenu::OnButton3����"));
		
		return ;
	}
	
	ChangeWin(MEDIUM_DECLARE_MENU);

}

//���糭��
void CFiscalMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		DBG_PRINT(("�˳�FiscalMainMenu::OnButton4����"));
		
		return ;
	}
	
	ChangeWin(NET_DECLARE_MENU);
	
}

//��˰�̿������
void CFiscalMenu::OnButton5(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		DBG_PRINT(("�˳�FiscalMainMenu::OnButton5����"));
		
		return ;
	}
	
  ChangeWin(CHANGE_DISK_PSW_WIN);
}

//------------------------------------------------------------------------------------
//��Ʊ�ϴ�
//------------------------------------------------------------------------------------
void CFiscalMenu::OnButton6(int iEvent, unsigned char * pEventData, int iDataLen)
{
	
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}
	
	CaProgressBar proBar("��Ʊ�ϴ���...");
	proBar.Show();
	
	string strErr("");
	UINT8 ret=SUCCESS;
	
	ret = INV_InvoiceUpload(strErr);
	if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return ;
	}
	CaMsgBox::ShowMsg( "��Ʊ��ʼ�ϴ�");
	
	return;	
}

//��Ʊ��¼
void CFiscalMenu::OnButton7(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		DBG_PRINT(("�˳�FiscalMainMenu::OnButton7����"));
		
		return ;
	}
	
	ChangeWin(FPBL_WIN);
}

#if (TYPE_MODE == ZHQ_MODE)
//��������
void CFiscalMenu::OnButton8(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		DBG_PRINT(("�˳�FiscalMainMenu::OnButton5����"));
		
		return ;
	}

	ChangeWin(HQLXSJ_WIN);
}
#endif

int CFiscalMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (RETURN_MAIN_MENU == iEvent)
	{
		ChangeWin(SYSTEM_MAIN_MENU);
		return SUCCESS;
	}
	 
	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

