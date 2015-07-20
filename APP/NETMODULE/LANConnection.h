/**
 @file  LANConnection.h
 @brief ���ļ��������������ģʽ�йصļ��������ࡣ
 @author   zl
*/
#ifndef	__H_NET_LAN_CONNECTION_
#define	__H_NET_LAN_CONNECTION_


#include "netConnection.h"



/**
 @class LANCheck 
 @brief ���ฺ���ѯ�������״̬��������ר�ã���
 @warning �ֹ�����IP������£�Ŀǰ�޷���ѯ����״̬��ֱ�ӷ��ɹ���
 */
class LANCheck : public CheckConnectionACT
{
public:
	int check();

	LANCheck(CNetConnection *p):CheckConnectionACT(p){};
	virtual ~LANCheck(){};
};



/**
 *@class LANConnection 
 *@brief ������ģʽ�������ࡣ
 
	����ʵ���˾�����ģʽ����ĸ�����������������������¾���Ĳ�������
	�յ�������Ͽ�����connectNothing��disconnectNothing���������κ��£���		
	����������״̬��ѯ����LANCheck��
	ͨ��IP��Ϣ��ȡ����CommonGetIPinfo��
 */
class LANConnection : public CNetConnection
{
public:
	INT32 m_dhcpMode;

	int initNetDevice(string &strErr);

	/*!
	@brief ����DHCPģʽ��	
	@param[in] dhcpMode LAN_DHCP_ON��LAN_DHCP_OFF
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	int setDhcpMode(INT32 dhcpMode, string &strErr);

	/*!
	@brief �ֹ����õ�ǰIP״̬��	
	@param[in] info IP��Ϣ�ṹ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	int setIPinfo(IPinfo *info, string &strErr);

	LANConnection();
	~LANConnection();

};

#endif

