/*! \file    InvAssignWin.h
   \brief    awe4000r��Ʊ�˻أ����ֻ�һ��������
   \author   xsr
   \version  1.0
   \date     2008-2-22
 */
#ifndef _RET_TO_INV_WIN_H
#define _RET_TO_INV_WIN_H

#include"CaWindow.h"
#include"pos_debug.h"
#include "g_def.h"
#include "CaLabel.h"
#include "CMainFrame.h"
#include "CaInput.h"
#include "CaButton.h"


/**
 *@class CRetToInvWin 
 *@brief ��Ʊ�˻أ����ֻ�һ����ָ������
 */
class CRetToInvWin : public CaWindow
{
public:
	CaInput *m_pInput1;				/**< ָ����������ָ�� */  
	CaInput *m_pInput2;				/**< ָ����������ָ�� */
	CaInput *m_pInput3;				/**< ָ����������ָ�� */  
	CaButton *m_pBtn1;				/**< ָ��ť��ָ�� */
	CaButton *m_pBtn2;				/**< ָ��ť��ָ�� */
	
	int m_iBtnW;					/**< ����ʱ���ؼ��Ŀ�� */  
	int m_iColW;					/**< ����ʱ���ڶ��еĺ����� */  
   
	string m_invCode;               /**< ��Ʊ����*/
	UINT32 m_invStartNo;			/**< ��Ʊ��ʼ���� */ 
	UINT32 m_invNum;				/**< ��Ʊ���� */ 


public:
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
	@brief ���캯��	
	*/
	CRetToInvWin();

	/*!
	@brief ��������Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnInput1(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��������Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnInput2(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��������Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnInput3(int iEvent, unsigned char * pEventData, int iDataLen);

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
	@brief ������ʾ���ݵľ�̬����	 
	*/
	static void S_OnActive(CaWindow *obj);
    
	/*!
	@brief ������ʾ���ݵĺ���	 
	*/
	void DoActive(); 
	
private:
	
	/*!
	@brief ��������Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��������Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��������Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnInput3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
   
	/*!
	@brief ������������յ�ֵ�Ƿ���Ч	
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	@return   1  ������Ч�� 0 ������Ч
	*/
	UINT8 CheckInputValid();
};


#endif
