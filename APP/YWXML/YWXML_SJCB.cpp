/*! \file    YWXML_SJCB.cpp
   \brief    ������õ��м���ӿ� ҵ��2.17���ݳ���
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "YWXML_SJCB.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
// CSjcb::CSjcb(CYWXML_GY &ywxml_gy, string &strSq, string &strFpmx, string &strFpdxx, string &strFphz, string &strSzfphz, string &strQtxx):CYWXmlBase(ywxml_gy),\
// m_strSq(strSq), m_strFpmx(strFpmx), m_strFpdxx(strFpdxx), m_strFphz(strFphz), m_strSzfphz(strSzfphz), m_strQtxx(strQtxx)
// {
// 	
// }

CSjcb::CSjcb(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strSq, string &strFphz):CYWXmlBase(ywxml_gy), m_jzlx(jzlx), m_strSq(strSq), m_strFphz(strFphz)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CSjcb::~CSjcb()
{

}

INT32 CSjcb::XmlBuild()
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
	DBG_PRINT(("SKJ_SJCB: jpbh : %s", m_ywxml_gy.m_jqbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "nsrsbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_nsrsbh);	//��˰��ʶ���
	DBG_PRINT(("SKJ_SJCB: nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbbh);	//˰���豸���
	DBG_PRINT(("SKJ_SJCB: sksbbh : %s", m_ywxml_gy.m_sksbbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbkl");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbkl);	//˰���豸����
	DBG_PRINT(("SKJ_SJCB: sksbkl : %s", m_ywxml_gy.m_sksbkl.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fplxdm");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_fplxdm);	//��Ʊ���ʹ���
	DBG_PRINT(("SKJ_SJCB: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "jzlx");
	sprintf(buf, "%u", m_jzlx);
	m_pXmlConstruct.AddText(buf);	//��������
	DBG_PRINT(("SKJ_SJCB: buf : %s", buf));

	return XML_SUCCESS;
}

INT32 CSjcb::XmlParse( )
{
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "sq");
	m_strSq = m_pXmlParse.GetText();		//����
	DBG_PRINT(("SKJ_SJCB: sq = %s", m_strSq.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fpmx");
	m_strFpmx = m_pXmlParse.GetText();		//��Ʊ��ϸ����
	DBG_PRINT(("SKJ_SJCB: fpmx = %s", m_strFpmx.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fpdxx");
	m_strFpdxx = m_pXmlParse.GetText();		//��Ʊ����Ϣ
	DBG_PRINT(("SKJ_SJCB: fpdxx = %s", m_strFpdxx.c_str()));

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fphz");
	m_strFphz = m_pXmlParse.GetText();		//��Ʊ��������
	DBG_PRINT(("SKJ_SJCB: fphz = %s", m_strFphz.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "szfphz");
	m_strSzfphz = m_pXmlParse.GetText();		//ʱ�ӷ�Ʊ��������
	DBG_PRINT(("SKJ_SJCB: szfphz = %s", m_strSzfphz.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "qtxx");
	m_strQtxx = m_pXmlParse.GetText();		//������Ϣ
	DBG_PRINT(("SKJ_SJCB: qtxx = %s", m_strQtxx.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();		//���ش���
	DBG_PRINT(("SKJ_SJCB: returncode = %s", m_retInfo.m_retCode.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();		//������Ϣ
	DBG_PRINT(("SKJ_SJCB: returnmsg = %s", m_retInfo.m_retMsg.c_str()));	

	return XML_SUCCESS;
}


