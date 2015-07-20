/* Generated by Together */

#ifndef CAWINDOW_H
#define CAWINDOW_H
#include "CaGroup.h"
class CPosFrame;

class CaWindow : public CaGroup {
private:
	int m_iWinID;
	CaWindow * m_pPreWin;//父窗体
	static bool m_bShowMsgBox;
	
public: //property
	bool m_bResetFlag;//是否初始窗体，清空该窗体中的动态内容
	CPosFrame *m_pFrame;
	void (*OnActive) (CaWindow *obj);
	int  WinID(){return m_iWinID;};
	void WinID(int id){m_iWinID=id;};

	static bool IsShowMsgBox(void);
	static void SetShowMsgBox(bool show);
public:
	CaWindow(LABEL_POS lbPos,int lbW);
	CaWindow();
	virtual ~CaWindow();
	void PreWin(CaWindow *p){m_pPreWin=p;};
	CaWindow *PreWin(){return m_pPreWin;};

	void ChangeWin( CaWindow * pNewWin);       //改变窗口 
	void ChangeWin(int id);
	virtual bool IsCurWin();
	
	virtual int  Create(int iX,int iY,int iW,int iH);
    virtual int  ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	virtual int  ReFresh(bool force = false);
//	virtual int  ReFresh(int id);
	virtual int  SetFocus(void);	
//	virtual int  SetTitle(unsigned char * pData,int iLen);
    virtual int OnUpKey(void);
    virtual int OnDownKey(void);
    virtual int OnLeftKey(void);
    virtual int OnRightKey(void);
    virtual int OnTabKey(void);
public:
    virtual int OnPgDnKey(void);
    virtual int OnPgUpKey(void);
	virtual void ResetWin(void);//初始窗体，清空该窗体中的动态内容(如输入域)
};
#endif //CAWINDOW_H


