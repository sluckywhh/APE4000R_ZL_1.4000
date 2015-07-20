/*! \file    YWXML_BSPFPSH.h
   \brief    ������õ��м���ӿ� ҵ��2.16 ��Ʊ�ջ�
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_BSPFPSH_H
#define YWXML_BSPFPSH_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

/**
 *@class CBspfpsh
 *@brief ��Ʊ�ջ�
 */
class CBspfpsh: public CYWXmlBase
{
public:
	/*!
	@brief 2.16.��Ʊ�ջ�
	@param[in] ywlx 		ҵ������
	@param[in] invvol		��Ʊ������Ϣ
	@param[in]  strJzlx	��������
	*/
	CBspfpsh(CYWXML_GY &ywxml_gy, CInvVol &invvol, UINT8 strJzlx);
	~CBspfpsh();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	CInvVol &m_invvol;
	UINT8 m_strJzlx;
	

private:
	
};


#endif

