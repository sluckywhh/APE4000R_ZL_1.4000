/*! \file     YWXML_GPXXCX.cpp
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��Ϣ��ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_GPXXCX.h"
// #include "JSKMakeInvoice.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CGpxxcx::CGpxxcx(CYWXML_GY &ywxml_gy, CInvVol &InvVol):m_InvVol(InvVol), CYWXmlBase(ywxml_gy)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CGpxxcx::~CGpxxcx()
{

}


INT32 CGpxxcx::XmlBuild()
{
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_RootElement, "body");
	m_pXmlConstruct.m_parentElement[1] = m_pXmlConstruct.m_NewElement;
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[1], "input");
	m_pXmlConstruct.m_parentElement[2] = m_pXmlConstruct.m_NewElement;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "jqbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_jqbh);
	DBG_PRINT(("m_ywxml_gy.m_jqbh : %s", m_ywxml_gy.m_jqbh.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "nsrsbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_nsrsbh);	
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbbh);	
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbkl");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbkl);	
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fplxdm");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_fplxdm);		
	
	return XML_SUCCESS;
}

INT32 CGpxxcx::XmlParse()
{
	INT8 Buf[64];
	//���body�ڵ�
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fplxdm");
	m_InvVol.m_fplxdm = m_pXmlParse.GetText();
	m_InvVol.m_invtype = (UINT8)atoi(m_pXmlParse.GetText().c_str());
	DBG_PRINT(("m_InvVol.m_invtype : %u", m_InvVol.m_invtype));
	DBG_PRINT(("m_InvVol.m_fplxdm : %s", m_InvVol.m_fplxdm.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "dqfpdm");
	m_InvVol.m_code = m_pXmlParse.GetText();
	DBG_PRINT(("m_InvVol.m_code : %s", m_InvVol.m_code.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "dqfphm");
	m_InvVol.m_curInvNo = atoi(m_pXmlParse.GetText().c_str());
	DBG_PRINT(("m_InvVol.m_curInvNo : %u", m_InvVol.m_curInvNo));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "zsyfs");	//ʣ�����
	m_InvVol.m_remain = atoi(m_pXmlParse.GetText().c_str());
	DBG_PRINT(("m_InvVol.m_remain : %u", m_InvVol.m_remain));

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();
	DBG_PRINT(("returncode : %s", m_retInfo.m_retCode.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();
	DBG_PRINT(("returnmsg : %s", m_retInfo.m_retMsg.c_str()));
	
	return XML_SUCCESS;

}




