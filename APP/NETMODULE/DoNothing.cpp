/**
 @file  DoNothing.cpp
 @brief ���ļ�����������κ�����ģʽ�������ࣨ��ߴ�������ԣ���
 @author   zl
*/
#include "DoNothing.h"


int connectNothing::connect(string &strErr)
{
	return NET_SUCCESS;
}

int disconnectNothing::disConnect()
{
	return NET_SUCCESS;
}

int checkNothing::check()
{
	return CHECK_NOT;
}

int IPinfoDoNothing::getIPinfo(IPinfo *info, string &strErr)
{
	strErr="��ǰ����ģʽ����IP��Ϣ"; 
	return NET_MODE_ER;
}


NoneConnection::NoneConnection()
{
	m_connectionMode = NET_NONE;
	m_dialState = NOT_DIALED;	
	m_pConnect = new connectNothing(this);
	m_pDisConnect = new disconnectNothing(this);
	m_pCheck = new checkNothing(this);	
	m_pGetIPinfo = new IPinfoDoNothing(this);
}

NoneConnection::~NoneConnection()
{
}

