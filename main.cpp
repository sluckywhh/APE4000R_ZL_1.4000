#include "IncludeMe.h"
#include "VersionConfig.h"

#include "PrintDriver.h"
#include "Scanner.h"
//#include "usb_keyboard.h"
#include "powoff_protect.h"
#include "vfd.h"
#include "commonFunc.h"


#include "CaProgressBar.h"
#include "CMainFrame.h"
//#include "PowOffRecover.h"
#include "CInvDet.h"
#include "CGlobalArg.h"
#include "YWXMLGY.h"

#include "SysMainMenu.h"
#include "MaintenanceMenu.h"	//xsr
#include "LoginWin.h"
#include "SaleFunc.h"
#include "BusinessBase.h"

#include "netManager.h"

#include <pthread.h>

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#if TYPE_MODE == ZHQ_MODE
#include "APIzhqProc.h"
#endif

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#include<conio.h>
#else
#include "lcd_tiny.h"
#endif

#include "keypad.h"
#include "rtc.h"
#include "beep.h"
#include "USBMount.h"


#include "CDB.h"

#include "gZip.h"


CMainFrame g_mainFrame;

pthread_mutex_t	g_net_mutex;


#ifndef WIN32
static void alarm_handler(int sig)
{

	alarm(1);
}
#endif

int main()
{
	CaProgressBar info("");

#ifdef WIN32 
	LCD_Init();
	LCDClearDisplay();
#else
	Beep_Ini();
	Beep_On();
	LCD_Init();
	info.SetText("���Ӳ����ʼ��...");
	info.ReFresh();
	KeyEnable();
	I2C_Init();
    OpenPrinterDEV();
//	PrinterComIni();
//	InitTmplate();
	// PowOff_init();	
	SPI_Init();
#endif

#ifndef WIN32 
	if (signal (SIGALRM, alarm_handler) == SIG_ERR)
	{
		exit (1);
	}
//	alarm (1);
#endif

   int i = 0; //linuxƽ̨������
   int j = 0; //linuxƽ̨������
   int key;
   char scanEndSTR[4] = {0x0d, 0x00};

	info.SetText("���ݿ��ʼ��...");
	info.ReFresh();

	pthread_mutex_init(&g_net_mutex, NULL); 
	
	CDB *m_db = CDB::GetInstance();
	m_db->Open();
	m_db->Init();
	CommonSleep(300);

	g_globalArg = CGlobalArg::GetInstance();
	g_YwXmlArg = CYWXML_GY::GetInstance();

#ifndef WIN32
//	SmartCard_Init();
#endif	

	
	UINT8 index;
	for(index = 0; index<DET_ARRAY_LEN; index++)
	{
		s_DetArray[index] = new CInvDet;
		DBG_ASSERT_EXIT((s_DetArray[index] != NULL), (" s_DetArray[index] == NULL!"));
	}//������ڵ���ָ�֮ǰ

	DBG_PRINT(("g_globalArg->InitGlobalArg() begin"));
	g_globalArg->InitGlobalArg();
	DBG_PRINT(("g_globalArg->InitGlobalArg() over"));

	string strErr("");
	g_netManager = CNetManager::GetInstance();
	if (g_netManager->init(strErr) != NET_SUCCESS)
	{ 
		DBG_PRINT(("strErr: %s", strErr.c_str()));
	}

#if TYPE_MODE ==  SKJ_MODE

	CBusinessBase::InitBusiness();

#endif

	CAPIBase::InitAPI();


//	g_globalArg->OnLineTest();  //�������ʱ��������

	CLoginWin win;			//��¼����
	win.Create(0,0,SCREEN_W,SCREEN_H);     
	g_mainFrame.CurrWin(&win); 
	win.ReFresh();     
	
	SPI_WRITE_STR("0.00");		//��������

	pthread_t threadWrt;   /**< �����߳� */

//	if (g_globalArg->m_initFlag == 1)//�ѳ�ʼ�����������߳�
//	{
//#if (ON_LINE==0)

		DBG_PRINT(("�ѳ�ʼ�����������߳�ǰ"));
		pthread_create(&threadWrt, NULL, NetCommunicate, NULL);
		DBG_PRINT(("�ѳ�ʼ�����������̺߳�"));
//#endif
//	}
	

#if RELEASE_VER
	DBG_PRINT((" *****��˰������汾��%.4f ********",SOFTWARE_VERSION));
#else
	DBG_PRINT((" *****��˰������汾��%.6f ********",SOFTWARE_VERSION));
#endif


#ifdef WIN32
	while(true)
	{
		if(_kbhit())
		{
			key =_getche();
   			if (EXIT_APP_KEY == key) 
			{
				break;
   			}
			g_mainFrame.ProcEvent(key,NULL,0);
		}
	}
#else
	
  while(true)
   	{
	  
		//��ɨ��ǹ
	  
// 		if(	ScannerStateCheck() )
// 		{
// 				//DBG_PRINT(("ScannerStateCheck!"));
// 			if (ScannerPressed_mode2(scanEndSTR) == SUCCESS)
// 			{
// 				//DBG_PRINT(("ScannerPressed_mode2  SUCCESS!"));
// 			//	DBG_PRINT(("scan:  %s", ScannerCode()));
// 				WB_LCM_BKL_ON();
// 				g_mainFrame.ProcEvent(SCANNER_EVENT_KEY, NULL, 0);
// 			}
// 		}


		//�����߳��д�����ϢҪ��ʾ
// 	//	if (1 == g_globalArg->m_ifMsg) 
// 		if ((1 == g_globalArg->m_ifMsg)&&("������������ʧ��" != g_globalArg->m_strMsg))//��������Ϣ���ݣ�by yy 20120823
// 		{
// 			DBG_PRINT(("main.cpp������Ϣ��:%s", g_globalArg->m_strMsg.c_str()));
// 			CaMsgBox::ShowMsg(g_globalArg->m_strMsg);
// 			g_globalArg->m_strMsg = "";
// 			g_globalArg->m_ifMsg = 0;
// 
// 		}

		//����ֵ
		if(	key = ReadKeypad())
   		{

#if (RELEASE_VER == 0)
			if (EXIT_APP_KEY == key) 
			{
				break;
   			}
#endif			
			WB_LCM_BKL_ON();
			g_mainFrame.ProcEvent(key,NULL,0);
   		}

		CommonSleep(50);
   	}
#endif
   
#ifndef WIN32 
	PowOff_release();
	KeyDisable();
	SPI_Release();
#endif

	for(index = 0; index<DET_ARRAY_LEN; index++)
	{
		if (NULL != s_DetArray[index]) 
		{
			delete s_DetArray[index];
		}		
	}

	pthread_exit(NULL);	
	return 1;

}

