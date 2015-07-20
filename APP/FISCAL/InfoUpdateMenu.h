/*! \file    InfoUpdateMenu.h
   \brief    ��Ϣ���²˵�
   \author   zl
   \version  1.0
   \date     2008-01-01
 */

#ifndef INFO_UPDATE_MENU_H
#define INFO_UPDATE_MENU_H

#include "MultiBtnCommonWin.h"
#include "CaLabel.h"
#include "CaButton.h"
#include "CMainFrame.h"


/**
 *@class CInfoUpdateMenu 
 *@brief ��Ϣ���²˵�
 */
class CInfoUpdateMenu : public CMultiBtnCommonWin
{
public:
	CInfoUpdateMenu();
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
	@brief ��ҵ��Ϣ
	*/
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	/*!
	@brief Ȩ����Ϣ 
	*/
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);
	
};


#endif
