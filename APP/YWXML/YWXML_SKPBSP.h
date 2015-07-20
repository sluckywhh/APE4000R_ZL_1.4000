/*! \file    YWXML_SKPBSP.h
   \brief    ������õ��м���ӿ� ҵ��: ˰���豸��˰����ϲ���
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_SKPBSP_H
#define YWXML_SKPBSP_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


/**
 *@class CSkpBsp
 *@brief ˰���豸��˰����ϲ���
 */
class CSkpBsp: public CYWXmlBase
{

public:

	
	/*!
	@brief ˰���豸��˰����ϲ���
	@param[in] ywlx ҵ������
	@param[in]  Czlx ��������
	@param[in]  Hzxx ������Ϣ
	*/
	CSkpBsp(CYWXML_GY &ywxml_gy, UINT8 Czlx, string Hzxx);
	~CSkpBsp();

private:

	/*!
	@brief ˰���豸��˰����ϲ��������������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief ˰���豸��˰����ϲ������������������XML�ļ���
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlParse();	

	UINT8 m_Czlx;
	string m_Hzxx;
};


#endif



