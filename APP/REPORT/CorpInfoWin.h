/*! \file    CorpInfoWin.h
   \brief    awe4000r�����ӡ����ҵ��Ϣ����
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */

#ifndef CORP_INFO_WIN_H
#define CORP_INFO_WIN_H

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
 *@brief �����ӡ����ҵ��Ϣ����
 */
class CCorpInfoWin : public CMultiLabelCommonWin
{
private:
// 	CTax *ptaxItem;							/**< ˰��˰Ŀ��Ϣ���ָ��*/
	struct TCorpInfoPrnData	m_corpInfo;		/**< ��ҵ��Ϣ�ṹ��*/
	struct TCorpInfoPrnData	*m_pCorpInfo;	/**< ��ҵ��Ϣ�ṹ��ָ��*/
	
public:

	/*!
	@brief ���캯��	
	*/
	CCorpInfoWin();

	/*!
	@brief ��������	
	*/
	~CCorpInfoWin();

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
	UINT8 PrintCorpInfo();
	
};


#endif