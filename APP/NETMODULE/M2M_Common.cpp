/**
 @file  M2M_Common.cpp
 @brief ���ļ�ʵ����M2Mģ���һЩ����������������������WMMP��APN�ࡣ
 @author   zl
*/
#include "DoNothing.h"
#include "M2M_WMMP_Connection.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


M2MCommon::M2MCommon()
{
}

M2MCommon::~M2MCommon()
{
}


int M2MCommon::getCSQ(int *rssi, int *ber)
{
	return at_getCSQ(rssi, ber);	
}

int M2MCommon::getModlueInfo(M2Minfo *info)
{
	int rc=0;

	rc = getM2MInfo(info);
	if (rc != 0)
	{
		DBG_PRINT(("rc = %d", rc))
		return NET_M2M_MODULE_ER;
	}
	
	return NET_SUCCESS;	
}

int M2MCommon::setM2MState(int state)
{
	int rc=0;
	INT32 curState=0;
	string strErr("");

	//ֻ�������ݱ�־������ʲôҲ������
	//������ģʽ�л�Ϊwmmp��apnʱ�������initNetDevice������ģ��Ĺ���״̬
	if (CNetDBWork::save_M2M_State(state, strErr) != SQLITE_OK)
	{
		return NET_OPERATOR_DB_ER;
	}
	return NET_SUCCESS;	
}

