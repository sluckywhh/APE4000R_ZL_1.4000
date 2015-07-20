/*! \file    YWXML_SKSBQTYXXCX.h
   \brief    ������õ��м���ӿ� ҵ��: ˰���豸������Ϣ��ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_SKSBQTYXXCX_H
#define YWXML_SKSBQTYXXCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

#include "CInvVol.h"


/**
 *@class CSksbqtxxcx
 *@brief ˰���豸������Ϣ��ѯ
 */
class CSksbqtxxcx : public CYWXmlBase
{

public:

	/*!
	@brief ˰���豸������Ϣ��ѯ
	@param[in] ywlx ҵ������
	@param[in] xxlx	��Ϣ����
	@param[out] sksbxx ˰���豸��Ϣ
	*/
	CSksbqtxxcx(CYWXML_GY &ywxml_gy, UINT8 xxlx, string &sksbxx);
	~CSksbqtxxcx();


	/*!
	@brief ˰���豸������Ϣ��ѯ�����������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*!
	@brief ˰���豸������Ϣ��ѯ�������������������XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse();

	UINT8 m_xxlx;	//��Ϣ����
	string &m_sksbxx; //˰���豸��Ϣ
};


#endif



