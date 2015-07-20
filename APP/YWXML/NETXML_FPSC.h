/*! \file    NETXML_FPSC.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ�ϴ�
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef NETXML_FPSC_H
#define NETXML_FPSC_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


/**
 *@class CFpsc
 *@brief ��Ʊ�ϴ�
 */
class CFpsc: public CYWXmlBase
{

public:

	/*!
	@brief  ��Ʊ��ϸ�ϴ�
	@param[in] ywlx ҵ������
	@param[in]  Fpmx	��Ʊ��ϸ
	@param[in]  FpmxCount	��Ʊ��ϸ��
	@param[in]  Fpzs		��Ʊ����
	@param[out] Count
	*/
	CFpsc(CYWXML_GY &ywxml_gy, const string &Fpmx, UINT32 Fpzs, string &Slxlh);
	~CFpsc();

	/*!
	@brief ��Ʊ��ϸ�ϴ������������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief ��Ʊ��ϸ�ϴ��������������������XML�ļ��� 
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlParse();	

	const string &m_Fpmx;
	UINT32 m_FpCount;
	UINT32 m_Fpzs;
	UINT32 m_Count;
	string &m_Slxlh;

};


#endif



