/**
 @file  ZhqBtlSetWin.h
 @brief �����ļ���ת���������д��ڲ���������
*/

#include "ZhqBtlSetWin.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "APIBase.h"
#include "CSysArg.h"
#include "SysArgMac.h"
#include "CGlobalArg.h"
#include "VersionConfig.h"
#include "SerialProtocol.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CZhqBtlSetWin::CZhqBtlSetWin():CaWindow()
{
	m_zhqbaudrate =0 ;
	m_com2baudrate =0 ;
	m_iBtnW =0;
	m_iColW =0;
}

CZhqBtlSetWin::~CZhqBtlSetWin()
{
}

int CZhqBtlSetWin::Create(int iX,int iY,int iW,int iH)
{
	int curH=0;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;
	int inputW = SCREEN_W - left_offset*4;

	m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,ZHQ_BTL_SET_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window

	//����һ��Lable  ��һ��
	curH = SCREEN_TOP_OFFSET;
	strcpy(title, "ת����ԭֵ: ");
	m_pLbl1 = new CaLabel(false,CaObject::ALIGN_LEFT);
	m_pLbl1->Create(left_offset,curH, SCREEN_W, CHAR_H);
	m_pLbl1->SetTitle(title, strlen(title));

	//����һ��Input  �ڶ���
	strcpy(title, "�� ֵ: ");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(left_offset,curH,inputW+1,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(1);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ��������
	m_pInput1->OnObject = S_OnInput1;

	strcpy(title, "1:9600  2:19200  3:38400");
	m_pLbl2 = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	m_pLbl2->Create(left_offset,curH, SCREEN_W, CHAR_H);
	m_pLbl2->SetTitle(title, strlen(title));

	strcpy(title, "4:57600  5:115200");
	m_pLbl3 = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	m_pLbl3->Create(left_offset,curH, SCREEN_W, CHAR_H);
	m_pLbl3->SetTitle(title, strlen(title));
	
	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�

	//����һ��Button  ������
	strcpy(title, "�޸�");
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

int CZhqBtlSetWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU: 
		{
			ChangeWin(ZHQ_PARA_SET_MENU);						
			return SUCCESS;
		}
		break;		
	default: 
		break;		
	}
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}

int CZhqBtlSetWin::ReFresh()
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


void CZhqBtlSetWin::S_OnActive(CaWindow *obj)
{
	((CZhqBtlSetWin *)obj)->DoActive();
}

void CZhqBtlSetWin::DoActive()
{
	DispCurInfo();
	ReFresh();
}

void CZhqBtlSetWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CZhqBtlSetWin *win=(CZhqBtlSetWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CZhqBtlSetWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); 
	return;		
}

void CZhqBtlSetWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CZhqBtlSetWin *win=(CZhqBtlSetWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CZhqBtlSetWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CZhqBtlSetWin *win=(CZhqBtlSetWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void CZhqBtlSetWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strErr("");
	if( CheckInputValid(strErr) != SUCCESS )
	{
		CaMsgBox::ShowMsg(strErr);
		return;
	}
	INT8 ret = ChangeBaudRate(strErr);
	if (SUCCESS == ret)
	{
		CaMsgBox::ShowMsg("�������޸ĳɹ�!");
		ChangeWin(ZHQ_PARA_SET_MENU);
	}
	else
	{
		CaMsgBox::ShowMsg(strErr);
	}
}

void CZhqBtlSetWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ChangeWin(ZHQ_PARA_SET_MENU);
}

void CZhqBtlSetWin::DispCurInfo()
{
	char chValue[OBJ_TITLE_MAX_LEN+1];

	switch (g_globalArg->m_zhqcomBaudRate)
	{
	case 9600:
		m_zhqbaudrate = 1;
		break;
	case 19200:
		m_zhqbaudrate = 2;
		break;
	case 38400:
		m_zhqbaudrate = 3;
		break;
	case 57600:
		m_zhqbaudrate = 4;
		break;
	case 115200:
		m_zhqbaudrate = 5;
		break;
	default:
		CaMsgBox::ShowMsg("ԭת�����������쳣");
		break;
	}
	switch (g_globalArg->m_com2BaudRate)
	{
	case 9600:
		m_com2baudrate = 1;
		break;
	case 19200:
		m_com2baudrate = 2;
		break;
	case 38400:
		m_com2baudrate = 3;
		break;
	case 57600:
		m_com2baudrate = 4;
		break;
	case 115200:
		m_com2baudrate = 5;
		break;
	default:
		CaMsgBox::ShowMsg("ԭ�������쳣");
		break;

	}

	memset(chValue, 0, sizeof(chValue));
	sprintf(chValue, "ת����ԭֵ: %u, ���ԭֵ: %u", m_zhqbaudrate,m_com2baudrate);
	DBG_ASSERT_EXIT((strlen(chValue)<=OBJ_TITLE_MAX_LEN),("Label_length over length!"));
	m_pLbl1->SetTitle(chValue, strlen(chValue));

	m_pInput1->Clear();
}

INT8 CZhqBtlSetWin::ChangeBaudRate(string &RetErr)
{
	string strErr("");
	char sqlbuf[256];
	string sqlstr("");
	INT32 errorcode = 0;
	CSysArg sysarg;
	CSysArg *psysarg = &sysarg;

	CaProgressBar proBar("�����ʸ�����...");	
	proBar.Show();

	UINT32 iBaudrate = atoi((char*)(m_pInput1->m_contentBuf));

	switch (iBaudrate)
	{
	case 1:
		psysarg->m_vInt = 9600;
		break;
	case 2:
		psysarg->m_vInt = 19200;
		break;
	case 3:
		psysarg->m_vInt = 38400;
		break;
	case 4:
		psysarg->m_vInt = 57600;
		break;
	case 5:
		psysarg->m_vInt = 115200;
		break;
	default:
		RetErr = "�Ƿ�������ֵ";
		return FAILURE;	
	}

	//����ת�����ӿڣ�����ת����������

	INT32 nRet = g_pAPIBase->SetBaudRate(psysarg->m_vInt, strErr);
	DBG_PRINT(("SetBaudRate: nRet = %d",nRet));
	if (nRet != SUCCESS)
	{
                DBG_PRINT(("strErr : %s", strErr.c_str()));
		RetErr = "����������ʧ��";
		return FAILURE;
	}

	INT8 ret = 0;

	SerialProtocol* m_serialProtocol;
	m_serialProtocol = SerialProtocol::getInstance();
	ret = m_serialProtocol->ReleasePort();
	if (SUCCESS != ret)
	{
		RetErr = "���ڹر�ʧ��!";			
		return FAILURE;
	}
	ret = m_serialProtocol->InitPort(UART_DEV_NAME, psysarg->m_vInt);
	DBG_PRINT(("ret = %d", ret));
	if (ret != SUCCESS)
	{
		RetErr = "���´򿪴���ʧ��!";			
		return FAILURE;
	}

		memset(sqlbuf,0,sizeof(sqlbuf));
		sprintf(sqlbuf, "update SYSARG set V_INT = %u where SA_ID = %d", 
			psysarg->m_vInt, SYS_COM2_BAUD_RATE);
		DBG_PRINT(("sqlbuf = %s", sqlbuf));
		sqlstr = sqlbuf;
		psysarg->SetSQL(sqlstr);
		errorcode = psysarg->ExecuteSQL();
		if (errorcode != SQLITE_OK)
		{
			RetErr = "��������ʴ�����!";			
			return FAILURE;
		}

		#if TYPE_MODE == ZHQ_MODE
			memset(sqlbuf,0,sizeof(sqlbuf));
			sprintf(sqlbuf, "update SYSARG set V_INT = %u where SA_ID = %d", 
				psysarg->m_vInt, ZHQ_COM_BAUD_RATE);
			DBG_PRINT(("sqlbuf = %s", sqlbuf));
			sqlstr = sqlbuf;
			psysarg->SetSQL(sqlstr);
			errorcode = psysarg->ExecuteSQL();
			if (errorcode != SQLITE_OK)
			{
				RetErr = "ת���������ʴ�����!";			
				return FAILURE;
			}
 		#endif

		//����ȫ�ֱ���
		g_globalArg->m_com2BaudRate = psysarg->m_vInt;
		g_globalArg->m_zhqcomBaudRate = psysarg->m_vInt;
		
		DBG_PRINT(("�������޸ĳɹ�"));
		return SUCCESS;
}

UINT8 CZhqBtlSetWin::CheckInputValid(string &strErr)
{
	INT32 iBaudrate = atoi((char*)(m_pInput1->m_contentBuf));

	if( (iBaudrate!=1) && (iBaudrate!=2) && (iBaudrate!=3)&& (iBaudrate!=4)&& (iBaudrate!=5))
	{
		strErr = "�Ƿ�������ֵ";
		return FAILURE;
	}
// 	if (m_zhqbaudrate!=m_com2baudrate)
// 	{
// 		strErr = "�����������ת������һ��";
// 		return FAILURE;
// 	}

	if( iBaudrate == m_zhqbaudrate )
	{
		strErr = "��ǰ������,�����޸�";
		return FAILURE;
	}

	return SUCCESS;
}

