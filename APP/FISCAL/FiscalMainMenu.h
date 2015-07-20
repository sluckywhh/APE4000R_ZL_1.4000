/*! \file    FiscalMainMenu.h
   \brief    ˰�ع������˵�
   \author   zl
   \version  1.0
   \date     2008-01-01
 */

#ifndef FISCAL_MENU_H
#define FISCAL_MENU_H

#include "MultiBtnCommonWin.h"
#include "CaLabel.h"
#include "CaButton.h"
#include "CMainFrame.h"
#include "CGlobalArg.h"

/**
 *@class CFiscalMenu 
 *@brief ˰��������
 */
class CFiscalMenu : public CMultiBtnCommonWin
{
public:
	CFiscalMenu();
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
	
private:
	/*!
	@brief ��ʼ����ť
	*/
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	/*!
	@brief �걨��ť
	*/
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);
	/*!
	@brief ��Ʊ�ַ���ť
	*/
	void OnButton3(int iEvent, unsigned char * pEventData, int iDataLen);
	/*!
	@brief ��˰��ť
	*/
	void OnButton4(int iEvent, unsigned char * pEventData, int iDataLen); 
	/*!
	@brief ��Ϣ���°�ť
	*/
	void OnButton5(int iEvent, unsigned char * pEventData, int iDataLen); 
	/*!
	@brief ��Ʊ�ϴ���ť
	*/
	void OnButton6(int iEvent, unsigned char * pEventData, int iDataLen); 
	/*!
	@brief ��Ʊ��¼��ť
	*/
	void OnButton7(int iEvent, unsigned char * pEventData, int iDataLen); 
	/*!
	@brief �������ݰ�ť
	*/
	void OnButton8(int iEvent, unsigned char * pEventData, int iDataLen); 

};


#endif
