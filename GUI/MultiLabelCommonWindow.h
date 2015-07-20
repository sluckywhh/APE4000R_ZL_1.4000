#ifndef MULTI_LABEL_COMMON_WIN_H
#define MULTI_LABEL_COMMON_WIN_H
#include"CaWindow.h"
#include"LOGCTRL.h"
#include"pos_debug.h"
#include "g_def.h"
#include "CaLabel.h"
#include "CaButton.h"
#include "CaButtonList.h"

/*!
@class ����10��button�Ĵ������ 
һ��ButtonList�������8��Button��������Button�����á�P������ʹ���������������ּ��ƶ���
*/
class CMultiLabelCommonWin : public CaWindow
{
private:
	CaButtonList *m_pBtnList;
    CaButton *m_pBtn[8];

	CaButton *m_pBtn1;
	CaButton *m_pBtn2;


public:
	CMultiLabelCommonWin(int numOfBtn);

	virtual int Create(int iX,int iY,int iW,int iH);
	virtual int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	
	void SetTitle(int num, const char *title);
	
	virtual void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);

	void SetBtnFocus();

	//�޸Ĵ��ڸ߶�m_iH���Ա�֤����ȵ���䴰�ڡ�
	//h ���ӵ���
	inline void Adjustm_iH(int h)
	{
		 m_pBtnList->m_iH += h ; 
	}

private:
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

protected:
	int m_iNumOfBtn;
};

#endif


