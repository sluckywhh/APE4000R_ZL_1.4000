/**
 @file  Sending.cpp
 @brief ���ļ�ʵ�������������շ��Ļ��࣬��������Ϊ������շ������ࡣ
 */
#include "Sending.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


Sending::Sending()
{
	m_serverIP="";
	m_serverPort="";
}

Sending::~Sending()
{
}

int Sending::init()
{
	DBG_PRINT(("in Sending::init()"))
	return NET_SUCCESS;
}

void Sending::setFlow(int flow)
{
	DBG_ASSERT_EXIT((0), ("not WMMP mode. ERR!!"));
}

void Sending::SetServerIP(const string IP, const string Port)
{
	m_serverIP.assign(IP);
	m_serverPort.assign(Port);
}
	


