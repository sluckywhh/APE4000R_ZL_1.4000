/*! \file    InvWstQueryWin.cpp
   \brief    awe4000r��Ʊ�������ѿ���Ʊ���ϲ�ѯ����
   \author   Yu Yan 
   \version  1.0
   \date     2008-2-28
 */


#include "InvWstQueryWin.h"

#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CInvWstQueryWin::CInvWstQueryWin():CaWindow()
{
	m_ret = 0;
	m_code = "";
	m_invStartNo = 0;
	m_invEndNo = 0;
	
}

CInvWstQueryWin::~CInvWstQueryWin()
{
	
}


int CInvWstQueryWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,INV_WST_QUERY_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	
	//����һ��Input  ��һ��
	strcpy(title, "��Ʊ����:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET;
	curH += LINE_H;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(12);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;
	
	//����һ��Input  �ڶ���
	strcpy(title, "��Ʊ����:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(8);
	m_pInput2->m_InputType = m_pInput2->aINT; //�������ֻ��������ֵ
	m_pInput2->OnObject = S_OnInput2;
	
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

int CInvWstQueryWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  
		ChangeWin(INV_WASTE_MENU);			
		return SUCCESS;
		break;
		
	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CInvWstQueryWin::ReFresh()
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

UINT8 CInvWstQueryWin::ErrMsgBox(UINT8 ret)
{
	string pText;
	switch(ret)
	{
		case CODE_NO_ERROR:
		    pText = "δʹ�ù��÷�Ʊ����";
			break;
		case NO_MATCHED_INV:
		    pText = "��ƥ��ķ�Ʊ���";
			break;
    	case NO_END_INV:
		pText = "�����뷢Ʊ��ֹ����";
			break;
		case NO_INV_NO:
		    pText = "�����뷢Ʊ����";
			break;
		case QUERY_ERROR:
			 pText = "��ѯ���ݿ�ʧ��";
			break;
		case HAVE_FU_INV:
			pText = "��Ʊ�ѳ��";
			break;
		default:;
	}  

	if (FAILURE != ret)
	{
		CaMsgBox::ShowMsg(pText);
	}
	
	return FAILURE;	
}



void CInvWstQueryWin::S_OnActive(CaWindow *obj)
{
	((CInvWstQueryWin *)obj)->DoActive();
}


void CInvWstQueryWin::DoActive()
{
	m_pInput1->Clear();//���Input�������
	m_pInput2->Clear();
	m_code = "";
	m_invStartNo = 0;
	m_invEndNo = 0;

	m_pInput1->SetContentBuf((UINT8*)g_globalArg->m_curInvVol->m_code.c_str(), g_globalArg->m_curInvVol->m_code.length());

	ReFresh();	
}



void CInvWstQueryWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvWstQueryWin *win=(CInvWstQueryWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CInvWstQueryWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvWstQueryWin *win=(CInvWstQueryWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}

void CInvWstQueryWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvWstQueryWin *win=(CInvWstQueryWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CInvWstQueryWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvWstQueryWin *win=(CInvWstQueryWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void CInvWstQueryWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CInvWstQueryWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CInvWstQueryWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 ret = CheckInput();
	if(ret == SUCCESS)
	{
		ChangeWin(INV_WST_WIN);	 //�ѿ���Ʊ���Ͻ���
	}
	else
	{
		INVM_ErrMsgBox(ret);
	//	ErrMsgBox(ret);
	}
	
}

void CInvWstQueryWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(INV_WASTE_MENU);	 //���ط�Ʊ�������		
}

UINT8 CInvWstQueryWin::CheckInput(void)
{
	DBG_PRINT(("CheckInput begin"));
	
	UINT8 ret = SUCCESS;
	char *content1, *content2, *content3;
	INT32 tmp;

	content1 = (char*)(m_pInput1->m_contentBuf); 
	content2 = (char*)(m_pInput2->m_contentBuf);
	//content3 = (char*)(m_pInput2->m_contentBuf);

	//δ���뷢Ʊ����
	if (strlen(content2)==0)
	{
		m_pInput2->SetFocus();
		return(NO_INV_NO);
	}

	m_invStartNo = atoi(content2);
	m_invEndNo = atoi(content2);

	//δ���뷢Ʊ����
	if (strlen(content1)==0)
	{
		m_pInput2->SetFocus();
		return(CODE_NO_ERROR);
	}

	//δ���뷢Ʊ����
// 	if(strlen(content1)==0)
// 	{
// 		m_code = g_globalArg->m_curInvVol->m_code;	
// 		DBG_PRINT(("g_globalArg->m_curInvVol->m_code = %s", g_globalArg->m_curInvVol->m_code.c_str()));
// 	}
// 	else //��鷢Ʊ����Ϸ���
// 	{

		m_code = content1;
//	}

	//����Ƿ��з��������ķ�Ʊ���
	UINT32 nTmpNum = 0;
	CInvHead invHead;
	DBG_PRINT(("m_code = %s", m_code.c_str()));
//	ret = GetInvNum(m_code, m_invStartNo, m_invEndNo, nTmpNum);
	ret = INVM_CheckIsNoDB(m_code, m_invStartNo,&invHead);
	if(ret != SUCCESS)
	{
		return ret;
	}
// 	if (ret==FAILURE)
// 	{
// 		return(QUERY_ERROR);		
// 	}
// 	else if((ret==SUCCESS)&&(nTmpNum == 0))
// 	{
// 		return(NO_MATCHED_INV);		
// 	}

	return SUCCESS;
}

