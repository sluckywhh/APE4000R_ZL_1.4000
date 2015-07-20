/*! \file    IssueSumDateWin.cpp
   \brief    awe4000r�����ӡ�Ŀ�Ʊͳ��ʱ���������
   \author   Yu Yan
   \version  1.0
   \date     2008-9-5 
 */

#include "IssueSumDateWin.h"
#include "ReportFunc.h"
#include "sqlite3.h"

#include "CGlobalArg.h"
#include "CInvHead.h"
#include "CaProgressBar.h"
#include "PrintDriver.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CIssueSumDateWin::CIssueSumDateWin():CaWindow()
{
	m_StartDate = 0;
	m_EndDate = 0;
	m_StartTime = 0;
	m_EndTime = 0;
	m_strTimeSeg = "";

	m_iPrnType = 0;
}

CIssueSumDateWin::~CIssueSumDateWin()
{
	
}


int CIssueSumDateWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,ISSUE_SUM_DATE_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	
	//����һ��Input  ��һ��
	strcpy(title, "��ʼ����:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(8);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;
	
	//����һ��Input  �ڶ���
	strcpy(title, "��ʼʱ��:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(6);
	m_pInput2->m_InputType = m_pInput2->aINT; //�������ֻ�����ַ�
	m_pInput2->OnObject = S_OnInput2;
	
	//����һ��Input  ������
	strcpy(title, "��ֹ����:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput3=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput3->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput3->SetTitle(title,titleLen / CHAR_W);	
	m_pInput3->SetMaxLen(8);
	m_pInput3->m_InputType = m_pInput3->aINT; //�������ֻ�����ַ�
	m_pInput3->OnObject = S_OnInput3;

	//����һ��Input  ������
	strcpy(title, "��ֹʱ��:");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput4=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput4->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput4->SetTitle(title,titleLen / CHAR_W);	
	m_pInput4->SetMaxLen(6);
	m_pInput4->m_InputType = m_pInput4->aINT; //�������ֻ�����ַ�
	m_pInput4->OnObject = S_OnInput4;
	
	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	
	//����һ��Button  ������
	strcpy(title, "��ӡ");
	m_pBtn1 = new CaButton();
	curH += LINE_H;
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

int CIssueSumDateWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
			ChangeWin(FISCAL_REPORT_MENU);			
			return SUCCESS;
		  break;		
	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CIssueSumDateWin::ReFresh()
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

void CIssueSumDateWin::S_OnActive(CaWindow *obj)
{
	((CIssueSumDateWin *)obj)->DoActive();
}


void CIssueSumDateWin::DoActive()
{
	DBG_PRINT((" CIssueSumDateWin::DoActive()!"));
	
	m_pInput1->Clear();//���Input�������
	m_pInput2->Clear();//���Input�������
	m_pInput3->Clear();//���Input�������
	m_pInput4->Clear();//���Input�������

	m_pInput2->SetContentBuf((UINT8 *)"000000", 6);
	m_pInput4->SetContentBuf((UINT8 *)"235959", 6);
	
	m_StartDate = 0;
	m_EndDate = 0;
	ReFresh();	
}



void CIssueSumDateWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CIssueSumDateWin *win=(CIssueSumDateWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CIssueSumDateWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CIssueSumDateWin *win=(CIssueSumDateWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}

void CIssueSumDateWin::S_OnInput3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CIssueSumDateWin *win=(CIssueSumDateWin *)obj->GetdWin();
	win->OnInput3(iEvent,pEventData,iDataLen);
}

void CIssueSumDateWin::S_OnInput4(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CIssueSumDateWin *win=(CIssueSumDateWin *)obj->GetdWin();
	win->OnInput4(iEvent,pEventData,iDataLen);
}


void CIssueSumDateWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CIssueSumDateWin *win=(CIssueSumDateWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CIssueSumDateWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CIssueSumDateWin *win=(CIssueSumDateWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CIssueSumDateWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CIssueSumDateWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CIssueSumDateWin::OnInput3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CIssueSumDateWin::OnInput4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}


void CIssueSumDateWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 retCode;
	UINT8 ret = CheckInput();
	if(ret == SUCCESS)
	{
		INT32 status;
		CaMsgBox msgBox("��Ʊ����(1��2��3��):",CaMsgBox::MB_INPUT);
		msgBox.SetInputType(CaInput::aINT);
		msgBox.SetMaxInputLen(1);

		msgBox.ShowBox();
		status = msgBox.m_iStatus;
		if (status != OK_PRESSED)
		{
			return;
		}
		m_iPrnType = atoi((INT8 *)msgBox.GetInputContent());
		DBG_PRINT(("m_iPrnType = %d", m_iPrnType));
		if( (m_iPrnType > 3)||(m_iPrnType == 0) )
		{
			//m_iPrnType = 0;
			CaMsgBox::ShowMsg("��������ȷ�ķ�Ʊ����");
			return ;
		}
		CaProgressBar proBar("��Ϣ��ȡ��.....");
		proBar.ReFresh();
		//ͳ�Ʋ���ӡ�տ�Ʊͳ�Ʊ���
		retCode = PrnIssueSumProc();
		if (SUCCESS == retCode) 
		{
			ChangeWin(FISCAL_REPORT_MENU);	 //����˰����Ϣ����	
		}
	}	
}


void CIssueSumDateWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(FISCAL_REPORT_MENU);	 //����˰����Ϣ����		
}


UINT8 CIssueSumDateWin::CheckInput(void)
{
	DBG_PRINT(("CheckInput begin"));
	
	char *content1, *content2, *content3, *content4;
	UINT32 nNum = 0;

	content1 = (char*)(m_pInput1->m_contentBuf); 
	content2 = (char*)(m_pInput2->m_contentBuf); 
	content3 = (char*)(m_pInput3->m_contentBuf); 
	content4 = (char*)(m_pInput4->m_contentBuf); 
	DBG_PRINT(("CheckInput content1 = %s", content1));
	DBG_PRINT(("CheckInput content2 = %s", content2));


	//δ����
	if ((strlen(content1)==0)||(strlen(content2)==0))
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��������ʼ����/ʱ��");
		return FAILURE;
	}
	if ((strlen(content3)==0)||(strlen(content4)==0))
	{
		m_pInput3->SetFocus();
		CaMsgBox::ShowMsg("�������ֹ����/ʱ��");
		return FAILURE;
	}

	//�������ڱ�����8λ��
	if ((strlen(content1)!=8)||(strlen(content3)!=8))
	{
		CaMsgBox::ShowMsg("�������ڱ�����8λ��");
		return FAILURE;
	}

	//����ʱ�������6λ��
	if ((strlen(content2)!=6)||(strlen(content4)!=6))
	{
		CaMsgBox::ShowMsg("����ʱ�������6λ��");
		return FAILURE;
	}
	m_StartDate = atoi(content1);
	m_StartTime = atoi(content2);
	m_EndDate = atoi(content3);
	m_EndTime = atoi(content4);

    //����ʱ�������Ч��
	if (IsTimeValid(m_StartTime) != SUCCESS)
	{
		CaMsgBox::ShowMsg("��ʼʱ����Ч!");
		return FAILURE;
	}
	if (IsTimeValid(m_EndTime) != SUCCESS)
	{
		CaMsgBox::ShowMsg("��ֹʱ����Ч!");
		return FAILURE;
	}


	if (m_StartDate>m_EndDate) 
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ʼ����\n���ڽ�ֹ����!");
		return FAILURE;
	}
	else if ((m_StartDate==m_EndDate)&&(m_StartTime>m_EndTime)) 
	{
		CaMsgBox::ShowMsg("��ʼʱ��\n���ڽ�ֹʱ��!");
		return FAILURE;
	}

	UINT32 nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	UINT32 nCurTime = TDateTime::CurrentDateTime().FormatInt(HHMMSS);
	if (m_StartDate>nCurDate) 
	{
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ʼ���ڴ��ڵ�ǰ����!");
		return FAILURE;		
	}
	else if((m_StartDate==nCurDate)&&(m_StartTime>nCurTime))
	{
		m_pInput2->SetFocus();
		CaMsgBox::ShowMsg("��ʼʱ��\n���ڵ�ǰʱ��!");
		return FAILURE;	
	}

	if (m_StartDate<g_globalArg->m_initDate) //��ʼ����С�ڳ�ʼ������
	{
// 		m_StartDate = g_globalArg->m_initDate;//��ʼ������
// 		m_StartTime = 0;
		DBG_PRINT(("m_StartDate = %u", m_StartDate));
		DBG_PRINT(("m_initDate = %u", g_globalArg->m_initDate));
		m_pInput1->SetFocus();
		CaMsgBox::ShowMsg("��ʼ����\nС�ڳ�ʼ������!");
		return FAILURE;	
	}

	if (m_EndDate<g_globalArg->m_initDate) 
	{
		m_pInput3->SetFocus();
		CaMsgBox::ShowMsg("��ֹ����\nС�ڳ�ʼ������!");
		return FAILURE;		
	}
	if (m_EndDate>nCurDate) 
	{
		m_pInput3->SetFocus();
		CaMsgBox::ShowMsg("��ֹ����\n���ڵ�ǰ����!");
		return FAILURE;		
	}
	else if((m_EndDate==nCurDate)&&(m_EndTime>nCurTime))//���ڵ�ǰʱ��
	{
		m_EndTime = nCurTime;
	}

    
	//����Ƿ��з���������ʱ��λ��ܼ�¼
	INT8 chValue[256];
	memset((void*)chValue, 0, sizeof(chValue));

	if (m_StartDate!=m_EndDate) //��ʼ�պͽ����ղ���ͬһ��
	{
		//�м�ʱ��
		UINT32 startDay, endDay;
		TDateTime sDateTime(m_StartDate, 0);
		TDateTime eDateTime(m_EndDate, 0);
		TDateTime *sDate = &sDateTime;
		TDateTime *eDate = &eDateTime;
		DBG_ASSERT_EXIT((sDate != NULL), (" sDate == NULL!"));
		DBG_ASSERT_EXIT((eDate != NULL), (" eDate == NULL!"));
		(*sDate)++;
		(*eDate)--;
		startDay = sDate->FormatInt(YYYYMMDD);
		endDay = eDate->FormatInt(YYYYMMDD);
		sprintf(chValue, " where KPRQ >= %u and KPRQ <= %u",startDay,endDay);
		m_strTimeSeg = chValue;//���棬ͳ��ʱ��
		sDate = NULL;
		eDate = NULL;
	}

	return SUCCESS;
}


UINT8 CIssueSumDateWin::PrnIssueSumProc()
{
	DBG_PRINT(("PrnSalerSumProc()"));

	UINT8 ret;
	string strTime = "";
	INT8 chValue[256];
	memset((void*)chValue, 0, sizeof(chValue));

	//��ֽ���
	ret = YesNoMsgBox("������ֽ���Ƿ��ӡ��");
	if (ret==FAILURE)
	{
		return FAILURE;//����ӡ
	}
	if (isPaper() != 0)
	{	
		CaMsgBox::ShowMsg("��ӡ��δ��⵽ֽ");
		return FAILURE;
	}

	CaProgressBar proBar("��Ʊͳ�ƴ�ӡ��.....");
	proBar.ReFresh();

	//��ӡ����ͷ
	PrnIssueSumHead(m_StartDate, m_StartTime, m_EndDate, m_EndTime);

	if (m_StartDate!=m_EndDate) //��ʼ�պͽ����ղ���ͬһ��
	{
		ret = IssueSumHandle(0);//��Ԥ��ʱ��ε�sql���
	}
	else
	{
		ret = IssueSumHandle(1);
	}

	return ret;
}



UINT8 CIssueSumDateWin::IssueSumHandle(UINT8 nIfSameDay)
{
	DBG_PRINT(("SalerSumHandle()"));

	INT32 retCode;
	UINT32 nNorInvNum = 0;//��Ʊ����
	UINT32 nRetInvNum = 0;//��Ʊ����
	UINT32 nWasteInvNum = 0;//��Ʊ����
	INT64 norMoney = 0;//��Ʊ���
	INT64 retMoney = 0;//��Ʊ���
	INT8 chValue[512];
	memset((void*)chValue, 0, sizeof(chValue));
	UINT8 nCount = 0;
	UINT8 i = 0;
	string filterArr[3];

	if (1 == nIfSameDay) 
	{
		DBG_PRINT(("��ͬһ��"));
		nCount = 1;
		sprintf(chValue, "where KPRQ = %u and KPSJ >= %u and KPSJ <= %u ", m_StartDate, m_StartTime, m_EndTime);		
		filterArr[0] = chValue;
		DBG_PRINT(("filterArr[0] = %s", filterArr[0].c_str()));
	}
	else
	{
		DBG_PRINT(("����ͬһ��"));
		nCount = 3;
		//��ʼ��
		sprintf(chValue, "where KPRQ = %u and KPSJ >= %u ", m_StartDate, m_StartTime);
		filterArr[0] = chValue;	
		DBG_PRINT(("filterArr[0] = %s", filterArr[0].c_str()));
		//�м�ʱ��
		filterArr[1] = m_strTimeSeg;//��Ԥ��ʱ��ε�sql���
		DBG_PRINT(("filterArr[1] = %s", filterArr[1].c_str()));
		//��ֹ��
		sprintf(chValue, "where KPRQ = %u and KPSJ <= %u ", m_EndDate, m_EndTime);
		filterArr[2] = chValue;	
		DBG_PRINT(("filterArr[2] = %s", filterArr[2].c_str()));
		
	}
	
	DBG_PRINT(("*******��ʼͳ��*******************"));
	
	CInvHead invHead;
	string tmpfpdm = "";

	for(i = 0; i<nCount; i++)
	{
		invHead.m_filter = filterArr[i];
		invHead.m_filter += " order by FPDM, FPHM";
		invHead.Requery();
		retCode = invHead.MoveFirst();
		if( strcmp(tmpfpdm.c_str(), invHead.m_fpdm.c_str()) != 0 )
		{
			tmpfpdm = invHead.m_fpdm;
			PrnIssueSumCode(tmpfpdm);
		}

		while (retCode == SQLITE_ROW) 
		{
			if( strcmp(tmpfpdm.c_str(), invHead.m_fpdm.c_str()) != 0 )
			{
				tmpfpdm = invHead.m_fpdm;
				PrnIssueSumCode(tmpfpdm);
			}

			if( m_iPrnType == 0 )
				PrnIssueSumBody(invHead.m_fphm, invHead.m_kplx, invHead.m_kphjje);
			switch(invHead.m_kplx) 
			{
			case NORMAL_INV:
				if( m_iPrnType == 1 )
					PrnIssueSumBody(invHead.m_fphm, invHead.m_kplx, invHead.m_kphjje);
				nNorInvNum++;
				norMoney += invHead.m_kphjje;
				break;
			case RETURN_INV:
			case RET_MANUAL_INV:
			case RET_SPECIAL_INV:
				if( m_iPrnType == 2 )
					PrnIssueSumBody(invHead.m_fphm, invHead.m_kplx, invHead.m_kphjje);
				nRetInvNum++;
				retMoney += invHead.m_kphjje;
				break;
			case WASTE_INV:
			case WASTE_NOR:
			case WASTE_RET:
				if( m_iPrnType == 3 )
					PrnIssueSumBody(invHead.m_fphm, invHead.m_kplx, invHead.m_kphjje);
				nWasteInvNum++;
			default:;
			}
			retCode = invHead.MoveNext();
		}
		invHead.MoveEnd(); 
		if (retCode!=SQLITE_DONE) 
		{
			CaMsgBox::ShowMsg("��ѯ���ݿ����");
			return FAILURE;
		}
	}
	PrnIssueSumEnd(nNorInvNum, nRetInvNum, nWasteInvNum, norMoney, retMoney);

	DBG_PRINT(("��Ʊͳ�Ƴɹ�"));

	return SUCCESS;

}