/*! \file    ProductSaleWin.h
   \brief    awe4000r���۳�������Ʒ���۴���
   \author   Yu Yan
   \version  1.0
   \date     2007-11-28
 */


#ifndef PRODUCT_SALE_WIN_H
#define PRODUCT_SALE_WIN_H

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
#include "TDateTime.h"
#include "SaleData.h"
#include "CaObject.h"
#include "CaMsgBox.h"


//#define TITLE_MAX_LEN = 32						/**< ��ǩ��ʾ�����ݳ��� */

class CProductSaleWin : public CaWindow
{
public:
//	char title_array[5][OBJ_TITLE_MAX_LEN + 1];	/**< ��ǩ��ʾ������ ����ʱδ�ã� */
	CaLabel *label[7];							/**< ָ���ǩ��ָ�� */
	string m_strSuffix;							/**< ��ǩ��ʾ���ݵĲ��䲿�� */
	
	CaInput *m_pInput1;							/**< ָ����������ָ�� */
	CaInput *m_pInput2;							/**< ָ����������ָ�� */   

	bool m_IfCancel;							/**< �Ƿ񰴡���Ʒȡ������ */ 
	
	int m_iBtnW;								/**< ����ʱ���ؼ��Ŀ�� */  
    int m_iColW;								/**< ����ʱ���ڶ��еĺ����� */ 
     
//  CProductSaleMainMenu *pPSMWin;


public:

	/*!
	@brief ���캯��	
	*/
	CProductSaleWin();
	
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

//	bool IsCurWin();

	/*!
	@brief ˢ�´�����ʾ	
	@return 1: SUCCESS
	*/
	virtual int ReFresh();
    
	/*!
	@brief �ı�Label��������titleֵ	
	@return  1: SUCCESS; 0: FAILURE
	*/
	int ChangeTitle();

	/*!
	@brief ������Ϣ��ʾ��	
	@param[in] ret   ����� 
	@return  FAILURE
	*/
    int ErrMsgBox(UINT8 ret);

	/*!
	@brief ��Label��ʾ�����ӡ����	
	@param[in] dCash   ʵ���ֽ��
	@return  1: SUCCESS; 0: FAILURE
	*/
    UINT8 CashShow(double cash);

    /*!
	@brief ��Label��ʾ��Ʒ��������	 
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 DeptSaleShow();

    /*!
	@brief ��Label��ʾ������	 
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 ClientShow();

	/*!
	@brief ��Label��ʾ������˰��	 
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 ClientCodeShow();

	/*!
	@brief ��ʾ��Ʒȡ��	 
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 CancelGoodsShow();

	/*!
	@brief ����ȡ���Ĵ�����	 
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 TotalCancelProc();

	/*!
	@brief �������۹���
	@param[in] deptNo �����
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 DeptSaleProc(UINT32 deptNo);

	/*!
	@brief ��Label��ʾ�������Ϣ����ӡ
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 InvSumShowPrn(void);

	/*!
	@brief �������������
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 ClientInputProc(void);

	/*!
	@brief ������˰���������
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 ClientCodeInputProc(void);

	/*!
	@brief ��ע�������
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 RemarksInputProc(void);

	/*!
	@brief ���ù���
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 GoodesReductProc(void);

	/*!
	@brief �����������
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 PriceInputProc(void);

	/*!
	@brief �ܼ��������
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 SumInputProc(void);
 
	/*!
	@brief ��ʱ�������
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 PlusProc(void);

	/*!
	@brief ������۹���
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 QuickSaleProc(void);
	
};

#endif

