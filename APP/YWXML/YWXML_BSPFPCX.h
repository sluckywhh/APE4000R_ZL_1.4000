/*! \file    YWXML_BSPFPCX.h
   \brief    ������õ��м���ӿ� ҵ��2.14 ��˰�̷�Ʊ��ѯ
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_BSPFPCX_H
#define YWXML_BSPFPCX_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

class CInvVolInfo
{
public:
	CInvVol m_InvVol[INVVOL_MAX_NUM];
	UINT8 m_InvvolCount;
	
	CInvVolInfo();
	~CInvVolInfo();
};

/**
 *@class CBspfpcx
 *@brief ��˰�̷�Ʊ��ѯ
 */
class CBspfpcx : public CYWXmlBase
{
public:
	/*!
	@brief 2.14.��˰�̷�Ʊ��ѯ
	@param[in] ywlx 		ҵ������
	@param[out] InvCount	��Ʊ���þ���
	@param[out] invvol		��Ʊ������Ϣ
	@param[out] strLgry		�칺��Ա
	*/

	CBspfpcx(CYWXML_GY &ywxml_gy, CInvVolInfo &invvolinfo);
	~CBspfpcx();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	CInvVolInfo &m_invvolinfo;
	// string 	&m_strLgry;

private:
	
};


#endif













































