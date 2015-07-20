#include "CInvKind.h"

#include "LOGCTRL.h"
#include "pos_debug.h"


CInvKind::CInvKind()
{
	m_roll = 1;	

	SET_TABLE_NAME("INV_KIND");
	SET_FIELD_NUM(7);

	SET_FIELD_MEMBER(DB_UINT32, &m_No, "NO", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_fplxdm, "FPLXDM", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_Lxssr, "LX_SSR", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_Lxkjsj, "LX_KJSJ", 0);
	SET_FIELD_MEMBER(DB_INT64, &m_maxSign, "MAX_SING", 0);	
	SET_FIELD_MEMBER(DB_INT64, &m_maxSum, "MAX_SUM", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_backup, "BACKUP", 0);
	
	ResetKind();
}

CInvKind::~CInvKind()
{

}

UINT8 CInvKind::ResetKind()
{

	m_fplxdm = "";
	m_Lxssr = 0;			/**< ���������գ�ÿ�µĵڼ��죩 */
	m_Lxkjsj = 0;			/**< ���߿���ʱ�䣨��λСʱ�� */
	m_maxSign = 0;
	m_maxSum = 0;		/**< ���Ʊ��� */
	m_backup = "";		/**< �����ֶ� */
	m_pzCode = "";
	m_fplx = 0;
	m_bsqsrq = "";
	m_bszzrq = "";

}

UINT8 CInvKind::CompareInvKind(CInvKind *p1, CInvKind *p2)
{
	if (p1->m_fplx !=  p2->m_fplx)
	{
		DBG_PRINT(("Ʊ�ִ��벻ͬ"));
		return FAILURE;
	}

	if ((p1->m_maxSum != p2->m_maxSum)||
		(p1->m_maxSign != p2->m_maxSign))
	{
		DBG_PRINT(("������ͬ"));
		return FAILURE;
	}

	return SUCCESS; //��ͬ
}