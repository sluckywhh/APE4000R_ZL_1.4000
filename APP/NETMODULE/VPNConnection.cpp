/**
 @file  VPNConnection.cpp
 @brief ���ļ�ʵ������VPN����ģʽ�йصļ��������ࡣ
 @author   zl
*/

#include "commonFunc.h"
#include "vpnProc.h"
#include "CommonCheck.h"
#include "CommonGetIPinfo.h"
#include "netManager.h"
#include "VPNConnection.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"



int connectVPN::connect(string &strErr)
{
	const INT32 MAX_RETRY_TIMES=8;	
	INT32 i = 0; 
	INT32 ret = 0; 
	INT32 connectModeL1 = 0; 
	CNetConnection *connectL1 = NULL; 
	string vpnIP(""), vpnName(""), vpnPwd("");
	INT8 tmpbuf[128];
	CNetConnection *p = m_pConnection;

	DBG_PRINT(("ConnectVPN..."));

	connectL1 = g_netManager->GetConnectionHandle();
	if (connectL1->performCheck() != CHECK_OK)
	{
		strErr = "��һ�����ӶϿ����޷�VPN����";
		return NET_CONNECT_FAIL;
	}

	DBG_PRINT(("is VPN already connect?"));
	if (p->performCheck() == CHECK_OK)
	{
		DBG_PRINT(("VPN������δ�Ͽ�"))
		return NET_SUCCESS;
	}

	DBG_PRINT(("load VPN info..."));
	if (CNetDBWork::loadVPNServer(vpnIP, strErr) != SQLITE_OK)
	{
		strErr += ":vpnIP";
		return NET_OPERATOR_DB_ER;		
	}
	if (CNetDBWork::loadVPNUserNamePwd(vpnName, vpnPwd, strErr) != SQLITE_OK)
	{
		return NET_OPERATOR_DB_ER;		
	}

	DBG_PRINT(("dial VPN proc..."));
	//����VPN���Ź���
	//�ȱ���ԭʼ·��
	if((ret=VPN_getOri_route()) != VPN_SUCCESS)
	{
		strErr = "����ԭ·�ɳ���";
		return NET_CONNECT_FAIL;
	}

	//VPN����
	connectModeL1 = g_netManager->GetConnectionMode();
	ret= VPN_connent(vpnIP.c_str(), vpnName.c_str(), vpnPwd.c_str());
	if(ret < 0)
	{
		memset((void*)tmpbuf,0 ,sizeof(tmpbuf));
		sprintf(tmpbuf,"VPN���ų���:%d",ret);
		strErr = tmpbuf;
		VPN_close(connectModeL1);
		return NET_CONNECT_FAIL;
	}
	//�ȴ�VPNͨ������
	for(i=0; i<MAX_RETRY_TIMES; i++)
	{			
		if (p->performCheck() == CHECK_OK)
		{
			DBG_PRINT(("ConnectVPN..CHECK_OK."));
			CommonSleep(500);
			break;
		}
		else
		{
			CommonSleep(2000);
		}
	}
	if (i>=MAX_RETRY_TIMES)
	{
		strErr = "VPN����ʧ��";
		VPN_close(connectModeL1);
		return NET_CONNECT_FAIL;
	}
		
	//�����µ�·��
    if((ret=VPN_setVPN_route(connectModeL1)) != VPN_SUCCESS)
	{
		strErr = "������·�ɳ���";
		VPN_close(connectModeL1);
		return NET_CONNECT_FAIL;
	}
	

	p->m_dialState = HAVE_DIALED;
	return NET_SUCCESS;
}

int disconnectVPN::disConnect()
{
	int ret=0;
	INT32 connectModeL1 = g_netManager->GetConnectionMode(); 
	CNetConnection *p = m_pConnection;

	//�ָ�ԭ·��
	VPN_setOri_route();

	//VPN�Ͽ�
	ret = VPN_close(connectModeL1);
	if(ret !=0)
	{
		DBG_PRINT(("vpn close fail, ret = %d", ret));
		return NET_CONNECT_FAIL;
	}
	
	p->m_dialState = NOT_DIALED;
	return NET_SUCCESS;
}



VPNConnection::VPNConnection()
{
	m_connectionMode = NET_VPN;
	m_dialState = NOT_DIALED;

	m_pConnect = new connectVPN(this);
	m_pDisConnect = new disconnectVPN(this);
	m_pCheck = new CommonCheck(this);
	m_pGetIPinfo = new CommonGetIPinfo(this);
}

VPNConnection::~VPNConnection()
{
}


int VPNConnection::setVPNip(string ip, string &strErr)
{
	int ret=0;
	string name(""), pwd("");
	INT8 tmpbuf[16];

	if (performCheck() != CHECK_NOT)
	{
		strErr = "���ȶϿ�VPN����";
		return NET_CONDITION_ER;
	}
	
	if (CNetDBWork::loadVPNUserNamePwd(name, pwd, strErr) != SQLITE_OK)
	{
		DBG_PRINT(("��VPN�ʻ���Ϣ����%s", strErr.c_str()));
	}

	if ((ret=setVPN_para(ip.c_str(), name.c_str(), pwd.c_str())) != VPN_SUCCESS)
	{
		strErr = "�޸�VPN�����ļ���:";
		sprintf(tmpbuf, "%d", ret);
		strErr += tmpbuf;
		return NET_OPERATOR_FILE_ER;
	}
	DBG_PRINT(("setVPN_para SUCCESS"));

	if (CNetDBWork::saveVPNServer(ip, strErr) != SQLITE_OK)
	{
		strErr += ":vpnIP";
		return NET_OPERATOR_DB_ER;
	}
	return NET_SUCCESS;
}

int VPNConnection::setUserNamePwd(string name, string pwd, string &strErr)
{
	int ret=0;
	string ip("");
	INT8 tmpbuf[16];
	
	if (performCheck() != CHECK_NOT)
	{
		strErr = "���ȶϿ�VPN����";
		return NET_CONDITION_ER;
	}

	if (CNetDBWork::loadVPNServer(ip, strErr) != SQLITE_OK)
	{
		DBG_PRINT(("��VPN������IP��%s", strErr.c_str()));
	}

	if ((ret=setVPN_para(ip.c_str(), name.c_str(), pwd.c_str())) != VPN_SUCCESS)
	{
		strErr = "�޸�VPN�����ļ���:";
		sprintf(tmpbuf, "%d", ret);
		strErr += tmpbuf;
		return NET_OPERATOR_FILE_ER;
	}

	if (CNetDBWork::saveVPNUserNamePwd(name, pwd, strErr) != SQLITE_OK)
	{
		return NET_OPERATOR_DB_ER;
	}
	return NET_SUCCESS;
}


