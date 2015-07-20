/*! \file    YWXML_GPXXCX.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��Ϣ��ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_GPXXCX_H
#define YWXML_GPXXCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

#include "CInvVol.h"


/**
 *@class CGpxxcx
 *@brief ��Ʊ��Ϣ��ѯ
 */
class CGpxxcx : public CYWXmlBase
{

public:

	/*!
	@brief ��Ʊ��Ϣ��ѯ
	@param[in] ywlx ҵ������
	@param[out] InvVol ��Ʊ��Ϣ
	*/
	CGpxxcx(CYWXML_GY &ywxml_gy, CInvVol &InvVol);
	~CGpxxcx();


	/*!
	@brief ��Ʊ��Ϣ��ѯ�����������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*!
	@brief ��Ʊ��Ϣ��ѯ�������������������XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse();

	CInvVol &m_InvVol;
};


#endif



