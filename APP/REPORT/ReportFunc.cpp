/*! \file    ReportFunc.cpp
   \brief    awe4000r�����ӡ��Ӧ�ú���
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */


#include "ReportFunc.h"
#include "CaProgressBar.h"
#include "keypad.h"

#include "TDateTime.h"
#include "PrintDriver.h"
#include "CGlobalArg.h"
#include "CInvDet.h"
#include "YWXMLGY.h"
#include "APIBase.h"

#ifndef WIN32
#include <sys/timeb.h>
#include "lcd_tiny.h"
#endif

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#define MAX_LINE_PRINT_NUM		255		//��ӡ�пɴ�ӡ�������
//�¼������б�
INT8 *g_EventTip[] = 
{
    "���ػ������",
	"��¼ϵͳ",
	"����ϵͳ",
	"����ģ��",
	"����",
	"�ο�",
	"���Ӳ���Ա",
	"ɾ������Ա",
	"�༭����Ա",
	"��Ʊ��Ϣ����",
	"��Ʊ����Ϣ����",
	"ϵͳ��־����",
	"���»�����Ϣ",
	"�Ƿ��û���",
	"�Ƿ�˰�ؿ�",
	"�Ƿ�����",
	"�Ƿ�PIN��",
	"��ʼ��",
	"��Ʊ�ַ�",
	"����Ʊ",
	"��Ʊ��Ϣ�����",
	"����ʱ��",
	"��˰",
	"��˰",
	"����",
	"�����û���Ϣ",
	"��Ʊ����",
	"���籣������ʼ������",
	"���籣������Ʊ�ַ�",
	"���籣������Ʊ����",
	"���籣������Ʊ",
	"���籣��������",
	"���籣������˰",
	"���籣������˰",
	"����Ʊ",
	"����Ʊ"
	
};

UINT8 YesNoMsgBox(string strInfo)
{
	DBG_ENTER("YesNoMsgBox(string strInfo)");
	
	CaMsgBox msgBox(strInfo.c_str(),CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
	{
		DBG_PRINT((" msgBox.m_iStatus == NO_PRESSED!"));
		DBG_RETURN(FAILURE); 
	}
	
	if(msgBox.m_iStatus == OK_PRESSED)
	{
//		ReFresh();
		DBG_PRINT((" msgBox.m_iStatus == OK_PRESSED!"));
		DBG_RETURN(SUCCESS);		
	}
}

//��ͳ�Ʋ�ѯ
UINT8 GetMonthSumCount(CTjxxhz *pTjxxhz, string &strErr)
{
	INT32 retCode = 0;
	
	DBG_PRINT(("g_YwXmlArg->m_fplxdm : %s", g_YwXmlArg->m_fplxdm.c_str()));
	
	retCode = g_pAPIBase->TJXXCXPro_API(*g_YwXmlArg, pTjxxhz, strErr);
	DBG_PRINT(("GetMonthSumCount_retCode : %d", retCode));

	if (retCode != SUCCESS)
	{
		return FAILURE;
	}
	return SUCCESS;
}

/*
//----�ջ��ܲ�ѯ
UINT8 GetDaySumCount(UINT32 nStartDate, UINT32 nEndDate, UINT32 &nNum)
{
	DBG_ENTER("GetDaySumCount");

	nNum = 0;
	INT32 errorcode;
	INT32 nTmpNum = 0;
	CDaySum curDaySum;
	CDaySum *pDaySum = &curDaySum;
	DBG_ASSERT_EXIT((pDaySum != NULL), (" pDaySum == NULL!"));

	//���ܼ�¼��

	INT8 value[256];
	memset((void*)value, 0, sizeof(value));
	pDaySum->m_filter = "";
	sprintf(value,"where I_DATE >= %u and I_DATE <= %u",nStartDate,nEndDate);
	pDaySum->m_filter.append(value);
	DBG_PRINT((" pDaySum->m_filter = %s!", pDaySum->m_filter.c_str()));
	nTmpNum = pDaySum->GetRecordNum();

// 	delete pDaySum;
	pDaySum = NULL;

	if (nTmpNum<0)
	{
		DBG_RETURN(FAILURE); 		
	}
	nNum = nTmpNum;
	DBG_RETURN(SUCCESS); 
}

//----ʱ��λ���
*/
UINT8 IsTimeValid(UINT32 hhmmss)
{
	UINT8 hour;
	UINT8 minute;
	UINT8 second;
	
	hour   = (UINT8)((hhmmss/10000));
	minute = (UINT8)((hhmmss/100)-(hour)*100);
	second = (UINT8)(hhmmss-(hhmmss/100)*100);

	if (hour>23 || minute >59 || second >59) 
	{
		return FAILURE;
	}

	return SUCCESS;
}
//---��ӡϵͳ��־

UINT8 PrnSysLogHead(UINT32 nStartDate, UINT32 nEndDate)
{
	DBG_PRINT((" PrnSysLogHead"));

	UINT32 nCurDate, nCurTime;
	
	SetLineSpace(REPORT_LINE_SPACE);

	PrintReportLine("         << �� ȫ �� ־ �� �� >>", sizeof("         << �� ȫ �� ־ �� �� >>"));
	nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	nCurTime = TDateTime::CurrentDateTime().FormatInt(HHMMSS);

	sprintf(pGeneralPrnBuff, "�Ʊ����ڣ�%04lu-%02lu-%02lu   ʱ�䣺%02lu:%02lu:%02lu", nCurDate / 10000,
			(nCurDate % 10000) / 100, nCurDate % 100, nCurTime / 10000, (nCurTime % 10000) / 100, nCurTime % 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "�� �� �ˣ�%s", g_globalArg->m_operator->m_name.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "��ӡ���䣺%04lu-%02lu-%02lu �� %04lu-%02lu-%02lu", 
			 nStartDate / 10000, (nStartDate % 10000) / 100, nStartDate % 100, 
			 nEndDate / 10000, (nEndDate % 10000) / 100, nEndDate % 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));			

	PrintReportLine("========================================", sizeof("========================================"));
	
	return SUCCESS;
}

UINT8 PrnSysLogDetail(const CSysLog *pSysLog)
{
	INT8 chValue[256];
	DBG_ASSERT_EXIT((pSysLog != NULL), (" pSysLog == NULL "));

	SetLineSpace(REPORT_LINE_SPACE);
	//�¼���������
	sprintf(pGeneralPrnBuff, "�¼��������ڣ�%04lu-%02lu-%02lu  ʱ�䣺%02lu:%02lu:%02lu", pSysLog->m_idate / 10000,
					(pSysLog->m_idate % 10000) / 100, pSysLog->m_idate % 100, pSysLog->m_itime / 10000, (pSysLog->m_itime % 10000) / 100, pSysLog->m_itime % 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));		
	
	//�¼�����
	sprintf(pGeneralPrnBuff, "�¼����ͣ�%s", g_EventTip[pSysLog->m_type]);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));	
		
	//�¼�����Ա
//	memset((void*)chValue, 0, sizeof(chValue));
//	sprintf(chValue, "where OP_ID = %u", pSysLog->m_operator);
//	COperator eventOperator;
//	eventOperator.m_filter = chValue;
//	eventOperator.Requery();
//	if(eventOperator.LoadOneRecord()!=SQLITE_OK)
//	{
//		CaMsgBox::ShowMsg("������Ա��Ϣʧ��");
//		eventOperator.m_name = "";
//	}
	sprintf(pGeneralPrnBuff, "����Ա��  %s", pSysLog->m_operator.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	//�¼����
	switch(pSysLog->m_result) 
	{
		case FAILURE:
			sprintf(pGeneralPrnBuff, "�¼������ʧ��");
			break;
		case SUCCESS:
			sprintf(pGeneralPrnBuff, "�¼�������ɹ�");
			break;
		case OVERFLOW:
			sprintf(pGeneralPrnBuff, "�¼������Խ��");
			break;
		default:
			sprintf(pGeneralPrnBuff, "�¼������ʧ��  �������ʹ��룺%u", pSysLog->m_result);
			break;
	}
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	//�¼���ע
	if ("" != pSysLog->m_backup) 
	{
		sprintf(pGeneralPrnBuff, "�¼���ע��%s", pSysLog->m_backup.c_str());
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	}
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));

	DBG_PRINT((" PrnSysLogDetail SUCCESS"));
	return SUCCESS;
}

/*
//----��ӡPLU
UINT8 PrnPLUHead()
{
	DBG_PRINT((" PrnPLUHead"));

	SetLineSpace(REPORT_LINE_SPACE);
	PrintReportLine("             PLU��Ϣ�б�", sizeof("             PLU��Ŀ�б�"));	
	PrintReportLine("", sizeof(""));	
	PrintReportLine("����            ����               �۸� ", sizeof("����            ����               �۸� "));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	return SUCCESS;
}

UINT8 PrnPLUDetail(const CPlu *pPlu)
{
	DBG_PRINT((" PrnPLUDetail"));
	DBG_ASSERT_EXIT((pPlu != NULL), (" pPlu == NULL "));

	SetLineSpace(REPORT_LINE_SPACE);
	sprintf(pGeneralPrnBuff, "%-16s%-18s%6.2f", pPlu->m_code.c_str(), pPlu->m_name.c_str(), pPlu->m_price);				
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

//	ForwardNLine(FORWARD_LINES);
	return SUCCESS;

}
*/
//----��ӡ�ͻ�����
UINT8 PrnClientHead()
{
	DBG_PRINT((" PrnPLUHead"));

	SetLineSpace(REPORT_LINE_SPACE);
	PrintReportLine("             �ͻ�������", sizeof("             �ͻ�������"));	
	PrintReportLine("", sizeof(""));	
	PrintReportLine("���               ����", sizeof("���              ����"));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	return SUCCESS;
}

UINT8 PrnClientDetail(const CClient *pClient)
{
	DBG_PRINT((" PrnClientDetail"));
	DBG_ASSERT_EXIT((pClient != NULL), (" pClient == NULL "));

	SetLineSpace(REPORT_LINE_SPACE);
	sprintf(pGeneralPrnBuff, "%-5s%-18s", pClient->m_khbh.c_str(), pClient->m_khmc.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
//	ForwardNLine(FORWARD_LINES);
	return SUCCESS;

}

//----���౨��
UINT8 PrnDeptHead()
{
	DBG_PRINT((" PrnDeptHead"));

	SetLineSpace(REPORT_LINE_SPACE);
	PrintReportLine("             ��Ʒ��Ϣ�б�", sizeof("             ��Ʒ��Ϣ�б�"));	
	PrintReportLine("", sizeof(""));	
	PrintReportLine("��Ʒ����        �����      ����", sizeof("��Ʒ����        �����      ����"));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	return SUCCESS;
}

UINT8 PrnDeptDetail(const CDept *pDept)
{
	DBG_PRINT((" PrnDeptDetail"));
	DBG_ASSERT_EXIT((pDept != NULL), (" pDept == NULL "));

	SetLineSpace(REPORT_LINE_SPACE);
	sprintf(pGeneralPrnBuff, "%-13s   %-4u   %-20s",  pDept->m_spbm.c_str(), pDept->m_blh, pDept->m_spmc.c_str());				
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

//	ForwardNLine(FORWARD_LINES);
	return SUCCESS;

}

//----����Ա����
UINT8 PrnOperatorHead()
{
	DBG_PRINT((" PrnOperatorHead"));

	SetLineSpace(REPORT_LINE_SPACE);
	PrintReportLine("             ����Ա��Ϣ�б�", sizeof("             ����Ա��Ϣ�б�"));	
	PrintReportLine("", sizeof(""));	
	PrintReportLine("���                      ����", sizeof("���                      ����"));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	return SUCCESS;
}

UINT8 PrnOperatorDetail(const COperator *pOperator)
{
	DBG_PRINT((" PrnOperatorDetail"));
	DBG_ASSERT_EXIT((pOperator != NULL), (" pOperator == NULL "));

	SetLineSpace(REPORT_LINE_SPACE);
	sprintf(pGeneralPrnBuff, "%03d      %s", pOperator->m_opid, pOperator->m_name.c_str());				
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
    
	//ForwardNLine(FORWARD_LINES);
	return SUCCESS;

}
/*
//----����Աͳ��

UINT8 PrnSalerSumHead(UINT32 nStartDate, UINT32 nStartTime, UINT32 nEndDate, UINT32 nEndTime)
{
	DBG_PRINT((" PrnSalerSumHead()"));

	SetLineSpace(REPORT_LINE_SPACE);
	PrintReportLine("    << �� �� Ա  �� �� ͳ �� �� �� >>", sizeof("    << �� �� Ա  �� �� ͳ �� �� �� >>"));
//	PrintReportHead(startDate, endDate, &startTime, &endTime);		//��ӡ�Ʊ���Ϣ
	UINT32 nCurDate, nCurTime;

	nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	nCurTime = TDateTime::CurrentDateTime().FormatInt(HHMMSS);

	sprintf(pGeneralPrnBuff, "�Ʊ����ڣ�%04lu-%02lu-%02lu   ʱ�䣺%02lu:%02lu", nCurDate / 10000,
			(nCurDate % 10000) / 100, nCurDate % 100, nCurTime / 10000, (nCurTime % 10000) / 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "�� �� �ˣ�%s", g_globalArg->m_operator->m_name.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	

	sprintf(pGeneralPrnBuff, "ͳ�����䣺   %04lu-%02lu-%02lu   %02lu:%02lu:%02lu",
									nStartDate / 10000, (nStartDate % 10000) / 100, nStartDate % 100, 
									nStartTime / 10000, (nStartTime % 10000) / 100,(nStartTime % 10000) % 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	sprintf(pGeneralPrnBuff, "          �� %04lu-%02lu-%02lu   %02lu:%02lu:%02lu", 
									nEndDate / 10000, (nEndDate % 10000) / 100, nEndDate % 100, 
									nEndTime / 10000, (nEndTime % 10000) / 100, (nEndTime % 10000) % 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	PrintReportLine("========================================", sizeof("========================================"));

	return SUCCESS;
}

UINT8 PrnSaler(const string *pSaler)
{
	DBG_PRINT((" PrnSaler()"));
	sprintf(pGeneralPrnBuff, "����Ա��%s", pSaler->c_str());
	DBG_PRINT((" ����Ա��%s", pSaler->c_str()));
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	PrintReportLine("�� Ʒ                    ���۽��", sizeof("�� Ʒ                    ���۽��"));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	return SUCCESS;
}

UINT8 PrnSalerDeptSum(const string *pDeptName, INT64 nSum)
{
	DBG_PRINT((" PrnSalerDeptSum()"));
	sprintf(pGeneralPrnBuff, "%-20s %.2f", pDeptName->c_str(), (double)nSum/SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	return SUCCESS;
}

UINT8 PrnSalerSum(UINT32 nInvCount, INT64 nSum)
{
	DBG_PRINT((" PrnSalerSum()"));
	DBG_PRINT((" nInvCount = %u, nSum = %d", nInvCount, nSum));

	sprintf(pGeneralPrnBuff, "��Ʊ������%u", nInvCount);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "���۽�%.2f", (double)nSum/SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));		
	PrintReportLine("========================================", sizeof("========================================"));

	return SUCCESS;
}
*/

//----������ͳ��
UINT8 PrnSaleSumHead(UINT32 nStartDate, UINT32 nStartTime, UINT32 nEndDate, UINT32 nEndTime, UINT8 nIfDay)
{
	DBG_PRINT((" PrnDaySaleSumHead()"));
	SetLineSpace(REPORT_LINE_SPACE);

	if (1==nIfDay)
	{
		PrintReportLine("       << �� Ʊ �� ͳ �� �� �� >>", sizeof("        << �� Ʊ �� ͳ �� �� �� >>"));
	}
	else if (0==nIfDay) 
	{
		PrintReportLine("       << �� Ʊ �� ͳ �� �� �� >>", sizeof("        << �� Ʊ �� ͳ �� �� �� >>"));

	}
	

	UINT32 nCurDate, nCurTime;

	nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	nCurTime = TDateTime::CurrentDateTime().FormatInt(HHMMSS);

	sprintf(pGeneralPrnBuff, "�Ʊ����ڣ�%04lu-%02lu-%02lu   ʱ�䣺%02lu:%02lu", nCurDate / 10000,
			(nCurDate % 10000) / 100, nCurDate % 100, nCurTime / 10000, (nCurTime % 10000) / 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "�� �� �ˣ�%s", g_globalArg->m_operator->m_name.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	if (1==nIfDay) 
	{
		sprintf(pGeneralPrnBuff, "ͳ�����䣺   %04lu-%02lu-%02lu   %02lu:%02lu:%02lu",
									nStartDate / 10000, (nStartDate % 10000) / 100, nStartDate % 100, 
									nStartTime / 10000, (nStartTime % 10000) / 100,(nStartTime % 10000) % 100);
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
		
		sprintf(pGeneralPrnBuff, "          �� %04lu-%02lu-%02lu   %02lu:%02lu:%02lu", 
										nEndDate / 10000, (nEndDate % 10000) / 100, nEndDate % 100, 
										nEndTime / 10000, (nEndTime % 10000) / 100, (nEndTime % 10000) % 100);
	}
	else if (0==nIfDay)
	{
		sprintf(pGeneralPrnBuff, "ͳ�����䣺   %04lu-%02lu-%02lu  �� %04lu-%02lu-%02lu ",
									nStartDate / 10000, (nStartDate % 10000) / 100, nStartDate % 100, 
									nEndDate / 10000, (nEndDate % 10000) / 100, nEndDate % 100);
	}
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	PrintReportLine("========================================", sizeof("========================================"));

	return SUCCESS;
}

UINT8 PrnDate(const string *strIssueDate)
{
	DBG_PRINT((" PrnSaler()"));
	sprintf(pGeneralPrnBuff, "��Ʊ���ڣ�%s", strIssueDate->c_str());
	DBG_PRINT((" ��Ʊ���ڣ�%s", strIssueDate->c_str()));
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	PrintReportLine("�� Ʒ                 ���۽��", sizeof("�� Ʒ                 ���۽��"));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	return SUCCESS;
}

UINT8 PrnDayDeptSum(const string *pDeptName, INT64 nSum)
{
	DBG_PRINT((" PrnSalerDeptSum()"));


	sprintf(pGeneralPrnBuff, "%-20s %.2f", pDeptName->c_str(), (double)nSum/SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	PrintReportLine("========================================", sizeof("========================================"));
	return SUCCESS;
}

UINT8 PrnDaySaleSum(UINT32 nInvCount, INT64 nSum)
{
	DBG_PRINT((" PrnSalerSum()"));
	DBG_PRINT((" nInvCount = %u, nSum = %d", nInvCount, nSum));

	sprintf(pGeneralPrnBuff, "�տ�Ʊ������%u", nInvCount);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "�������ܶ%.2f", (double)nSum/SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));		
	PrintReportLine("========================================", sizeof("========================================"));

	return SUCCESS;
}

UINT8 PrnAllDaySaleSum(UINT32 nInvCount, INT64 nSum)
{
	DBG_PRINT((" PrnAllDaySaleSum()"));
	DBG_PRINT((" nInvCount = %u, nSum = %d", nInvCount, nSum));

	PrintReportLine("           �� ��", sizeof("           �� ��"));
	sprintf(pGeneralPrnBuff, "�ܿ�Ʊ ������ %u", nInvCount);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "�� �� �� � %.2f", (double)nSum/100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	PrintReportLine("�� Ʒ                    ���۽��", sizeof("�� Ʒ                    ���۽��"));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));

	return SUCCESS;
}

UINT8 PrnDeptMoney(INT64 &sumMoney, const string *strFilter)
{
	DBG_ASSERT_EXIT((strFilter != NULL), (" strFilter == NULL!"));

	INT32 retCode;
	INT64 norMoney = 0;//ĳ������Ʊ���
	INT64 retMoney = 0;//ĳ�����Ʊ���
	
	INT8 chDeptValue[128];
	memset((void*)chDeptValue, 0, sizeof(chDeptValue));
	INT8 chValue[512];
	memset((void*)chValue, 0, sizeof(chValue));

	CInvDet invDet;
	CDept dept;

	//���������ͳ��,��ӡ������
	dept.Requery();
	retCode = dept.MoveFirst();
	while((retCode == SQLITE_ROW)||(retCode == SQLITE_DONE))
	{
		if(retCode == SQLITE_DONE)
		{
			dept.m_spbm = "000";
			dept.m_blh = 0;
			dept.m_spmc = "����";
		}
		sprintf(chDeptValue, " and SPBM = '%s' ", dept.m_spbm.c_str());//�����
	
		DBG_PRINT(("chDeptValue %s", chDeptValue));
		sprintf(chValue, " and KPLX = %u ", NORMAL_INV);//��Ʊ����
		invDet.m_filter = *strFilter;
		invDet.m_filter += chDeptValue;
		invDet.m_filter += chValue;
		norMoney = invDet.PartMoneySum();//ĳ�������Ʊ���۽��
		DBG_PRINT(("����ʱ��ĳ��������۽�� %d", norMoney));

		sprintf(chValue, " and (KPLX = %u or KPLX = %u or KPLX = %u)", 
			RETURN_INV, RET_MANUAL_INV, RET_SPECIAL_INV);//��Ʊ����
		invDet.m_filter = *strFilter;
		invDet.m_filter += chDeptValue;
		invDet.m_filter += chValue;
		retMoney = invDet.PartMoneySum();//ĳ����ĺ�Ʊ���۽��
		DBG_PRINT(("����ʱ��ĳ��������ۺ��� %d", retMoney));

		//��-��
		norMoney = norMoney - retMoney;//ĳ��������۽��
		sumMoney += norMoney;
		if (0 != norMoney)
		{
			DBG_PRINT(("����ʱ��ĳ��������۽�� %d", norMoney));
			PrnDayDeptSum(&(dept.m_spmc), norMoney);//��ӡ����ʱ�β������۽��
		}
					
		if(retCode == SQLITE_DONE)
		{
			break;
		}
		retCode = dept.MoveNext();		
	}
		if (retCode != SQLITE_DONE) 
	{
		CaMsgBox::ShowMsg("��ѯ������Ϣʧ��");
		DBG_PRINT(("��ѯ������Ϣʧ��"));
		dept.MoveEnd();	
		return FAILURE;
	}
	dept.MoveEnd(); 
	return SUCCESS;
}

UINT8 PrnPeriodDeptMoney(INT64 &sumMoney, UINT32 nStartDate, UINT32 nStartTime, UINT32 nEndDate, UINT32 nEndTime)
{
	INT32 retCode;
	INT64 norMoney = 0;//ĳ������Ʊ���
	INT64 retMoney = 0;//ĳ�����Ʊ���
	
	INT8 chDeptValue[128];
	memset((void*)chDeptValue, 0, sizeof(chDeptValue));
	INT8 chValue[512];
	memset((void*)chValue, 0, sizeof(chValue));

	CInvDet invDet;
	CDept dept;

	UINT8 nCount = 0;
	UINT8 i = 0;
	string filterArr[3];

	if (nStartDate == nEndDate) 
	{
		DBG_PRINT(("��ͬһ��"));
		nCount = 1;
		sprintf(chValue, "where KPRQ = %u and KPSJ >= %u and KPSJ <= %u ", nStartDate, nStartTime, nEndTime);		
		filterArr[0] = chValue;
		DBG_PRINT(("filterArr[0] = %s", filterArr[0].c_str()));
	}
	else
	{
		DBG_PRINT(("����ͬһ��"));
		nCount = 3;
		//��ʼ��
		sprintf(chValue, "where KPRQ = %u and KPSJ >= %u ", nStartDate, nStartTime);
		filterArr[0] = chValue;	
		DBG_PRINT(("filterArr[0] = %s", filterArr[0].c_str()));
		//��ֹ��
		sprintf(chValue, "where KPRQ = %u and KPSJ <= %u ", nEndDate, nEndTime);
		filterArr[1] = chValue;	
		DBG_PRINT(("filterArr[1] = %s", filterArr[0].c_str()));
		//�м�ʱ��
		sprintf(chValue, " where KPRQ > %u and KPRQ < %u",nStartDate,nEndDate);
		filterArr[2] = chValue;
		DBG_PRINT(("filterArr[2] = %s", filterArr[0].c_str()));
	}

	//���������ͳ��,��ӡ������
	dept.Requery();
	retCode = dept.MoveFirst();
	while((retCode == SQLITE_ROW)||(retCode == SQLITE_DONE))
	{
		if(retCode == SQLITE_DONE)
		{
			dept.m_spbm = "000";
			dept.m_blh = 0;
			dept.m_spmc = "����";
		}
		sprintf(chDeptValue, " and SPBM = '%s' ", dept.m_spbm.c_str());//��Ʒ����
	
		norMoney = 0;
		retMoney = 0;
		for(i = 0; i<nCount; i++)
		{
			sprintf(chValue, " and KPLX = %u ", NORMAL_INV);//��Ʊ����
			invDet.m_filter = filterArr[i];
			invDet.m_filter += chDeptValue;
			invDet.m_filter += chValue;
			norMoney += invDet.PartMoneySum();//ĳ�������Ʊ���۽��

			sprintf(chValue, " and (KPLX = %u or KPLX = %u or KPLX = %u )",
				RETURN_INV, RET_MANUAL_INV, RET_SPECIAL_INV);//��Ʊ����
			invDet.m_filter = filterArr[i];
			invDet.m_filter += chDeptValue;
			invDet.m_filter += chValue;
			retMoney += invDet.PartMoneySum();//ĳ����ĺ�Ʊ���۽��
		}
		norMoney -= retMoney;//ĳ��������۽��
		sumMoney += norMoney;
		if (0 != norMoney)
		{
			DBG_PRINT(("����ʱ��ĳ��������۽�� %d", norMoney));
			PrnDayDeptSum(&(dept.m_spmc), norMoney);//��ӡ����ʱ�β������۽��
		}

		if(retCode == SQLITE_DONE)
		{
			break;
		}
		retCode = dept.MoveNext();		
	}
	if (retCode != SQLITE_DONE) 
	{
		CaMsgBox::ShowMsg("��ѯ������Ϣʧ��");
		DBG_PRINT(("��ѯ������Ϣʧ��"));
		dept.MoveEnd();
		return FAILURE;
	}
		dept.MoveEnd();
	return SUCCESS;
}

//-----������ͳ��
UINT8 PrnMonth(UINT32 sumDate)
{
	DBG_PRINT((" PrnSaler()"));
	sprintf(pGeneralPrnBuff, "�·ݣ�%04lu-%02lu", sumDate / 10000, (sumDate % 10000) / 100);
// 	sprintf(pGeneralPrnBuff, "��Ʊ���ڣ�%s", strIssueDate->c_str());
	DBG_PRINT((" ͳ���·ݣ�%u", sumDate));
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	PrintReportLine("�� Ʒ                    ���۽��", sizeof("�� Ʒ                    ���۽��"));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	return SUCCESS;
}

UINT8 PrnMonthSaleSum(UINT32 nInvCount, INT64 nSum)
{
	DBG_PRINT((" PrnMonthSaleSum()"));
	DBG_PRINT((" nInvCount = %u, nSum = %d", nInvCount, nSum));

	sprintf(pGeneralPrnBuff, "��Ʊ������%u", nInvCount);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "�������ܶ%.2f", (double)nSum/SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));		
	PrintReportLine("========================================", sizeof("========================================"));

	return SUCCESS;
}

//----��Ʊͳ��
UINT8 PrnIssueSumHead(UINT32 nStartDate, UINT32 nStartTime, UINT32 nEndDate, UINT32 nEndTime)
{
	DBG_PRINT((" PrnSalerSumHead()"));

	SetLineSpace(REPORT_LINE_SPACE);
	PrintReportLine("            << �� Ʊ �� �� >>", sizeof("            << �� Ʊ �� �� >>"));
	UINT32 nCurDate, nCurTime;

	nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	nCurTime = TDateTime::CurrentDateTime().FormatInt(HHMMSS);

	sprintf(pGeneralPrnBuff, "�Ʊ����ڣ�%04lu-%02lu-%02lu   ʱ�䣺%02lu:%02lu", nCurDate / 10000,
			(nCurDate % 10000) / 100, nCurDate % 100, nCurTime / 10000, (nCurTime % 10000) / 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "�� �� �ˣ�%s", g_globalArg->m_operator->m_name.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	

	sprintf(pGeneralPrnBuff, "ͳ�����䣺   %04lu-%02lu-%02lu   %02lu:%02lu:%02lu",
									nStartDate / 10000, (nStartDate % 10000) / 100, nStartDate % 100, 
									nStartTime / 10000, (nStartTime % 10000) / 100,(nStartTime % 10000) % 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	sprintf(pGeneralPrnBuff, "          �� %04lu-%02lu-%02lu   %02lu:%02lu:%02lu", 
									nEndDate / 10000, (nEndDate % 10000) / 100, nEndDate % 100, 
									nEndTime / 10000, (nEndTime % 10000) / 100, (nEndTime % 10000) % 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	PrintReportLine("========================================", sizeof("========================================"));

// 	PrintReportLine("��Ʊ��         ��Ʊ����         ���۽��", sizeof("��Ʊ��         ��Ʊ����         ���۽��"));
// 	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	
	return SUCCESS;
}

UINT8 PrnIssueSumCode(string fpdm)
{
	ForwardNLine(1);

	sprintf(pGeneralPrnBuff, "��Ʊ����: %s", fpdm.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	
	PrintReportLine("��Ʊ��         ��Ʊ����         ���۽��", sizeof("��Ʊ��         ��Ʊ����         ���۽��"));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));

	return SUCCESS;
}

UINT8 PrnIssueSumBody(UINT32 nInvNo, UINT8 nInvType, INT64 nInvMoney)
{
	string strType = "";

	switch(nInvType) 
	{
		case NORMAL_INV:
			strType = "��Ʊ";
			break;
		case RETURN_INV:
			strType = "��Ʊ";
			break;
		case WASTE_INV:
			strType = "��Ʊ";
			break;
		case WASTE_NOR:
			strType = "����";
			break;
		case WASTE_RET:
			strType = "���";
			break;
		case RET_MANUAL_INV:
			strType = "�ֹ���Ʊ";
			break;
 		case RET_SPECIAL_INV:
 			strType = "�����Ʊ"; 
			break;
		default:;
	}
	sprintf(pGeneralPrnBuff, "%08lu %12s %17.2f", nInvNo, strType.c_str(), 
															(double)nInvMoney / SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	return SUCCESS;
}

UINT8 PrnIssueSumEnd(UINT32 nNormalNum, UINT32 nReturnNum, UINT32 nWasteNum, INT64 norMoney, INT64 retMoney)
{
	INT64 leftMoney = norMoney - retMoney;//�����

	PrintReportLine("========================================", 
					sizeof("========================================")); 
	
	SetLineSpace(REPORT_LINE_SPACE2);	
//	PrintSeparateLine();	
	sprintf(pGeneralPrnBuff, "��Ʊ���� : %11lu", nNormalNum);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "��Ʊ���� : %11lu", nReturnNum);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "��Ʊ���� : %11lu", nWasteNum);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));


	sprintf(pGeneralPrnBuff, "��Ʊ��� : %11.2f", ((double)norMoney) / SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	sprintf(pGeneralPrnBuff, "��Ʊ��� : %11.2f", ((double)retMoney) / SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	sprintf(pGeneralPrnBuff, "��  ��� : %11.2f", ((double)leftMoney) / SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	ForwardNLine(FORWARD_LINES);

	return SUCCESS;

}

UINT8 PrnInvCheckOldHead(string nsrmc, string swdjzh,TCheckOld* checkoldHead)
{
	int i = 0;
	SetLineSpace(REPORT_LINE_SPACE);
	PrintReportLine("      << �� Ʊ �� �� �� �� �� �� �� >>", sizeof("      <<  �� Ʊ �� �� �� �� �� �� �� >>"));

	sprintf(pGeneralPrnBuff, "��˰�����ƣ�%s ", nsrmc.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "��˰��ʶ��ţ�%s", swdjzh.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

// 	sprintf(pGeneralPrnBuff, "��Ʊ���ڣ�%04lu-%02lu-%02lu �� %04lu-%02lu-%02lu",
// 		nStartDate / 10000, (nStartDate % 10000) / 100, nStartDate % 100,
// 		nEndDate / 10000, (nEndDate % 10000) / 100, nEndDate % 100);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
// 	
	sprintf(pGeneralPrnBuff, "��ˮ�ţ�%s", checkoldHead[i].searchNo.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	UINT32 nCurDate, nCurTime;
	nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	//nCurTime = TDateTime::CurrentDateTime().FormatInt(HHMMSS);

	sprintf(pGeneralPrnBuff, "��ӡʱ�䣺%04lu-%02lu-%02lu", nCurDate / 10000,
		(nCurDate % 10000) / 100, nCurDate % 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	//PrintReportLine("########################################", sizeof("########################################"));
	//PrintReportLine("****************************************", sizeof("****************************************"));
	
	return SUCCESS;

}
UINT8 PrnTimeDeptMoney(INT64 &sumMoney,INT64 &norMoney,INT64 &retMoney, const string *strFilter)
{
	DBG_ASSERT_EXIT((strFilter != NULL), (" strFilter == NULL!"));
	
	INT32 retCode;
	// 	INT64 norMoney = 0;//ĳ������Ʊ���
	// 	INT64 retMoney = 0;//ĳ������Ʊ���
	
	INT64 NorMoney=0,RetMoney=0;
	
	INT8 chDeptValue[128];
	memset((void*)chDeptValue, 0, sizeof(chDeptValue));
	INT8 chValue[512];
	memset((void*)chValue, 0, sizeof(chValue));
	
	CInvDet invDet;
	CDept dept;
	
	//���������ͳ��,��ӡ������
	dept.Requery();
	retCode = dept.MoveFirst();
	
	while((retCode == SQLITE_ROW)||(retCode == SQLITE_DONE))
	{
		if(retCode == SQLITE_DONE)
		{
			dept.m_spbm = "0000000000000";
			//dept.m_taxCode = "00000000";
			dept.m_blh = 0;
			dept.m_spmc = "����";
		}
		DBG_PRINT(("dept.m_spbm = %s",dept.m_spbm.c_str()));
		sprintf(chDeptValue, " and SPBM = '%s' ", dept.m_spbm.c_str());//��Ʒ����
		
		sprintf(chValue, " and KPLX = %u ", NORMAL_INV);//��Ʊ����
		invDet.m_filter = *strFilter;
		invDet.m_filter += chDeptValue;
		invDet.m_filter += chValue;
		DBG_PRINT(("invDet.m_filter= %s",invDet.m_filter.c_str()));
		NorMoney = invDet.PartMoneySum();//ĳ�������Ʊ���۽��
		DBG_PRINT(("norMoney = %ld",norMoney));
		
		sprintf(chValue, " and (KPLX = %u or KPLX = %u or KPLX = %u)", 
			RETURN_INV, RET_MANUAL_INV, RET_SPECIAL_INV);//��Ʊ����
		invDet.m_filter = *strFilter;
		invDet.m_filter += chDeptValue;
		invDet.m_filter += chValue;
		RetMoney = invDet.PartMoneySum();//ĳ�������Ʊ���۽��
		DBG_PRINT(("retMoney = %ld",retMoney));
		
		norMoney +=NorMoney;
		DBG_PRINT(("norMoney = %ld",norMoney));
		
		retMoney+=RetMoney;
		DBG_PRINT(("retMoney = %ld",retMoney));
		
		//��-��
		NorMoney = NorMoney - RetMoney;//ĳ��������۽��
		sumMoney += NorMoney;
		DBG_PRINT(("sumMoney = %ld",sumMoney));
		if (0 != norMoney)
		{
			DBG_PRINT(("����ʱ��ĳ��������۽�� %d", norMoney));
			//PrnDayDeptSum(&(dept.m_spmc), norMoney);//��ӡ����ʱ�β������۽��
		}
		
		if(retCode == SQLITE_DONE)
		{
			break;
		}
		retCode = dept.MoveNext();		
	}
	if (retCode != SQLITE_DONE) 
	{
		CaMsgBox::ShowMsg("��ѯ������Ϣʧ��");
		DBG_PRINT(("��ѯ������Ϣʧ��"));
		dept.MoveEnd();	
		return FAILURE;
	}
	dept.MoveEnd();
	return SUCCESS;
}



UINT8 PrnInvCheckOldBody(TCheckOld* checkoldHead, int &nHeadNum, TCheckOldInfo* checkoldInfo, int &nInfoNum)
{
   // int nTemp = 0;

	for(int i=0; i<nHeadNum; i++)
	{
		PrintReportLine("========================================", sizeof("========================================"));
		sprintf(pGeneralPrnBuff, "��Ʊ���ƣ�%s ", checkoldHead[i].invName.c_str());
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

		sprintf(pGeneralPrnBuff, "��Ʊ���룺%s ", checkoldHead[i].invCode.c_str());
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
		
		sprintf(pGeneralPrnBuff, "��Ʊ��ţ�%s       ��Ʊֹ�ţ�%s", checkoldHead[i].invSNo.c_str(), checkoldHead[i].invENo.c_str());
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

		sprintf(pGeneralPrnBuff, "����ʱ�䣺%s       ������%u", checkoldHead[i].checkDate.c_str(), checkoldHead[i].num);
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
		PrintReportLine("========================================", sizeof("========================================"));
	
		UINT32 nSNo, nENo;
        nSNo =  atoi(checkoldHead[i].invSNo.c_str());
		DBG_PRINT(("nSNo = %u", nSNo));
        nENo =  atoi(checkoldHead[i].invENo.c_str());
		DBG_PRINT(("nENo = %u", nENo));
		
	    int nTemp = 0;
     
		DBG_PRINT(("nInfoNum = %u", nInfoNum));
		for(int j=nTemp; j<nInfoNum; j++)
		{
			UINT32 nStartNo, nEndNo;
			nStartNo = atoi(checkoldInfo[j].invSNo.c_str());
			DBG_PRINT(("nStartNo = %u", nStartNo));
			nEndNo  =  atoi(checkoldInfo[j].invENo.c_str());
		    DBG_PRINT(("nEndNo = %u", nEndNo));

			DBG_PRINT(("$$$$$$$$$$$$$j == %d", j));

		   if((nSNo <= nStartNo ) && (nEndNo <= nENo))
		   {
			  sprintf(pGeneralPrnBuff, "����ʱ�䣺%s        ������%u", checkoldInfo[j].checkDate.c_str(), checkoldInfo[j].num);
			  PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
			  
			  sprintf(pGeneralPrnBuff, "��Ʊ��ţ�%s       ��Ʊֹ�ţ�%s", checkoldInfo[j].invSNo.c_str(), checkoldInfo[j].invENo.c_str());
			  PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
			  
			  DBG_PRINT(("SE == %s", checkoldInfo[j].taxMoney.c_str()));
			  sprintf(pGeneralPrnBuff, "���%s          �˰�%s", checkoldInfo[j].money.c_str(), checkoldInfo[j].taxMoney.c_str());
			  PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
			  
			  sprintf(pGeneralPrnBuff, "ʹ�������%s ", checkoldInfo[j].resContent.c_str());
			  PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

			  PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));

	       	  //nTemp++;
		   }
// 		   else
// 		   {
// 			    
// 			   break;
// 		   }
	       nTemp++;
	  }
      
	  //PrintReportLine("****************************************", sizeof("****************************************"));

	}

	ForwardNLine(FORWARD_LINES);
	return SUCCESS;
	
}

/**************************************************************************
����     ����ӡ��ƱƱ�ֻ�����Ϣ
��ʽ     ��int print_goodsfo(UINT8 bFindBlackMark )
������� ��UINT8 bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ�
                               ��ʼ��ӡ
������� ��
����ֵ   ��-1����ʧ�ܣ�SUCCESS�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
UINT8 print_invkindifo(/*struct TInvKindInfoPrnData *invkindData, */ UINT8 bFindBlackMark)
{
  
	SetLineSpace(REPORT_LINE_SPACE);
	PrintRptTitle("�� Ʊ Ʊ �� �� Ϣ");
    PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	
	CInvKind *pInvKind ;
	CInvKind InvKind;
	pInvKind=&InvKind;
	INT8 value[256];
	sprintf(value, "order by NO ");	
	pInvKind->m_filter=value;
	pInvKind->Requery();
    int i=0;
	INT32 errorcode = pInvKind->MoveFirst();
	DBG_PRINT(("errorcode = %u", errorcode));
	while (errorcode == SQLITE_ROW)
	{	
		DBG_PRINT(("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&i == %d", i));	
		DBG_PRINT(("��Ʊ���ʹ��� = %s", InvKind.m_fplxdm.c_str()));
		sprintf(pGeneralPrnBuff, "��Ʊ���ʹ��� : %s", InvKind.m_fplxdm.c_str());
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
		
		DBG_PRINT(("�����޶� = %f",((double)InvKind.m_maxSign)/SUM_EXTENSION));
		sprintf(pGeneralPrnBuff, "�����޶� : %.2f", ((double)InvKind.m_maxSign)/SUM_EXTENSION);
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

		DBG_PRINT(("���������� = %u", InvKind.m_Lxssr));
		sprintf(pGeneralPrnBuff, "���������� : %u", InvKind.m_Lxssr);
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

		DBG_PRINT(("���߿���ʱ��(Сʱ) = %u", InvKind.m_Lxkjsj));
		sprintf(pGeneralPrnBuff, "���߿���ʱ��(Сʱ) : %u", InvKind.m_Lxkjsj);
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
		
		DBG_PRINT(("������Ʊ�ۼ��޶� = %f",((double)InvKind.m_maxSum)/SUM_EXTENSION));
		sprintf(pGeneralPrnBuff, "������Ʊ�ۼ��޶� : %.2f", ((double)InvKind.m_maxSum)/SUM_EXTENSION);
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
			
		PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
		errorcode = pInvKind->MoveNext();
		i++; 
	}
	     pInvKind->MoveEnd();
	    ForwardNLine(FORWARD_LINES);
	    ForwardNLine(FORWARD_LINES);
	
	    return 0;
}

/**************************************************************************

����     ����ӡ˰��˰Ŀ��Ϣ

��ʽ     ��UINT8 print_taxiteminfo( struct TTaxItemPrnData *taxitem,

                 UINT8 bFindBlackMark )

������� ��struct TTaxItemPrnData *taxitem  ˰��˰Ŀ��Ϣ

         ��UINT8 bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ�

                               ��ʼ��ӡ

������� ��

����ֵ   ��-1����ʧ�ܣ�0�����ɹ�

����     ��

����     ��

ժҪ     ��

**************************************************************************/



INT8 print_taxiteminfo(UINT8 bFindBlackMark )

{

	UINT8 i;
	INT8 tmpCode[2 * TAX_ITME_CODE_LEN + 1];

	PrinterIni(bidirection);
	SetLineSpace(REPORT_LINE_SPACE);

	PrintRptTitle("˰ �� ˰ Ŀ �� Ϣ");
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	sprintf(pGeneralPrnBuff, "˰��            ˰��");
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	CTax *pTax;
	CTax Tax;
	pTax = &Tax;
	INT8 value[256];
	sprintf(value, "order by NO ");	
	pTax->m_filter=value;
	pTax->Requery();
	INT32 errorcode = pTax->MoveFirst();
	DBG_PRINT(("errorcode = %u", errorcode));
	while (errorcode == SQLITE_ROW)
	{	
		DBG_PRINT(("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&i == %d", i));	

		sprintf(pGeneralPrnBuff, "%-2u            %.2f%%", pTax->m_no, (double)(pTax->m_sl)/100);
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));	
	
		errorcode = pTax->MoveNext();
		i++; 
	}
	pTax->MoveEnd();
	ForwardNLine(FORWARD_LINES);
	ForwardNLine(FORWARD_LINES);

	return 0;

}


void DivideCNStr(string &str1, INT32 len, string &str2)
{
	if ( str1.size()<=len || len<=0 )
		return;
	
	string strTmp(str1);
	
	if( GetHalfHZCount((unsigned char *)strTmp.c_str(), len)%2 == 0 )
	{
		len=strTmp.size() > len ? len: strTmp.size();
	}
	else
	{
		len=strTmp.size() > len-1 ? len-1: strTmp.size();
	}
	
	str1.assign( strTmp, 0, len );
	str2.assign( strTmp, len, strTmp.size()-len );
}


int GetHalfHZCount(unsigned char *str,int len)
{
	int c=0;
	int p=0;
	while (p < len)
	{
		if ((str[p] >= 0x81) && (str[p] <= 0xfe))
		{
			c++;
			p++;
			if (p < len)
			{
				if ((str[p] >= 0x40) && (str[p] <= 0xfe))
				{
					c++;
					p++;
				}
			}
		}
		else
		{
			p++;
		}
	}
	
	return c;
}

INT8 PrintTitle()
{
	//	PrintReportLine("          << ͨ ֪ �� Ϣ �� >>", sizeof("           <<  ͨ ֪ �� Ϣ �� >>"));
	PrintRptTitle("<< ͨ ֪ �� Ϣ �� >>");
}

INT8 PrintSeparator()
{
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
}

INT8 PrintDoubleSeparator()
{
	PrintReportLine("========================================", sizeof("========================================"));
}

/*
UINT8 PrnMessageDetail(const CMessage *message)
{
	DBG_PRINT((" PrnMessageDetail"));
	DBG_ASSERT_EXIT((message != NULL), (" message == NULL "));
	
	SetLineSpace(REPORT_LINE_SPACE);
	
	string strMsg = "����: " + message->m_title;
	string tmpStr("");
	do 
	{
		DivideCNStr(strMsg, 46, tmpStr);
		sprintf(pGeneralPrnBuff, "%s", strMsg.c_str());
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
		strMsg = tmpStr;
	} while (tmpStr.size() > 46);
	
	sprintf(pGeneralPrnBuff, "%s", tmpStr.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	
	strMsg = "����: " + message->m_content;
	tmpStr = "";
	do 
	{
		DivideCNStr(strMsg, MAX_LINE_PRINT_NUM, tmpStr);
		sprintf(pGeneralPrnBuff, "%s", strMsg.c_str());
#if 0
		int i; 
		for(i=0; i<1024; i++)
		{
			printf("%2x ",pGeneralPrnBuff[i]);
		}
#endif
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
		strMsg = tmpStr;
		DBG_PRINT(("tmpStr.size = %u",tmpStr.size()));
	} while (tmpStr.size() >MAX_LINE_PRINT_NUM);
	

	sprintf(pGeneralPrnBuff, "%s", tmpStr.c_str());
     
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));


   UINT32 tmpcjsj=atoi(message->m_cjsj.substr(0,8).c_str());

	sprintf(pGeneralPrnBuff, "����ʱ��: %04lu-%02lu-%02lu", 
		tmpcjsj/10000, (tmpcjsj%10000)/100, tmpcjsj%100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	 UINT32 tmpxxsj=atoi(message->m_xxsj.substr(0,8).c_str());

	sprintf(pGeneralPrnBuff, "��Ϣʱ��: %04lu-%02lu-%02lu", 
		tmpxxsj/10000, (tmpxxsj%10000)/100, tmpxxsj%100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	 UINT32 tmpxgsj=atoi(message->m_xgsj.substr(0,8).c_str());

	sprintf(pGeneralPrnBuff, "�޸�ʱ��: %04lu-%02lu-%02lu", 
		tmpxgsj/10000, (tmpxgsj%10000)/100, tmpxgsj%100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "˰����ش���: %s",message->m_swjgdm.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "������Ա����: %s",message->m_czrydm.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "��ע: %s",message->m_remark.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	
	PrintSeparator();
	
	return SUCCESS;
}
*/
/*
//------�ۼƽ��
UINT8 PrnMoneyInfo(INT64  normalSum, INT64  returnSum, INT64  normalVolSum, INT64  returnVolSum)
{
	DBG_PRINT((" PrnMoneyInfo()"));

	SetLineSpace(REPORT_LINE_SPACE);

	PrintReportLine("            ���ۼƽ���", sizeof("            ���ۼƽ���"));

	UINT32 nCurDate, nCurTime;

	nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	nCurTime = TDateTime::CurrentDateTime().FormatInt(HHMMSS);

	sprintf(pGeneralPrnBuff, "�Ʊ����ڣ�%04lu-%02lu-%02lu   ʱ�䣺%02lu:%02lu", nCurDate / 10000,
			(nCurDate % 10000) / 100, nCurDate % 100, nCurTime / 10000, (nCurTime % 10000) / 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "�� �� �ˣ�%s", g_globalArg->m_operator->m_name.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	PrintReportLine("========================================", sizeof("========================================"));

	PrintReportLine("����                     ���", sizeof("����                     ���"));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	sprintf(pGeneralPrnBuff, "�걨����Ʊ�ۼƽ�� : %11.2f", ((double)normalSum) / SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "�걨�ں�Ʊ�ۼƽ�� : %11.2f", ((double)returnSum) / SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "��Ʊ����Ʊ�ۼƽ�� : %11.2f", ((double)normalVolSum) / SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "��Ʊ���Ʊ�ۼƽ�� : %11.2f", ((double)returnVolSum) / SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	ForwardNLine(FORWARD_LINES);
	return SUCCESS;
}
	
//----��Ʊ������ͳ��

UINT8 PrnInvSaleSumHead(UINT32 nStartNo, UINT32 nEndNo, const string *strpCode)
{
	DBG_PRINT((" PrnDaySaleSumHead()"));
	SetLineSpace(REPORT_LINE_SPACE);
	
	PrintReportLine("       << �� Ʊ �� ͳ �� �� �� >>", sizeof("        << �� Ʊ �� ͳ �� �� �� >>"));
	
	UINT32 nCurDate, nCurTime;
	nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	nCurTime = TDateTime::CurrentDateTime().FormatInt(HHMMSS);

	sprintf(pGeneralPrnBuff, "�Ʊ����ڣ�%04lu-%02lu-%02lu   ʱ�䣺%02lu:%02lu", nCurDate / 10000,
			(nCurDate % 10000) / 100, nCurDate % 100, nCurTime / 10000, (nCurTime % 10000) / 100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	sprintf(pGeneralPrnBuff, "�� �� �ˣ�%s", g_globalArg->m_operator->m_name.c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "��Ʊ���룺   %s ", strpCode->c_str());
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "ͳ�����䣺   %08lu  �� %08lu ", nStartNo, nEndNo);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	PrintReportLine("========================================", sizeof("========================================"));

	PrintReportLine("�� Ʒ                    ���۽��", sizeof("�� Ʒ                    ���۽��"));
	PrintReportLine("----------------------------------------", sizeof("----------------------------------------"));
	
	return SUCCESS;
}

UINT8 PrnInvSaleSumEnd(UINT32 nInvCount, INT64 nSum)
{
	DBG_PRINT((" PrnAllDaySaleSum()"));
	DBG_PRINT((" nInvCount = %u, nSum = %d", nInvCount, nSum));

	PrintReportLine("========================================", sizeof("========================================"));

	PrintReportLine("           �� ��", sizeof("           �� ��"));
	sprintf(pGeneralPrnBuff, "�ܿ�Ʊ ������ %u", nInvCount);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "�� �� �� � %.2f", (double)nSum/100);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	return SUCCESS;
}
*/