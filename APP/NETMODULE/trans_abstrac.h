/**
 @file  trans_abstrac.h
 @brief ���ļ��������������ݴ��������trans_abstrac�����༰��������ʵ���˾���Ĵ�����̡�
 */
#ifndef	__H_ABSTRAC_TRANS_
#define	__H_ABSTRAC_TRANS_

#include "IncludeMe.h"
#include "netHeaderDef.h"
#include "transfers_base.h"
#include "Sending.h"


/**
 @class trans_abstrac 
 @brief ���ݴ�������ࡣ��������ͬ������Э������ࡣ
 */
class trans_abstrac : public CNetTransfers
{
private:
	 Sending *m_pSending;			/**< ����ͨѶ�Ķ���ָ�� */

public:
	trans_abstrac(Sending *p);
	virtual ~trans_abstrac();

	void SetServerIP(const string IP, const string Port);
	int CheckServerLink(string &strErr);
	
private:
	/*!
	@brief �����շ�����
	@param[in] psBuf �����͵�����
	@param[in] sLen �������ݳ���
	@param[out] prBuf ���յ�����
	@param[in,out] rLen ������ջ����С�����ʵ�ʽ��ճ���
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	virtual int sendData(UINT8 *psBuf, INT32 sLen, UINT8 *prBuf, INT32 *rLen, string &strErr)=0;

	/*!
	@brief �������
	@param[in] psBuf �����͵�����
	@param[in] sLen �������ݳ���
	@param[out] prBuf ���յ�����
	@param[in,out] rLen ������ջ����С�����ʵ�ʽ��ճ���
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	@note ��������ʵ���˴���ʧ�ܺ�������߼�
	*/
	int trans_proc(UINT8 *psBuf, INT32 sLen, UINT8 *prBuf, INT32 *rLen, string &strErr);

protected:
	/*!
	@brief ִ�����ӷ���������
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int connectServer(string &strErr);
	/*!
	@brief ִ�жϿ�����������
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int disConnect();
	/*!
	@brief ִ�з��Ͳ���
	@param[in] psBuf �����͵�����
	@param[in] sLen �������ݳ���
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int send(UINT8 *psBuf, INT32 sLen, string &strErr);
	/*!
	@brief ִ�н��ղ���
	@param[in] rBufSize ���ջ������BUFF
	@param[out] prBuf ���յ�����
	@param[out] rLen ʵ�ʽ��ճ���
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int rev(INT32 rBufSize, UINT8 *prBuf, INT32 *rLen, string &strErr);
	
};





#endif


