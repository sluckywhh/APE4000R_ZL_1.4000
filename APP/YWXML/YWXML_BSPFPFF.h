/*! \file    YWXML_BSPFPFF.h
   \brief    ������õ��м���ӿ� ҵ��2.15 ��Ʊ�ַ�
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_BSPFPFF_H
#define YWXML_BSPFPFF_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

/**
 *@class CBspfpff
 *@brief ��Ʊ�ַ�
 */
class CBspfpff : public CYWXmlBase
{
public:
	/*!
	@brief 2.15.��Ʊ�ַ�
	@param[in] ywlx 		ҵ������
	@param[in] invvol		��Ʊ������Ϣ
	@param[in]  strJzlx	��������
	*/
	CBspfpff(CYWXML_GY &ywxml_gy, CInvVol &invvol, UINT8 strJzlx);
	~CBspfpff();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	CInvVol &m_invvol;
	UINT8 	m_strJzlx;
	
private:

};


#endif


