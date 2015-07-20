/*! \file    IssueSumDateWin.h
   \brief    awe4000r�����ӡ�Ŀ�Ʊͳ��ʱ���������
   \author   Yu Yan
   \version  1.0
   \date     2008-9-5 
 */


#ifndef ISSUE_SUM_DATE_WIN_H
#define ISSUE_SUM_DATE_WIN_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef WIN32
#include <conio.h>
#endif

#include "IncludeMe.h"
#include "CaWindow.h"
//#include "LOGCTRL.h"
//#include "pos_debug.h"
#include "g_def.h"
#include "CaLabel.h"
#include "CMainFrame.h"
#include "CaInput.h"
#include "CaButton.h"
#include "CaMsgBox.h"
#include "TDateTime.h"

#include "SysMacDef.h"


/**
 *@class CIssueSumDateWin 
 *@brief �����ӡ��ʱ��λ��� ʱ���������
 */
class CIssueSumDateWin : public CaWindow
{
public:
	
	CaInput *m_pInput1;			/**< ָ����������ָ��*/
	CaInput *m_pInput2;			/**< ָ����������ָ��*/
	CaInput *m_pInput3;			/**< ָ����������ָ��*/
	CaInput *m_pInput4;			/**< ָ����������ָ��*/
	CaButton *m_pBtn1, *m_pBtn2;/**< ָ��ť��ָ��*/
	        	
	int m_iBtnW;				/**< ����ʱ���ؼ��Ŀ�� */  
	int m_iColW;				/**< ����ʱ���ڶ��еĺ����� */  

	UINT32 m_StartDate;			/**< ��ѯ����ʼ����*/
    UINT32 m_EndDate;			/**< ��ѯ�Ľ�ֹ����*/
    UINT32 m_StartTime;			/**< ��ѯ����ʼʱ��*/
    UINT32 m_EndTime;			/**< ��ѯ�Ľ�ֹʱ��*/
	string m_strTimeSeg;		/**< ʱ����޶������ַ���*/

private:

	int m_iPrnType;

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
	
	/*!
	@brief ��������Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��������Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��������Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnInput3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��������Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnInput4(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

	
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
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��������Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnInput1(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��������Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnInput2(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��������Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnInput3(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��������Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnInput4(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ���캯��	
	*/
	CIssueSumDateWin();

	/*!
	@brief ��������	
	*/
	virtual ~CIssueSumDateWin();
      
	/*!
	@brief ������ʾ���ݵľ�̬����	 
	*/
	static void S_OnActive(CaWindow *obj);
    
	/*!
	@brief ������ʾ���ݵĺ���	 
	*/
	void DoActive(); 

	
	/*!
	@brief �������ֵ
	@return  1: SUCCESS; ��1: �������
	*/
	UINT8 CheckInput(void);

	/*!
	@brief ��ӡ��Ʊͳ�Ʊ������
	@return  1: SUCCESS; 0��FAILRE
	*/
	UINT8 PrnIssueSumProc();

	/*!
	@brief ��Ʊͳ�ƺ��ĳ���
	@param[in] nIfSameDay ʱ����Ƿ���һ��֮�ڣ� 1���ǣ� 0����
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 IssueSumHandle(UINT8 nIfSameDay);
  
};

#endif