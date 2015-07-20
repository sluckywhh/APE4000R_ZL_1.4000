/**
 @file  DoNothing.h
 @brief ���ļ�����������κ�����ģʽ�������ࣨ��ߴ�������ԣ���
 @author   zl
*/
#ifndef	__H_NET_DO_NOTHING_
#define	__H_NET_DO_NOTHING_


#include "netConnection.h"


/**
 @class connectNothing 
 @brief �յĽ������Ӳ���
 */
class connectNothing : public ConnectACT
{
public:
	int connect(string &strErr);

	connectNothing(CNetConnection *p):ConnectACT(p){};
	virtual ~connectNothing(){};
};

/**
 @class disconnectNothing 
 @brief �յĶϿ����Ӳ���
 */
class disconnectNothing : public DisConnectACT
{
public:
	int disConnect();

	disconnectNothing(CNetConnection *p):DisConnectACT(p){};
	virtual ~disconnectNothing(){};
};

/**
 @class checkNothing 
 @brief �յļ������״̬����
 */
class checkNothing : public CheckConnectionACT
{
public:
	int check();

	checkNothing(CNetConnection *p):CheckConnectionACT(p){};
	virtual ~checkNothing(){};
};

/**
 @class IPinfoDoNothing 
 @brief �յĻ�ȡIP����
 */
class IPinfoDoNothing : public GetIPinfoACT
{
public:
	int getIPinfo(IPinfo *info, string &strErr);

	IPinfoDoNothing(CNetConnection *p):GetIPinfoACT(p){};
	virtual ~IPinfoDoNothing(){};
};


/**
 @class NoneConnection 
 @brief �յ�����ģʽ����ߴ�������ԣ�
 */
class NoneConnection : public CNetConnection
{
public:
	NoneConnection();
	~NoneConnection();
};

#endif

