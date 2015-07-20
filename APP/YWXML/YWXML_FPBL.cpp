 /*! \file    YWXML_FPBL.cpp
   \brief    ������õ��м���ӿ� ҵ��2.28.��Ʊ��¼
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "YWXML_FPBL.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CFpbl::CFpbl(CYWXML_GY &ywxml_gy, UINT32 StartDate, UINT32 EndDate):CYWXmlBase(ywxml_gy), m_StartDate(StartDate), m_EndDate(EndDate)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CFpbl::~CFpbl()
{

}

INT32 CFpbl::XmlBuild( )
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
	DBG_PRINT(("SKJ_FPBL: jpbh : %s", m_ywxml_gy.m_jqbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "nsrsbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_nsrsbh);	//��˰��ʶ���
	DBG_PRINT(("SKJ_FPBL: nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbbh);	//˰���豸���
	DBG_PRINT(("SKJ_FPBL: sksbbh : %s", m_ywxml_gy.m_sksbbh.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbkl");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbkl);	//˰���豸����
	DBG_PRINT(("SKJ_FPBL: sksbkl : %s", m_ywxml_gy.m_sksbkl.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fplxdm");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_fplxdm);	//��Ʊ���ʹ���
	DBG_PRINT(("SKJ_FPBL: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "bsqsrq");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%u", m_StartDate);
	m_pXmlConstruct.AddText(buf);	//��˰��ʼ����
	DBG_PRINT(("SKJ_FPBL: bsqsrq : %s", buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "bsjzrq");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%u", m_EndDate);
	m_pXmlConstruct.AddText(buf);	//��˰��ֹ����
	DBG_PRINT(("SKJ_FPBL: bsjzrq : %s", buf));

	return XML_SUCCESS;
}

INT32 CFpbl::XmlParse( )
{
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();		//���ش���
	DBG_PRINT(("SKJ_FPBL: returncode = %s", m_retInfo.m_retCode.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();		//������Ϣ
	DBG_PRINT(("SKJ_FPBL: returnmsg = %s", m_retInfo.m_retMsg.c_str()));	
	
	return XML_SUCCESS;
}


