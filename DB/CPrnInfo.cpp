#include "CPrnInfo.h"

#include "LOGCTRL.h"
#include "pos_debug.h"

CPrnInfo::CPrnInfo()
{

	SET_TABLE_NAME("PRN_INFO");
	SET_FIELD_NUM(6);

	SET_FIELD_MEMBER(DB_TEXT, &m_zdyTab1, "ZDY_TAB1", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_zdyCont1, "ZDY_CONT1", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_zdyTab2, "ZDY_TAB2", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_zdyCont2, "ZDY_CONT2", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_remarks, "REMARKS", 0);	
	SET_FIELD_MEMBER(DB_TEXT, &m_backup, "BACKUP", 0);	

	
	m_zdyTab1 = "";			/**< �Զ�������1 */
	m_zdyCont1= "";		/**< �Զ�������1 */
	m_zdyTab2= "";				/**< �Զ�������2 */
	m_zdyCont2= "";		/**< �Զ�������2 */
	m_remarks= "";			/**< �����ֶ� */
	m_backup= "";				/**< ���� */
}

CPrnInfo::~CPrnInfo()
{
}


