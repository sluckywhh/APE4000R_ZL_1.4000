/*! \file    NETXML_WLLQFPJGQR.h
   \brief    ������õ��м���ӿ� ҵ��3.7 ������ȡ��Ʊ���ȷ��
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef NETXML_WLLQFPJGQR_H
#define NETXML_WLLQFPJGQR_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

/**
 *@class CWllqfpjgqr
 *@brief ������ȡ��Ʊ���ȷ��
 */
class CWllqfpjgqr : public CYWXmlBase
{
public:
	/*!
	@brief 3.7. ������ȡ��Ʊ���ȷ��
	@param[in] ywlx 		ҵ������
	@param[in] invvol		��Ʊ������Ϣ
	@param[in]  strQtxx		������Ϣ
	*/

	CWllqfpjgqr(CYWXML_GY &ywxml_gy, CInvVol &invvol, string &strQtxx);
	~CWllqfpjgqr();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	CInvVol &m_invvol;
	string	&m_strQtxx;
private:
	
};


#endif

