/*! \file    ClearDepotWin.cpp
   \brief    awe4000r���۳�����ϵͳά����������
   \author   Yu Yan
   \version  1.0
   \date     2008-2-22
 */

#include <string>
#ifndef WIN32
#include <sys/timeb.h>
#endif
#include "ClearDepotWin.h"
#include "CMachine.h"
#include "CaProgressBar.h"
//#include "PowerOffData.h"
#include "SaleData.h"

#include "SysArgEditWin.h"
#include "SysArgMac.h"
#include "netdbWork.h"
#include "LANConnection.h"


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


#define CLEAR_SPEED_TEST 1
#define SQL_CMD "../sqlite3 AWE < ../awe.sql" //"./sqlite3 /usr/app/AWE < /usr/app/awe.sql" //�ؽ����ݿ�����
#define MACHINE_CMD "../sqlite3 AWE < machine.sql"
#define RM_CMD "rm -rf AWE" //"rm -rf /usr/app/AWE"   //ɾ�����ݿ��ļ�����
#define MACHINE_DIR "machine.sql"  //д����������ļ�


extern UINT8 bidirection;

CClearDepotWin::CClearDepotWin():CaWindow()
{
	m_workState = WORK_COMPLETE;	
}

CClearDepotWin::~CClearDepotWin()
{
	;	
}


int CClearDepotWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,CLEAR_DEPOT_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	
	//����һ��Input  ��һ��
	strcpy(title, "��������:");
	titleLen = strlen(title) * CHAR_W;
	curH = SCREEN_TOP_OFFSET;
	curH += LINE_H;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(12);
	m_pInput1->m_InputType = m_pInput1->aINT; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;

	m_iBtnW = (SCREEN_W - 40)/2 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/2; //Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;

	//����һ��Button  ������
	strcpy(title, "ȷ��");
	m_pBtn1 = new CaButton();
	curH += 3*LINE_H;
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

int CClearDepotWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
    UINT8 ret = 0;
	
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
		if (m_workState == WORK_COMPLETE) 
		{
			ChangeWin(MAINTENANCE_MENU);			
		}		
		return SUCCESS;
		break;
		
	default: break;		
	}
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CClearDepotWin::ReFresh()
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


void CClearDepotWin::S_OnActive(CaWindow *obj)
{
	((CClearDepotWin *)obj)->DoActive();
}


void CClearDepotWin::DoActive()
{
	DBG_PRINT((" CClearDepotWin::DoActive()!"));
	
	m_pInput1->Clear();//���Input�������
	ReFresh();	
}



void CClearDepotWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CClearDepotWin *win=(CClearDepotWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}


void CClearDepotWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CClearDepotWin *win=(CClearDepotWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}


void CClearDepotWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CClearDepotWin *win=(CClearDepotWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}


void CClearDepotWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CClearDepotWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	UINT8 ret;
	string strInfo;
	m_workState = WORK_INCOMPLETE;
	g_globalArg->m_threadIn = 0;//��������߳�ѭ��
	ret = ClearDepot(strInfo);
	if (ret==FAILURE)
	{
		CaMsgBox::ShowMsg(strInfo);
		m_workState = WORK_COMPLETE;
		g_globalArg->m_threadIn = 1;//������߳�ѭ��
	}
	else
	{
		while(1);
	}	
}


void CClearDepotWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (m_workState == WORK_COMPLETE) 
	{
		ChangeWin(MAINTENANCE_MENU);	 //���ط�Ʊ�������		
	}		

}


UINT8 CClearDepotWin::ClearDepot(string &strInfo)
{
	UINT8 ret = SUCCESS;
	INT8 *content1;
	INT32 tmp, errorcode;
	INT32 dhcpMode=0;
    string strMachineNo = "";
	bool dbRet;
	CSysArg cSysArg, *sysArg;
	sysArg = &cSysArg;

	m_workState = WORK_INCOMPLETE;

	//����Ƕ�̬IPģʽ����ָ�Ϊ��̬IPģʽ
	CNetDBWork::loadDHCPMode(&dhcpMode, strInfo);
	if (dhcpMode == LAN_DHCP_ON)
	{
		LANConnection tmpLan;
		tmpLan.setDhcpMode(LAN_DHCP_OFF, strInfo);;
	}


	content1 = (char*)(m_pInput1->m_contentBuf); 
	//�������������뵫����12λ���Ƴ�
	//û������ɼ�������
	if (strlen(content1)!=0) 
	{
		if(strlen(content1)!=12)
		{
			m_workState = WORK_COMPLETE;
			strInfo = "��������Ƿ���";	
			return(FAILURE);
		}
		strMachineNo = content1; //��������Ϊ12λ
	}
	m_pInput1->Clear();

	CMachine machine;
	machine.Requery();
	errorcode = machine.LoadOneRecord();
	if (errorcode != SQLITE_OK)//��ʼ��CMachine�����
	{	   
		DBG_PRINT((" Warning: ��һ�����"));
		machine.m_machineNo = "222222222222";
		machine.m_pDate = "20110101";
		machine.m_hVer = "hver1.0";
		machine.m_sVer = "sver1.0";			
	}
	
	//add
	INT8 sqlbuf[128];
	memset((void *)sqlbuf,0x00,sizeof(sqlbuf));

	sprintf(sqlbuf,  "where SA_ID = %d", SYS_BIDIRECTION_PRINT);
	sysArg->m_filter.append(sqlbuf);
	sysArg->Requery();
	errorcode = sysArg->LoadOneRecord();

	string sqlstr = "";
	if (errorcode != SQLITE_OK)
	{
//		sysArg->m_vString = "";
//		sysArg->m_vInt = 4;	
		;
	}
	else
	{
		if( sysArg->m_vInt>9 || sysArg->m_vInt<0 )
		{
			sysArg->m_vInt = 3;
		}

		memset((void *)sqlbuf,0x00,sizeof(sqlbuf));
		sprintf(sqlbuf, "update SYSARG set V_INT = %u, V_TEXT = '%s' where SA_ID = %d;\n", 
			sysArg->m_vInt, sysArg->m_vText.c_str(), SYS_BIDIRECTION_PRINT);
		DBG_PRINT(("sqlbuf = %s", sqlbuf));		
		sqlstr = sqlbuf;
	}


	memset((void *)sqlbuf,0x00,sizeof(sqlbuf));
	sprintf(sqlbuf,  "where SA_ID = %d", SYS_CERTIF_PSW);
	sysArg->m_filter.append(sqlbuf);
	sysArg->Requery();
	errorcode = sysArg->LoadOneRecord();
	DBG_PRINT(("errorcode= %d",errorcode));
	if (errorcode == SQLITE_OK)
	{
		memset((void *)sqlbuf,0x00,sizeof(sqlbuf));
		sprintf(sqlbuf, "update SYSARG set V_TEXT = '%s' where SA_ID = %d;\n", 
			sysArg->m_vText.c_str(), SYS_CERTIF_PSW);
		//DBG_PRINT(("sqlbuf = %s", sqlbuf));		
		sqlstr += sqlbuf;
		DBG_PRINT(("sqlstr = %s", sqlstr.c_str()));
	}

	memset((void *)sqlbuf,0x00,sizeof(sqlbuf));
	sprintf(sqlbuf,  "where SA_ID = %d", SYS_DISK_PSW);
	sysArg->m_filter.append(sqlbuf);
	sysArg->Requery();
	errorcode = sysArg->LoadOneRecord();
	DBG_PRINT(("errorcode= %d",errorcode));
	if (errorcode == SQLITE_OK)
	{
		memset((void *)sqlbuf,0x00,sizeof(sqlbuf));
		sprintf(sqlbuf, "update SYSARG set V_TEXT = '%s' where SA_ID = %d;\n", 
			sysArg->m_vText.c_str(), SYS_DISK_PSW);
	//	DBG_PRINT(("sqlbuf = %s", sqlbuf));		
		sqlstr += sqlbuf;
		DBG_PRINT(("sqlstr = %s", sqlstr.c_str()));
	}


	string strMachine("");
	//���û������������
	if ((strMachineNo.length())==12)
	{
		machine.m_machineNo = strMachineNo;
	}
	strMachine = "DELETE FROM machine; ";
	//��װд������Ϣ��ָ�� "DELETE FROM "
	strMachine += "INSERT INTO machine values('";
	strMachine += machine.m_machineNo;
	strMachine += "', '";
	strMachine += machine.m_pDate;
	strMachine += "', '";
	strMachine += machine.m_hVer;
	strMachine += "', '";
	strMachine += machine.m_sVer;
	strMachine += "');";
	DBG_PRINT((" strMachine = %s", strMachine.c_str()));

	FILE *fp1; 
	if( (fp1=fopen(MACHINE_DIR,"w"))==NULL ) 
	{ 
		fclose(fp1); 
		strInfo = "��machine.sql�ļ�����";
		DBG_PRINT((" ��machine.sql�ļ�����"));
		return FAILURE;
	} 
	INT32 nRealLen = strMachine.length();
	INT32 nLen = 0;
	nLen = fwrite(strMachine.c_str(),1, nRealLen,fp1); 
	if (nLen!=nRealLen) 
	{
		fclose(fp1); 
		strInfo = "дmachine.sql�ļ�����";
		DBG_PRINT((" дmachine.sql�ļ�����"));
		return FAILURE;
	}

	nRealLen = sqlstr.length();
	nLen = fwrite(sqlstr.c_str(),1, nRealLen,fp1); 
	if (nLen!=nRealLen) 
	{
		fclose(fp1); 
		strInfo = "дmachine.sql�ļ�����";
		DBG_PRINT((" дmachine.sql�ļ�����"));
		return FAILURE;
	}

	fclose(fp1);
	
	//ɾ�����ݿ��ļ�
	system(RM_CMD);
	DBG_PRINT((" ɾ�����ݿ��ļ�"));
	
	//�ؽ����ݿ�
	DBG_PRINT((" �ؽ����ݿ�"));
	CaProgressBar proBar("���...");
	proBar.ReFresh();
	string strCmd = SQL_CMD;
	string strCmd2 = MACHINE_CMD;
	DBG_PRINT((" strCmd = %s", strCmd.c_str()));
	DBG_PRINT((" strCmd2 = %s", strCmd2.c_str()));
	if ( system(strCmd.c_str()) != 0 )
	{
		strInfo = "������";	
        return FAILURE;
	}
	
	proBar.SetText("д������Ϣ...");
	proBar.ReFresh();
//	POWOFF_DISABLE(); //���ε����ж�
	if ( system(strCmd2.c_str()) != 0 )
	{
		strInfo = "д������Ϣ����";	
        return FAILURE;
	}
//	POWOFF_ENABLE();//�������ж�

	proBar.SetText("д������Ϣ...");
	proBar.ReFresh();

	//�ر����ݿ�
//	dbRet = CDB::GetInstance()->Close();
//	DBG_PRINT((" �ر����ݿ�"));
//	if(dbRet != true)
//	{
//		DBG_PRINT((" �ر����ݿ����"));		
//		strInfo = "�ر����ݿ����";
//		delete machine;
//		machine = NULL;
//	    return FAILURE;
//	}	

	proBar.SetText("������!��������������!");
	proBar.ReFresh();
	DBG_PRINT((" ������!��������������"));
	return SUCCESS;
}




	



	

	


    



	
