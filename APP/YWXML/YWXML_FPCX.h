/*! \file    YWXML_FPCX.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_FPCX_H
#define YWXML_FPCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvHead.h"
#include "CUserInfo.h"

/**
 *@class CFpcx
 *@brief ��Ʊ��ѯ
 */
class CFpcx: public CYWXmlBase
{

public:

	/*!
	@brief ��Ʊ��ѯ
	@param[in] ywlx ҵ������
	@param[in]  cxfs	  ��ѯ��ʽ
	@param[in]  cxtj     ��ѯ����
	@param[out] Userinfo ��Ʊ��Ϣ
	@param[out] strurCTime ��Ʊ����
	*/
	CFpcx(CYWXML_GY &ywxml_gy, UINT8 cxfs, string cxtj, CInvHead &InvInfo, UINT32 &InvCOunt);
	~CFpcx();

	/*!
	@brief ��Ʊ��ѯ�����������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief ��Ʊ��ѯ�������������������XML�ļ���
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlParse();
	
	CInvHead &m_InvInfo;
// 	CUserInfo m_UserInfo;

	UINT32 &m_InvCOunt;
	UINT8 m_cxfs;
	string m_cxtj;
};



#endif



