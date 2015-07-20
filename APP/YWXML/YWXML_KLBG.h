/*! \file    YWXML_KLBG.h
   \brief    ������õ��м���ӿ� ҵ��: ��˰�̿�����
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_KLBG_H
#define YWXML_KLBG_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


/**
 *@class CKlbg
 *@brief ��˰�̿�����
 */
class CKlbg: public CYWXmlBase
{

public:


	/*!
	@brief��˰�̿�����
	@param[in] ywlx ҵ������
	@param[in] ykl ��ԭ���� 
	@param[in] xkl ���¿���
	*/
	CKlbg(CYWXML_GY &ywxml_gy, string ykl, string xkl);
	~CKlbg();


	/*!
	@brief ��˰�̿����������������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();

	/*!
	@brief ��˰�̿������������������������XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse();

	string m_ykl;
	string m_xkl;
};


#endif



