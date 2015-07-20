 /*! \file    NETXML_WLLQFP.cpp
   \brief    ������õ��м���ӿ� ҵ��3.6 ������ȡ��Ʊ
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "NETXML_WLLQFP.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CWllqfp::CWllqfp(CYWXML_GY &ywxml_gy, CInvVol &invvol, const string &strQtxx):CYWXmlBase(ywxml_gy),\ 
m_invvol(invvol), m_strQtxx(strQtxx)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CWllqfp::~CWllqfp()
{

}

INT32 CWllqfp::XmlBuild( )
{	
	INT8 buf[256];
	memset(buf,0,sizeof(buf));
	
	//���body�ڵ�
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_RootElement, "body");
	m_pXmlConstruct.m_parentElement[1] = m_pXmlConstruct.m_NewElement;
	m_pXmlConstruct.AddAttr("skph",m_ywxml_gy.m_sksbbh);//�̺�����(���︳ֵ��˰���豸���)
	DBG_PRINT(("SKJ_WLLQFP: skph : %s", m_ywxml_gy.m_sksbbh.c_str()));
	m_pXmlConstruct.AddAttr("nsrsbh",m_ywxml_gy.m_nsrsbh);//��˰��ʶ�������
	DBG_PRINT(("SKJ_WLLQFP: nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));

	m_pXmlConstruct.AddAttr("kpjh", m_ywxml_gy.m_kpjh);
	DBG_PRINT(("SKJ_WLLQFP: kpjh : %s", m_ywxml_gy.m_kpjh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[1], "input");
	m_pXmlConstruct.m_parentElement[2] = m_pXmlConstruct.m_NewElement;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fplxdm");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_fplxdm);	//��Ʊ���ʹ���
	DBG_PRINT(("SKJ_WLLQFP: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fpdm");
	m_pXmlConstruct.AddText(m_invvol.m_code);	//��Ʊ����
	DBG_PRINT(("SKJ_WLLQFP: fpdm : %s", m_invvol.m_code.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fpqshm");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%u", m_invvol.m_isno);
	m_pXmlConstruct.AddText(buf);			//��Ʊ��ʼ����
	DBG_PRINT(("SKJ_WLLQFP: fpqshm : %s",buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fpzzhm");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%u", m_invvol.m_ieno);
	m_pXmlConstruct.AddText(buf);			//��Ʊ��ֹ����
	DBG_PRINT(("SKJ_WLLQFP: fpzzhm : %s",buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "zfs");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%u", m_invvol.m_fpzfs);
	m_pXmlConstruct.AddText(buf);			//��Ʊ�ܷ���
	DBG_PRINT(("SKJ_WLLQFP: zfs : %s",buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "qtxx");
	m_pXmlConstruct.AddText(m_strQtxx);	//������Ϣ
	DBG_PRINT(("SKJ_WLLQFP: qtxx : %s", m_strQtxx.c_str()));

	return XML_SUCCESS;
}

INT32 CWllqfp::XmlParse( )
{
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = m_pXmlParse.GetText();		//��Ʊ���ʹ���
	DBG_PRINT(("SKJ_WLLQFP: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fpdm");
	m_invvol.m_code = m_pXmlParse.GetText();		//��Ʊ����
	DBG_PRINT(("SKJ_WLLQFP: fpdm = %s", m_invvol.m_code.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "qshm");
	m_invvol.m_isno = atoi(m_pXmlParse.GetText().c_str());		//��Ʊ��ʼ����
	DBG_PRINT(("SKJ_WLLQFP: qshm = %u", m_invvol.m_isno));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "zzhm");
	m_invvol.m_ieno = atoi(m_pXmlParse.GetText().c_str());		//��Ʊ��ֹ����
	DBG_PRINT(("SKJ_WLLQFP: zzhm = %u", m_invvol.m_ieno));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fpfs");
	m_invvol.m_fpzfs = atoi(m_pXmlParse.GetText().c_str());		//��Ʊ����
	DBG_PRINT(("SKJ_WLLQFP: fpfs = %u", m_invvol.m_fpzfs));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "lgrq");
	m_invvol.m_date = atoi(m_pXmlParse.GetText().c_str());		//�칺����(��ʱ�Թ������ڴ���)
	DBG_PRINT(("SKJ_WLLQFP: lgrq = %u", m_invvol.m_date));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "gpxxmw");
	m_invvol.m_fpjmw = m_pXmlParse.GetText();		//��Ʊ��Ϣ����(��Ӧ��Ʊ������Ϣ)
	DBG_PRINT(("SKJ_WLLQFP: gpxxmw = %s", m_invvol.m_fpjmw.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();		//���ش���
	DBG_PRINT(("SKJ_WLLQFP: returncode = %s", m_retInfo.m_retCode.c_str()));	

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();		//������Ϣ
	DBG_PRINT(("SKJ_WLLQFP: returnmsg = %s", m_retInfo.m_retMsg.c_str()));	
	
	return XML_SUCCESS;
}


