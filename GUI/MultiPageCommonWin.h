#ifndef MULTI_PAGE_COMMON_WIN_H
#define MULTI_PAGE_COMMON_WIN_H
#include"CaWindow.h"
#include"pos_debug.h"
#include "g_def.h"
#include "CaLabel.h"
#include "CaButton.h"

#define		PAGE_LINE_NUM	5

/*!
@class ��ҳ��ÿҳȫ��label ��ȫ��button��
*/
class CMultiPageCommonWin : public CaWindow
{
private:
	CaButton *m_pBtn1;//��ǰҳ��1����ť
	CaButton *m_pBtn2;//��ǰҳ��2����ť
	CaButton *m_pBtn3;//��ǰҳ��3����ť
	CaButton *m_pBtn4;//��ǰҳ��4����ť
	CaButton *m_pBtn5;//��ǰҳ��5����ť

	CaLabel *m_pLabel1;//��ǰҳ��1��label
	CaLabel *m_pLabel2;//��ǰҳ��2��label
	CaLabel *m_pLabel3;//��ǰҳ��3��label
	CaLabel *m_pLabel4;//��ǰҳ��4��label
	CaLabel *m_pLabel5;//��ǰҳ��5��label

protected:
	CaLabel *m_pPageLabel;//��ʾҳ���label
	CaLabel *m_pPageLabel_2;//���õ���ʾҳ���label

	int m_iCurWinLastComIndex;//��ǰ�������һ�����ܵ������е�index
	int m_iComType;//ȫ��label ���� ȫ��button
	int m_iPressedBtnIndex;//����enter��ʱ���µ��ǵڼ�����ť
	int m_iTotalLine;//������
	int m_iCurPageNum;//��ǰҳ��ҳ��
	int m_iTotalPage;//��ҳ��
public:
	char **m_pStrList;//���labels ����buttons ��titles
public:
	enum{MULTI_LABELS_MULTI_PAGE,MULTI_BUTTONS_MULTI_PAGE};
	
	CMultiPageCommonWin(int type);

	virtual int Create(int iX,int iY,int iW,int iH);
	virtual int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	virtual ~CMultiPageCommonWin();
	virtual int ReFresh(void);
	virtual bool IsCurWin(void);
	virtual void EndProcess();//������Ժ�Ĵ���
	virtual void OnBtnPressed();//�����û�ѡ��������

	void ClearListBuff(void);
	void SetTitles(char ** titles, int totalLine);
	int GetSelectedIndex();
	//�����ý������
	int GetFocusIndex();
	inline int GetTotalPageNum(){return m_iTotalPage;}
	inline int GetCurPageNum(){return m_iCurPageNum;}
	inline int GetTotalLineNum(){return m_iTotalLine;}
	void GetNextPage();
	void GetPrePage();

	//�����ú�m_pStrList�� �������õ�һҳ��ʾ
	/*	@brief ����Ҫ��ʾ��ҳ��Ĭ���ǵ�һҳ�����Ը��ݲ�����ʾ����ҳ
		@totalLine �ܵ�����
		@curPageNum Ҫ��ʾ�ڼ�ҳ
		@startIndex Ҫ��ʾ��������m_pStrList�е���ʼ����
	*/
	void InitFirstPage(int totalLine, int curPageNum = 1, int startIndex = 0);


	void SetPageNumVisible(bool visible);
	void SetPageNumVisible_2(bool visible);

private:
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton4(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton5(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

	/*!@brief ��������ÿҳ��ʾ����,��ʾǰendNum�� 	*/
	void ResetVisiable(int endNum);

protected:	

	virtual void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton3(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton4(int iEvent, unsigned char * pEventData, int iDataLen);
	virtual void OnButton5(int iEvent, unsigned char * pEventData, int iDataLen);

};

#endif


