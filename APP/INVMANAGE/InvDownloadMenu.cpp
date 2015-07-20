
#include "InvDownloadMenu.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "CGlobalArg.h"

CInvDownloadMenu::CInvDownloadMenu():CMultiBtnCommonWin(2)
{
}

int CInvDownloadMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,INV_DOWNLOAD_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.����β�ѯ");
	SetTitle(2,"B.ʱ��β�ѯ");
	
	return 1;
}

//------------------------------------------------------------------------------------
//�������ƣ�����β�ѯ
//�������ܣ�
//�������ߣ�
//------------------------------------------------------------------------------------
void CInvDownloadMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{

	if(g_globalArg->m_curInvVol->m_remain==0)
	{
	//	CaMsgBox::ShowMsg("���ȵ��뷢Ʊ��");
	//	return ;
	}
	
	ChangeWin(INV_DOWNLOAD_NO_WIN);	
}

//------------------------------------------------------------------------------------
//�������ƣ�ʱ��β�ѯ
//�������ܣ�
//�������ߣ�
//------------------------------------------------------------------------------------
void CInvDownloadMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	
// 	if ((g_globalArg->m_InvServNum >= 1)&&
// 		(g_globalArg->m_operator->m_role!=DEMO_ROLE)) 
// 	{
// 		CaMsgBox::ShowMsg("��������ʧ�ܣ���ֹ��Ʊ");
// 		return;		
//  	}

	CaMsgBox::ShowMsg("�ݲ�֧��,�˹���");
	return;
	ChangeWin(INV_DOWNLOAD_DATE_WIN);
}


int CInvDownloadMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	UINT8 ret;
	switch(iEvent) 
	{
		case RETURN_MAIN_MENU:
			ChangeWin(INV_MANAGE_MENU);
			return SUCCESS;
			break;

		default: break;
	}
	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

