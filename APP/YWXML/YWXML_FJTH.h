/*! \file    YWXML_FJTH.h
   \brief    ������õ��м���ӿ� ҵ��2.24 �ֻ��˻�
   \author   zfj
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_FJTH_H
#define YWXML_FJTH_H


#include "IncludeMe.h"
#include "YWXmlBase.h"


/**
 *@class CFjth
 *@brief �ֻ��˻�
 */
class CYWXMLFjth : public CYWXmlBase
{
public:
	/*!
	@brief 2.24.�ֻ��˻�
	@param[in] ywlx 		ҵ������
	@param[in]  strJzlx	��������
	*/
	CYWXMLFjth(CYWXML_GY &ywxml_gy, UINT8 strJzlx);
	~CYWXMLFjth();
	
	INT32 XmlBuild();
	INT32 XmlParse();
	
	UINT8 	m_strJzlx;
private:
	
};


#endif



