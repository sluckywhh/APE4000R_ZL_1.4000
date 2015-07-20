/*! \file    MachineInfo.h
   \brief    awe4000r�����ӡ�Ļ�����Ϣ����
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */

#ifndef MACHINE_INFO_WIN_H
#define MACHINE_INFO_WIN_H

#include "CaWindow.h"
#include "CaButton.h"
#include "CaLabel.h"
#include "printer.h"
#include "CGlobalArg.h"
#include "netHeaderDef.h"

using namespace std;

/**
 *@class CMachineInfoWin 
 *@brief �����ӡ�Ļ�����Ϣ����
 */
class CMachineInfoWin : public CaWindow
{
private:
	CaLabel *m_pLabel1;		/**< ָ���ǩ��ָ�� */
	CaLabel *m_pLabel2;		/**< ָ���ǩ��ָ�� */
	CaLabel *m_pLabel3;		/**< ָ���ǩ��ָ�� */
	CaLabel *m_pLabel4;		/**< ָ���ǩ��ָ�� */
	
	CaButton *m_pButton1;	/**< ָ��ť��ָ�� */
	CaButton *m_pButton2;	/**< ָ��ť��ָ�� */
	
	int m_iButtonW;			/**< ����ʱ���ؼ��Ŀ�� */  
	int m_iButtonH;			/**< ����ʱ���ڶ�����ʼ��ĺ����� */  
	
	struct TMachinePrnData m_machinePrnInfo; /**< ������Ϣ�ṹ�� */  
	struct TMachinePrnData *m_pMachPrnInfo;  /**< ������Ϣ�ṹ��ָ�� */  

	string m_IMEI;

public:

	/*!
	@brief ���캯��	
	*/
	CMachineInfoWin();

	/*!
	@brief ��������	
	*/
	~CMachineInfoWin();

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
	@brief ����ӡ����ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void PrintMachineInfo(int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief �����ء���ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void ReturnBack(int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ������ʾ���ݵľ�̬����	 
	*/
	static void S_OnActive(CaWindow *obj);
    
	/*!
	@brief ������ʾ���ݵĺ���	 
	*/
	void DoActive(); 

private:

	/*!
	@brief ����ӡ����ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_PrintMachineInfo(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief �����ء���ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_ReturnBack(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
#if _CONFIG_M2M_MODULE
	void GetWmmpIMEINo();
#endif

};
	

#endif
