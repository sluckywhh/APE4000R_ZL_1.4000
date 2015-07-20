/*! \file    InvStubWin.cpp
   \brief    awe4000r��Ʊ�����ķ�Ʊ�����ѯ����
   \author   Yu Yan 
   \version  1.0
   \date     2008-2-28
 */

#include "InvStubWin.h"
#include "InvStubPrnWin.h"

#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CInvStubWin::CInvStubWin():CaWindow()
{
	m_ret = 0;
	m_code = "";
	m_invStartNo = 0;
	m_invEndNo = 0;
	
}

CInvStubWin::~CInvStubWin()
{
	
}

int CInvStubWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,INV_STUB_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	
	//����һ��Input  ��һ��
	strcpy(title, "��Ʊ����:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(12);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;
	
	//����һ��Input  �ڶ���
	strcpy(title, "��Ʊ��ʼ����:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(8);
	m_pInput2->m_InputType = m_pInput2->aINT; //�������ֻ��������ֵ
	m_pInput2->OnObject = S_OnInput2;
	
	//����һ��Input  ������
	strcpy(title, "��Ʊ��ֹ����:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput3=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput3->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput3->SetTitle(title,titleLen / CHAR_W);	
	m_pInput3->SetMaxLen(8);
	m_pInput3->m_InputType = m_pInput3->aINT; //�������ֻ��������ֵ
	m_pInput3->OnObject = S_OnInput3;

	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;

	//����һ��Button  ������
	strcpy(title, "��ѯ");
	m_pBtn1 = new CaButton();
	curH += 2*LINE_H;
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

int CInvStubWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
#if (0 == RELEASE_VER)
	string strErr("");
	string strInvCode("");
	string strDate("");
	UINT32 nInvNo = 0;
#endif
	
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
		ChangeWin(INV_MANAGE_MENU);			
		return SUCCESS;
		break;

	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CInvStubWin::ReFresh()
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

UINT8 CInvStubWin::ErrMsgBox(UINT8 ret)
{
	string pText("");
	switch(ret)
	{
//		case INV_SUM_ERROR:
//			pText = "�����ʧ��";
//			break;
//		case PRN_INV_ERROR:
//		    pText = "��Ʊʧ��";
//			break;
//		case RETURN_NUM_ERROR:
//		    pText = "��Ʊ���벻����";
//			break;
//		case NO_INV:
//		    pText = "�Ǳ���������Ʊ";
//			break;
//		case RT_INV:
//		    pText = "��Ʊ���ܱ��˻�";
//			break;
//		case WT_INV:
//		    pText = "��Ʊ���ܱ��˻�";
//			break;
//		case RM_SUM_EXCEED:
//		    pText = "��Ʊ�ۼƽ���";
//			break;
//		case RVM_SUM_EXCEED:
//		    pText = "�����Ʊ�ۼƽ���";
//			break;
//		case HAVE_RT_INV:
//		    pText = "�ѿ�����Ʊ";
//			break;
			
		case CODE_NO_ERROR:
		    //pText = "δʹ�ù��÷�Ʊ����";
			pText = "�����뷢Ʊ����";
			break;
		case NO_MATCHED_INV:
		    pText = "��ƥ��ķ�Ʊ���";
			break;
		case NO_START_INV:
		    pText = "�����뷢Ʊ��ʼ����";
			break;
		case NO_END_INV:
		    pText = "�����뷢Ʊ��ֹ����";
			break;
		case QUERY_ERROR:
			 pText = "��ѯ���ݿ�ʧ��";
			break;
		case NO_INV_ERROR:
			pText = "��Ʊ��ʼ�Ŵ��ڷ�Ʊ��ֹ��";
			break;
		default:
			break;
	}  

	CaMsgBox::ShowMsg(pText);
	return FAILURE;	
}

void CInvStubWin::S_OnActive(CaWindow *obj)
{
	((CInvStubWin *)obj)->DoActive();
}


void CInvStubWin::DoActive()
{
	DBG_PRINT((" CInvStubWin::DoActive()!"));
	
	m_pInput1->Clear();//���Input�������
	m_pInput2->Clear();
	m_pInput3->Clear();
	m_code = "";
	m_invStartNo = 0;
	m_invEndNo = 0;

	m_pInput1->SetContentBuf((UINT8*)g_globalArg->m_curInvVol->m_code.c_str(), g_globalArg->m_curInvVol->m_code.length());
	ReFresh();	
}

void CInvStubWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvStubWin *win=(CInvStubWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CInvStubWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvStubWin *win=(CInvStubWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}

void CInvStubWin::S_OnInput3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvStubWin *win=(CInvStubWin *)obj->GetdWin();
	win->OnInput3(iEvent,pEventData,iDataLen);
}


void CInvStubWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvStubWin *win=(CInvStubWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}


void CInvStubWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvStubWin *win=(CInvStubWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CInvStubWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CInvStubWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CInvStubWin::OnInput3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CInvStubWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 ret = CheckInput();
	if(ret == SUCCESS)
	{
		DBG_PRINT(("ChangeWin(INV_STUB_PRN_WIN)"));
		((CInvStubPrnWin *)m_pFrame->GetWin(INV_STUB_PRN_WIN))->m_pageflag = 0;
		ChangeWin(INV_STUB_PRN_WIN);	 //�����ӡ����	
	}
	else
	{
		ErrMsgBox(ret);
	}
	
}

void CInvStubWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(INV_MANAGE_MENU);	 //���ط�Ʊ�������		
}

UINT8 CInvStubWin::CheckInput(void)
{
	DBG_PRINT(("CheckInput begin"));
	
	UINT8 ret = SUCCESS;
	char *content1, *content2, *content3;
	INT32 tmp;

	content1 = (char*)(m_pInput1->m_contentBuf); 
	content2 = (char*)(m_pInput2->m_contentBuf);
	content3 = (char*)(m_pInput3->m_contentBuf);
	DBG_PRINT(("InvStubWin  code = %s", content1));
	DBG_PRINT(("InvStubWin  fpqshm = %s", content2));
	DBG_PRINT(("InvStubWin  fpjzhm = %s", content3));

	//δ���뷢Ʊ����
	if(strlen(content1)==0)
	{
		m_pInput1->SetFocus();
		return(CODE_NO_ERROR);
	}
	
	//δ���뷢Ʊ����
	if (strlen(content2)==0)
	{
		m_pInput2->SetFocus();
		return(NO_START_INV);
	}

	if (strlen(content3)==0)
	{
		m_pInput3->SetFocus();
		return(NO_END_INV);
	}
	
	m_code = (char *)content1;
	m_invStartNo = atoi(content2);
	m_invEndNo = atoi(content3);

//�ж��������ʼ�źͽ�����
	if (m_invStartNo>m_invEndNo) 
	{
		m_pInput2->SetFocus();
		return (NO_INV_ERROR);
	}

	//����Ƿ��з��������ķ�Ʊ���
	UINT32 nTmpNum = 0;
	DBG_PRINT(("g_globalArg->m_curInvVol->m_code = %s", g_globalArg->m_curInvVol->m_code.c_str()));
	DBG_PRINT(("m_invStartNo = %u, m_invEndNo = %u", m_invStartNo, m_invEndNo));
	ret = INVM_GetInvNum(m_code, m_invStartNo, m_invEndNo, nTmpNum);
	if (ret==FAILURE)
	{
		return(QUERY_ERROR);		
	}
	else if((ret==SUCCESS)&&(nTmpNum == 0))
	{
		return(NO_MATCHED_INV);		
	}

	return SUCCESS;
}

