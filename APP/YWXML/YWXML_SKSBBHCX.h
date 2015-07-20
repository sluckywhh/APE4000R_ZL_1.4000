/*! \file    YWXML_SKSBBHCX.h
   \brief    ������õ��м���ӿ� ҵ��2.1 ˰���豸��Ų�ѯ
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_SKSBBHCX_H
#define YWXML_SKSBBHCX_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


/**
 *@class CSksbbhcx
 *@brief 2.1.˰���豸��Ų�ѯ
 */
class CSksbbhcx : public CYWXmlBase
{


public:

	/*!
	@brief 2.1.˰���豸��Ų�ѯ
	@param[in] ywlx ҵ������
	@param[out] sksbbh ˰���豸���
	@param[out] sksbbh ��˰�̱��
	*/
	CSksbbhcx(CYWXML_GY &ywxml_gy, string &sksbbh, string &bspbh, string &qtxx);
	~CSksbbhcx();
	
	/*!
	@brief ˰���豸��Ų�ѯ�����������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*!
	@brief ˰���豸��Ų�ѯ�������������������XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse();
	string &m_sksbbh;
	string &m_bspbh;
	string &m_qtxx;

private:
	
		
};


#endif



