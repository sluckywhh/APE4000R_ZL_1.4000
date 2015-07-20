 /*! \file    NETXML_LXXXSC.cpp
   \brief    ������õ��м���ӿ� ҵ��3.5 ������Ϣ�ϴ�
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "NETXML_LXXXSC.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CLxxxsc::CLxxxsc(CYWXML_GY &ywxml_gy, CInvKind &invkind, string &strQtxx, string &strLxkzxx):CYWXmlBase(ywxml_gy),\
m_invkind(invkind), m_strQtxx(strQtxx), m_strLxkzxx(strLxkzxx)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CLxxxsc::~CLxxxsc()
{

}

INT32 CLxxxsc::XmlBuild( )
{
	INT8 buf[256];
	memset(buf,0,sizeof(buf));
	float fRate = 1.0;
	
	//���body�ڵ�
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_RootElement, "body");
	m_pXmlConstruct.m_parentElement[1] = m_pXmlConstruct.m_NewElement;
	m_pXmlConstruct.AddAttr("skph",m_ywxml_gy.m_sksbbh);//�̺�(���︳ֵ��˰���豸���)����
	DBG_PRINT(("SKJ_LXXXSC: skph : %s", m_ywxml_gy.m_sksbbh.c_str()));
	m_pXmlConstruct.AddAttr("nsrsbh", m_ywxml_gy.m_nsrsbh);//��˰��ʶ���
	DBG_PRINT(("SKJ_LXXXSC: nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));
	m_pXmlConstruct.AddAttr("kpjh", m_ywxml_gy.m_kpjh);
	DBG_PRINT(("kpjh : %s", m_ywxml_gy.m_kpjh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[1], "input");
	m_pXmlConstruct.m_parentElement[2] = m_pXmlConstruct.m_NewElement;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "scjzrq");
	sprintf(buf, "%u", m_invkind.m_Lxssr);
	m_pXmlConstruct.AddText(buf);	//�ϴ���ֹ����
	DBG_PRINT(("SKJ_LXXXSC: scjzrq : %s", buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "lxkpsc");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%u", m_invkind.m_Lxkjsj);
	m_pXmlConstruct.AddText(buf);	//���߿�Ʊʱ��(Сʱ)
	DBG_PRINT(("SKJ_LXXXSC: lxkpsc : %s", buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "lxzsljje");
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%.2f", ((double)m_invkind.m_maxSum * fRate)/SUM_EXTENSION);
	m_pXmlConstruct.AddText(buf);	//���������ۼƽ��(��λС��)
	DBG_PRINT(("SKJ_LXXXSC: lxzsljje : %s", buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "qtxx");
	m_pXmlConstruct.AddText(m_strQtxx);	//������Ϣ
	DBG_PRINT(("SKJ_LXXXSC: qtxx : %s", m_strQtxx.c_str()));

	return XML_SUCCESS;
}

INT32 CLxxxsc::XmlParse( )
{
	INT32 temp_count = 0;//������Ϣ��Ŀ����
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;
	temp_count = atoi(m_pXmlParse.GetAttr("count").c_str());//������Ϣ����
	DBG_PRINT(("SKJ_LXXXSC: count = %d", temp_count));
// 	m_ywxml_gy.m_sksbbh = m_pXmlParse.GetAttr("skph");//�̺�����,����˰���豸��Ŵ���
// 	DBG_PRINT(("SKJ_LXXXSC: skph = %s", m_ywxml_gy.m_sksbbh.c_str()));
// 	m_ywxml_gy.m_nsrsbh = m_pXmlParse.GetAttr("nsrsbh");//��˰��ʶ�������
// 	DBG_PRINT(("SKJ_LXXXSC: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();		//���ش���
	DBG_PRINT(("SKJ_LXXXSC: returncode = %s", m_retInfo.m_retCode.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();		//������Ϣ
	DBG_PRINT(("SKJ_LXXXSC: returnmsg = %s", m_retInfo.m_retMsg.c_str()));	

// 	if ( m_retInfo.m_retCode =="-101")
// 	{
// 		return  XML_INTERNAL_ERR_NO;
// 	}

	for (INT32 temp_i=0; temp_i < temp_count;temp_i++)
	{
		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "group",temp_i);
		m_pXmlParse.m_parentElement[3] = m_pXmlParse.m_Child;

		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[3], "fplxdm");
		m_ywxml_gy.m_fplxdm = m_pXmlParse.GetText();		//��Ʊ���ʹ���
		DBG_PRINT(("SKJ_LXXXSC: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[3], "lxkzxx");
		m_strLxkzxx = m_pXmlParse.GetText();		//���߿�����Ϣ
		DBG_PRINT(("SKJ_LXXXSC: lxkzxx = %s", m_strLxkzxx.c_str()));
		
	}
	
	return XML_SUCCESS;
}


