 /*! \file    YWXML_FPSSSC.cpp
   \brief    ������õ��м���ӿ� ҵ��2.21.��Ʊʱʱ�ϴ�
   \author   YY
   \version  1.0
   \date     2015
 */

#include "YWXML_FPSSSC.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CFpsssc::CFpsssc(CYWXML_GY &ywxml_gy, UINT32 &nFpzs, UINT8 &strCzlx, string &strInvBuf):CYWXmlBase(ywxml_gy),\
m_nFpzs(nFpzs), m_strCzlx(strCzlx), m_strInvBuf(strInvBuf)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CFpsssc::~CFpsssc()
{

}

INT32 CFpsssc::XmlBuild( )
{
	INT8 buf[256];
	memset(buf,0,sizeof(buf));
	
	//���body�ڵ�
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_RootElement, "body");
	m_pXmlConstruct.m_parentElement[1] = m_pXmlConstruct.m_NewElement;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[1], "input");
	m_pXmlConstruct.m_parentElement[2] = m_pXmlConstruct.m_NewElement;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "jqbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_jqbh);	//˰���տ�����
	DBG_PRINT(("SKJ_FPSSSC: jpbh : %s", m_ywxml_gy.m_jqbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "nsrsbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_nsrsbh);	//��˰��ʶ���
	DBG_PRINT(("SKJ_FPSSSC: nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));	

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbbh);	//˰���豸���
	DBG_PRINT(("SKJ_FPSSSC: sksbbh : %s", m_ywxml_gy.m_sksbbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbkl");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbkl);	//˰���豸����
	DBG_PRINT(("SKJ_FPSSSC: sksbkl : %s", m_ywxml_gy.m_sksbkl.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fplxdm");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_fplxdm);	//��Ʊ���ʹ���
	DBG_PRINT(("SKJ_FPSSSC: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fpzs");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%u", m_nFpzs);
	m_pXmlConstruct.AddText(buf);	//��Ʊ����
	DBG_PRINT(("SKJ_FPSSSC: fpzs : %s", buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "czlx");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%u", m_strCzlx);
	m_pXmlConstruct.AddText(buf);	//��������
	
	return XML_SUCCESS;
}

INT32 CFpsssc::XmlParse( )
{
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = m_pXmlParse.GetText();		//��Ʊ���ʹ���
	DBG_PRINT(("SKJ_FPSSSC: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "czlx");
	m_strCzlx = atoi(m_pXmlParse.GetText().c_str());		//��������
	DBG_PRINT(("SKJ_FPSSSC: czlx = %u", m_strCzlx));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fpzs");
	m_nFpzs = atoi(m_pXmlParse.GetText().c_str());		//��Ʊ����
	DBG_PRINT(("SKJ_FPSSSC: fpzs = %d", m_nFpzs));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fpmx");
	m_strInvBuf= m_pXmlParse.GetText();		//��Ʊ��ϸ
	//DBG_PRINT(("SKJ_FPSSSC: fpmx = %s", m_strInvBuf.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();		//���ش���
	DBG_PRINT(("SKJ_FPSSSC: returncode = %s", m_retInfo.m_retCode.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();		//������Ϣ
	DBG_PRINT(("SKJ_FPSSSC: returnmsg = %s", m_retInfo.m_retMsg.c_str()));	
	
	return XML_SUCCESS;
}


