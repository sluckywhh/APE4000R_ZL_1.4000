/**
 @file  CommonGetIPinfo.h
 @brief ���ļ������˻�ȡIP��Ϣ��ͨ�ã��������ࡣ
 @author   zl
*/
#ifndef	__H_NET_COMMON_IP_INFO_
#define	__H_NET_COMMON_IP_INFO_


#include "netConnection.h"



/**
 @class CommonGetIPinfo 
 @brief ���ฺ���ȡ��ǰ�����IP��Ϣ�������ڶ�������ģʽ����
 */
class CommonGetIPinfo : public GetIPinfoACT
{
public:
	int getIPinfo(IPinfo *info, string &strErr);

	CommonGetIPinfo(CNetConnection *p):GetIPinfoACT(p){};
	virtual ~CommonGetIPinfo(){};	
};



#endif

