/**
 @file  netManager.h
 @brief ���ļ�����������ģ���е����������CNetManager��
 */

#ifndef	__H_NET_MANAGER_
#define	__H_NET_MANAGER_


#include "IncludeMe.h"
#include "netHeaderDef.h"
#include "netConnection.h"
#include "transfers_base.h"

extern unsigned char g_netSendBuf[];
extern unsigned char g_netRevBuf[];


/**
 @class CNetManager 
 @brief ���������

  ���ڹ�����������������ͨѶ������ģ��Ĺ��졢���������õȹ��̡�
  ��������һ��ȫ���Ե�ʵ�����
 */
class CNetManager
{
private:
	CNetConnection *m_pConnectionL1;		/**< ��һ���������ӵ�ָ��		*/
	CNetConnection *m_pConnectionL2;		/**< �ڶ����������ӵ�ָ��					*/

	TransMode m_transMode;					/**< ���䷽ʽ					*/

	string m_defServerIP;					/**< Ĭ�ϵķ�����IP				*/
	string m_defServerPort;					/**< Ĭ�ϵķ�����PORT			*/
	string m_defServerFile;					/**< Ĭ�ϵ�HTTP·��				*/

	UINT8 *m_pDefSendBuff;					/**< Ĭ�ϵķ���BUFָ���볤��	*/
	UINT32 m_defSendBuffLen;				
	UINT8 *m_pDefRevBuff;					/**< Ĭ�ϵĽ���BUFָ���볤��	*/
	UINT32 m_defRevBuffLen;

	static CNetManager *m_pNetManager;		/**< ָ����������ָ��			*/
	
public:
	/*!
	@brief �����������ӷ�ʽ����һ�㣩
	@param[in] mode ���ӷ�ʽ
	@param[out] handle ������������Ӿ��
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int SetConnectionMode(int mode, CNetConnection **handle, string &strErr);
	/*!
	@brief �����������ӷ�ʽ���ڶ��㣩
	@param[in] mode ���ӷ�ʽ
	@param[out] handle ������������Ӷ���ָ��
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int SetConnectionModeL2(int mode, CNetConnection **handle, string &strErr);


	/*!
	@brief ��ȡ��ǰ���������ӷ�ʽ
	@return ���ӷ�ʽ 
	*/
	int GetConnectionMode();
	/*!
	@brief ��ȡ��ǰ���������ӷ�ʽ���ڶ��㣩
	@return ���ӷ�ʽ 
	*/
	int GetConnectionModeL2();

	/*!
	@brief ��ȡ��ǰ�������Ӷ����ָ��
	@return ���ӷ�ʽ 
	*/
	CNetConnection* GetConnectionHandle();
	/*!
	@brief ��ȡ��ǰ�������Ӷ��󣨵ڶ��㣩��ָ��
	@return ���ӷ�ʽ 
	*/
	CNetConnection* GetConnectionHandleL2();
		

	/*!
	@brief ��ѯ��ǰ������״̬���������Ӷ����м�飩
	@return CONNECT_ON_L2 - �ѽ����ڶ������� 
			CONNECT_ON_L1 - �ѽ�����һ������  
			CONNECT_OFF   - δ��������
	@mark ������������ʵ��ʱ����Ϊû�н�������
	*/
	int checkConnect();

	
	/*!
	@brief ��ȡ��ǰ��IP��Ϣ������ڶ������ӽ���������ڶ����IP��
	@param[out] info �����IP��Ϣ
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int getIPinfo(IPinfo *info, string &strErr);


	/*!
	@brief ����ģ��ĳ�ʼ������������ʱ���á�
		   �������ݿ��¼��ʼ��Ĭ�ϵ����ӷ�ʽ��������IP�ȡ�
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int init(string &strErr);
	
	/*!
	@brief �����Զ��������Ӻ�����
		   �������ݿ�ļ�¼�����Զ��������ӡ�
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int autoDialProc(string &strErr);

	

	/*!
	@brief ��ȡ���ݴ�������ָ�룬���������ʹ��Ĭ��ֵ��
	@return   ��������ָ��	NULL-ʧ�� 
	*/
	CNetTransfers* GetTransHandle();
	/*!
	@brief ��ȡ���ݴ�������ָ�룬������������Ͳ�����
	@param[in] module ������ģ��ѡ��
	@param[in] appProtocal Ӧ�ò�Э������
	@param[in] transMethod ���䷽ʽ ����ȡ����
	@param[in] dataKeepType �������ݵ��ݴ淽ʽ���ļ���BUFF��
	@return   ��������ָ��	NULL-ʧ�� 
	*/
	CNetTransfers* GetTransHandle(int module,int appProtocal,int transMethod,int dataKeepType);
	
	/*!
	@brief �ͷ�һ���������ʵ�塣
	@param[in] ��������ָ��
	@return    
	*/
	void ReleaseTransHandle(CNetTransfers *p);
	

	/*!
	@brief ����Ĭ�ϵĴ��������
	*/
	void setTransMode(int module,int appProtocal,int transMethod,int dataKeepType);
	/*!
	@brief ʹ��netHeaderDef.h�ļ��еĺ궨����ΪĬ�ϵĴ������
	*/
	void defTransMode();


	/*!
	@brief ����Ĭ�ϵĴ��������IP��port��
	*/
	void setDefServerIP(const string ip, const string port);
	/*!
	@brief ����Ĭ�ϵĴ���HTTP·����
	*/
	void setDefServerFile(const string file);
	/*!
	@brief ����Ĭ�ϵķ��ͻ��档
	*/
	void SetDefSendBuff(UINT8 *pBuf, INT32 maxLen);
	/*!
	@brief ����Ĭ�ϵĽ��ջ��档
	*/
	void SetDefRevBuff(UINT8 *pBuf, INT32 maxLen);


	/*!
	@brief �ϻ�����
	*/
	void NetTransMutexLock();
	/*!
	@brief �⻥����
	*/
	void NetTransMutexUnlock();


	/*!
	@brief ��ȡ����Ψһ�����ʵ��
	*/
	static CNetManager* GetInstance(void);


private:

	/*!
	@brief ����һ���������ӵĶ���ʵ��
	@param[in] mode ���ӷ�ʽ
	@param[out] handle ������������Ӷ���ָ��
	@return   NET_SUCCESS-�ɹ���	����ֵ-ʧ�� 
	*/
	int buildConnectionInstance(int mode, CNetConnection **handle, string &strErr);


	/*!
	@brief ����һ�����ݴ���Ķ���ʵ��
	@param[out] pNetTrans ��������ݴ������ָ��
	@param[in] transMode ���䷽ʽ�Ĳ���
	*/
	int buildTransInstance(CNetTransfers **pNetTrans, TransMode *transMode);


	
	CNetManager();
	~CNetManager();


};


extern CNetManager *g_netManager;


#endif

