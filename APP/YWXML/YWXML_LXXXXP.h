/*! \file    YWXML_LXXXXP.h
   \brief    ������õ��м���ӿ� ҵ��2.20.������Ϣд��
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_LXXXXP_H
#define YWXML_LXXXXP_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


/**
 *@class CLxxxxp
 *@brief 2.20.������Ϣд��
 */
class CLxxxxp : public CYWXmlBase
{
public:
	/*!
	@brief 2.20.������Ϣд��
	@param[in] ywlx 		ҵ������
	@param[in]  strLxxxmw ������Ϣ����
	*/
	CLxxxxp(CYWXML_GY &ywxml_gy, string strLxxxmw);
	~CLxxxxp();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	string 	m_strLxxxmw;
	
private:
	
};


#endif



