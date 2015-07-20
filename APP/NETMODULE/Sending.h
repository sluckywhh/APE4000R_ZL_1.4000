/**
 @file  Sending.h
 @brief ���ļ����������������շ��Ļ��࣬��������Ϊ������շ������ࡣ
 */
#ifndef __H_SENDING_DATA_
#define __H_SENDING_DATA_

#include "IncludeMe.h"
#include "netHeaderDef.h"


/**
 @class Sending 
 @brief ���������շ����࣬���ඨ������������������ӡ����͡��������ݵľ���ӿڡ�
 */
class Sending 
{
protected:
	string m_serverIP;			/**< Ŀ�������IP */
	string m_serverPort;		/**< Ŀ��������˿� */

public:
	Sending();
	virtual ~Sending();

	/*!
	@brief ��ʼ����
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	virtual int init();

	/*!
	@brief ������Ŀ������������ӡ�
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	virtual int connectServer(string &strErr)=0;

	/*!
	@brief �Ͽ���������
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	virtual int disConnect()=0;

	/*!
	@brief ���ݷ��͡�
	@param[in] psBuf �����͵�����
	@param[in] sLen �������ݳ���
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	virtual int send(UINT8 *psBuf, INT32 sLen, string &strErr)=0;

	/*!
	@brief ���ݽ��ա�
	@param[in] rBufSize ���ջ������BUFF
	@param[out] prBuf ���յ�����
	@param[out] rLen ʵ�ʽ��ճ���
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	virtual int rev(INT32 rBufSize, UINT8 *prBuf, INT32 *rLen, string &strErr)=0;

	/*!
	@brief ����Ŀ�������IP��˿ڡ�
	@param[in] IP Ŀ�������IP
	@param[in] Port Ŀ��������˿�
	*/
	virtual void SetServerIP(const string IP, const string Port);

	/*!
	@brief M2Mģ����������
	@param[in] flow �����
	*/
	virtual void setFlow(int flow);

	

};



#endif

