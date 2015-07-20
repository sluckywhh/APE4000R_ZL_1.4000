/*! \file    CommerceReportMenu.h
   \brief    awe4000r�����ӡ����ҵͳ�Ʋ˵�
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */


#ifndef COMMERCE_REPORT_MENU_H
#define COMMERCE_REPORT_MENU_H
#include "MultiBtnCommonWin.h"
//#include "LOGCTRL.h"
// #include "pos_debug.h"
#include "g_def.h"
#include "CaLabel.h"
#include "CMainFrame.h"
#include "CaButton.h"
#include <string>

using namespace std;

/**
 *@class CCommerceReportMenu 
 *@brief �����ӡ�Ļ�����Ϣ�˵�
 */
class CCommerceReportMenu : public CMultiBtnCommonWin
{
public:

	/*!
	@brief ���캯��	
	*/
	CCommerceReportMenu();

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
// 	void OnButton4(int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
// 	void OnButton5(int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
// 	void OnButton6(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
//	void OnButton7(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
//	void OnButton8(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
//	void OnButton9(int iEvent, unsigned char * pEventData, int iDataLen);

public:

	/*!
	@brief ��ӡȫ���ͻ���Ϣ
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 PrnClient();

	/*!
	@brief ��ӡȫ��������Ϣ
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 PrnDept();

	/*!
	@brief ��ӡȫ������Ա��Ϣ
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 PrnOperator();

};

#endif