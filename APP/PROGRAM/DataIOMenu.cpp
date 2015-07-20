/*! \file    DataIOMenu.cpp
   \brief    awe4000r���ݵ��뵼���˵�
   \author   Yu Yan
   \version  1.0
   \date     2008-8-13
 */


#include "DataIOMenu.h"
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "MultiBtnCommonWin.h"
#include "CGlobalArg.h"
#include "DataIOFunc.h"
#include "USBMount.h"
#include "SysArgMac.h"
#include "CSysArg.h"
#include "SysArgMenu.h"

CDataIOMenu::CDataIOMenu():CMultiBtnCommonWin(6,2)
{
}

int CDataIOMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,DATA_IO_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.ģ�嵼��");
	SetTitle(2,"B.ģ�嵼��");
	SetTitle(3,"C.��Ʒ����");
	SetTitle(4,"D.��Ʒ����");
	SetTitle(5,"E.�ͻ�����");
	SetTitle(6,"F.�ͻ�����");
	
	return 1;
}

void CDataIOMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 j=0, res;
	char tmp[64];
	string file_S = PRINT_TEMPLATE_FILE_NAME;
	string file_D = "/mnt/mb";
	string cmd = "";
	
	CaProgressBar proBar("");
	proBar.SetText("ģ�嵼����..."); 
	proBar.ReFresh();
	
	//����U��
	res = UsbDiskMount(NULL);
	if (SUCCESS != res)
	{
		DBG_PRINT(("����U��ʧ�� res = %u", res));
		CaMsgBox::ShowMsg("����U��ʧ��");
		UsbDiskUnMount();
		return;
	}
	
	//���ζ�ȡģ���ļ�����������UPAN
	system("/rw");
	for (j=0; j<PRINT_TEMPLATE_NUMBER; j++)
	{
		file_S = "/mnt/mb";
		file_D = PRINT_TEMPLATE_FILE_NAME;
		
		//��ȡ���Ϊj��ģ�壬��������û�ж�Ӧģ������ֹ����
		sprintf(tmp, "%02u.bin", j+1);
		file_S += tmp;
		
		sprintf(tmp, "%02u.txt", j+1);
		file_D += tmp;
		
		cmd = "cp " + file_S + " " + file_D;
		DBG_PRINT(("cmd: %s", cmd.c_str()));
		
		if (system(cmd.c_str()) != 0)
			break;
	}	
	
	UsbDiskUnMount();
	sprintf(tmp, "������%u��ģ��", j);
	CaMsgBox::ShowMsg(tmp);
	CGlobalArg::SysLog(EVENT_UPDATE_TEMPLATE, SUCCESS, tmp);
	// �����ж��������������ģ��Ϊ0����������1��ģ��Ϊ��ǰģ��
	if(0 != j)
	{
	//����1��ģ��Ϊ��ǰģ��
	INT32 errorcode;
	string sqlstr;
	CSysArg sysArg;
	
	g_globalArg->m_curTemplateNo = 1;
	
	//�޸�ϵͳ������
	sysArg.m_vInt = g_globalArg->m_curTemplateNo;
	sprintf(tmp, "update SYSARG set V_INT = %u where SA_ID = %d", 
		sysArg.m_vInt, SYS_CUR_TEMPLATE_NO );
	DBG_PRINT(("tmp = %s", tmp));
	sqlstr=tmp;
	sysArg.SetSQL(sqlstr);
	errorcode = sysArg.ExecuteSQL();
	if (errorcode != SQLITE_OK)
	{
		return;
	}
	g_globalArg->InitSysArg();
	
	CSysArgMenu *pWin;
	pWin = (CSysArgMenu *)(((CMainFrame *)m_pFrame)->IsWinExist(SYSTEM_ARG_MENU));
	if (pWin != NULL)
	{
		((CSysArgMenu *)(m_pFrame->GetWin(SYSTEM_ARG_MENU)))->ReFresh();
	}
	
	//����ǰģ�����ڴ�
	g_globalArg->ReadPrintTemplate(g_globalArg->m_templateBuffer, g_globalArg->m_curTemplateNo, PRINT_TEMPLATE_BUF_LEN);
	
	sprintf(tmp, "����ģ��%uΪ��ǰģ��", g_globalArg->m_curTemplateNo);
	CaMsgBox::ShowMsg(tmp);

	CaMsgBox::ShowMsg("���������,ʹ��ģ����Ч!");
	while (1)
	{
		;
	}
	}
	
}

void CDataIOMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 j=0, res;
	char tmp[64];
	string file_S = PRINT_TEMPLATE_FILE_NAME;
	string file_D = "/mnt/mb";
	string cmd = "";
	
	CaProgressBar proBar("");
	proBar.SetText("ģ�嵼����..."); 
	proBar.ReFresh();
	
	//����U��
	res = UsbDiskMount(NULL);
	if (SUCCESS != res)
	{
		DBG_PRINT(("����U��ʧ�� res = %u", res));
		CaMsgBox::ShowMsg("����U��ʧ��");
		UsbDiskUnMount();
		return;
	}
	
	//���ζ�ȡģ���ļ�����������UPAN 
	for (j=0; j<PRINT_TEMPLATE_NUMBER; j++)
	{
		file_S = PRINT_TEMPLATE_FILE_NAME;
		file_D = "/mnt/mb";
		
		//��ȡ���Ϊj��ģ�壬��������û�ж�Ӧģ������ֹ����
		sprintf(tmp, "%02u.txt", j+1);
		file_S += tmp;
		//	DBG_PRINT(("Template file: %s", file_S.c_str()));
		
		sprintf(tmp, "%02u.bin", j+1);
		file_D += tmp;
		//	DBG_PRINT(("USB file: %s", file_S.c_str()));
		
		cmd = "cp " + file_S + " " + file_D;
		DBG_PRINT(("cmd: %s", cmd.c_str()));
		
		if (system(cmd.c_str()) != 0)
			break;
	}	
	
	UsbDiskUnMount();
	sprintf(tmp, "������%u��ģ��", j);
	CaMsgBox::ShowMsg(tmp);
}

void CDataIOMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	CaMsgBox::ShowMsg("�����ȱ��ݵ����\n��Ʒ��Ϣ���ⶪʧ");
	UINT8 ret = DeptImportProc();
}
void CDataIOMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	DeptExportProc();
}

void CDataIOMenu::OnButton5(int iEvent, unsigned char * pEventData, int iDataLen)
{
	CaMsgBox::ShowMsg("�����ȱ��ݵ����\n�ͻ���Ϣ���ⶪʧ");
	UINT8 ret = ClientImportProc();
}
void CDataIOMenu::OnButton6(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ClientExportProc();
}


int CDataIOMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	UINT8 ret;
	switch(iEvent) 
	{
	case RETURN_MAIN_MENU:
		ChangeWin(PROGRAM_CTRL_MAIN_MENU);
		return SUCCESS;
		break;	
		
	default: break;
	}

	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}




