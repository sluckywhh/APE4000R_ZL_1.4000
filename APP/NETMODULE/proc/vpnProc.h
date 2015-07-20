#ifndef __VPN_CONNECT_
#define __VPN_CONNECT_

#include <stdio.h>
#include "comdatatype.h"

#ifdef __cplusplus
extern "C"
{
#endif


//VPN����Э���йصĶ���
#define VPN_ENCRYPT_PAP			1
#define VPN_ENCRYPT_CHAP		2
#define VPN_ENCRYPT_PROTOCOL	VPN_ENCRYPT_PAP

#if (VPN_ENCRYPT_PROTOCOL==VPN_ENCRYPT_PAP)
#define	VPN_FILE_SECRET			"/etc/ppp/pap-secrets"
#endif
#if (VPN_ENCRYPT_PROTOCOL==VPN_ENCRYPT_CHAP)
#define	VPN_FILE_SECRET			"/etc/ppp/chap-secrets"
#endif

#define	VPN_FILE_XL2TPD			"/etc/xl2tpd/xl2tpd.conf"


//VPN�������Ͷ���
#define VPN_SUCCESS								0
#define VPN_PARA_ER								-1
#define VPN_CHANGE_XL2TP_ER						-2
#define VPN_CHANGE_SERCRET_ER					-3
#define VPN_READ_FILE_ER						-5
#define VPN_DISCONNECT_ER						-6
#define VPN_RUN_XL2TPD_ER						-7
#define VPN_READ_ROUTE_ER						-8
#define VPN_RUN_L2TP_ER							-9
#define VPN_DISCONNECT					    	-10

#define VPN_FILE_EOF							FILE_EOF





typedef struct{
	UINT8 Iface[8];
	UINT8 Destination[4];
	UINT8 Gateway[4];
	INT32 Flags;
}RouteInfo;





/**
 * brief ��s_VPN_IP��s_VPN_username������Э�����Ϣд��VPN���Žű��ļ�
 * @param void
 * @return �ɹ���VPN_SUCCESS��ʧ�ܣ���Ӧ������
 */
int change_xl2tp_script();

/**
 * brief ��������������s_VPN_IP��s_VPN_username��s_VPN_passwd
 * @param char *ip��VPN��IP��ַ��
 * @param char *userName��VPN���û�����
 * @param char *passwd��VPN�����룻
 * @return �ɹ���VPN_SUCCESS��ʧ�ܣ���Ӧ������
 */
int setLocalVar(const char *ip, const char *userName, const char* passwd); 

/**
 * brief ��VPN����д��ű��ļ�
 * @param char *ip��VPN��IP��ַ��
 * @param char *userName��VPN���û�����
 * @param char *passwd��VPN�����룻
 * @return �ɹ���VPN_SUCCESS��ʧ�ܣ���Ӧ������
 */
int setVPN_para(const char *ip, const char *userName, const char* passwd);


//////////////////////////////////////////////////////////////////////////
// ����Ϊ�ṩ����һ����õĽӿ�
//////////////////////////////////////////////////////////////////////////

/**
 * brief ��ȡ��ǰ·�ɱ��е���Ϣ������s_ori_gw_IP��s_ori_host_IP��s_ori_host_type��������
 * @param void
 * @return �ɹ���VPN_SUCCESS��ʧ�ܣ���Ӧ������
 */
int VPN_getOri_route();

/**
 * brief ɾ����ǰ·����Ϣ������s_ori_gw_IP��s_ori_host_IP��s_ori_host_type�е�·����Ϣд��·�ɱ�
 * @param void
 * @return �ɹ���VPN_SUCCESS��ʧ�ܣ���Ӧ������
 */
int VPN_setOri_route();

/**
 * brief ɾ����ǰ·����Ϣ������s_VPN_IP�д�ŵ�·����Ϣд��·�ɱ�
 * @param void
 * @return �ɹ���VPN_SUCCESS��ʧ�ܣ���Ӧ������
 */
int VPN_setVPN_route(int netmode);

/**
 * brief ����VPN����
 * @param char *ip��VPN��IP��ַ��
 * @param char *userName��VPN���û�����
 * @param char *passwd��VPN�����룻
 * @return �ɹ���VPN_SUCCESS��ʧ�ܣ���Ӧ������
 */
int VPN_connent(const char *ip, const char *userName, const char* passwd);

/**
 * brief �Ͽ�VPN����
 * @return �ɹ���VPN_SUCCESS��ʧ�ܣ���Ӧ������
 */
int VPN_close(int netmode);



#ifdef __cplusplus
}
#endif

#endif

