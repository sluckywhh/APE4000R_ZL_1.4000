/*! \file   NETXML_QLJS.h
   \brief    ������õ��м���ӿ� ҵ��: ��ػش�, �����������
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef NETXML_QLJS_H
#define NETXML_QLJS_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


/**
 *@class CQljs
 *@brief �����������
 */
class CQljs: public CYWXmlBase
{

public:

	/*!
	@brief �������������Ϣ��ѯ
	@param[in] ywlx ҵ������
	@param[in]  Kpjh		��Ʊ����
	@param[in]  FpmxCount	��Ʊ��ϸ��
	@param[out] Fpjkmw ��Ʊ�������
	@param[out] Szjkmw ʱ�Ӽ������
	@param[out] Count �ϴ���Ʊ��ϸ����
	*/
	CQljs(CYWXML_GY &ywxml_gy, string Qtxx,string &Fpjkmw);
	~CQljs();

	/*!
	@brief ����������������������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief ������������������������������XML�ļ��� 
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlParse();
	
	string &m_Fpjkmw;
	UINT32 m_Count;

	UINT32 m_FpCount;
	string m_Qtxx;
};


#endif



