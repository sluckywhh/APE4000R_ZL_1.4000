/*! \file    YWXML_SQSLCX.h
   \brief    ������õ��м���ӿ� ҵ��:��Ȩ˰�ʲ�ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_SQSLCX_H
#define YWXML_SQSLCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

#include "CTax.h"

class CTaxInfo
{
public:
		CTax m_Tax[MAX_TAX_NUM];
		UINT8 m_TaxCoun;

		CTaxInfo();
		~CTaxInfo();
};

/**
 *@class CSqslcx
 *@brief ��Ȩ˰�ʲ�ѯ
 */
class CSqslcx : public CYWXmlBase
{

public:

	/*!
	@brief	��Ȩ˰�ʲ�ѯ
	@param[in] ywlx ҵ������
	@param[out] Tax ˰����Ϣ
	*/
	CSqslcx(CYWXML_GY &ywxml_gy, CTaxInfo &TaxInfo);
	~CSqslcx();

	/*!
	@brief ��Ȩ˰�ʲ�ѯ�����������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*!
	@brief ��Ȩ˰�ʲ�ѯ�������������������XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse();

	CTaxInfo &m_TaxInfo;

};


#endif



