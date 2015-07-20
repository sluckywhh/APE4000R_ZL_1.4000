#ifndef MULTI_BTN_NEW_COMMON_WIN_H
#define MULTI_BTN_NEW_COMMON_WIN_H

#include"CaWindow.h"
#include "g_def.h"
#include "CaLabel.h"
#include "CaButton.h"
#include "CaButtonList.h"

#include "LOGCTRL.h"
#include "pos_debug.h"

#define MAX_BUTTON_NUM	10
#define MAX_TITLE_NUM	20
/*!
@class ����7��button�Ĵ������  //���޸�
*/
class CMultiBtnNewCommonWin : public CaWindow
{

private:
	CaButton *m_pBtn[MAX_BUTTON_NUM];

	CaButtonList *m_pBtnList;
	unsigned int m_nNum;
	unsigned int m_iNumOfCol; //ǿ�����ò˵�����(1,����2) 

    char *m_pTitle[MAX_BUTTON_NUM];

public:
	CMultiBtnNewCommonWin(unsigned int colCount=0); //colCountǿ�����ò˵����� Ĭ�ϸ��ݲ˵���ȷ��
    ~CMultiBtnNewCommonWin();
	virtual int Create(int iX,int iY,int iW,int iH);
	virtual int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	
	void SetTitle(const char *title);
	void SetButton();

	virtual void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton3(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton4(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton5(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton6(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton7(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton8(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton9(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton10(int iEvent, unsigned char * pEventData, int iDataLen);

	virtual void OnButton(int iEvent, unsigned char * pEventData, int iDataLen);

	//�޸Ĵ��ڸ߶�m_iH���Ա�֤����ȵ���䴰�ڡ�
	//h ���ӵ���
	inline void Adjustm_iH(int h)
	{
		 m_pBtnList->m_iH += h ; 
	}

private:
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton4(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton5(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton6(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton7(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton8(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton9(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton10(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

	static void S_OnButton(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

	int ProcShortcut(int iEvent,unsigned char *pEventData, int iDataLen);

};

#endif


