/*! \file    YWXML_TJXXCX.h
   \brief    ������õ��м���ӿ� ҵ��2.19ͳ����Ϣ��ѯ
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_TJXXCX_H
#define YWXML_TJXXCX_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CTjxxhz.h"
#include "SysMacDef.h"

/**
 *@class CTjxxcx
 *@brief ͳ����Ϣ��ѯ
 */
class CTjxxcx : public CYWXmlBase
{
public:
	/*!
	@brief 2.19.ͳ����Ϣ��ѯ
	@param[in] ywlx 		ҵ������
	@param[in&out]  tjxxhz	ͳ����Ϣ������
	*/

	CTjxxcx(CYWXML_GY &ywxml_gy, CTjxxhz &tjxxhz);
	~CTjxxcx();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	CTjxxhz 	&m_tjxxhz;
private:
	
};


#endif


