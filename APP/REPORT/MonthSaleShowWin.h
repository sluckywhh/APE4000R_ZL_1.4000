/*! \file    MonthSaleShowWin.h
   \brief    awe4000r������ͳ����ʾ����
   \author   Yu Yan
   \version  1.0
   \date     2015-06-15
 */

#ifndef MONTH_SALE_SHOW_WIN_H
#define MONTH_SALE_SHOW_WIN_H

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
#include "CaButton.h"

#include "SysMacDef.h"
#include "CGlobalArg.h"
#include "CTjxxhz.h"


/**
 *@class MonthSaleShowWin 
 *@brief ������ͳ����ʾ����
 */
class CMonthSaleShowWIn : public CaWindow
{
public:
	char title_array[7][OBJ_TITLE_MAX_LEN + 1];	/**< ��ǩ�ı���*/

	CaLabel *label[7];							/**< ָ���ǩ��ָ�� */
	
	CaButton *m_pBtn1, *m_pBtn2;				/**< ָ��ť��ָ�� */
	        	
	int m_iBtnW;								/**< ����ʱ���ؼ��Ŀ�� */  
	int m_iColW;								/**< ����ʱ���ڶ��еĺ����� */  

	UINT32 m_pageIndex;							/**< ��ǰҳ��*/
	UINT32 m_pageNum;							/**< ��ҳ����*/
	CTjxxhz *m_ptrTjxxhz;						/**< ��Ʊ������Ϣ*/
	UINT32 m_recordIndex;						/**< ��¼�ڱ��е����*/

	UINT32 m_iStartDate;					/**< ��ѯ����ʼ����*/
    UINT32 m_iEndDate;					/**< ��ѯ�Ľ�ֹ����*/


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
	CMonthSaleShowWIn();

	/*!
	@brief ��������	
	*/
	virtual ~CMonthSaleShowWIn();
   
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
	@brief ��ȡ������ͳ����Ϣ�����޸���Ļ��ʾ
	@param[in] pTjxxhz ͳ����Ϣ��ѯ���ָ��
	@param[in] nPageIndex  ������Ļ��ʾ��ҳ���
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 QueryShow(CTjxxhz *pTjxxhz, UINT32 nPageIndex);

		/*!
	@brief ��ӡ������ͳ�ƹ���
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 PrnMonthSaleSumProc();

	/*!
	@brief ������ͳ�ƺ��Ĺ���
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 MonthSaleSumHandle();
  

};

#endif
