#ifndef __CCBHZ_H
#define __CCBHZ_H

#include "CTable.h"
#include "CDB.h"


/**
 *@class CCbhz
 *@brief �������ܱ�
 *@brief 
 */
class CCbhz : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CCbhz();

    /*!
	@brief ��������	
	*/
	~CCbhz();

	void clear();
	
	UINT32  m_no;		/**< ��� */
	UINT32  m_Ssq;		/**< ������ */
	UINT32  m_Ssqq;		/**< �������� */
	UINT32  m_Ssqz;		/**< ������ֹ */
	UINT32  m_Zpfs;		/**< ��Ʊ���� */
	INT64	m_Zpkpje;	/**< ��Ʊ��Ʊ��� */
	UINT32  m_Hpfs;		/**< ��Ʊ���� */
	INT64   m_Hpkpje;	/**< ��Ʊ��Ʊ��� */
	UINT32  m_Zffs;		/**< ��Ʊ���� */
	INT64   m_Zfkpje;	/**< ��Ʊ��Ʊ��� */
	UINT32  m_Hffs;		/**< ��Ϸ��� */
	INT64   m_Hfkpje;	/**< ��Ͽ�Ʊ��� */
	UINT32  m_Kbfpfs;	/**< �հ׷�Ʊ���� */
	UINT32  m_Bsrq;		/**< �������� */
	UINT32  m_Bscgrq;	/**< �����ɹ����� */
	string  m_Bssbyy;	/**< ʧ��ԭ�� */
	UINT8   m_Bslx;		/**< �������� */
	UINT8   m_Bscgbz;	/**< ��˰�ɹ���־ */
	UINT8   m_Bsjzbz;	/**< ���ͽ��ʱ�־ */
	UINT32  m_Wscfps;	/**< δ�ϴ���Ʊ���� */
};

#endif
