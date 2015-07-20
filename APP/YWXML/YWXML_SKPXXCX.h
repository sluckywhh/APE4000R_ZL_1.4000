/*! \file    YWXML_SKPXXCX.h
   \brief    ������õ��м���ӿ� ҵ��2.2.˰���豸��Ϣ��ѯ
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_SKPXXCX_H
#define YWXML_SKPXXCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CUserInfo.h"

/**
 *@class CSkpxxcx
 *@brief 2.2.˰���豸��Ϣ��ѯ
 */
class CSkpxxcx:  public CYWXmlBase
{

public:

	/*!
	@brief 2.2.˰���豸��Ϣ��ѯ
	@param[in] ywlx ҵ������
	@param[out] Userinfo ��˰����Ϣ
	@param[out] strCurTime ��ǰʱ��YYYYMMDDHHMMSS
	*/
	CSkpxxcx(CYWXML_GY &ywxml_gy, CUserInfo &UserInfo, string &strCurTime);
	~CSkpxxcx();

	/*!
	@brief ˰���豸��Ϣ��ѯ�����������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*!
	@brief ˰���豸��Ϣ��ѯ�������������������XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse();
	
	CUserInfo &m_UserInfo;	//��˰����Ϣ
	string	  &m_strCurTime;	//��ǰʱ��YYYYMMDDHHMMSS

	private:
		
};


#endif



