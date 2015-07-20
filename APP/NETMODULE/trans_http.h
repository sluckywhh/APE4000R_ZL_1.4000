/**
 @file  trans_http.h
 @brief ���ļ�������httpЭ�鴫���ࡣ
 */
#ifndef	__H_TRANS_HTTP_
#define	__H_TRANS_HTTP_

#include "IncludeMe.h"
#include "netHeaderDef.h"
#include "trans_abstrac.h"

#define	HTTP_HEAD_LEN_MAX		1024

#define	HTTP_TRANSFER_CHUNKED		1
#define	HTTP_TRANSFER_CONLENGTH		0


#define	HTTP_USE_POST_KEYWORD		0
#define	HTTP_USE_GET_KEYWORD		1



/**
 @class trans_http 
 @brief ʵ��httpЭ��Ĵ��䡣
 */
class trans_http : public trans_abstrac
{
private:
	char *m_pHttpHeadBuff;
	int m_transferType;
	int m_sendMode;

public:
	trans_http(Sending *p);
	virtual ~trans_http();

	/*!
	@brief ����HTTP���ͷ�ʽ��POST��GET
	@param[in] mode HTTP_USE_POST_KEYWORD����HTTP_USE_GET_KEYWORD
	*/
	void SetSendMode(int mode);

private:
	
	int sendData(UINT8 *psBuf, INT32 sLen, UINT8 *prBuf, INT32 *rLen, string &strErr);


	/*!
	@brief ���ղ�����http��ͷ
	@param[out] contentLen ����Content-Lengthֵ������HTTP�����ݳ��ȣ�chunkedģʽ���Ϊ0��
	@return   ���յ���ͷ���ֽ��� 
	*/
	int ReadHttpHead(INT32 *contentLen);

	/*!
	@brief ����chunked��ʽ�µ�HTTP��
	@param[out] revBuf ������
	@param[out] recContent_len ���ճ���
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int RecvHttp_chunked(UINT8 *revBuf, INT32 *recContent_len, string &strErr);


	/*!
	@brief ����http��ͷ
	@param[in] msg POST��GET��ʽ
	@param[in] file http·��
	@param[in] serverIP ������IP
	@param[in] serverPort �������˿�
	@param[in] con_len HTTP�����ݳ���
	*/
	void sethttphead(char *msg,const char* file,const char * serverIP, const char *serverPort, UINT32 con_len);

	/*!
	@brief ��ȡ��ͷ��ĳ�ֶ�ֵ
	@param[in] sheader ��ͷBUFFָ��
	@param[out] sKeyWord �ֶ���
	@return   >=0�ֶ�ֵ	; <0�޸��ֶ�     ������ֵ�Ķ����ƺ����������⣡��
	*/
	int getValue(char *sheader,char *sKeyWord);
	/*!
	@brief �жϰ�ͷ��ĳ�ֶ�ֵ�Ƿ����
	@param[in] sheader ��ͷBUFFָ��
	@param[out] sKeyWord �ֶ���
	@return   0-������	; 1-����     
	*/
	int isExist(char *sheader,char *sKeyWord);

	/*!
	@brief ����HTTP״ֵ̬
	@param[in] sheader ��ͷBUFFָ��
	@return       ״ֵ̬
	*/
	int getHttpState(char *sheader);
	/*!
	@brief ����content-lengthֵ
	@param[in] sheader ��ͷBUFFָ��
	@return   ontent-lengthֵ
	*/
	int getconlength(char* sheader);
	/*!
	@brief ����resultTypeֵ
	@param[in] sheader ��ͷBUFFָ��
	@return   resultTypeֵ
	*/
	int getserverstate(char * sheader);
	/*!
	@brief �����Ƿ�Ϊchunked״̬
	@param[in] sheader ��ͷBUFFָ��
	@return   HTTP_TRANSFER_CHUNKED��HTTP_TRANSFER_CONLENGTH
	*/
	int getTransferState(char* sheader);

};





#endif


