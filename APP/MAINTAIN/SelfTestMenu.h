/*! \file    SelfTestMenu.h
   \brief    awe4000r���۳����л����Լ����˵�
   \author   Yu Yan
   \version  1.0
   \date     2008-3-19
 */

#ifndef SELF_TEST_MENU_H
#define SELF_TEST_MENU_H

#include "MaintenanceFunc.h"
#include "CMainFrame.h"
#include "CaWindow.h"
#include "CaLabel.h"
#include "CaButton.h"
#include "CaButtonList.h"

#include "SysArgInfo.h"
#include "SysArgEditWin.h"


#include"pos_debug.h"
#include "g_def.h"
#include <string>
using namespace std;

#define MAX_BTN_NUM		15

/**
 *@class CSelfTestMenu 
 *@brief �����Լ����˵�
 */
class CSelfTestMenu : public CaWindow
{
private:
	int m_iNumOfBtn;			/**< ��ť���� */
	CaButton *m_pBtn[MAX_BTN_NUM];		/**< ָ��ť��ָ�� */
	CaButtonList *m_pBtnList;	/**< ָ��ť�б��ָ�� */
    UINT8 ifLightOn;            /**< ����Ƶ�����־ */
	CSysArgEditWin *m_pSysArgEditWin;
private:
	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton0(int iEvent, unsigned char * pEventData, int iDataLen);
	
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
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton8(int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton9(int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton10(int iEvent, unsigned char * pEventData, int iDataLen); 
	
	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton11(int iEvent, unsigned char * pEventData, int iDataLen); 
	
	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton12(int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton13(int iEvent, unsigned char * pEventData, int iDataLen); 
#if (POS_TYPE != POS_APE5020R)
	/*!
	@brief ��ť��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnButton14(int iEvent, unsigned char * pEventData, int iDataLen); 
#endif
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton0(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
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
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton4(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton5(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton6(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton7(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton8(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton9(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton10(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton11(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton12(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton13(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

#if (POS_TYPE != POS_APE5020R)
	/*!
	@brief ��ť��Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnButton14(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
#endif
//	inline void Adjustm_iH(int h)
//	{
//		// m_pBtnList->m_iH += h ; 
//	}
public:

	/*!
	@brief ���캯��	
	*/
	CSelfTestMenu();

	/*!
	@brief ��������	
	*/
	~CSelfTestMenu();

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
};


#endif
