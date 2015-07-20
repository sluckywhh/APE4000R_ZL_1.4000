// InvRetServerWin.h: interface for the CInvRetServerWin class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __INV_RET_TO_SERVER_H
#define __INV_RET_TO_SERVER_H

#include "CaWindow.h"
#include "CaInput.h"
#include "CaButton.h"
#include "comdatatype.h"
#include <string>
using namespace std;
#include "CInvVol.h"

class CInvRetServerWin : public CaWindow  
{
private:
	CaInput *m_pInput1, *m_pInput2, *m_pInput3; /**< ָ����������ָ�� */
	CaButton *m_pBtn1, *m_pBtn2;				/**< ָ��ť��ָ�� */
	
	int m_iBtnW;								/**< ����ʱ���ؼ��Ŀ�� */  

	string m_strSno, m_strEno, m_strCode;
	INT32 m_sInvNo, m_eInvNo;
	int m_iColW;	
	CInvVol m_invVol;
public:
	CInvRetServerWin();
	~CInvRetServerWin();

	/*! @function
	*************************************************************************
	<PRE>
	������  : 
	����    : ��������
	����    : [in] int iX ���ϽǺ�����
				[in] int iY ���Ͻ�������
				[in] int iW ���
				[in] int iH �߶�
	����ֵ  : 1 ���ɹ���������ʧ��
	����    : ������
	����    : 2010-12-01
	��ע    : 
	</PRE>
	************************************************************************/
	int Create(int iX,int iY,int iW,int iH);

	/*! @function
	*************************************************************************
	<PRE>
	������  : 
	����    : �����¼�
	����    : [in] iEvent �¼����
				[in] pEventData �¼�����
				[in] iDataLen �¼����ݳ���
	����ֵ  : 1  �Ѵ��� 0 �޷�����
	����    : ������
	����    : 2010-12-01
	��ע    : 
	</PRE>
	************************************************************************/
	int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);

	/*! @function
	*************************************************************************
	<PRE>
	������  : 
	����    : ˢ�´�����ʾ
	����    : 
	����ֵ  : 1: SUCCESS
	����    : ������
	����    : 2010-12-01
	��ע    : 
	</PRE>
	************************************************************************/
	virtual int ReFresh();

	/*! @function
	*************************************************************************
	<PRE>
	������  : S_OnButton1
	����    : ��ť1��Ӧ�¼�
	����    : 
	����ֵ  :
	����    : ������
	����    : 2010-12-01
	��ע    : 
	</PRE>
	************************************************************************/
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

	/*! @function
	*************************************************************************
	<PRE>
	������  : S_OnButton1
	����    : ��ť1��Ӧ�¼�
	����    : 
	����ֵ  :
	����    : ������
	����    : 2010-12-01
	��ע    : 
	</PRE>
	************************************************************************/
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);

	/*! @function
	*************************************************************************
	<PRE>
	������  : S_OnButton2
	����    : ��ť2��Ӧ�¼�
	����    : 
	����ֵ  :
	����    : ������
	����    : 2010-12-01
	��ע    : 
	</PRE>
	************************************************************************/
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

	/*! @function
	*************************************************************************
	<PRE>
	������  : S_OnButton2
	����    : ��ť2��Ӧ�¼�
	����    : 
	����ֵ  :
	����    : ������
	����    : 2010-12-01
	��ע    : 
	</PRE>
	************************************************************************/
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);
	
	void DoActive();
	
	static	void S_OnActive(CaWindow *obj);

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
	static void S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ��������Ӧ�ľ�̬����
	@param[in] obj �ؼ�ָ��
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	static void S_OnInput3(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

	/*! @function
	*************************************************************************
	<PRE>
	������  : 
	����    : ��������Ƿ���Ч 
	����    : 
	����ֵ  : 1 SUCCESS; ����: �������
	����    : ������
	����    : 2010-12-04
	��ע    : 
	</PRE>
	************************************************************************/
	UINT8 CheckInput(string &strErr);
	
	/*! @function
	*************************************************************************
	<PRE>
	������  : 
	����    : ������Ϣ��ʾ�� 
	����    : 
	����ֵ  : ret   ����� 
	����    : ������
	����    : 2010-12-04
	��ע    : 
	</PRE>
	************************************************************************/
    UINT8 ErrMsgBox(UINT8 ret);

	/*!
	@brief ������1��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnInput1(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ������2��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnInput2(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief ������2��Ӧ����	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	*/
	void OnInput3(int iEvent, unsigned char * pEventData, int iDataLen);

};

#endif // !defined(AFX_INVRETSERVERWIN_H__98B88A47_BA1B_4EE2_BCA0_33F230CE2627__INCLUDED_)
