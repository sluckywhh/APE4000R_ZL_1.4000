#ifndef __COPERATOR_H
#define __COPERATOR_H

#include "CTable.h"
#include "CDB.h"


#define ADMINISTRATOR_ROLE   1  //ϵͳ����Ա��ɫ
#define DIRECTOR_ROLE		 2  //���ܲ���Ա��ɫ
#define NORMAL_ROLE			 3  //��ͨ����Ա��ɫ
#define DEMO_ROLE			 4  //ѧϰģʽ��ɫ


/**
 *@class COperator 
 *@brief ����Ա��Ϣ��
 *@brief 
 */
class COperator : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	COperator();

    /*!
	@brief ��������	
	*/
	~COperator();
	
	UINT8   m_opid;		/**< ���� */
	string  m_name;		/**< ���� */
	string  m_passwd;	/**< ���� */
	UINT8   m_role;		/**< ��ɫ */
};

#endif
