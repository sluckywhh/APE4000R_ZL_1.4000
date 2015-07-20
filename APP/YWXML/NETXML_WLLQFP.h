/*! \file    NETXML_WLLQFP.h
   \brief    ������õ��м���ӿ� ҵ��3.6 ������ȡ��Ʊ
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef NETXML_WLLQFP_H
#define NETXML_WLLQFP_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

/**
 *@class CWllqfp
 *@brief ������ȡ��Ʊ
 */
class CWllqfp : public CYWXmlBase
{
public:
	/*!
	@brief 3.6. ������ȡ��Ʊ
	@param[in] ywlx 		ҵ������
	@param[in&out] invvol		��Ʊ������Ϣ
	@param[in]  strQtxx		������Ϣ
	*/
	CWllqfp(CYWXML_GY &ywxml_gy, CInvVol &invvol, const string &strQtxx);
	~CWllqfp();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	CInvVol &m_invvol;
	const string &m_strQtxx;
	
private:
	
};


#endif


