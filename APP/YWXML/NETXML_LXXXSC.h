/*! \file    NETXML_LXXXSC.h
   \brief    ������õ��м���ӿ� ҵ��3.5 ������Ϣ�ϴ�
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef NETXML_LXXXSC_H
#define NETXML_LXXXSC_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvKind.h"
#include "SysMacDef.h"

/**
 *@class CLxxxsc
 *@brief ������Ϣ�ϴ�
 */
class CLxxxsc : public CYWXmlBase
{
public:
	/*!
	@brief 3.5. ������Ϣ�ϴ�
	@param[in] ywlx 		ҵ������
	@param[in]  invkind		��˰��Ʊ�ֱ�
	@param[in]  strScjzrq	�ϴ���ֹ����
	@param[in]  strQtxx		������Ϣ
	@param[out]  strLzkzxx		���߿�����Ϣ
	*/
	CLxxxsc(CYWXML_GY &ywxml_gy, CInvKind &invkind, string &strQtxx, string &strLzkzxx);
	~CLxxxsc();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	const CInvKind &m_invkind;
	const string &m_strQtxx;
	string &m_strLxkzxx;
private:
	
};


#endif

