/**
 @file  netdbWork.h
 @brief ���ļ�����������ģ���е����ݿ������CNetDBWork��
 */

#ifndef	__H_NET_DATABASE_WORK_
#define	__H_NET_DATABASE_WORK_


#include "IncludeMe.h"
#include "sqlite3.h"
#include "netSysArgDef.h"
#include "netConnection.h"



/**
 *@class CNetDBWork 
 *@brief ���ݿ���ʽӿ��ࡣ

  ������������ݿ���ʽӿ�ģ������ٴη�װ��
  ���ϲ�������ݿ�����Ĵ�������Ҳ�𵽸�������ģ�������ݿ�ģ������á�
  �����Ŀǰ��ȫ����Ա������Ϊ��̬�����������ݳ�Ա��
 */
class CNetDBWork
{
public:	

	/*!
	@brief �洢��ǰ����ģʽ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveNetMode(INT32 mode, string &strErr);
	/*!
	@brief ��ȡ��ǰ����ģʽ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadNetMode(INT32 *mode, string &strErr);
	
	/*!
	@brief �洢�ڶ�������ģʽ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveNetModeL2(INT32 mode, string &strErr);
	/*!
	@brief ��ȡ�ڶ�������ģʽ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadNetModeL2(INT32 *mode, string &strErr);

	/*!
	@brief �洢�Զ����ŷ�ʽ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveAutoDialType(INT32 type, string &strErr);
	/*!
	@brief ��ȡ�Զ����ŷ�ʽ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadAutoDialType(INT32 *type, string &strErr);

	/*!
	@brief �洢DHCPģʽ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveDHCPMode(INT32 dhcpmode, string &strErr);
	/*!
	@brief ��ȡDHCPģʽ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadDHCPMode(INT32 *dhcpmode, string &strErr);

	/*!
	@brief �洢IP��Ϣ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveIPinfo(IPinfo *info, string &strErr);
	/*!
	@brief ��ȡIP��Ϣ��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadIPinfo(IPinfo *info, string &strErr);

	/*!
	@brief �洢ADSL�û��������롣
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveADSLUserNamePwd(string &name, string &pwd, string &strErr);
	/*!
	@brief ��ȡADSL�û��������롣
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadADSLUserNamePwd(string &name, string &pwd, string &strErr);

	/*!
	@brief �洢3G�û��������롣
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 save3gUserNamePwd(string &name, string &pwd, string &strErr);
	/*!
	@brief ��ȡ3G�û��������롣
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 load3gUserNamePwd(string &name, string &pwd, string &strErr);
	
	/*!
	@brief �洢3G��Ӫ�̡�
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 save3gCarrier(INT32 carrierType, string &strErr);
	/*!
	@brief ��ȡ3G��Ӫ�̡�
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 load3gCarrier(INT32 *carrierType, string &strErr);

	/*!
	@brief �洢M2M����״̬��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 save_M2M_State(INT32 actState, string &strErr);
	/*!
	@brief ��ȡM2M����״̬��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 load_M2M_State(INT32 *actState, string &strErr);

	/*!
	@brief �洢APN���������㡣
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 save_APN_Acc_Num(string &AccPoint, string &Number, string &strErr);
	/*!
	@brief ��ȡAPN���������㡣
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 load_APN_Acc_Num(string &AccPoint, string &Number, string &strErr);

	/*!
	@brief �洢VPN�û��������롣
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveVPNUserNamePwd(string &name, string &pwd, string &strErr);
	/*!
	@brief ��ȡVPN�û��������롣
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadVPNUserNamePwd(string &name, string &pwd, string &strErr);

	/*!
	@brief �洢VPN������IP��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveVPNServer(string &ip, string &strErr);
	/*!
	@brief ��ȡVPN������IP��
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadVPNServer(string &ip, string &strErr);


	/*!
	@brief �洢Ӧ�÷�������IP��˿ڡ�
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveAPPServerIP(string &ip, string &port, string &strErr);
	/*!
	@brief ��ȡӦ�÷�������IP��˿ڡ�
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadAPPServerIP(string &ip, string &port, string &strErr);

	/*!
	@brief �洢Ӧ�÷�������HTTP·����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveAPPServerFILE(string &file, string &strErr);
	/*!
	@brief ��ȡӦ�÷�������HTTP·����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadAPPServerFILE(string &file, string &strErr);

	/*!
	@brief �洢ʱ���������IP��˿ڡ�
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveTIMEServerIP(string &ip, string &port, string &strErr);
	/*!
	@brief ��ȡʱ���������IP��˿ڡ�
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadTIMEServerIP(string &ip, string &port, string &strErr);

	/*!
	@brief �洢ʱ���������HTTP·����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveTimeServerFILE(string &file, string &strErr);
	/*!
	@brief �洢ʱ���������HTTP·����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadTimeServerFILE(string &file, string &strErr);


private:

	/*!
	@brief ͨ��loadproc������һ������ֵ��ϵͳ������
	@param[in] id ϵͳ������ʶ��
	@param[out] v_int ϵͳ����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadSysArg(INT32 id, INT32 *v_int, string &strErr);
	/*!
	@brief ͨ��loadproc������һ���ַ���ֵ��ϵͳ������
	@param[in] id ϵͳ������ʶ��
	@param[out] v_int ϵͳ����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadSysArg(INT32 id, string &m_vText, string &strErr);
	/*!
	@brief ��һ��ϵͳ������
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadproc(INT32 id, INT32 *v_int, string &v_text, string &strErr);
	
	/*!
	@brief ͨ��saveproc��һ������ֵ��ϵͳ������
	@param[in] id ϵͳ������ʶ��
	@param[out] v_int ϵͳ����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveSysArg(INT32 id, INT32 v_int, string &strErr);
	/*!
	@brief ͨ��saveproc��һ���ַ���ֵ��ϵͳ������
	@param[in] id ϵͳ������ʶ��
	@param[out] v_int ϵͳ����
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveSysArg(INT32 id, string &m_vText, string &strErr);
	/*!
	@brief ��ӻ����һ��ϵͳ�������Զ�������ӻ��Ǹ��µ��жϣ���
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveproc(INT32 id, INT32 v_int, string &v_text, string &strErr);

	/*!
	@brief ͨ��saveproc������ϵͳ������
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 saveTwoSysArgFunc(INT32 ID1, string &value1, INT32 ID2, 
									string &value2, string &strErr);
	/*!
	@brief ͨ��loadprocȡ����ϵͳ������
	@return NET_SUCCESS - �ɹ������� - ʧ��
	*/
	static INT32 loadTwoSysArgFunc(INT32 ID1, string &value1, INT32 ID2, 
									string &value2, string &strErr);
	

	CNetDBWork();
	~CNetDBWork();

};




#endif

