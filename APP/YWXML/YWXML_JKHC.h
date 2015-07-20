/*! \file    YWXML_JKHC.h
   \brief    ������õ��м���ӿ� ҵ��2.18��ػش�
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_JKHC_H
#define YWXML_JKHC_H


#include "IncludeMe.h"
#include "YWXmlBase.h"

/**
 *@class CJkhc
 *@brief ��ػش�
 */
class CJkhc : public CYWXmlBase
{
public:
	/*!
	@brief 2.18.��ػش�
	@param[in] ywlx 		ҵ������
	@param[in]  strFpjkmw	��Ʊ�������

	*/
	CJkhc(CYWXML_GY &ywxml_gy, string strFpjkmw);
	~CJkhc();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	string 	m_strFpjkmw;
// 	string 	&m_strSzjkmw;

private:
		
};


#endif































