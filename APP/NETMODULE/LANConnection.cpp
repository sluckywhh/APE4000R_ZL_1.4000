/**
 @file  LANConnection.cpp
 @brief ���ļ�ʵ�����������ģʽ�йصļ��������ࡣ
 @author   zl
*/
#include "commonFunc.h"
#include "DoNothing.h"
#include "CommonGetIPinfo.h"
#include "setToFileProc.h"
#include "netManager.h"
#include "LANConnection.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"



int LANCheck::check()
{
	int sysRet=0;
	LANConnection *p = (LANConnection *)m_pConnection;
	
	if (p->m_dhcpMode == LAN_DHCP_ON)
	{
		sysRet = system("ifconfig eth0");
		if (sysRet != 0)
			return CHECK_OFF;
		else
			return CHECK_OK;
	}
	else		//�ֶ���IP��ʽ�£�Ŀǰ���޷��ж�����״̬
	{
		return CHECK_OK;
	}

}


LANConnection::LANConnection()
{
	string strErr("");

	m_connectionMode = NET_LAN;
	m_dialState = HAVE_DIALED;	//LANģʽ��ֱ�Ӵ����Ѳ��ŵ�״̬
	
	m_pConnect = new connectNothing(this);
	m_pDisConnect = new disconnectNothing(this);
	m_pCheck = new LANCheck(this);
	m_pGetIPinfo = new CommonGetIPinfo(this);

	if (CNetDBWork::loadDHCPMode(&m_dhcpMode, strErr) != SQLITE_OK)
	{
		m_dhcpMode = LAN_DHCP_OFF;
	}
}

LANConnection::~LANConnection()
{
}

int LANConnection::setDhcpMode(INT32 dhcpMode, string &strErr)
{
	if (g_netManager->checkConnect() == CONNECT_ON_L2)
	{
		strErr = "���ȶϿ�VPN����";
		return NET_CONDITION_ER;
	}

	//�޸�/bin/init�ű�
	if (updateInitFileForDHCP(dhcpMode) != NET_SUCCESS)
	{
		strErr = "�޸�init�ű�����";
		return NET_OPERATOR_FILE_ER;
	}
		
	//DHCP״̬�������ݿ�
	if (CNetDBWork::saveDHCPMode(dhcpMode, strErr) != SQLITE_OK)
	{
		return NET_OPERATOR_DB_ER;
	}

	m_dhcpMode = dhcpMode;

	//����DHCP
	IPinfo info;
	if (CNetDBWork::loadIPinfo(&info, strErr) != SQLITE_OK)
	{
		DBG_PRINT(("%s", strErr.c_str()))
		DBG_PRINT(("���ݿ�����ip��Ϣ,"));
		return NET_SUCCESS;
	}
	restartDHCP(m_dhcpMode, &info);

	return NET_SUCCESS;
}

int LANConnection::setIPinfo(IPinfo *info, string &strErr)
{
	if (m_dhcpMode == LAN_DHCP_ON)
	{
		strErr = "�Զ���ȡIPģʽ���޷�����";
		return NET_MODE_ER;
	}
	if (g_netManager->checkConnect() == CONNECT_ON_L2)
	{
		strErr = "���ȶϿ�VPN����";
		return NET_CONDITION_ER;
	}

	//�޸�/bin/init�ű���DNS�����ļ�
	if (setIPinfoToFile(info) != NET_SUCCESS)
	{
		strErr = "�޸������ļ�����";
		return NET_OPERATOR_FILE_ER;
	}

	//�µ�IP���ü�¼���
	if (CNetDBWork::saveIPinfo(info, strErr) != SQLITE_OK)
	{
		return NET_OPERATOR_DB_ER;
	}

	//����������
	restartLAN(info);

	return NET_SUCCESS;
}

int LANConnection::initNetDevice(string &strErr)
{
	IPinfo info;
	char tmpbuf[32];

	CNetDBWork::loadIPinfo(&info, strErr);
	system("ifconfig eth0 up");
	sprintf(tmpbuf, "route add default gw %s", info.GeteWay);
	DBG_PRINT(("%s", tmpbuf))
	system(tmpbuf);
	return NET_SUCCESS;
}

