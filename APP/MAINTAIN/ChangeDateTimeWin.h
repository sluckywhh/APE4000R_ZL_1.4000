#ifndef CHANGE_DATE_TIME_H
#define CHANGE_DATE_TIME_H

#include"CaWindow.h"
#include"pos_debug.h"
#include "g_def.h"
#include "CaLabel.h"
#include "CMainFrame.h"
#include "CaInput.h"
#include "CaButton.h"
#include "TDateTime.h"
#include <string>


/**
 *@class CChangeDateTime 
 *@brief ������ʱ��ĺ��Ž���
 */
class CChangeDateTime : public CaWindow{
public:

	CaInput  *m_pInput1;
	CaInput  *m_pInput2;	  
	CaButton *m_pBtn1;
	CaButton *m_pBtn2;
	
	int m_iBtnW;//Button �Ŀ��
	int m_iColW;
	
public:
	int Create(int iX,int iY,int iW,int iH);
	int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	bool IsCurWin();	
	virtual int ReFresh();
	void ConfirmDateTime(int iEvent, unsigned char * pEventData, int iDataLen);
	void DefaultDateTime(int iEvent, unsigned char * pEventData, int iDataLen);
	void SetSystemDate(int iEvent, unsigned char * pEventData, int iDataLen);
	void SetSystemTime(int iEvent, unsigned char * pEventData, int iDataLen);

	CChangeDateTime();
	~CChangeDateTime();

private:
	static void S_ConfirmDateTime(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_DefaultDateTime(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_SetSystemDate(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_SetSystemTime(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	/*!
	@brief У���������ں�ʱ�����Ч��
	@param[in] &datetime ��������ں��ս� strErr ������Ϣ
	@return  1�� �ɹ��� ������ʧ��
	*/
	UINT8 CheckDateTimeValid(TDateTime &datetime, string &strErr);
	/*!
	@brief ��ʼ������
	@return  1�� �ɹ��� ������ʧ��
	*/
	UINT8 DoInitProc();

	/**
	 * S_OnActive
	 * @param CaWindow *obj
	 * @return static void 
	 */
	static void S_OnActive(CaWindow *obj);
	void DoActive(); 

};


#endif
