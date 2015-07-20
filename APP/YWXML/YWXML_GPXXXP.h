/*! \file    YWXML_GPXXXP.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��Ϣд��
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_GPXXXP_H
#define YWXML_GPXXXP_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


/**
 *@class CGpxxxp
 *@brief ��Ʊ��Ϣд��
 */
class CGpxxxp: public CYWXmlBase
{

public:

	/*!
	@brief ��Ʊ��Ϣд��
	@param[in] ywlx ҵ������
	@param[in] gpxxmw ��Ʊ��Ϣ����
	*/
	CGpxxxp(CYWXML_GY &ywxml_gy, string gpxxmw);
	~CGpxxxp();
	

	/*!
	@brief ��Ʊ��Ϣд�̣����������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*!
	@brief ��Ʊ��Ϣд�̣������������������XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse();
	
	string m_gpxxmw;	//��Ʊ��Ϣ����
};


#endif



