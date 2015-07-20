/**
 @file  3GConnection.h
 @brief ���ļ���������3G����ģʽ�йصļ��������ࡣ
 @author   zl
*/

#ifndef	__H_NET_3G_CONNECTION_
#define	__H_NET_3G_CONNECTION_


#include "netConnection.h"


/** @brief ö�٣�������Ӫ������ */
enum CARRIER_TYPE
{
	CARRIER_NONE = 0,
	CARRIER_CT,			/**< ���� */
	CARRIER_CU,			/**< ��ͨ */
};


#define	SCRIPT_FILE_CT		"/etc/ppp/peers/evdo"
#define	SCRIPT_FILE_CU		"/etc/ppp/peers/unicom"

#define	SECRETS_FILE		"/etc/ppp/chap-secrets"


#define	DEF_USER_NAME_CT		"card"
#define	DEF_USER_PWD_CT			"card"

#define	DEF_USER_NAME_CU		"3gnet"
#define	DEF_USER_PWD_CU			"GSM"

#define _AT_BAUDRATE_3G			B115200 


/**
 @class connect3G 
 @brief ���ฺ����3G�������ӡ�
 */
class connect3G : public ConnectACT
{
public:
	int connect(string &strErr);

	connect3G(CNetConnection *p):ConnectACT(p){};
	virtual ~connect3G(){};
};

/**
 @class disconnect3G 
 @brief ���ฺ��Ͽ�3G���硣
 */
class disconnect3G : public DisConnectACT
{
public:
	int disConnect();

	disconnect3G(CNetConnection *p):DisConnectACT(p){};
	virtual ~disconnect3G(){};
};





/**
 *@class _3GConnection 
 *@brief 3G����ģʽ�������ࡣ
 
	����ʵ����3G����ģʽ����ĸ�����������������������¾���Ĳ�������
	3G������Ͽ�����connect3G��disconnect3G��		
	ͨ�ý���״̬��ѯ����CommonCheck��
	ͨ��IP��Ϣ��ȡ����CommonGetIPinfo��
 */
class _3GConnection : public CNetConnection
{
private:
	char *m_pATBuff;				/**< AT�����ָ�� */

public:
	int setUserNamePwd(string name, string pwd, string &strErr);
	int getCSQ(int *rssi, int *ber);

	/*!
	@brief ����3G��Ӫ�̡�	
	@param[in] type ��Ӫ������
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	int set3Gcarrier(int type, string &strErr);
	


	_3GConnection();
	~_3GConnection();

private:
	/*!
	@brief �޸�3G���Žű�������
	@param[in] name �û�����
	@param[in] pwd ����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	int set3GScirptFunc(string &name, string &pwd, string &strErr);

	/*!
	@brief ��ȡĬ�ϵ�3G�û��������롣
	@param[out] name �û�����
	@param[out] pwd ����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	void getDefUserNamePwd(string &name, string &pwd);

	/*!
	@brief ����3G�˿��ļ���
	@return 3G�˿��ļ�������
	@note �����γ��Դ�ÿ�����ܵ��豸�ļ�����
	*/
	int open_at_port();

};



#endif

