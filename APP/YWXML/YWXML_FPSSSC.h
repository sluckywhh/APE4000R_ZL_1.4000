/*! \file    YWXML_FPSSSC.h
   \brief    ������õ��м���ӿ� ҵ��2.21.��Ʊʵʱ�ϴ�
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_FPSSSC_H
#define YWXML_FPSSSC_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


/**
 *@class CFpsssc
 *@brief 2.21.��Ʊʵʱ�ϴ�
 */
class CFpsssc : public CYWXmlBase
{
public:
	/*!
	@brief 2.21.��Ʊʵʱ�ϴ�
	@param[in] ywlx 		ҵ������
	@param[in&out] nFpzs		��Ʊ����
	@param[in&out] strCzlx		��������
	@param[out]  strInvBuf		��Ʊ��ϸ
	*/

	CFpsssc(CYWXML_GY &ywxml_gy, UINT32 &nFpzs, UINT8 &strCzlx, string &strInvBuf);
	~CFpsssc();
	
	
	INT32 XmlBuild();
	INT32 XmlParse();

	UINT32 &m_nFpzs;
	UINT8 &m_strCzlx;
	string &m_strInvBuf;

private:
		
};


#endif



