/*! \file    NETXML_WLLQFPJGQR.cpp
   \brief    ������õ��м���ӿ� ҵ��3.7 ������ȡ��Ʊ���ȷ��
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "NETXML_WLLQFPJGQR.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CWllqfpjgqr::CWllqfpjgqr(CYWXML_GY &ywxml_gy, CInvVol &invvol, string &strQtxx):CYWXmlBase(ywxml_gy),\
m_invvol(invvol), m_strQtxx(strQtxx)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CWllqfpjgqr::~CWllqfpjgqr()
{

}

INT32 CWllqfpjgqr::XmlBuild( )
{
	INT8 buf[256];
	memset(buf,0,sizeof(buf));
	
	//���body�ڵ�
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_RootElement, "body");
	m_pXmlConstruct.m_parentElement[1] = m_pXmlConstruct.m_NewElement;
	m_pXmlConstruct.AddAttr("skph",m_ywxml_gy.m_sksbbh);//�̺�����(���︳ֵ��˰���豸���)
	DBG_PRINT(("SKJ_WLLQFPJGQR: skph : %s", m_ywxml_gy.m_sksbbh.c_str()));
	m_pXmlConstruct.AddAttr("nsrsbh",m_ywxml_gy.m_nsrsbh);//��˰��ʶ�������
	DBG_PRINT(("SKJ_WLLQFPJGQR: nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[1], "input");
	m_pXmlConstruct.m_parentElement[2] = m_pXmlConstruct.m_NewElement;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fplxdm");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_fplxdm);	//��Ʊ���ʹ���
	DBG_PRINT(("SKJ_WLLQFPJGQR: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fpdm");
	m_pXmlConstruct.AddText(m_invvol.m_code);	//��Ʊ����
	DBG_PRINT(("SKJ_WLLQFPJGQR: fpdm : %s", m_invvol.m_code.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "qshm");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%u", m_invvol.m_isno);
	m_pXmlConstruct.AddText(buf);			//��Ʊ��ʼ����
	DBG_PRINT(("SKJ_WLLQFPJGQR: qshm : %s",buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "zzhm");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%u", m_invvol.m_ieno);
	m_pXmlConstruct.AddText(buf);			//��Ʊ��ֹ����
	DBG_PRINT(("SKJ_WLLQFPJGQR: zzhm : %s",buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "qtxx");
	m_pXmlConstruct.AddText(m_strQtxx);	//������Ϣ
	DBG_PRINT(("SKJ_WLLQFPJGQR: qtxx : %s", m_strQtxx.c_str()));
	
	return XML_SUCCESS;
}

INT32 CWllqfpjgqr::XmlParse( )
{
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = m_pXmlParse.GetText();		//��Ʊ���ʹ���
	DBG_PRINT(("SKJ_WLLQFPJGQR: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "gpxxjgqr");
	m_invvol.m_fpjjsmw = m_pXmlParse.GetText();		//��Ʊ��Ϣ���ȷ��(��Ӧ��Ʊ���������)
	DBG_PRINT(("SKJ_WLLQFPJGQR: gpxxjgqr = %s", m_invvol.m_fpjjsmw.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();		//���ش���
	DBG_PRINT(("SKJ_WLLQFPJGQR: returncode = %s", m_retInfo.m_retCode.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();		//������Ϣ
	DBG_PRINT(("SKJ_WLLQFPJGQR: returnmsg = %s", m_retInfo.m_retMsg.c_str()));	
	
	return XML_SUCCESS;
}


