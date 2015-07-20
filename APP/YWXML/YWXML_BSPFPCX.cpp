 /*! \file    YWXML_BSPFPCX.cpp
   \brief    ������õ��м���ӿ� ҵ��2.14��Ʊ��ѯ
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "YWXML_BSPFPCX.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"

CInvVolInfo::CInvVolInfo()
{
	m_InvvolCount = 0;
// 	for (int i=0; i<INVVOL_MAX_NUM ;i++)
// 	{
// 		m_InvVol[i].ResetVol();
// 	}

}

CInvVolInfo::~CInvVolInfo()
{
	
}

//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CBspfpcx::CBspfpcx(CYWXML_GY &ywxml_gy, CInvVolInfo &invvolinfo):CYWXmlBase(ywxml_gy), m_invvolinfo(invvolinfo)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CBspfpcx::~CBspfpcx()
{

}

INT32 CBspfpcx::XmlBuild( )
{
	//���body�ڵ�
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_RootElement, "body");
	m_pXmlConstruct.m_parentElement[1] = m_pXmlConstruct.m_NewElement;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[1], "input");
	m_pXmlConstruct.m_parentElement[2] = m_pXmlConstruct.m_NewElement;
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "jqbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_jqbh);	//˰���տ�����
	DBG_PRINT(("SKJ_BSPFPCX: jpbh : %s", m_ywxml_gy.m_jqbh.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "nsrsbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_nsrsbh);	//��˰��ʶ���
	DBG_PRINT(("SKJ_BSPFPCX: nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "bspbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbbh);	//˰���豸���
	DBG_PRINT(("SKJ_BSPFPCX: sksbbh : %s", m_ywxml_gy.m_sksbbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "bspkl");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbkl);	//˰���豸����
	DBG_PRINT(("SKJ_BSPFPCX: sksbkl : %s", m_ywxml_gy.m_sksbkl.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fplxdm");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_fplxdm);	//��Ʊ���ʹ���
	DBG_PRINT(("SKJ_BSPFPCX: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	return XML_SUCCESS;
}

INT32 CBspfpcx::XmlParse( )
{
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = m_pXmlParse.GetText();		//��Ʊ���ʹ���
	DBG_PRINT(("SKJ_BSPFPCX: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fpdxx");
	m_pXmlParse.m_parentElement[3] = m_pXmlParse.m_Child;
	m_invvolinfo.m_InvvolCount = atoi(m_pXmlParse.GetAttr("count").c_str());//��Ʊ���ѯ����
	DBG_PRINT(("SKJ_BSPFPCX: fpdxx_count = %u", m_invvolinfo.m_InvvolCount));

	for (INT32 temp_i=0; temp_i<m_invvolinfo.m_InvvolCount; temp_i++)
	{
		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[3], "group", temp_i);
		m_pXmlParse.m_parentElement[4] = m_pXmlParse.m_Child;
		
		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[4], "fpdm");
		m_invvolinfo.m_InvVol[temp_i].m_code = m_pXmlParse.GetText();	//��Ʊ����
		DBG_PRINT(("SKJ_BSPFPCX: m_InvVol[%d].code = %s", temp_i,m_invvolinfo.m_InvVol[temp_i].m_code.c_str()));
		
		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[4], "qshm");
		m_invvolinfo.m_InvVol[temp_i].m_isno = atoi(m_pXmlParse.GetText().c_str());	//��Ʊ��ʼ����
		DBG_PRINT(("SKJ_BSPFPCX: m_InvVol[%d].qshm = %u", temp_i, m_invvolinfo.m_InvVol[temp_i].m_isno));
		
		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[4], "zzhm");
		m_invvolinfo.m_InvVol[temp_i].m_ieno = atoi(m_pXmlParse.GetText().c_str());	//��Ʊ��ֹ����
		DBG_PRINT(("SKJ_BSPFPCX: m_InvVol[%d].zzhm = %u", temp_i, m_invvolinfo.m_InvVol[temp_i].m_ieno));

		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[4], "fpfs");
		m_invvolinfo.m_InvVol[temp_i].m_fpzfs = atoi(m_pXmlParse.GetText().c_str());	//��Ʊ����
		DBG_PRINT(("SKJ_BSPFPCX: m_InvVol[%d].fpfs = %u", temp_i, m_invvolinfo.m_InvVol[temp_i].m_fpzfs));

		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[4], "syfs");
		m_invvolinfo.m_InvVol[temp_i].m_remain = atoi(m_pXmlParse.GetText().c_str());	//ʣ�����
		DBG_PRINT(("SKJ_BSPFPCX: m_InvVol[%d].syfs = %u", temp_i, m_invvolinfo.m_InvVol[temp_i].m_remain));

		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[4], "lgrq");
		m_invvolinfo.m_InvVol[temp_i].m_date = atoi(m_pXmlParse.GetText().c_str());	//�칺����
		DBG_PRINT(("SKJ_BSPFPCX: m_InvVol[%d].lgrq = %u", temp_i, m_invvolinfo.m_InvVol[temp_i].m_date));

// 		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[4], "lgry");
// 		m_strLgry = m_pXmlParse.GetText();	//�칺��Ա
// 		DBG_PRINT(("SKJ_BSPFPCX: lgry = %s", m_strLgry.c_str()));
	}

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();		//���ش���
	DBG_PRINT(("SKJ_BSPFPCX: returncode = %s", m_retInfo.m_retCode.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();		//������Ϣ
	DBG_PRINT(("SKJ_BSPFPCX: returnmsg = %s", m_retInfo.m_retMsg.c_str()));	
	
	return XML_SUCCESS;
}

