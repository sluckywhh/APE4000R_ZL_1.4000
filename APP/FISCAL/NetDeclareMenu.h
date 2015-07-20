/*! \file    NetDeclareMenu.h
   \brief    ���糭���˵�
   \author   zcy
   \version  1.0
   \date     20150-05-06
 */

#ifndef NET_DECLARE_MENU_H
#define NET_DECLARE_MENU_H

#include "MultiBtnCommonWin.h"
#include "CaLabel.h"
#include "CaButton.h"
#include "CMainFrame.h"


/**
 *@class CNetDeclMenu
 *@brief ˰��������
 */
class CNetDeclMenu : public CMultiBtnCommonWin
{
public:
	CNetDeclMenu();
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
	@brief ���糭˰
	*/
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	/*!
	@brief �����忨"
	*/
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);
	
};


#endif
