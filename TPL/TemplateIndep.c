/*! \file    TemplateIndep.c
\brief    ��ӡģ��ӿ�ʵ�֡�
\author   Xiao Pengkun   2005-07-20
 */

//#define POS_DEBUG_TO_TTY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      /*�ļ�����*/

#include "TemplateIndep.h" 
#include "TemplateGeneralFuc.h"
#include "TemplateInterface.h"  
#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_log.h"

UINT8  templateBuffer[PRINT_TEMPLATE_BUF_LEN] = "BEGIN\n\
0~TEMP_TYPE#0~VER#2.31~DIS#����~DATE#20050621~\n\
1~TYPE#76#128~FONT#16#16~MARK#0~END_FORWARDPOINT#450~BEGIN_FORWARDPOINT#142~BACKWARD_POINT#80~MAX_GOODS_COUNT#6~INV_76_MM#1~REPAIR#0~SKDW_MAX#28~FKDW_MAX#23~SPMC_MAX#12~SKY_MAX#4~JEDX_MAX#26~\n\
2~LN#2~HEAD#~FONT#8#8~ROWH#30~ROWBH#16~LB#0#��Ʊ����:#2~CO#FPHM#12~\n\
2~LN#3~HEAD#~FONT#8#8~ROWH#30~ROWBH#16~LB#0#�������:#2~CO#JQBH#12~\n\
2~LN#4~HEAD#~ROWH#30~ROWBH#32~EMPTY_FORWARD#15~LB#0#�տλ:#2~CO#SKDW#12~\n\
2~LN#5~HEAD#~FONT#8#8~ROWH#30~ROWBH#15~LB#0#˰��:#2~CO#SWDJH#6~\n\
2~LN#7~HEAD#~ROWH#30~ROWBH#15~LB#0#��Ʊ����:#2~CO#KPRQ#12~LB#0#�տ�Ա:#24~CO#SKY#34~\n\
2~LN#6~HEAD#~ROWH#30~ROWBH#24~EMPTY_FORWARD#-10~LB#0#���λ(����):#2~CO#FKDW#18~\n\
2~LN#9~HEAD#~ROWH#30~ROWBH#10~LB#0#��Ŀ#2~LB#0#����#19~LB#0#����#28~LB#0#���#38~\n\
2~LN#7~CYCLE_BEGIN#~\n\
2~LN#15~DATACYCLE#~ROWH#20~ROWBH#16~CO#SPMC#1~CO#SPDJ#-22~CO#SPSL#28~CO#SPJE#-41~\n\
2~LN#16~START_TAIL#~\n\
2~LN#20~TAIL#~ROWH#40~ROWBH#18~LB#1#�ϼ�(Сд):#2~CO#JEXX#-41~\n\
2~LN#21~TAIL#~ROWH#40~ROWBH#20~EMPTY_FORWARD#0~LB#1#�ϼ�(��д):#2~CO#JEDX#12~\n\
2~LN#16~TAIL#~ROWH#40~ROWBH#20~LB#1#˰����:#2~CO#SKM#12~\n\
END\n";

UINT8 CycleTempLineBuf[TEMPLATE_LINE_BUF_LEN];

//���Ӵ����־sub_inv,���Ӵ����ӡ��λ��sub_place
UINT8 stubFlag = 0;
UINT8 stubPlace = 0;

//��Ʊ����д��־continueWriteFlag,��Ʊ����дλ��continueLocation
UINT8 continueWriteFlag = 0;
UINT8 continueWriteLocation = 0;

//ģ��ѭ���б�ǣ����ģ��������NEXT_CYCLE = 1,˵����һ����ѭ��ģ���У�Ϊ�˽�����ͨ��������İ취
UINT8 CycleTempFlag = 0;
UINT8 BeginCycleTemp = 0;

// �洢��Ҫ�����ģ����Ϣ(�޸�Ϊȫ�ֵ�)
TSaveTemplateInfo saveTemplateInfo;
TSaveTemplateInfo *pSaveTemplateInfo = &saveTemplateInfo;


//ģ����0��ģ����1�ṹ��
static TPrnTempLine1 prnTempLine1;
static TPrnTempLine0  prnTempLine0;

//ָ��ģ�����ݻ����ָ��
static UINT8 *prnTempBuf = templateBuffer;

//���մ�ӡ�нṹ��,������ӡ����ʹ��
static TPrnLineInfo  PrintLineInfo;
static TPrnLineInfo *pPrnLineInfo = &PrintLineInfo;

//���մ�ӡ�нṹ��,�����������ʹ��
static TPrnLineInfo  TurnBackLineInfo;
static TPrnLineInfo *conWriteBuffer=&TurnBackLineInfo;

//ģ����2�ṹ��
static TPrnTempRow   prnTempLine2;
static TPrnTempRow   *pprnTempLine2=&prnTempLine2;

//���Է�Ʊ�ṹ��
static TPrnInvoiceInfo testInv;
static TPrnInvoiceInfo *testInvPtr=&testInv;
//��Ʒ��ϸ�����
INT8 templateNo = 0;

//��ҵ���ƴ�ӡ����
extern UINT8 CorpNameCounte;
extern UINT8 *startPointer;
extern UINT8 *endPointer;

//��ӡ��Ʊ�ṹ�壨ȫ�֣�
TPrnInvoiceInfo g_invPrnData;

void ResetTempBuf(void )
{
    prnTempBuf = templateBuffer;
    memset(conWriteBuffer,0,sizeof(TurnBackLineInfo));
    if(pPrnLineInfo != NULL )
    {
       memset(pPrnLineInfo,0,sizeof(PrintLineInfo));
    }
    memset(pprnTempLine2,0,sizeof(prnTempLine2));
    pPrnLineInfo = NULL;
    CycleTempFlag = 0;
}


void CreateInvData( TPrnInvoiceInfo *pInvPrnData )
{
    INT32 i=0;
    pInvPrnData->PrintType = STUB_PRINT_TEMPLATE;
    /* ��Ʊ���� */
    pInvPrnData->InvType =1 ;
    /* ԭ��Ʊ���� */
    pInvPrnData->PosInvNo =0;

    // ��Ʊ���� CCYYMMDD             
    pInvPrnData->m_Date=20050812U;

    /* ��Ʊ������ 10 BCD             */
    memcpy(pInvPrnData->chTypeCode,"12345678901234567890",20);
    
    /*��Ʊ����                      */
    pInvPrnData->InvNo =88888888U;
 
    /*��˰������ 40 ASC           */
    memcpy((void *)pInvPrnData->chCorpName,"qwsa������Ϣ�ɷ����޹�˾1234sd��Ϣ�й�ss",40);
    
    /*��˰�˱�� 16 ASC           */
    memcpy(pInvPrnData->chCorpNo,"1234567890123456",16);
    
    /* ˰�� 20 ASC                  */ 
    memcpy((void *)pInvPrnData->chCorpCode,
                   "12345678901234567890",20);
    
    /*������ 40 ASC                 */
    memcpy((void *)pInvPrnData->chClientName,"qwsa������Ϣ�ɷ����޹�˾1234sd��Ϣ�й�ss" ,40);
    
    /*�������� 16 ASC             */
    memcpy((void *)pInvPrnData->chMachineNo,"1234567890123456",16);
       
    /*��ƱԱ���			       */
    pInvPrnData->OperatorID =255U ;
    
    /*��ƱԱ������10 ASC       */
    memcpy((void *)&pInvPrnData->chOperatorName,"123456    ",10);
    
    /*�̵����       */
    memcpy(pInvPrnData->chShopNo,"1234567890",10);

    /*��ҵ�Զ��������� */
    memcpy(pInvPrnData->chMachineIndex,"1234567890",10);

    /*��Ʊ�ܽ�� ��λ���� */
    pInvPrnData->InvSumLowcase =4000000000U;
    
    /*��Ʊ�ܽ�� ��λ����  ��д*/
    memcpy(pInvPrnData->chInvSumUppercase,"��ǪҼ�۷�ʰ������Ǫ���½ʰ��Բ�ƽǾ���",40);
    
    /*˰����*/
    memcpy(pInvPrnData->chTaxCtrCode,"00123456789012345678",20);
   
	
    /* ��Ʒ������                   */
    pInvPrnData->GoodsLineCount = 3;
	
    for(i=0;i<3;i++)
    {
        pInvPrnData->GoodsLines[i].Amount =10000U;

        pInvPrnData->GoodsLines[i].Price =3000U;
        pInvPrnData->GoodsLines[i].Sum =300;

        pInvPrnData->GoodsLines[i].TaxItemIndex =i+1 ;

        memcpy((void *)pInvPrnData->GoodsLines[i].chProductPLUCode,"1234567890123456",16 );

        memcpy((void *)pInvPrnData->GoodsLines[i].chProductName, 
                           "qwsa������Ϣ�ɷ����޹�˾1234sd��Ϣ�й�ss",40);
        i++;
    }
}


UINT8  CheckTempValid(void)
{	
	UINT8 ii;
	TPrnLineInfo *pPrnLineInfo = NULL;
	ResetTempBuf();
    memset(testInvPtr,0,sizeof(TPrnInvoiceInfo));
    
    //������Ʊ��������
    CreateInvData(testInvPtr);
     
	for(;;)
	{
		if( (ii = ParseTempLine(testInvPtr,&pPrnLineInfo)) != 0 )
		{
		 	ResetTempBuf();
			prn_log2("ParseTempLine return %u ", ii);
			return 1;
			
		}
		else
		{			
			if(CycleTempFlag == 1)
			{
				CycleTempFlag = 0;
				continue;
			}
      
			if (pPrnLineInfo == NULL)
			{
				break;
			}

		}
	}

     ResetTempBuf();
	 SKYContinueFlag = 0;
     return 0;
} 

UINT8  ParseTempLine(TPrnInvoiceInfo *pInv,TPrnLineInfo **pPrnLine)
{
	
	UINT8 *tempLineBuf=NULL;	
	UINT8 chBegin=0;
	UINT8 hzNum = 0;
	UINT8 HZCounte = 0;
	UINT8 ascNum = 0;
	UINT8 gbhz = 0;	
	UINT8 ii = 0;
    prn_log("start ParseTempLine ");

	if(pPrnLineInfo == NULL)
	{
	    pPrnLineInfo = &PrintLineInfo;	   
	}

    if( pInv == NULL )
    {
        return 1;
    } 
	
	InitPrinLineInfo(pPrnLineInfo);
	
		
	memset(pprnTempLine2,0,sizeof(TPrnTempRow));
	
	    
    //��ӡ���Ӵ��
    if (stubFlag == 1)
	{	
		strncpy(&(pPrnLineInfo->chContent[stubPlace]),"��  ��  ��  ��",strlen("��  ��  ��  ��"));
	    stubFlag =0;
	    pPrnLineInfo->FontW = prnTempLine1.FontW;
		pPrnLineInfo->FontH = prnTempLine1.FontH;
		pPrnLineInfo->Bhigh = 16;		//Ϊ�˴�ӡ�� ���Ӵ��  ���жξ��룬д��Ϊ16��̫����
			
    	*pPrnLine= pPrnLineInfo;
        prn_log("end ParseTempLine ");
        return 0;
	}

	if((stubFlag ==2) && (pSaveTemplateInfo->workMode != WORK_MODE))
	{
		strncpy(&(pPrnLineInfo->chContent[stubPlace]),"�� �� �� ��",strlen("�� �� �� ��"));
	    stubFlag =0;
	    pPrnLineInfo->FontW = prnTempLine1.FontW;
		pPrnLineInfo->FontH = prnTempLine1.FontH;
	
    	*pPrnLine= pPrnLineInfo;
        prn_log("end ParseTempLine ");
        return 0;
	}
	//���д�ӡ
    if( (continueWriteFlag == 1) || (continueWriteFlag == 2))
	{
		continueWriteFlag = 0;	
		conWriteBuffer->FontW = prnTempLine1.FontW;
		conWriteBuffer->FontH = prnTempLine1.FontH;
        *pPrnLine= conWriteBuffer;
       
        prn_log("end ParseTempLine ");
        return 0;
	}

	if (continueWriteFlag == 3)
	{
		prn_log2("CorpNameCounte = %u", CorpNameCounte);
		if (CorpNameCounte == 0)
		{
			continueWriteFlag = 0;	
			conWriteBuffer->FontW = prnTempLine1.FontW;
			conWriteBuffer->FontH = prnTempLine1.FontH;
        }
        else
        {
        	while(1)
			{
				if (*endPointer == '\0')
				{
					CorpNameCounte = 0;
					break;
				}
				if (HZCounte == (42 - continueWriteLocation) / 2)
				{
					break;
				}
				gbhz = is_gb_4byte(endPointer);
				prn_log2("gbhz = %u", gbhz);
				if (gbhz == 2)
				{
					endPointer += 4;
					HZCounte++;
				}
				if (gbhz == 1)
				{
					endPointer += 2;
					HZCounte++;
				}
				if (gbhz == 0)
				{
					endPointer += 1;
					ascNum++;
					if (ascNum == 2)
					{
						HZCounte++;
						ascNum = 0;
					}
				}
				prn_log2("endPointer = %x", endPointer);
			}
			prn_log2("HZCounte = %u", HZCounte);
			prn_log2("endPointer-startPointer = %u", endPointer-startPointer);
			strncpy(&(conWriteBuffer->chContent[continueWriteLocation-1]), (INT8 *)startPointer, endPointer-startPointer);
			conWriteBuffer->chContent[continueWriteLocation-1+endPointer-startPointer] = 0x00;
			prn_log2("conwritebuffer����  %s", conWriteBuffer->chContent);
			startPointer = endPointer;
			HZCounte = 0;
			*pPrnLine = conWriteBuffer;
			
			return 0;
        }
	}
	
	InitPrinLineInfo(conWriteBuffer);
	

	tempLineBuf = NULL;
	GetTemplateLineBuffer((void **)&tempLineBuf);
    	
	if (!tempLineBuf)
	{
		prn_log("tempLineBuf == NULL");
		return 1;
	}
	
	if(CycleTempFlag == 0)
	{
		if( (ii = GetPtLine(&prnTempBuf,tempLineBuf)) != 0)
		{
			prn_log("��ȡ��һ��ģ����");
			prn_log2("ii = %d", ii);
			
			return 2;
		}	
    }
    //���ѭ���п�ʼ��־Ϊ1����tempLineBuf���ݿ�����һ��ģ���л�����
	if(BeginCycleTemp == 1)
	{
		memset((void *)CycleTempLineBuf, 0, TEMPLATE_LINE_BUF_LEN);
		memcpy((void *)CycleTempLineBuf, (void *)tempLineBuf, TEMPLATE_LINE_BUF_LEN);
		BeginCycleTemp = 0;
	}
	//ѭ�������ݱ�־Ϊ1��ֱ�ӵ��ý����洢����һ��ģ����
	if(CycleTempFlag == 1)
	{
		templateNo += 1;
		
		if( ParsePtLine2(CycleTempLineBuf,pprnTempLine2,pPrnLineInfo,&prnTempLine1) != 0)
        {
            return 3;
        }
        
        prn_log2("pPrnLineInfo->Property = %d",pPrnLineInfo->Property);
        
        
		if( GetPrnLineData(pprnTempLine2,conWriteBuffer,
                          &prnTempLine1,pPrnLineInfo,pInv) != 0)
        {
            return 4;
        }	
        
		
		//������Ĵ�ӡ���е�'\0'�滻Ϊ�ո�,�����е�ĩβ;
		ScanReplaceSpace(pPrnLineInfo);
		prn_log2("pPrnLineInfo->chContent = %s",pPrnLineInfo->chContent);
		prn_log2("pPrnLineInfo->FontH = %d", pPrnLineInfo->FontH);
		*pPrnLine= pPrnLineInfo;
        prn_log("end ParseTempLine ");
        return 0;	
	}
	
	//ͨ���ж�ģ���е�һ���ַ���ѡ��������
	chBegin = *tempLineBuf;
	
	//ģ���н�������������ӡ�нṹ��ģ���л�����Ϊ��ʼ״̬���ȴ���һ�ε��ã�			
	if (*tempLineBuf == 'E')
	{
        prn_log("ģ�������һ��");      
		pPrnLineInfo = NULL;
		memset(tempLineBuf,0,TEMPLATE_LINE_BUF_LEN);
		prnTempBuf = templateBuffer;
		templateNo = 0;              
	}	
	
	else
	{		
		
		switch(chBegin)
		{
		case '2':		
			 
			
			if( ParsePtLine2(tempLineBuf,pprnTempLine2,pPrnLineInfo,&prnTempLine1) != 0)
            {
                return 3;
            }

			if( GetPrnLineData(pprnTempLine2,conWriteBuffer,
                              &prnTempLine1,pPrnLineInfo,pInv) != 0)
            {
                return 4;
	        }				
	        				
			//������Ĵ�ӡ���е�'\0'�滻Ϊ�ո�,�����е�ĩβ;
			ScanReplaceSpace(pPrnLineInfo);
			
			prn_log2("pPrnLineInfo->chContent = %s",pPrnLineInfo->chContent);
			prn_log2("pPrnLineInfo->FontH = %d", pPrnLineInfo->FontH);
						
			break;
			
		case '1': 
			if( ParsePtLine1(tempLineBuf,&prnTempLine1) != 0)
            {
                   return 3;
            }
			
			/*�����󣬽�ģ����1�ṹ���е���Ӧ����ֵ������ӡ�нṹ�壬����
			 * �����ԣ���ʼ��ֽ���룬������ֽ������Ƿ��Һڱ�,����ĸ߶ȺͿ�� */
			 
			pPrnLineInfo->Property = NEED_SAVE_TEMPLATE_LINE;
			pPrnLineInfo->BeginForwardPoint = (INT16)prnTempLine1.BeginForwardPoint;
			pPrnLineInfo->EndForwardPoint = (INT16)prnTempLine1.EndForwardPoint;
			pPrnLineInfo->MarkFlag = prnTempLine1.MarkFlag;
			pPrnLineInfo->FontW = prnTempLine1.FontW;
			pPrnLineInfo->FontH = prnTempLine1.FontH;

			pPrnLineInfo->BackwardPoint = prnTempLine1.BackwardPoint;
			
			prn_log2("pPrnLineInfo->BackwardPoint = %d",pPrnLineInfo->BackwardPoint);
	
			
			break;
			
		case '0':
		
			if( ParsePtLine0(tempLineBuf,&prnTempLine0) != 0 )
            {
                  return 3;
            }
			
			pPrnLineInfo->Property = INVALID_TEMPLATE_LINE;	
			
			break;
			
		case 'B':	
		
			pPrnLineInfo->Property = INVALID_TEMPLATE_LINE;	
			break;
		default:
		    return 5;
		}		

		memset(tempLineBuf,0,TEMPLATE_LINE_BUF_LEN);
		
	}//end of else
	
	*pPrnLine= pPrnLineInfo;
   prn_log("end ParseTempLine ");
    return 0;	
}


/**************************************************************************
����     ������ģ������
��ʽ     ��SaveTemplate(TSaveTemplateInfo *pSaveTemplateInfo)
������� ��void 
������� ��UINT8
����ֵ   ��
����     ��
ժҪ     ��
**************************************************************************/
TSaveTemplateInfo * SaveTemplate(void)
{
    memset(pSaveTemplateInfo,0,sizeof(TSaveTemplateInfo));
	pSaveTemplateInfo->markFlag = prnTempLine1.MarkFlag;
	pSaveTemplateInfo->MaxSPMCCharacter = prnTempLine1.MaxSPMCCharacter;
	pSaveTemplateInfo->EndBackwardFlag = prnTempLine1.EndBackwardFlag;
	pSaveTemplateInfo->EndForwardPoint = (UINT16)prnTempLine1.EndForwardPoint;
	pSaveTemplateInfo->MaxGoodsCount = prnTempLine1.MaxGoodsCount;
	pSaveTemplateInfo->BackwardPoint  = prnTempLine1.BackwardPoint;
	pSaveTemplateInfo->RepairPoint  = prnTempLine1.RepairPoint; //zongcan test
	pSaveTemplateInfo->QRCodeLeftMargin = prnTempLine1.QRCodeLeftMargin;
	prn_log2("pSaveTemplateInfo->markFlag %d", pSaveTemplateInfo->markFlag);
	prn_log2("pSaveTemplateInfo->MaxSPMCCharacter %d", pSaveTemplateInfo->MaxSPMCCharacter);
	prn_log2("pSaveTemplateInfo->MaxGoodsCount %d", pSaveTemplateInfo->MaxGoodsCount);
	prn_log2("pSaveTemplateInfo->BackwardPoint %d", pSaveTemplateInfo->BackwardPoint);
	prn_log2("pSaveTemplateInfo->QRCodeLeftMargin %d", pSaveTemplateInfo->QRCodeLeftMargin);
/**********for 57mm***********/
	pSaveTemplateInfo->InvFlag76     = prnTempLine1.InvFlag76;
/**********for 57mm***********/

	return pSaveTemplateInfo;
}

UINT8 ReadPrintTemplate(UINT8 TemplateNo)
{
	prn_log("CGlobalArg::ReadPrintTemplate");

	UINT8 *TemplateBuf;
	TemplateBuf = templateBuffer;
	UINT32 len = PRINT_TEMPLATE_BUF_LEN;
#ifndef WIN32
	INT8 tmp[16];
	INT8 name[32];
	INT32 fd;
	
	memset(name, 0, sizeof(name));
	sprintf(name, "%s%02u.txt", PRINT_TEMPLATE_FILE_NAME, TemplateNo);
	prn_log2("Template file: %s", name);
	
	if ( (fd = open(name, O_RDONLY)) == -1 )
	{
		prn_log("open Template file err");
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

UINT8 LoadPrintTemplate(UINT8 TemplateNo)
{
	UINT8 errcode;
	if (ReadPrintTemplate(TemplateNo) != SUCCESS)
	{
		errcode = 5;//BOOT_NO_TEMPLATE;
		return errcode;
	}

	if (CheckTempValid() != 0)
	{
		errcode = 6;//BOOT_INVALID_TEMPLATE;
		return errcode;
	}

	SaveTemplate();
	pSaveTemplateInfo->workMode = WORK_MODE; 
	pSaveTemplateInfo->FixedModeFlag = 1; 

	return SUCCESS;
}

void  SetTplInfoWorkMode(UINT8 workMode)
{
	pSaveTemplateInfo->workMode = workMode;
}
UINT8 GetTplInfoWorkMode()
{
	return pSaveTemplateInfo->workMode;
}

UINT8 GetTplInfoMarkFlag()
{
	return pSaveTemplateInfo->markFlag;
}

UINT8 GetTplInfoMaxGoodsCount()
{
	return pSaveTemplateInfo->MaxGoodsCount;
}

UINT8 GetTplInfoMaxSPMCCharacter()
{
	return pSaveTemplateInfo->MaxSPMCCharacter;
}
UINT16 GetTplInfoEndForwardPoint()
{
	return pSaveTemplateInfo->EndForwardPoint;
}

