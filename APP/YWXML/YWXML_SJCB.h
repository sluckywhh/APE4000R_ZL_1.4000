/*! \file    YWXML_SJCB.h
   \brief    ������õ��м���ӿ� ҵ��2.17���ݳ���
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_SJCB_H
#define YWXML_SJCB_H


#include "IncludeMe.h"
#include "YWXmlBase.h"

/**
 *@class CSjcb
 *@brief ���ݳ���
 */
class CSjcb : public CYWXmlBase
{
public:
	/*!
	@brief 2.17.���ݳ���
	@param[in] ywlx ҵ������
	@param[in] jzlx ��������
	@param[out]  strSq			����
	@param[out]  strFpmx		��Ʊ��ϸ����
	@param[out]  strFpdxx		��Ʊ����Ϣ
	@param[out]  strFphz		��Ʊ��������
	@param[out]  strSzfphz		ʱ�ӷ�Ʊ��������
	@param[out]  strQtxx		������Ϣ
	*/

//	CSjcb(CYWXML_GY &ywxml_gy, string &strSq, string &strFpmx, string &strFpdxx, string &strFphz, string &strSzfphz, string &strQtxx);
	CSjcb(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strSq, string &strFphz);
	~CSjcb();
	
	INT32 XmlBuild();
	INT32 XmlParse();

	string &m_strSq;
	string &m_strFphz;

	string m_strFpmx;
	string m_strFpdxx;
	string m_strSzfphz;
	string m_strQtxx;

	UINT8 m_jzlx;

private:
	
};


#endif























