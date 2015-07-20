#include "comdatatype.h"
#include "CaProgressBar.h"
#include "CaInput.h"
#include "SysMacDef.h"
#include "CaLabel.h"
#include "CaMsgBox.h"
#include "TDateTime.h"
#include "COperator.h"

#include "CMainFrame.h"
#include "CGlobalArg.h"
#include "LoginWin.h"
#include "FiscalFun.h" //20150510_linzihao
//#include "YWXMLGY.h"//20150517_linzihao


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#define STUDY_INV_NUM   1000         /**< �ٷ�Ʊ��ķ�Ʊ�� */    
#define CONTENT_MAX_LEN 1024       /**< ��¼��ʾ֪ͨ��Ϣ���ݽ�ȡ�ĳ��� */
//#define MAX_MESSAGE_NUM			10    /**< ��ʾ֪ͨ��Ϣ������ */

CLoginWin::CLoginWin():CaWindow()
{
	m_LoginOper = &m_cLoginOper;
	m_ifStudyIn = 0;
	m_loginErrorCount = 0;
	m_DatabaseErr_Flag = 0;
}

CLoginWin::~CLoginWin()
{
}

//
int CLoginWin::Create(int iX,int iY,int iW,int iH)
{
	int curH, lineinterval, left_offset;
	int inputW, leftoffset_btn;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

	m_pFrame->RegsiterWin(this, LOGIN_WIN);    
	CaWindow::Create(iX,iY,iW,iH); 

	curH = SCREEN_TOP_OFFSET+4;
	lineinterval = LINE_H + 2;
	left_offset = SCREEN_LEFT_OFFSET+8;
	inputW = SCREEN_W - left_offset*2;

	INT8 chValue[64];
#if RELEASE_VER
	sprintf(chValue, "����Ա��¼ %.4f",SOFTWARE_VERSION);
#else
	sprintf(chValue, "����Ա��¼ %.6f",SOFTWARE_VERSION);
#endif

//	strcpy(title, "����Ա��¼");
	strcpy(title, chValue);
	m_pLabel = new CaLabel(false,CaObject::ALIGN_CENTER);
	m_pLabel->Create(SCREEN_LEFT_OFFSET,curH, SCREEN_W, CHAR_H);
	m_pLabel->SetTitle(title, strlen(title));
	curH += lineinterval;

	strcpy(title, "����Ա��ţ�");
	titleLen = strlen(title) * CHAR_W + 1;
	m_pInput1=new CaInput(CaObject::ON_LEFT, titleLen);
	m_pInput1->Create(left_offset, curH, inputW+1, LINE_H);
	m_pInput1->SetTitle(title, titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(9);
	m_pInput1->m_InputType = CaInput::aINT;
	m_pInput1->OnObject = S_OnInput1;
	curH += lineinterval;

	strcpy(title, "����Ա���룺");
	titleLen = strlen(title) * CHAR_W + 1;
	m_pInput2=new CaInput(CaObject::ON_LEFT, titleLen);
	m_pInput2->Create(left_offset, curH, inputW+1, LINE_H);
	m_pInput2->SetTitle(title, titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(9);
	m_pInput2->m_InputType = CaInput::aPASSWORD;
	m_pInput2->OnObject = S_OnInput2;
	curH += lineinterval;
	
 	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�
	leftoffset_btn = left_offset + 14;
	strcpy(title, "ȷ��");
	m_pBtn1 = new CaButton();
	m_pBtn1->Create(leftoffset_btn, curH, m_iBtnW, WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;
	
	strcpy(title, "����");
	m_pBtn2 = new CaButton();
	m_pBtn2->Create(leftoffset_btn+m_iColW, curH, m_iBtnW, WORD_H); //m_iColW δ���壬����ֵ������
	m_pBtn2->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn2->SetTitle(title, strlen(title));
	m_pBtn2->BoxType(CaObject::BOX_NO);
	m_pBtn2->OnObject = S_OnButton2;	

	this->End();
	return 0;
}

int CLoginWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
   return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


bool CLoginWin::IsCurWin()
{
	return true;
}

int CLoginWin::ReFresh()
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


void CLoginWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CLoginWin *win=(CLoginWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CLoginWin::S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CLoginWin *win=(CLoginWin *)obj->GetdWin();
	win->OnInput2(iEvent,pEventData,iDataLen);
}

void CLoginWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CLoginWin *win=(CLoginWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CLoginWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CLoginWin *win=(CLoginWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void CLoginWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{	
	m_pInput2->SetFocus();
}

void CLoginWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_pBtn1->SetFocus();
	this->ReFresh();
}

//-----------------------------------------------------------------------------
//��ȷ�ϡ���ť
//-----------------------------------------------------------------------------
void CLoginWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	DBG_PRINT(("����CLoginWin::OnButton1����"));
	
	INT8 value[128];
	INT32 errorcode;
	UINT8 OperNo;
	INT32 ret=0;
	INT32 type=0;
	string strErr(""), passwd("");
	string UK_OperStr(""), UK_OperName(""), UK_OperPwd("");
	CaProgressBar proBar("");
//	CDownLoadInvVolFun cDownloadInvProc;
	string tmp_str("");
	//	INT32 nSize = MAX_MESSAGE_NUM;
	
	if (CheckInputValid(strErr) == FAILURE) 
	{
		CaMsgBox::ShowMsg(strErr);
		this->ReFresh();
		return ;
	}

	//--------------------------------------------------------------------
	//������ݿ��Ѿ�����ʼ��
	//--------------------------------------------------------------------
	if( m_DatabaseErr_Flag == 0 )
	{
		OperNo = atoi((char *)(m_pInput1->m_contentBuf));
		passwd = (char *)(m_pInput2->m_contentBuf);

		DBG_PRINT(("OperNo == %d", OperNo));
		DBG_PRINT(("passwd == %s", passwd.c_str()));

		sprintf(value, "WHERE OP_ID = %u", OperNo);
		m_LoginOper->m_filter.append(value);
		m_LoginOper->Requery();
		errorcode = m_LoginOper->LoadOneRecord();

		if (errorcode == SQLITE_DONE)
		{
			CaMsgBox::ShowMsg("�޴˱�ŵĲ���Ա");
			m_pInput1->SetFocus();
			ReFresh();
			return ;
		}
		else if (errorcode == SQLITE_OK)
		{
			if( passwd != m_LoginOper->m_passwd )
			{
				CaMsgBox::ShowMsg("���벻��ȷ");
				m_pInput2->SetFocus();
				ReFresh();

				m_loginErrorCount++;
				if (m_loginErrorCount == 3)
				{
					CGlobalArg::SysLog(EVENT_LOGIN_SYSTEM, FAILURE, "�����������");	
					proBar.SetText("δ��Ȩ�û�������"); 
					proBar.ReFresh();
					while(1);
				}

				return ;
			}
			else
			{
				
				g_globalArg->m_operator->m_name = m_LoginOper->m_name;  
				g_globalArg->m_operator->m_opid = m_LoginOper->m_opid;
				g_globalArg->m_operator->m_passwd = m_LoginOper->m_passwd;
				g_globalArg->m_operator->m_role = m_LoginOper->m_role;

				DBG_PRINT(("g_globalArg->m_operator->m_name == %s", g_globalArg->m_operator->m_name.c_str()));
				DBG_PRINT(("g_globalArg->m_operator->m_opid == %d", g_globalArg->m_operator->m_opid));

				tmp_str = "      �� ¼ �� ��     ";
				switch(g_globalArg->m_operator->m_role) 
				{
				case SYSTEM_ADMINISTRATOR:
					tmp_str += " ��ɫ��ϵͳ����Ա";
					break;
				case DIRECTOR_OPERATOR:
					tmp_str += " ��ɫ�����ܲ���Ա";
					break;
				case NORMAL_OPERATOR:
					tmp_str += " ��ɫ����ͨ����Ա";
					break;
				case DEMO_OPERATOR:
					tmp_str += " ��ɫ���� ѧ ��";
					break;
				default:
					break;
				}
			//	CaMsgBox::ShowMsg(tmp_str);		
				//CGlobalArg::SysLog(EVENT_LOGIN_SYSTEM, SUCCESS, tmp_str);	
			}
		}
		else
		{
					CaMsgBox::ShowMsg("���ݿ����");
					m_pInput1->SetFocus();
					ReFresh();
					return ;		
		}
	}
	//--------------------------------------------------------------------
	//������ݿ�û������ʼ��
	//--------------------------------------------------------------------
	else
	{
		//���ݿ�û������ʼ��
		DBG_PRINT(("m_DatabaseErr_Flag = %d", m_DatabaseErr_Flag));
		if (m_DatabaseErr_Flag == SQLITE_MISUSE)
		{
			string OperNoStr;
			OperNoStr = (char *)(m_pInput1->m_contentBuf);
			passwd = (char *)(m_pInput2->m_contentBuf);
			DBG_PRINT(("OperNoStr = %s", OperNoStr.c_str()));
			DBG_PRINT(("passwd = %s", passwd.c_str()));
			if (OperNoStr == "999999999" && passwd == "999999999")
			{
				g_globalArg->m_operator->m_role = SYSTEM_ADMINISTRATOR;
				tmp_str += " ��ɫ��ϵͳ����Ա";
			}
			else
			{
				CaMsgBox::ShowMsg("�޴˱�ŵĲ���Ա");
				m_pInput1->SetFocus();
				ReFresh();
				return ;		
			}
		}
		else
		{
			CaMsgBox::ShowMsg("���ݿ����");
			m_pInput1->SetFocus();
			ReFresh();
			//ChangeWin(MAINTENANCE_MENU);
			return ;		
		}
	}

	//--------------------------------------------------------------------
	// UKEY����
	//--------------------------------------------------------------------

	CaMsgBox::ShowMsg(tmp_str);	//��ʾ��¼��Ϣ	
	ClearLoginWin(); 
	g_globalArg->m_threadIn = 0;
	g_globalArg->pSaveTemplateInfo->workMode = WORK_MODE; 

	//����ѧϰ��ɫ������ٵĵ�ǰ��Ʊ
	if (g_globalArg->m_operator->m_role==DEMO_ROLE) 
	{
		  g_globalArg->m_curInvVol->m_isno = 1;  /**< ��Ʊ��ʼ���� */
		  g_globalArg->m_curInvVol->m_ieno = STUDY_INV_NUM;        /**< ��Ʊ��ֹ���� */    
		  g_globalArg->m_curInvVol->m_remain = STUDY_INV_NUM;             /**< ��Ʊ��ʣ����� */
		  g_globalArg->m_curInvVol->m_usedflag = 0;             /**< ��Ʊ��ʹ�ñ�־ 1:�÷�Ʊ��δ��Ʊ 0:�ѿ�Ʊ */
		  g_globalArg->m_curInvVol->m_overflag = 1;             /**< ��Ʊ�������־ 1:δ���� 0:���� */
		
		  g_globalArg->pSaveTemplateInfo->workMode = TRAINING_MODE; 
		  m_ifStudyIn = 1;
		  //if (g_globalArg->m_initFlag == 0)//δ��ʼ�� 
		  {
//			  g_globalArg->m_invKind->m_maxSum = MAX_MONEY;
		//	  g_globalArg->m_invKind->m_minSum = 0;
// 			  g_globalArg->m_corpInfo->m_sgLmt = MAX_MONEY;
// 			  g_globalArg->m_corpInfo->m_nsLmt = MAX_MONEY;
// 			  g_globalArg->m_corpInfo->m_rsLmt = MAX_MONEY;			  
		  }		  
	}
	//������ѧϰ��ɫ
	else
	{
		DBG_PRINT(("m_ifStudyIn == %d", m_ifStudyIn));
		if (1==m_ifStudyIn) 
		{
			//��ǰ����Ϣ
			DBG_PRINT(("��ȡ��ǰ����Ϣ"));
			g_globalArg->m_curInvVol->m_remain = 0;

			DBG_PRINT(("value = %s", value));
			sprintf(value,"where USED_FLAG = %u and OVER_FLAG = %u",0,1);
			DBG_PRINT(("value = %s", value));
			DBG_PRINT(("m_filter = %s", g_globalArg->m_curInvVol->m_filter.c_str()));
			g_globalArg->m_curInvVol->m_filter.append(value); 
			DBG_PRINT(("m_filter = %s", g_globalArg->m_curInvVol->m_filter.c_str()));
			g_globalArg->m_curInvVol->Requery(); 
			errorcode = g_globalArg->m_curInvVol->LoadOneRecord(); 
			switch(errorcode)
			{
				case SQLITE_OK:
					break;
				case SQLITE_DONE:
					{
						CInvVol tmpLink;
						sprintf(value, "order by NO desc limit 1");
						tmpLink.m_filter.append(value); 
						tmpLink.Requery(); 
						errorcode = tmpLink.LoadOneRecord(); 
						DBG_PRINT(("errorcode = %d", errorcode));
						if (errorcode == SQLITE_OK)
						{
							g_globalArg->m_curInvVol->m_code = tmpLink.m_code;
						}
					}

					break;
				default:
					sprintf(value, "�赱ǰ�����ݿ��%02x", errorcode);
					CaMsgBox::ShowMsg(value);
					return;
			}
		}
		m_ifStudyIn = 0;
		if((g_globalArg->m_initFlag != 0)&&
			(g_globalArg->m_operator->m_role != SYSTEM_ADMINISTRATOR))
		{
			//��Ʊ����Ϣ����ȡ���Ʊ����Ʊ����Ϣ
			/*
			g_globalArg->m_invKind->Requery();
			errorcode = g_globalArg->m_invKind->LoadOneRecord();
			if (SQLITE_OK != errorcode)
			{
				sprintf(value, "��Ʊ����Ϣ����%u", errorcode);
				CaMsgBox::ShowMsg(value);
			}
			*/
	#if 1
			//��Ϣ����		
			if (FSC_InfoUpdate(strErr) != SUCCESS)
			{
				CaMsgBox::ShowMsg(strErr);
			}
			DBG_PRINT(("g_globalArg->m_invKind->m_bsqsrq= %s",g_globalArg->m_invKind->m_bsqsrq.c_str()));
			string curtime = TDateTime::CurrentDate().FormatString(YYYYMMDD);
			string tmpCurTime = curtime.assign(curtime, 0, 4);
			DBG_PRINT(("curtime = %s, tmpCurTime = %s",curtime.c_str(), tmpCurTime.c_str()));
			if ("1970" == tmpCurTime)
			{
				CaMsgBox::ShowMsg("�������Ϊ1970�����޸�");
				return;
			}
#endif				
		}


//		if (0 < g_globalArg->m_invKind->m_nNum)//��������
// 		{
			g_globalArg->m_threadIn = 1;//�������̵߳Ĵ��ϴ���Ʊ����
 //		}	

			
	}


	DBG_PRINT(("*****����ģʽ******��%u", g_globalArg->pSaveTemplateInfo->workMode));
	//��ʾ֪ͨ��Ϣ
//	ShowSystemMessage(msgArr, nSize);

	if (g_globalArg->m_operator->m_role == SYSTEM_ADMINISTRATOR)
	{
		g_globalArg->m_threadIn = 0;//�رմ��߳���ѭ��
		ChangeWin(MAINTENANCE_MENU);
	}
	else
	{
		ChangeWin(SYSTEM_MAIN_MENU);
	}

	m_loginErrorCount = 0;

	DBG_PRINT(("�˳�CLoginWin::OnButton1����"));
	
	return;
}

//-----------------------------------------------------------------------------
//�����ء���ť
//-----------------------------------------------------------------------------
void CLoginWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ClearLoginWin();
 
}

UINT8 CLoginWin::CheckInputValid(string &strErr)
{	
	UINT8 errorcode;
	UINT32 OperNo;
	INT8 value[64];
	
	if (m_pInput1->IsEmpty())
	{	
		strErr = "δ�������Ա���";
		m_pInput1->SetFocus();
		return FAILURE;
	}
	if (m_pInput1->m_iConLen < 3)
	{	
		strErr = "����Ա��ų�������3λ";
		m_pInput1->SetFocus();
		return FAILURE;
	}

	if (m_pInput2->IsEmpty())
	{	
		strErr = "δ�������Ա����";
		m_pInput2->SetFocus();
		return FAILURE;
	}

	//�жϲ���Ա���Ƿ�������ʾ���ݿ��Ƿ񾭹���ʼ����
	sprintf(value, "limit 1");
	m_LoginOper->Requery();
	errorcode = m_LoginOper->LoadOneRecord();
	if (errorcode != SQLITE_DONE && errorcode != SQLITE_OK)
	{
		DBG_PRINT(("m_LoginOper->LoadOneRecord Failure!"));
		m_DatabaseErr_Flag = errorcode;
	}
	else
	{
		m_DatabaseErr_Flag = 0;
		OperNo = atoi((char *)(m_pInput1->m_contentBuf));
		if (OperNo>200)
		{
			strErr = "����Ա��ŷǷ�";
			m_pInput1->SetFocus();
			return FAILURE;
		}
	}

	return SUCCESS;
}

void CLoginWin::ClearLoginWin()
{
	m_pInput1->Clear();
	m_pInput1->ReFresh();
	m_pInput2->Clear();
	m_pInput2->ReFresh();
	m_pInput1->SetFocus();
	this->ReFresh();

}
