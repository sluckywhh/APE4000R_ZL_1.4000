/**
 @file  SendByWmmp.h
 @brief ���ļ�������WMMP��ʽ�����������շ��ࡣ
 */
#ifndef __H_SEND_BY_WMMP_
#define __H_SEND_BY_WMMP_

#include "IncludeMe.h"
#include "netHeaderDef.h"
#include "Sending.h"


/**
 @class SendByWmmp 
 @brief WMMP���������շ��ࡣ
 */
class SendByWmmp : public Sending 
{
private:
	int m_flow;					/**< ����� */

	UINT8 *m_pRevTmpBuf;		/**< WMMPר�ý��ջ���ָ�� */
	int m_revBufHead;			/**< ���ջ�������ͷλ�� */
	int m_revBufRear;			/**< ���ջ�������βλ�� */

public:
	SendByWmmp();
	virtual ~SendByWmmp();

	int connectServer(string &strErr);
	int disConnect();
	int send(UINT8 *psBuf, INT32 sLen, string &strErr);
	int rev(INT32 rBufSize, UINT8 *prBuf, INT32 *rLen, string &strErr);

	void SetServerIP(const string IP, const string Port);
	void setFlow(int flow);

private:
	/*!
	@brief ���ص�ǰ����BUFF�����ݳ��ȡ�
	@return   BUFF�����ݳ���
	*/
	int curBuffLength();

	/*!
	@brief �ӻ���BUFF��ȡ���ݡ�
	@param[out] prBuf ȡ��������
	@param[in] conlen ȡ�����ݳ���
	*/
	void getDataFromBuff(UINT8 *prBuf, INT32 conlen);

};



#endif

