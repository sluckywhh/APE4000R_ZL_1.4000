/**
 @file  ApnAccPointSetWin.cpp
 @brief �����ļ�������APN�����
*/
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "netManager.h"
#include "M2M_APN_Connection.h"
#include "ApnAccPointSetWin.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CApnAccPointSetWin::CApnAccPointSetWin():CaWindow()
{
}

CApnAccPointSetWin::~CApnAccPointSetWin()
{
}


int CApnAccPointSetWin::Create(int iX,int iY,int iW,int iH)
{
	int curH=0;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	int inputW = SCREEN_W - left_offset*2;


	m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,APN_ACCPOINT_SET_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window

	//����һ��Input  ��һ��
	strcpy(title, "APN����:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET+4;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(left_offset,curH,inputW+1,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(40);
	m_pInput1->m_InputType = m_pInput1->aCHAR; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;

	strcpy(title, "��   ��:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pLabel1 = new CaLabel(false,CaObject::ALIGN_LEFT);
	m_pLabel1->Create(left_offset, curH, inputW+1, LINE_H);
	m_pLabel1->SetTitle(title, titleLen / CHAR_W);		

	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�

	//����һ��Button  ������
	strcpy(title, "ȷ��");
	m_pBtn1 = new CaButton();
	curH += LINE_H*2;
	m_pBtn1->Create(leftoffset_btn,curH,m_iBtnW,WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;
	
	//����һ��Button  ������
	strcpy(title, "����");
	m_pBtn2 = new CaButton();
	m_pBtn2->Create(leftoffset_btn + m_iColW,curH,m_iBtnW,WORD_H); 
	m_pBtn2->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn2->SetTitle(title, strlen(title));
	m_pBtn2->BoxType(CaObject::BOX_NO);
	m_pBtn2->OnObject = S_OnButton2;

	OnActive = S_OnActive;
	
	this->End();  
	return 0;
}

int CApnAccPointSetWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU: 
		ClearWin();
		ChangeWin(M2M_MANAGE_MENU);						
		return SUCCESS;
		break;		
	default: 
		break;		
	}
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CApnAccPointSetWin::ReFresh()
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


void CApnAccPointSetWin::S_OnActive(CaWindow *obj)
{
	((CApnAccPointSetWin *)obj)->DoActive();
}


void CApnAccPointSetWin::DoActive()
{
	DispApnAccPointInfo();
	ReFresh();
}

void CApnAccPointSetWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CApnAccPointSetWin *win=(CApnAccPointSetWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CApnAccPointSetWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); 
	return;		
}

void CApnAccPointSetWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CApnAccPointSetWin *win=(CApnAccPointSetWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CApnAccPointSetWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CApnAccPointSetWin *win=(CApnAccPointSetWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void CApnAccPointSetWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	int ret=0;
	string apnAccPoint(""), apnNumber("");
	string strErr("");
	CaProgressBar proBar("");

	if (g_netManager->GetConnectionMode() != NET_M2M_APN)
	{
		CaMsgBox::ShowMsg("��ǰ��M2M APNģʽ,�޷��޸�");
		return;
	}

	//ֻ��apnAccPoint�����ã�apnNumber�����ʱ�̶�����
	CNetDBWork::load_APN_Acc_Num(apnAccPoint, apnNumber, strErr);

	proBar.SetText("�����������...");
	proBar.ReFresh();

	apnAccPoint = (char *)m_pInput1->m_contentBuf;
	if( apnAccPoint.length() <= 0 )
	{
		CaMsgBox::ShowMsg("����㲻��Ϊ��");
		m_pInput1->SetFocus();
		this->ReFresh();
		return;
	}

	M2M_APN_Connection *pAPN = (M2M_APN_Connection *)g_netManager->GetConnectionHandle();

	ret = pAPN->setApn_Acc_Num(apnAccPoint, apnNumber, strErr);
	if (ret != NET_SUCCESS)
	{
		DBG_PRINT(("ret = %d", ret))
		CaMsgBox::ShowMsg(strErr);
		return;
	}

	CaMsgBox::ShowMsg("APN��������óɹ�");
	ClearWin();
	ChangeWin(M2M_MANAGE_MENU);
}

void CApnAccPointSetWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ClearWin();
	ChangeWin(M2M_MANAGE_MENU);
}

void CApnAccPointSetWin::DispApnAccPointInfo()
{
	int ret=0;
    INT32 titleLen=0;	
	INT8 title[64];
	string acc(""), num("");
	string strErr("");

	ret = CNetDBWork::load_APN_Acc_Num(acc, num, strErr);
	if (ret != SQLITE_OK)
	{
		DBG_PRINT(("ret = %d", ret))
		CaMsgBox::ShowMsg(strErr);
		return;
	}
	m_pInput1->SetContentBuf((UINT8 *)acc.c_str(), acc.length());

	sprintf(title, "��   ��:%s", num.c_str());
	titleLen = strlen(title);
	m_pLabel1->SetTitle(title, titleLen);	

}

void CApnAccPointSetWin::ClearWin()
{
	m_pInput1->Clear();
}





