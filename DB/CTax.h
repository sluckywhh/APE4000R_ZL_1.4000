#ifndef __CTax_H
#define __CTax_H

#include "CTable.h"
#include "CDB.h"




/**
 *@class CTax 
 *@brief ˰����Ϣ��
 *@brief ˰����Ϣ
 */
class CTax : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CTax();

    /*!
	@brief ��������	
	*/
	~CTax();

	 /*!
	@brief ��������	
	*/
	void ResetTax();

    UINT32 m_no;		/**< ��� */
	UINT32 m_sl;        /**< ˰�� */
	string m_backup;    /**< ���� */	
};

#endif
