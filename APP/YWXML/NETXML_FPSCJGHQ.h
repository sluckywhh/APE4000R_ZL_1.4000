/*! \file    NETXML_FPSCJGHQ.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��ϸ�ϴ������ȡ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef NETXML_FPSCJGHQ_H
#define NETXML_FPSCJGHQ_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


/**
 *@class CFpscjghq
 *@brief ��Ʊ��ϸ�ϴ������ȡ
 */
class CFpscjghq: public CYWXmlBase
{

public:


	/*!
	@brief ��Ʊ��ϸ�ϴ������ȡ
	@param[in] ywlx ҵ������
	@param[in]  FpmxCount	��Ʊ��ϸ��
	@param[out] Mxjgmw ���ܺ����ϸ�ϴ�������� 
	@param[out] Count �ϴ���Ʊ��ϸ����
	*/
	CFpscjghq(CYWXML_GY &ywxml_gy, string qtxx, string &Mxjgmw);
	~CFpscjghq();
	
	/*!
	@brief ��Ʊ��ϸ�ϴ������ȡ�����������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief ��Ʊ��ϸ�ϴ������ȡ�������������������XML�ļ��� 
	@param[out] Mxjgmw ���ܺ����ϸ�ϴ�������� 
	@param[out] Count �ϴ���Ʊ��ϸ����
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlParse();
	
	string &m_Mxjgmw;
	UINT32 m_Count;
	UINT32 m_FpCount;
	string m_Slxlh;
	string m_Qtxx;
};


#endif



