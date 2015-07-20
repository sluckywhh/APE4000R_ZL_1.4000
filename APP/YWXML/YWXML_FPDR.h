/*! \file    YWXML_FPDR.h
   \brief    ������õ��м���ӿ� ҵ��2.23.��Ʊ����
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_FPDR_H
#define YWXML_FPDR_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


/**
 *@class CFpdr
 *@brief 2.23.��Ʊ����
 */
class CFpdr : public CYWXmlBase
{
public:
	/*!
	@brief 2.23.��Ʊ����
	@param[in] ywlx 		ҵ������
	@param[in]  strJzlx	��������
	*/
	CFpdr(CYWXML_GY &ywxml_gy, UINT8 strJzlx);
	~CFpdr();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	UINT8 	m_strJzlx;
	
private:
	
};


#endif



