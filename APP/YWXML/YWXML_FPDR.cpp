 /*! \file    YWXML_FPDR.cpp
   \brief    ������õ��м���ӿ� ҵ��2.23.��Ʊ����
   \author   YY
   \version  1.0
   \date     2015
 */

#include "YWXML_FPDR.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CFpdr::CFpdr(CYWXML_GY &ywxml_gy, UINT8 strJzlx):CYWXmlBase(ywxml_gy), m_strJzlx(strJzlx)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CFpdr::~CFpdr()
{

}

INT32 CFpdr::XmlBuild( )
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
	DBG_PRINT(("SKJ_FPDR: jpbh : %s", m_ywxml_gy.m_jqbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "nsrsbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_nsrsbh);	//��˰��ʶ���
	DBG_PRINT(("SKJ_FPDR: nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "jzlx");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%u", m_strJzlx);
	m_pXmlConstruct.AddText(buf);	//��������
	DBG_PRINT(("SKJ_FPDR: jzlx : %s", buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "bspbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_bspbh);	//��˰�̱��
	DBG_PRINT(("SKJ_FPDR: bspbh : %s", m_ywxml_gy.m_bspbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "bspkl");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_bspkl);	//��˰�̿���
	DBG_PRINT(("SKJ_FPDR: bspkl : %s", m_ywxml_gy.m_bspkl.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbbh);	//˰���豸���
	DBG_PRINT(("SKJ_FPDR: sksbbh : %s", m_ywxml_gy.m_sksbbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbkl");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbkl);	//˰���豸����
	DBG_PRINT(("SKJ_FPDR: sksbkl : %s", m_ywxml_gy.m_sksbkl.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fplxdm");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_fplxdm);	//��Ʊ���ʹ���
	DBG_PRINT(("SKJ_FPDR: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	return XML_SUCCESS;
}

INT32 CFpdr::XmlParse( )
{
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();		//���ش���
	DBG_PRINT(("SKJ_FPDR: returncode = %s", m_retInfo.m_retCode.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();		//������Ϣ
	DBG_PRINT(("SKJ_FPDR: returnmsg = %s", m_retInfo.m_retMsg.c_str()));	
	
	return XML_SUCCESS;
}


