/**
 @file  M2M_Common.h
 @brief ���ļ���������M2Mģ���йص������࣬���������WMMP��APN�ࡣ
 @author   zl
*/
#ifndef	__H_NET_M2M_COMMOM_
#define	__H_NET_M2M_COMMOM_


#include "command_at.h"
#include "netConnection.h"


#define M2M_ACT_ON		1
#define M2M_ACT_OFF		0


/**
 @class M2MCommon 
 @brief ����ʵ����һЩM2M�Ļ������������������WMMP��APN�ࡣ
 */
class M2MCommon : public CNetConnection
{
public:
	virtual int initNetDevice(string &strErr)=0;

	int getCSQ(int *rssi, int *ber);

	/*!
	@brief ��ȡM2Mģ����Ϣ��
	@param[out] info M2M��Ϣ�ṹ�塣
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	int getModlueInfo(M2Minfo *info);
	
	/*!
	@brief ����M2Mģ�鼤��״̬��
	@param[in] state 1-���0-��������
	@return NET_SUCCESS - �ɹ������� - ʧ��
	@note ������Ŀǰֻ�������ݿ��־λ������ʲôҲ������
		  ʵ�ʵ�ģ��������initNetDevice����ִ�С�
	*/
	static int setM2MState(int state);

	M2MCommon();
	virtual ~M2MCommon();

};


#endif

