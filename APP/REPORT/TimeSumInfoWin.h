/*! \file    TimeSumInfoWin.h
   \brief    awe4000r�����ӡ��ʱ��λ��ܽ���
   \author   Yu Yan
   \version  1.0
   \date     2008-02-14
 */

#ifndef TIME_SUM_INFO_WIN_H
#define TIME_SUM_INFO_WIN_H

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

#include "TimeSumDateWin.h"
#include "SysMacDef.h"
#include "printer.h"


/**
 *@class CTimeSumInfoWin 
 *@brief �����ӡ��ʱ��λ��ܽ���
 */
class CTimeSumInfoWin : public CaWindow
{
public:
	char title_array[5][OBJ_TITLE_MAX_LEN + 1];	/**< ��ǩ�ı���*/

	CaLabel *label[3];							/**< ָ���ǩ��ָ�� */
	
	CaButton *m_pBtn1, *m_pBtn2;				/**< ָ��ť��ָ�� */
	CTimeSumDateWin* m_pDateWin;				/**< ָ��ʱ��λ��ܵ�ʱ����������ָ�� */
	
	int m_iBtnW;								/**< ����ʱ���ؼ��Ŀ�� */  
	int m_iColW;								/**< ����ʱ���ڶ��еĺ����� */  

//	UINT8 m_create;								/**< ����״̬*/

	UINT32 m_StartDate;							/**< ��ѯ����ʼ����*/
	UINT32 m_EndDate;							/**< ��ѯ�Ľ�ֹ����*/
	UINT32 m_StartTime;							/**< ��ѯ����ʼʱ��*/
	UINT32 m_EndTime;							/**< ��ѯ�Ľ�ֹʱ��*/
	struct TDateSegSumPrnData m_segSumPrnData;  /**< ʱ��λ�������*/
	struct TDateSegSumPrnData *m_pSegSumPrnData;/**< ʱ��λ�������ָ��*/

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
	@brief ��������Ӧ�ľ�̬����
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
	@brief ���캯��	
	*/
	CTimeSumInfoWin();

	/*!
	@brief ��������	
	*/
	virtual ~CTimeSumInfoWin();
      
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
	@brief ��ȡʱ��λ�����Ϣ�����޸���Ļ��ʾ
	@param[in] pSegSumPrnData ʱ��λ��ܼ�¼��ָ��
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 QueryShow(struct TDateSegSumPrnData *pSegSumPrnData);

	/*!
	@brief ��ӡ��ǰ��ʾ��ʱ��λ�����Ϣ
	@param[in] pSegSumPrnData ʱ��λ��ܼ�¼��ָ��
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 PrnTimeSumInfo(struct TDateSegSumPrnData *pSegSumPrnData);
};

#endif

