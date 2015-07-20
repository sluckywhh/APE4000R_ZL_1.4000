/*! \file    InvKindInfoWin.cpp
   \brief    awe4000r�����ӡ��Ʊ����Ϣ����
   \author   zcy
   \version  1.0
   \date     2011-7-5
 */

#include "InvKindInfoWin.h"
#include "ReportFunc.h"
#include "TemplateGeneralFuc.h"
#include "commonFunc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#include <stdio.h>

CInvKindInfoWin::CInvKindInfoWin():CMultiLabelCommonWin(4)
{
	m_pInvKindInfo = NULL;
}
CInvKindInfoWin::~CInvKindInfoWin()
{
		
}
int CInvKindInfoWin::Create(int iX, int iY, int iW, int iH)
{
	UINT8 i, j=0;
	UINT8 errorcode;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;


	m_pFrame->RegsiterWin(this, INV_KIND_INFO_WIN);    
	CMultiLabelCommonWin::Create(iX,iY,iW,iH); // creat a window
	sprintf(title, "��ӡ");
	SetTitle(9, title);
	sprintf(title, "����");
	SetTitle(10, title);

	OnActive = S_OnActive;
	this->End();
	return 0;
}

int CInvKindInfoWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	//������һ���˵�
	if (RETURN_MAIN_MENU == iEvent)
	{
		ChangeWin(BASIC_REPORT_MENU);
		return SUCCESS;
	}

	return CMultiLabelCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}


int CInvKindInfoWin::ReFresh()
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

void CInvKindInfoWin::OnButton1(int iEvent,unsigned char *pEventData, int iDataLen)
{
	PrintInvKindInfo();
	ChangeWin(BASIC_REPORT_MENU);	
}

void CInvKindInfoWin::OnButton2(int iEvent,unsigned char *pEventData, int iDataLen)
{
	ChangeWin(BASIC_REPORT_MENU);
}

UINT8 CInvKindInfoWin::NormalShow()
{
	UINT8 len = 0;
	char title[OBJ_TITLE_MAX_LEN + 1];

	CInvKind curInvKind;
	CInvKind *invKind= &curInvKind;
	UINT8 errorcode;
	INT8 value[256];
	memset((void *)value, 0, sizeof(value));
	sprintf(value,"WHERE NO = %d",1);
	invKind->m_filter = "";
	invKind->m_filter.append(value); 
	invKind->Requery(); 
	errorcode = invKind->LoadOneRecord(); 
	DBG_PRINT(("errorcode = %u\n", errorcode));


	 DBG_PRINT(("��Ʊ���ʹ��� = %s",curInvKind.m_fplxdm.c_str()));
	sprintf(title, "��Ʊ���ʹ���:%s ", curInvKind.m_fplxdm.c_str());
	SetTitle(1, title);
    
	DBG_PRINT(("���߿���ʱ��:%u ������:%u",curInvKind.m_Lxkjsj,curInvKind.m_Lxssr ));
	sprintf(title, "���߿���ʱ��:%u ������:%u", curInvKind.m_Lxkjsj,curInvKind.m_Lxssr);
	SetTitle(2, title);

	DBG_PRINT(("�����޶� = %f", ((double)(curInvKind.m_maxSign))/SUM_EXTENSION));
	sprintf(title, "�����޶�:%.2f", ((double)(curInvKind.m_maxSign))/SUM_EXTENSION);
	SetTitle(3, title);
    
	DBG_PRINT(("���������ۼ��޶�  = %f", ((double)(curInvKind.m_maxSum))/SUM_EXTENSION));
	sprintf(title, "���������ۼ��޶�:%.2f ", ((double)(curInvKind.m_maxSum))/SUM_EXTENSION);
	SetTitle(4, title);
 

	return SUCCESS;
}


void CInvKindInfoWin::S_OnActive(CaWindow *obj)
{
	((CInvKindInfoWin *)obj)->DoActive();
}


void CInvKindInfoWin::DoActive()
{
	DBG_PRINT(("CInvKindInfoWin::DoActive()"));
  	
	NormalShow();
	SetBtnFocus();
	ReFresh();
}

UINT8 CInvKindInfoWin::PrintInvKindInfo()
{
	UINT8 ret;
	string strErr;
	if (isPaper() != 0)
	{	
		strErr = "��ӡ��δ��⵽ֽ";
		CaMsgBox::ShowMsg(strErr);
		this->ReFresh();
		return FAILURE;
	}
	ret = YesNoMsgBox("��Ű�ֽ���Ƿ��ӡ��");
	if (ret==FAILURE)
	{
		return SUCCESS;
	}

// 	m_pInvKindInfo = &m_InvKindInfo;
// 	memset((void *)m_pInvKindInfo, 0x00, sizeof(struct TInvKindInfoPrnData));
	
	//��ϵͳ�����л�ȡ����, �������ӳ��
// 	CInvKind curInvKind;
// 	CInvKind *invKind = &curInvKind;
// 	UINT8 errorcode;
// 	INT8 value[256];
// 	memset((void *)value, 0, sizeof(value));
// 	sprintf(value,"WHERE NO = %d",1);
// 	invKind->m_filter = "";
// 	invKind->m_filter.append(value); 
// 	invKind->Requery(); 
// 	errorcode = invKind->LoadOneRecord(); 
// 	DBG_PRINT(("errorcode = %u\n", errorcode));
// 
// 	memcpy((void *)m_pInvKindInfo->InvKindCode, g_globalArg->m_invKind->m_fplxdm.c_str(), INV_KIND_CODE_LEN);	  
// 	m_pInvKindInfo->MaxSign = g_globalArg->m_invKind->m_maxSign;
// 	m_pInvKindInfo->InvMaxMoney = g_globalArg->m_invKind->m_maxSum;
// 	m_pInvKindInfo->Lxssr = g_globalArg->m_invKind->m_Lxssr;
// 	m_pInvKindInfo->Lxkjsj = g_globalArg->m_invKind->m_Lxkjsj;
	
	//��ӡ
//	if (print_invKindinfo(m_pInvKindInfo, 1) != 0)
	if (print_invkindifo(1) != 0)	
	{
		strErr = "��ӡƱ����Ϣʧ��!";
		CaMsgBox::ShowMsg(strErr);
		this->ReFresh();
		return FAILURE;
	}
#ifndef WIN32
	CommonSleep(1000);
#endif

	return SUCCESS;
}