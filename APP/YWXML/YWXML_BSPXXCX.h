/*! \file    YWXML_BSPXXCX.h
   \brief    ������õ��м���ӿ� ҵ��: ��˰����Ϣ��ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_BSPXXCX_H
#define YWXML_BSPXXCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CUserInfo.h"


/**
 *@class CBspxxcx
 *@brief ��˰����Ϣ��ѯ
 */
class CBspxxcx : public CYWXmlBase
{

public:

	/*!
	@brief ��˰����Ϣ��ѯ
	@param[in] ywlx		ҵ������
	@param[out] sksbbh  ��˰�̱��
	*/
	CBspxxcx(CYWXML_GY &ywxml_gy, CUserInfo &userInfo);
	~CBspxxcx();

	/*!
	@brief ��˰����Ϣ��ѯ�����������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*!
	@brief ��˰����Ϣ��ѯ�������������������XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse();

	CUserInfo &m_UserInfo;


	private:
};


#endif



