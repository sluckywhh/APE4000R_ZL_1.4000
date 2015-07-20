/*! \file    CorpInfoWin.cpp
   \brief    awe4000r�����ӡ����ҵ��Ϣ����
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */

#include "CorpInfoWin.h"
#include "ReportFunc.h"
#include "TemplateGeneralFuc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#include <stdio.h>

CCorpInfoWin::CCorpInfoWin():CMultiLabelCommonWin(4)
{
	m_pCorpInfo = NULL;
}
CCorpInfoWin::~CCorpInfoWin()
{
		
}
int CCorpInfoWin::Create(int iX, int iY, int iW, int iH)
{
	UINT8 i, j=0;
	UINT8 errorcode;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

	m_pFrame->RegsiterWin(this, CORP_INFO_WIN);    
	CMultiLabelCommonWin::Create(iX,iY,iW,iH); // creat a window
//	DBG_PRINT(("CCorpInfoWin::NormalShow()"));
//	NormalShow();
	sprintf(title, "��ӡ");
	SetTitle(9, title);
	sprintf(title, "����");
	SetTitle(10, title);

	OnActive = S_OnActive;
	this->End();
	return 0;
}

int CCorpInfoWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	//������һ���˵�
	if (RETURN_MAIN_MENU == iEvent)
	{
		ChangeWin(BASIC_REPORT_MENU);
		return SUCCESS;
	}

	return CMultiLabelCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}


int CCorpInfoWin::ReFresh()
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

void CCorpInfoWin::OnButton1(int iEvent,unsigned char *pEventData, int iDataLen)
{
	PrintCorpInfo();
	ChangeWin(BASIC_REPORT_MENU);	
}

void CCorpInfoWin::OnButton2(int iEvent,unsigned char *pEventData, int iDataLen)
{
	ChangeWin(BASIC_REPORT_MENU);
}


UINT8 CCorpInfoWin::NormalShow()
{
	UINT8 len = 0;
	char title[OBJ_TITLE_MAX_LEN + 1];
	char title1[OBJ_TITLE_MAX_LEN + 1] = "����:";

	DBG_PRINT(("g_globalArg->m_corpInfo->m_Nsrmc = %s", g_globalArg->m_corpInfo->m_Nsrmc.c_str()));
	DBG_PRINT(("*******lenth = %u",g_globalArg->m_corpInfo->m_Nsrmc.length())); 

	UINT8 buff[CORP_NAME_LEN+1];
	memset(buff, 0, sizeof(buff));
	sprintf((char *)buff, "%s", g_globalArg->m_corpInfo->m_Nsrmc.c_str());
	len = OBJ_TITLE_MAX_LEN;
	if( GetHalfHZCount(buff, OBJ_TITLE_MAX_LEN-6)%2 == 0 )
	{
		len = OBJ_TITLE_MAX_LEN-6;
	}
	else
	{
		len = OBJ_TITLE_MAX_LEN-7;
	}
	memcpy((void *)(title1+5), 
	(void *)(g_globalArg->m_corpInfo->m_Nsrmc.c_str()), len);

	DBG_PRINT(("title1 = %s",title1)); 
	SetTitle(1, title1);

	sprintf(title, "˰��:%s ", g_globalArg->m_corpInfo->m_Nsrsbh.c_str());
	SetTitle(2, title);

	string strTmp("");

	if (g_globalArg->m_corpInfo->m_Kpjhm ==0)
	{
		strTmp="����";
	}
	else
	{
		strTmp="�ֻ�";
	}
	sprintf(title, "���ֻ���־:%s ", strTmp.c_str());
	SetTitle(3, title);

     DBG_PRINT(("��˰�̱�� = %s",  g_globalArg->m_corpInfo->m_Jspsbh.c_str())); 
	sprintf(title, "��˰�̱��:%s ", g_globalArg->m_corpInfo->m_Jspsbh.c_str());

	DBG_PRINT(("������= %s", title)); 
	SetTitle(4, title);

	return SUCCESS;
}

void CCorpInfoWin::S_OnActive(CaWindow *obj)
{
	((CCorpInfoWin *)obj)->DoActive();
}


void CCorpInfoWin::DoActive()
{
	DBG_PRINT(("CCorpInfoWin::DoActive()"));
  
	NormalShow();
	SetBtnFocus();
	ReFresh();
}

UINT8 CCorpInfoWin::PrintCorpInfo()
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

	m_pCorpInfo = &m_corpInfo;
	memset((void *)m_pCorpInfo, 0x00, sizeof(struct TCorpInfoPrnData));
	
	//��ϵͳ�����л�ȡ����, �������ӳ��
	memcpy((void *)m_pCorpInfo->Nsrsbh, g_globalArg->m_corpInfo->m_Nsrsbh.c_str(), CORP_SBH_LEN);
	memcpy((void *)m_pCorpInfo->Nsrmc, g_globalArg->m_corpInfo->m_Nsrmc.c_str(), CORP_NAME_LEN);
	memcpy((void *)m_pCorpInfo->Jspsbh, g_globalArg->m_corpInfo->m_Jspsbh.c_str(), CORP_JSPBH_LEN);
	memcpy((void *)m_pCorpInfo->Nsrswjgdm, g_globalArg->m_corpInfo->m_Swjgdm.c_str(), CORP_SWJGDM_LEN);
	memcpy((void *)m_pCorpInfo->Nsrswjgmc, g_globalArg->m_corpInfo->m_Swjgmc.c_str(), CORP_ZGSWGY_LEN);
	memcpy((void *)m_pCorpInfo->Qysj, g_globalArg->m_corpInfo->m_qysj.c_str(), CORP_QYSJ_LEN);


	if (g_globalArg->m_corpInfo->m_zfFlag ==0)
	{
		memcpy((void *)m_pCorpInfo->Zfbz, "����", sizeof("����"));
	}
	else
	{
		memcpy((void *)m_pCorpInfo->Zfbz, "�ֻ�", sizeof("�ֻ�"));
	}

	if (g_globalArg->m_corpInfo->m_Qylx == "000")
	{
		memcpy((void *)m_pCorpInfo->Qylx, "��������ҵ", sizeof("��������ҵ"));
	}
	else
	{
		memcpy((void *)m_pCorpInfo->Qylx, "������ҵ", sizeof("������ҵ"));
	}
	

	//��ӡ
	if (print_corpinfo(m_pCorpInfo, 1) != 0)
	{
		strErr = "��ӡ��ҵ��Ϣʧ��!";
		CaMsgBox::ShowMsg(strErr);
		this->ReFresh();
		return FAILURE;
	}

	return SUCCESS;
}