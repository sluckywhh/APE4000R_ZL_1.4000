/*! \file    YWXML_FPBL.h
   \brief    ������õ��м���ӿ� ҵ��2.28.��Ʊ��¼
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_FPBL_H
#define YWXML_FPBL_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


/**
 *@class CFpbl
 *@brief 2.28.��Ʊ��¼
 */
class CFpbl : public CYWXmlBase
{
public:
	/*!
	@brief 2.28.��Ʊ��¼
	@param[in] ywlx 		ҵ������
	@param[in]  StartDate	��˰��ʼ����
	@param[in]  EndDate		��˰��ֹ����
	*/
	CFpbl(CYWXML_GY &ywxml_gy, UINT32 StartDate, UINT32 EndDate);
	~CFpbl();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	UINT32 	m_StartDate;
	UINT32 	m_EndDate;	
private:
	
};


#endif



