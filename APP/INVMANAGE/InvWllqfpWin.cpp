/*! \file    InvWllqfpWin.cpp
   \brief    awe4000r������ȡ��Ʊ����
   \author   lzh
   \version  1.0
   \date     2015-06-03
 */
#include "InvWllqfpWin.h"
#include "CaLabel.h"
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include <string.h>
#include "stdlib.h"
#include "InvVolFunc.h" 
#include "SysMacDef.h"
#include "CGlobalArg.h"


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CInvWllqfpWin::CInvWllqfpWin():CaWindow()
{
	m_invCode = "";
	m_invStartNo = 0;
	m_invNum = 0;
}

int CInvWllqfpWin::Create(int iX,int iY,int iW,int iH)
{
	int curH = 0;
	char title[OBJ_TITLE_MAX_LEN + 1];

    int titleLen = 0;
	m_pFrame->RegsiterWin(this,INV_WLLQFP_WIN);    
	CaWindow::Create(iX,iY,iW,iH); // creat a window

	curH = SCREEN_TOP_OFFSET;
	m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�


	//����һ��Input  ��һ��
	strcpy(title, "��Ʊ����:");
	titleLen = strlen(title) * CHAR_W;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(12);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ��������ֵ
	m_pInput1->OnObject = S_OnInput1;

	strcpy(title, "��ʼ����:");
	titleLen = strlen(title) * CHAR_W;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	curH += LINE_H;
	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);
	m_pInput2->SetMaxLen(8);
    m_pInput2->OnObject = S_OnInput2;
	m_pInput2->m_InputType = m_pInput2->aINT; //�������ֻ��������ֵ

	strcpy(title, "��Ʊ����:");
	titleLen = strlen(title) * CHAR_W;
	m_pInput3=new CaInput(CaObject::ON_LEFT,titleLen);
	curH += LINE_H;
	m_pInput3->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput3->SetTitle(title,titleLen / CHAR_W);
	m_pInput3->SetMaxLen(4);
    m_pInput3->OnObject = S_OnInput3;
	m_pInput3->m_InputType = m_pInput3->aINT; //�������ֻ��������ֵ

	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	
	strcpy(title, "��ȡ");
	m_pBtn1 = new CaButton();
	curH += 2*LINE_H;
	m_pBtn1->Create(leftoffset_btn,curH,m_iBtnW,WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;
	
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

int CInvWllqfpWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to INV_SEG_MENU
		ChangeWin(INV_MANAGE_MENU);	
		
		return SUCCESS;
		break;
		
	default: break;		
	}
   return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CInvWllqfpWin::ReFresh()
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


void CInvWllqfpWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvWllqfpWin *win=(CInvWllqfpWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}
void CInvWllqfpWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvWllqfpWin *win=(CInvWllqfpWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}
void CInvWllqfpWin::S_OnInput3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvWllqfpWin *win=(CInvWllqfpWin *)obj->GetdWin();
	win->OnInput3(iEvent,pEventData,iDataLen);
}

void CInvWllqfpWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvWllqfpWin *win=(CInvWllqfpWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}
void CInvWllqfpWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvWllqfpWin *win=(CInvWllqfpWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void CInvWllqfpWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;	

}
void CInvWllqfpWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;	
}
void CInvWllqfpWin::OnInput3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;	
}

void CInvWllqfpWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
 	string strErr("");
 	
 	//��鷢Ʊ����ͷ�Ʊ���� ����
 	if (CheckInputValid(strErr) == FAILURE) 
 	{
 		return ;
 	}

	CaMsgBox msgBox("�Ƿ�������ȡ��Ʊ��", CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
	{
		return; 
	}
   
	UINT8 ret=SUCCESS;

	CaProgressBar proBar("");
	proBar.SetText("������ȡ��Ʊ��...");
    proBar.Show();

	ret= INV_NetInvVol( m_invCode, m_invStartNo, m_invNum, strErr);
	if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return ;
	}

	CaMsgBox::ShowMsg("������ȡ��Ʊ�ɹ�");
	
}

void CInvWllqfpWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
		ChangeWin(INV_MANAGE_MENU);	
}


UINT8 CInvWllqfpWin::CheckInputValid(string &strErr)
{
 	UINT8 nRet = SUCCESS;
 
 	//���벻��Ϊ��
 	if(m_pInput1->IsEmpty())
 	{ 
 		CaMsgBox::ShowMsg("�����뷢Ʊ����");
 		m_pInput1->SetFocus();
 		this->ReFresh();
 		return FAILURE;
 	}
 
 	if(m_pInput2->IsEmpty())
 	{ 
 		CaMsgBox::ShowMsg("��������ʼ����");
 		m_pInput2->SetFocus();
 		this->ReFresh();
 		return FAILURE;
 	}
 
	if(m_pInput3->IsEmpty())
	{ 
		CaMsgBox::ShowMsg("�����뷢Ʊ����");
		m_pInput3->SetFocus();
		this->ReFresh();
		return FAILURE;
 	}

 	
 	UINT32 nLen = strlen((char*)(m_pInput1->m_contentBuf));
 	if (nLen != 2*INV_TYPE_CODE_LEN) 
 	{
 		CaMsgBox::ShowMsg("��Ʊ����Ƿ�");
 		m_pInput1->SetFocus();
 		this->ReFresh();
 		return FAILURE;
 	}
 	else if (0 == atoi((INT8 *)m_pInput1->m_contentBuf)) 
 	{
 		DBG_PRINT(("��Ʊ����Ƿ�"));
 		CaMsgBox::ShowMsg("��Ʊ����Ƿ�");
 		m_pInput1->SetFocus();
 		this->ReFresh();
 		return FAILURE;
 	}

    m_invCode = (INT8 *)(m_pInput1->m_contentBuf);


 	//��ȡ��Ʊ����ʼ����
 	m_invStartNo = atoi((INT8 *)m_pInput2->m_contentBuf);
 	if(m_invStartNo == 0)
 	{
 		CaMsgBox::ShowMsg("��ʼ���벻��Ϊ��");
 		m_pInput2->SetFocus();
 		this->ReFresh();
 		return FAILURE;
 	}

	m_invNum = atoi((INT8 *)m_pInput3->m_contentBuf);
	
	if(m_invNum == 0)
	{
		CaMsgBox::ShowMsg("��Ʊ��������Ϊ��");
		m_pInput3->SetFocus();
		this->ReFresh();
		return FAILURE;
	}
 	
 	this->ReFresh();
	return nRet;
}

void CInvWllqfpWin::S_OnActive(CaWindow *obj)
{
	((CInvWllqfpWin *)obj)->DoActive();
}


void CInvWllqfpWin::DoActive()
{
	DBG_ENTER("CInvWllqfpWin::DoActive()");

	m_pInput1->Clear();
	m_pInput2->Clear();
	m_pInput3->Clear();

	ReFresh();
}
