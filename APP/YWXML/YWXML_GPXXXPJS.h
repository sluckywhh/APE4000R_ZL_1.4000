/*! \file    YWXML_GPXXXPJS.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��Ϣд�̽���
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_GPXXXPJS_H
#define YWXML_GPXXXPJS_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


/**
 *@class CGpxxxpjs
 *@brief ��Ʊ��Ϣд�̽���
 */
class CGpxxxpjs: public CYWXmlBase
{

public:

	/*!
	@brief ��Ʊ��Ϣд�̽���
	@param[in] ywlx ҵ������
	@param[in] wslpjsxx ������Ʊ������Ϣ
	*/
	CGpxxxpjs(CYWXML_GY &ywxml_gy, string wslpjsxx);
	~CGpxxxpjs();


	/*!
	@brief ��Ʊ��Ϣд�̽��������������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*!
	@brief ��Ʊ��Ϣд�̽����������������������XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse();	
	
	string m_wslpjsxx;
};


#endif



