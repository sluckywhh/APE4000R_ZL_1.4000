#include <string.h>
#include "stdlib.h"
#include "SysMacDef.h"
#include "comdatatype.h"
#include "CaLabel.h"
#include "CaMsgBox.h"
#include "TDateTime.h"
#include "CaProgressBar.h"
#include "CaInput.h"
#include "CMainFrame.h"
#include "CGlobalArg.h"
#include "COperator.h"
#include "OperatorEditWin.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

COperatorEditWin::COperatorEditWin():CaWindow()
{
	m_Oper_edit = new COperator;
	m_isOperExist = false;
}

COperatorEditWin::~COperatorEditWin()
{
	if (m_Oper_edit != NULL)
	{
		delete m_Oper_edit;
		m_Oper_edit = NULL;
	}
}

int COperatorEditWin::Create(int iX,int iY,int iW,int iH)
{
	int curH, lineinterval, left_offset;
	int inputW, leftoffset_btn;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;
	m_pFrame->RegsiterWin(this, OPERATOR_EDIT_WIN);    
	CaWindow::Create(iX,iY,iW,iH); // creat a window

	curH = SCREEN_TOP_OFFSET;
	lineinterval = LINE_H;
	left_offset = SCREEN_LEFT_OFFSET+8;
	inputW = SCREEN_W - left_offset*2;

	strcpy(title, "Ա�����룺");
	titleLen = strlen(title) * CHAR_W + 1;
	m_pInput1=new CaInput(CaObject::ON_LEFT, titleLen);
	m_pInput1->Create(left_offset, curH, inputW+1, LINE_H);
	m_pInput1->SetTitle(title, titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(3);
	m_pInput1->m_InputType = CaInput::aINT;
	m_pInput1->OnObject = S_OnInput1;
	curH += lineinterval;

	strcpy(title, "Ա�����ƣ�");
	titleLen = strlen(title) * CHAR_W;
	m_pInput2=new CaInput(CaObject::ON_LEFT, titleLen);
	m_pInput2->Create(left_offset, curH, inputW, LINE_H);
	m_pInput2->SetTitle(title, titleLen / CHAR_W);	
 	m_pInput2->SetMaxLen(10);
	m_pInput2->OnObject = S_OnInput2;
	curH += lineinterval;
	
	strcpy(title, "Ա�����룺");
	titleLen = strlen(title) * CHAR_W + 1;
	m_pInput3=new CaInput(CaObject::ON_LEFT, titleLen);
	m_pInput3->Create(left_offset, curH, inputW+1, LINE_H);
	m_pInput3->SetTitle(title, titleLen / CHAR_W);	
	m_pInput3->SetMaxLen(6);
	m_pInput3->m_InputType = CaInput::aPASSWORD;
	m_pInput3->OnObject = S_OnInput3;
	curH += lineinterval;

	strcpy(title, "����ȷ�ϣ�");
	titleLen = strlen(title) * CHAR_W + 1;
	m_pInput4=new CaInput(CaObject::ON_LEFT, titleLen);
	m_pInput4->Create(left_offset, curH, inputW+1, LINE_H);
	m_pInput4->SetTitle(title, titleLen / CHAR_W);	
	m_pInput4->SetMaxLen(6);
	m_pInput4->m_InputType = CaInput::aPASSWORD;
	m_pInput4->OnObject = S_OnInput4;
	curH += lineinterval;
	
 	m_iBtnW = (SCREEN_W - 40)/3 - 4; 
 	m_iColW = (SCREEN_W - 40)/3; 
	leftoffset_btn = left_offset + 14;

	strcpy(title, "ȷ��");
	m_pBtn1 = new CaButton();
	m_pBtn1->Create(leftoffset_btn, curH, m_iBtnW, WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;
	
	strcpy(title, "ɾ��");
	m_pBtn2 = new CaButton();
	m_pBtn2->Create(leftoffset_btn+m_iColW, curH, m_iBtnW, WORD_H); 
	m_pBtn2->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn2->SetTitle(title, strlen(title));
	m_pBtn2->BoxType(CaObject::BOX_NO);
	m_pBtn2->OnObject = S_OnButton2;	

	strcpy(title, "����");
	m_pBtn3 = new CaButton();
	m_pBtn3->Create(leftoffset_btn+m_iColW*2, curH, m_iBtnW, WORD_H); 
	m_pBtn3->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn3->SetTitle(title, strlen(title));
	m_pBtn3->BoxType(CaObject::BOX_NO);
	m_pBtn3->OnObject = S_OnButton3;	

	OnActive = S_OnActive;
	
	this->End();
	return 0;
}

int COperatorEditWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU: 
		ClearOperatorWin();
		ChangeWin(PROGRAM_CTRL_MAIN_MENU);						
		return SUCCESS;
		break;		
	default: 
		break;		
	}
   return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}

bool COperatorEditWin::IsCurWin()
{
	return true;
}

int COperatorEditWin::ReFresh()
{
	ReFreshTitle();
	CaGroup::ReFresh();
	if(m_pCurObj != NULL )
	{
 		m_pCurObj->SetFocusIn();
	}
	LCDRedraw();

	return 1;
}


void COperatorEditWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	COperatorEditWin *win=(COperatorEditWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void COperatorEditWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	COperatorEditWin *win=(COperatorEditWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}

void COperatorEditWin::S_OnInput3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	COperatorEditWin *win=(COperatorEditWin *)obj->GetdWin();
	win->OnInput3(iEvent,pEventData,iDataLen);
}

void COperatorEditWin::S_OnInput4(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	COperatorEditWin *win=(COperatorEditWin *)obj->GetdWin();
	win->OnInput4(iEvent,pEventData,iDataLen);
}

void COperatorEditWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	COperatorEditWin *win=(COperatorEditWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void COperatorEditWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	COperatorEditWin *win=(COperatorEditWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void COperatorEditWin::S_OnButton3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	COperatorEditWin *win=(COperatorEditWin *)obj->GetdWin();
	win->OnButton3(iEvent,pEventData,iDataLen);
}

void COperatorEditWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{	
	m_pInput2->SetFocus();
}

void COperatorEditWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_pInput3->SetFocus();
}

void COperatorEditWin::OnInput3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_pInput4->SetFocus();
}

void COperatorEditWin::OnInput4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_pBtn1->SetFocus();
}

void COperatorEditWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	int errcode;
	string strErr;
	
	if (CheckInputValid(strErr) == FAILURE) 
	{
		CaMsgBox::ShowMsg(strErr);
		this->ReFresh();
		return ;
	}

	m_Oper_edit->m_opid = atoi((char *)(m_pInput1->m_contentBuf));
	m_Oper_edit->m_name = (char *)(m_pInput2->m_contentBuf);
	m_Oper_edit->m_passwd = (char *)(m_pInput3->m_contentBuf);
	m_Oper_edit->m_role = NORMAL_OPERATOR;

	string confirmPasswd = (char *)(m_pInput4->m_contentBuf);
	if (m_Oper_edit->m_passwd.compare(confirmPasswd) != 0)
	{	
		CaMsgBox::ShowMsg("����������ȷ�����룡");
		m_pInput4->SetFocus();
		ReFresh();
		return ;
	}
	
	if (m_isOperExist == false)
	{
		errcode = m_Oper_edit->AddNew();
		DBG_PRINT(("errorcode=%d", errcode));
		if (errcode == SQLITE_OK)
		{
			CGlobalArg::SysLog(EVENT_ADD_OPERATOR, SUCCESS);
			CaMsgBox::ShowMsg("��ƱԱ��ӳɹ�");
		}
		else
		{
			CaMsgBox::ShowMsg("��ƱԱ��Ӵ���");
		}
	}
	else
	{
		char sqlbuf[128];
		string sqlstr;	

		memset((void *)sqlbuf, 0, sizeof(sqlbuf));
		sprintf(sqlbuf, "update OPERATOR set NAME = '%s', PASSWD = '%s' where OP_ID = '%u'",
							m_Oper_edit->m_name.c_str(), m_Oper_edit->m_passwd.c_str(), 
							m_Oper_edit->m_opid );
		DBG_PRINT(("sqlbuf = %s", sqlbuf));
		sqlstr=sqlbuf;
		m_Oper_edit->SetSQL(sqlstr);
		errcode = m_Oper_edit->ExecuteSQL();
		if (errcode != SQLITE_OK)
		{
			strErr = "��ƱԱ�޸Ĵ���";			
			return ;
		}		

		CGlobalArg::SysLog(EVENT_EDIT_OPERATOR, SUCCESS);
		CaMsgBox::ShowMsg("��ƱԱ�޸ĳɹ�");

		 // ���µ�ǰ����Ա�󣬼�ʱ����ȫ�ֱ��� ����޸ĵĲ���Ա�ǵ�ǰ����Ա
		if (m_Oper_edit->m_opid == g_globalArg->m_operator->m_opid)
		{
			g_globalArg->m_operator->m_name = m_Oper_edit->m_name;  
			g_globalArg->m_operator->m_opid = m_Oper_edit->m_opid;
			//g_globalArg->m_operator->m_passwd = m_LoginOper->m_passwd;
	    	//g_globalArg->m_operator->m_role = m_LoginOper->m_role;
		}
	}

	ClearOperatorWin();
	ChangeWin(PROGRAM_CTRL_MAIN_MENU);
}

void COperatorEditWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	INT8 tmpstr[32];
	INT32 res;

	if (m_isOperExist == true)
	{
		m_Oper_edit->m_opid = atoi((INT8 *)m_pInput1->m_contentBuf);
		if( g_globalArg->m_operator->m_role == NORMAL_OPERATOR )
		{
			CaMsgBox::ShowMsg("��ͨ����Ա,��Ȩɾ��");
		}
		else if( (m_Oper_edit->m_opid == DIRECTOR_OPERATOR_ID) || (m_Oper_edit->m_opid == DEMO_OPERATOR_ID))
		{
			CaMsgBox::ShowMsg("�ÿ�ƱԱ����ɾ��");
		}
		else
		{
			sprintf(tmpstr, "WHERE OP_ID = '%u'", m_Oper_edit->m_opid);
			m_Oper_edit->m_filter.append(tmpstr);
			res = m_Oper_edit->Delete();
			if (res == SQLITE_OK)
			{
				CGlobalArg::SysLog(EVENT_DEL_OPERATOR, SUCCESS);
				CaMsgBox::ShowMsg("ɾ���ɹ�");
			}
			else
			{
				CaMsgBox::ShowMsg("ɾ��ʧ��");
			}
		}
	}
	else
	{
		CaMsgBox::ShowMsg("�޴˿�ƱԱ��Ϣ");
	}
	
	ClearOperatorWin();
	ChangeWin(PROGRAM_CTRL_MAIN_MENU);
}

void COperatorEditWin::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ClearOperatorWin();
	ChangeWin(PROGRAM_CTRL_MAIN_MENU);
}

UINT8 COperatorEditWin::CheckInputValid(string &strErr)
{	
	//����Ա����Ƿ�������ȷ
	if (m_pInput1->IsEmpty())
	{	
		strErr = "δ���뿪ƱԱ����";
		m_pInput1->SetFocus();
		return FAILURE;
	}

	//����Ա�����Ƿ�������ȷ
	if (m_pInput2->IsEmpty())
	{	
		strErr = "δ���뿪ƱԱ����";
		m_pInput2->SetFocus();
		return FAILURE;
	}

	//����Ա�����Ƿ�������ȷ
	if (m_pInput3->IsEmpty())
	{	
		strErr = "δ���뿪ƱԱ����";
		m_pInput3->SetFocus();
		return FAILURE;
	}

	return SUCCESS;
}

void COperatorEditWin::DispOperatorInfo(COperator *oper)
{
	INT8 tempstr[10];
	
	sprintf(tempstr, "%03u", oper->m_opid);
	m_pInput1->SetContentBuf((UINT8 *)tempstr, strlen(tempstr));

	m_pInput2->SetContentBuf((UINT8 *)oper->m_name.c_str(), oper->m_name.length());
	
	m_pInput3->SetContentBuf((UINT8 *)oper->m_passwd.c_str(), oper->m_passwd.length());

	m_pInput4->SetContentBuf((UINT8 *)oper->m_passwd.c_str(), oper->m_passwd.length());

	m_pBtn2->SetFocus();

}

void COperatorEditWin::ClearOperatorWin()
{
	m_pInput1->Clear();
	m_pInput2->Clear();
	m_pInput3->Clear();
	m_pInput4->Clear();
}

void COperatorEditWin::S_OnActive(CaWindow *obj)
{
	((COperatorEditWin *)obj)->DoActive();
}
void COperatorEditWin::DoActive()
{
	INT8 editFlag = 0;
	UINT8 errorcode;
	UINT32 OperNo;
	INT32 status;
	INT8 tmpStr[32];

	DBG_ENTER("COperatorEditWin::DoActive()");
	ReFresh();

	CaMsgBox msgBox("��ƱԱ����:",CaMsgBox::MB_INPUT);
	msgBox.SetInputType(CaInput::aINT);
	msgBox.SetMaxInputLen(3);
	while (1)
	{
		string tmpNo("");
		msgBox.ShowBox();
		status = msgBox.m_iStatus;
		if (status != OK_PRESSED)
		{
			break;
		}
		tmpNo = (INT8 *)msgBox.GetInputContent();
		if (tmpNo == "")
		{
			CaMsgBox::ShowMsg("�����뿪ƱԱ����");
			continue;
		}
		if (tmpNo.length() < 3) 
		{
			CaMsgBox::ShowMsg("��ƱԱ���볤������3λ");
			continue;
		}

		OperNo = atoi(tmpNo.c_str());
		if (OperNo > 99)
		{
			CaMsgBox::ShowMsg("��ƱԱ��ŷǷ�");
			continue;
		}
		else if( g_globalArg->m_operator->m_role != DIRECTOR_ROLE &&
				 g_globalArg->m_operator->m_opid != OperNo )
		{
			CaMsgBox::ShowMsg("��ֹ�༭������ƱԱ��Ϣ");
			continue;
		}

		break;
	}

	if (status == OK_PRESSED)
	{
		sprintf(tmpStr, "WHERE OP_ID = %u", OperNo);
		m_Oper_edit->m_filter.append(tmpStr);
		m_Oper_edit->Requery();
		errorcode = m_Oper_edit->LoadOneRecord();
		DBG_PRINT(("errorcode = %u", errorcode));
		
		switch(errorcode)
		{
		case SQLITE_DONE:
			{
				CaMsgBox msgBox("�޴˿�ƱԱ,�Ƿ����?", CaMsgBox::MB_YESNO);
				msgBox.ShowBox();
				if (msgBox.m_iStatus == OK_PRESSED)
				{
					sprintf(tmpStr, "%03u", OperNo);
					m_pInput1->SetContentBuf((UINT8 *)tmpStr, strlen(tmpStr));
					m_isOperExist = false;		
					editFlag = 1;
				}
				else
				{
					editFlag = 0;
				}
			}
			break;
			
		case SQLITE_OK:
			DispOperatorInfo(m_Oper_edit);
			m_isOperExist = true;
			editFlag = 1;
			break;

		default:
			CaMsgBox::ShowMsg("��ƱԱ��Ϣ�����");
			editFlag = 0;
			break;
		}
	}
	else
	{
		editFlag = 0;
	}
	
	
	if (editFlag == 1)
	{
		m_pInput2->SetFocus();
		m_pInput1->m_bReadOnly = true;
		ReFresh(); 
	}
	else
	{
		m_pInput1->m_bReadOnly = false;
		ClearOperatorWin();
		ChangeWin(PROGRAM_CTRL_MAIN_MENU);
	}
}
