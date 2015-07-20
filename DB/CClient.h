#ifndef __CCLIENT_H
#define __CCLIENT_H

#include "CTable.h"
#include "CDB.h"

/**
 *@class CClient 
 *@brief �ͻ�������Ϣ
 *@brief �Ծ���ʹ�õĸ��������ƽ��м�ƹ���
 */
class CClient : public CTable
{
public:

	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CClient();

    /*!
	@brief ��������	
	*/
	~CClient();

	string m_khbh;		/**< ���ر�� */
	string m_khdm;		/**< �ͻ����� */
	string m_khjm; 		/**< ������� */
	string m_khmc;		/**< �ͻ����� */
	string m_khsh;		/**< ˰�� */
};

#endif
