/*! \file    BasicReportMenu.h
   \brief    awe4000r�����ӡ�Ļ�����Ϣ�˵�
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */


#ifndef BASIC_REPORT_MENU_H
#define BASIC_REPORT_MENU_H
#include "CaButton.h"
#include "MultiBtnCommonWin.h"
#include "CaLabel.h"

using namespace std;

/**
 *@class CBasicReportMenu 
 *@brief �����ӡ�Ļ�����Ϣ�˵�
 */
class CBasicReportMenu : public CMultiBtnCommonWin
{
public:

	/*!
	@brief ���캯��	
	*/
	CBasicReportMenu();

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


};

#endif