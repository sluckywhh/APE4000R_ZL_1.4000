/**
 @file  trans_abstrac.cpp
 @brief ���ļ�ʵ�����������ݴ��������trans_abstrac��
 */
#include "trans_abstrac.h"
#include "commonFunc.h"
#include "netConnection.h"
#include "netManager.h"
#ifdef APE_GUI
#include "CaProgressBar.h"
#endif

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"



trans_abstrac::trans_abstrac(Sending *p)
{
	DBG_PRINT(("trans_abstrac()"))
	m_pSending = p;
}

trans_abstrac::~trans_abstrac()
{
	DBG_PRINT(("~trans_abstrac()"))
	if (m_pSending != NULL)
	{
		delete m_pSending;
		m_pSending = NULL;
	}
}

int trans_abstrac::trans_proc(UINT8 *psBuf, INT32 sLen, UINT8 *prBuf, INT32 *rLen, string &strErr)
{
	int ret=0;
	UINT8 vpn_reConnect_flag=0;
	UINT8 vpn_reConnect_times=0;
	INT32 rec_len=0;
	CNetConnection *pL2 = g_netManager->GetConnectionHandleL2();
	PROBAR_DEF();

#if (_DBG_PRINT_TRANSDATA==1)
	if( sLen > 0 )
	{
		DBG_PRINT(("sLen = %d", sLen));
		printf("-------------------sendBuf----------------------\n");
		printf("%s", psBuf);
		printf("\n------------------sendBuf_end-------------------\n");
	}
#endif
	
	vpn_reConnect_flag = 0;
	vpn_reConnect_times = 0;
	while(1)
	{		
		if (vpn_reConnect_flag != 0)		//�Ƿ����VPN������	
		{
			if (vpn_reConnect_times++ >= 3)
			{			
				strErr = "���Զ��,�����Դ���ʧ��";
				return NET_TRANS_FAIL;
			}
			
			PROBAR_SHOW("�����ӷ�������,���Ժ�...");
			DBG_PRINT(("***�Ͽ�VPN����***"));
			disConnect();
			
			DBG_PRINT(("***����VPN����***"));
			ret = pL2->performConnect(strErr);
			if(ret != NET_SUCCESS)
			{
				DBG_PRINT(("strErr= %s",strErr.c_str()));
				continue;
			}
			else
			{
		//		vpn_reConnect_times = 0;
				vpn_reConnect_flag = 0;
				strErr = "";
			}
		}

		
		DBG_PRINT(("������������Ĵ���ͨ��...."));
		PROBAR_SHOW("���������ӽ�����,���Ժ�...");
		
		if((ret=connectServer(strErr)) != NET_SUCCESS)
		{	
			if (pL2->m_connectionMode==NET_VPN && pL2->m_dialState==HAVE_DIALED)
			{
				DBG_PRINT(("��������������ʧ�ܣ�׼������..."));
				vpn_reConnect_flag = 1;
				//vpn_reConnect_times = 4;
				continue;
			}
			return ret;
		}
		CommonSleep(500);
		

		DBG_PRINT(("��ʼ���ݽ���...."));
		PROBAR_SHOW("ҵ�����ݽ�����...");
		
		ret = sendData(m_pSendBuff, sLen, prBuf, &rec_len, strErr);
		if (ret != NET_SUCCESS)
		{
			DBG_PRINT(("SendData FAILURE. "));
			disConnect();

			//vpnģʽʱҪ����������
			if (pL2->m_connectionMode==NET_VPN && pL2->m_dialState==HAVE_DIALED)
			{
				DBG_PRINT(("׼������..."));
				vpn_reConnect_flag = 1;
				//vpn_reConnect_times = 4;
				continue;
			}

			return ret;
		}

		DBG_PRINT(("���ݽ���������rec_len=%d", rec_len));
		disConnect();		

#if (_DBG_PRINT_TRANSDATA==1)
		if( rec_len > 0 )
		{
			printf("-------------------revBuf----------------------\n");
			printf("%s", prBuf);
			printf("\n------------------revBuf_end-------------------\n");
		}		
#endif
		
		break;
	}

	*rLen = rec_len;
	DBG_PRINT(("TransToSever End"));
	return NET_SUCCESS;
}

void trans_abstrac::SetServerIP(const string IP, const string Port)
{
	m_serverIP.assign(IP);
	m_serverPort.assign(Port);
	m_pSending->SetServerIP(IP, Port);
}

int trans_abstrac::CheckServerLink(string &strErr)
{
	int ret=0;
	ret = connectServer(strErr);
	disConnect();
	return ret;
}


int trans_abstrac::connectServer(string &strErr) 
{
	return m_pSending->connectServer(strErr);
}
int trans_abstrac::disConnect() 
{
	return m_pSending->disConnect();
}
int trans_abstrac::send(UINT8 *psBuf, INT32 sLen, string &strErr) 
{
	return m_pSending->send(psBuf,sLen,strErr);
}
int trans_abstrac::rev(INT32 rBufSize, UINT8 *prBuf, INT32 *rLen, string &strErr) 
{
	return m_pSending->rev(rBufSize, prBuf,rLen,strErr);
}


