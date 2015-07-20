/*! \file    RetToInvWin.cpp
   \brief    awe4000r��Ʊ�˻أ����ֻ�һ��������
   \author   zcy
   \version  1.0
   \date     2014-6-3
 */
#include "RetToInvWin.h"
#include "CaLabel.h"
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include <string.h>
#include "stdlib.h"
#include "CInvVol.h"
#include "InvVolFunc.h" 

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CRetToInvWin::CRetToInvWin():CaWindow()
{

}

int CRetToInvWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];

    int titleLen=0;
	m_pFrame->RegsiterWin(this,RET_TO_INV_WIN);    
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
	
	strcpy(title, "�˻�");
	m_pBtn1 = new CaButton();
	curH += 2*LINE_H;
	m_pBtn1->Create(leftoffset_btn,curH,m_iBtnW,WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;
	
	strcpy(title, "����");
	m_pBtn2 = new CaButton();
	m_pBtn2->Create(leftoffset_btn+m_iColW,curH,m_iBtnW,WORD_H); //m_iColW δ���壬����ֵ������
	m_pBtn2->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn2->SetTitle(title, strlen(title));
	m_pBtn2->BoxType(CaObject::BOX_NO);
	m_pBtn2->OnObject = S_OnButton2;	

	OnActive = S_OnActive;
	this->End();
	return 0;
}

int CRetToInvWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to INV_SEG_MENU
		ChangeWin(INV_SEG_MENU);	
		
		return SUCCESS;
		break;
		
	default: break;		
	}
   return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CRetToInvWin::ReFresh()
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


void CRetToInvWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CRetToInvWin *win=(CRetToInvWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}
void CRetToInvWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CRetToInvWin *win=(CRetToInvWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}
void CRetToInvWin::S_OnInput3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CRetToInvWin *win=(CRetToInvWin *)obj->GetdWin();
	win->OnInput3(iEvent,pEventData,iDataLen);
}

void CRetToInvWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CRetToInvWin *win=(CRetToInvWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}
void CRetToInvWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CRetToInvWin *win=(CRetToInvWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void CRetToInvWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;	

}
void CRetToInvWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;	
}
void CRetToInvWin::OnInput3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;	
}

void CRetToInvWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
 	string strErr("");
 	INT32 nRet =0;
 	UINT8 ret=SUCCESS;

 	//��鷢Ʊ����ͷ�Ʊ���� ����
 	if (CheckInputValid() == FAILURE) 
 	{
 		return ;
 	}

	CaMsgBox msgBox("�Ƿ��˻ط�Ʊ��", CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
	{
		return; 
	}

    UINT8 uJZlx=2;//��˰�̽���

	ret= INV_MediumType(uJZlx,strErr);
    if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return ;
	}

	CaProgressBar proBar("");
	proBar.SetText("��Ʊ�˻���...");
    proBar.Show();
	
	ret= INV_RetToInvVol(uJZlx,m_invCode,m_invStartNo,m_invNum,strErr);
	if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return ;
	}
	CaMsgBox::ShowMsg("��Ʊ�˻سɹ�");


	/*
//  	nRet = CJSKInfoFunc::ExtReturnInv(&tmpInvVol, strErr);
//    DBG_PRINT(("nRet= %d",nRet));
//  	if ( nRet != JSK_SUCCESS)
//  	{
// 		CaMsgBox::ShowMsg(strErr);
// 		return;
//  	}
//  	else
 	{
 		strErr = "��Ʊ�˻سɹ�";
 		CaMsgBox::ShowMsg(strErr);

		//��ѯ���еķ�Ʊ����Ϣ
		proBar.SetText("��ȡ��˰���з�Ʊ����Ϣ...");
	     proBar.Show();
         UINT32 nNum;

// 		//���̻�ȡƱԴ���ģ����뱾��DB
// 		if (CJSKInvDownProc::JSK_InvVolFunc(nNum, strErr) !=SUCCESS)
// 		{
// 			CaMsgBox::ShowMsg(strErr);
// 		}
// 		else
// 		{
// 			CaMsgBox::ShowMsg("����Ʊ����Ϣ�ɹ�!");
// 		}

 		DoActive();
 		ChangeWin(INV_SEG_MENU);
 	}
*/

}

void CRetToInvWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
		ChangeWin(INV_SEG_MENU);	
}


UINT8 CRetToInvWin::CheckInputValid()
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
 	if (nLen!=2*INV_TYPE_CODE_LEN) 
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
 
	//�ж���ʼ����ĩβ�Ƿ�Ϊ��01��
// 	if (m_invStartNo%100 != 1 )
// 	{
// 		CaMsgBox::ShowMsg("��ʼ����Ƿ�");
//  		m_pInput2->SetFocus();
//  		this->ReFresh();
//  		return FAILURE;
// 	}

 	m_invNum = atoi((INT8 *)m_pInput3->m_contentBuf);
	
	if ( m_invNum ==0)
	{
		CaMsgBox::ShowMsg("��Ʊ��������Ϊ��");
 		m_pInput3->SetFocus();
 		this->ReFresh();
 		return FAILURE;
	}

//  	if(m_invNum%100 != 0)
//  	{
//  		CaMsgBox::ShowMsg("��Ʊ������������");
//  		m_pInput3->SetFocus();
//  		this->ReFresh();
//  		return FAILURE;
//  	}
 

 	this->ReFresh();
	return nRet;
}

void CRetToInvWin::S_OnActive(CaWindow *obj)
{
	((CRetToInvWin *)obj)->DoActive();
}


void CRetToInvWin::DoActive()
{
	DBG_ENTER("CRetToInvWin::DoActive()");

	m_pInput1->Clear();
	m_pInput2->Clear();
	m_pInput3->Clear();

	ReFresh();
}
