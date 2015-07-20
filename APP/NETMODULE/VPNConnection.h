/**
 @file  VPNConnection.h
 @brief ���ļ���������VPN����ģʽ�йصļ��������ࡣ
 @author   zl
*/

#ifndef	__H_NET_VPN_CONNECTION_
#define	__H_NET_VPN_CONNECTION_


#include "netConnection.h"



/**
 @class connectVPN 
 @brief ���ฺ����VPN�������ӡ�
 */
class connectVPN : public ConnectACT
{
public:
	int connect(string &strErr);

	connectVPN(CNetConnection *p):ConnectACT(p){};
	virtual ~connectVPN(){};
};

/**
 @class disconnectVPN 
 @brief ���ฺ��Ͽ�VPN���硣
 */
class disconnectVPN : public DisConnectACT
{
public:
	int disConnect();

	disconnectVPN(CNetConnection *p):DisConnectACT(p){};
	virtual ~disconnectVPN(){};
};



/**
 *@class VPNConnection 
 *@brief VPN����ģʽ�������ࡣ
 
	����ʵ����VPN����ģʽ����ĸ�����������������������¾���Ĳ�������
	VPN������Ͽ�����connectVPN��disconnectVPN��		
	ͨ�ý���״̬��ѯ����CommonCheck��
	ͨ��IP��Ϣ��ȡ����CommonGetIPinfo��
 */
class VPNConnection : public CNetConnection
{
public:
	/*!
	@brief ����VPN������IP��	
	@param[in] ip VPN������IP
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	int setVPNip(string ip, string &strErr);

	int setUserNamePwd(string name, string pwd, string &strErr);

	VPNConnection();
	~VPNConnection();
};


#endif

