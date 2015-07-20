/*! \file    YWXML_FPZF.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ����
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_FPZF_H
#define YWXML_FPZF_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvHead.h"

/**
 *@class CFpzf
 *@brief ��Ʊ����
 */
class CFpzf: public CYWXmlBase
{

public:

	/*!
	@brief ��Ʊ����
	@param[in] ywlx ҵ������
	@param[out] InvInfo ��Ʊ��Ϣ
	*/
	CFpzf(CYWXML_GY &ywxml_gy, UINT8 zflx, CInvHead &InvInfo);
	~CFpzf();
	
	/*!
	@brief ��Ʊ���ϣ����������װ����װ��XML�ļ���
	@param[in]  pInvInfo  ��Ʊ����
	@param[in] zflx  ��������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief ��Ʊ���ϣ������������������XML�ļ���
	@param[in] pInvVol ָ��Ʊ��Ϣ���ָ�� 
	@param[in] retInfo ������Ϣָ��Ϣ�����
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlParse();	

	CInvHead &m_InvInfo;
	UINT8 m_zflx;
};


#endif



