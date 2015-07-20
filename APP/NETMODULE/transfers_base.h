/**
 @file  transfers_base.h
 @brief ���ļ��������������ݴ������CNetTransfers��
 */

#ifndef	__H_NET_TRANSFERS_
#define	__H_NET_TRANSFERS_


#include "IncludeMe.h"
#include "netHeaderDef.h"


/**
 @struct TransMode 
 @brief �����˼������ݴ����еĲ�����
 */
typedef struct{
	int module;				/**< ����ģ��ѡ�� */
	int appProtocal;		/**< Ӧ�ò�Э�� */
//	int transMethod;		//���䷽��ѡ�� ����ȡ�� 140528��
	int dataKeepType;		/**< �����ݴ淽ʽ */
}TransMode;



/**
 @class CNetTransfers 
 @brief ���ݴ������
 
  ���������ݴ�������ӿڡ��ṩ�˷��������á��������õȺ�����
 */
class CNetTransfers
{
private:
	string m_sendFileName;		/**< DATA_IN_FILE����µ����ݷ�����ʱ�ļ� */
	string m_revFileName;		/**< DATA_IN_FILE����µ����ݽ�����ʱ�ļ� */

	INT32 m_dataKeepType;		/**< �������ݵ��ݴ淽ʽ��DATA_IN_BUFF��DATA_IN_FILE */

protected:
	UINT8 *m_pSendBuff;			/**< ���ݷ��ͻ���ָ�� */
	UINT32 m_sendBuffLen;		/**< ���ݷ��ͻ����С */
	UINT8 *m_pRevBuff;			/**< ���ݽ��ջ���ָ�� */
	UINT32 m_revBuffLen;		/**< ���ݷ��ͻ����С */

public:
	string m_serverIP;			/**< ������IP */
	string m_serverPort;		/**< �������˿� */
	string m_serverFile;		/**< ������·�� */


public:
	CNetTransfers();
	virtual ~CNetTransfers();

	/*!
	@brief �������ݴ���������������ϲ���á�
	@param[in] sLen ���ͳ���
	@param[out] rLen ���ճ���
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int TransToSever(INT32 sLen, INT32 *rLen, string &strErr);

	/*!
	@brief ���÷����IP\PORT
	@param[in] IP �����IP
	@param[in] Port ����˶˿ں�
	*/
	virtual void SetServerIP(const string IP, const string Port)=0;

	/*!
	@brief ���÷����HTTP·��
	*/
	void SetServerFile(const string file);

	/*!
	@brief ���÷����û���
	*/
	void SetSendBuff(UINT8 *pBuf, INT32 maxLen);
	/*!
	@brief ���ý����û���
	*/
	void SetRevBuff(UINT8 *pBuf, INT32 maxLen);

	/*!
	@brief ��÷��ͻ���ָ���볤��
	*/
	UINT8* GetSendBuff(INT32 *bufLen);

	/*!
	@brief ��ý��ջ���ָ���볤��
	*/
	UINT8* GetRevBuff(INT32 *bufLen);

	/*!
	@brief ���ô������ݵ��ݴ淽ʽ
	@param[in] type-���ͣ�DATA_IN_BUFF-�����ݴ���BUFF��DATA_IN_FILE-�����ݴ����ļ�
	*/
	void SetDataKeepType(INT32 type);

	/*!
	@brief ����������֮������ӡ���SOCKET��ʽ��ֻ���Խ���SOCKET��
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	virtual int CheckServerLink(string &strErr)=0;


private:
	/*!
	@brief ���ݲ�ͬ�ݴ淽ʽ���Ҫ���͵�����
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int getSendData(INT32 *sLen);
	/*!
	@brief ���ݲ�ͬ�ݴ淽ʽд����յ�����
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int putRevData(INT32 len);
	
	/*!
	@brief �������
	@param[in] psBuf �����͵�����
	@param[in] sLen �������ݳ���
	@param[out] prBuf ���յ�����
	@param[in,out] rLen ������ջ����С�����ʵ�ʽ��ճ���
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	virtual int trans_proc(UINT8 *psBuf, INT32 sLen, UINT8 *prBuf, INT32 *rLen, string &strErr)=0;
	
};

#endif

