#ifndef __CTJXXHZ_H
#define __CTJXXHZ_H

#include "IncludeMe.h"

//#include "CTable.h"
//#include "CDB.h"


/**
 *@class CTjxxhz
 *@brief ͳ����Ϣ���ܱ�
 *@brief 
 */
class CTjxxhz
{
public:
    
	/*!
	@brief ���캯��	
	*/ 
	CTjxxhz();

    	/*!
	@brief ��������	
	*/
	~CTjxxhz();
		
public:
	UINT32  m_Qsrq;		/**< ��ʼ����*/
	UINT32  m_Jzrq;		/**< ��ֹ����*/
	UINT32  m_Qckcfs;	/**< �ڳ������� */
	UINT32  m_Lgfpfs;	/**< �칺��Ʊ���� */
	UINT32  m_Thfpfs;	/**< �˻ط�Ʊ���� */
	UINT32  m_Zsfpfs;	/**< ������Ʊ���� */
	UINT32  m_Zffpfs;		/**< ���Ϸ�Ʊ���� */
	UINT32  m_Fsfpfs;	/**< ������Ʊ���� */
	UINT32  m_Fffpfs;		/**< ���Ϸ�Ʊ���� */
	UINT32  m_Kffpfs;	/**< �շϷ�Ʊ���� */
	UINT32  m_Qmkcfs;	/**< ��ĩ������ */
	INT64	m_Zsfpljje;	/**< ������Ʊ�ۼƽ�� */
	INT64	m_Zsfpljse;	/**< ������Ʊ�ۼ�˰�� */
	INT64	m_Zffpljje;	/**< ���Ϸ�Ʊ�ۼƽ�� */
	INT64	m_Zffpljse;	/**< ���Ϸ�Ʊ�ۼ�˰�� */
	INT64	m_Fsfpljje;	/**< ������Ʊ�ۼƽ�� */
	INT64	m_Fsfpljse;	/**< ������Ʊ�ۼ�˰�� */
	INT64	m_Fffpljje;	/**< ���Ϸ�Ʊ�ۼƽ�� */
	INT64	m_Fffpljse;	/**< ���Ϸ�Ʊ�ۼ�˰�� */
	
};

#endif
