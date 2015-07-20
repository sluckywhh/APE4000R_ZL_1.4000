/**
 @file  M2M_WMMP_Connection.h
 @brief ���ļ���������M2M-WMMPģʽ�йصļ��������ࡣ
 @author   zl
*/
#ifndef	__H_NET_M2M_WMMP_CONNECTION_
#define	__H_NET_M2M_WMMP_CONNECTION_


#include "M2M_Common.h"


/**
 @class M2M_WMMP_Check 
 @brief ���ฺ���ѯ�������״̬��WMMPģʽר�ã���
 @note ��ʵû�����κ�ʵ�ʵ��жϡ�
 */
class M2M_WMMP_Check : public CheckConnectionACT
{
public:
	int check();

	M2M_WMMP_Check(CNetConnection *p):CheckConnectionACT(p){};
	virtual ~M2M_WMMP_Check(){};
};



/**
 *@class M2M_WMMP_Connection 
 *@brief M2M_WMMPģʽ�������ࡣ
 
	����ʵ����M2M_WMMPģʽ����ĸ�����������������������¾���Ĳ�������
	�յ�������Ͽ�����connectNothing��disconnectNothing��		
	M2M_WMMPר�ý���״̬��ѯ����M2M_WMMP_Check��
	�յ�IP��Ϣ��ȡ����IPinfoDoNothing��
 */
class M2M_WMMP_Connection : public M2MCommon
{
public:
	int initNetDevice(string &strErr);

	M2M_WMMP_Connection();
	~M2M_WMMP_Connection();

};


#endif

