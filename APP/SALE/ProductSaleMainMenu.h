/*! \file    ProductSaleMainMenu.cpp
   \brief    awe4000r���۳�������Ʒ���۵�������
   \author   Yu Yan
   \version  1.0
   \date     2007-11-28
 */


#ifndef PRODUCT_SALE_MAIN_MENU_H
#define PRODUCT_SALE_MAIN_MENU_H


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
#include "SaleData.h"
#include "TDateTime.h"
#include "ProductSaleWin.h"



//#define STUDY_INV_NUM 1000		/**< �ٷ�Ʊ��ķ�Ʊ�� */	

extern char title_arr[7][33];	/**< CProductSaleWin��Label�ı��� */	 

/*!
@class CProductSaleMainMenu
@brief ��Ʒ�������˵�
*/
class CProductSaleMainMenu : public CaWindow
{
public:
	char title_array[5][OBJ_TITLE_MAX_LEN + 1];		/**< ��ǩ��ʾ������ */
	string m_strSuffix;								/**< ��ǩ��ʾ���ݵĲ��䲿�� */

	CaLabel *label[7];								/**< ָ���ǩ��ָ�� */
	
//	CaInput *m_pInput1;								/**< ָ����������ָ�� */
	CaInput *m_pInput2;								/**< ָ����������ָ�� */  
       	
	int m_iBtnW;									/**< ����ʱ���ؼ��Ŀ�� */  
    int m_iColW;									/**< ����ʱ���ڶ��еĺ����� */  
  
	CProductSaleWin *pPSWin;						/**< ��Ʒ���۴��ڵ�ָ�� */
	
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

//	/*!
//	@brief �Ƿ�ǰ����	
//	@return true
//	*/
//	bool IsCurWin();

	/*!
	@brief ˢ�´�����ʾ	
	@return 1: SUCCESS
	*/
    virtual int ReFresh();

	/*!
	@brief ���캯��	
	*/
	CProductSaleMainMenu();

	/*!
	@brief ��������
	*/
	virtual ~CProductSaleMainMenu();
    
	/*!
	@brief ������Ϣ��ʾ��	
	@param[in] ret   ����� 
	@return  FAILURE
	*/
    UINT8 ErrMsgBox(UINT8 ret);
    
	/*!
	@brief ��Label��ʾ��Ʒ��������	 
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 DeptSaleShow();
    
	/*!
	@brief ������ʾ���ݾ�̬����	 
	*/
	static void S_OnActive(CaWindow *obj);
    
	/*!
	@brief ������ʾ���ݺ���	 
	*/
	void DoActive(); 

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
	@brief ������ʾ	 
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 NormalShow();

	/*!
	@brief �ı�Label��������titleֵ	
	@return  1: SUCCESS; 0: FAILURE
	*/
	int ChangeTitle();
	
    /*!
	@brief ��ֽ	
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 ForwardKeyProc();

	/*!
	@brief �������۹���
	@param[in] deptNo �����
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 DeptSaleProc(UINT32 deptNo);

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

	/*!
	@brief ��������������ж�Ӧȫ�ֱ�����ֵ
	@return  1: SUCCESS; 0: FAILURE
	@attention ��Ʊ����ͷ�Ʊ�Ż�����װ��Ʊ��Ϣʱ���£��������ﲻ����
	*/
	UINT8 UpdateSaleValue(void);
	

};

#endif

