/*! \file    InvDistQueryWin.CPP
   \brief    awe4000r��Ʊ�����ķַ���ѯ����
   \author   Yu Yan
   \version  1.0
   \date     2008-2-22
 */


#include "InvDistQueryWin.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CInvDistQueryWin::CInvDistQueryWin():CaWindow()
{
	m_workState = WORK_COMPLETE;
	m_pageIndex = 1;
	m_pageNum = 0;

	m_codelink = "";
	m_pInvVol = new CInvVol;
	DBG_ASSERT_EXIT((m_pInvVol != NULL), (" m_pInvVol == NULL!"));
	
}

CInvDistQueryWin::~CInvDistQueryWin()
{
	if(m_pInvVol != NULL)
	{
		delete m_pInvVol;
	    m_pInvVol = NULL;
	}	
}

int CInvDistQueryWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;
	

    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,INV_DIST_QUERY_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window

// 	GetVolNum(m_pageNum);//���δ����ķ�Ʊ����
// 	QueryShow(m_pInvVol, 0, m_pageIndex, m_pageNum, 0);//��֯��Ļ��ʾ��Ϣ

	//����һ����ǩ  ��һ��	
	label[0] = new CaLabel(false,CaObject::ALIGN_RIGHT);
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
	label[2]->Create(0,curH, m_iBtnW, CHAR_H);
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));

	//����һ����ǩ ������
	label[3] = new CaLabel(false,CaObject::ALIGN_LEFT);
	label[3]->Create(m_iColW,curH, m_iBtnW, CHAR_H);
	label[3]->SetTitle(title_array[3], strlen(title_array[3]));
	
	//����һ����ǩ  ������
	//label[4] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	//label[4]->Create(0,curH, SCREEN_W, CHAR_H);
	//label[4]->SetTitle(title_array[4], strlen(title_array[4]));

	m_iBtnW = (SCREEN_W - 40)/2 - 4;	//Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2;		//Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	
	//����һ��Button  ������
	strcpy(title, "ȷ��");
	m_pBtn1 = new CaButton();
	curH += LINE_H;
	m_pBtn1->Create(leftoffset_btn,curH,m_iBtnW,WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;
	m_pBtn1->Visible(false); //���ɼ�


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

int CInvDistQueryWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	UINT32 ii;
	char *content;

	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
		 if (m_workState == WORK_COMPLETE) 
		 {
			 ChangeWin(INV_MANAGE_MENU);			
		 }		
		 return SUCCESS;
	 	 break;

	case PAGEUP_KEY:

		 DBG_PRINT(("PAGEUP_KEY"));
		 if ((m_pageIndex-1)<1)
		 {
			 return FAILURE;
		 }
		 m_pageIndex--;
		 QueryShow(m_pInvVol, m_pageIndex);
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
		 QueryShow(m_pInvVol, m_pageIndex);
		 ChangeTitle();
	     ReFresh();	
		 return SUCCESS;
		 break;

	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}

int CInvDistQueryWin::ReFresh()
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

UINT8 CInvDistQueryWin::ErrMsgBox(UINT8 ret)
{
	string pText;
	switch(ret)
	{
		case PRE_INV_ERROR:
		    pText = "��ѯ�ϱʽ���ʧ��";
			break;
		case NO_DIST_INV:
		    pText = "��ǰ0��Ʊδ����";
			break;
		case QUERY_ERROR:
		    pText = "��ѯʧ��";
			break;
		default:;
	}  

	CaMsgBox::ShowMsg(pText);
	return FAILURE;	
}




void CInvDistQueryWin::S_OnActive(CaWindow *obj)
{
	((CInvDistQueryWin *)obj)->DoActive();
}


void CInvDistQueryWin::DoActive()
{
	DBG_PRINT((" CInvDistQueryWin::DoActive()!"));
	m_pageIndex = 1;
	m_codelink = "";
	INVM_GetVolNum(m_pageNum);//���δ����ķ�Ʊ����
	QueryShow(m_pInvVol, m_pageIndex);//��֯��Ļ��ʾ��Ϣ
	ChangeTitle();
	ReFresh();	
}

UINT8 CInvDistQueryWin::ChangeTitle()
{
	label[0]->SetTitle(title_array[0], strlen(title_array[0]));
	label[1]->SetTitle(title_array[1], strlen(title_array[1]));
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));
	label[3]->SetTitle(title_array[3], strlen(title_array[3]));
    //label[4]->SetTitle(title_array[4], strlen(title_array[4]));  
	return SUCCESS;
}

//--------------------------------------------------------------------------------------------------------------------
//��ȡδ���뷢Ʊ����Ϣ�����޸���Ļ��ʾ
//--------------------------------------------------------------------------------------------------------------------
UINT8 CInvDistQueryWin::QueryShow(CInvVol *pInvVol, UINT32 nPageIndex)
{
	DBG_ASSERT_EXIT((m_pInvVol != NULL), (" m_pInvVol == NULL!"));
	
	UINT8 ret = SUCCESS;
	char value[256];
	INT32 errorcode=0;
// 	INT8 chCode[INV_TYPE_CODE_PRN_LEN+1];		//��Ʊ����
	memset((void*)value, 0, sizeof(value));

	DBG_PRINT((" nPageIndex == %u", nPageIndex));
	//ҳ����ų���
	if( (nPageIndex<1) || (nPageIndex>m_pageNum) )
	{
		return FAILURE;
	}

	//���һ���ѷַ�δ����ļ�¼
	pInvVol->m_filter = "where USED_FLAG = 1 and OVER_FLAG = 1 ";
	
	sprintf(value,"and NO > %u ",(nPageIndex - 1));
		pInvVol->m_filter.append(value);
		pInvVol->m_filter.append("limit 1 ");
	
	pInvVol->Requery();  //��ѯ
	errorcode = pInvVol->LoadOneRecord();
	if (errorcode != SQLITE_OK)
	{
		ErrMsgBox(QUERY_ERROR);
		return FAILURE;
	}

    //�����Ӧ��Ʊ����
// 	memset((void *)chCode, 0, INV_TYPE_CODE_PRN_LEN+1);

	sprintf(title_array[0], "[ҳ%u/%u]", nPageIndex, m_pageNum);
	sprintf(title_array[1], "��Ʊ����: %s", pInvVol->m_code.c_str());
	sprintf(title_array[2], "ʼ��: %08u", pInvVol->m_isno);
	sprintf(title_array[3], "ֹ��: %08u", pInvVol->m_ieno);
	sprintf(title_array[4], "��������: %u", pInvVol->m_date); 

	return ret;
}

void CInvDistQueryWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvDistQueryWin *win=(CInvDistQueryWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
} 


void CInvDistQueryWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CInvDistQueryWin *win=(CInvDistQueryWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CInvDistQueryWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{

	ChangeWin(INV_MANAGE_MENU);	 //���ط�Ʊ�������	
		return ;		

  		
}


void CInvDistQueryWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (m_workState == WORK_COMPLETE) 
	{
		ChangeWin(INV_MANAGE_MENU);	 //���ط�Ʊ�������		
	}		
}










