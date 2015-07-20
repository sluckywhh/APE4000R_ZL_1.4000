/****************************************************************************

�ļ���           ��printer.c

����             ��APL-1000��ӡ����

��ʼ����         ��2004-09-16

����             ���Խ���

****************************************************************************/

//#define POS_DEBUG_TO_TTY

#include <stdio.h>

#include <string.h>

#include "printer.h"

#include "PrintDriver.h"

#include "arithmetic.h"  

#include "TemplateIndep.h"

//#include "pwoffdatadesign.h"

//#include "systemdef.h"

#include "pos_log.h"



// ��ʱ��� BY ZL///////////

#define	BIDIRECTIONAL	3

////////////////////////////



UINT8 g_AlreadyFindBlack = 0;

extern UINT8 bidirection ;


INT8 print_buffer[1024];



INT8 *pGeneralPrnBuff = print_buffer;

/**************************************************************************
����     ����ӡ����Ʊʹ�û������ݱ���
��ʽ     ��INT8 print_volumeinfo(struct TVolSumPrnData *volsumdata,
                     UINT8 bFindBlackMark)
������� ��struct TVolSumPrnData *volsumdata  ��Ʊ���������
         ��UINT8 bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ�
                               ��ʼ��ӡ
������� ��
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
INT8 print_volumeinfo(struct TVolSumPrnData *volsumdata,UINT8 bFindBlackMark)
{

	UINT8 invCode[INV_TYPE_CODE_LEN*2+1];

//	PrinterIni(BIDIRECTIONAL);
PrinterIni(bidirection);


	SetLineSpace(REPORT_LINE_SPACE);

	

	PrintRptTitle("����Ʊʹ�û������ݱ���");

	

	sprintf(pGeneralPrnBuff, "�� λ  �� �� : %s", volsumdata->CorpName);

	PrintReportLine(pGeneralPrnBuff, (UINT8)strlen(pGeneralPrnBuff));

	

// 	sprintf(pGeneralPrnBuff, "˰        �� : %s", volsumdata->TaxCode);
// 	PrintReportLine(pGeneralPrnBuff, (UINT8)strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��   ��   �� : %s", volsumdata->MachineCode);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� Ʊ  ʱ �� : %04lu-%02lu-%02lu �� %04lu-%02lu-%02lu", 

		volsumdata->StartDate / 10000,  (volsumdata->StartDate % 10000) / 100, volsumdata->StartDate % 100, 

		volsumdata->EndDate / 10000,  (volsumdata->EndDate % 10000) / 100, volsumdata->EndDate % 100);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

//	sprintf(pGeneralPrnBuff, "�� Ʊ  �� �� :                      ");

// 	bin2char(volsumdata->TypeCode, (INT8 *)invCode, INV_TYPE_CODE_LEN);

// 	memcpy((void *)&pGeneralPrnBuff[15], (void *)(invCode), INV_TYPE_CODE_LEN*2);	
	sprintf(pGeneralPrnBuff, "�� Ʊ  �� �� : %s", volsumdata->TypeCode);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��Ʊ��ʼ���� : %08lu", volsumdata->StartInvNo);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��Ʊ��ֹ���� : %08lu", volsumdata->EndInvNo);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "������Ʊ���� : %lu", volsumdata->PosInvCount);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "������Ʊ���߽�� : %.2f", ((double)(volsumdata->PosInvSum))/SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� Ʊ  �� �� : %lu", volsumdata->WasteInvCount);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� Ʊ  �� �� : %lu", volsumdata->ReInvCount);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� Ʊ  �� �� : %.2f", ((double)(volsumdata->ReInvSum))/SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	ForwardNLine(FORWARD_LINES);
	

/*
#if PETROL_STATION_VER == 0

//	ForwardNLine(FORWARD_LINES);

#endif*/


	

	return 0;

}



/**************************************************************************

����     ����ӡʱ��η�Ʊʹ�û������ݱ���

��ʽ     ��int print_dateseginvsuminfo( struct TDateSegSumPrnData * daySumData

                             UINT8 bFindBlackMark );

������� ��struct TDateSegSumPrnData * dateSegSumData  ʱ��η�Ʊ��������

         ��UINT8 bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ�

                               ��ʼ��ӡ

������� ��

����ֵ   ��-1����ʧ�ܣ�0�����ɹ�

����     ��

����     ��

ժҪ     ��

**************************************************************************/

int print_dateseginvsuminfo( struct TDateSegSumPrnData * dateSegSumData,

                             UINT8 bFindBlackMark,UINT32 startTime, UINT32 endTime)

{

	UINT8 i;

	

//	PrinterIni(BIDIRECTIONAL);
PrinterIni(bidirection);


	SetLineSpace(REPORT_LINE_SPACE);

	PrintRptTitle("��Ʊʹ�û������ݱ���");

	

	sprintf(pGeneralPrnBuff, "�� λ  �� �� : %s", dateSegSumData->CorpName);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "˰        �� : %s", dateSegSumData->TaxCode);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��   ��   �� : %s", dateSegSumData->MachineCode);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� Ʊ  ʱ �� : %04lu-%02lu-%02lu   %02lu:%02lu:%02lu", 

		dateSegSumData->StartDate / 10000,  (dateSegSumData->StartDate % 10000) / 100, dateSegSumData->StartDate % 100, 

		startTime / 10000,  (startTime % 10000) / 100, startTime % 100);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "          �� : %04lu-%02lu-%02lu   %02lu:%02lu:%02lu", 

		dateSegSumData->EndDate / 10000,  (dateSegSumData->EndDate % 10000) / 100, dateSegSumData->EndDate % 100, 

		endTime / 10000,  (endTime % 10000) / 100, endTime % 100);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "������Ʊ���� : %lu", dateSegSumData->PosInvCount);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "������Ʊ���߽�� : %.2f", ((double)(dateSegSumData->PosInvSum))/SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� Ʊ  �� �� : %lu", dateSegSumData->WasteInvCount);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� Ʊ �� �� : %lu", dateSegSumData->ReInvCount);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� Ʊ  �� �� : %.2f", ((double)(dateSegSumData->ReInvSum))/SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	
/*
	PrintSeparateLine();

	
	sprintf(pGeneralPrnBuff, "˰��        ��Ʊ���       ��Ʊ���");

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));	

	for( i=0 ; i<TAX_ITEM_MAX_COUNT ; i++ )

	{

		if (dateSegSumData->TaxItem[i] == 0)

		{

			continue;

		}

		sprintf(pGeneralPrnBuff, "%3u      %11.2f    %11.2f", dateSegSumData->TaxItem[i], 

															((double)(dateSegSumData->PosInvSumByTax[i]))/SUM_EXTENSION, 

															((double)(dateSegSumData->ReInvSumByTax[i]))/SUM_EXTENSION);

		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	}
*/


	ForwardNLine(FORWARD_LINES);

	

    return 0;

}



/**************************************************************************

����     ����ӡ�ս��׻������ݱ���

��ʽ     ��int print_daystatinfo( struct TDaySumInfoPrnData *daySumData,

         �� UINT8 bFindBlackMark );

������� ��struct TDaySumInfoPrnData *daySumData �ս��׻�������

         ��UINT8 bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ�

                               ��ʼ��ӡ

������� ��

����ֵ   ��-1����ʧ�ܣ�0�����ɹ�

����     ��

����     ��

ժҪ     ��

**************************************************************************/

int print_daystatinfo( struct TDaySumInfoPrnData *daySumData, UINT8 bFindBlackMark )

{

	UINT8 i;



//	PrinterIni(BIDIRECTIONAL);
PrinterIni(bidirection);


	SetLineSpace(REPORT_LINE_SPACE);

	PrintRptTitle("�� �� �� �������ݱ���");

	

	sprintf(pGeneralPrnBuff, "�� λ  �� �� : %s", daySumData->CorpName);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "˰        �� : %s", daySumData->TaxCode);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��   ��   �� : %s", daySumData->MachineCode);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� Ʊ  �� �� : %04lu-%02lu-%02lu", 

		daySumData->Date / 10000,  (daySumData->Date % 10000) / 100, daySumData->Date % 100);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "        ����Ʊ   ��Ʊ      ��Ʊ");

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "����    %-6lu   %-4lu        %-4lu", daySumData->PosInvCount, 

		daySumData->ReInvCount, daySumData->WasteInvCount);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	PrintSeparateLine();

	

//	sprintf(pGeneralPrnBuff, "˰��        ��Ʊ���       ��Ʊ���");
	sprintf(pGeneralPrnBuff, "��Ʊ���       ��Ʊ���");
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "%-11.2f  %-11.2f",
		((double)(daySumData->PosInvSum))/SUM_EXTENSION, ((double)(daySumData->ReInvSum))/SUM_EXTENSION);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	
/*
	for( i=0 ; i<TAX_ITEM_MAX_COUNT ; i++ )

	{

		if (daySumData->TaxItem[i] == 0)

		{

			continue;

		}

		sprintf(pGeneralPrnBuff, "%3u      %11.2f    %11.2f", daySumData->TaxItem[i], 

			((double)(daySumData->PosInvSum[i]))/SUM_EXTENSION, ((double)(daySumData->ReInvSum[i]))/SUM_EXTENSION);

		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	}
*/
	

	ForwardNLine(FORWARD_LINES);

	

    return 0;

}



/**************************************************************************

����     ����ӡ�걨���ݻ��ܱ����ѯ

��ʽ     ��int print_sbstatinfo( struct TDeclareSumPrnData *declareData,

                       bool bFindBlackMark )

������� ��struct TDeclareSumPrnData *declareData �걨���ݻ�������

         ��UINT8 bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ�

                               ��ʼ��ӡ

������� ��

����ֵ   ��-1����ʧ�ܣ�0�����ɹ�

����     ��

����     ��

ժҪ     ��

**************************************************************************/

int print_sbstatinfo(  struct TDeclareSumPrnData *DeclareSumPrnData )

{

	UINT8 i;

	

//	PrinterIni(BIDIRECTIONAL);
PrinterIni(bidirection);


	SetLineSpace(REPORT_LINE_SPACE);

	PrintRptTitle("�� �� �� Ϣ ���ݱ���");

	

	sprintf(pGeneralPrnBuff, "��λ���� : %s", DeclareSumPrnData->CorpName);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "˰    �� : %s", DeclareSumPrnData->TaxCode);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� �� �� : %s", DeclareSumPrnData->MachineCode);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�걨���� :  %04lu-%02lu-%02lu �� %04lu-%02lu-%02lu", 

		DeclareSumPrnData->StartDate / 10000,  (DeclareSumPrnData->StartDate % 10000) / 100, DeclareSumPrnData->StartDate % 100, 

		DeclareSumPrnData->EndDate / 10000,  (DeclareSumPrnData->EndDate % 10000) / 100, DeclareSumPrnData->EndDate % 100);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "        ����Ʊ     ��Ʊ      ��Ʊ");

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "����    %-6lu     %-4lu        %-4lu", DeclareSumPrnData->PosInvCount, 

		DeclareSumPrnData->ReInvCount, DeclareSumPrnData->WasteInvCount);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	PrintSeparateLine();

	

	sprintf(pGeneralPrnBuff, "˰��        ��Ʊ���       ��Ʊ���");

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	for( i=0 ; i<TAX_ITEM_MAX_COUNT ; i++ )

	{

		if (DeclareSumPrnData->TaxItem[i] == 0)

		{

			continue;

		}

		sprintf(pGeneralPrnBuff, "%-3u         %-11.2f   %-11.2f", DeclareSumPrnData->TaxItem[i], 

			((double)(DeclareSumPrnData->PosInvSum[i]))/SUM_EXTENSION, ((double)(DeclareSumPrnData->ReInvSum[i]))/SUM_EXTENSION);

		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	}

	

	ForwardNLine(FORWARD_LINES);

	

    return 0;

}



/**************************************************************************

����     ����ӡ˰�ػ�������Ϣ

��ʽ     ��int print_macinfo(struct TMachinePrnData *machineData, 

             UINT8 bFindBlackMark )

������� ��struct TMachinePrnData *machineData ˰�ػ�������Ϣ

         ��UINT8 bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ�

                               ��ʼ��ӡ

������� ��

����ֵ   ��-1����ʧ�ܣ�0�����ɹ�

����     ��

����     ��

ժҪ     ��

**************************************************************************/



int print_macinfo(struct TMachinePrnData *machineData,  UINT8 bFindBlackMark )

{

//	PrinterIni(BIDIRECTIONAL);
PrinterIni(bidirection);
	

	SetLineSpace(REPORT_LINE_SPACE);

	PrintRptTitle("�� �� �� Ϣ");

	sprintf(pGeneralPrnBuff, "�� �� �� �� : %s", machineData->MachineNo);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "Ӳ �� �� �� :  %s", machineData->HardVer);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� �� �� �� :  %s", machineData->SoftVer);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� �� �� �� :  %04lu-%02lu-%02lu", machineData->MakeDate / 10000, 

		(machineData->MakeDate % 10000) / 100, machineData->MakeDate % 100);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	if( machineData->IMEIFlag == 1 )
	{
		sprintf(pGeneralPrnBuff, "����IMEI :  %s", machineData->IMEI);
		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	}

	ForwardNLine(FORWARD_LINES);

	return 0;

}



/**************************************************************************

����     ����ӡ��ҵ�û���Ϣ

��ʽ     ��int print_corpinfo(struct TCorpInfoPrnData *corpData, 

             UINT8 bFindBlackMark )

������� ��struct TCorpInfoPrnData *corpData ��ҵ�û���Ϣ

         ��UINT8 bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ�

                               ��ʼ��ӡ

������� ��

����ֵ   ��-1����ʧ�ܣ�0�����ɹ�

����     ��

����     ��

ժҪ     ��

**************************************************************************/

int print_corpinfo(struct TCorpInfoPrnData *corpData,  UINT8 bFindBlackMark )
{
//	PrinterIni(BIDIRECTIONAL);
	PrinterIni(bidirection);
	SetLineSpace(REPORT_LINE_SPACE);

	UINT8 flagBuff[64];
	PrintRptTitle(" �� ҵ �� Ϣ");

	sprintf(pGeneralPrnBuff, "��˰������ : %s", corpData->Nsrmc);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "��˰��ʶ��� : %s", corpData->Nsrsbh);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	sprintf(pGeneralPrnBuff, "��˰�̱�� : %s", corpData->Jspsbh);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
// 	sprintf(pGeneralPrnBuff, "��ҵ���� : %s", corpData->Nsrhydm);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
// 	sprintf(pGeneralPrnBuff, "��ҵ���� : %s", corpData->Nsrhymc);
//	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

// 	sprintf(pGeneralPrnBuff, "��Ӫ��Ŀ���� : %s", corpData->Nsrjyxmzwmc);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	sprintf(pGeneralPrnBuff, "����˰����ش��� : %s", corpData->Nsrswjgdm);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	sprintf(pGeneralPrnBuff, "����˰��������� : %s", corpData->Nsrswjgmc);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "����ʱ�� : %s", corpData->Qysj);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "���ֻ� : %s", corpData->Zfbz);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "��ҵ���� : %s", corpData->Qylx);
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
// 	memset(flagBuff, 0, sizeof(flagBuff));
// 	if( corpData->Yxbz == 1 )
// 		sprintf(flagBuff, "��Ч");
// 	else
// 		sprintf(flagBuff, "ע��");
// 	sprintf(pGeneralPrnBuff, "��Ч��־ : %s", flagBuff);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
// 	memset(flagBuff, 0, sizeof(flagBuff));
// 	if( corpData->Nsrlx == 1 )
// 		sprintf(flagBuff, "һ����˰��");
// 	else if( corpData->Nsrlx == 2 )
// 		sprintf(flagBuff, "С��ģ��˰��");
// 	sprintf(pGeneralPrnBuff, "��˰������ : %s", flagBuff);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
// 
// 	sprintf(pGeneralPrnBuff, "���շ�ʽ���� : %s", corpData->Zsfs_dm);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
// 	
// 	sprintf(pGeneralPrnBuff, "�Զ�����ҵ���� : %u", corpData->Zdy_qylx);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

// 	sprintf(pGeneralPrnBuff, "��Ʊ����Ա : %s", corpData->Kpgly);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

// 	sprintf(pGeneralPrnBuff, "��Ʊģʽ : %u", corpData->Kpms);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
// 	sprintf(pGeneralPrnBuff, "��Ʊģʽ���� : %s", corpData->Kpmsmc);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	

// 	sprintf(pGeneralPrnBuff, "��Ʊ������ : %u", corpData->Kpjsl);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
// 	sprintf(pGeneralPrnBuff, "��Ʊ�޶� : %.2f", ((double)(corpData->MaxSum))/SUM_EXTENSION);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
// 	sprintf(pGeneralPrnBuff, "������߿�Ʊ���� : %u", corpData->MaxDay);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
// 
// 	sprintf(pGeneralPrnBuff, "������߿�Ʊ���� : %u", corpData->MaxNum);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
// 
// 	sprintf(pGeneralPrnBuff, "������߿�Ʊ��� : %.2f", ((double)(corpData->MaxMoney))/SUM_EXTENSION);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	ForwardNLine(FORWARD_LINES);

	return 0;
}

int print_invKindinfo(struct TInvKindInfoPrnData *invkindData,  UINT8 bFindBlackMark )
{
	//	PrinterIni(BIDIRECTIONAL);
// 	PrinterIni(bidirection);
// 	SetLineSpace(REPORT_LINE_SPACE);
// 	
// 	UINT8 flagBuff[64];
// 	PrintRptTitle(" Ʊ �� �� Ϣ");
// 
// 
// 	sprintf(pGeneralPrnBuff, "Ʊ������ : %s", invkindData->InvKindName);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
// 	
// 	sprintf(pGeneralPrnBuff, "Ʊ�ִ��� : %s", invkindData->InvKindCode);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
// 	
// 	/*DBG_PRINT(("����� = %f",((double)(invkindData->InvMaxMoney))/SUM_EXTENSION));*/
// 	sprintf(pGeneralPrnBuff, "��Ʊ����� : %.2f", ((double)invkindData->InvMaxMoney)/SUM_EXTENSION);
// 	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
// 	
// 	
// 	sprintf(pGeneralPrnBuff, "��Ʊ��С��� : %.2f", ((double)invkindData->InvMinMoney)/SUM_EXTENSION);
// 	 PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
// 
// 	
// 	ForwardNLine(FORWARD_LINES);
	
	return 0;
}
/**************************************************************************

����     �����ʼ���ص���Ϣ

��ʽ     ��int print_initinfo()

������� ��

         ��

������� ��

����ֵ   ��

����     ��

����     ��

ժҪ     ��

**************************************************************************/
/*		��ʱע��	BY ZL
void  print_initinfo(UINT8 Init_Update)

{

	UINT32 curDate = GetCurDate();

	UINT8 i, j;

	struct TTaxItemPrnData taxItemPrnData;

	struct TTaxItem	taxItem;

	INT8 tmpCode[2 * TAX_ITME_CODE_LEN + 1];

	

	PrinterIni(BIDIRECTIONAL);



	SetLineSpace(REPORT_LINE_SPACE);

	if (Init_Update == 1)

		PrintRptTitle(" �� ʼ �� �� ��");

	else

		PrintRptTitle(" ��Ϣ���� �� ��");

	

	//sprintf(pGeneralPrnBuff, "��ʼ�� �� �� : %04lu-%02lu-%02lu", G_SysArg->daySumStartDate / 10000,

			//(G_SysArg->daySumStartDate % 10000) / 100, G_SysArg->daySumStartDate % 100);

	if (Init_Update == 1)

	{

		sprintf(pGeneralPrnBuff, "��ʼ�� �� �� : %04lu-%02lu-%02lu", curDate / 10000,

			(curDate % 10000) / 100, curDate % 100);

	}

	else

	{

		sprintf(pGeneralPrnBuff, "��Ϣ�������� : %04lu-%02lu-%02lu", curDate / 10000,

			(curDate % 10000) / 100, curDate % 100);

	}

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� λ  �� �� : %s", G_SysArg->corpInfo.Name);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� λ  �� �� :                       ");

	bin2char(G_SysArg->corpInfo.CorpNo, &pGeneralPrnBuff[15], CORP_NO_LEN);	

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "˰        �� : %s", G_SysArg->corpInfo.TaxCode);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "˰�ؿ� �� �� :                       ");

	bin2char(G_SysArg->corpInfo.FCardNo, &pGeneralPrnBuff[15], FCARD_NO_LEN);	

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "˰�ؿ�ԭʼPIN�� :                    ");

	bin2char(G_SysArg->corpInfo.FCardPwd, &pGeneralPrnBuff[17], FCARD_PWD_LEN);	

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));



	sprintf(pGeneralPrnBuff, "�� ��  �� �� : %04lu-%02lu-%02lu", G_SysArg->corpInfo.StartDate / 10000, 

		(G_SysArg->corpInfo.StartDate % 10000) / 100, G_SysArg->corpInfo.StartDate % 100);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "�� Ч  �� �� : %04lu-%02lu-%02lu", G_SysArg->corpInfo.ValidDate / 10000, 

		(G_SysArg->corpInfo.ValidDate % 10000) / 100, G_SysArg->corpInfo.ValidDate % 100);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "���ܻ��ر�� :                       ");

//	bin2char(corpData->ZGFJNo, &pGeneralPrnBuff[15], ZGJG_CODE_LEN);	

	sprintf(&pGeneralPrnBuff[15], "%010lu", G_SysArg->corpInfo.ZGFJNo);	

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	if (G_SysArg->corpInfo.DeclareType == 1)

	{

		sprintf(pGeneralPrnBuff, "�� ��  �� ʽ : �û����걨");

		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	}

	else

	{

		sprintf(pGeneralPrnBuff, "�� ��  �� ʽ : ������ʽ�걨");

		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	}

	

	sprintf(pGeneralPrnBuff, "��Ʊ��ֹ���� : %04lu-%02lu-%02lu", G_SysArg->corpInfo.InvEndDate / 10000, 

		(G_SysArg->corpInfo.InvEndDate % 10000) / 100, G_SysArg->corpInfo.InvEndDate % 100);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));



	sprintf(pGeneralPrnBuff, "���ŷ�Ʊ�޶� : %11.2f", ((double)(G_SysArg->corpInfo.SingleInvLimit)) / SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��Ʊ�ۼ��޶� : %11.2f", ((double)(G_SysArg->corpInfo.PosInvAccLimit)) / SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��Ʊ�ۼ��޶� : %11.2f", ((double)(G_SysArg->corpInfo.ReInvAccLimit)) / SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "˰��         ����            ˰��");

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	memset((void *)&taxItemPrnData, 0, sizeof(struct TTaxItemPrnData));

	for (i=0; i<TAX_ITEM_MAX_COUNT; i++)

	{

		if (G_SysArg->taxItemID[i] == 0)

			continue;

		

		taxItemPrnData.TaxItems[i].ID = G_SysArg->taxItemID[i];

		for (j=0; j<TAX_ITEM_RECORD_NUM; j++)

		{

			memset((void *)&taxItem, 0, sizeof(struct TTaxItem));

			if (ReadTaxItem(j, &taxItem) == FAILURE)

			{

				MsgBox("��ȡ����ʧ��", g_messageArray[CASH_KEY_RETURN], E_ERRO);

				return;

			}

			

			if (taxItem.ID == G_SysArg->taxItemID[i])

			{

				memcpy((void *)taxItemPrnData.TaxItems[i].Code, (void *)taxItem.Code, TAX_ITME_CODE_LEN);

				memcpy((void *)taxItemPrnData.TaxItems[i].ChName, (void *)taxItem.ChName, TAX_ITEM_NAME_LEN);

				memcpy((void *)taxItemPrnData.TaxItems[i].EnName, (void *)taxItem.EnName, TAX_ITEM_NAME_LEN);



				taxItemPrnData.TaxItems[i].TaxRate	= taxItem.TaxRate;

				

				break;

			}

		}

	}

	for (i=0; i < TAX_ITEM_MAX_COUNT ;i++)

	{

		if (taxItemPrnData.TaxItems[i].ID == 0)

		{

			continue;

		}

		

		memset((void *)tmpCode, 0, TAX_ITME_CODE_LEN * 2 + 1);

		bin2char(taxItemPrnData.TaxItems[i].Code , tmpCode , TAX_ITME_CODE_LEN ); 

		sprintf(pGeneralPrnBuff, "%2u         %s          %.2f%%", taxItemPrnData.TaxItems[i].ID, 

			tmpCode, ((double)(taxItemPrnData.TaxItems[i].TaxRate))/100);

		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

		

		sprintf(pGeneralPrnBuff, " �������� : %s", taxItemPrnData.TaxItems[i].ChName);

		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

		

		sprintf(pGeneralPrnBuff, " Ӣ������ : %s", taxItemPrnData.TaxItems[i].EnName);

		PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	}

	

	ForwardNLine(FORWARD_LINES);

	return;

}
*/





/**************************************************************************

����     ����ӡ��Ʊ�޶��ѯ

��ʽ     ��INT8 print_invoiceLimits( struct TInvLimitPrnData *invLimits,UINT8 bFindBlackMark )

������� ��struct TInvLimitPrnData *invLimits  ��Ʊ�޶���Ϣ

         ��UINT8 bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ�

                               ��ʼ��ӡ

������� ��

����ֵ   ��-1����ʧ�ܣ�0�����ɹ�

����     ��

����     ��

ժҪ     ��

**************************************************************************/



INT8 print_invoiceLimits( struct TInvLimitPrnData *invLimits, UINT8 bFindBlackMark )

{

//	PrinterIni(BIDIRECTIONAL);
PrinterIni(bidirection);


	SetLineSpace(REPORT_LINE_SPACE);

	

	PrintRptTitle("�� Ʊ  �� ��");



	sprintf(pGeneralPrnBuff, "�� λ  �� �� : %s", invLimits->CorpName);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "˰        �� : %s", invLimits->TaxCode);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��   ��   �� : %s", invLimits->MachineNo);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	sprintf(pGeneralPrnBuff, "���ŷ�Ʊ�޶� :  %.2f", ((double)(invLimits->SigleInvLimit)) / SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��Ʊ�ۼ��޶� :  %.2f", ((double)(invLimits->PosInvTotalLimit)) / SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��Ʊ�ۼ��޶� :  %.2f", ((double)(invLimits->ReInvTotalLimit)) / SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	ForwardNLine(FORWARD_LINES);

	return 0;

}



/**************************************************************************

		��ʽ������

		

����     ���Խ���

����     ��2005-04-04

**************************************************************************/



/*char * format_date(char * date)

{

	char tmpdate[9];

	

	memcpy(tmpdate,date,8);

	

	date[4] = '-' ;

	date[7] = '-' ;

	

	memcpy(date+5,tmpdate+4,2);

	memcpy(date+8,tmpdate+6,2);

	

	return  date ;

}*/



/**************************************************************************

		��ʽ���·�

		

����     ���Խ���

����     ��2005-04-06

**************************************************************************/



/*char * format_month(char * month)

{

	char tmp_month[7];

	

	memcpy(tmp_month,month,6);

	

	month[4] = '-' ;

	

	memcpy(month+5,tmp_month+4,2);

	

	return  month ;

}*/





/*-------------------------------------------------------------------------

		����վҪ�� ��ͳ�� ����

		

����     ���Խ���                       

����     ��2005-04-06

---------------------------------��ͷ��----------------------------------*/



/*void print_Head( struct TBegin_End_Date *Begin_End_Date, \

						   int x0,int y0,char *Title, \

						   int x1,int y1,char *FieldName_1, \

						   int x2,int y2,char *FieldName_2, \

						   int x3,int y3,char *FieldName_3 )

{

	PrinterIni();



	SetLineSpace(REPORT_LINE_SPACE);

	

	PrintRptTitle(Title);

	

	memset((void *)pGeneralPrnBuff, ' ', MAX_CHAR_NUM);

	pGeneralPrnBuff[MAX_CHAR_NUM] = 0x0;



	memcpy((void *)&pGeneralPrnBuff[x1 - strlen(FieldName_1)], (void *)FieldName_1, strlen(FieldName_1));

	memcpy((void *)&pGeneralPrnBuff[x2 - strlen(FieldName_2)], (void *)FieldName_2, strlen(FieldName_2));

	memcpy((void *)&pGeneralPrnBuff[x3 - strlen(FieldName_3)], (void *)FieldName_3, strlen(FieldName_3));

	

	SetLineSpace(REPORT_LINE_SPACE2);

	

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	PrintSeparateLine();



	return;	

}





//--------------------------- ���С�-----------------------------



void print_invDetail_Line( struct TInvDetail_Line *invDetail_Line )

{

	SetLineSpace(REPORT_LINE_SPACE2);



	sprintf(pGeneralPrnBuff, "%04lu-%02lu-%02lu", invDetail_Line->Date / 10000, 

		(invDetail_Line->Date % 10000) / 100, invDetail_Line->Date % 100);

	sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], "      %010lu", invDetail_Line->InvNo);

	sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], "  %11.2f", ((double)(invDetail_Line->Sum)) / SUM_EXTENSION);

	

	PrintAsciiLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));



	return;		

}*/



//-----------------------------��β��----------------------------------



void print_invDetail_End( struct TInvDetail_End *invDetail_End )

{



	SetLineSpace(REPORT_LINE_SPACE2);

	

//	PrintSeparateLine();

	

	sprintf(pGeneralPrnBuff, "��Ʊ��� : %11.2f", ((double)(invDetail_End->PosInvSum)) / SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��Ʊ��� : %11.2f", ((double)(invDetail_End->ReInvSum)) / SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	sprintf(pGeneralPrnBuff, "��  ��� : %11.2f", ((double)(invDetail_End->NetInvSum)) / SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));



	ForwardNLine(FORWARD_LINES);

	

	return;	

}





//-----------------------------------���С�-----------------------------------



/*void print_Day_Line( struct TDay *day )

{

	SetLineSpace(REPORT_LINE_SPACE2);



	sprintf(pGeneralPrnBuff, "%04lu-%02lu-%02lu", day->Date / 10000, 

		(day->Date % 10000) / 100, day->Date % 100);

	sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], "    %6lu", day->Amount);

	sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], "       %11.2f", ((double)(day->Sum)) / SUM_EXTENSION);

	

	PrintAsciiLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));



	return;		

}*/



//--------------------------------��β��----------------------------------



void print_NetSum_End( INT64 NetSum , INT64 LiterSum)

{

	SetLineSpace(REPORT_LINE_SPACE2);

	

//	PrintSeparateLine();

	

	sprintf(pGeneralPrnBuff, "��  ��� : %11.2f", ((double)(NetSum)) / SUM_EXTENSION);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

#if DALIAN_VER

#else

    sprintf(pGeneralPrnBuff, "�������� : %11.2f", ((double)(LiterSum)) / 100);

    PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

#endif

//	ForwardNLine(FORWARD_LINES);

	

	return;

}





//-----------------------------------���С�----------------------------------- 



void print_Month_Line( struct TMonth *Month )       

{

	SetLineSpace(REPORT_LINE_SPACE2);



	sprintf(pGeneralPrnBuff, "%04lu-%02lu", Month->month / 100,  Month->month % 100);

	sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], "      %6lu", Month->Amount);

	sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], "        %11.2f", ((double)(Month->Sum)) / SUM_EXTENSION);

	

	PrintAsciiLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));



	return;	

}



//-----------------------------------���С�----------------------------------- ����



/*void print_Sales_Line( struct TSalesman *Salesman )       

{

	SetLineSpace(REPORT_LINE_SPACE2);



	sprintf(pGeneralPrnBuff, "%-10s", Salesman->Name);

	sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], " %11lu", Salesman->Amount);

	sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], "       %11.2f", ((double)(Salesman->Sum)) / SUM_EXTENSION);

	

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));



	return;	

}*/



/*------------------------------------------------------------------------------



��Ʒ���� 



����: �Խ���



����: 2005-04-07



-----------------------------------���С�-------------------------------------*/



void print_Goods_Line( struct TGoods * Goods ) // ��Ʒ������

{

	SetLineSpace(REPORT_LINE_SPACE2);

#if DALIAN_VER

	sprintf(pGeneralPrnBuff, "%-20s", Goods->GoodsName);

#else

	sprintf(pGeneralPrnBuff, "%-12s", Goods->GoodsName);

#endif	



#if DALIAN_VER

	sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], " %19.2f", ((double)(Goods->SalesSum)) / PRICE_EXTENSION);

#else

	if (memcmp((void *)Goods->GoodsName, "����", 4)!=0)

	{	

		sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], " %7.2f", ((double)(Goods->Price)) / PRICE_EXTENSION);

		sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], " %7.2f", ((double)(Goods->GoodsNum)) / 100);

		sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], " %10.2f", ((double)(Goods->SalesSum)) / SUM_EXTENSION);

	}

	else

	{

		sprintf(&pGeneralPrnBuff[strlen(pGeneralPrnBuff)], " %26.2f", ((double)(Goods->SalesSum)) / SUM_EXTENSION);	

	}

#endif

	prn_log2("pGeneralPrnBuff = \"%s\"", pGeneralPrnBuff);

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));



	return;	

}



INT8 PrintRptTitle(INT8 *title)

{

	UINT8 i;

	UINT8 N;

	

	N = strlen(title);

	

	N = (MAX_CHAR_NUM - N) / 2;

	for(i=0; i<N; i++)

	{

		pGeneralPrnBuff[i] = ' ';

	}

	sprintf(&pGeneralPrnBuff[N],"%s", title);

	

	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));

	

	return 0;

}

char PrintYwtm(char *title)
{
	unsigned char i;
	unsigned char N;
	
	N = strlen(title);
	N = (46 - N) / 2;
	
	for(i=0; i<N; i++)	
	{
		
		pGeneralPrnBuff[i] = ' ';

	}
	
	sprintf(&pGeneralPrnBuff[N],"%s", title);
	
	PrintReportLine(pGeneralPrnBuff, strlen(pGeneralPrnBuff));
	
	return 0;	
}











































