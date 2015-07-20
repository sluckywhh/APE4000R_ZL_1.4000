#ifndef __CINV_SUM_H
#define __CINV_SUM_H

#include "CTable.h"
#include "CDB.h"


/**
 *@class CInvSum 
 *@brief ����Ʊ��Ϣͳ�Ʊ�
 *@brief 
 */
class CInvSum : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CInvSum();

    /*!
	@brief ��������	
	*/
	~CInvSum();

	/*!
	@brief �ж��Ƿ�����������ڼ�¼̫��ʱ���Ƿ�ɾ�����ּ�¼
	@param[in] nCount ��ʵ�ʴ洢�ļ�¼����
	@param[in] strRefDate �ϴ��걨���ݵĽ�ֹ����
	@param[out] nDelDate ʵ��Ҫɾ����¼�Ľ�ֹ����
	@return  0 ʧ�ܣ�  1 �ɹ�
	*/
	INT32 CheckRoll(INT32 nCount, UINT32 strRefDate, UINT32 &nDelDate);

	/*!
	@brief �����������ڼ�¼̫��ʱ��ɾ�����ּ�¼
	@param[in] nDelDate ʵ��Ҫɾ����¼�Ľ�ֹ����
	@return  0 ʧ�ܣ�  1 �ɹ�
	*/
	INT32 Roll(UINT32 nDelDate);
    

	UINT32 m_no; 			/**< ������ */
	UINT8 	    m_Type;       			/*��Ʊ����*/

	UINT32		m_Qsrq;			/**< ��ʼ����*/
	UINT32		m_Jzrq;			/**< ��ֹ����*/
	UINT32	    m_OpenInventory;		 /*�ڳ����*/  
	UINT32    	m_NewBuy; 			/*�����¹�*/ 
	UINT32    	m_EndInventory; 		/*��ĩ���*/
	UINT32     	m_ReBack; 				/*�����˻�*/
	UINT32     	m_InvNum; 			/*������Ʊ���߷���*/
	UINT32      m_InvCancelNum; 		/*������Ʊ���Ϸ���*/
	UINT32      m_NegInvNum; 			/*������Ʊ���߷���*/
	UINT32      m_NegInvCancelNum; 		/*������Ʊ���Ϸ���*/
	UINT32		m_Kffpfs;			/**< �շϷ�Ʊ���� */

	INT64     	m_InvSum; 			/*������Ʊ�ۼƽ��*/
	INT64    	m_InvTax; 			/*������Ʊ�ۼ�˰��*/
	INT64		m_Zffpljje;		/**< ���Ϸ�Ʊ�ۼƽ�� */
	INT64		m_Zffpljse;		/**< ���Ϸ�Ʊ�ۼ�˰�� */
	INT64     	m_NegInvSum; 		/*������Ʊ�ۼƽ��*/
	INT64     	m_NegInvTax; 		/*������Ʊ�ۼ�˰��*/
	INT64		m_Fffpljje;		/**< ���Ϸ�Ʊ�ۼƽ�� */
	INT64		m_Fffpljse;		/**< ���Ϸ�Ʊ�ۼ�˰�� */

};

#endif