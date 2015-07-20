/*! \file    InvWstWin.h
   \brief    awe4000r��Ʊ�������ѿ���Ʊ���Ͻ���
   \author   Yu Yan 
   \version  1.0
   \date     2008-2-14 
 */


#include "InvWstWin.h"


#include <string>
#include "CaProgressBar.h"
#include "keypad.h"
#include "CSysArg.h"
#include "SysArgMac.h"


#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"


CInvWstWin::CInvWstWin():CaWindow()
{
	m_pageIndex = 1;
	m_pageNum = 0;
	m_invType = WASTE_INV;

	m_pInvHead = &m_invHead;
	DBG_ASSERT_EXIT((m_pInvHead != NULL), (" m_pInvHead == NULL!"));	
}

CInvWstWin::~CInvWstWin()
{
    m_pInvHead = NULL;
}


int CInvWstWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;
	

    m_iBtnW = (SCREEN_W/2 - 16) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,INV_WST_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window


	m_pPSWin = (CInvWstQueryWin*)m_pFrame->GetWin(INV_WST_QUERY_WIN);
	m_code = m_pPSWin->m_code;
	m_invStartNo = m_pPSWin->m_invStartNo;
    m_invEndNo = m_pPSWin->m_invEndNo;
	INVM_GetInvNum(m_code, m_invStartNo, m_invEndNo, m_pageNum);//��÷�Ʊ�����
	QueryShow(m_pInvHead, 0, m_pageIndex, m_pageNum, 0);//��֯��Ļ��ʾ��Ϣ

	//����һ����ǩ  ��һ��	
	label[0] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH = SCREEN_TOP_OFFSET;
	label[0]->Create(0,curH, SCREEN_W, CHAR_H); //����������
	label[0]->SetTitle(title_array[0], strlen(title_array[0]));
  
	//����һ����ǩ  �ڶ���
	label[1] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[1]->Create(0,curH, SCREEN_W, CHAR_H); //����������
	label[1]->SetTitle(title_array[1], strlen(title_array[1]));

	
	//����һ����ǩ  ������
	label[2] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[2]->Create(0,curH, m_iBtnW-8, CHAR_H);
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));
	
	//����һ����ǩ  ������
	label[3] = new CaLabel(false,CaObject::ALIGN_LEFT);
	label[3]->Create(m_iColW-8,curH, m_iBtnW+24, CHAR_H);
	label[3]->SetTitle(title_array[3], strlen(title_array[3]));

	//����һ����ǩ  ������
	label[4] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[4]->Create(0,curH, SCREEN_W, CHAR_H);
	label[4]->SetTitle(title_array[4], strlen(title_array[4]));
	label[4]->Visible(false);

	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;

	//����һ��Button  ������
	strcpy(title, "����");
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

int CInvWstWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	UINT32 ii;
	char *content;

	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
		 ChangeWin(INV_WASTE_MENU);			
		 return SUCCESS;
	 	 break;

// 	case PAGEUP_KEY:
// 		 DBG_PRINT(("PAGEUP_KEY"));
// 		 if ((m_pageIndex-1)<1)
// 		 {
// 			 return FAILURE;
// 		 }
// 		 m_pageIndex--;
// 		 QueryShow(m_pInvHead, m_pInvHead->m_fphm, m_pageIndex, m_pageNum, 1);
// 		 ChangeTitle();
// 	     ReFresh();	
// 		 DBG_PRINT(("PAGEUP_KEY"));
// 		 return SUCCESS;
// 		 break;
// 
// 	case PAGEDOWN_KEY:
// 		 if ((m_pageIndex+1)>m_pageNum)
// 		 {
// 			 return FAILURE;
// 		 }
// 		 m_pageIndex++;
// 		 QueryShow(m_pInvHead, m_pInvHead->m_fphm, m_pageIndex, m_pageNum, 0);
// 		 ChangeTitle();
// 	     ReFresh();	
// 		 return SUCCESS;
// 		 break;

	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CInvWstWin::ReFresh()
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

UINT8 CInvWstWin::ErrMsgBox(UINT8 ret)
{
	string pText;
	switch(ret)
	{
		case NO_PAPER:
		    pText = "ûֽ��";
			break;
		case MALLOC_MEM_ERROR:
		    pText = "�����ڴ�ʧ��";
			break;
		case QUERY_ERROR:
		    pText = "��ѯʧ��";
			break;
		default:;
	}  

	CaMsgBox::ShowMsg(pText);
	return FAILURE;	
}

void CInvWstWin::S_OnActive(CaWindow *obj)
{
	((CInvWstWin *)obj)->DoActive();
}


void CInvWstWin::DoActive()
{
	DBG_PRINT((" CInvWstWin::DoActive()!"));

	m_pPSWin = (CInvWstQueryWin*)m_pFrame->GetWin(INV_WST_QUERY_WIN);
	m_code = m_pPSWin->m_code;
	m_invStartNo = m_pPSWin->m_invStartNo;
    m_invEndNo = m_pPSWin->m_invEndNo;

	m_pageIndex = 1;
//	GetInvNum(m_code, m_invStartNo, m_invEndNo, m_pageNum);//��÷�Ʊ��
	QueryShow(m_pInvHead, 0, m_pageIndex, m_pageNum, 0);//��֯��Ļ��ʾ��Ϣ
	ChangeTitle();
	ReFresh();	
}

UINT8 CInvWstWin::ChangeTitle()
{
	label[0]->SetTitle(title_array[0], strlen(title_array[0]));
	label[1]->SetTitle(title_array[1], strlen(title_array[1]));
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));
	label[3]->SetTitle(title_array[3], strlen(title_array[3]));
	label[4]->SetTitle(title_array[4], strlen(title_array[4]));

	return SUCCESS;
}


UINT8 CInvWstWin::QueryShow(CInvHead *pInvHead, UINT32 nIndex, UINT32 nPageIndex, UINT32 nPageNum, UINT8 nOrder)
{
	DBG_ASSERT_EXIT((pInvHead != NULL), (" pInvHead == NULL!"));
	
	UINT8 errorcode = SUCCESS;

	DBG_PRINT((" nPageIndex = %u", nPageIndex));

	//���һ�ŷ�Ʊ���
	INT8 val[80];
	memset((void*)val, 0, sizeof(val));
	pInvHead->m_filter = "where FPDM = ";
	sprintf(val,"'%s' and FPHM >= %u and FPHM <= %u ",m_code.c_str(),m_invStartNo,m_invEndNo);
	pInvHead->m_filter.append(val);
	
	errorcode = pInvHead->Load();
	if (errorcode != SQLITE_OK)
	{
		ErrMsgBox(QUERY_ERROR);
		return FAILURE;
	}

	switch(pInvHead->m_kplx)
	{
		case NORMAL_INV:
			 m_invType = WASTE_NOR;
			 sprintf(title_array[2], "����: ��Ʊ");
			 break;
		case RET_MANUAL_INV:
		case RET_SPECIAL_INV:
		case RETURN_INV:
			 m_invType = WASTE_RET;
			 sprintf(title_array[2], "����: ��Ʊ");
			 break;
		case WASTE_INV:
		case WASTE_NOR:
		case WASTE_RET:
			 sprintf(title_array[2], "����: ��Ʊ");
			 break;
		default:;
	}

	TDateTime tmpDate(pInvHead->m_kprq, pInvHead->m_kpsj);
    string strTmpDate = tmpDate.FormatString(YYYYMMDDHHMMSS);

	sprintf(title_array[0], "��Ʊ����: %08d", pInvHead->m_fphm);
	sprintf(title_array[1], "��Ʊʱ��: %s", strTmpDate.c_str());
//	sprintf(title_array[3], "���: %.2lf", (double)(pInvHead->m_kphjje)/100.0);
	if ((pInvHead->m_kplx==RETURN_INV)||(pInvHead->m_kplx==RET_MANUAL_INV)||(pInvHead->m_kplx==RET_SPECIAL_INV)) 
	{
		sprintf(title_array[3], "���: -%.2lf", (double)(pInvHead->m_kphjje)/100.0);
	}
	else
	{
		sprintf(title_array[3], "���: %.2lf", (double)(pInvHead->m_kphjje)/100.0);
	}
	
	return SUCCESS;
}

void CInvWstWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvWstWin *win=(CInvWstWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
} 


void CInvWstWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvWstWin *win=(CInvWstWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CInvWstWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 nRet;
	string strErr("");
	if (g_globalArg->m_operator->m_role == DEMO_ROLE) 
	{
		CaMsgBox::ShowMsg("ѧϰ��ɫ���������ѿ�Ʊ");
    	return;
	}
	nRet = CheckCancelValid();
	if (SUCCESS != nRet)
	{
		return;
	}

	CaMsgBox msgBox("�Ƿ�����?",CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
	{
		return;
	}
    else if(msgBox.m_iStatus == OK_PRESSED)
	{
		CaProgressBar proBar("��Ʊ������.....");
		proBar.Show();
		m_pInvHead->m_zskl = g_globalArg->m_strZskl;

		nRet = INVM_WstInv(m_pInvHead,strErr);
		if (SUCCESS != nRet)
		{
			CaMsgBox::ShowMsg(strErr);
			return;
		}

      CaMsgBox::ShowMsg("��Ʊ���ϳɹ�");
		ChangeWin(INV_WASTE_MENU);	 //���ط�Ʊ�������	
		return;	
	}  	
}


void CInvWstWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(INV_WASTE_MENU);	 //���ط�Ʊ�������		
}

UINT8 CInvWstWin::CheckCancelValid(void)
{
	CInvHead *pInvHead = m_pInvHead; 
	char val[256];
	INT32 errorcode;
	memset((void*)val, 0, sizeof(val));

	//��Ϊ��Ʊ������
    if( (WASTE_INV == pInvHead->m_kplx) || (WASTE_NOR == pInvHead->m_kplx)
		|| (WASTE_RET == pInvHead->m_kplx) )
    {
		CaMsgBox::ShowMsg("�������Ϸ�Ʊ"); 
		return FAILURE;
    }
	
	//��Ϊ���˷�Ʊ������
	memset((void*)val, 0, sizeof(val));
	sprintf(val,"where FPDM = '%s' and FPHM = %u",pInvHead->m_fpdm.c_str(), pInvHead->m_fphm);	
	DBG_PRINT(("val = %s", val));
	CRtInv rtInv;
	rtInv.m_filter = val;
	rtInv.Requery();

	DBG_PRINT(("m_pInvHead->m_bzkz = %s", pInvHead->m_bzkz.c_str()));
	if (rtInv.LoadOneRecord() == SQLITE_OK)//һ����Ʊ�ѱ�����������ϣ�����Ӧ�ĺ�Ʊ��������
	{
		CaMsgBox::ShowMsg("��Ʊ�ѿ���Ʊ"); 
		return FAILURE;
	}

	return SUCCESS;
}