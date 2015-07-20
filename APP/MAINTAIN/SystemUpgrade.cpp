#ifndef WIN32
#include  <fcntl.h>
#endif
#include <string.h>
#include <stdlib.h>

#include "IncludeMe.h"
#include "comdatatype.h"
//#include "keypad.h"
#include "USBMount.h"
#include "powoff_protect.h"

#include "VersionConfig.h"
#include "CGlobalArg.h"
#include "SysMacDef.h"
#include "SysArgMac.h"

#include "CaLabel.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "CMainFrame.h"
#include "SystemUpgrade.h"
#include "beep.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#define VERIFY_INFO_LEN		15

CSystemUpgradeWin::CSystemUpgradeWin():CaWindow()
{
}

CSystemUpgradeWin::~CSystemUpgradeWin()
{
}

int CSystemUpgradeWin::Create(int iX,int iY,int iW,int iH)
{
	char title[OBJ_TITLE_MAX_LEN + 1];
    int titleLen=0;
	m_pFrame->RegsiterWin(this, SYSTEM_UPGRADE_WIN);    
	CaWindow::Create(iX,iY,iW,iH); // creat a window

	strcpy(title, "�� �� �� ��");
	m_pLabel = new CaLabel(false,CaObject::ALIGN_CENTER);
	m_pLabel->Create(SCREEN_LEFT_OFFSET,2, SCREEN_W, CHAR_H);
	m_pLabel->SetTitle(title, strlen(title));

	strcpy(title, "�� �� �� �� �� ��");
	m_pBtn1 = new CaButton();
	m_pBtn1->Create(SCREEN_LEFT_OFFSET+70, 50, 115, WORD_H); 
	m_pBtn1->SetTitleAlign(CaObject::ALIGN_CENTER);
	m_pBtn1->SetTitle(title, strlen(title));
	m_pBtn1->BoxType(CaObject::BOX_NO);
	m_pBtn1->OnObject = S_OnButton1;
	
	OnActive = S_OnActive;
	
	this->End();

	return 0;
}

int CSystemUpgradeWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
   return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}
bool CSystemUpgradeWin::IsCurWin()
{
	return true;
}

int CSystemUpgradeWin::ReFresh()
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

void CSystemUpgradeWin::S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen)
{
	CSystemUpgradeWin *win=(CSystemUpgradeWin *)obj->GetdWin();
	win->OnButton1(iEvent,pEventData,iDataLen);
}

void CSystemUpgradeWin::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
//	ChangeWin(PROGRAM_CTRL_MAIN_MENU);
}

void CSystemUpgradeWin::ShowMsg(string strInfo)
{
	CaProgressBar ProgressBar(strInfo.c_str());

	ProgressBar.Show();
}


/*!
@brief �ȴ����մ�������	 
*/
void CSystemUpgradeWin::S_OnActive(CaWindow *obj)
{
	((CSystemUpgradeWin *)obj)->DoActive();
}
void CSystemUpgradeWin::DoActive()
{
	UINT8 errorcode;
	UINT8 retryNum=0;
	INT32 status;
	ReFresh();

	while (1)
	{
		ShowMsg("���USB�����豸...");

		errorcode = UsbDiskMount(NULL);
 		if (errorcode != SUCCESS)
 		{
			if (retryNum < 1)
			{
				CaMsgBox msgBox("�����USB�����豸", CaMsgBox::MB_YESNO);
				msgBox.ShowBox();
				status = msgBox.m_iStatus;
			}
			if (status != OK_PRESSED || retryNum>1)
			{
				CaMsgBox::ShowMsg("δ����USB�����豸���޷�����");
				
				//ChangeWin(MAINTENANCE_MENU);
				ChangeWinUpgrade();

				return;
			}
 			retryNum++;
		}
		else
		{
			break;
		}
	}

//������������Ҫ���������ļ�FCR.BIN�����԰���awe4000r
#if (RELEASE_VER == 1)
	FILE *fp, *fpw;
	UINT8 tmpchar1, tmpchar2;
	INT32 nByte;
	UINT8 verify[VERIFY_INFO_LEN+2];
	UINT8 soft_version[VERIFY_INFO_LEN+1];
	UINT8 upBuffer[4096]; 

	ShowMsg("�����ļ������...");
	fp = fopen("/mnt/FCR.BIN", "rb");
	if (fp == NULL)
	{
		CaMsgBox::ShowMsg("δ�ҵ�U�������ļ�");
		//ChangeWin(MAINTENANCE_MENU);
		ChangeWinUpgrade();
		UsbDiskUnMount();
		return;
	}

	if ( system("mount -o remount rw /") != 0 )
	{
		CaMsgBox::ShowMsg("�������ô���");
		//ChangeWin(MAINTENANCE_MENU);
		ChangeWinUpgrade();
		UsbDiskUnMount();
		return;
	}

	// �����ļ�У�飺�ļ���ʽУ��Ͱ汾У��
	sprintf((char *)soft_version, ":AISINO%5.4f", SOFTWARE_VERSION);
	fread(verify, VERIFY_INFO_LEN, 1, fp);
	for (int j=0; j<7; j++)
	{
		if (*(verify+j) != *(soft_version+j))
		{
			CaMsgBox::ShowMsg("�Ƿ������ļ�");
			fclose(fp);
			UsbDiskUnMount();
			//ChangeWin(MAINTENANCE_MENU);
		ChangeWinUpgrade();
			return;
		}
	}

	tmpchar1 = *(verify + 7);
	tmpchar1 = (~tmpchar1) - 10;
	tmpchar2 = *(verify + 9);
	tmpchar2 = (~tmpchar2) - 30;

	if ((tmpchar1 < *(soft_version+7)) || 
		(tmpchar1 == *(soft_version+7) && tmpchar2 < *(soft_version+9)))
	{
		CaMsgBox msgBox("�����汾�ȵ�ǰ�汾�ͣ��Ƿ���Ҫ����?",CaMsgBox::MB_YESNO);
		msgBox.ShowBox();
		if (msgBox.m_iStatus != OK_PRESSED)
		{
			fclose(fp);
			UsbDiskUnMount();
			//ChangeWin(MAINTENANCE_MENU);
		ChangeWinUpgrade();
			return;
		}
	}

	// ִ������
	ShowMsg("ϵͳ����������...");
	g_globalArg->m_threadIn = 0;//��������߳�ѭ��
	MASK_ALARM_SIGNAL();
	system("rm /usr/awe4000r");
	FOR_DELAY(0xFFFFFF);

	fpw = fopen("/usr/awe4000r", "wb");
	while (!feof(fp))
	{
		nByte = fread(upBuffer, 1, 4096, fp);
		if (nByte <= 0)
		{
			fclose(fp);
			fclose(fpw);
			CaMsgBox::ShowMsg("�ļ��������󣡿�������޷�����������");
 			UsbDiskUnMount();
			CGlobalArg::SysLog(EVENT_UPDATE_SYSTEM, FAILURE);
			//ChangeWin(MAINTENANCE_MENU);
		ChangeWinUpgrade();
			return;
		}
		fwrite(upBuffer, nByte, 1, fpw);
	}	
	fclose(fp);
	fclose(fpw);
	FOR_DELAY(0xFFFFFF);

	system("chmod +x /usr/awe4000r");
	FOR_DELAY(0xFFFFF);
	system("cp /mnt/awe.sql /usr/");
	FOR_DELAY(0xFFFFF);

#else 
	ShowMsg("ϵͳ����������...");
	if ( system("ls /mnt/awe4000r") != 0 )
	{
		CaMsgBox::ShowMsg("δ�ҵ�U�������ļ�");
		UsbDiskUnMount();
		//ChangeWin(MAINTENANCE_MENU);
		ChangeWinUpgrade();
		return;
	}

	if ( system("mount -o remount rw /") != 0 )
	{
		CaMsgBox::ShowMsg("�������ô���");
		UsbDiskUnMount();
		//ChangeWin(MAINTENANCE_MENU);
		ChangeWinUpgrade();
		return;
	}

	g_globalArg->m_threadIn = 0;//��������߳�ѭ��
	system("rm /usr/awe4000r");
	FOR_DELAY(0xFFFFFF);
	
	if ( system("cp /mnt/awe4000r ../") != 0 )
	{
		CaMsgBox::ShowMsg("�ļ���������");
 		UsbDiskUnMount();
		CGlobalArg::SysLog(EVENT_UPDATE_SYSTEM, FAILURE);
		//ChangeWin(MAINTENANCE_MENU);
		ChangeWinUpgrade();
		return;
	}
	FOR_DELAY(0xFFFFFF);
	system("cp /mnt/awe.sql ../");
	FOR_DELAY(0xFFFFF);
#endif
	
 	UsbDiskUnMount();
	CGlobalArg::SysLog(EVENT_UPDATE_SYSTEM, SUCCESS);
	Beep_On();
	ShowMsg("������ɣ�����������");
	while(1);

}

void CSystemUpgradeWin::ChangeWinUpgrade()
{
	DBG_PRINT(("g_globalArg->m_operator->m_role= %u",g_globalArg->m_operator->m_role));

	if (g_globalArg->m_operator->m_role == SYSTEM_ADMINISTRATOR)
	{
		ChangeWin(MAINTENANCE_MENU);
	}
	else
	{
		ChangeWin(PROGRAM_CTRL_MAIN_MENU);
	}
return;
}


