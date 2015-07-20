#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "MultiBtnCommonWin.h"
#include "CGlobalArg.h"
#include "SysArgMenu.h"
#include "SysArgMac.h"

#include "PrintDriver.h"
#include "printer.h"
#include "MaintenanceFunc.h"


struct _Sys_Arg_info sys_arg_info[] = 
{
	{SYS_CUR_TEMPLATE_NO,	"��ǰģ����",		{""},				1, "1"}, 
	{SYS_DEFAULT_PAYER_NAME,"ȱʡ������",		{"����"},			1, "����"}, 
	{SYS_COM1_BAUD_RATE,	"����1������",			{"9600","38400","57600","115200"},		1, "9600"}, 
	{SYS_COM2_BAUD_RATE,	"����2������",			{"9600","38400","57600","115200"},		1, "9600"}, 
	{SYS_SALE_MODE,			"Ĭ�Ͽ������",		{"0-�ܼ�����","1-��ʱ������","2-��������"},  1, "2"},
//	{SYS_NEED_DECLARE_ALARM,"��Ʊ��ֹ���ڱ�������", {""},				1, "10"}, 
	{SYS_HW_TYPE,			"��д������",		{"0-����","1-����"},  1, "0"},
 	{SYS_BIDIRECTION_PRINT, "˫���ӡ����",		{""},				1, "0"}, 

};


CSysArgMenu::CSysArgMenu():CMultiBtnCommonWin(7)
{
	m_sysArg = new CSysArg;
	m_curSysarg_num = sizeof(sys_arg_info) / sizeof(struct _Sys_Arg_info);
	m_EditSysArgID = 0;

	m_pSysArgEditWin = (CSysArgEditWin *)(m_pFrame->GetWin(SYS_ARG_EDIT_WIN));
}

CSysArgMenu::~CSysArgMenu()
{
	if (m_sysArg != NULL)
	{
		delete m_sysArg;
		m_sysArg = NULL;
	}
}

//
int CSysArgMenu::Create(int iX,int iY,int iW,int iH)
{
	DBG_PRINT(("����CSysArgMenu::Create����"));
	
	int i;
	m_pFrame->RegsiterWin(this, SYSTEM_ARG_MENU);    
   
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	DBG_PRINT(("m_curSysarg_num == %d", m_curSysarg_num));
	for (i=0; i<m_curSysarg_num; i++)
	{
		SysArg_SetTitle(i+1, &(sys_arg_info[i]));
	}
	
	DBG_PRINT(("�˳�CSysArgMenu::Create����"));
	return 1;
}

//��ť1����ǰʹ��ģ����
void CSysArgMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_EditSysArgID = SYS_CUR_TEMPLATE_NO;
	m_pSysArgEditWin->ReFresh();
	ChangeWin(SYS_ARG_EDIT_WIN);
}

//��ť2��ȱʡ����������
void CSysArgMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{	
	m_EditSysArgID = SYS_DEFAULT_PAYER_NAME;
	m_pSysArgEditWin->ReFresh();
	ChangeWin(SYS_ARG_EDIT_WIN);
}

//��ť3������1������
void CSysArgMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_EditSysArgID = SYS_COM1_BAUD_RATE;
	m_pSysArgEditWin->ReFresh();
	ChangeWin(SYS_ARG_EDIT_WIN);
}

//��ť4������2������
void CSysArgMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_EditSysArgID = SYS_COM2_BAUD_RATE;
	m_pSysArgEditWin->ReFresh();
	ChangeWin(SYS_ARG_EDIT_WIN);
}

//��ť5��Ĭ�Ͽ�����۷�ʽ
void CSysArgMenu::OnButton5(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_EditSysArgID = SYS_SALE_MODE;
	m_pSysArgEditWin->ReFresh();
	ChangeWin(SYS_ARG_EDIT_WIN);
}
//��ť6����д���ͷ�ʽ
void CSysArgMenu::OnButton6(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_EditSysArgID = SYS_HW_TYPE;
	m_pSysArgEditWin->ReFresh();
	ChangeWin(SYS_ARG_EDIT_WIN);
}
//��ť7��˫���ӡ����
void CSysArgMenu::OnButton7(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strErr = "�Ƿ�����ֽ��ӡ��";
	if(YesNoMsBox(strErr)==SUCCESS)
	{
		if (isPaper() != 0)
		{ 
			CaMsgBox::ShowMsg("��ӡ��δ��⵽ֽ");
			return;
		}
		
		char chValue[256];
		
		UINT8 i =0;
		for(i=0;i<10;i++)
		{
			memset(chValue, 0, sizeof(chValue));
			DBG_PRINT(("i=%u", i));
			
			PrinterIni(i);
			sprintf(chValue, "˫���ӡ������ӡ:������Ϣ�����������쳣״̬ ����%u",i);
			//PrintStr(chValue);
			
			//PrintChineseLine(chValue, strlen(chValue));
			PrintAsciiLine(chValue, strlen(chValue));
			
			SetLineSpace(0);
			sprintf(chValue, "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH");
			//PrintChineseLine(chValue, strlen(chValue));
			PrintAsciiLine(chValue, strlen(chValue));
			sprintf(chValue, "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH");
			//PrintChineseLine(chValue, strlen(chValue));
			PrintAsciiLine(chValue, strlen(chValue));

			CarriageReturn();
		}	
		ForwardNLine(FORWARD_LINES);
	}
	
	m_EditSysArgID = SYS_BIDIRECTION_PRINT;
	m_pSysArgEditWin->ReFresh();
	ChangeWin(SYS_ARG_EDIT_WIN);
}

int CSysArgMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (RETURN_MAIN_MENU == iEvent)
	{
		ChangeWin(PROGRAM_CTRL_MAIN_MENU);
		return SUCCESS;
	}
	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

int CSysArgMenu::ReFresh()
{
	int i;
	for (i=0; i<m_curSysarg_num; i++)
	{
		SysArg_SetTitle(i+1, &(sys_arg_info[i]));
	}

	ReFreshTitle();
	CaGroup::ReFresh();
	if(m_pCurObj != NULL )
	{
 		m_pCurObj->SetFocusIn();
	}
	LCDRedraw();

	return 1;
}


int CSysArgMenu::ReadArgByID(int argID, string &strErr)
{
	DBG_PRINT(("����ReadArgByID����"));
	
	char value[30];
	int errorcode;

	memset(value,0,sizeof(value));
	sprintf(value, "WHERE SA_ID = %u", argID);
	m_sysArg->m_filter.append(value);
	m_sysArg->Requery();
	errorcode = m_sysArg->LoadOneRecord();
	DBG_PRINT(("errorcode = %u", errorcode));
	
	switch(errorcode)
	{
	case SQLITE_DONE:
		strErr = "���ݿ����޸ñ�ŵ�ϵͳ����";
		return FAILURE;
		break;

	case SQLITE_OK:
		break;

	default:
		strErr = "���ݿ��ѯ����";
		return FAILURE;
		break;
	}
	
	DBG_PRINT(("�˳�ReadArgByID����"));
	return SUCCESS;
}

void CSysArgMenu::SysArg_SetTitle(int num, struct _Sys_Arg_info *arg_info)
{
	DBG_PRINT(("����SysArg_SetTitle����"));
	
	char str_val[30], str_No[5];
	string title_string(""), errStr("");

	if (ReadArgByID(arg_info->id, errStr) != SUCCESS)
	{
		DBG_PRINT(("ReadArgByID����ִ��ʧ��"));
		//this->ShowMsg(errStr);
	}
	
	sprintf(str_No, "%u.", arg_info->id);
	
	title_string = str_No;
	title_string += arg_info->name;
	if (*(arg_info->item[0])!=0 && m_sysArg->m_vInt<5)
	{
		if (arg_info->id == SYS_DEFAULT_PAYER_NAME)
		{
			sprintf(str_val, "��%s", m_sysArg->m_vText.c_str());
		}
		else
		{
			sprintf(str_val, "��%s", arg_info->item[m_sysArg->m_vInt]);
		}
	}
	else
	{
		sprintf(str_val, "��%u", m_sysArg->m_vInt);
	}
	title_string += str_val;

	SetTitle(num, title_string.c_str());

	DBG_PRINT(("�˳�SysArg_SetTitle����"));

}
