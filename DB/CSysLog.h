#ifndef __CSYSLOG_H
#define __CSYSLOG_H

#include "CTable.h"
#include "CDB.h"

/**
 *@class CSysLog 
 *@brief ϵͳ��־��Ϣ��
 *@brief 
 */
class CSysLog : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CSysLog();

    /*!
	@brief ��������	
	*/
	~CSysLog();

	/*!
	@brief �����жϣ������ڼ�¼̫��ʱ���Ƿ�ɾ�����ּ�¼
	@param[in] nCount ��ʵ�ʴ洢�ļ�¼����
	@param[out] nDelNo ʵ��Ҫɾ����¼�Ľ�ֹ���
	@return  0 ʧ�ܣ�  1 �ɹ�
	*/
	INT32 CheckRoll(INT32 nCount, UINT32 &nDelNo);

	/*!
	@brief �����������ڼ�¼̫��ʱ��ɾ�����ּ�¼
	@param[in] nDelNo ʵ��Ҫɾ����¼�Ľ�ֹ���
	@return  0 ʧ�ܣ�  1 �ɹ�
	*/
	INT32 Roll(UINT32 nDelNo);

	/*!
	@brief ͳ��SYSLOG��洢�ķ�Ʊ��
	@return  >=0: ��Ʊ��; -1: ͳ��ʧ��
	*/
	INT32 GetSysLogNum();
  
	
	UINT32 m_no; 		/**< ���� */
	UINT32 m_idate;		/**< ���� */
	UINT32 m_itime;		/**< ʱ�� */
	string m_operator;	/**< ����Ա���� */
	UINT8   m_type;		/**< �������� */
	UINT32 m_result;	/**< ������� */
	string m_backup;	/**< ���� */
};

#endif
