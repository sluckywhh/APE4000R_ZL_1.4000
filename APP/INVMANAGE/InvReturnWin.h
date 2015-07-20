/*! \file    InvReturnWin.h
   \brief    awe4000r��Ʊ�����ķ�Ʊ�˻ؽ���
   \author   Yu Yan 
   \version  1.0
   \date     2008-2-14 
 */

#ifndef INV_RETURN_WIN_H
#define INV_RETURN_WIN_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef WIN32
#include <conio.h>
#endif

#include "IncludeMe.h"
#include "CaWindow.h"
#include "LOGCTRL.h"
#include "pos_debug.h"
#include "g_def.h"
#include "CaLabel.h"
#include "CMainFrame.h"
#include "CaInput.h"
#include "CaButton.h"
#include "InvRetQueryWin.h"




/**
 *@class CInvReturnWin 
 *@brief ��Ʊ�����ķ�Ʊ�˻ؽ���
 */
class CInvReturnWin : public CaWindow
{
public:
	char title_array[5][OBJ_TITLE_MAX_LEN + 1];	/**< ��ǩ�ı���*/

	CaLabel *label[5];							/**< ָ���ǩ��ָ�� */
	
	CaInput *m_pInput1, *m_pInput2;				/**< ָ�����ָ�� */
	CaButton *m_pBtn1, *m_pBtn2;				/**< ָ��ť��ָ�� */
	        	
	int m_iBtnW;								/**< ����ʱ���ؼ��Ŀ�� */  
	int m_iColW;								/**< ����ʱ���ڶ��еĺ����� */  

	CInvHead *m_pRtInvHead;                       /**< ���˷�Ʊ��Ϣ*/ 
	CInvRetQueryWin *m_pQueryWin;				/**< ��Ʊ��ѯ�����ָ��*/
private:

	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	

public:

	/*!
	@brief ��������	
	@param iX ���ϽǺ�����
	@param iY ���Ͻ�������
	@param iW ���
	@param iH �߶�
	@return 1 ���ɹ���������ʧ��
	*/
	int Create(int iX,int iY,int iW,int iH);

	/*!
	@brief �����¼�	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	@return   1  �Ѵ��� 0 �޷�����
	*/
	int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);

	/*!
	@brief ˢ�´�����ʾ	
	@return 1: SUCCESS
	*/
	virtual int ReFresh();

	/*!
	@brief ��ť1��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť2��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);
	
	
	/*!
	@brief ���캯��	
	*/
	CInvReturnWin();

	/*!
	@brief ��������	
	*/
	virtual ~CInvReturnWin();
    
	/*!
	@brief ������Ϣ��ʾ��	
	@param[in] ret   ����� 
	@return  FAILURE
	*/
    UINT8 ErrMsgBox(UINT8 ret);
    
	  
	/*!
	@brief ������ʾ���ݵľ�̬����	 
	*/
	static void S_OnActive(CaWindow *obj);
    
	/*!
	@brief ������ʾ���ݵĺ���	 
	*/
	void DoActive(); 

	
	/*!
	@brief �ı�Label��������titleֵ	
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 ChangeTitle();

	/*!
	@brief ��ʼ��Ļ��ʾ
	*/
	void NormalShow();

	/*!
	@brief ��Ʊ�˻�ʱ����Ļ��ʾ
	@param[in] invHead    ���˷�Ʊ
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 ReturnShow(CInvHead *pInvHead);
	
  
};

#endif
