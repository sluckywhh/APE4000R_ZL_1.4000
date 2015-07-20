/**
 @file  M2M_APN_Connection.h
 @brief ���ļ���������M2M-APNģʽ�йصļ��������ࡣ
 @author   zl
*/
#ifndef	__H_NET_M2M_APN_CONNECTION_
#define	__H_NET_M2M_APN_CONNECTION_


#include "M2M_Common.h"


#define		APN_TAG		"0002"


/**
 @class connect_M2M_APN 
 @brief ���ฺ����M2M_APN�������ӡ�
 */
class connect_M2M_APN : public ConnectACT
{
public:
	int connect(string &strErr);

	connect_M2M_APN(CNetConnection *p):ConnectACT(p){};
	virtual ~connect_M2M_APN(){};
};

/**
 @class disconnect_M2M_APN 
 @brief ���ฺ��Ͽ�M2M_APN���硣
 */
class disconnect_M2M_APN : public DisConnectACT
{
public:
	int disConnect();

	disconnect_M2M_APN(CNetConnection *p):DisConnectACT(p){};
	virtual ~disconnect_M2M_APN(){};
};



/**
 *@class M2M_APN_Connection 
 *@brief M2M_APNģʽ�������ࡣ
 
	����ʵ����M2M_APNģʽ����ĸ�����������������������¾���Ĳ�������
	3G������Ͽ�����connect_M2M_APN��disconnect_M2M_APN��		
	ͨ�ý���״̬��ѯ����CommonCheck��
	ͨ��IP��Ϣ��ȡ����CommonGetIPinfo��
 */
class M2M_APN_Connection : public M2MCommon
{
public:
	int initNetDevice(string &strErr);
	
	/*!
	@brief ����APN�Ľ��������롣
	@param[in] Acc �����
	@param[in] Num ����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	int setApn_Acc_Num(string &Acc, string &Num, string &strErr);

	M2M_APN_Connection();
	~M2M_APN_Connection();

private:
	/*!
	@brief ����APN���Žű���
	*/
	void UpdateMobileChat(const INT8 *apnValue, const INT8 *apnNumber, UINT8 nameFlag);
	
};


#endif

