/*! \file    YWXML_JKSJCX.h
\brief    ������õ��м���ӿ� ҵ��: ������ݲ�ѯ
\author   myf
\version  1.0
\date     2015 
*/

#ifndef YWXML_JKSJCX_H
#define YWXML_JKSJCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CUserInfo.h"
#include "CInvKind.h"
//#include "JSKManageProc.h"

/**
 *@class CJksjcx
 *@brief ������ݲ�ѯ
 */
class CJksjcx: public CYWXmlBase
{

public:

	/*!
	@brief		������ݲ�ѯ
	@param[in] ywlx ҵ������
	@param[out] Userinfo ��˰����Ϣ
	@param[out] InvKind ��Ʊ������Ϣ
	*/
	CJksjcx(CYWXML_GY &ywxml_gy, CInvKind &InvKind);
	~CJksjcx();
	
	/*!
	@brief ������ݲ�ѯ�����������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*!
	@brief ������ݲ�ѯ�������������������XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse();	

	CInvKind &m_InvKind;

private:
};


#endif



