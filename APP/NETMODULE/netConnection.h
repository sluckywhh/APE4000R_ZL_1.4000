/**
 @file  netConnection.h
 @brief ���ļ������������������صļ������ࡣ

	���ļ�������4������������������Ļ��ࣺ			
	ConnectACT��DisConnectACT��CheckConnectionACT��GetIPinfoACT��
	��һ������ģʽ�Ļ��ࣺ
	CNetConnection��

 @author   zl

*/

#ifndef	__H_NET_CONNECTION_
#define	__H_NET_CONNECTION_


#include "IncludeMe.h"
#include "netHeaderDef.h"
#include "netdbWork.h"
#ifndef _DEBUG_VERSION
#include "powoff_protect.h"
#endif

class CNetConnection;

/**
 @class ConnectACT 
 @brief �����������ӵĻ��ࡣ
 
	�����˽����������ӹ��ܵ�ͳһ�ӿڣ���������ͬ��ʽ�Ľ������������ࡣ
 */
class ConnectACT
{
protected:
	CNetConnection *m_pConnection;				/**< ָ������˱������CNetConnection���� */

public:
	/*!
	@brief �������ӡ�	
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	virtual int connect(string &strErr)=0;
	
	/*!
	@brief ��ȡ��ǰ����ģʽ��	
	@return ����ģʽֵ����ö������ENUM_NET_MODE�ж��塣
	*/
	int curNetMode();

	ConnectACT(CNetConnection *p):m_pConnection(p){};
	virtual ~ConnectACT() {};
};

/**
 @class DisConnectACT 
 @brief �Ͽ��������ӵĻ��ࡣ
 
   �����˶Ͽ��������ӹ��ܵ�ͳһ�ӿڣ���������ͬ��ʽ�ĶϿ����������ࡣ
 */
class DisConnectACT
{
protected:
	CNetConnection *m_pConnection;				/**< ָ������˱������CNetConnection���� */

public:
	/*!
	@brief �Ͽ����ӡ�	
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	virtual int disConnect()=0;
	
	/*!
	@brief ��ȡ��ǰ����ģʽ��	
	@return ����ģʽֵ����ö������ENUM_NET_MODE�ж��塣
	*/
	int curNetMode();
	
	DisConnectACT(CNetConnection *p):m_pConnection(p){};
	virtual ~DisConnectACT() {};
};

/**
 @class CheckConnectionACT 
 @brief ����������״̬�Ļ��ࡣ
 
   �����˸ù��ܵ�ͳһ�ӿڣ���������ͬ��ʽ��״̬��ѯ�����ࡣ
 */
class CheckConnectionACT
{
protected:
	CNetConnection *m_pConnection;			/**< ָ������˱������CNetConnection���� */

public:
	/*!
	@brief �������״̬��ѯ��	
	@return CHECK_OK - �����ӣ�CHECK_NOT - δ�������ӣ�CHECK_OFF - ���Ӻ����
	*/
	virtual int check()=0;
	
	/*!
	@brief ��ȡ��ǰ����ģʽ��	
	@return ����ģʽֵ����ö������ENUM_NET_MODE�ж��塣
	*/
	int curNetMode();

	CheckConnectionACT(CNetConnection *p):m_pConnection(p){};
	virtual ~CheckConnectionACT() {};
};

/**
 @class GetIPinfoACT 
 @brief ��ȡIP��Ϣ�Ļ��ࡣ
 
   �����˸ù��ܵ�ͳһ�ӿڣ���������ͬ��ʽ�Ļ�ȡIP��Ϣ�����ࡣ
 */
class GetIPinfoACT
{
protected:
	CNetConnection *m_pConnection;			/**< ָ������˱������CNetConnection���� */

public:
	/*!
	@brief ��ȡIP��Ϣ��	
	@param[out] info IP��Ϣ�ṹ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	virtual int getIPinfo(IPinfo *info, string &strErr)=0;
	
	/*!
	@brief ��ȡ��ǰ����ģʽ��	
	@return ����ģʽֵ����ö������ENUM_NET_MODE�ж��塣
	*/
	int curNetMode();

	GetIPinfoACT(CNetConnection *p):m_pConnection(p){};
	virtual ~GetIPinfoACT() {};	
};




/**
 *@class CNetConnection 
 *@brief ��������ģʽ�Ļ��ࡣ
 
   �����а�����4��������������Ļ���ָ�룬������Ͼ���������ࡣ
   ����Ϊ�ϲ���붨������������ӿڡ�
   �����������Ϊ�����������뷽ʽ�ࣨ��3G��ADSL�ȣ���
 */
class CNetConnection
{
public:
	int m_connectionMode;				/**< ��������ģʽ */
	int m_dialState;					/**< �Ƿ���ִ�н������ӡ�HAVE_DIALED��NOT_DIALED */

protected:
	ConnectACT *m_pConnect;				/**< ָ����彨�����Ӷ����ָ�� */
	DisConnectACT *m_pDisConnect;		/**< ָ�����Ͽ����Ӷ����ָ�� */
	CheckConnectionACT *m_pCheck;		/**< ָ�����״̬��ѯ�����ָ�� */
	GetIPinfoACT *m_pGetIPinfo;			/**< ָ������ȡIP��Ϣ�����ָ�� */

	
public:
	/*!
	@brief ִ�н����������Ӳ������˺����Ƕ�ҵ���Ľӿڡ�	
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	int performConnect(string &strErr);

	/*!
	@brief ִ�жϿ�����������˺����Ƕ�ҵ���Ľӿڡ�	
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	int performDisConnect();

	/*!
	@brief ִ�н���״̬��ѯ�������˺����Ƕ�ҵ���Ľӿڡ�	
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	int performCheck();

	/*!
	@brief ִ�л�ȡIP��Ϣ�������˺����Ƕ�ҵ���Ľӿڡ�	
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	int performGetIPinfo(IPinfo *info, string &strErr);

	/*!
	@brief �����豸��ʼ����	
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	virtual int initNetDevice(string &strErr);

	/*!
	@brief �����û��������롣	
	@param[in] name �û���
	@param[in] pwd ����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	virtual int setUserNamePwd(string name, string pwd, string &strErr);	

	/*!
	@brief ��ȡ�����ź�ǿ�ȡ�	
	@param[out] rssi �ź�ǿ��ֵ
	@param[out] ber �ź���Ч��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	virtual int getCSQ(int *rssi, int *ber);

	/*!
	@brief ��ȡ��ǰ����ģʽ��	
	@return ����ģʽֵ����ö������ENUM_NET_MODE�ж��塣
	*/
	int curNetMode(){return m_connectionMode;};

	CNetConnection();
	virtual ~CNetConnection();


};

#endif

