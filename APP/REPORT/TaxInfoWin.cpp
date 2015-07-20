/*! \file    TaxInfoWin.cpp
   \brief    awe4000r�����ӡ��˰����Ϣ����
   \author   zcy
   \version  1.0
   \date     2015-6-6
 */

#include "TaxInfoWin.h"
#include "ReportFunc.h"
#include "TemplateGeneralFuc.h"
#include "commonFunc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CTaxInfoWin::CTaxInfoWin():CaWindow()
{
	m_pageIndex = 1;
	m_pageNum = 0;

	m_pTax = new CTax;
	m_recordIndex = 0;
	DBG_ASSERT_EXIT((m_pTax != NULL), (" m_pTax == NULL!"));
	
}

CTaxInfoWin::~CTaxInfoWin()
{
	if(m_pTax != NULL)
	{
		delete m_pTax;
	    m_pTax = NULL;
	}	
}

int CTaxInfoWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;
	
    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,TAX_INFO_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window

	GetTaxNum(m_pageNum);//�����Ȩ˰����������ת������ʾҳ��
	QueryShow(m_pTax, 0, m_pageIndex, m_pageNum);//��֯��Ļ��ʾ��Ϣ

	//����һ����ǩ  ��һ��	
	label[0] = new CaLabel(false,CaObject::ALIGN_RIGHT);
	curH = SCREEN_TOP_OFFSET;
	label[0]->Create(0,curH, SCREEN_W, CHAR_H); //����������
	label[0]->SetTitle(title_array[0], strlen(title_array[0]));
  
	//����һ����ǩ  �ڶ���
	label[1] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[1]->Create(SCREEN_LEFT_OFFSET,curH, SCREEN_W, CHAR_H); //����������
	label[1]->SetTitle(title_array[1], strlen(title_array[1]));

	//����һ����ǩ  ������
	label[2] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[2]->Create(SCREEN_LEFT_OFFSET,curH, SCREEN_W, CHAR_H);
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));

	//����һ����ǩ ������
	label[3] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;	
	label[3]->Create(SCREEN_LEFT_OFFSET,curH, SCREEN_W, CHAR_H);
	label[3]->SetTitle(title_array[3], strlen(title_array[3]));
	

	m_iBtnW = (SCREEN_W - 40)/2 - 4;	//Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2;		//Button���п�
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
	m_pBtn1->Visible(1); //�ɼ�


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

int CTaxInfoWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	UINT32 ii;
	char *content;

	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU

		ChangeWin(BASIC_REPORT_MENU);					
		return SUCCESS;
	 	break;

	case PAGEUP_KEY:

		 DBG_PRINT(("PAGEUP_KEY"));
		 if ((m_pageIndex-1)<1)
		 {
			 return FAILURE;
		 }
		 m_pageIndex--;
		 QueryShow(m_pTax, (m_pageIndex-1)*SHOWNUM_TAX, m_pageIndex, m_pageNum);
		 ChangeTitle();
	     ReFresh();	
		 DBG_PRINT(("PAGEUP_KEY"));
		 return SUCCESS;
		 break;

	case PAGEDOWN_KEY:
		 if ((m_pageIndex+1)>m_pageNum)
		 {
			 return FAILURE;
		 }
		 m_pageIndex++;
		 QueryShow(m_pTax, (m_pageIndex-1)*SHOWNUM_TAX, m_pageIndex, m_pageNum);
		 ChangeTitle();
	     ReFresh();	
		 DBG_PRINT(("PAGEDOWM_KEY"));
		 return SUCCESS;
		 break;

	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}

int CTaxInfoWin::ReFresh()
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

void CTaxInfoWin::S_OnActive(CaWindow *obj)
{
	((CTaxInfoWin *)obj)->DoActive();
}


void CTaxInfoWin::DoActive()
{
	DBG_PRINT((" CTaxInfoWin::DoActive()!"));
	m_pageIndex = 1;
// 	GetTaxNum(m_pageNum);//�����ʾҳ��
// 	QueryShow(m_pTax, 0, m_pageIndex, m_pageNum);//��֯��Ļ��ʾ��Ϣ
// 	ChangeTitle();
	ReFresh();	
}

UINT8 CTaxInfoWin::ChangeTitle()
{
	for (UINT32 itemp=0; itemp<=SHOWNUM_TAX; itemp++ )
	{
		label[itemp]->SetTitle(title_array[itemp], strlen(title_array[itemp]));
	}
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------------------------
//��ȡ��Ȩ˰����Ϣ�����޸���Ļ��ʾ
//--------------------------------------------------------------------------------------------------------------------
UINT8 CTaxInfoWin::QueryShow(CTax *pTax, UINT32 nIndex, UINT32 nPageIndex, UINT32 nPageNum)
{
	DBG_ASSERT_EXIT((pTax != NULL), (" pTax == NULL!"));
	
	UINT8 ret = SUCCESS;
	char value[256];
	INT32 errorcode;
	memset((void*)value, 0, sizeof(value));

	DBG_PRINT((" nPageIndex == %u", nPageIndex));
	//ҳ����ų���
	if( (nPageIndex<1) || (nPageIndex>nPageNum) )
	{
		return FAILURE;
	}

	for(UINT32 itemp=1; itemp<=SHOWNUM_TAX; itemp++)
	{
		sprintf(title_array[itemp], "");
	}

	for(UINT32 itemp=1; itemp<=SHOWNUM_TAX; itemp++)
	{
		DBG_PRINT(("itemp = %u",itemp));
		sprintf(value,"where NO > %u ",nIndex);
		pTax->m_filter.append(value);
		pTax->m_filter.append("limit 1 ");
		pTax->Requery();  //��ѯ
		errorcode = pTax->LoadOneRecord();
		if (errorcode == SQLITE_DONE)
		{
			break;
		}
		if (errorcode != SQLITE_OK)
		{
			CaMsgBox::ShowMsg("��ѯʧ��");
			return FAILURE;
		}
		sprintf(title_array[itemp], "˰��%d: %u%%", (nPageIndex-1)*SHOWNUM_TAX+itemp, pTax->m_sl);
		nIndex++;
	}

	sprintf(title_array[0], "[ҳ%u/%u]", nPageIndex, nPageNum);

	return ret;
}

void CTaxInfoWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CTaxInfoWin *win=(CTaxInfoWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
} 


void CTaxInfoWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CTaxInfoWin *win=(CTaxInfoWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CTaxInfoWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	PrintTaxInfo();
	ChangeWin(BASIC_REPORT_MENU);	 //���ػ�����Ϣ����	
	return ;		 		
}


void CTaxInfoWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(BASIC_REPORT_MENU);	 //���ػ�����Ϣ����		
	return;	
}

//-------------------------------------------------------------
//˰��������ѯ
//-------------------------------------------------------------
UINT8 CTaxInfoWin::GetTaxNum(UINT32 &nNum)
{
	DBG_ENTER("GetTaxNum(UINT32 &nNum)");
	
	INT32 errorcode;
	nNum = 0;
	INT32 nTmpNum = 0;
	CTax curTax;
	CTax *pTax = &curTax;
	DBG_ASSERT_EXIT((pTax != NULL), (" pTax == NULL!"));
	
	//��ѯ˰����������ת��ΪpageNum
	nTmpNum = pTax->GetRecordNum();
	DBG_PRINT(("nTmpNum = %d",nTmpNum));
	if (nTmpNum <= 0)
	{
		pTax = NULL;
		DBG_RETURN(FAILURE); 
	}
	if (0 == nTmpNum % SHOWNUM_TAX)//ÿҳ��ʾ3��˰��
	{
		nNum = nTmpNum/SHOWNUM_TAX;
	}
	else
	{
		nNum = nTmpNum/SHOWNUM_TAX + 1;
	}
	DBG_PRINT(("nNum = %u",nNum));
	pTax = NULL;
	DBG_PRINT((" GetTaxNum!"));
	DBG_RETURN(SUCCESS);
}

UINT8 CTaxInfoWin::PrintTaxInfo()
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

	//��ӡ
	if (print_taxiteminfo(1) != 0)	
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
