/*! \file    YWXML_JKSJCX.cpp
   \brief    ������õ��м���ӿ� ҵ��: ������ݲ�ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_JKSJCX.h"
#include "base64.h"
#include "arithmetic.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CJksjcx::CJksjcx(CYWXML_GY &ywxml_gy,CInvKind &InvKind):m_InvKind(InvKind), CYWXmlBase(ywxml_gy)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CJksjcx::~CJksjcx()
{

}


INT32 CJksjcx::XmlBuild()
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
	DBG_PRINT(("m_ywxml_gy.m_nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbbh);
	DBG_PRINT(("m_ywxml_gy.m_sksbbh : %s", m_ywxml_gy.m_sksbbh.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbkl");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbkl);
	DBG_PRINT(("m_ywxml_gy.m_sksbkl : %s", m_ywxml_gy.m_sksbkl.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fplxdm");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_fplxdm);
	DBG_PRINT(("m_ywxml_gy.m_fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));
	
	return XML_SUCCESS;
}



INT32 CJksjcx::XmlParse()
{
	INT8 Buf[64];

	//���body�ڵ�
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fplxdm");
	m_InvKind.m_fplxdm = m_pXmlParse.GetText();
	DBG_PRINT(("m_InvKind.m_fplxdm : %s", m_InvKind.m_fplxdm.c_str()));
	
	//��Ʊ����ʱ��
// 	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "kpjzsj");
// 	m_pXmlParse.GetText("");
// 	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));

	//���ݱ�����ʼ����
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "bsqsrq");
	m_InvKind.m_bsqsrq = m_pXmlParse.GetText();
	DBG_PRINT(("m_InvKind.m_bsqsrq  : %s", m_InvKind.m_bsqsrq .c_str()));

	//���ݱ��ͽ�ֹ����
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "bszzrq");
	m_InvKind.m_bszzrq = m_pXmlParse.GetText();
	DBG_PRINT(("m_InvKind.m_bszzrq  : %s", m_InvKind.m_bszzrq .c_str()));

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "dzkpxe");
	m_InvKind.m_maxSign = double2int(atof(m_pXmlParse.GetText().c_str())*SUM_EXTENSION);			//�ӽ�˰�̶�ȡ�Ľ�� ��λ����
	DBG_PRINT(("m_InvKind.m_maxSign : %lld", m_InvKind.m_maxSign));

	//���±�˰����
// 	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "zxbsrq");
// 	m_UserInfo.m_zxbsrq = m_pXmlParse.GetText();
// 	DBG_PRINT(("m_UserInfo.m_zxbsrq  : %s", m_UserInfo.m_zxbsrq .c_str()));

	//ʣ������
// 	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "syrl");
// 	m_pXmlParse.GetText("");

	//�ϴ���ֹ����
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "scjzrq");
	m_InvKind.m_Lxssr = atoi(m_pXmlParse.GetText().c_str());
	DBG_PRINT(("m_InvKind.m_Lxssr  : %u", m_InvKind.m_Lxssr));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "lxkpsc");
	m_InvKind.m_Lxkjsj = atoi(m_pXmlParse.GetText().c_str());
	DBG_PRINT(("m_InvKind.m_Lxkjsj  : %u", m_InvKind.m_Lxkjsj));

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "lxzsljje");
	m_InvKind.m_maxSum = double2int(atof(m_pXmlParse.GetText().c_str())*SUM_EXTENSION);
	DBG_PRINT(("m_InvKind.m_maxSum  : %lld", m_InvKind.m_maxSum));

	//������չ��Ϣ
// 	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "lxkzxx");
// 	m_pXmlParse.GetText("");
// 	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));
	
	//�Զ�����Ϣ
// 	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "zdyxx");
// 	m_pXmlParse.GetText("");
// 	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();
	DBG_PRINT(("returncode : %s", m_retInfo.m_retCode.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();
	DBG_PRINT(("returnmsg : %s", m_retInfo.m_retMsg.c_str()));
	
	return XML_SUCCESS;
	
}






