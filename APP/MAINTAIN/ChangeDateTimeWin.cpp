#include <string.h>
#include "CGlobalArg.h"
#include "CaLabel.h"
#include "CMainFrame.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "comdatatype.h"
#include "TDateTime.h"
#include "ChangeDateTimeWin.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CChangeDateTime::CChangeDateTime():CaWindow()
{
}

CChangeDateTime::~CChangeDateTime()
{
}

int CChangeDateTime::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
	UINT8 tmpBuffer[16];
	TDateTime datacurrent = TDateTime::CurrentDateTime();
    int titleLen=0;

	memset(tmpBuffer, 0, sizeof(tmpBuffer));
	sprintf((INT8*)tmpBuffer,"%4u%02u%02u", datacurrent.Year(),datacurrent.Month(), datacurrent.DayOfMonth());

	m_pFrame->RegsiterWin(this, CHANGE_DATETIME_WIN);    
	CaWindow::Create(iX,iY,iW,iH); 

	curH = SCREEN_TOP_OFFSET;
 	m_iBtnW = (SCREEN_W - 32)/2 - 4; 
 	m_iColW = (SCREEN_W - 32)/2; 

	strcpy(title, "ϵͳ����:");
	titleLen = strlen(title) * CHAR_W + 1;

	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	curH = SCREEN_TOP_OFFSET + LINE_H;
	
	m_pInput1->Create(SCREEN_LEFT_OFFSET,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(8);
	m_pInput1->SetContentBuf(tmpBuffer,8);
	m_pInput1->OnObject = S_SetSystemDate;

	memset(tmpBuffer, 0, sizeof(tmpBuffer));
	sprintf((INT8*)tmpBuffer,"%02u%02u%02u", datacurrent.Hour(),datacurrent.Minute(), datacurrent.Second());
	strcpy(title, "ϵͳʱ��:");
	titleLen = strlen(title) * CHAR_W;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	curH += LINE_H;
	m_pInput2->Create(SCREEN_LEFT_OFFSET,curH,SCREEN_W,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(6);
 	m_pInput2->SetContentBuf(tmpBuffer,6);
    m_pInput2->OnObject = S_SetSystemTime;
	
	strcpy(title, "ȷ��");
	m_pBtn1 = new CaButton();
	curH += LINE_H;
	m_pBtn1->Create(SCREEN_LEFT_OFFSET,curH,m_iBtnW,WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_ConfirmDateTime;
	
	strcpy(title, "����");
	m_pBtn2 = new CaButton();
	m_pBtn2->Create(SCREEN_LEFT_OFFSET+m_iColW,curH,m_iBtnW,WORD_H); 
	m_pBtn2->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn2->SetTitle(title, strlen(title));
	m_pBtn2->BoxType(CaObject::BOX_NO);
	m_pBtn2->OnObject = S_DefaultDateTime;

	OnActive = S_OnActive;
	
	this->End();
	return 0;
}

int CChangeDateTime::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	DBG_PRINT(("iEvent = %x", iEvent));
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU: 
		ChangeWin(MAINTENANCE_MENU);						
		return SUCCESS;
		break;		
	default: 
		break;		
	}
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}
bool CChangeDateTime::IsCurWin()
{
	return true;
}

int CChangeDateTime::ReFresh()
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


void CChangeDateTime::S_SetSystemDate(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CChangeDateTime *win=(CChangeDateTime *)obj->GetdWin();
	win->SetSystemDate(iEvent,pEventData,iDataLen);
}

void CChangeDateTime::S_SetSystemTime(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CChangeDateTime *win=(CChangeDateTime *)obj->GetdWin();
	win->SetSystemTime(iEvent,pEventData,iDataLen);
}
void CChangeDateTime::S_ConfirmDateTime(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CChangeDateTime *win=(CChangeDateTime *)obj->GetdWin();
	win->ConfirmDateTime(iEvent,pEventData,iDataLen);
}
void CChangeDateTime::S_DefaultDateTime(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CChangeDateTime *win=(CChangeDateTime *)obj->GetdWin();
	win->DefaultDateTime(iEvent,pEventData,iDataLen);
}
void CChangeDateTime::ConfirmDateTime(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strErr;
	string result;
	TDateTime dateTime;
	

	if (CheckDateTimeValid(dateTime, strErr) != SUCCESS)
	{	
		CaMsgBox::ShowMsg(strErr);
		this->ReFresh();
		return;
	}

	CaProgressBar info("�޸�ʱ����...");
	info.Show();

	//������Ϣ�����õ�����ʱ���Ƿ���ȷ
	result = dateTime.FormatString(YYYYMMDD, NULL);
	DBG_PRINT(("��ǰ���� %s", result.c_str()));
	result = dateTime.FormatString(HHMMSS, NULL);
	DBG_PRINT(("��ǰʱ�� %s", result.c_str()));
	//END

	TDateTime::SetCurrentDateTime(dateTime);
	info.SetText("�޸�ʱ����ɣ�������");
	info.Show();
	CGlobalArg::SysLog(EVENT_SET_TIME, SUCCESS, "�����޸�ʱ��");
	while(1);

	ChangeWin(MAINTENANCE_MENU);

}

void CChangeDateTime::DefaultDateTime(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_pInput1->Clear();
	m_pInput2->Clear();
	ChangeWin(MAINTENANCE_MENU);
}

void CChangeDateTime::SetSystemDate(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strErr;
	TDateTime dateTime;
	if (CheckDateTimeValid(dateTime, strErr) != SUCCESS)
	{	
		CaMsgBox::ShowMsg(strErr);
		this->ReFresh();
		return;
	}

	m_pInput2->SetFocus();
}

void CChangeDateTime::SetSystemTime(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strErr;
	TDateTime dateTime;
	if (CheckDateTimeValid(dateTime, strErr) != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);	
		this->ReFresh();
		return;
	}

	m_pBtn1->SetFocus();
}

UINT8 CChangeDateTime::CheckDateTimeValid(TDateTime &datetime, string &strErr)
{
	char tmpStr[9];
	UINT32 year, month, day;
	UINT32 Hour, Minute, Second;
	TDateTime tmpDateTime;

	//�������ڵĺϷ���	
	if ( (m_pInput1->IsEmpty())	|| (m_pInput1->m_iConLen != 8))
	{		
		strErr = "������Ч������";
		m_pInput1->SetFocus();
		m_pInput1->Clear();
		return FAILURE; 
	}
	memset(tmpStr, 0, 9);
	memcpy(tmpStr,(char *)m_pInput1->m_contentBuf,4);
	year = atoi(tmpStr);

	memset(tmpStr, 0, 9);
	memcpy(tmpStr,(char *)m_pInput1->m_contentBuf + 4,2);
	month  = atoi(tmpStr);
	
	memset(tmpStr, 0, 9);
	memcpy(tmpStr,(char *)m_pInput1->m_contentBuf + 6,2);
	day  = atoi(tmpStr);
	
	if ( !tmpDateTime.DateIsValid(year,month,day) )
	{
		strErr = "������Ч������";
		m_pInput1->SetFocus();
		m_pInput1->Clear();
		return FAILURE; 
	}

	//����ʱ��ĺϷ���	
	if ( (m_pInput2->IsEmpty())	|| (m_pInput2->m_iConLen != 6))
	{		
		strErr = "ʱ����Ч������";
		m_pInput2->SetFocus();
		m_pInput2->Clear();
		return FAILURE; 
	}
	memset(tmpStr, 0, 9);
	memcpy(tmpStr,(char *)m_pInput2->m_contentBuf,2);
	Hour  = atoi(tmpStr);
	
	memset(tmpStr, 0, 9);
	memcpy(tmpStr,(char *)m_pInput2->m_contentBuf + 2 ,2);
	Minute  = atoi(tmpStr);

	memset(tmpStr, 0, 9);
	memcpy(tmpStr,(char *)m_pInput2->m_contentBuf + 4 ,2);
	Second  = atoi(tmpStr);
	
	if ( !tmpDateTime.TimeIsValid(Hour,Minute,Second) )
	{
		strErr = "ʱ����Ч������";
		m_pInput2->SetFocus();
		m_pInput2->Clear();
		return FAILURE; 
	}
    //��ȡ����ʱ�䣬ת����TDateTime
	TDateTime currentDateTime(year, month, day, Hour, Minute, Second);
	datetime = currentDateTime;
	
	return SUCCESS;
}

void CChangeDateTime::S_OnActive(CaWindow *obj)
{
	((CChangeDateTime *)obj)->DoActive();
}
void CChangeDateTime::DoActive()
{
	TDateTime datacurrent = TDateTime::CurrentDateTime();
	
	m_pInput1->SetContentBuf((UINT8 *)datacurrent.FormatString(YYYYMMDD, "%u%02u%02u").c_str(), 8);
	m_pInput2->SetContentBuf((UINT8 *)datacurrent.FormatString(HHMMSS, "%02u%02u%02u").c_str(), 6);
	
	ReFresh();
}

