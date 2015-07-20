/**
 @file  ADSLConnection.h
 @brief ���ļ�������ADSL����ģʽ�йصļ��������ࡣ
 @author   zl
*/

#ifndef	__H_NET_ADSL_CONNECTION_
#define	__H_NET_ADSL_CONNECTION_

#include "netConnection.h"



/**
 @class connectADSL 
 @brief ���ฺ����ADSL�������ӡ�
 */
class connectADSL : public ConnectACT
{
public:
	int connect(string &strErr);

	connectADSL(CNetConnection *p):ConnectACT(p){};
	virtual ~connectADSL(){};
};

/**
 @class disconnectADSL 
 @brief ���ฺ��Ͽ�ADSL���硣
 */
class disconnectADSL : public DisConnectACT
{
public:
	int disConnect();

	disconnectADSL(CNetConnection *p):DisConnectACT(p){};
	virtual ~disconnectADSL(){};
};

/**
 @class GetIPinfoADSL 
 @brief ���ฺ���ȡADSL�����µ�IP��Ϣ��
 */
class GetIPinfoADSL : public GetIPinfoACT
{
public:
	int getIPinfo(IPinfo *info, string &strErr);

	GetIPinfoADSL(CNetConnection *p):GetIPinfoACT(p){};
	virtual ~GetIPinfoADSL(){};
};




/**
 *@class ADSLConnection 
 *@brief ADSL����ģʽ�������ࡣ
 
	����ʵ����ADSL����ģʽ����ĸ�����������������������¾���Ĳ�������
	ADSL������Ͽ�����connectADSL��disconnectADSL��		
	ͨ�ý���״̬��ѯ����CommonCheck��
	ADSLר��IP��Ϣ��ȡ����GetIPinfoADSL��
 */
class ADSLConnection : public CNetConnection
{
public:
	ADSLConnection();
	~ADSLConnection();
	
	int setUserNamePwd(string name, string pwd, string &strErr);

};



#endif

