/*! \file    MediumDeclareMenu.cpp
   \brief    ���ʳ����˵�
   \author   zcy
   \version  1.0
   \date     2015-05-06
 */

#ifndef MED_DECL_MENU_H
#define MED_DECL_MENU_H

#include "MultiBtnCommonWin.h"
#include "CaLabel.h"
#include "CaButton.h"
#include "CMainFrame.h"


/**
 *@class CMedDeclMenu 
 *@brief ˰��������
 */
class CMedDeclMenu : public CMultiBtnCommonWin
{
public:
	CMedDeclMenu();
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
	@brief ���ڳ�˰
	*/
	//void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	/*!
	@brief ���ʱ�˰
	*/
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	/*!
	@brief �������
	*/
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);



};


#endif
