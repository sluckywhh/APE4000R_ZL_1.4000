/*! \file     YWXML_FPKJ.cpp
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ����
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_FPKJ.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CFpkj::CFpkj(CYWXML_GY &ywxml_gy, CInvHead &InvInfo):m_InvInfo(InvInfo), CYWXmlBase(ywxml_gy)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CFpkj::~CFpkj()
{

}


INT32 CFpkj::XmlBuild()
{
	INT8 Buf[64];
	UINT8 i = 0;
	UINT8 tmpFplx = 0;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_RootElement, "body");
	m_pXmlConstruct.m_parentElement[1] = m_pXmlConstruct.m_NewElement;
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[1], "input");
	m_pXmlConstruct.m_parentElement[2] = m_pXmlConstruct.m_NewElement;

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "jqbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_jqbh);
	DBG_PRINT(("m_ywxml_gy.m_jqbh : %s", m_ywxml_gy.m_jqbh.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "zskl");
	m_pXmlConstruct.AddText(m_InvInfo.m_zskl);
	DBG_PRINT(("m_ywxml_gy.m_jqbh : %s", m_InvInfo.m_zskl.c_str()));

	//������λʶ���
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "xhdwdm");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_nsrsbh);	
	DBG_PRINT(("m_ywxml_gy.xhdwdm == %s", m_ywxml_gy.m_nsrsbh.c_str()));

	//������λ����
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "xhdwmc");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_nsrmc);	
	DBG_PRINT(("m_ywxml_gy.xhdwmc == %s", m_ywxml_gy.m_nsrmc.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbbh");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbbh);	
	DBG_PRINT(("m_ywxml_gy.sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sksbkl");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_sksbkl);	
	DBG_PRINT(("m_ywxml_gy.sksbkl == %s", m_ywxml_gy.m_sksbkl.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "fplxdm");
	m_pXmlConstruct.AddText(m_ywxml_gy.m_fplxdm);	
	DBG_PRINT(("m_ywxml_gy.fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));

	if(m_InvInfo.m_kplx == NORMAL_INV)
		tmpFplx = 0;
	else if(m_InvInfo.m_kplx == RETURN_INV)
		tmpFplx = 1;
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "kplx");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%u", tmpFplx);
	m_pXmlConstruct.AddText(Buf);
	DBG_PRINT(("m_ywxml_gy.kplx == %s", Buf));

// 	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "hyfl");
// 	m_pXmlConstruct.AddText(m_InvInfo.m_hyfl);	
// 	DBG_PRINT(("m_InvInfo.m_hyfl== %s", m_InvInfo.m_hyfl.c_str()));

	//������λʶ���
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "ghdwdm");
	m_pXmlConstruct.AddText(m_InvInfo.m_fkdwsh);	
	DBG_PRINT(("m_InvInfo.m_fkdwsh == %s", m_InvInfo.m_fkdwsh.c_str()));
	//������λ����
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "ghdwmc");
	m_pXmlConstruct.AddText(m_InvInfo.m_fkdw);	
	DBG_PRINT(("m_InvInfo.m_fkdw == %s", m_InvInfo.m_fkdw.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "sfxm");
	m_pXmlConstruct.m_parentElement[3] = m_pXmlConstruct.m_NewElement;
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%u", m_InvInfo.m_sphsl);
	m_pXmlConstruct.AddAttr("count", Buf);
	
	CInvDet *pInvDet = m_InvInfo.pHead;
	for (i=1; i<=m_InvInfo.m_sphsl; i++, pInvDet = pInvDet->pNext)
	{
		//�õ�group�ڵ�
		m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[3], "group");
		m_pXmlConstruct.m_parentElement[4] = m_pXmlConstruct.m_NewElement;
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", i);
		m_pXmlConstruct.AddAttr("xh", Buf);

		m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[4], "xm");
		m_pXmlConstruct.AddText(pInvDet->m_spmc);	
		DBG_PRINT(("pInvDet->m_spmc == %s", pInvDet->m_spmc.c_str()));

		m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[4], "dj");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.3lf", pInvDet->m_dj);//����˰����
		m_pXmlConstruct.AddText(Buf);
		DBG_PRINT(("pInvDet->m_dj == %s", Buf));

		m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[4], "sl");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.3lf", pInvDet->m_spsl);
		m_pXmlConstruct.AddText(Buf);
		DBG_PRINT(("pInvDet->m_spsl == %s", Buf));

		m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[4], "je");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvDet->m_je)/SUM_EXTENSION);//����˰���
		m_pXmlConstruct.AddText(Buf);
		DBG_PRINT(("pInvDet->m_je == %s", Buf));

		m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[4], "zsl");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2f", pInvDet->m_sl);
		m_pXmlConstruct.AddText(Buf);
		DBG_PRINT(("pInvDet->m_sl == %s", Buf));

		m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[4], "se");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvDet->m_spse)/SUM_EXTENSION);//˰��
		m_pXmlConstruct.AddText(Buf);
		DBG_PRINT(("pInvDet->m_spse == %s", Buf));

		m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[4], "hsdj");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.3lf", pInvDet->m_spdj);//��˰����
		m_pXmlConstruct.AddText(Buf);
		DBG_PRINT(("pInvDet->m_spdj == %s", Buf));
		
		m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[4], "hsje");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvDet->m_spje)/SUM_EXTENSION);//��˰���
		m_pXmlConstruct.AddText(Buf);
		DBG_PRINT(("pInvDet->m_spje == %s", Buf));

	}
	m_InvInfo.m_kpje = m_InvInfo.m_kphjje-m_InvInfo.m_kpse;//��Ʊ���  ����˰
	DBG_PRINT(("m_InvInfo.m_kpje == %lld", m_InvInfo.m_kpje));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "hjje");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%.2lf", ((double)m_InvInfo.m_kpje)/SUM_EXTENSION);
	m_pXmlConstruct.AddText(Buf);
	DBG_PRINT(("pInvDet->m_hjje == %s", Buf));

	DBG_PRINT(("m_InvInfo.m_kpse == %lld", m_InvInfo.m_kpse));
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "hjse");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%.2lf", ((double)(m_InvInfo.m_kpse))/SUM_EXTENSION);
	m_pXmlConstruct.AddText(Buf);
	DBG_PRINT(("pInvDet->m_hjse == %s", Buf));

	DBG_PRINT(("m_InvInfo.m_kphjje == %lld", m_InvInfo.m_kphjje));
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "jshj");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%.2lf", ((double)(m_InvInfo.m_kphjje)/SUM_EXTENSION));//��˰�ϼ�
	m_pXmlConstruct.AddText(Buf);
	DBG_PRINT(("pInvDet->m_kphjje == %s", Buf));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "bz");
	m_pXmlConstruct.AddText(m_InvInfo.m_backup1);	

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "skr");//�м����ʹ��m_sky����
	m_pXmlConstruct.AddText(m_InvInfo.m_sky);	
	DBG_PRINT(("m_InvInfo.m_sky == %s", m_InvInfo.m_sky.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "kpr");//�м���в��ٽ���
	m_pXmlConstruct.AddText(m_InvInfo.m_sky);	
	DBG_PRINT(("m_InvInfo.m_sky == %s", m_InvInfo.m_sky.c_str()));

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "yfpdm");
	m_pXmlConstruct.AddText(m_InvInfo.m_yfpdm);	

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "yfphm");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%u", m_InvInfo.m_yfphm);
	m_pXmlConstruct.AddText(Buf);

	return XML_SUCCESS;
}

INT32 CFpkj::XmlParse()
{
	//���body�ڵ�
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fplxdm");
	m_InvInfo.m_fplb = (UINT8)atoi(m_pXmlParse.GetText().c_str());
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fpdm");
	m_InvInfo.m_fpdm = m_pXmlParse.GetText();
	DBG_PRINT(("m_InvInfo.m_fpdm : %s", m_InvInfo.m_fpdm.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "fphm");
	m_InvInfo.m_fphm = atoi(m_pXmlParse.GetText().c_str());
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "kprq");	
	string strDate="";
	strDate = m_pXmlParse.GetText();
        DBG_PRINT(("strDate : %s", strDate.c_str()));
	DBG_PRINT(("strDate_len : %u", strDate.length()));
	if (strDate.length()>=14)
	{
	m_InvInfo.m_kprq = atoi((strDate.substr(0, 8)).c_str());
	m_InvInfo.m_kpsj = atoi((strDate.substr(8, 6)).c_str());
	}
	DBG_PRINT(("m_InvInfo.m_kprq= %u",m_InvInfo.m_kprq));
	DBG_PRINT(("m_InvInfo.m_kpsj= %u",m_InvInfo.m_kpsj));
	
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "skm");	
	m_InvInfo.m_fwm = m_pXmlParse.GetText();
	DBG_PRINT(("m_InvInfo.m_fwm : %s", m_InvInfo.m_fwm.c_str()));

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "qmz");	
	m_InvInfo.m_casign = m_pXmlParse.GetText();
	DBG_PRINT(("m_InvInfo.m_casign : %s", m_InvInfo.m_casign.c_str()));

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returncode");
	m_retInfo.m_retCode = m_pXmlParse.GetText();
	DBG_PRINT(("returncode : %s", m_retInfo.m_retCode.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "returnmsg");
	m_retInfo.m_retMsg = m_pXmlParse.GetText();
	DBG_PRINT(("returnmsg : %s", m_retInfo.m_retMsg.c_str()));
	
	return XML_SUCCESS;

}




