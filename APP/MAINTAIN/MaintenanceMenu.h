/*! \file    MaintenanceMenu.h
   \brief    awe4000r���۳�����ϵͳά�����˵�
   \author   Yu Yan
   \version  1.0
   \date     2008-3-19 
 */

#ifndef MAINTENANCE_MENU_H
#define MAINTENANCE_MENU_H

#include "MaintenanceFunc.h"
#include "CMainFrame.h"
#include "MultiBtnCommonWin.h"
#include "CaLabel.h"
#include "CaButton.h"
#include"pos_debug.h"
#include "g_def.h"
#include <string>
using namespace std;

/**
 *@class CMaintenanceMenu 
 *@brief ϵͳά�����˵�
 */
class CMaintenanceMenu : public CMultiBtnCommonWin
{
public:
	CMaintenanceMenu();

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
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton3(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton4(int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton5(int iEvent, unsigned char * pEventData, int iDataLen); 

	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton6(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��ť��Ӧ����
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton7(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��������	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton8(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief �������	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton9(int iEvent, unsigned char * pEventData, int iDataLen);

//	void OnButton10(int iEvent, unsigned char * pEventData, int iDataLen);

};


#endif
