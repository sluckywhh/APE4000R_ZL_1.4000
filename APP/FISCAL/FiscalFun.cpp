/*! \file    FiscalFun.h
   \brief    ����˰��ͨ�ú���
   \author   zl
   \version  1.0
   \date     2008-01-01
 */

#include "FiscalFun.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#include "CInvKind.h"
#include "CUserInfo.h"
#include "CUserMore.h"
#include "CTax.h"
#include "CSysArg.h"
#include "CGlobalArg.h"
#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "SysArgMac.h"
#include "TDateTime.h"
#include "ManageBusinessFunc.h"
#include "YWXMLGY.h"
#include "APIBase.h"
#include "YWXmlBase.h"

void FSC_InvDateHex(UINT32 date, UINT32 time, UINT8 *hexInvDate)
{
	UINT8 day = 0;
	UINT8 month = 0;
	UINT16 year = 0;
	UINT8 hour = 0, minute = 0, second = 0;
	UINT32 decInvDate;
	UINT32 temp_year = 0, temp_month = 0, temp_day = 0;
	UINT32 temp_hour = 0, temp_minute = 0, temp_second = 0;
	
	TDateTime Date(date, time);
	Date.DecodeDate(temp_year, temp_month, temp_day);
	year = temp_year;
	month = temp_month;
	day = temp_day;
	
	Date.DecodeTime(temp_hour,temp_minute,temp_second);
	hour = temp_hour;
	minute = temp_minute;
	second = temp_second;
	
	year %= 100;
	decInvDate = year*1048576 + month*65536 + day*2048 + hour*64 + minute;
	
	int2hex(hexInvDate, decInvDate, 4);
}

//---------------------------------------------------------------------------
//��ʼ����ں���
//---------------------------------------------------------------------------

UINT8 FSC_InitProc(const string &strOldPsw, const string &strNewPsw, string &strErr)
{
	DBG_PRINT(("����FSC_InitProc����"));

	UINT8 retcode=0;
	CSysArg sysArg;
	char sqlbuf[256];
	CaProgressBar proBar("");

	//1.��ȡ��˰����Ϣ����˰��ʱ��
	proBar.SetText("��ȡ��˰����Ϣ��...");
	proBar.Show();
	retcode = FSC_GetNsrInfo(strErr);
	if (retcode != SUCCESS)
	{
		DBG_PRINT(("��˰����Ϣ��ʼ��ʧ�ܣ�%s",strErr.c_str()));
		return FAILURE;
	}
	g_globalArg->m_corpInfo->Requery();
	g_globalArg->m_corpInfo->LoadOneRecord();
	DBG_PRINT(("m_corpInfo->m_Kpjhm : %u", g_globalArg->m_corpInfo->m_Kpjhm));


	//2.��ȡ��Ȩ˰��
	proBar.SetText("��ȡ��Ȩ˰����...");
	proBar.Show();
	retcode = FSC_GetTaxInfo(strErr);
	if (retcode != SUCCESS)
	{
		DBG_PRINT(("��Ȩ˰�ʳ�ʼ��ʧ�ܣ�%s",strErr.c_str()));
		return FAILURE;
	}

#if 0
	//3.��ȡ��˰�̺ͱ�˰�̲�����Ϣ
	//��˰�̲�����Ϣ����FSC_GetNsrInfo()�����л�ȡ���浽��userinfo�����У�
	//�����Ҫ��⣬�轫��Щ������userinfoת�Ƶ�usermore����
	proBar.SetText("��ȡ��˰�̡���˰�̲�����Ϣ��...");
	proBar.Show();
	retcode = FSC_GetJSKInfo(strErr);	
	if (retcode != SUCCESS)
	{
		DBG_PRINT(("�̲�����Ϣ��ʼ��ʧ�ܣ�%s",strErr.c_str()));
		return FAILURE;
	}
	g_globalArg->m_usermore->Requery();
	g_globalArg->m_usermore->LoadOneRecord();
#endif

	//4.��ȡ��˰�����߿�����Ϣ
	proBar.SetText("��ȡ���߿�����Ϣ...");
	proBar.Show();
	retcode =FSC_GetInvKindInfo(strErr);
	if (retcode != SUCCESS)
	{
		DBG_PRINT(("���߿�����Ϣ��ʼ��ʧ�ܣ�%s",strErr.c_str()));
		return FAILURE;
	}
	g_globalArg->m_invKind->Requery();	
	g_globalArg->m_invKind->LoadOneRecord();


	//5.���³�ʼ�����ڡ���ʼ����ʶ�Լ�update���ڲ�����ϵͳ������Sysarg
	// 	proBar.SetText("���³�ʼ�����ںͱ�ʶ��...");
	// 	proBar.Show();
	DBG_PRINT(("���³�ʼ��ʱ����..."));
	g_globalArg->m_initDate = TDateTime::CurrentDateTime().FormatInt();
	DBG_PRINT(("m_initDate=%d", g_globalArg->m_initDate));
	memset(sqlbuf,0,sizeof(sqlbuf));
	sprintf(sqlbuf, "update SYSARG set V_INT = %u where SA_ID = %d",
		g_globalArg->m_initDate, SYS_INIT_DATE);
	sysArg.SetSQL(sqlbuf);
	if (sysArg.ExecuteSQL() != SQLITE_OK)
	{
		strErr = "���³�ʼ��ʱ��ʧ��";	
		DBG_PRINT(("���³�ʼ��ʱ��ʧ��"));
		return FAILURE;
	}
	DBG_PRINT(("���³�ʼ��ʱ��ɹ�"));

// 	DBG_PRINT(("����updateʱ����..."));
// 	g_globalArg->m_updateDate = g_globalArg->m_initDate;
// 	sprintf(sqlbuf, "update SYSARG set V_INT = %u where SA_ID = %d",
// 		g_globalArg->m_updateDate, SYS_INFO_UPDATE_DATE);
// 	sysArg.SetSQL(sqlbuf);
// 	if (sysArg.ExecuteSQL() != SQLITE_OK)
// 	{
// 		strErr = "����updateʱ��ʧ��";
// 		DBG_PRINT(("����updateʱ��ʧ��"));
// 		return FAILURE;
// 	}
// 	DBG_PRINT(("����updateʱ��ɹ�"));
	
	DBG_PRINT(("���³�ʼ����ʶ��..."));
	memset(sqlbuf,0,sizeof(sqlbuf));	
	sprintf(sqlbuf, "update SYSARG set V_INT = %u where SA_ID = %d",\
		1, SYS_MACHINE_INIT_FLAG);
	sysArg.SetSQL(sqlbuf);
	if (sysArg.ExecuteSQL() != SQLITE_OK)
	{
		strErr = "���³�ʼ����ʶʧ��";
		DBG_PRINT(("���³�ʼ����ʶʧ��"));
		return FAILURE;
	}
	DBG_PRINT(("���³�ʼ����ʶ�ɹ�"));

	DBG_PRINT(("����֤�������..."));
	memset((void*)sqlbuf, 0 ,sizeof(sqlbuf));
	sprintf(sqlbuf, "UPDATE SYSARG SET V_TEXT = '%s' where SA_ID = %d", strNewPsw.c_str(), SYS_CERTIF_PSW);
	sysArg.SetSQL(sqlbuf);
	if (sysArg.ExecuteSQL() != SQLITE_OK)
	{
		strErr = "����֤�����ʧ��";
		DBG_PRINT(("����֤�����ʧ��"));
		return FAILURE;
	}
	DBG_PRINT(("����֤�����ɹ�"));

	//���Ľ�˰����֤�����
	INT32 retAPI = g_pAPIBase->BGZSKL_API(*g_YwXmlArg, strOldPsw, strNewPsw, strErr);
	if (retAPI != SUCCESS)
	{
		DBG_PRINT(("֤��������ʧ�ܣ�%s",strErr.c_str()));

		memset(sqlbuf,0,sizeof(sqlbuf));	
		sprintf(sqlbuf, "update SYSARG set V_INT = %u where SA_ID = %d", 0, SYS_MACHINE_INIT_FLAG);
		sysArg.SetSQL(sqlbuf);
		sysArg.ExecuteSQL();
		memset((void*)sqlbuf, 0 ,sizeof(sqlbuf));
		sprintf(sqlbuf, "UPDATE SYSARG SET V_TEXT = '%s' where SA_ID = %d", strOldPsw.c_str(), SYS_CERTIF_PSW);
		sysArg.SetSQL(sqlbuf);
		sysArg.ExecuteSQL();

		return FAILURE;
	}
	DBG_PRINT(("֤�������ĳɹ�"));


	//����֤�����
	g_globalArg->m_strZskl = strNewPsw;
	g_YwXmlArg->m_zskl = g_globalArg->m_strZskl;
	//���³�ʼ����־
	g_globalArg->m_initFlag = 1;


	CaMsgBox::ShowMsg("������ʼ���ɹ�");

	DBG_PRINT(("�˳�FSC_InitProc����"));

	return SUCCESS;
}

UINT8 FSC_GetNsrInfo(string &strErr)
{
	DBG_PRINT(("����FSC_GetNsrInfo����"));

	INT32 ret=0;
	CUserInfo userinfo;//��˰�˻�����Ϣ
	string strCurtime("");//�ӽ�˰�̻�õĵ�ǰʱ��

	//��ȡ��˰����Ϣ&&��˰��ʱ��
	DBG_PRINT(("��ȡ��˰����Ϣ��..."));

	ret = g_pAPIBase->GetTaxpayerInfo_API(*g_YwXmlArg, userinfo, strCurtime, strErr);

	if (ret != SUCCESS)
	{
		DBG_PRINT(("��˰����Ϣ��ȡʧ��"));
	 	return FAILURE;
	}/**/
	DBG_PRINT(("��˰����Ϣ��ȡ�ɹ�"));

// 	g_YwXmlArg->m_bspbh = "bspbh4444444444";			//��˰�̱��
// 	g_YwXmlArg->m_bspkl = "bspkl12345678";			//��˰�̿���

	g_YwXmlArg->m_nsrsbh = userinfo.m_Nsrsbh;		//��˰��ʶ���
	g_YwXmlArg->m_nsrmc = userinfo.m_Nsrmc;			//��˰������
	g_YwXmlArg->m_fplxdm = userinfo.m_fplxdm;		//��Ʊ���ʹ���
	g_YwXmlArg->m_sksbbh =userinfo.m_Jspsbh;		//˰���豸���
	INT8 tempkpjh[8];
	memset(tempkpjh, 0, sizeof(tempkpjh));
	sprintf(tempkpjh, "%u", userinfo.m_Kpjhm);
	g_YwXmlArg->m_kpjh = tempkpjh;		//��Ʊ����

	DBG_PRINT(("g_YwXmlArg->m_nsrsbh : %s", g_YwXmlArg->m_nsrsbh.c_str()));
	DBG_PRINT(("g_YwXmlArg->m_nsrmc : %s", g_YwXmlArg->m_nsrmc.c_str()));
	DBG_PRINT(("g_YwXmlArg->m_fplxdm : %s", g_YwXmlArg->m_fplxdm.c_str()));
	DBG_PRINT(("g_YwXmlArg->m_kpjh : %s", g_YwXmlArg->m_kpjh.c_str()));


	//����˰����Ϣ�������ݿ�useinfo����
	DBG_PRINT(("��˰����Ϣ�洢��..."));
	userinfo.Delete();//���userinfo��
	ret = userinfo.AddNew();	
	if (ret != SQLITE_OK)
	{
		strErr = "��˰����Ϣ�洢ʧ��";
		DBG_PRINT(("��˰����Ϣ�洢ʧ��"));
		return FAILURE;
	}
	DBG_PRINT(("��˰����Ϣ�洢�ɹ�"));

	//ͬ�����ʱ��
	DBG_PRINT(("ͬ�����ʱ����..."));
	if(strCurtime.length()>=14)
	{
	string strDate = strCurtime.substr(0,8);
	string strTime = strCurtime.substr(8);
	UINT32 tmpDate = (UINT32)atoi(strDate.c_str());
	UINT32 tmpTime = (UINT32)atoi(strTime.c_str());	
	TDateTime tmpDateTime(tmpDate, tmpTime);
	if ( TDateTime::SetCurrentDateTime(tmpDateTime))
	{	
		DBG_PRINT(("ͬ�����ʱ��ɹ�"));
	}
	else
	{
		DBG_PRINT(("ͬ�����ʱ��ʧ��"));
		return FAILURE;
	}
	}
	else
	{
		DBG_PRINT(("��ȡ��ǰʱ�䲻�Ϸ�"));
		return FAILURE;
	}

	DBG_PRINT(("�˳�FSC_GetNsrInfo����"));

	return SUCCESS;			
}

UINT8 FSC_GetTaxInfo(string &strErr)
{	
	DBG_PRINT(("����FSC_GetTaxInfo����"));
	
	INT32 ret=0;
	CTax pTax[MAX_TAX_NUM];//��Ȩ˰��
	UINT8 chTaxNum = MAX_TAX_NUM;//��Ȩ˰�ʸ���

	DBG_PRINT(("��Ȩ˰�ʻ�ȡ��..."));

	ret = g_pAPIBase->GetTaxRateInfo_API(*g_YwXmlArg, pTax, chTaxNum, strErr);

	if (ret != SUCCESS)
	{
		DBG_PRINT(("��Ȩ˰�ʻ�ȡʧ��"));
		return FAILURE;
	}/**/
	DBG_PRINT(("��Ȩ˰�ʻ�ȡ�ɹ�"));
	
	//����Ȩ˰�ʴ������ݿ�TAX����
	DBG_PRINT(("��Ȩ˰�ʴ洢��..."));
	DBG_ASSERT_EXIT((pTax != NULL), (" pTax == NULL!"));
	DBG_PRINT(("chTaxNum= %u",chTaxNum));
	
	pTax[0].Delete();//���TAX��
    for (int i=0; i<chTaxNum;i++)
	{
		//DBG_PRINT(("&(pTax[%d])= 0x%x", i, &(pTax[i])));
		
		ret= pTax[i].AddNew();
		if (ret != SQLITE_OK)
		{
			strErr = "��Ȩ˰�ʴ洢ʧ��";
			DBG_PRINT(("��Ȩ˰�ʴ洢ʧ��"));
			return FAILURE;
		}	
	}	
	DBG_PRINT(("��Ȩ˰�ʴ洢�ɹ�"));

	DBG_PRINT(("�˳�FSC_GetTaxInfo����"));
	
	return SUCCESS;			

}

UINT8 FSC_GetInvKindInfo(string &strErr)
{
	DBG_PRINT(("����FSC_GetInvKindInfo����"));

	INT32 ret=0;
	CInvKind pInvKind;//���߿�����Ϣ

	//��ȡ���߿�����Ϣ
	//��Ȼ��˰�����ж��ֶ�Ӧ��ͬ��Ʊ���͵�������Ϣ
	//��ÿ��ֻ���ݲ�ѯ�ķ�Ʊ���ʹ���ȡ����Ӧ��һ��������Ϣ
	//���øú���ǰ������ȷg_YwXmlArg�е�fplxdm
	DBG_PRINT(("���߿�����Ϣ��ȡ��..."));

 	ret = g_pAPIBase->GetJKSJ_API(*g_YwXmlArg, pInvKind, strErr);

	if (ret != SUCCESS)
	{
		DBG_PRINT(("��˰�����߿�����Ϣ��ȡʧ��"));
	 	return FAILURE;
 	}/**/
	DBG_PRINT(("���߿�����Ϣ��ȡ�ɹ�"));

	DBG_PRINT(("pInvKind.m_fplxdm : %s", pInvKind.m_fplxdm.c_str()));
	DBG_PRINT(("pInvKind.m_bsqsrq  : %s", pInvKind.m_bsqsrq .c_str()));
	DBG_PRINT(("pInvKind.m_bszzrq  : %s", pInvKind.m_bszzrq .c_str()));
// 	DBG_PRINT(("pInvKind.m_maxSign : %lld", pInvKind.m_maxSign));
// 	DBG_PRINT(("pInvKind.m_Lxssr  : %u", pInvKind.m_Lxssr));
// 	DBG_PRINT(("pInvKind.m_Lxkjsj  : %u", pInvKind.m_Lxkjsj));
// 	DBG_PRINT(("pInvKind.m_maxSum  : %lld", pInvKind.m_maxSum));

	//�����߿�����Ϣ�������ݿ�invkind����
	DBG_PRINT(("���߿�����Ϣ�洢��..."));

	pInvKind.Delete();//���invkind��
	ret= pInvKind.AddNew();
	DBG_PRINT(("!!!!!!!!!!!!!!ret = %d", ret));
	if (ret != SQLITE_OK)
	{
		strErr = "���߿�����Ϣ�洢ʧ��";
		DBG_PRINT(("���߿�����Ϣ�洢ʧ��"));
		return FAILURE;
	}	
	DBG_PRINT(("���߿�����Ϣ�洢�ɹ�"));
	
	DBG_PRINT(("�˳�FSC_GetInvKindInfo����"));

	return SUCCESS;			
}

UINT8 FSC_GetJSKInfo(string &strErr)
{
	INT32 ret=0;
	CUserMore usermore;//��˰�˲�����Ϣ���洢��˰�̺ͱ�˰�̲�����Ϣ
	
	//��ȡ��˰�̺ͱ�˰�̲�����Ϣ(����ͬ����˰��ʱ��)
	
	/*INT32 ret=CJSKInfoFunc::GetTaxCardInfo(&m_userInfo,strErr);
	if (ret !=JSK_SUCCESS)
	{
	 	DBG_PRINT(("��Ȩ˰�ʴ洢ʧ��"));
	 	return FAILURE;
	 }*/

	//������Ϣ�������ݿ�usermore����
	usermore.Delete();//���usermore��
	ret = usermore.AddNew();	
	if (ret != SQLITE_OK)
	{
		strErr = "�̲�����Ϣ�洢ʧ��";
		DBG_PRINT(("�̲�����Ϣ�洢ʧ��"));
		return FAILURE;
	}
	DBG_PRINT(("�̲�����Ϣ�洢�ɹ�"));

	return SUCCESS;	
}

UINT8 FSC_InfoUpdate(string &strErr)
{
	UINT8 retcode=0;
	CSysArg sysArg;
	char sqlbuf[256];

	//1.������˰����Ϣ	
	DBG_PRINT(("��˰����Ϣ����"));	
	CaProgressBar proBar("");
	proBar.SetText("��˰����Ϣ������...");
	proBar.Show();
	retcode = FSC_GetNsrInfo(strErr);
	if (retcode != SUCCESS)
	{
		return FAILURE;
	}
	g_globalArg->m_corpInfo->Requery();
	g_globalArg->m_corpInfo->LoadOneRecord();

	//2.������Ȩ˰��
	DBG_PRINT(("��Ȩ˰�ʸ���"));	
	proBar.SetText("��Ȩ˰�ʸ�����...");
	proBar.Show();
	retcode = FSC_GetTaxInfo(strErr);
	if (retcode != SUCCESS)
	{
		return FAILURE;
	}

	//3.�������߿�����Ϣ	
	DBG_PRINT(("���߿�����Ϣ����"));	
	proBar.SetText("���߿�����Ϣ������...");
	proBar.Show();
	retcode =FSC_GetInvKindInfo(strErr);
	if (retcode != SUCCESS)
	{
		return FAILURE;
	}
// 	CaProgressBar proBar3("��Ʊ����Ϣ��...");
// 	proBar3.Show();
	g_globalArg->m_invKind->Requery();
	INT32 errorcode = g_globalArg->m_invKind->LoadOneRecord();
	if (SQLITE_OK != errorcode)
	{
		memset((void*)sqlbuf, 0, sizeof(sqlbuf));
		sprintf(sqlbuf, "��Ʊ����Ϣ����%u", errorcode);
		strErr = sqlbuf;
		return FAILURE;
	}
	DBG_PRINT(("m_invKind->m_maxSum = %lld",g_globalArg->m_invKind->m_maxSum));
	DBG_PRINT(("g_globalArg->m_invKind->m_bsqsrq= %s",g_globalArg->m_invKind->m_bsqsrq.c_str()));

	return SUCCESS;
}

// UINT8 FSC_CheckDeclare(string &strErr)
// {
// 
// 	string curDate ="";
// 	curDate=TDateTime::CurrentDate().FormatString(YYYYMMDD);
// 	DBG_PRINT(("curDate= %s",curDate.c_str()));
// 
// 	string bsqsDate="";
// 	DBG_PRINT(("g_globalArg->m_invKind->m_bsqsrq= %s",g_globalArg->m_invKind->m_bsqsrq.c_str()));
// 	bsqsDate=g_globalArg->m_invKind->m_bsqsrq;
//     DBG_PRINT(("bsqsDate= %s",bsqsDate.c_str()));
//     bsqsDate=g_globalArg->m_invKind->m_bsqsrq.substr(0,8);
//     DBG_PRINT(("bsqsDate= %s",bsqsDate.c_str()));
// 
// 	if (curDate == bsqsDate)
// 	{
// 		strErr ="�������������㣬����쳭��";
// 		return FAILURE;
// 	}
// 
// 
// 	return SUCCESS;
// }


void FSC_NetDeclare()
{
	string strErr("");
	CaMsgBox msgBox("�Ƿ����糭��?",CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
	{
		return ;
	}

	CaProgressBar proBar("���糭����.....");
	proBar.Show();

	INT32 nRet = g_pAPIBase->NetDeclareProc_API(*g_YwXmlArg, strErr);
	DBG_PRINT(("nRet= %d",nRet));
	
	if (nRet != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
	}
	else
	{
		CaMsgBox::ShowMsg("���糭���ɹ�");
	}

	return ;
}

void FSC_DiskDeclare(UINT8 uJZlx)
{
	string strMsge("");
	if (1==uJZlx)
	{
		strMsge = "��˰�̳�����....";
	}
	else if (2==uJZlx)
	{
		strMsge = "��˰�̳�����....";
	}
	else
	{
		CaMsgBox::ShowMsg("�������ʹ���");
		return;
	}
	
	CaProgressBar proBar("");
	proBar.SetText(strMsge.c_str());
	proBar.Show();
	
    string strErr("");
	INT32 nRet = g_pAPIBase->DeclareProc_API(*g_YwXmlArg,uJZlx, strErr);
	DBG_PRINT(("nRet= %d",nRet));

	if (nRet != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
	}
	else
	{
		CaMsgBox::ShowMsg("���ʳ�˰�ɹ�");
	}

	return ;

}

void FSC_NetUpdateTax()
{
	string strErr("");
	CaMsgBox msgBox("�Ƿ������忨?",CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
	{
		return ;
	}
	
	CaProgressBar proBar("�����忨��.....");
	proBar.Show();
	
	INT32 nRet = g_pAPIBase->NetUpdateTaxProc_API(*g_YwXmlArg, strErr);
	if (nRet != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
	}
	else
	{
		CaMsgBox::ShowMsg("�����忨�ɹ�");
	}
	
	return ;
}

void FSC_DiskUpdateTax()
{
	string strErr("");
	CaMsgBox msgBox("�Ƿ��������?",CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
	{
		return ;
	}
	
	CaProgressBar proBar("��˰�����������.....");
	proBar.Show();
	
	INT32 nRet = g_pAPIBase->UpdateTaxProc_API(*g_YwXmlArg, strErr);

	if (nRet != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
	}
	else
	{
		CaMsgBox::ShowMsg("��������ɹ�");
	}
	
	return ;
}

UINT8 FSC_ChangeDiskPsw(string strOldPsw, string strNewPsw,string &strErr)
{
	CSysArg sysArg;
	INT8 chValue[128];
	memset((void*)chValue, 0 ,sizeof(chValue));

	sprintf(chValue, "where SA_ID = %d", SYS_DISK_PSW);
	sysArg.m_filter.append(chValue);
	sysArg.Requery();
	sysArg.LoadOneRecord();

	if (sysArg.m_vText != strOldPsw)
	{
		strErr="�ɿ����������";
	    return FAILURE;
	}

	CaProgressBar proBar("��˰�̿����޸���.....");
	proBar.Show();

	UINT32 ret = 0; 
	ret = g_pAPIBase->SKPKLBG_API(*g_YwXmlArg, strOldPsw, strNewPsw, strErr);
	if (ret != SUCCESS)
	{
		memset((void*)chValue, 0 ,sizeof(chValue));
		sprintf(chValue, "UPDATE SYSARG SET V_TEXT = '%s' where SA_ID = %d", strOldPsw.c_str(), SYS_DISK_PSW);
		sysArg.SetSQL(chValue);
		sysArg.ExecuteSQL();

		return FAILURE;
	}
	
	memset((void*)chValue, 0 ,sizeof(chValue));
	sprintf(chValue, "UPDATE SYSARG SET V_TEXT = '%s' where SA_ID = %d", strNewPsw.c_str(), SYS_DISK_PSW);
	sysArg.SetSQL(chValue);
	INT32 nRetCode = sysArg.ExecuteSQL();
	if (SQLITE_OK != nRetCode)
	{
		strErr="�޸Ŀ�����󣬸������ݿ����";
		return FAILURE;
	}

	CaMsgBox::ShowMsg("��˰�̿����޸ĳɹ�");

	return SUCCESS;
}


UINT8 FSC_FpblProc(UINT32 SDate, UINT32 EDate, string &strErr)
{
	DBG_PRINT(("����FSC_FpblProc����"));
	
	INT32 ret=0;

	DBG_PRINT(("��Ʊ��¼��..."));
	
	ret = g_pAPIBase->Fpbl_API(*g_YwXmlArg, SDate, EDate, strErr);
	
	if (ret != SUCCESS)
	{
		DBG_PRINT(("��Ʊ��¼ʧ��"));
		return FAILURE;
	}/**/
	DBG_PRINT(("��Ʊ��¼�ɹ�"));
	return SUCCESS;
}