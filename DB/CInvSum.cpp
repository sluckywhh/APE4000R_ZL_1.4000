#include "CInvSum.h"
#include "SysMacDef.h"

#include "LOGCTRL.h"
#include "pos_debug.h"

//#define  INV_SUM_DEL_MAX   5  /**< ����ʱɾ��������¼�� */
//#define  INV_SUM_MAX		15  /**< ��������������¼��	 */

CInvSum::CInvSum()
{
	m_roll = 1;	
	m_Type=0;       			/*��Ʊ����*/

	m_Qsrq = 0;		
	m_Jzrq = 0;		

	m_OpenInventory=0;		 /*�ڳ����*/  
	m_NewBuy=0; 			/*�����¹�*/ 
	m_EndInventory=0; 		/*��ĩ���*/
	m_ReBack=0;				/*�����˻�*/

	m_InvNum=0; 			/*������Ʊ���߷���*/
	m_InvCancelNum=0; 		/*������Ʊ���Ϸ���*/
	m_NegInvNum=0; 			/*������Ʊ���߷���*/
	m_NegInvCancelNum=0; 		/*������Ʊ���Ϸ���*/
	m_Kffpfs = 0;	

	m_InvSum=0;			/*������Ʊ�ۼƽ��*/
	m_InvTax=0; 			/*������Ʊ�ۼ�˰��*/
	m_Zffpljje = 0;		
	m_Zffpljse = 0;	
	m_NegInvSum=0; 		/*������Ʊ�ۼƽ��*/
	m_NegInvTax =0; 		/*������Ʊ�ۼ�˰��*/
	m_Fffpljje = 0;		
	m_Fffpljse = 0;	

	
	SET_TABLE_NAME("INV_SUM");
	SET_FIELD_NUM(20);
	
	SET_FIELD_MEMBER(DB_UINT32, &m_no, "NO", 0);
	
	SET_FIELD_MEMBER(DB_UINT32, &m_Qsrq, "QSRQ", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_Jzrq, "JZRQ", 0);

	SET_FIELD_MEMBER(DB_UINT32, &m_OpenInventory, "QCKC", 0);	  
	SET_FIELD_MEMBER(DB_UINT32, &m_NewBuy, "BQXG", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_ReBack, "BQTH", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_EndInventory, "QMKC", 0);
	  
	SET_FIELD_MEMBER(DB_UINT32, &m_InvNum, "ZSFS", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_InvCancelNum, "ZFFS", 0);	
	SET_FIELD_MEMBER(DB_UINT32, &m_NegInvNum, "FSFS", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_NegInvCancelNum, "FFFS", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_Kffpfs, "KFFS", 0);

	SET_FIELD_MEMBER(DB_INT64, &m_InvSum, "ZSJE", 0);
	SET_FIELD_MEMBER(DB_INT64, &m_InvTax, "ZSSE", 0);	
	SET_FIELD_MEMBER(DB_INT64, &m_Zffpljje, "ZFJE", 0);
	SET_FIELD_MEMBER(DB_INT64, &m_Zffpljse, "ZFSE", 0);
	SET_FIELD_MEMBER(DB_INT64, &m_NegInvSum, "FSJE", 0);
	SET_FIELD_MEMBER(DB_INT64, &m_NegInvTax, "FSSE", 0);	
	SET_FIELD_MEMBER(DB_INT64, &m_Fffpljje, "FFJE", 0);
	SET_FIELD_MEMBER(DB_INT64, &m_Fffpljse, "FFSE", 0);
}

CInvSum::~CInvSum()
{
}

INT32 CInvSum::CheckRoll(INT32 nCount, UINT32 strRefDate, UINT32 &nDelDate)
{
	DBG_ENTER("CInvSum::Roll");
	
	INT32 nNoStart, nNoEnd;
	char value[32];
	UINT32 strEndDate;
	nDelDate = 0;
	
	if (nCount>=INV_SUM_MAX) //������������¼��
	{
		//�õ���һ����¼�����
		Requery();
		if (LoadOneRecord() == SQLITE_OK)
		{
			nNoStart = m_no;
		}
		else
		{
			DBG_ASSERT_WARNING(false,("Can not load the first record!"));
			DBG_RETURN(FAILURE);
		}
        //��ѯ��ֹ��������IE_DATE�ֶ�
		nNoEnd = nNoStart + INV_SUM_DEL_MAX - 1;
		sprintf(value,"%d",nNoEnd);		
        m_filter = "WHERE NO = ";
		m_filter.append(value);
		
        Requery();
		if (LoadOneRecord() == SQLITE_OK)
		{
			//strEndDate = m_issueEndDate;
		}
		else
		{
			DBG_ASSERT_WARNING(false,("Can not load the first record!"));
			DBG_RETURN(FAILURE);
		}
        
		//		//�Ƚ������ֶΣ�ȷ��ɾ������ 
		//		if(strRefDate <= strEndDate)
		//		{
		//			nDelDate = strRefDate;
		//		}
		//		else
		//		{
		nDelDate = strEndDate;     
		//		}
		DBG_RETURN(SUCCESS);
		
	}
	
	DBG_RETURN(SUCCESS);
}

INT32 CInvSum::Roll(UINT32 nDelDate)
{
	INT8 value[128];
	if (nDelDate>0) //Ҫ����
	{
		sprintf(value, "WHERE IE_DATE <= %lu", nDelDate);
		m_filter = value;
		Delete(); 
	}
	DBG_RETURN(SUCCESS);
	
}
