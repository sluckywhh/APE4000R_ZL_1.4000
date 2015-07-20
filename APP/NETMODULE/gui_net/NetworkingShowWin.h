/**
 @file  NetworkingShowWin.h
 @brief �����ļ���IP��Ϣ��ʾ
*/
#ifndef NETWORKING_SHOW_WIN_H
#define NETWORKING_SHOW_WIN_H

#include "IncludeMe.h"
#include "CaWindow.h"
#include "CaButton.h"
#include "CaLabel.h"
#include "CaMsgBox.h"



/**
 *@class CNetworkingShowWin 
 *@brief ����IP��ʾ����
 */
class CNetworkingShowWin : public CaWindow
{
public:
	char title_array[5][OBJ_TITLE_MAX_LEN + 1];	/**< ��ǩ�ı���*/

	CaLabel *label[4];					
	CaButton *m_pBtn1;				
	
	int m_iBtnW;									
	int m_iColW;								

	UINT8 m_create;								

	IPinfo m_ipInfo;
		

private:
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
public:
	int Create(int iX,int iY,int iW,int iH);
	int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	virtual int ReFresh();
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnActive(CaWindow *obj);
	void DoActive(); 

	CNetworkingShowWin();
	virtual ~CNetworkingShowWin();
      

	
	/*!
	@brief �ı�Label��������titleֵ	
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 ChangeTitle();

	/*!
	@brief ��ȡ����IP��Ϣ
	@param[in] pInvSum ����ܼ�¼��ָ��
	@param[in] codeNo  ��Ʊ���������
	@param[in] invNo   ��Ʊ����
	@return  1: SUCCESS; 0: FAILURE
	*/
	void GetNetworkingInfo();

	void ClearNetworkingInfo();
	void DispNetworkingInfo();

};
	

#endif
