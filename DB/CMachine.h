#ifndef __CMACHINE_H
#define __CMACHINE_H

#include "CTable.h"
#include "CDB.h"


/**
 *@class CMachine 
 *@brief �տ��������Ϣ��
 *@brief 
 */
class CMachine : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CMachine();

    /*!
	@brief ��������	
	*/
	~CMachine();
	
	string m_machineNo;		/**< ������� */
	string m_pDate;			/**< �������� */		//ԭΪUINT32
	string m_hVer;			/**< Ӳ���汾�� */
	string m_sVer;			/**< ����汾�� */

	string m_IMEI;		/**< ����ģ��IMEI��� */
};

#endif
