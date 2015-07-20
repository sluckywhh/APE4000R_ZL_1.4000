/**
 @file  ZhqBtlSetWin.h
 @brief �����ļ���ת���������д��ڲ���������
*/
#ifndef ZHQ_BTL_SET_WIN_H
#define ZHQ_BTL_SET_WIN_H

#include "IncludeMe.h"
#include "CaInput.h"
#include "CaButton.h"
#include "CaWindow.h"
#include "CMainFrame.h"

class CZhqBtlSetWin : public CaWindow
{
public:
	CaLabel *m_pLbl1, *m_pLbl2, *m_pLbl3;
	CaInput *m_pInput1;							
	CaButton *m_pBtn1, *m_pBtn2;				
	
	int m_iBtnW;								
	int m_iColW;
	UINT32 m_zhqbaudrate;//ת���������ʶ�Ӧ��ID��
	UINT32 m_com2baudrate;//��������ʶ�Ӧ��ID��
	
public:
	
	int Create(int iX,int iY,int iW,int iH);
	int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	virtual int ReFresh();
	
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnInput1(int iEvent, unsigned char * pEventData, int iDataLen);
	
	static void S_OnActive(CaWindow *obj);
	void DoActive();
	
	CZhqBtlSetWin();
	virtual ~CZhqBtlSetWin();
	
	
private:
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	UINT8 CheckInputValid(string &strErr);
	void DispCurInfo();
	INT8 ChangeBaudRate(string &RetErr);	
};


#endif
