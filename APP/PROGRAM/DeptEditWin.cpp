
#include "Scanner.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "CMainFrame.h"
#include "CGlobalArg.h"
#include "DeptEditWin.h"
#include "arithmetic.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

//���캯��
CDeptEditWin::CDeptEditWin():CMultiInputCommonWin(6)
{
	m_iNumOfInput = 6;
	m_iNumOfBtn = 3;

	m_Dept_edit = &m_dept;		//ԭ����CPlu
	m_isDeptExist = false;
}

//��������
CDeptEditWin::~CDeptEditWin()
{
//	if (m_Dept_edit != NULL)
//	{
//		delete m_Dept_edit;
//		m_Dept_edit = NULL;
//	}
}

//
int CDeptEditWin::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this, DEPT_EDIT_WIN);    
	CMultiInputCommonWin::Create(iX,iY,iW,iH);

	SetObjPara(1,"��Ʒ���룺",	CaInput::aCHAR,GOODS_CODE_LEN);
	SetObjPara(2,"��Ʒ���ƣ�",	CaInput::aCHAR,GOODS_NAME_LEN);
	SetObjPara(3,"���ۣ�",		CaInput::aFLOAT,12);	//double?
	SetObjPara(4,"˰�ʣ�",		CaInput::aFLOAT,4);	//�����ݿ�һ��,���븡����,��˰��Ϊ17%,������0.17,�����λС��20150507linzihao
	SetObjPara(5,"��λ��",	    CaInput::aCHAR,8);	
	SetObjPara(6,"����ţ�",	CaInput::aINT,2);

	SetObjPara(10," ȷ�� ");
	SetObjPara(11," ɾ�� ");
	SetObjPara(12," ���� ");

	OnActive = S_OnActive;
	
	this->ReFresh();

	return 0;
}

int CDeptEditWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	char *content;
	string code("");
	INT8 nLen  = 0;

	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU: 
		ClearDeptWin();
		ChangeWin(PROGRAM_CTRL_MAIN_MENU);						
		return SUCCESS;
		break;		
	case SCANNER_EVENT_KEY:
		content = (char*)ScannerCode();
		
		code = "";
        nLen = GOODS_CODE_LEN - strlen(content);
		if (nLen > 0)//����16λ����ǰ���㵽16λ
		{
			while(nLen > 0)
			{
				code += "0";
				nLen--;
			}
		}
		code += content;
		
		m_Dept_edit->m_spbm = code;
		m_pInput1->SetContentBuf((UINT8 *)m_Dept_edit->m_spbm.c_str(), 
			m_Dept_edit->m_spbm.length());
		ReFresh();
		return SUCCESS;		
	default: 
		break;		
	}
   return CMultiInputCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

void CDeptEditWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{	
	m_pInputList->SetFocusToObj(m_pInput2);
	ReFresh(); 
	string strSpbm = (char *)(m_pInput1->m_contentBuf);
	DBG_PRINT(("strSpbm==%s", strSpbm.c_str()));

	if( strSpbm == DErrorCode() )
	{
		CaMsgBox::ShowMsg("����Ʒ��Ų������");
		this->ReFresh();
		return;
	}
}

void CDeptEditWin::OnInput2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_pInputList->SetFocusToObj(m_pInput3);
	ReFresh(); 
}

void CDeptEditWin::OnInput3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_pInputList->SetFocusToObj(m_pInput4);
	ReFresh(); 
}

void CDeptEditWin::OnInput4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_pInputList->SetFocusToObj(m_pInput5);
	ReFresh(); 
}

void CDeptEditWin::OnInput5(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_pInputList->SetFocusToObj(m_pInput6);
	ReFresh(); 
}

void CDeptEditWin::OnInput6(int iEvent, unsigned char * pEventData, int iDataLen)
{
	m_pInputList->SetFocusToObj(m_pBtn1);
	ReFresh(); 
}


void CDeptEditWin::OnBtn1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	int errcode;
	string strErr;
	char sqlbuf[256];
	memset((void*)sqlbuf, 0, sizeof(sqlbuf));
	string sqlstr;	
	DBG_PRINT(("OnBtn1"));
	if (CheckInputValid(strErr) == FAILURE) 
	{
		CaMsgBox::ShowMsg(strErr);
		this->ReFresh();
		return ;
	}

	m_Dept_edit->m_spbm = (char *)(m_pInput1->m_contentBuf);
	DBG_PRINT(("m_Dept_edit->m_spbm==%s", m_Dept_edit->m_spbm.c_str()));
	if( m_Dept_edit->m_spbm == DErrorCode() )
	{
		m_pInputList->SetFocusToObj(m_pInput1);
		CaMsgBox::ShowMsg("����Ʒ��Ų������");
		this->ReFresh();
		return;
	}
	
	m_Dept_edit->m_spmc = (char *)(m_pInput2->m_contentBuf);
	m_Dept_edit->m_spdj = atof((char *)(m_pInput3->m_contentBuf));
	m_Dept_edit->m_spsl = atof((char *)(m_pInput4->m_contentBuf));
	m_Dept_edit->m_spdw = (char *)(m_pInput5->m_contentBuf);
	m_Dept_edit->m_blh = atoi((char *)(m_pInput6->m_contentBuf));

	DBG_PRINT(("blh = %d",m_Dept_edit->m_blh));

	CDept dept;
	if (0 != m_Dept_edit->m_blh)//����Ų�Ϊ�ղ�Ϊ0
	{ 	
		sprintf(sqlbuf, "where SP_BM <> '%s' and BLH = %u",		
			m_Dept_edit->m_spbm.c_str(), m_Dept_edit->m_blh);
		dept.m_filter = sqlbuf;
		dept.Requery();
		errcode = dept.LoadOneRecord();
		if (SQLITE_OK == errcode)
		{
			memset((void*)sqlbuf, 0, sizeof(sqlbuf));
			sprintf(sqlbuf, "�����Ϊ'%s'������ظ�", dept.m_spbm.c_str());
			m_pInputList->SetFocusToObj(m_pInput6);
			CaMsgBox::ShowMsg(sqlbuf);
			this->ReFresh();
			return ;
		}
		else if(SQLITE_DONE != errcode)
		{
			m_pInputList->SetFocusToObj(m_pInput6);
			CaMsgBox::ShowMsg("��ѯ��Ʒ��Ϣ�����");
			this->ReFresh();
			return ;
		}
	}
	CTax temptax;
	memset((void*)sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf,"where SL = %u", (UINT32)(m_Dept_edit->m_spsl*DEPT_TAX_EXTENSION));//��Ȩ˰�ʱ�CTax��˰����INT��ʽ���棬��CDept�в�һ��
	temptax.m_filter = sqlbuf;
	temptax.Requery();
	errcode = temptax.LoadOneRecord();
	if (SQLITE_DONE == errcode)
	{
		m_pInputList->SetFocusToObj(m_pInput4);
		CaMsgBox::ShowMsg("�޴���Ȩ˰��");
		this->ReFresh();
		return ;
	} 
	else if(SQLITE_OK != errcode)
	{
		m_pInputList->SetFocusToObj(m_pInput4);
		CaMsgBox::ShowMsg("��ѯ��Ȩ˰�ʱ����");
		this->ReFresh();
		return ;
	}
	else
	{ }

	if (m_isDeptExist == false)
	{
		errcode = m_Dept_edit->AddNew();
		DBG_PRINT(("errorcode=%d", errcode));
		if (errcode == SQLITE_OK)
		{
			CaMsgBox::ShowMsg("��Ʒ��ӳɹ�");
		}
		else
		{
			CaMsgBox::ShowMsg("��Ʒ��Ӵ���");
		}
	}
	else
	{
		memset((void *)sqlbuf, 0, sizeof(sqlbuf));

	    sprintf(sqlbuf, "update DEPT set SP_MC = '%s', SP_DJ = %f, SP_SL = %f, SP_DW = '%s', BLH = %u where SP_BM = '%s'",
							m_Dept_edit->m_spmc.c_str(),  m_Dept_edit->m_spdj, m_Dept_edit->m_spsl,
							m_Dept_edit->m_spdw.c_str(),  m_Dept_edit->m_blh,
							m_Dept_edit->m_spbm.c_str()
				);
		DBG_PRINT(("sqlbuf = %s", sqlbuf));
		sqlstr=sqlbuf;
		m_Dept_edit->SetSQL(sqlstr);
		errcode = m_Dept_edit->ExecuteSQL();

		if (errcode != SQLITE_OK)
		{
			strErr = "��Ʒ�޸Ĵ���";			
			return ;
		}		

		CaMsgBox::ShowMsg("��Ʒ�޸ĳɹ�");
	}

	ClearDeptWin();
	ChangeWin(PROGRAM_CTRL_MAIN_MENU);
}

void CDeptEditWin::OnBtn2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	INT8 tmpstr[32];
	INT32 res;

	if (m_isDeptExist == true)
	{
		m_Dept_edit->m_spbm = (char *)(m_pInput1->m_contentBuf);
		sprintf(tmpstr, "WHERE SP_BM = '%s'", m_Dept_edit->m_spbm.c_str());
		m_Dept_edit->m_filter.append(tmpstr);
		res = m_Dept_edit->Delete();
		if (res == SQLITE_OK)
		{
			CaMsgBox::ShowMsg("ɾ���ɹ�");
		}
		else
		{
			CaMsgBox::ShowMsg("ɾ��ʧ��");
		}
		DBG_PRINT(("res = %d", res));
	}
	else
	{
		CaMsgBox::ShowMsg("���޴˱�ŵ���Ʒ");
	}
	
	ClearDeptWin();
	ChangeWin(PROGRAM_CTRL_MAIN_MENU);
}

void CDeptEditWin::OnBtn3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ClearDeptWin();
	ChangeWin(PROGRAM_CTRL_MAIN_MENU);
}


UINT8 CDeptEditWin::CheckInputValid(string &strErr)
{
	DBG_PRINT(("CheckInputValid(string &strErr)"));
	//��Ʒ�����Ƿ�������ȷ
	if (m_pInput1->IsEmpty())
	{	
		strErr = "δ������Ʒ����";
		m_pInputList->SetFocusToObj(m_pInput1);
		return FAILURE;
	}

	//��Ʒ�����Ƿ�������ȷ
	if (m_pInput2->IsEmpty())
	{	
		strErr = "δ������Ʒ����";
		m_pInputList->SetFocusToObj(m_pInput2);
		return FAILURE;
	}

	//���������Ƿ���ȷ
	if (m_pInput3->IsEmpty())
	{	
		strErr = "δ���뵥��";
		m_pInputList->SetFocusToObj(m_pInput3);
		return FAILURE;
	}
	double dPrice = atof((char *)(m_pInput3->m_contentBuf));
// 	if (((UINT64)(PRICE_EXTENSION * dPrice)) > MAX_MONEY ) 
		if (((UINT64)(double2int(dPrice))) > MAX_MONEY_A )
	{
		DBG_PRINT(("dPrice = %f",  dPrice));
		DBG_PRINT(("MAX_MONEY_A = %lld",  MAX_MONEY_A));
		//DBG_PRINT(("PRICE_EXTENSION * dPrice = %lld", PRICE_EXTENSION * dPrice));
		strErr = "���۳���";
		m_pInputList->SetFocusToObj(m_pInput3);
		return FAILURE;		
	}
 	else if (((UINT64)(PRICE_EXTENSION * dPrice)) == 0 )
	{
		strErr = "��������Ϊ0";
		m_pInputList->SetFocusToObj(m_pInput3);
		return FAILURE;		
	}

	//˰�������Ƿ���ȷ
	if (m_pInput4->IsEmpty())
	{	
		strErr = "δ����˰��";
		m_pInputList->SetFocusToObj(m_pInput4);
		return FAILURE;
	}
	double dTax = atof((char *)(m_pInput4->m_contentBuf));
	if ( dTax >= 1.0 )
	{
		DBG_PRINT(("dTax = %f",  dTax));
		strErr = "����˰�ʲ��Ϸ�";
		m_pInputList->SetFocusToObj(m_pInput4);
		return FAILURE;		
	}

	//����������Ƿ���ȷ
	if (m_pInput6->IsEmpty())
	{	
		strErr = "δ���벿���";
		m_pInputList->SetFocusToObj(m_pInput6);
		return FAILURE;
	}

	if ( 0==atoi((char *)(m_pInput6->m_contentBuf)) )
	{
		strErr = "���������Ϊ0";
		m_pInputList->SetFocusToObj(m_pInput6);
		return FAILURE;
	}
	
	return SUCCESS;
}

void CDeptEditWin::DispDeptInfo(CDept *dept)
{
	INT8 tempstr[32];
	
	m_pInput1->SetContentBuf((UINT8 *)dept->m_spbm.c_str(), dept->m_spbm.length());

	m_pInput2->SetContentBuf((UINT8 *)dept->m_spmc.c_str(), dept->m_spmc.length());

	sprintf(tempstr, "%0.2f", dept->m_spdj);
	m_pInput3->SetContentBuf((UINT8 *)tempstr, strlen(tempstr));

	sprintf(tempstr, "%0.2f", dept->m_spsl);
	m_pInput4->SetContentBuf((UINT8 *)tempstr, strlen(tempstr));
	
	m_pInput5->SetContentBuf((UINT8 *)dept->m_spdw.c_str(), dept->m_spdw.length());

	sprintf(tempstr, "%u", dept->m_blh);
	m_pInput6->SetContentBuf((UINT8 *)tempstr, strlen(tempstr));


	m_pInputList->SetFocusToObj(m_pInput2);
}

void CDeptEditWin::ClearDeptWin()
{
	m_pInput1->Clear();
	m_pInput2->Clear();
	m_pInput3->Clear();
	m_pInput4->Clear();
	m_pInput5->Clear();
	m_pInput6->Clear();

	m_pInputList->SetFocusToObj(m_pInput2);
}

int CDeptEditWin::ReFresh()
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

void CDeptEditWin::S_OnActive(CaWindow *obj)
{
	((CDeptEditWin *)obj)->DoActive();
}
/*����Ʒ�����������ȵ�����Ϣ���ӣ�Ҫ��������Ʒ���룬
 *�����������Ѵ��������ݿ⣬�򽫸ñ����Ӧ����Ʒ��Ϣ����Input��(������)
 *��������ڣ���ѯ���Ƿ���Ӹ���Ʒ�����������input2
*/
void CDeptEditWin::DoActive()
{
	INT8 editFlag = 0;
	UINT8 errorcode;
	INT32 status;
	INT8 tmpstr[64];
	string deptNo("");
	INT32 nLen  = 0;
	string code = "";

	DBG_ENTER("CDeptEditWin::DoActive()");
	ReFresh();

//	ScannerInit();
	CaMsgBox msgBox("��Ʒ����:",CaMsgBox::MB_INPUT);
	msgBox.SetInputType(CaInput::aINT);	
	msgBox.SetMaxInputLen(GOODS_CODE_LEN);
	while (1)
	{
		code = "";
		msgBox.ShowBox();
		status = msgBox.m_iStatus;
		deptNo = (INT8 *)msgBox.GetInputContent();
		if (status != OK_PRESSED || deptNo != "")//�ܽ�������һ������OK_PRESSED��
		{
			if (status == OK_PRESSED)
			{
				nLen = GOODS_CODE_LEN - deptNo.length();
				if (nLen > 0)//����16λ����ǰ���㵽16λ
				{
					while(nLen > 0)
					{
						code += "0";
						nLen--;
					}
				}		
				code += deptNo;

				if( code == DErrorCode() )
				{
					CaMsgBox::ShowMsg("��Ʒ��Ų��Ϸ�");
					this->ReFresh();
					continue;//������˵���Ȱ���һ������OK_PRESSED�ļ��������OK_PRESSED��������deptNo�ǿգ������code��Ч�����������
				}
			}
			break;
		}
		CaMsgBox::ShowMsg("��������Ʒ����");//ֻ����OK_PRESSED��
	}
			
	if (status == OK_PRESSED)
	{
		deptNo = code;

		DBG_PRINT(("deptNo==%s", deptNo.c_str()));
		sprintf(tmpstr, "WHERE SP_BM = '%s'", deptNo.c_str());
		m_Dept_edit->m_filter.append(tmpstr);
		m_Dept_edit->Requery();
		errorcode = m_Dept_edit->LoadOneRecord();
		DBG_PRINT(("errorcode = %u", errorcode));

		switch(errorcode)
		{
		case SQLITE_DONE:
			{
				CaMsgBox msgBox2("�޴���Ʒ��Ϣ���Ƿ����?", CaMsgBox::MB_YESNO);
				msgBox2.ShowBox();
				if (msgBox2.m_iStatus == OK_PRESSED)
				{
					ClearDeptWin();
					m_pInput1->SetContentBuf((UINT8 *)deptNo.c_str(), deptNo.length());
					m_isDeptExist = false;
					editFlag = 1;
				}
				else
				{
					editFlag = 0;
				}
			}
			break;
			
		case SQLITE_OK:
			DispDeptInfo(m_Dept_edit);
			m_isDeptExist = true;
			editFlag = 1;
			break;

		default:
			CaMsgBox::ShowMsg("��Ʒ��Ϣ�����");
					editFlag = 0;
			break;
		}
	}
	else
	{
		editFlag = 0;
	}
	
	if (editFlag == 1)
	{
		m_pInputList->SetFocusToObj(m_pInput1);
		m_pInputList->SetFocusToObj(m_pInput2);
		m_pInput1->m_bReadOnly = true;
		ReFresh(); 
	}
	else
	{
		m_pInput1->m_bReadOnly = false;
		ClearDeptWin();
		ChangeWin(PROGRAM_CTRL_MAIN_MENU);
	}
}

string CDeptEditWin::DErrorCode()
{
	string errorcode("");
	for (UINT32 tempi=1; tempi<=GOODS_CODE_LEN; tempi++)
	{
		errorcode +="0";
	}
	return errorcode;
}