/*! \file    MaintenanceFunc.cpp
   \brief    awe4000r���۳�����ϵͳά���ĺ���
   \author   Yu Yan
   \version  1.0
   \date     2008-3-19
 */

#include "MaintenanceFunc.h"
#include "SelfTestFunc.h"
#include "PrintDriver.h"
#include "CaProgressBar.h"
#include "TDateTime.h"
#include "TemplatePrintInv.h"

#include "CMachine.h"
#include "SysMacDef.h"
#include "arithmetic.h"
//#include "keypad.h"
#include "SerialPort.h"
#include "PowerOffData.h"
#include "CGlobalArg.h"
//#include "printer.h"
//#include "usb_keyboard.h"
#include "keypad.h"

#ifndef WIN32
#include <sys/timeb.h>
#include "lcd_tiny.h"
#include"commonFunc.h"
#endif

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
//#include "CGlobalArg.h"


#define HEADER1         0X4F  //�������ݰ�ͷ�ĵ�һ���ж��ֽ�
#define HEADER2         0X4B  //�������ݰ�ͷ�ĵڶ����ж��ֽ�
#define HEADER_NUM      2     //�������ݰ�ͷ���ж��ֽڳ���
#define SEND_DATA_NUM   8     //�������ݰ�����(����CRCУ����), Byte
#define GET_DATA_NUM    62    //�������ݰ�����(����CRCУ����), Byte
#define CRC_NUM         2     //CRCУ����ĳ���, Byte
#define SEND_LEN_POS    4     //�������ݵĳ���ֵ������λ��
#define GET_LEN_POS     3     //�������ݵĳ���ֵ������λ��
#define	MACHINE_NO_POS  4    //���������ʼ�ֽ�������λ��
#define HARD_VER_POS    42   //Ӳ���汾����ʼ�ֽ�������λ��
#define TIME_POS        20   //����������ʼ�ֽ�������λ��
#define TIME_LEN        4    //���յ��������ڳ���, Byte
#define DOWNLOAD_BYTE_LEN	64


#define FORWARD_LINE_NUM 6  //��ֽ�߿��е�����

#define TEST_TIME_SEG  3600  //��ʱ�Լ��ʱ��������λ����

extern UINT8 bidirection;
UINT8 YesNoMsBox(string strInfo)
{
	DBG_ENTER("YesNoBox(string strInfo)");
	
	CaMsgBox msgBox(strInfo.c_str(),CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
	{
		DBG_PRINT((" msgBox.m_iStatus == NO_PRESSED!"));
		DBG_RETURN(FAILURE); 
	}
	
	if(msgBox.m_iStatus == OK_PRESSED)
	{
//		ReFresh();
		DBG_PRINT((" msgBox.m_iStatus == OK_PRESSED!"));
		DBG_RETURN(SUCCESS);		
	}
}



//------------�����Լ�

void PrintStr(INT8 *str)
{ 
	PrinterIni(bidirection);
	PrintChineseLine(str, strlen(str));
	CarriageReturn();
}

//CPU
UINT8 CPUEvent(UINT8 IfForward)
{
	LCDClearDisplay();//����
	CaProgressBar proBar("");
	if (CPUTest()==SUCCESS)
	{
		DBG_PRINT(("CPU self test success"));
		proBar.SetText("CPU״̬������");		
		PrintStr("CPU״̬������");
	}
	else
	{
		DBG_PRINT(("CPU self test fail"));
		proBar.SetText("CPU״̬���쳣");	
		PrintStr("CPU״̬���쳣");
	}
	proBar.ReFresh();
	
	if (IfForward == 1)
	{
		ForwardNLine(FORWARD_LINE_NUM);
	}
	
#ifndef WIN32
	//usleep(600000);
	CommonSleep(600);
#endif
	
	return SUCCESS;
}

//Beep
UINT8 BeepEvent(UINT8 IfForward)
{
	LCDClearDisplay();//����
	CaProgressBar proBar("�������Լ�");
	proBar.ReFresh();
	BeepTest();
//	if (BeepTest()==SUCCESS)
//	{
//		DBG_PRINT(("Beep self test success"));
//		proBar.SetText("������״̬������");		
//		PrintStr("������״̬������");
//	}
//	else
//	{
//		DBG_PRINT(("Beep self test fail"));
//		proBar.SetText("������״̬���쳣");	
//		PrintStr("������״̬���쳣");
//	}
	
	PrintStr(" ");
	PrintStr("�������Լ�");
	
	if (IfForward == 1)
	{
		ForwardNLine(FORWARD_LINE_NUM);
	}
	
#ifndef WIN32
	//usleep(600000);
	CommonSleep(600);
#endif
	
	return SUCCESS;
}

//Beep
UINT8 BoxEvent(UINT8 IfForward)
{
	LCDClearDisplay();//����
	CaProgressBar proBar("");
	
	MoneyBoxTest();
	DBG_PRINT(("Beep self test success"));
	proBar.SetText("Ǯ��״̬:");		
	PrintStr("Ǯ��״̬:");
	proBar.ReFresh();
	
	if (IfForward == 1)
	{
		ForwardNLine(FORWARD_LINE_NUM);
	}
	
#ifndef WIN32
//	usleep(600000);
	CommonSleep(600);
#endif
	
	return SUCCESS;
}

//flash
UINT8 FlashEvent(UINT8 IfForward)
{
	LCDClearDisplay();//����
	CaProgressBar proBar("");
	if (FlashTest()==SUCCESS)
	{
		DBG_PRINT(("FLASH self test success"));
		proBar.SetText("FLASH״̬������");		
		PrintStr("FLASH״̬������");
	}
	else
	{
		DBG_PRINT(("FLASH self test fail"));
		proBar.SetText("FLASH״̬���쳣");	
		PrintStr("FLASH״̬���쳣");
	}
	proBar.ReFresh();
	
	if (IfForward == 1)
	{
		ForwardNLine(FORWARD_LINE_NUM);
	}
	
#ifndef WIN32
//	usleep(600000);
	CommonSleep(600);
#endif

	return SUCCESS;
}

//RAM
UINT8 RAMEvent(UINT8 IfForward)
{
	LCDClearDisplay();//����
	CaProgressBar proBar("");
	if (RAMTest()==SUCCESS)
	{
		DBG_PRINT(("RAM self test success"));
		proBar.SetText("RAM״̬������");		
		PrintStr("RAM״̬������");
	}
	else
	{
		DBG_PRINT(("RAM self test fail"));
		proBar.SetText("RAM״̬���쳣");	
		PrintStr("RAM״̬���쳣");
	}
	proBar.ReFresh();
	
	if (IfForward == 1)
	{
		ForwardNLine(FORWARD_LINE_NUM);
	}
	
#ifndef WIN32
	//usleep(600000);
	CommonSleep(600);
#endif
	
	return SUCCESS;
}

//COM0
UINT8 COM0Event(UINT8 IfForward)
{
	LCDClearDisplay();//����
	CaProgressBar proBar("");
	if (COM0Test()==SUCCESS)
	{
		DBG_PRINT(("COM1 self test success"));
		proBar.SetText("COM1״̬������");		
		PrintStr("COM1״̬������");
	}
	else
	{
		DBG_PRINT(("COM1 self test fail"));
		proBar.SetText("COM1״̬���쳣");	
		PrintStr("COM1״̬���쳣");
	}
	proBar.ReFresh();
	
	if (IfForward == 1)
	{
		ForwardNLine(FORWARD_LINE_NUM);
	}
	
#ifndef WIN32
//	usleep(600000);
	CommonSleep(600);
#endif

	return SUCCESS;
}

//COM2
UINT8 COM2Event(UINT8 IfForward)
{
	LCDClearDisplay();//����
	CaProgressBar proBar("");
	if (COM2Test()==SUCCESS)
	{
		DBG_PRINT(("COM2 self test success"));
		proBar.SetText("COM2״̬������");		
		PrintStr("COM2״̬������");
	}
	else
	{
		DBG_PRINT(("COM2 self test fail"));
		proBar.SetText("COM2״̬���쳣");	
		PrintStr("COM2״̬���쳣");
	}
	proBar.ReFresh();
	
	if (IfForward == 1)
	{
		ForwardNLine(FORWARD_LINE_NUM);
	}
	
#ifndef WIN32
//	usleep(600000);
	CommonSleep(600);
#endif
	
	return SUCCESS;
}

//printer
UINT8 PrinterEvent(UINT8 IfForward)
{
	UINT8 i;
	LCDClearDisplay();//����
	CaProgressBar proBar("��ӡ���Լ�...");
	proBar.ReFresh();
	
	PrintStr(" ");
	PrintStr("��ӡ���Լ�");
	
	SetLineSpace(3);
	
	PrintAsciiLine("           XXXXXXXXXX", strlen("           XXXXXXXXXX"));				// ��Ʊ��
	PrintAsciiLine("           XXXXXXXXXXXXXXXX", strlen("           XXXXXXXXXXXXXXXX"));		// ������
	PrintAsciiLine("           XXXXXXXXXX", strlen("           XXXXXXXXXX"));				// �տλ
	ForwardNPoint(8);
	PrintAsciiLine("     XXXXXXXXXXXXXXXXXXXX", strlen("     XXXXXXXXXXXXXXXXXXXX"));	// ˰��
	PrintAsciiLine("         XXXXXXXX            XXX", strlen("         XXXXXXXX            XXX"));	// ��Ʊ����  �տ�Ա
	PrintAsciiLine("            XXXXXXXXXXXXXXXX", strlen("            XXXXXXXXXXXXXXXX"));		// ���λ
	
	UINT8 strlength = strlen("   XXXXXX        XXX     XXX    XXXX");
	for ( i=0; i<5; i++ )
	{
		PrintAsciiLine("   XXXXXX        XXX     XXX    XXXX", strlength);    		// ��Ŀ ���� ���� 
	}
		
	PrintAsciiLine("                                XXXX", strlen("                                XXXX"));
	PrintAsciiLine("      XXXX", strlen("      XXXX"));

	PrintAsciiLine("      XXXX XXXX XXXX XXXX XXXX", strlen("      XXXX XXXX XXXX XXXX XXXX"));

	if (IfForward == 1)
	{
		ForwardNLine(FORWARD_LINE_NUM);
	}

#ifndef WIN32
//	usleep(6000000);
	CommonSleep(600);
#endif

	return SUCCESS;	
}

//LCD
UINT8 LCDEvent(UINT8 IfForward)
{
	LCDClearDisplay();//����
	CaProgressBar proBar("��ʾ���Լ�...");
	proBar.ReFresh();
	
	PrintStr(" ");
	PrintStr("LCD�Լ�");
	
#ifndef WIN32
//	usleep(300000);
	CommonSleep(300);
#endif
	
	if (IfForward == 1)
	{
		ForwardNLine(FORWARD_LINE_NUM);
	}
	
	LCDTest();
	DBG_PRINT(("LCDTest() over"));
	return SUCCESS;	
}

//keyboard
UINT8 KeyboardEvent(UINT8 IfForward)
{
	UINT8 ret;
	LCDClearDisplay();//����
	CaProgressBar proBar("���̼��...");
	proBar.ReFresh();

#ifndef WIN32
//	usleep(600000);
	CommonSleep(600);
#endif

	PrintStr(" ");
	PrintStr("�����Լ�");

#ifndef WIN32
//	usleep(10000);
	CommonSleep(100);
#endif
		
	if (IfForward == 1)
	{
		ForwardNLine(FORWARD_LINE_NUM);
	}
	
	KeyboardTest();
	return SUCCESS;
}

//USB
UINT8 USBEvent(UINT8 IfForward)
{
	LCDClearDisplay();//����
	CaProgressBar proBar("");
	if (USBTest()==SUCCESS)
	{
		DBG_PRINT(("USB self test success"));
		proBar.SetText("USB״̬������");		
		PrintStr("USB״̬������");
	}
	else
	{
		DBG_PRINT(("USB self test fail"));
		proBar.SetText("USB״̬���쳣");	
		PrintStr("USB״̬���쳣");
	}
	proBar.ReFresh();
	
	if (IfForward == 1)
	{
		ForwardNLine(FORWARD_LINE_NUM);
	}
	
#ifndef WIN32
//	usleep(600000);
	CommonSleep(600);
#endif
	
	return SUCCESS;
}

//IC Card
// UINT8 ICCardEvent(UINT8 IfForward)
// {
// 	UINT8 ret;
// 	UINT8 tempbuff[10];
// 	memset((void *)tempbuff, 0, 10);
// 	
// 	LCDClearDisplay();//����
// 	CaProgressBar proBar("˰�ؿ����...");
// 	proBar.ReFresh();
// 
// #ifndef WIN32
// 	usleep(600000);
// #endif
// 	
// 	if ((ret = reset_card(FISCAL_CARD_NAD)) != IC_SUCCESS)
// 	{
// 		proBar.SetText("˰�ؿ�״̬���쳣");
// 		PrintStr("˰�ؿ�״̬���쳣");
// 		DBG_PRINT(("˰�ؿ�״̬���쳣, ret = %u", ret));
// 	}
// 	else
// 	{
// 		if (rand_card(FISCAL_CARD_NAD, tempbuff) == IC_SUCCESS)
// 		{
// 			proBar.SetText("˰�ؿ�״̬������");
// 			PrintStr("˰�ؿ�״̬������");
// 			DBG_PRINT(("˰�ؿ�״̬������"));
// 
// 			// ����У��PIN��
// //			if (icData.baseInfo_f.register_flag == 0)
// //			{
// 				if (verify_fiscal_pin(NULL) != IC_SUCCESS)	
// 				{
// 					if (verify_fiscal_pin(g_globalArg->m_corpInfo->m_fcPin) != IC_SUCCESS)	
// 					{
// 						proBar.SetText("У��PIN��ʧ��.");
// 					}
// 				}
// //			}
// //			else
// //			{
// //				proBar.SetText("�Ǳ���˰�ؿ�");
// //			}
// 		}
// 		else
// 		{
// 			proBar.SetText("˰�ؿ�״̬���쳣");
// 			PrintStr("˰�ؿ�״̬���쳣");
// 			DBG_PRINT(("˰�ؿ�״̬���쳣"));
// 		}
// 	}
// 	proBar.ReFresh();
// 
// #ifndef WIN32
// 	usleep(600000);
// #endif
// 	
// 	memset((void *)tempbuff, 0, 10);
// 	proBar.SetText("�û������...");
// 	proBar.ReFresh();
// 
// 	if ((ret = reset_card(USER_CARD_NAD))!= IC_SUCCESS)
// 	{
// 		proBar.SetText("�û���״̬���쳣");
// 		PrintStr("�û���״̬���쳣");
// 		DBG_PRINT(("�û���״̬���쳣, ret = %u", ret));
// 	}
// 	else
// 	{
// 		if (rand_card(USER_CARD_NAD, tempbuff) == IC_SUCCESS)
// 		{
// 			proBar.SetText("�û���״̬������");
// 			PrintStr("�û���״̬������");
// 			DBG_PRINT(("�û���״̬������"));
// 		}
// 		else
// 		{
// 			proBar.SetText("�û���״̬���쳣");
// 			PrintStr("�û���״̬���쳣");
// 			DBG_PRINT(("�û���״̬���쳣"));
// 		}
// 	}
// 	proBar.ReFresh();
// 
// #ifndef WIN32
// 	usleep(600000);
// #endif
// 	
// 	if (IfForward == 1)
// 	{
// 		ForwardNLine(FORWARD_LINE_NUM);
// 	}
// //	else
// //	{
// //		ForwardNLine(FORWARD_LINE_NUM*2);
// //	}
// 	
// 	return SUCCESS;
// }

//continuous test
UINT8 ContinuousTestEvent(void)
{
	UINT8 IfForward = 0;
	
	// CPU���
	DBG_PRINT(("------------CPU check------------"));
	CPUEvent(IfForward);
	
	// RAM���
	DBG_PRINT(("------------RAM check------------"));
	RAMEvent(IfForward);
	
	// FLASH���
	DBG_PRINT(("------------FLASH check------------"));
	FlashEvent(IfForward);
	
	// LCD��ʾ�����
	DBG_PRINT(("------------LCD check------------"));
	LCDEvent(IfForward);
	
	// ��ӡ�����
	DBG_PRINT(("------------Printer check------------"));
	PrinterEvent(IfForward);
	
	// ���̼��
//	DBG_PRINT(("------------Keyboard check------------"));
//	KeyboardEvent(IfForward);
	
	// ����0�Ի����
//	DBG_PRINT(("------------COM0 check------------"));
//	COM0Event(IfForward);
	
	// ����2�Ի����
	DBG_PRINT(("------------COM3 check------------"));
	COM2Event(IfForward);
	
	// Ǯ����
	DBG_PRINT(("------------Money Box check------------"));
	BoxEvent(IfForward);
	
	// ���������
//	DBG_PRINT(("------------Buzzer check------------"));
	BeepEvent(IfForward);
	
	// USB���
	DBG_PRINT(("------------USB check------------"));
	USBEvent(IfForward);

	// IC card���
	//DBG_PRINT(("------------IC Card check------------"));
	//ICCardEvent(IfForward);
	
	ForwardNLine(FORWARD_LINE_NUM);
	return SUCCESS;
}

//Auto test
UINT8 MachineAutoCheck(void)
{
	UINT64 fTime, fTime2, interval;
#ifndef WIN32
	struct timeb tp;
	ftime(&tp);
	fTime = tp.time;
#endif

	CaProgressBar proBar("");
    UINT8 IfForward = 0;
	UINT8 firstTime = 1;
	
	DBG_PRINT(("begin to machine's self check"));
	
	for (;;)
	{
#ifndef WIN32
		ftime(&tp);
		fTime2 = tp.time;
#endif
		interval = fTime2-fTime;
		
		if ((interval < (TEST_TIME_SEG+10) && interval >= TEST_TIME_SEG) || firstTime == 1) 
		{
			//�ж�װ��ֽ�ʷ�Ʊ	
			if (isPaper() != 0)
			{		
				CaMsgBox::ShowMsg("��װ��ֽ�ʷ�Ʊ");
				return SUCCESS;
			}
			DBG_PRINT((" MachineAutoCheck��interval = %llu ", interval));
			if (firstTime == 1)
			{
				firstTime = 0;
			}		
			fTime = fTime2;
			DBG_PRINT(("begin to machine's self check"));	
			// CPU���
			DBG_PRINT(("------------CPU check------------"));
			CPUEvent(IfForward);
			
			// RAM���
			DBG_PRINT(("------------RAM check------------"));
			RAMEvent(IfForward);
			
			// FLASH���
			DBG_PRINT(("------------FLASH check------------"));
			FlashEvent(IfForward);
			
			// LCD��ʾ�����
			DBG_PRINT(("------------LCD check------------"));
			LCDEvent(IfForward);
			
			// ��ӡ�����
			DBG_PRINT(("------------Printer check------------"));
			PrinterEvent(IfForward);
			
			// ���̼��
//			DBG_PRINT(("------------Keyboard check------------"));
//			KeyboardEvent(IfForward);
			
#if RELEASE_VER == 1
			// ����0�Ի����
			DBG_PRINT(("------------COM0 check------------"));
			COM0Event(IfForward);
#endif

			// ����2�Ի����
			DBG_PRINT(("------------COM3 check------------"));
			COM2Event(IfForward);
			
			// Ǯ����
		//	DBG_PRINT(("------------Money Box check------------"));
		//	BoxEvent();
			
			// ���������
		//	DBG_PRINT(("------------Buzzer check------------"));
			BeepEvent(IfForward);
			
			// USB���
			DBG_PRINT(("------------USB check------------"));
			USBEvent(IfForward);

			// IC card���
			//DBG_PRINT(("------------IC Card check------------"));
			//ICCardEvent(IfForward);
			
			ForwardNLine(FORWARD_LINE_NUM);
			
			proBar.SetText("�ȴ��´��Լ�(ESC���˳�)");
			proBar.ReFresh();
			DBG_PRINT(("�ȴ���һ�λ����Լ�..."));
		}
		
#ifndef WIN32
//		usleep(100000);
		CommonSleep(100);
#endif

 		INT32 key;
// 		if(	key = GetKey() )
//    		{
//  			return SUCCESS;
// 		}

		if (key = ReadKeypad())
		{
			return SUCCESS;
		}
	}	
	return SUCCESS;
}


//���ػ�������
UINT8 DownloadFCRCode(void)
{
	UINT8 Count = 0;
	INT8 Ch;
	UINT16 year; 
	UINT8 mon;
	UINT8 day;
	UINT8 hh;
	UINT8 mm; 
	UINT8 ss;
	INT8 buff[DOWNLOAD_BYTE_LEN];
	UINT32 tmpTime, tmpDate;
	CMachine curMachine;
	CMachine *machine = &curMachine;
	
	LCDClearDisplay();			//����
	CaProgressBar proBar("��ȡ��������...");
	proBar.ReFresh();

	//��ʼ������
	INT32 res;
	UINT8 chPut, chGet, chGetNext;
	SerialPort serial, *pSerial;
	pSerial = &serial;
	SerialPortContruct(pSerial);
//	res = pSerial->InitPort(pSerial, UART1_DEV_NAME, UART1, 9600);
	res = pSerial->InitPort(pSerial, UART0_DEV_NAME, UART0, 9600);
	if (res == FAILURE) 
	{
		pSerial->ClosePort(pSerial);
		DBG_PRINT(("COM3: InitPort Failure!"));
		return FAILURE;
	}
	DBG_PRINT(("COM3: InitPort Success!"));

	//��ս������Ļ���
	UINT32 nNum, i;
	nNum = pSerial->GetReceiveCount(pSerial);
	if(nNum!=0)
	{
		for(i = 0; i < nNum; i++)
		{
			chGet = pSerial->GetChar(pSerial);
		}		
	}

	//��������
	UINT8 sendData[SEND_DATA_NUM];
	UINT8 received = 0;
	UINT16 crcsend = 0;
	memset(sendData,0,SEND_DATA_NUM);

	sendData[0] = 0x02;
#if PRODUCT_TYPE == 1
 	sendData[1] = 0x30;
 	sendData[2] = PRODUCT_TYPE_CODE;
#else
	sendData[1] = PRODUCT_TYPE_CODE_BYTE1;
	sendData[2] = PRODUCT_TYPE_CODE_BYTE2;
#endif
	for(i = 0; i<3; i++)
	{
		pSerial->PutChar(pSerial, sendData+i);
	}
	
	DBG_PRINT(("�������յ�������..."));

	for(year=0; year<100; year++)
	{
		if (pSerial->GetReceiveCount(pSerial) != 0)
		{
			Ch = pSerial->GetChar(pSerial);
			if (Ch != 0x02)
			{
				pSerial->ClosePort(pSerial);
				return FAILURE;
			}
			else
			{
				break;
			}
		}
		FOR_DELAY(0x2FFFFF);
	}
	
	if (year >= 100)
	{
		pSerial->ClosePort(pSerial);
		return FAILURE;
	}
	
	while(1)
	{
		buff[Count++] = pSerial->GetChar(pSerial);
		
		if (Count >= DOWNLOAD_BYTE_LEN)
		{
			break;
		}
	}
	
	machine->m_machineNo = (INT8 *)buff;
	machine->m_machineNo.erase(0,4);//���ص�16λ��������ֻ������12λ��
	DBG_PRINT(("machine->m_machineNo = %s!", machine->m_machineNo.c_str()));
	machine->m_hVer = (INT8 *)(buff+20);
	DBG_PRINT(("machine->m_hVer = %s!", machine->m_hVer.c_str()));


	sendData[3] = 0x04;//������
	pSerial->PutChar(pSerial, sendData+3);
	
	proBar.SetText(machine->m_machineNo.c_str());
	proBar.ReFresh();
	
	FOR_DELAY(0x6FFFFFF);//�����и�ʱ�ӣ�����mac���ܻ�ȡ���ɹ�
//	FOR_DELAY(0x2FFFFFF);
	while (pSerial->GetReceiveCount(pSerial) != 0)
	{
		Ch = pSerial->GetChar(pSerial);
	}//��ջ���
	
	proBar.SetText("��ȡ��������ʱ��...");
	proBar.ReFresh();
	
	//д��������ʱ��
	sendData[0] = 0x01;
#if PRODUCT_TYPE == 1
 	sendData[1] = 0x30;
 	sendData[2] = PRODUCT_TYPE_CODE;
#else
	sendData[1] = PRODUCT_TYPE_CODE_BYTE1;
	sendData[2] = PRODUCT_TYPE_CODE_BYTE2;
#endif
	for(i = 0; i<3; i++)
	{
		pSerial->PutChar(pSerial, sendData+i);
	}
	
	Ch = pSerial->GetChar(pSerial);
	if (Ch != 0x01)
	{
		pSerial->ClosePort(pSerial);
		return FAILURE;
	}
	
	pSerial->GetChar(pSerial);
	
	Count = 0;
#if PRODUCT_TYPE == 1
	while(1)
	{
		if (pSerial->GetReceiveCount(pSerial) != 0)
		{
			buff[Count] = pSerial->GetChar(pSerial);
			Count++;
			if (Count >= 7)
			{
				break;
			}
		}
	}
	
	memcpy((void *)&year, (void *)buff, 2);
	mon = buff[2];
	day = buff[3];
	hh = buff[4];
	mm = buff[5]; 
	ss = buff[6];
#else
	while(1)
	{
		if (pSerial->GetReceiveCount(pSerial) != 0)
		{
			pSerial->GetChar(pSerial);
			pSerial->GetChar(pSerial);
			buff[Count++] = pSerial->GetChar(pSerial);
			buff[Count++] = pSerial->GetChar(pSerial);
			if (Count >= 12)
			{
				break;
			}
		}
	}
	
	memcpy((void *)&year, (void *)buff, 2);
	mon = buff[2];
	day = buff[4];
	hh = buff[6];
	mm = buff[8]; 
	ss = buff[10];
#endif
	
	tmpTime = hh * 10000 + mm * 100 + ss;	
	tmpDate = year * 10000 + mon * 100 + day;	
	TDateTime tmpDateTime(tmpDate, tmpTime);
	TDateTime::SetCurrentDateTime(tmpDateTime);
	
	machine->m_pDate = tmpDateTime.FormatString(YYYYMMDD, "%u%02u%02u");
	DBG_PRINT(("machine->m_pDate = %s!", machine->m_pDate.c_str()));

	machine->m_sVer = MACHINE_S_VER;
	
	proBar.SetText("���������Ϣ��...");
	proBar.ReFresh();
	
	POWOFF_DISABLE(); //���ε����ж�
	machine->Delete();
	DBG_PRINT(("machine->Delete()!"));
	machine->AddNew();
	CGlobalArg::SysLog(EVENT_DOWNLOAD_MACHINE_NO , SUCCESS);//дϵͳ��־
	POWOFF_ENABLE();//�������ж�
	
	g_globalArg->m_machine->Requery();
	g_globalArg->m_machine->LoadOneRecord();//����װ��ȫ�ֱ���
	
//	proBar.SetText("�����������سɹ�,������");
//	proBar.ReFresh();

// 	delete machine;
	machine = NULL;

	pSerial->ClosePort(pSerial);
//	while(1);
	return SUCCESS;
}

//------����Mac
UINT8 DownloadMAC(INT8* pMacAddr, INT32 nMacLen)
{
	DBG_ASSERT_EXIT((pMacAddr != NULL)&&(nMacLen >= MAC_LEN), (" pMacAddr == NULL or nMacLen < MAC_LEN "));

	string strErr;
//	strErr = "�Ƿ�����MAC��ַ";
//	if(YesNoMsBox(strErr)==FAILURE)
//	{
//		return FAILURE;
//	}

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
		return FAILURE;
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
	DBG_PRINT(("��ս������Ļ���!"));

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

	ProgressBar.SetText("����MAC������...");
	ProgressBar.Show();
	
	for(i=0; i<100; i++)
	{
		if (pSerial->GetReceiveCount(pSerial) != 0)
		{
			DBG_PRINT(("Ch = 0x%x!", Ch));
			Ch = pSerial->GetChar(pSerial);
			if (Ch != 0x06)
			{
				pSerial->ClosePort(pSerial);
				CaMsgBox::ShowMsg("����MAC�������ʹ���");
				return FAILURE;
			}
			else
			{
				DBG_PRINT(("Ch == 0x06!"));
				break;
			}
		}
		FOR_DELAY(0x2FFFFF);
	}
	
	if (i >= 100)
	{
		pSerial->ClosePort(pSerial);
	//	CaMsgBox::ShowMsg("�������ݴ���");
		CaMsgBox::ShowMsg("δ���յ�MAC����");
		return FAILURE;
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
	DBG_PRINT(("PutChar 0x04!"));

	ProgressBar.SetText("MAC��ַ������...");
	ProgressBar.Show();

//	memset(MacAddr, 0, sizeof(MacAddr));
	sprintf(pMacAddr, "%02x:%02x:%02x:%02x:%02x:%02x",buff[16],buff[17],buff[18],buff[19],buff[20],buff[21]);

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
	sprintf(lineBuf, "ifconfig eth0 hw ether %s\n", pMacAddr);
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
// 	POWOFF_ENABLE();

	return SUCCESS;
}


UINT8 CheckKey(UINT8 &nKeyTime)
{
	INT32 nKey = 0x0;
	if((nKey = ReadKeypad())&&(RETURN_MAIN_MENU == nKey) )
   	{
		nKeyTime++;
		if (nKeyTime==2)
		{
			nKeyTime = 0;
			return SUCCESS;
		}		
   	}
	return FAILURE;
}


