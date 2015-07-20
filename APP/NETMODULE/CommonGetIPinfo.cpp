/**
 @file  CommonGetIPinfo.cpp
 @brief ���ļ�ʵ���˻�ȡIP��Ϣ��ͨ�ã��������ࡣ
 @author   zl
*/
#include "netManager.h"
#include "ipInfoProc.h"
#include "CommonGetIPinfo.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"




int CommonGetIPinfo::getIPinfo(IPinfo *info, string &strErr)
{	
	DBG_ASSERT_EXIT((info != NULL), ("info == NULL!"));

	INT32 res=0;
	INT32 netMode = curNetMode();
	string tmpStr("");
	CNetConnection *p = m_pConnection;

	if (netMode==NET_NONE || netMode==NET_M2M_WMMP )
	{
		DBG_PRINT(("getIPinfo. netMode=%d", netMode))
		strErr = "��ǰ����ģʽ����IP��Ϣ";
		return NET_MODE_ER;
	}
	
	if (p->performCheck() != CHECK_OK)
	{
		strErr = "������δ��ͨ,��IP��Ϣ";
		return NET_CONNECT_FAIL;
	}

	//ȷ����ȡIP��Ϣ�Ķ���
	if (netMode == NET_VPN)
	{
		if (g_netManager->GetConnectionMode() == NET_LAN)
			tmpStr = "ppp0";
		else
			tmpStr = "ppp1";
	}
	else if (netMode == NET_LAN)
	{
		tmpStr = "eth0";
	}
	else
	{
		tmpStr = "ppp0";
	}

	memset((void *)info, 0, sizeof(IPinfo));

	// ��ȡIP����������
	res = getIPandMASK(tmpStr.c_str(), info);
	if (res != GET_IPINFO_SUCCESS)
	{
		strErr = "��ȡ����IP����";
		return NET_OTHER_ER;
	}

	// ��ȡ������Ϣ
	res = getRoute(info);
	if (res != GET_IPINFO_SUCCESS)
	{
		strErr = "��ȡ·����Ϣ����";
		return NET_OTHER_ER;
	}
	DBG_PRINT(("m_GateWay = %s", info->GeteWay));

	// ��ȡDNS��Ϣ
	res = getDNS(info);
	if (res != GET_IPINFO_SUCCESS)
	{
		strErr = "��ȡ����DNS����";
		return NET_OTHER_ER;
	}

	return NET_SUCCESS;
}

