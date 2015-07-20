/*! \file    YWXML_FPKJ.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ����
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_FPKJ_H
#define YWXML_FPKJ_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvHead.h"
#include "CInvDet.h"

/**
 *@class CFpkj
 *@brief ��Ʊ����
 */
class CFpkj: public CYWXmlBase
{

public:

	/*!
	@brief ��Ʊ
	@param[in] ywlx ҵ������
	@param[out] InvHead ��Ʊ������Ϣ
	*/
	CFpkj(CYWXML_GY &ywxml_gy, CInvHead &InvInfo);
	~CFpkj();

	/*!
	@brief ��Ʊ���ߣ����������װ����װ��XML�ļ���
	@param[in]  InvInfo	  ��Ʊ��Ϣ
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief ��Ʊ���ߣ��������������������XML�ļ���
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlParse();
	
	CInvHead &m_InvInfo;
};


#endif



