#include <stdlib.h>
#include "SysMacDef.h"
#include "comdatatype.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "DownLoadMacWin.h"
#include "PowerOffData.h"
#include "MaintenanceFunc.h"
#include "SerialPort.h"
#include "CGlobalArg.h"
#include "arithmetic.h"

#ifndef WIN32
#include "lcd_tiny.h"
#endif

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CDownLoadMacWin::CDownLoadMacWin():CaWindow()
{
}

CDownLoadMacWin::~CDownLoadMacWin()
{
	;	
}


int CDownLoadMacWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;

    m_iBtnW = (SCREEN_W/2 - 0) ; //�ؼ��Ŀ��
	m_iColW = m_iBtnW + 0;        //�ؼ����п�
  
	m_pFrame->RegsiterWin(this,DOWNLOAD_MAC_WIN);
  
	CaWindow::Create(iX,iY,iW,iH); // creat a window

	m_pLbl1 = new CaLabel(false,CaObject::ALIGN_CENTER);
	curH = SCREEN_TOP_OFFSET;
	m_pLbl1->Create(0,curH, SCREEN_W, CHAR_H);
	m_pLbl1->SetTitle("MAC ��ַ", strlen("MAC ��ַ"));

	//����һ��Input  ��һ��
	strcpy(title, " ");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput1=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput1->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput1->SetTitle(title,titleLen / CHAR_W);	
	m_pInput1->SetMaxLen(17);
	m_pInput1->m_InputType = m_pInput1->aCHAR; //�������ֻ�����ַ�
	m_pInput1->OnObject = S_OnInput1;

	m_iBtnW = (SCREEN_W - 40)/3 - 4; //Button�Ŀ��
 	m_iColW = (SCREEN_W - 40)/3; //Button���п�
	INT32 left_offset = SCREEN_LEFT_OFFSET+8;
	INT32 leftoffset_btn = left_offset + 14;

	//����һ��Button  ������
	strcpy(title, "����");
	m_pBtn1 = new CaButton();
	curH += 2*LINE_H;
	m_pBtn1->Create(leftoffset_btn,curH,m_iBtnW,WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;
	
	//����һ��Button  ������
	strcpy(title, "�޸�");
	m_pBtn2 = new CaButton();
	m_pBtn2->Create(leftoffset_btn + m_iColW,curH,m_iBtnW,WORD_H); 
	m_pBtn2->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn2->SetTitle(title, strlen(title));
	m_pBtn2->BoxType(CaObject::BOX_NO);
	m_pBtn2->OnObject = S_OnButton2;

	strcpy(title, "����");
	m_pBtn3 = new CaButton();
	m_pBtn3->Create(leftoffset_btn+m_iColW*2,curH,m_iBtnW,WORD_H); 
	m_pBtn3->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn3->SetTitle(title, strlen(title));
	m_pBtn3->BoxType(CaObject::BOX_NO);
	m_pBtn3->OnObject = S_OnButton3;
	
	OnActive = S_OnActive;
	
	this->End();  
	return 0;
}

int CDownLoadMacWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	switch(iEvent)
	{	   
	case RETURN_MAIN_MENU: 
		ClearMacWin();
		ChangeWin(NET_SERV_MENU);						
		return SUCCESS;
		break;		
	default: 
		break;		
	}
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}


int CDownLoadMacWin::ReFresh()
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


void CDownLoadMacWin::S_OnActive(CaWindow *obj)
{
	((CDownLoadMacWin *)obj)->DoActive();
}


void CDownLoadMacWin::DoActive()
{
	INT32 res=0;
	FILE *fp;
	INT8 lineBuf[128];
	INT8 tmpBuf1[20];
	int macflag = 0;
	
	fp = fopen("/usr/app/macfile", "r");
	if( fp != NULL )
	{
		while (!feof(fp))
		{
			fgets(lineBuf, 128, fp);
			
			// ��ȡ������Ϣ
			res = sscanf(lineBuf, " ifconfig eth0 hw ether %s", tmpBuf1);
			if (res == 1)
			{
				DBG_PRINT(("MAC matched SUCCESS."));
				memcpy ((char *)m_MAC, tmpBuf1, sizeof(tmpBuf1));
				macflag = 1;
				break;
			}
		}
		fclose(fp);
		DBG_PRINT(("m_MAC = %s", m_MAC));
	}
	
	DBG_PRINT(("macflag = %d", macflag));
	if( macflag == 1 )
	{
		DispMacInfo();
	}
	else
	{
		CaMsgBox::ShowMsg("�����ļ���ʽ����");
	}
	m_pInput1->SetFocus();
	return;
}



void CDownLoadMacWin::S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CDownLoadMacWin *win=(CDownLoadMacWin *)obj->GetdWin();
	win->OnInput1(iEvent,pEventData,iDataLen);
}

void CDownLoadMacWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CDownLoadMacWin *win=(CDownLoadMacWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CDownLoadMacWin::S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CDownLoadMacWin *win=(CDownLoadMacWin *)obj->GetdWin();
	win->OnButton2(iEvent,pEventData,iDataLen);
}

void CDownLoadMacWin::S_OnButton3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CDownLoadMacWin *win=(CDownLoadMacWin *)obj->GetdWin();
	win->OnButton3(iEvent,pEventData,iDataLen);
}

void CDownLoadMacWin::OnInput1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	OnDownKey(); //�л����㵽��һ���ؼ�
	return;		
}

void CDownLoadMacWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{

	UINT8 nRet = SUCCESS;
	CaProgressBar ProgressBar("");
	
	memset(m_MAC, 0, sizeof(m_MAC));
	nRet = DownloadMAC(m_MAC, MAC_LEN);
	if(SUCCESS != nRet)
	{
		return;
	}
/*
	string strErr;
	strErr = "�Ƿ�����MAC��ַ";
	if(YesNoMsBox(strErr)==FAILURE)
	{
		return;
	}

	//����MAC
	CaProgressBar ProgressBar("");

	UINT8 Count = 0;
	INT8 Ch;
	UINT8 i; 
	INT8 buff[64];
	
	ProgressBar.SetText("��ȡMAC��Ϣ");
	ProgressBar.Show();

	//��ʼ������
	INT32 res;
	UINT8 chPut, chGet, chGetNext;
	SerialPort serial, *pSerial;
	pSerial = &serial;
	SerialPortContruct(pSerial);
	res = pSerial->InitPort(pSerial, UART0_DEV_NAME, UART0, 9600);
	if (res == FAILURE) 
	{
		pSerial->ClosePort(pSerial);
		CaMsgBox::ShowMsg("��ʼ�����ڴ���");
		return;
	}
	DBG_PRINT(("COM3: InitPort Success!"));

	//��ս������Ļ���
	UINT32 nNum;
	nNum = pSerial->GetReceiveCount(pSerial);
	if(nNum!=0)
	{
		for(i = 0; i < nNum; i++)
		{
			chGet = pSerial->GetChar(pSerial);
		}		
	}

	//��������
	UINT8 sendData[32];
	UINT8 received = 0;
	UINT16 crcsend = 0;
	memset(sendData,0,sizeof(sendData));

	sendData[0] = 0x06;
	memcpy(sendData+5, g_globalArg->m_machine->m_machineNo.c_str(), MACHINE_NO_LEN-4);

	for(i = 0; i<17; i++)
	{
		pSerial->PutChar(pSerial, sendData+i);
	}
	
	for(i=0; i<100; i++)
	{
		if (pSerial->GetReceiveCount(pSerial) != 0)
		{
			Ch = pSerial->GetChar(pSerial);
			if (Ch != 0x06)
			{
				pSerial->ClosePort(pSerial);
				CaMsgBox::ShowMsg("�����������ʹ���");
				return;
			}
			else
			{
				break;
			}
		}
		FOR_DELAY(0x2FFFFF);
	}
	
	if (i >= 100)
	{
		pSerial->ClosePort(pSerial);
		CaMsgBox::ShowMsg("�������ݴ���");
		return;
	}

	char showBuff[32];
	INT8 tmpBuf1[16];
	while(1)
	{
		buff[Count++] = pSerial->GetChar(pSerial);

		if (Count >= 22)
		{
			break;
		}
	}

	nNum = pSerial->GetReceiveCount(pSerial);
	if(nNum!=0)
	{
		for(i = 0; i < nNum; i++)
		{
			chGet = pSerial->GetChar(pSerial);
		}		
	}
	sendData[0] = 0x04;
	pSerial->PutChar(pSerial, sendData);

	memset(m_MAC, 0, sizeof(m_MAC));
	sprintf(m_MAC, "%02x:%02x:%02x:%02x:%02x:%02x",buff[16],buff[17],buff[18],buff[19],buff[20],buff[21]);

	//����MAC�ļ�
	INT8 lineBuf[128];
	FILE *fps, *fpd;
	
	system("/rw");
	system("rm /usr/app/macfile_new");
	fps = fopen("/usr/app/macfile_new", "w");

	memset(lineBuf, 0, sizeof(lineBuf));	
	sprintf(lineBuf, "#!/bin/sh\n");
	fputs(lineBuf, fps);
	memset(lineBuf, 0, sizeof(lineBuf));	
	sprintf(lineBuf, "ifconfig eth0 hw ether %s\n", m_MAC);
	fputs(lineBuf, fps);
	fclose(fps);

	//�滻ԭʼ�ļ�������籣��
	POWOFF_DISABLE();
	system("cp /usr/app/macfile_new /usr/app/macfile");
	system("chmod +x /usr/app/macfile");
	system("rm /usr/app/macfile_new");
	POWOFF_ENABLE();
	
// 	system("rm /bin/init_new");
// 	fps = fopen("/bin/init", "r");
// 	fpd = fopen("/bin/init_new", "w");
// 	
// 	while (!feof(fps))
// 	{
// 		memset(lineBuf, 0, sizeof(lineBuf));
// 		
// 		//��ȡԭʼ�ļ���һ��
// 		fgets(lineBuf, 128, fps);
// 		
// 		//����ǹؼ��У����޸�����
// 		res = sscanf(lineBuf, " ifconfig eth0 hw ether %s", tmpBuf1);
// 		{
// 			sprintf(lineBuf, "ifconfig eth0 hw ether %s\n", m_MAC);
// 		}
// 		
// 		//д�����ļ�
// 		fputs(lineBuf, fpd);
// 	}
// 	fclose(fps);
// 	fclose(fpd);
// 
// 	//�滻ԭʼ�ļ�������籣��
// 	POWOFF_DISABLE();
// 	system("cp /bin/init_new /bin/init");
// 	system("chmod +x /bin/init");
// 	POWOFF_ENABLE();*/

	//��������
	DispMacInfo();
	ProgressBar.SetText("���سɹ�,������");
	ProgressBar.Show();
	while(1);
}

void CDownLoadMacWin::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
}

void CDownLoadMacWin::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	ClearMacWin();
	ChangeWin(NET_SERV_MENU);
}

UINT8 CDownLoadMacWin::CheckInputValid(string &strErr)
{	
	return SUCCESS;
}

void CDownLoadMacWin::DispMacInfo()
{
	m_pInput1->SetContentBuf((UINT8 *)m_MAC, strlen(m_MAC));
	this->ReFresh();
}

void CDownLoadMacWin::ClearMacWin()
{
	m_pInput1->Clear();
}


