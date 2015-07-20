/*! \file    HqlxsjWin.cpp
   \brief    awe4000r��ȡ�������ݽ���
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */

#include "HqlxsjWin.h"
#include "ReportFunc.h"
#include "TemplateGeneralFuc.h"
#include "APIBase.h"
#include "LOGCTRL.h"
#include "CaProgressBar.h"

//#define NO_POS_DEBUG
#include "pos_debug.h"

#include <stdio.h>

CHqlxsjWin::CHqlxsjWin():CMultiLabelCommonWin(3)
{
	m_pOffLineDate = NULL;
	Reset();
}
CHqlxsjWin::~CHqlxsjWin()
{
		
}

void CHqlxsjWin::Reset()
{
	m_wscfpzs = "";		//δ�ϴ���Ʊ����
	m_wscfpsj = "";		//δ�ϴ���Ʊʱ��
	m_wscfpljje = "";		//δ�ϴ���Ʊ�ۼƽ��
	m_sczs = "";			//�ϴ�����
	m_scsjjg = "";		//�ϴ�ʱ����
}

int CHqlxsjWin::Create(int iX, int iY, int iW, int iH)
{
	UINT8 i, j=0;
	UINT8 errorcode;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;


	m_pFrame->RegsiterWin(this, HQLXSJ_WIN);    
	CMultiLabelCommonWin::Create(iX,iY,iW,iH); // creat a window
	sprintf(title, "ȷ��");
	SetTitle(9, title);
	sprintf(title, "����");
	SetTitle(10, title);

	OnActive = S_OnActive;
	this->End();
	return 0;
}

int CHqlxsjWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	//������һ���˵�
	if (RETURN_MAIN_MENU == iEvent)
	{
		ChangeWin(FISCAL_MAIN_MENU);
		return SUCCESS;
	}

	return CMultiLabelCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}


int CHqlxsjWin::ReFresh()
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

void CHqlxsjWin::OnButton1(int iEvent,unsigned char *pEventData, int iDataLen)
{
//	PrintOffLineDate();
	ChangeWin(FISCAL_MAIN_MENU);	
}

void CHqlxsjWin::OnButton2(int iEvent,unsigned char *pEventData, int iDataLen)
{
	ChangeWin(FISCAL_MAIN_MENU);
}


UINT8 CHqlxsjWin::NormalShow()
{
	char title[OBJ_TITLE_MAX_LEN + 1];

	sprintf(title, "δ�ϴ���Ʊ����:%s", m_wscfpzs.c_str());
	DBG_PRINT(("δ�ϴ���Ʊ����= %s", title))
	SetTitle(1, title);

	sprintf(title, "δ�ϴ���Ʊʱ��:%s ", m_wscfpsj.c_str());
	DBG_PRINT(("δ�ϴ���Ʊʱ��= %s", title))
	SetTitle(2, title);

	sprintf(title, "δ�ϴ���Ʊ�ۼƽ��:%s ", m_wscfpljje.c_str());
	DBG_PRINT(("δ�ϴ���Ʊ�ۼƽ��= %s", title))
	SetTitle(3, title);

// 	sprintf(title, "�ϴ�����:%s ", m_sczs.c_str());
// 	DBG_PRINT(("�ϴ�����= %s", title)); 
// 	SetTitle(4, title);
// 
// 	sprintf(title, "�ϴ�ʱ����:%s ", m_scsjjg.c_str());
// 	DBG_PRINT(("�ϴ�ʱ����= %s", title))
// 	SetTitle(5, title);

	return SUCCESS;
}

void CHqlxsjWin::S_OnActive(CaWindow *obj)
{
	((CHqlxsjWin *)obj)->DoActive();
}


void CHqlxsjWin::DoActive()
{
	DBG_PRINT(("CHqlxsjWin::DoActive()"));
	

	CaProgressBar proBar("��ȡ����������...");
	proBar.Show();
	INT32 ret = GetOffLineDate();
 	if (SUCCESS != ret)
 	{
		Reset();
		CaMsgBox::ShowMsg("��ȡ��������ʧ��");
	}
	NormalShow();
	SetBtnFocus();
	ReFresh();
}

UINT8 CHqlxsjWin::GetOffLineDate()
{
	string strErr = "";
	INT32 ret = g_pAPIBase->Hqlxsj_API(m_wscfpzs, m_wscfpsj, m_wscfpljje, m_sczs, m_scsjjg, strErr);

	return ret;
}

UINT8 CHqlxsjWin::PrintOffLineDate()
{
// 
// 	UINT8 ret;
// 	string strErr;
// 	if (isPaper() != 0)
// 	{	
// 		strErr = "��ӡ��δ��⵽ֽ";
// 		CaMsgBox::ShowMsg(strErr);
// 		this->ReFresh();
// 		return FAILURE;
// 	}
// 	ret = YesNoMsgBox("��Ű�ֽ���Ƿ��ӡ��");
// 	if (ret==FAILURE)
// 	{
// 		return SUCCESS;
// 	}
// 
// 	m_pCorpInfo = &m_corpInfo;
// 	memset((void *)m_pCorpInfo, 0x00, sizeof(struct TCorpInfoPrnData));
// 	
// 	//��ϵͳ�����л�ȡ����, �������ӳ��
// 	memcpy((void *)m_pCorpInfo->Nsrsbh, g_globalArg->m_corpInfo->m_Nsrsbh.c_str(), CORP_SBH_LEN);
// 	memcpy((void *)m_pCorpInfo->Nsrmc, g_globalArg->m_corpInfo->m_Nsrmc.c_str(), CORP_NAME_LEN);
// // 	memcpy((void *)m_pCorpInfo->Nsrhydm, g_globalArg->m_corpInfo->m_Hy_dm.c_str(), CORP_HYDM_LEN);
// // 	memcpy((void *)m_pCorpInfo->Nsrhymc, g_globalArg->m_corpInfo->m_Hy_mc.c_str(), CORP_HYMC_LEN);
// // 	memcpy((void *)m_pCorpInfo->Nsrjyxmzwmc, g_globalArg->m_corpInfo->m_Jyxmzwmc.c_str(), CORP_JYXMZWMC_LEN);
// 	
// 	memcpy((void *)m_pCorpInfo->Nsrswjgdm, g_globalArg->m_corpInfo->m_Swjgdm.c_str(), CORP_SWJGDM_LEN);
// 	memcpy((void *)m_pCorpInfo->Nsrswjgmc, g_globalArg->m_corpInfo->m_Swjgmc.c_str(), CORP_ZGSWGY_LEN);
// 
// 	//��ӡ
// 	if (print_corpinfo(m_pCorpInfo, 1) != 0)
// 	{
// 		strErr = "��ӡ��ҵ��Ϣʧ��!";
// 		CaMsgBox::ShowMsg(strErr);
// 		this->ReFresh();
// 		return FAILURE;
// 	}

	return SUCCESS;
}