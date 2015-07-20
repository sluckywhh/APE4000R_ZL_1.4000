/*! \file    YWXML_BGZSKL.cpp
   \brief    ������õ��м���ӿ� ҵ��: ���֤�����
   \author   lzh
   \version  1.0
   \date     2015 
*/

#include "YWXML_BGZSKL.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CBgzskl::CBgzskl(CYWXML_GY &ywxml_gy, string yzskl, string xzskl): m_yzskl(yzskl), m_xzskl(xzskl), CYWXmlBase(ywxml_gy)

{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CBgzskl::~CBgzskl()
{

}

INT32 CBgzskl::XmlBuild()
{
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_RootElement, "body");
	m_pXmlConstruct.m_parentElement[1] = m_pXmlConstruct.m_NewElement;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[1], "input");
	m_pXmlConstruct.m_parentElement[2] = m_pXmlConstruct.m_NewElement;
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "yzskl");
	m_pXmlConstruct.AddText(m_yzskl);	
	DBG_PRINT(("m_yzskl : %s", m_yzskl.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "xzskl");
	m_pXmlConstruct.AddText(m_xzskl);	
	DBG_PRINT(("m_xzskl : %s", m_xzskl.c_str()));
	return XML_SUCCESS;
}

INT32 CBgzskl::XmlParse()
{
	
	//���body�ڵ�
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();
	DBG_PRINT(("returncode : %s", m_retInfo.m_retCode.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();
	DBG_PRINT(("returnmsg : %s", m_retInfo.m_retMsg.c_str()));
	
	return XML_SUCCESS;

}





