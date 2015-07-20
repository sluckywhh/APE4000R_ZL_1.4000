#ifndef __CDEPT_H
#define __CDEPT_H

#include "CTable.h"
#include "CDB.h"

/**
 *@class CDept 
 *@brief ��Ʒ��Ϣ��
 *@brief 
 */
class CDept : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CDept();

    /*!
	@brief ��������	
	*/
	~CDept();
	
	string m_spbm;		/**< ���� */
	string m_spmc;		/**< ���� */
	double m_spdj;		/**< ���� */
	float  m_spsl;		/**< ˰�� */
	string m_spdw;		/**< ��λ */
	UINT32 m_blh;       /**< ��Ӧ�Ĳ���ţ�Ĭ��Ϊ�� */

	string m_spjm;		/**< ��� */
	string m_spgg;		/**< ��� */
	string m_zspmdm;	/**< ������Ʒ����(˰Ŀ) */
	float  m_spzsl;		/**< ������ */
	float  m_rate;		/**< ��Ʒ�ۿ��� */

};

#endif
