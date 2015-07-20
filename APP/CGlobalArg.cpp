#include "VersionConfig.h"

#include "beep.h"
#include "TDateTime.h"
#include "commonFunc.h"
#include "CaProgressBar.h"
#include "CaMsgBox.h"
#include "command_at.h"
#include "CaIMEWin.h"

#include "SysArgMac.h"
#include "YWXMLGY.h"

#include "TemplateIndep.h"
#include "CSysArg.h"
#include "CInvHead.h"
#include "CClient.h" 
#include "CRtInv.h"
#include "CSysLog.h"
#include "CInvServ.h"
#include "CInvSum.h"
//#include "PowOffRecover.h"
//#include "SaleData.h"
#include "SerialProtocol.h"

#include "CGlobalArg.h"
#include "inter.h"
#include "PrintDriver.h"
#include "APIBase.h"
#include "VersionConfig.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CGlobalArg* CGlobalArg::m_globalArg = NULL;
CGlobalArg *g_globalArg = NULL;
extern UINT8 bidirection;

//static INT8 s_sq_wm[8*1024];	//��������� 3~5K

CGlobalArg::CGlobalArg()
{
	DBG_PRINT(("����CGlobalArg::CGlobalArg()"));
	m_corpInfo = new CUserInfo();
	m_curInvVol = new CInvVol();
	m_machine = new CMachine();
	m_operator = new COperator();
//	m_ssqsz = new CSsqsz();

	m_usermore = new CUserMore();
	m_invKind = new CInvKind();
	DBG_PRINT(("����CGlobalArg::CGlobalArg()"));
	m_prnInfo = new CPrnInfo();
	
	m_templateBuffer = templateBuffer;

	m_bootStatus = 0;
	m_declareLimitFlag = 0;
	//m_pydm = VOL_PYCODE;
	//m_kindFlag.assign(m_pydm, 2, 2);
//	DBG_PRINT(("ͬһ��ƱԴ��ʶ, %s", m_kindFlag.c_str()));
	m_sjbsfs = "10";
	m_netOn = 0;
	m_IngSegPoint = 0;
	m_allowIssue = 0;

	m_threadIn = 0;
	m_strMsg = "";       /**< ���̴߳�����Ϣ*/
	m_ifMsg = 0;        /**< �Ƿ��д�����Ϣ*/
	m_InvServNum = 0;
	m_InvServSum = 0;

	m_sendInvFlag = 0;
	m_updateDate=0;
	
	m_pthreadFlag = 0;
	m_pthreadErr = "";
	m_pthreadNsrsbh = "";
	m_pthreadJqbh = "";
	m_pthreadSksbbh = "";
	m_pthreadSksbkl = "";
	m_pthreadFplxdm = "";
	m_pthreadKpjh = "";

//	memset(s_sq_wm, 0, sizeof(s_sq_wm));
//	m_sq_wm = s_sq_wm;


	DBG_PRINT(("�˳�CGlobalArg::CGlobalArg()"));
}

CGlobalArg::~CGlobalArg()
{
	if (m_corpInfo != NULL)
	{
		delete m_corpInfo;
		m_corpInfo = NULL;
	}

	if (m_curInvVol != NULL)
	{
		delete m_curInvVol;
		m_curInvVol = NULL;
	}

	if (m_machine != NULL)
	{
		delete m_machine;
		m_machine = NULL;
	}

	if (m_operator != NULL)
	{
		delete m_operator;
		m_operator = NULL;
	}

	if (m_invKind != NULL)
	{
		delete m_invKind;
		m_invKind = NULL;
	}

	if (m_globalArg != NULL)
	{
		delete m_globalArg;
		m_globalArg = NULL;
	}
}

CGlobalArg* CGlobalArg::GetInstance()
{
	if (m_globalArg == NULL)
	{
		m_globalArg = new CGlobalArg();
	}

	DBG_RETURN(m_globalArg);
}

//--------------------------------------------------
//��ʼ����������ֵ
//--------------------------------------------------
UINT8 CGlobalArg::InitGlobalArg()
{
	DBG_PRINT(("����InitGlobalArg����"));
	
	INT8  value[256], tmpbuf[32];
	UINT8 errorcode=0;
	string tmpStr("");
	BAR_DEF();

	//��ʼ��ϵͳ����
	BAR_SHOW("ϵͳ������ʼ��...");
	InitSysArg();

	//�豣���ģ������
	info.SetText("��ȡ��ӡģ��...");
	info.ReFresh();
#if 1
	if (ReadPrintTemplate(m_templateBuffer, m_curTemplateNo, PRINT_TEMPLATE_BUF_LEN) != SUCCESS)
	{
		DBG_PRINT(("NO INVOICE TEMPLATE!!"));
		m_bootStatus = BOOT_NO_TEMPLATE;
		ShowMsg("δ��⵽��ӡģ��");
	}
	else
	{
		if (CheckTempValid() != 0)
		{
			DBG_PRINT(("INVALID TEMPLATE"));
			m_bootStatus = BOOT_INVALID_TEMPLATE;
			ShowMsg("��ȡ��ӡģ����Ч");
		}
		g_globalArg->pSaveTemplateInfo = SaveTemplate();
		g_globalArg->pSaveTemplateInfo->workMode = WORK_MODE; 
		g_globalArg->pSaveTemplateInfo->FixedModeFlag = 1; 
	}
#endif

	DBG_PRINT(("*****����ģʽ******��%u", g_globalArg->pSaveTemplateInfo->workMode));

	//��ȡ������Ϣ��ˢ������汾
	BAR_SHOW("��ȡ�����Ϣ...");
	g_globalArg->m_machine->Requery();
	g_globalArg->m_machine->LoadOneRecord();
	DBG_PRINT(("�������룺%s", g_globalArg->m_machine->m_machineNo.c_str() ));

#if RELEASE_VER
	sprintf(tmpbuf, "%.4f", SOFTWARE_VERSION);
#else
	sprintf(tmpbuf, "%.6f", SOFTWARE_VERSION);
#endif

	g_YwXmlArg->m_sksbkl = g_globalArg->m_strSksbkl;
	DBG_PRINT(("g_YwXmlArg->m_sksbkl = %s", g_YwXmlArg->m_sksbkl.c_str() ));
	g_YwXmlArg->m_zskl = g_globalArg->m_strZskl;
	DBG_PRINT(("g_YwXmlArg->m_zskl = %s", g_YwXmlArg->m_zskl.c_str() ));
	g_YwXmlArg->m_jqbh = g_globalArg->m_machine->m_machineNo;
    DBG_PRINT(("g_YwXmlArg->m_jqbh��%s", g_YwXmlArg->m_jqbh.c_str() ));

	memset((void*)value, 0, sizeof(value));
	//--------------------------------
	//��������Ѿ���ʼ����
	//--------------------------------
	if( g_globalArg->m_initFlag == 1 )
	{
		//��˰����Ϣ
		g_globalArg->m_corpInfo->Requery();
		g_globalArg->m_corpInfo->LoadOneRecord();

		g_YwXmlArg->m_nsrsbh = g_globalArg->m_corpInfo->m_Nsrsbh;
		g_YwXmlArg->m_nsrmc = g_globalArg->m_corpInfo->m_Nsrmc;
		g_YwXmlArg->m_sksbbh = g_globalArg->m_corpInfo->m_Jspsbh;
        
		//���ÿ�Ʊ����
		INT8 TempKpjh[8];
		memset(TempKpjh, 0, sizeof(TempKpjh));
		sprintf(TempKpjh, "%u", g_globalArg->m_corpInfo->m_Kpjhm);

		g_YwXmlArg->m_kpjh = TempKpjh;
		DBG_PRINT(("g_YwXmlArg->m_kpjh = %s", g_YwXmlArg->m_kpjh.c_str()));

		g_globalArg->m_curInvVol->m_curInvNo = 0;

		//�ۼ��޶��жϹ���
		BAR_SHOW("�ۼ��޶��ж�...");
		CalculateSum();

		//��ȡ�ɹ�����ļ�¼��
		BAR_SHOW("���������¼...");
		CInvHead curInvHead;
		CRtInv curRtInv;
		CInvSum curInvSum;
		m_invCount = curInvHead.GetInvHeadNum();
		m_rtInvCount = curRtInv.GetRecordNum();
		m_invSumCount = curInvSum.GetRecordNum();
		
		//xsr��ʱע�����ȴ��ڸ硪����������
		if ((m_invCount<0)||(m_rtInvCount<0))
		{
			m_invCount = 0;
			m_rtInvCount = 0;
			m_invSumCount = -9;
			//printf("xsr001\n");
			ShowMsg("ͳ�ƿɹ�����ļ�¼��ʧ��");			
		}
		//xsr��ʱע�����ȴ��ڸ硪����������


		DBG_PRINT(("m_invCount = %d", m_invCount));
		DBG_PRINT(("m_rtInvCount = %d", m_rtInvCount));
		DBG_PRINT(("m_invSumCount = %d", m_invSumCount));

		//��ȡ���ֱ�ļ�¼��
		BAR_SHOW("��ҵ����Ϣ...");
//		CPlu curPlu;
		CClient curClient;
		COperator curOperator;
//		m_pluCount = curPlu.GetRecordNum();
		m_clientCount = curClient.GetRecordNum();
		m_operatorCount = curOperator.GetRecordNum();
		if (/*(m_pluCount<0)||*/(m_clientCount<0)||(m_operatorCount<0))
		{
			m_pluCount = 0;
			m_clientCount = 0;
			m_operatorCount = 0;
			ShowMsg("ͳ���޶��ļ�¼��ʧ��");
		}
//		DBG_PRINT(("m_pluCount = %d", m_pluCount));
		DBG_PRINT(("m_clientCount = %d", m_clientCount));
		DBG_PRINT(("m_operatorCount = %d", m_operatorCount));
	}

	m_usermore->Requery();
	errorcode = m_usermore->LoadOneRecord();
	DBG_PRINT(("m_usermore errorcode = %u", errorcode));


	m_invKind->Requery();
	errorcode = m_invKind->LoadOneRecord();
	DBG_PRINT(("m_invKind errorcode = %u", errorcode));
	g_YwXmlArg->m_fplxdm = m_invKind->m_fplxdm;
	DBG_PRINT(("g_YwXmlArg->m_fplxdm= %s",g_YwXmlArg->m_fplxdm.c_str()));

#if TYPE_MODE == ZHQ_MODE
	SerialProtocol* m_serialProtocol;
	m_serialProtocol = SerialProtocol::getInstance();
	bool ret = 0;
	DBG_PRINT(("m_com2BaudRate = %u", m_com2BaudRate));
	ret = m_serialProtocol->InitPort(UART_DEV_NAME, m_com2BaudRate);
	DBG_PRINT(("ret = %u", ret));
	if (SUCCESS != ret)
	{
		ShowMsg("�򿪴���ʧ��");
	}
#endif

	DBG_PRINT(("�˳�InitGlobalArg����"));
	DBG_RETURN(SUCCESS);
}

//------------------------------------------------------
//��ʼ������ϵͳֵ
//------------------------------------------------------
UINT8 CGlobalArg::InitSysArg()
{
	DBG_PRINT(("����CGlobalArg::InitSysArg����"));
	char tmpChar[32];
	CSysArg cSysArg, *sysArg;
	sysArg = &cSysArg;
	int ret=0;

	sprintf(tmpChar,  "where SA_ID = %d", SYS_MACHINE_INIT_FLAG);
	sysArg->m_filter.append(tmpChar);
	ret = sysArg->Requery();
	DBG_PRINT(("ret : %u", ret));
	ret = sysArg->LoadOneRecord();
	DBG_PRINT(("ret : %u", ret));
	m_initFlag = sysArg->m_vInt;
	DBG_PRINT(("m_initFlag : %u", m_initFlag));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_INIT_DATE);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_initDate = sysArg->m_vInt;
	DBG_PRINT(("m_initDate : %lu", m_initDate));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_INV_DELIVER_FLAG);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_invDeliverFlag = sysArg->m_vInt;
	DBG_PRINT(("m_invDeliverFlag : %u", m_invDeliverFlag));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_DECLARE_FLAG);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_decFlag = sysArg->m_vInt;
	DBG_PRINT(("m_decFlag : %u", m_decFlag));

// 	sprintf(tmpChar,  "where SA_ID = %d", SYS_INV_REVOKE_FLAG);
// 	sysArg->m_filter.append(tmpChar);
// 	sysArg->Requery();
// 	sysArg->LoadOneRecord();
// 	m_startDecDate = sysArg->m_vInt;
	m_startDecDate =20991230;  //����û���걨
	DBG_PRINT(("m_startDecDate : %lu", m_startDecDate));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_BLOCKAGE_DATE);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_decDate = sysArg->m_vInt;					//xsr ���ʣ�������Ϊɶ��m_decDate��
	DBG_PRINT(("m_decDate : %lu", m_decDate));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_UNREGISTER_FLAG);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_forbidDaySum = sysArg->m_vInt;			//xsr ���ʣ�ע��״̬Ϊɶ��m_forbidDaySum��
	DBG_PRINT(("m_forbidDaySum : %lu", m_forbidDaySum));

//	sprintf(tmpChar,  "where SA_ID = %d", SYS_FJH);
//	sysArg->m_filter.append(tmpChar);
//	sysArg->Requery();
//	sysArg->LoadOneRecord();
//	m_fjh = sysArg->m_vInt;
// 	DBG_PRINT(("m_fjh : %u", m_fjh));

	//-------------------------------------------------------
	// SYSARG�����Ӷ����Ʋ��֣����ڿɰ����λ���string���洢
	//-------------------------------------------------------
	sprintf(tmpChar,  "where SA_ID = %d", SYS_CUR_TEMPLATE_NO);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_curTemplateNo = sysArg->m_vInt;
	DBG_PRINT(("m_curTemplateNo : %lu", m_curTemplateNo));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_DEFAULT_PAYER_NAME);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_defaultPayerName = sysArg->m_vText;
	DBG_PRINT(("m_defaultPayerName : %s", m_defaultPayerName.c_str()));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_COM1_BAUD_RATE);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_com1BaudRate = sysArg->m_vInt;
	DBG_PRINT(("m_com1BaudRate : %lu", m_com1BaudRate));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_COM2_BAUD_RATE);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_com2BaudRate = sysArg->m_vInt;
	DBG_PRINT(("m_com2BaudRate : %lu", m_com2BaudRate));

	sprintf(tmpChar,  "where SA_ID = %d", ZHQ_COM_BAUD_RATE);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_zhqcomBaudRate = sysArg->m_vInt;
	DBG_PRINT(("m_zhqcomBaudRate : %lu", m_zhqcomBaudRate));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_SALE_MODE);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_saleMode = sysArg->m_vInt;
	DBG_PRINT(("m_saleMode : %u", m_saleMode));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_HW_TYPE);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	g_nHWType = sysArg->m_vInt;//�ò�����CaIMEWin�ж��岢ʹ��
	DBG_PRINT(("g_nHWType : %lu", g_nHWType));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_BIDIRECTION_PRINT);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();

 	m_bidirection = sysArg->m_vInt;
 	DBG_PRINT(("m_bidirection : %lu", m_bidirection)); 
	bidirection = m_bidirection;
	PrinterIni(bidirection);

	//֤�����
	sprintf(tmpChar,  "where SA_ID = %d", SYS_CERTIF_PSW);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_strZskl = sysArg->m_vText;
	DBG_PRINT(("m_strZskl : %s", m_strZskl.c_str()));

	
	//˰���豸(��˰��)����
	sprintf(tmpChar,  "where SA_ID = %d", SYS_DISK_PSW);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_strSksbkl = sysArg->m_vText;
	DBG_PRINT(("m_strSksbkl : %s", m_strSksbkl.c_str()));

	
	DBG_PRINT(("�˳�CGlobalArg::InitSysArg����"));
	DBG_RETURN(SUCCESS);
}

UINT8 CGlobalArg::CalculateSum()
{
	DBG_ENTER("CGlobalArg::CalculateSum");
/*
	INT64 curNormalSum = 0;//������Ʊ�ۼƽ��
	INT64 curReturnSum = 0;//���պ�Ʊ�ۼƽ��  */
	m_normalSum = 0;
	m_returnSum = 0;
//	m_normalVolSum = 0;
//	m_returnVolSum = 0;

	string strTmp;
	char chValue[256], chTmpValue[64];
	CInvHead *pInvHead, invHead;
//	CDaySum  *pDaySum, daySum;

//	pDaySum = &daySum;
	pInvHead = &invHead;

	DBG_ASSERT_EXIT((pInvHead != NULL), (" pInvHead == NULL"));

	//-----------------------------------------------------------------
	// ����ÿ�µ���Ʊ�ۼƽ��ͺ�Ʊ�ۼƽ��
	//-----------------------------------------------------------------
	TDateTime curDate = TDateTime::CurrentDate();
	DBG_PRINT(("m_startDecDate = %ld", curDate.FormatInt()));

	TDateTime beginDate = curDate.MonthBegin(curDate);//���µ�һ��
	TDateTime endDate = curDate.MonthEnd(curDate);//�������һ��

	UINT32 beginDay = beginDate.FormatInt();
	UINT32 endDay = endDate.FormatInt();
	
	

	memset((void*)chValue, 0, sizeof(chValue));
	sprintf(chValue, "where KPRQ>=%u and KPRQ<=%u", beginDay, endDay);
	DBG_PRINT(("chValue = %s", chValue));

	//��Ʊ�ܽ��
	sprintf(chTmpValue, " and KPLX = %u", NORMAL_INV);
	strTmp = "select sum(KPHJJE) from INV_HEAD "; 
	strTmp.append(chValue);
	strTmp.append(chTmpValue);
	pInvHead->SetSQL(strTmp);
	pInvHead->GetOneResult(DB_INT64, (void*)&m_normalSum); 
    
	//��Ʊ�ܽ��
	sprintf(chTmpValue, " and KPLX = %u", RETURN_INV);
	strTmp = "select sum(KPHJJE) from INV_HEAD "; 
	strTmp.append(chValue);	
	strTmp.append(chTmpValue);
	pInvHead->SetSQL(strTmp);
	pInvHead->GetOneResult(DB_INT64, (void*)&m_returnSum); 
	
//	strTmp = "select sum(NM_SUM) from DAYSUM ";
//	strTmp.append(chValue);
//    pDaySum->SetSQL(strTmp);
//	pDaySum->GetOneResult(DB_INT64, (void*)&m_normalSum); 
//
//	strTmp = "select sum(RM_SUM) from DAYSUM ";
//	strTmp.append(chValue);
//    pDaySum->SetSQL(strTmp);
//	pDaySum->GetOneResult(DB_INT64, (void*)&m_returnSum); 
//
//	//����
//	memset((void*)chValue, 0, sizeof(chValue));
//	sprintf(chValue, "where I_DATE=%u and I_TYPE = %u", endDate, NORMAL_INV);
//		
//	strTmp = "select sum(M_SUM) from INV_HEAD "; 
//	strTmp.append(chValue);
//    pInvHead->SetSQL(strTmp);
//	pInvHead->GetOneResult(DB_INT64, (void*)&curNormalSum); 
//
//	memset((void*)chValue, 0, sizeof(chValue));
//	sprintf(chValue, "where I_DATE=%u and I_TYPE = %u", endDate, RETURN_INV);
//		
//	strTmp = "select sum(M_SUM) from INV_HEAD "; 
//	strTmp.append(chValue);
//    pInvHead->SetSQL(strTmp);
//	pInvHead->GetOneResult(DB_INT64, (void*)&curReturnSum); 
//
//	m_normalSum += curNormalSum; //��Ʊ�ۼƽ��
//	m_returnSum += curReturnSum; //��Ʊ�ۼƽ��
	

	//-----------------------------------------------------------------
	// ���㵥����ܵ���Ʊ�ۼƽ��ͺ�Ʊ�ۼƽ��
	//-----------------------------------------------------------------
// 	if (0 != g_globalArg->m_curInvVol->m_remain) 
// 	{
// 		sprintf(chValue, "where INV_NO>=%u and INV_NO<=%u and CODE_NO=%u", 
// 			g_globalArg->m_curInvVol->m_InvStartNo, 
// 			g_globalArg->m_curInvVol->m_InvEndNo, g_globalArg->m_curInvVol->m_codeNo);
// 
// 		//��Ʊ�ܽ��
// 		sprintf(chTmpValue, " and I_TYPE = %u", NORMAL_INV);
// 		strTmp = "select sum(M_SUM) from INV_HEAD "; 
// 		strTmp.append(chValue);
// 		strTmp.append(chTmpValue);
// 		pInvHead->SetSQL(strTmp);
// 		pInvHead->GetOneResult(DB_INT64, (void*)&m_normalVolSum); 
//     
// 		//��Ʊ�ܽ��
// 		sprintf(chTmpValue, " and I_TYPE = %u", RETURN_INV);
// 		strTmp = "select sum(M_SUM) from INV_HEAD "; 
// 		strTmp.append(chValue);	
// 		strTmp.append(chTmpValue);
// 		pInvHead->SetSQL(strTmp);
// 		pInvHead->GetOneResult(DB_INT64, (void*)&m_returnVolSum); 
// 
// 	}

	DBG_PRINT(("m_normalSum %ld", m_normalSum));
	DBG_PRINT(("m_returnSum %ld", m_returnSum));
//	DBG_PRINT(("m_normalVolSum %ld", m_normalVolSum));
//	DBG_PRINT(("m_normalVolSum %ld", m_normalVolSum));

	//-----------------------------------------------------------------
	// ���㻺�����Ʊ�ۼƽ��ͺ�Ʊ�ۼƽ��
	//-----------------------------------------------------------------	
	//	δ�ϴ�����Ʊ���
	CInvServ curInvServ;
	INT64 tmpSum;
//	char chValue[256], chTmpValue[64];
	memset((void*)chValue, 0, sizeof(chValue));
	sprintf(chValue, "where I_TYPE = %u", NORMAL_INV);
		
	strTmp = "select sum(M_SUM) from INV_SERV ";
	strTmp.append(chValue);
    curInvServ.SetSQL(strTmp);
	curInvServ.GetOneResult(DB_INT64, (void*)&m_InvServSum); 

//	memset((void*)chValue, 0, sizeof(chValue));
//	sprintf(chValue, "where I_TYPE = %u and WST_FLAG = 0", WASTE_INV);
//	
//	strTmp = "select sum(M_SUM) from INV_SERV ";
//	strTmp.append(chValue);
//    curInvServ.SetSQL(strTmp);
//	curInvServ.GetOneResult(DB_INT64, (void*)&tmpSum); 
//
//	m_InvServSum -= tmpSum;
	DBG_PRINT(("������ m_InvServSum= %ld",  m_InvServSum));
//	DBG_PRINT(("������ m_InvServSum= %ld",  g_globalArg->m_InvServSum));

//
//	//δ�ϴ��ĺ�Ʊ���
//	memset((void*)chValue, 0, sizeof(chValue));
//	sprintf(chValue, "where I_TYPE = %u and UP_FLAG = 0", RETURN_INV);
//		
//	strTmp = "select sum(M_SUM) from INV_SERV ";
//	strTmp.append(chValue);
//    curInvServ.SetSQL(strTmp);
//	curInvServ.GetOneResult(DB_INT64, (void*)&m_returnSum); 

	//ɾ��INV_SERV�������ü�¼
//	curInvServ.m_filter = "where UP_FLAG = 1 and WST_FLAG = 1";
//	curInvServ.Delete();

	//δ�ϴ���Ʊ����
//	sprintf(chValue, "where I_TYPE <= %u ", WASTE_INV);
//	curInvServ.m_filter = chValue;
	//m_InvServNum = curInvServ.GetRecordNum();
//	DBG_PRINT(("�������� m_InvServNum= %u", m_InvServNum));
	DBG_RETURN(SUCCESS);
}

//UINT8 CGlobalArg::CheckDaySum(UINT32 date)
//{
//	DBG_ENTER("CGlobalArg::CheckDaySum");
//	UINT32 tmpDate = 0;
//
//	CaProgressBar proBar("�ս��׻��ܼ����.....");
//	proBar.ReFresh();
//
//	CDaySum *daySum, cDaySum;
//	daySum = &cDaySum;
//	daySum->SetSQL("select max(I_DATE) from DAYSUM");	
//	daySum->GetOneResult(DB_UINT32, (void *)&tmpDate);
//	DBG_PRINT(("SELECT MAX RESULT %d", tmpDate));
//
//	if (tmpDate == 0)
//		tmpDate = g_globalArg->m_initDate;
//	else
//		tmpDate = (++TDateTime(tmpDate, 0)).FormatInt();
//
//	DBG_PRINT(("DAY SUM START DATE %lu", tmpDate));
//
//	UINT32 curDate = TDateTime::CurrentDate().FormatInt();
////	TDateTime endDateTime_declare(m_startDecDate, 80000); 
////	endDateTime_declare = endDateTime_declare+DEC_LIMIT_DAYS;
////	UINT32 nEndDate_declare = endDateTime_declare.FormatInt();  //δ�걨100����������
////	DBG_PRINT(("*****�걨��������100��nEndDate: %u**********", nEndDate_declare));
////	if (curDate >= nEndDate_declare)
////		m_declareLimitFlag = 1;
//
//	if (tmpDate >= curDate)
//		DBG_RETURN(SUCCESS);
//		
//	UINT32 errorcode = IC_SUCCESS;
//	TDateTime initDateTime(m_initDate, 80000); //������ʼ������
//	TDateTime endDateTime = initDateTime+(DAYSUM_LIMIT_DAYS-1); 
//	UINT32 nEndDate = endDateTime.FormatInt();  //�ս��׷���ǰһ��
//	DBG_PRINT(("*****�ս��׷���ǰһ��nEndDate: %u**********", nEndDate));
//
//	while (tmpDate < curDate)
//	{
//		if (tmpDate>nEndDate)
//		{
//			ShowMsg("�ս��׷���,�޷��ջ���");
//			break; //�ս��׷����󣬲������ջ���
//		}
////		if (tmpDate>=nEndDate_declare)
////		{
////			ShowMsg("����100��δ�걨,�޷��ջ���");
////			break; //����100��δ�걨�����ܼ�������
////		}
//		
//		char buf[64];
//		sprintf(buf, "%lu�շ�Ʊ���ݻ�����......", tmpDate);
//		proBar.SetText(buf);
//		proBar.ReFresh();
//
//		if ((errorcode = DaySum(tmpDate)) != SUCCESS)
//		{
////			DBG_PRINT(("DAY SUM ERROR: %02x", errorcode));
//			DBG_RETURN(errorcode);
//		}
//		Beep_On();
//		if (tmpDate>=nEndDate) //�ս��׷������
//		{
//			DBG_PRINT(("*********curDate: %u**********", curDate));
//			DBG_PRINT(("*****����Ʊ�����һ��nEndDate: %u**********", nEndDate));
//			m_forbidDaySum = 1; //�ս��׷�����־��λ
//			DBG_PRINT(("m_forbidDaySum : %lu", m_forbidDaySum));
//		}
//		tmpDate = (++TDateTime(tmpDate, 0)).FormatInt();
//	}
//
//	DBG_RETURN(SUCCESS);
//}

//UINT8 CGlobalArg::DaySum(UINT32 uDate)
//{
//	DBG_ENTER("SaleData::DaySum");
//    
//	UINT8 i;
//	char chValue[64];
//	DailyCollectData dailyCollectData, *pData;
//
//	pData = &dailyCollectData;
//    memset((void *)pData, 0, sizeof(DailyCollectData));//����
//	
//	CInvHead *pInvHead, curInvHead;
//	CInvDet  *pInvDet, curInvDet;
//	CDaySum  *pDaySum, curDaySum;
//	pInvHead = &curInvHead;
//	pInvDet  = &curInvDet;
//	pDaySum  = &curDaySum;	
//	
////pDaySum->m_issueDate = uDate;
////DBG_PRINT(("uDate = %u", uDate));
////for(i=0; i<TAX_ID_NUM; i++)                         
////{
////	pDaySum->m_taxid[i] = i+1;            
////}
//
//	//��װDailyCollectData�ṹ��
//	pData->data_type = 0;
//	pData->current_date = uDate;
//    
//	pInvHead->m_filter = "";
//	sprintf(chValue, "where I_DATE = %u",uDate);
//    pInvHead->m_filter.append(chValue);
//	pInvHead->GetInvoiceSum(pData->normal_invoice, pData->recede_invoice, pData->cancel_invoice);
//    
//    DBG_PRINT(("pData->normal_invoice = %u", pData->normal_invoice));
//    DBG_PRINT(("pData->recede_invoice = %u", pData->recede_invoice));
//	DBG_PRINT(("pData->cancel_invoice = %u", pData->cancel_invoice));
//
//	for(i=0; i<MAX_TAX_ITEM_NUM; i++)
//	{
//		pData->tax_item[i] = g_globalArg->m_taxID[i];
//	}
//
//	pInvDet->m_filter = "";
//	sprintf(chValue, "where I_DATE = %u and I_TYPE = %u",uDate, NORMAL_INV);
//	pInvDet->m_filter.append(chValue);
//	pInvDet->GetMoneySum(pData->normal_money, pData->tax_item, MAX_TAX_ITEM_NUM); //��Ʊ������
//
//	pInvDet->m_filter = "";
//	sprintf(chValue, "where I_DATE = %u and I_TYPE = %u",uDate, RETURN_INV);
//	pInvDet->m_filter.append(chValue);
//	pInvDet->GetMoneySum(pData->recede_money, pData->tax_item, MAX_TAX_ITEM_NUM); //��Ʊ������
//
//    for(i=0; i<MAX_TAX_ITEM_NUM; i++)
//	{
//		DBG_PRINT(("pData->normal_money[%u] = %u", i,pData->normal_money[i]));
//		DBG_PRINT(("pData->recede_money[%u] = %u", i,pData->recede_money[i]));
//	}
//
//    //��ȡ�ս���ǩ��		
//	UINT8 errorcode;
//    if((errorcode=daily_collect_sign((void *)pData, 
//									pDaySum->m_sign)) != IC_SUCCESS)
//	{
//		DBG_PRINT(("DAY SUM ERROR: %02x", errorcode));
//        DBG_RETURN(FAILURE);
//	}		
//
//	//�ջ������ݴ������ݿ�
//    pDaySum->m_issueDate = pData->current_date;		    //�ս������� 
//
//	pDaySum->m_normalInvNum = pData->normal_invoice;	//��Ʊ���� 
//	pDaySum->m_returnInvNum = pData->recede_invoice;	//��Ʊ���� 
//	pDaySum->m_wasteInvNum =  pData->cancel_invoice;	//��Ʊ���� 
//	
//	pDaySum->m_nm_sum = 0;	//������Ʊ�ܽ��
//	pDaySum->m_rm_sum = 0;	//���պ�Ʊ�ܽ��
//	for(i=0; i<TAX_ID_NUM; i++)                         
//	{
//		pDaySum->m_taxid[i] = pData->tax_item[i];            //˰��˰ĿID���� 
//		pDaySum->m_normalInvSum[i] = pData->normal_money[i]; //��˰��˰Ŀ�������Ʊ��� 
//		pDaySum->m_returnInvSum[i] = pData->recede_money[i]; // ��˰��˰Ŀ����ĺ�Ʊ���
//		pDaySum->m_nm_sum += pDaySum->m_normalInvSum[i];//������Ʊ�ܽ��
//		pDaySum->m_rm_sum += pDaySum->m_returnInvSum[i];//���պ�Ʊ�ܽ��
//	}		
//	
//	if (pDaySum->Save() != SUCCESS)
//	{
//		DBG_RETURN(FAILURE);
//	}
//
//	DBG_RETURN(SUCCESS);
//}

UINT8 CGlobalArg::ReadPrintTemplate(UINT8 *TemplateBuf, UINT8 TemplateNo, UINT32 len)
{ 

#ifndef WIN32
	INT8 tmp[16];
	string name = PRINT_TEMPLATE_FILE_NAME;
	INT32 fd;

	sprintf(tmp, "%02u.txt", TemplateNo);
	name += tmp;
//	memset(TemplateBuf, 0, PRINT_TEMPLATE_BUF_LEN);
	DBG_PRINT(("Template file: %s", name.c_str()));

	if ( (fd = open(name.c_str(), O_RDONLY)) == -1 )
	{
		DBG_PRINT(("open Template file err"));
		return FAILURE;
	}
	else
	{
		memset(TemplateBuf, 0, PRINT_TEMPLATE_BUF_LEN);
		read(fd, TemplateBuf, len);
	}
	
	close(fd);
	
#else
	int i;
	for (i=0;i<200;i++)
		TemplateBuf[i] = i+1;
	for (i=0;i<200;i++)
		TemplateBuf[i+200] = i+1;
	for (i=0;i<200;i++)
		TemplateBuf[i+400] = i+1;
	TemplateBuf[0]='B';
#endif
	
	return SUCCESS;
}

void CGlobalArg::ShowMsg(string strInfo)
{ 
	CaMsgBox msgBox(strInfo.c_str(),CaMsgBox::MB_OK);
	msgBox.ShowBox();
	msgBox.ReFresh();

}

UINT8 CGlobalArg::SysLog(UINT8 Eventtype, UINT32 EventResult, string Backup)
{ 
	INT32 ret;
	CSysLog syslog;
	syslog.m_idate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);	/**< ��־��¼����ʱ�� */
	syslog.m_itime = TDateTime::CurrentDateTime().FormatInt(HHMMSS);
	syslog.m_operator = g_globalArg->m_operator->m_name;	/**< �տ�Ա */
	syslog.m_type = Eventtype;				/**< �¼����� */
	syslog.m_result = EventResult;			/**< �¼���� */
	syslog.m_backup = Backup;				/**< ���� */

	ret = syslog.AddNew();
	if (ret!=SQLITE_OK)
	{
		DBG_PRINT(("дϵͳ��־��ʧ�� ret = %d", ret));
		return FAILURE;
	}

	return SUCCESS;
}


UINT8 CGlobalArg::SysLogRoll()
{
	CSysLog syslog;
	UINT8 ret = SUCCESS;
	UINT32 nRtDetNo = 0;
	INT32 nCount = 0;

	nCount = syslog.GetSysLogNum();
	DBG_PRINT(("nCount = %d", nCount));
	
	if (nCount<0)
	{
		nCount = 0;
		ShowMsg("ͳ��ϵͳ��־��ʧ��");
		DBG_RETURN(FAILURE);
	}
		
	ret = syslog.CheckRoll(nCount,nRtDetNo);
	if (ret!=SUCCESS)
	{
		DBG_RETURN(FAILURE);
	}

	if (nRtDetNo>0)
	{
#if AUTOISSUE
		ShowMsg("ϵͳ��־Ҫ����!");	
#endif
		DBG_PRINT(("ϵͳ��־������..... "));
		BAR_DEF();
		BAR_SHOW("ϵͳ��־������.....");
		syslog.Roll(nRtDetNo);//RtInv�����
		CommonSleep(1000);
		CGlobalArg::SysLog(EVENT_SYSLOG_ROLL , SUCCESS);//дϵͳ��־
	}
	
	DBG_RETURN(SUCCESS);
}

INT32 CGlobalArg::OnLineTest(string &strErr)
{
#if TYPE_MODE == ZHQ_MODE
	BAR_DEF();
	BAR_SHOW("��ת��������...");

	INT32 ret = SUCCESS;

	ret = g_pAPIBase->OnLine(strErr);
	
	return ret;
#endif
}









