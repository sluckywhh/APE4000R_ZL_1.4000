#ifndef __CPRN_INFO_H
#define __CPRN_INFO_H

#include "CTable.h"
#include "CDB.h"

/**
 *@class CPrnInfo 
 *@brief ��ӡ��Ʊʱ���Ķ�����Ϣ��
 *@brief 
 */
class CPrnInfo : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CPrnInfo();

    /*!
	@brief ��������	
	*/
	~CPrnInfo();
    
	string m_zdyTab1;			/**< �Զ�������1 */
	string m_zdyCont1;		/**< �Զ�������1 */
	string m_zdyTab2;			/**< �Զ�������2 */
	string m_zdyCont2;		/**< �Զ�������2 */
	string m_remarks;			/**< �����ֶ� */
	string m_backup;			/**< ���� */
};

#endif

