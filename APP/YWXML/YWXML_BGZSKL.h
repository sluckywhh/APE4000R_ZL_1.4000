/*! \file    YWXML_BGZSKL.h
   \brief    ������õ��м���ӿ� ҵ��: ������
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_BGZSKL_H
#define YWXML_BGZSKL_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

/**
 *@class CBgzskl
 *@brief ���֤�����
 */
class CBgzskl: public CYWXmlBase
{
public:
	/*!
	@brie֤�������
	@param[in] ywlx ҵ������
	@param[in] yzskl ԭ֤����� 
	@param[in] xzskl ��֤�����
	*/
	CBgzskl(CYWXML_GY &ywxml_gy, string yzskl, string xzskl);
	~CBgzskl();

	/*!
	@brief ֤������������������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();

	/*!
	@brief ֤��������������������������XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse();

	string m_yzskl;
	string m_xzskl;
};

#endif



