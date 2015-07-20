 /*! \file    YWXML_SKSBBHCX.cpp
   \brief    ������õ��м���ӿ� ҵ��2.1 ˰���豸��Ų�ѯ
   \author   YY
   \version  1.0
   \date     2015
 */

#include "YWXML_SKSBBHCX.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CSksbbhcx::CSksbbhcx(CYWXML_GY &ywxml_gy, string &sksbbh, string &bspbh, string &qtxx):
					m_sksbbh(sksbbh), m_bspbh(bspbh), m_qtxx(qtxx),CYWXmlBase(ywxml_gy)
{
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CSksbbhcx::~CSksbbhcx()
{

}

INT32 CSksbbhcx::XmlBuild()
{
	//���body�ڵ�
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_RootElement, "body");
	m_pXmlConstruct.m_parentElement[1] = m_pXmlConstruct.m_NewElement;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[1], "input");
	m_pXmlConstruct.m_parentElement[2] = m_pXmlConstruct.m_NewElement;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "jqbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_jqbh);
	DBG_PRINT(("m_ywxml_gy.m_jqbh : %s", m_ywxml_gy.m_jqbh.c_str()));
	
	return XML_SUCCESS;
}

INT32 CSksbbhcx::XmlParse()
{
	//���body�ڵ�
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "sksbbh");
	m_sksbbh = m_pXmlParse.GetText();
	DBG_PRINT(("sksbbh : %s", m_sksbbh.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "bspbh");
	m_bspbh = m_pXmlParse.GetText();
	DBG_PRINT(("bspbh : %s", m_bspbh.c_str()));

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "qtxx");
	m_qtxx = m_pXmlParse.GetText();
	DBG_PRINT(("m_qtxx : %s", m_qtxx.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();
	DBG_PRINT(("returncode : %s", m_retInfo.m_retCode.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();
	DBG_PRINT(("returnmsg : %s", m_retInfo.m_retMsg.c_str()));
	
	return XML_SUCCESS;
}



