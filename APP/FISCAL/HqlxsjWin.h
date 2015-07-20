/*! \file    HqlxsjWin.h
   \brief    awe4000r��ȡ�������ݽ���
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */

#ifndef HQLXSJ_WIN_H
#define HQLXSJ_WIN_H

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
 *@class CHqlxsjWin 
 *@brief �����ӡ����ҵ��Ϣ����
 */
class CHqlxsjWin : public CMultiLabelCommonWin
{
private:
	struct TGetOffLineData	m_OffLineDate;		/**< �������ݽṹ��*/
	struct TGetOffLineData	*m_pOffLineDate;	/**< �������ݽṹ��*/

	string m_wscfpzs;		//δ�ϴ���Ʊ����
	string m_wscfpsj;		//δ�ϴ���Ʊʱ��
	string m_wscfpljje;		//δ�ϴ���Ʊ�ۼƽ��
	string m_sczs;			//�ϴ�����
	string m_scsjjg;		//�ϴ�ʱ����
	
public:

	/*!
	@brief ���캯��	
	*/
	CHqlxsjWin();

	/*!
	@brief ��������	
	*/
	~CHqlxsjWin();

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
	@brief ��ȡ����������Ϣ
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 GetOffLineDate();

	/*!
	@brief ��ӡ����������Ϣ
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 PrintOffLineDate();
	
	void Reset();

};

#endif