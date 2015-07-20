/*! \file    InitEditWin.cpp
   \brief    awe4000r�����ʼ������
   \author   linzihao 
   \version  1.0
   \date     2015-05-22
 */


#include "InitEditWin.h"

#include "FiscalFun.h"

#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CInitEditWin::CInitEditWin():CaWindow()
{
	
	m_OldCertfPsw = "";
	m_NewCertfPsw = "";

	m_iBtnW = 0;
	m_iColW = 0;
	
}

CInitEditWin::~CInitEditWin()
{
	
}


int CInitEditWin::Create(int iX,int iY,int iW,int iH)
{
	int curH = 0;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;
  
	m_pFrame->RegsiterWin(this,INIT_EDIT_WIN);
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	
	//����һ��Input  ��һ��
	strcpy(title, "ԭ֤�����:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET;
	curH += (LINE_H - 6);
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(8);
	m_pInput1->m_InputType = CaInput::aPASSWORD; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;
	
	//����һ��Input  �ڶ���
	strcpy(title, "��֤�����:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(8);
	m_pInput2->m_InputType = CaInput::aPASSWORD; //�������ֻ��������ֵ
	m_pInput2->OnObject = S_OnInput2;

	//����һ��Input  �ڶ���
	strcpy(title, "�¿���ȷ��:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput3=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput3->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput3->SetTitle(title,titleLen / CHAR_W);	
	m_pInput3->SetMaxLen(8);
	m_pInput3->m_InputType = CaInput::aPASSWORD; //�������ֻ��������ֵ
	m_pInput3->OnObject = S_OnInput3;
	
	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;

	//����һ��Button  ������
	strcpy(title, "ȷ��");
	m_pBtn1 = new CaButton();
	curH += (LINE_H + 6);
	m_pBtn1->Create(leftoffset_btn,curH,m_iBtnW,WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;
	
	//����һ��Button  ������
	strcpy(title, "����");
	m_pBtn2 = new CaButton();
	m_pBtn2->Create(leftoffset_btn+m_iColW,curH,m_iBtnW,WORD_H); 
	m_pBtn2->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn2->SetTitle(title, strlen(title));
	m_pBtn2->BoxType(CaObject::BOX_NO);
	m_pBtn2->OnObject = S_OnButton2;

	OnActive = S_OnActive;
	
	this->End();  
	return 0;
}

int CInitEditWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  
		ChangeWin(FISCAL_MAIN_MENU);			
		return SUCCESS;
		break;
		
	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CInitEditWin::ReFresh()
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

void CInitEditWin::S_OnActive(CaWindow *obj)
{
	((CInitEditWin *)obj)->DoActive();
}

void CInitEditWin::DoActive()
{
	m_pInput1->Clear();//���Input�������
	m_pInput2->Clear();
	m_pInput3->Clear();
	
	m_OldCertfPsw = "";
	m_NewCertfPsw = "";

	ReFresh();	
}

void CInitEditWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInitEditWin *win=(CInitEditWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CInitEditWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInitEditWin *win=(CInitEditWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}

void CInitEditWin::S_OnInput3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInitEditWin *win=(CInitEditWin *)obj->GetdWin();
	win->OnInput3(iEvent,pEventData,iDataLen);
}

void CInitEditWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInitEditWin *win=(CInitEditWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CInitEditWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInitEditWin *win=(CInitEditWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void CInitEditWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CInitEditWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CInitEditWin::OnInput3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CInitEditWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	DBG_PRINT(("����InitEditWin::OnButton1����"));

	string strErr("");
	UINT8 ret = CheckInputValid();
	if (ret !=SUCCESS)
	{
		this->ReFresh();
		return;
	}

	ret = FSC_InitProc( m_OldCertfPsw, m_NewCertfPsw, strErr);
	
	if(ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return;
	}

	/**/
	DBG_PRINT(("�˳�InitEditWin::OnButton1����"));
	ChangeWin(FISCAL_MAIN_MENU);
}

void CInitEditWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(FISCAL_MAIN_MENU);	 //����˰�ص��˵�
}

UINT8 CInitEditWin::CheckInputValid(void)
{
	DBG_PRINT(("CInitEditWin::CheckInput begin"));
	
	UINT8 ret = SUCCESS;
	char *content1, *content2, *content3;
	INT32 tmp;

	content1 = (char*)(m_pInput1->m_contentBuf); 
	content2 = (char*)(m_pInput2->m_contentBuf);
	content3 = (char*)(m_pInput3->m_contentBuf);

	//δ����ԭ֤�����
	if (strlen(content1)==0)
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("������ԭ֤�����");
		return FAILURE;
	}
	//ԭ֤�����δ����λ
	if (strlen(content1)!=8)
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("ԭ֤��������");
		return FAILURE;
	}

	//δ������֤�����
	if (strlen(content2)==0)
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��������֤�����");
		return FAILURE;
	}
	//��֤�����δ����λ
	if (strlen(content2)!=8)
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��֤�����δ��8λ");
		return FAILURE;
	}

	//δ�����¿���
	if (strlen(content3)==0)
	{
		m_pInput3->SetFocus();
		CaMsgBox::ShowMsg("���ٴ�������֤�����");
		return FAILURE;
	}

	if (0 != strcmp(content2, content3))
	{
		m_pInput3->SetFocus();
		CaMsgBox::ShowMsg("���������¿��һ��");
		return FAILURE;
	}
	
	m_OldCertfPsw = content1;
	m_NewCertfPsw = content2;

	if (g_globalArg->m_strZskl != m_OldCertfPsw)
	{
		CaMsgBox::ShowMsg("�ɿ����������");
		return FAILURE;
	}
	DBG_PRINT(("��ѯ��֤�����ɹ�"));
	

	return SUCCESS;
}

