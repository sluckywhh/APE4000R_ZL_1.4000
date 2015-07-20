/**
 @file  netHeaderDef.h
 @brief ���ļ���������ģ����������ɺ궨����������͡�
 */
#ifndef	__H_NET_MACRO_DEF_
#define	__H_NET_MACRO_DEF_




//////////////////////////////////////////////////////////////////////////
//�������ӵ���ض���
//////////////////////////////////////////////////////////////////////////

/** @brief ö�����ͣ�����ģʽ */
enum ENUM_NET_MODE
{
	NET_NONE = 0,		/**< ������ģʽ		*/
	NET_LAN = 1,		/**< ������		*/
	NET_ADSL,			/**< ADSL		*/
	NET_3G,				/**< 3G			*/
	NET_M2M_WMMP,		/**< M2M_Wmmp		*/
	NET_M2M_APN,		/**< M2M_APN		*/
	NET_VPN = 10,		/**< VPN���β���		*/
};

/**
 *@struct _IPinfo 
 *@brief ����IP��Ϣ����
 */
typedef struct _IPinfo{
    char IP[16];
    char Mask[16];
    char GeteWay[16];
    char DNS[16];
}IPinfo;



//�������Ͷ���
#define	NET_SUCCESS							0
#define	NET_CONNECT_FAIL					-1
#define	NET_INIT_FAIL						-2
#define	NET_MODE_ER							-3
#define	NET_OPERATOR_FILE_ER				-4
#define	NET_OPERATOR_DB_ER					-5
#define	NET_INPUT_IP_ER						-6
#define	NET_M2M_MODULE_ER					-7
#define	NET_NOT_SUPPORT_ER					-8
#define	NET_POINT_NULL_ER					-9
#define	NET_BUFF_OVERFLOW_ER				-10
#define	NET_TRANS_FAIL						-11
#define	NET_SOCKET_FAIL						-12
#define	NET_WMMP_FAIL						-13
#define	NET_AT_CMD_FAIL						-14
#define	NET_CONDITION_ER					-15
#define	NET_OTHER_ER						-99



//CNetManager��checkConnect�ķ��ؽ������
#define	CONNECT_ON_L2						2				//�ڶ�������������
#define	CONNECT_ON_L1						1				//��һ�����������ӣ��ڶ���δ���ӻ�δ����
#define	CONNECT_OFF							0				//����δ����


//performCheck()�ķ���ֵ����
#define	CHECK_OK							0				//��ѯ���������
#define	CHECK_NOT							1				//��ѯ�����δ����
#define	CHECK_OFF							-1				//��ѯ�������������


//�Ƿ�ִ���˽�������
#define HAVE_DIALED				1
#define NOT_DIALED				0



//LANģʽ��ض���
#define	LAN_DHCP_ON				1
#define	LAN_DHCP_OFF			0



//M2Mģʽ��ض���
#define SIMCOM                  1   /**< 1: ֧���µ�SIMCOM��M2M 0: ֧�־ɵ�WAVECOM��M2M*/





//////////////////////////////////////////////////////////////////////////
//���ݴ������ض���
//////////////////////////////////////////////////////////////////////////

//��ģ��
#define	TRANS_BY_TRANSPROC				1
#define	TRANS_BY_CURL					2

//Ӧ�ò�Э��
#define	APP_LAYER_HTTP					1
#define	APP_LAYER_NONE					2

//�����������ڵ���ʽ
#define	DATA_IN_BUFF					0
#define	DATA_IN_FILE					1





//////////////////////////////////////////////////////////////////////////
//Ϊ���ò�����Ĭ��ֵ��
//���netModuleConfig.h�ļ���û�ж�ĳ���������壬�����ʱ��ʹ��Ĭ��ֵ��
//��ֲʱ��Ҫ�޸��ⲿ�ֶ��塣
//////////////////////////////////////////////////////////////////////////
#include "netModuleConfig.h"


//���뷽ʽ 
#ifndef _CONFIG_LAN_MODULE
#define	_CONFIG_LAN_MODULE					1
#endif
#ifndef _CONFIG_ADSL_MODULE
#define	_CONFIG_ADSL_MODULE					1
#endif
#ifndef _CONFIG_3G_MODULE
#define	_CONFIG_3G_MODULE					1
#endif
#ifndef _CONFIG_M2M_MODULE
#define	_CONFIG_M2M_MODULE					0
#endif
#ifndef _CONFIG_VPN_MODULE
#define	_CONFIG_VPN_MODULE					0
#endif

//���䷽ʽ
#ifndef _TRANS_MODULE_CURL
#define	_TRANS_MODULE_CURL					0
#endif

//���߳�֧��
#ifndef _TRANS_THREAD_SUPPORT
#define	_TRANS_THREAD_SUPPORT				1
#endif

//Ĭ�ϴ��䷽ʽ
#ifndef TRANS_MODULE_DEF
#define	TRANS_MODULE_DEF						TRANS_BY_TRANSPROC
#endif
#ifndef TRANS_APP_LAYER_DEF
#define	TRANS_APP_LAYER_DEF						APP_LAYER_HTTP
#endif
#ifndef TRANS_DATA_TYPE_DEF
#define	TRANS_DATA_TYPE_DEF						DATA_IN_BUFF
#endif

//HTTPĬ��·��
#ifndef SERVER_FILE_DEF
#define SERVER_FILE_DEF							"/Servlet"
#endif
#ifndef SERVER_TIME
#define SERVER_TIME								"/TimeServlet"
#endif

//WMMP ��һЩĬ�ϲ���
#ifndef WMMP_FLOW_DEFAULT
#define WMMP_FLOW_DEFAULT						2
#endif
#ifndef WMMP_TRANS_PACK_LEN
#define WMMP_TRANS_PACK_LEN						2048
#endif

//3G ��һЩĬ�ϲ���
#ifndef _3G_AT_BUFF_LEN
#define _3G_AT_BUFF_LEN							512 
#endif

//SOCKET��һЩĬ�ϲ���
#ifndef MAX_SOCKET_CONNECT_RETRY
#define MAX_SOCKET_CONNECT_RETRY				7			//����SOCKET����ʧ��ʱ��������Դ���			
#endif
#ifndef MAX_SOCKET_TRANS_RETRY
#define MAX_SOCKET_TRANS_RETRY					8			//SOCKETͨѶ����ʱ��������Դ���		
#endif
#ifndef SOCKET_SEND_PACKLEN
#define SOCKET_SEND_PACKLEN						2048		//ÿ��SOCKET���͵�������
#endif
#ifndef SOCKET_RECV_PACKLEN
#define SOCKET_RECV_PACKLEN						1024		//ÿ��SOCKET���յ�������
#endif

//���ݷ���������Ƿ���һ��������	1-���û��棻0-�����û�����
#ifndef SINGLE_TRANSBUFF_MODE
#define SINGLE_TRANSBUFF_MODE					0
#endif

//Ĭ��ͨѶ�����С
#ifndef DEF_SENDBUFF_LEN
#define DEF_SENDBUFF_LEN						(1024*20)
#endif
#ifndef DEF_RECVBUFF_LEN
#define DEF_RECVBUFF_LEN						(1024*20)
#endif

//Ĭ�����ݴ���ʱ����ʱ�ļ�
#ifndef DEF_REQ_FILE
#define	DEF_REQ_FILE						"XmlReqFile.xml"
#endif
#ifndef DEF_RSP_FILE
#define	DEF_RSP_FILE						"XmlRspFile.xml"
#endif

//�����Ӳ��ԡ����ܵ�ִ�з�ʽ	1-SOCKET��ʽ	2-APP��ʽ������ݾ���Ӧ���޸�NetManageMenu.cpp�д��룩
#ifndef TEST_CONNECT_TYPE
#define TEST_CONNECT_TYPE						1			
#endif

//���ݴ����е�LOG����
#ifndef _DBG_PRINT_TRANSDATA
#define	_DBG_PRINT_TRANSDATA					0
#endif






//////////////////////////////////////////////////////////////////////////
//�汾�����Զ���
//////////////////////////////////////////////////////////////////////////
//#define	_DEBUG_VERSION			


//ProgressBar����
#ifdef APE_GUI
#define	PROBAR_DEF()			CaProgressBar info("")
#define	PROBAR_SHOW(x)			{info.SetText(x);info.Show();}

#else
#define	PROBAR_DEF()
#define	PROBAR_SHOW(x)

#endif


//��ʱ
#ifdef _DEBUG_VERSION
#define	POWOFF_ENABLE()
#define	POWOFF_DISABLE()
#define	MASK_ALARM_SIGNAL()
#define	UN_MASK_ALARM_SIGNAL()
#endif





#endif

