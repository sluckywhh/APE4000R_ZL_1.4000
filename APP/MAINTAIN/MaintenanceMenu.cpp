/*! \file    MaintenanceMenu.cpp
   \brief    awe4000r���۳�����ϵͳά�����˵�
   \author   Yu Yan
   \version  1.0
   \date     2008-3-19 
 */

#include "MaintenanceMenu.h"
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "MultiBtnCommonWin.h"
#include "CGlobalArg.h"
#include "CInvServ.h"

CMaintenanceMenu::CMaintenanceMenu():CMultiBtnCommonWin(9, 2)
{
}

int CMaintenanceMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,MAINTENANCE_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.�����Լ�");
	SetTitle(2,"B.�������");
	SetTitle(3,"C.�޸�ʱ��");
	SetTitle(4,"D.��������");
	SetTitle(5,"E.�������");
	SetTitle(6,"F.�޸�����");
	//SetTitle(7,"G.���µ�ǰ��");
//	SetTitle(8,"H.��������");
//	SetTitle(9,"I.�������");
// 	SetTitle(10,"J.ɾ������");
	SetTitle(7,"G.��������");
	SetTitle(8,"H.�������");
	SetTitle(9,"I.ɾ������");
	//SetTitle(9,"I.APDU���");
	
	return 1;
}

//�����Լ�
void CMaintenanceMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{	
	ChangeWin(SELF_TEST_MENU);
	
}

//�������
void CMaintenanceMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strErr;
	//�ж�ϵͳ�������Ƿ������һ������

	strErr = "�Ƿ���⣿";

	if(YesNoMsBox(strErr)==FAILURE)
	{
		return;
	}
	else
	{
		ChangeWin(CLEAR_DEPOT_WIN);
		return;
	}
}

//�޸�ʱ��
void CMaintenanceMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(CHANGE_DATETIME_WIN);		
}

//��������
void CMaintenanceMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{
/*	string strErr;
	//�ж�ϵͳ�������Ƿ������һ������

	strErr = "�Ƿ����ػ������룿";

	if(YesNoMsBox(strErr)==FAILURE)
	{
		return;
	}
	else
	{
		//���ػ�������
		if(DownloadFCRCode()==FAILURE)
		{
			CaMsgBox::ShowMsg("���ػ�������ʧ��");
		}
		else
		{
			CaMsgBox::ShowMsg("���ػ�������ɹ�");
		}
		this->ReFresh();
		return;
	} */
		string strErr;
	//�ж�ϵͳ�������Ƿ������һ������
	CaProgressBar proBar("");
	strErr = "���ػ��������MAC?";

	if(YesNoMsBox(strErr)==FAILURE)
	{
		return;
	}
	else
	{
		//���ػ�������
		if(DownloadFCRCode()==FAILURE)
		{
			CaMsgBox::ShowMsg("���ػ�������ʧ��");
			this->ReFresh();
     		return;
		}
		else
		{
		//	CaMsgBox::ShowMsg("���ػ�������ɹ�");
			CaProgressBar proBar("");
			proBar.SetText("���ػ�������ɹ�");
	        proBar.ReFresh();
		}
//		this->ReFresh();
//		return;
	}
	

	DBG_PRINT(("����Mac!"));
	UINT8 nRet = SUCCESS;
	
	INT8 m_MAC[MAC_LEN];//���mac��ַ by yy 20120524
	memset(m_MAC, 0, sizeof(m_MAC));
	nRet = DownloadMAC(m_MAC, MAC_LEN);
	if(SUCCESS != nRet)
	{
		return;
	}
    proBar.SetText("���سɹ�,������");
	proBar.Show();
	while(1);
	return;

	
}

//�������
void CMaintenanceMenu::OnButton5(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(SYSTEM_UPGRADE_WIN);	
}


//�޸�����
void CMaintenanceMenu::OnButton6(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(PASSWD_EDIT_WIN);	
}

//void CMaintenanceMenu::OnButton7(int iEvent, unsigned char * pEventData, int iDataLen)
//{
//	string strErr = "";
//
//	DBG_PRINT(("g_globalArg->m_curInvVol->m_ieno = %u", g_globalArg->m_curInvVol->m_ieno));
//	DBG_PRINT(("g_globalArg->m_curInvVol->m_remain = %u", g_globalArg->m_curInvVol->m_remain));
//	INT32 nOldCurNo = g_globalArg->m_curInvVol->m_ieno + 1 - 
//		g_globalArg->m_curInvVol->m_remain;
//	DBG_PRINT(("g_globalArg->m_curInvVol->m_ieno = %u", nOldCurNo));
//
//	if (g_globalArg->m_initFlag == 0)
//	{
//		strErr = "����δ��ʼ��";
//		CaMsgBox::ShowMsg(strErr);
//		return ;
//	}
//
//	string strInvNo("");
//	INT32 status;
//	INT8 tmpstr[128];
//	UINT32 curInvNo;
//	CInvVol invVol;
//
//	DBG_ENTER("CDeptEditWin::DoActive()");
//	ReFresh();
//
//	CaMsgBox msgBox("�µ�ǰ��:",CaMsgBox::MB_INPUT);
//	msgBox.SetInputType(CaInput::aINT);
//	msgBox.SetMaxInputLen(8);
//	while (1)
//	{
//		msgBox.ShowBox();
//		status = msgBox.m_iStatus;
//		strInvNo = (INT8 *)msgBox.GetInputContent();
//		if (status != OK_PRESSED || strInvNo != "")
//			break;
//
//		CaMsgBox::ShowMsg("��������Ч��Ʊ��");
//	}
//
//	if (status == OK_PRESSED)
//	{
//		curInvNo  = atoi(strInvNo.c_str());
//		DBG_PRINT(("curInvNo = %u", curInvNo));
//
//		if (curInvNo <= 0)
//		{
//			CaMsgBox::ShowMsg("��ǰ��Ʊ�ű������0");
//			this->ReFresh();
//			return;
//		}
//
//		DBG_PRINT(("m_InvStartNo = %u", g_globalArg->m_curInvVol->m_isno));
//		DBG_PRINT(("m_InvEndNo = %u", g_globalArg->m_curInvVol->m_ieno));
////		if((curInvNo < g_globalArg->m_curInvVol->m_InvStartNo)||
////			((curInvNo - g_globalArg->m_curInvVol->m_InvStartNo) >= MAX_INV_VOL_NUM))
//		if( curInvNo < g_globalArg->m_curInvVol->m_isno || 
//			curInvNo > g_globalArg->m_curInvVol->m_ieno)
//		{
//			CaMsgBox::ShowMsg("��ǰ��Ʊ�ű������ڵ�ǰ��");
//			this->ReFresh();
//			return;
//		}
//
//		DBG_PRINT(("nOldCurNo = u%", nOldCurNo));
//    	DBG_PRINT(("curInvNo = u%", curInvNo));
//		if (curInvNo <= nOldCurNo)
//		{
//			CaMsgBox::ShowMsg("������ǰ����");
//			this->ReFresh();
//			return;
//		}
//
//		//����INV_VOL�еĵ�ǰ����Ϣ
//		string sqlstr= "";
//		INT32 errcode;
//		UINT32 nRemain = g_globalArg->m_curInvVol->m_ieno - curInvNo + 1;
//		
//		sprintf(tmpstr,"update INV_VOL set REMAIN = %u where CODE = '%s' and IS_NO = %u",
//			nRemain, g_globalArg->m_curInvVol->m_code.c_str(), 
//			g_globalArg->m_curInvVol->m_isno);
//		sqlstr=tmpstr;
//		invVol.SetSQL(sqlstr);
//		errcode = invVol.ExecuteSQL();
//		if (invVol.ExecuteSQL() != SQLITE_OK)
//		{
//			DBG_PRINT(("���µ�ǰ��Ʊ�Ŵ��� errcode=%d", errcode));
//			CaMsgBox::ShowMsg("���µ�ǰ��Ʊ��ʧ��");
//			return;
//		}
//		g_globalArg->m_curInvVol->m_remain = nRemain;
//		CaMsgBox::ShowMsg("���µ�ǰ��Ʊ�ųɹ�");		
//	}
//}
void CMaintenanceMenu::OnButton7(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strMsg("");
	COperator oper;
	INT8 chValue[64];
	memset((void*)chValue, 0, sizeof(chValue));
	
	sprintf(chValue, "where ROLE = %u", DIRECTOR_ROLE);
	oper.m_filter = chValue;
	oper.Requery();
	INT32 errcode = oper.LoadOneRecord();
	if (SQLITE_DONE == errcode)
	{
		strMsg = "������Ա��";
	}
	else if (SQLITE_OK == errcode)
	{
		sprintf(chValue, "���룺%s", oper.m_passwd.c_str());
		strMsg = chValue;		
	}
	else
	{
		strMsg = "��ѯ����Ա��ʧ��";	
	}
	CaMsgBox::ShowMsg(strMsg);
	
}

void CMaintenanceMenu::OnButton8(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(NET_SERV_MENU);	
}

void CMaintenanceMenu::OnButton9(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("����δ��ʼ��");
		return ;
	}

	CInvServ invServ;
	CInvHead invHead;
	CInvDet  invDet;
	INT32 nErrCode;
	INT8 chValue[128];

	invServ.Requery();
	nErrCode = invServ.LoadOneRecord();
   DBG_PRINT(("nErrCode= %u",nErrCode));
	if( nErrCode != SQLITE_OK )
	{
		CaMsgBox::ShowMsg("�޻����¼");
		return;
	}

	memset(chValue, 0, sizeof(chValue));
	sprintf(chValue,"����:%s ����:%u ȷ��ɾ��?", invServ.m_code.c_str(), invServ.m_InvNo);
	CaMsgBox msgBox(chValue,CaMsgBox::MB_YESNO);
	msgBox.ShowBox();	
	if (msgBox.m_iStatus == OK_PRESSED)
	{
		memset((void*)chValue, 0, sizeof(chValue));
		//sprintf(chValue, "where CODE = '%s' and INV_NO = %u", invServ.m_code.c_str(), invServ.m_InvNo);
		// ����inv_serv�е������ֶ�
		sprintf(chValue, "where FPDM = '%s' and FPHM = %u", invServ.m_code.c_str(), invServ.m_InvNo);
		invHead.m_filter = chValue;
		nErrCode = invHead.Delete();
		if (SQLITE_OK != nErrCode)
		{
			CaMsgBox::ShowMsg("ɾ��ʧ��");
			return;
		}
		invDet.m_filter = chValue;
		nErrCode = invDet.Delete();
		if (SQLITE_OK != nErrCode)
		{
			CaMsgBox::ShowMsg("ɾ��ʧ��");
			return;
		}
		
		sprintf(chValue, "where CODE = '%s' and INV_NO = %u", invServ.m_code.c_str(), invServ.m_InvNo);
		invServ.m_filter = chValue;
		nErrCode = invServ.Delete();
		if (SQLITE_OK != nErrCode)
		{
	
			CaMsgBox::ShowMsg("ɾ��ʧ��");
			return;
		}
		CaMsgBox::ShowMsg("ɾ���ɹ�");

		if(0 != g_globalArg->m_InvServNum)
		{
			g_globalArg->m_InvServNum--;
		}
		DBG_PRINT(("m_InvServNum = %u", g_globalArg->m_InvServNum ));
	}
}

int CMaintenanceMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (LOCKED_KEY == iEvent || ESC_KEY == iEvent)
	{
		CaMsgBox msgBox("�˳���ǰ����Ա?",CaMsgBox::MB_YESNO);
		msgBox.ShowBox();	
		if (msgBox.m_iStatus == OK_PRESSED)
		{	
			ChangeWin(LOGIN_WIN);
			return SUCCESS;
		}
	}

#if (0 == RELEASE_VER)
	CInvServ invServ;
	INT32 nErrCode;
	INT8 chValue[64];
	memset((void*)chValue, 0, sizeof(chValue));
	if(DISCOUNT_KEY == iEvent)
	{
		invServ.Requery();
		invServ.LoadOneRecord();

		sprintf(chValue, "where no = %u", invServ.m_no);
		invServ.m_filter = chValue;
		nErrCode = invServ.Delete();
		if (SQLITE_OK != nErrCode)
		{
			CaMsgBox::ShowMsg("ɾ����һ��ʧ��");
			return FAILURE;
		}
		CaMsgBox::ShowMsg("ɾ����һ���ɹ�");
		
		if(0 != g_globalArg->m_InvServNum)
		{
          g_globalArg->m_InvServNum--;
		}
		DBG_PRINT(("m_InvServNum = %u", g_globalArg->m_InvServNum ));
		return SUCCESS;
	}

#endif

	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

