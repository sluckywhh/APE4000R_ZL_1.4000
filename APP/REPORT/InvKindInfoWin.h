/*! \file    InvKindInfoWin.h
   \brief    awe4000r�����ӡ��Ʊ����Ϣ����
   \author   zcy
   \version  1.0
   \date     2011-7-5
 */

#ifndef   INV_KIND_INFO_WIN_H
#define INV_KIND_INFO_WIN_H

#include "MultiLabelCommonWindow.h"
#include "CMainFrame.h"
#include "CaButton.h"
#include "CaMsgBox.h"
#include "CaObject.h"
#include "printer.h"
#include "CGlobalArg.h"
#include <string>

using namespace std;

/**
 *@class CCorpInfoWin 
 *@brief �����ӡ��Ʊ����Ϣ����
 */
class CInvKindInfoWin : public CMultiLabelCommonWin
{
private:
//	CTax *ptaxItem;							/**< ˰��˰Ŀ��Ϣ���ָ��*/
	struct TInvKindInfoPrnData	m_InvKindInfo;		/**< Ʊ����Ϣ�ṹ��*/
	struct TInvKindInfoPrnData	*m_pInvKindInfo;	/**< Ʊ����Ϣ�ṹ��ָ��*/
	

public:

	/*!
	@brief ���캯��	
	*/
	CInvKindInfoWin();


	/*!
	@brief ��������	
	*/
	~CInvKindInfoWin();

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
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	virtual void OnButton1(int iEvent,unsigned char *pEventData, int iDataLen);

	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	virtual void OnButton2(int iEvent,unsigned char *pEventData, int iDataLen);
	
	/*!
	@brief ���ý�����ʾ����	 
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 NormalShow();

	/*!
	@brief ������ʾ���ݵľ�̬����	 
	*/
	static void S_OnActive(CaWindow *obj);
    
	/*!
	@brief ������ʾ���ݵĺ���	 
	*/
	void DoActive(); 

	/*!
	@brief ��ӡ��ҵ��Ϣ	 
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 PrintInvKindInfo();

	/*!
	@brief ��ѯINV_KIND����N0Ϊ1����
	@return 1: SUCCESS; 0: FAILURE
	*/
	UINT8 CheckInvKindOne();
	
};


#endif