/**
 @file  NetServerSetWin.h
 @brief �����ļ�������������
*/
#ifndef _NET_SERVER_SET_WIN_H
#define _NET_SERVER_SET_WIN_H

#include "IncludeMe.h"
#include "CaInput.h"
#include "CaButton.h"
#include "CaWindow.h"
#include "CMainFrame.h"

//#define PAYINV_SERV		1		/**<��Ʊ������ */
//#define DECLARE_SERV	2		/**<�걨������ */
#define APP_SERV		1			/**<Ӧ�÷����� */
#define TIME_SERV		2		/**<ʱ������� */

class CNetServerSetWin : public CaWindow
{
public:
	CaInput  *m_pInput1;
	CaInput  *m_pInput2;
	CaButton *m_pBtn1;
	CaButton *m_pBtn2;
	
	int m_iBtnW;	//Button �Ŀ��
	int m_iColW;
	
	UINT8 m_servType;		/**< ����������*/
	
private:
	string	m_serverIP;
	string	m_serverPort;
	int m_serverIP_flag;
	int m_serverPort_flag;

public:
	int Create(int iX,int iY,int iW,int iH);
	int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	bool IsCurWin();	
	virtual int ReFresh();
	void OnInput1(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnInput2(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);

	static void S_OnActive(CaWindow *obj);
	void DoActive(); 
	
	CNetServerSetWin();
	~CNetServerSetWin();

private:
	static void S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

    UINT8 CheckInputValid(string &strErr);
	void DispNetServerInfo();
	void ClearNetServerWin();
	UINT8 isIPValid(INT8 *ip);
	
};


#endif
