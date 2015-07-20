/*! \file    InvStubPrnWin.h
   \brief    awe4000r��Ʊ�����ķ�Ʊ�����ӡ����
   \author   Yu Yan 
   \version  1.0
   \date     2008-2-14 
 */


#ifndef INV_STUB_PRN_WIN_H
#define INV_STUB_PRN_WIN_H

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
#include "CaMsgBox.h"
#include "TDateTime.h"
#include "InvManageFunc.h"
#include "InvStubWin.h" 

#include "SysMacDef.h"
#include "CGlobalArg.h"
#include "SaleData.h"


/**
 *@class CInvStubPrnWin 
 *@brief ��Ʊ�����ķ�Ʊ�����ӡ����
 */
class CInvStubPrnWin : public CaWindow
{
public:
	char title_array[5][OBJ_TITLE_MAX_LEN + 1];	/**< ��ǩ�ı���*/


	CaLabel *label[5];							/**< ָ���ǩ��ָ�� */
	
	CaButton *m_pBtn1, *m_pBtn2, *m_pBtn3;		/**< ָ��ť��ָ�� */
	CInvStubWin* m_pPSWin;						/**< ��Ʊ�����ѯ�����ָ�� */
	//CInvInfoDownloadWin *m_pPIWin;
	
	int m_iBtnW;								/**< ����ʱ���ؼ��Ŀ�� */  
	int m_iColW;								/**< ����ʱ���ڶ��еĺ����� */ 

	UINT32 m_pageIndex;							/**< ��ǰҳ��*/
	UINT32 m_pageNum;							/**< ��ҳ����*/
	CInvHead *m_pInvHead;						/**< ��Ʊ������Ϣָ��*/
	CInvHead m_invHead;							/**< ��Ʊ������Ϣ*/
	UINT32 m_recordIndex;						/**< ��¼�ڱ��е����*/


	string m_code;								/**< ���˷�Ʊ����*/
	UINT32 m_invStartNo;						/**< ���˷�Ʊ����*/
	UINT32 m_invEndNo;							/**< ���˷�Ʊ����*/

	UINT8 m_pageflag;

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
	static void S_OnButton3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

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
	void OnButton3(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ���캯��	
	*/
	CInvStubPrnWin();

	/*!
	@brief ��������	
	*/
	virtual ~CInvStubPrnWin();
    
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
	@brief ��ȡ��Ʊ�����Ϣ�����޸���Ļ��ʾ
	@param[in] pInvHead ��Ʊ��¼��ָ��
	@param[in] nIndex  ��Ʊ��¼��������
	@param[in] nPageIndex  ������Ļ��ʾ��ҳ���
	@param[in] nPageNum  ������Ļ��ʾ��ҳ������
	@param[in] nOrder  ��ѯ���˳��  0������1������
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 QueryShow(CInvHead *pInvHead, UINT32 nIndex, UINT32 nPageIndex, UINT32 nPageNum, UINT8 nOrder);

	/*!
	@brief ������ӡ��ʼ��Ʊ�ŵ���ֹ��Ʊ�ŵĵ��Ӵ��
	*/
	void ContinuousIssue();

	/*!
	@brief ������ӡ��ʼ��Ʊ�ŵ���ֹ��Ʊ�ŵĵ��Ӵ��
	*/
	void ContinuousIssueOne();

	/*!
	@brief ��鰴�����ж��Ƿ��˳��Զ���Ʊ����	
	@param[out] nKeyTime      ������ȷ�ϼ��Ĵ��� 
	@return  1 ��(SUCCESS)�� 0 ��(FAILURE)
	*/
    UINT8 CheckKey(UINT8 &nKeyTime);

	void PrintInv(UINT8 printType);
};

#endif
