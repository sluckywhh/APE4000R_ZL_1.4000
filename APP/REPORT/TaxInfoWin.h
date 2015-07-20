
/*! \file    TaxInfoWin.h
   \brief    awe4000r�����ӡ��˰����Ϣ����
   \author   zcy
   \version  1.0
   \date     2015-6-6
 */

#ifndef		TAX_INFO_WIN_H
#define		TAX_INFO_WIN_H

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
#include "CaMsgBox.h"
#include "TDateTime.h"

#include "SysMacDef.h"
#include "CGlobalArg.h"
#include "CTax.h"

#define SHOWNUM_TAX 3

/**
 *@class CTaxInfoWin 
 *@brief �����ӡ��˰����Ϣ����
 */
class CTaxInfoWin : public CaWindow
{
public:
	char title_array[SHOWNUM_TAX+1][OBJ_TITLE_MAX_LEN + 1];	/**< ��ǩ�ı���*/

	CaLabel *label[SHOWNUM_TAX+1];							/**< ָ���ǩ��ָ�� */
	
	CaButton *m_pBtn1, *m_pBtn2;				/**< ָ��ť��ָ�� */
	        	
	int m_iBtnW;								/**< ����ʱ���ؼ��Ŀ�� */  
	int m_iColW;								/**< ����ʱ���ڶ��еĺ����� */  
	
	UINT32 m_pageIndex;							/**< ��ǰҳ��*/
	UINT32 m_pageNum;							/**< ��ҳ����*/
	CTax *m_pTax;								/**< ��Ȩ˰����Ϣ*/
	UINT32 m_recordIndex;						/**< ��¼�ڱ��е����*/

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
	CTaxInfoWin();

	/*!
	@brief ��������	
	*/
	virtual ~CTaxInfoWin(); 
	  
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
	@brief ��ȡ��Ȩ˰����Ϣ�����޸���Ļ��ʾ
	@param[in] pTax ˰�ʼ�¼��ָ��
	@param[in] nIndex  ˰�ʼ�¼��������
	@param[in] nPageIndex  ������Ļ��ʾ��ҳ���
	@param[in] nPageNum  ������Ļ��ʾ��ҳ������
	@param[in] nOrder  ��ѯ���˳��  0������1������
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 QueryShow(CTax *pTax, UINT32 nIndex, UINT32 nPageIndex, UINT32 nPageNum);

		/*!
	@brief ������Ϣ��ʾ��	
	@param[in&out] nNum   ��ʾҳ�� 
	@return  FAILURE
	*/

	UINT8 GetTaxNum(UINT32 &nNum);

	/*!
	@brief ��ӡ˰����Ϣ	 
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 PrintTaxInfo();
};

#endif
