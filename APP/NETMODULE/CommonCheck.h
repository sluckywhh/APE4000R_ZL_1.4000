/**
 @file  CommonCheck.h
 @brief ���ļ��������������״̬��ѯ��ͨ�ã��������ࡣ
 @author   zl
*/
#ifndef	__H_NET_COMMON_CHECK_
#define	__H_NET_COMMON_CHECK_

#include "netConnection.h"


/**
 @class CommonCheck 
 @brief ���ฺ���ѯ�������״̬�������ڶ�������ģʽ����
 */
class CommonCheck : public CheckConnectionACT
{
public:
	int check();

	CommonCheck(CNetConnection *p):CheckConnectionACT(p){};
	virtual ~CommonCheck(){};	

private:

};



#endif

