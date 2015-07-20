#ifndef _LOGIN_WIN_H
#define _LOGIN_WIN_H

#include <string>
#include"CaWindow.h"
#include "CaInput.h"
#include "CaButton.h"
#include"pos_debug.h"
#include "g_def.h"
#include "CMainFrame.h"
#include "ReportFunc.h"
#include "COperator.h"
using namespace std;

class CLoginWin : public CaWindow
{
public:

	CaLabel *m_pLabel;
	CaInput *m_pInput1;
	CaInput *m_pInput2;
	CaButton *m_pBtn1;
	CaButton *m_pBtn2;
	
	int m_iBtnW;//Button �Ŀ��
	int m_iColW;

	int m_ifStudyIn;						//��ѧϰ��ɫ��¼����Ϊ1
	
private:
	COperator *m_LoginOper, m_cLoginOper;
	int m_loginErrorCount;					/**< ϵͳ��¼������� ����3������ */
	unsigned char m_DatabaseErr_Flag;		

public:
	int Create(int iX,int iY,int iW,int iH);
	int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	bool IsCurWin();	
	virtual int ReFresh();
	void OnInput1(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnInput2(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);
   
	CLoginWin();
	~CLoginWin();

private:
	static void S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	void ShowMsg(string strInfo);

    UINT8 CheckInputValid(string &strErr);
	void ClearLoginWin();
	
};


#endif
