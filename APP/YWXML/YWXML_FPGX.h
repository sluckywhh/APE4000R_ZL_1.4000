/*! \file    YWXML_FPGX.h
   \brief    ������õ��м���ӿ� ҵ��2.22.��Ʊ����
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_FPGX_H
#define YWXML_FPGX_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


/**
 *@class CFpgx
 *@brief 2.22.��Ʊ����
 */
class CFpgx : public CYWXmlBase
{
public:
	/*!
	@brief 2.15.��Ʊ�ַ�
	@param[in] ywlx 		ҵ������
	@param[in] strScqrbw		�ϴ��ɹ�ȷ�ϱ���
	*/
	CFpgx(CYWXML_GY &ywxml_gy, string strScqrbw);
	~CFpgx();
	
	
	INT32 XmlBuild();
	INT32 XmlParse();

	string 	m_strScqrbw;


private:
	
};


#endif



