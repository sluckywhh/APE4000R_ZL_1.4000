/*! \file    TemplateInterface.c
\brief    ģ��ӿ��ļ�
\author   Xiao Pengkun   2005-06-23
 */

#include "TemplateInterface.h"
#include "TemplateGeneralFuc.h"
#include "TemplateDataDesign.h"
#include "TemplateMacro.h"
#include <string.h>
#include <stdlib.h>
#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_log.h"


extern UINT8 DetailCancelFlag;
//extern void PrintHexData(UINT8 *data, UINT32 len);
extern INT8 templateNo;
extern TSaveTemplateInfo *pSaveTemplateInfo;

//���Ӵ������д�еı�־��λ��
extern UINT8 stubFlag;
extern UINT8 stubPlace;
extern UINT8 continueWriteFlag;
extern UINT8 continueWriteLocation;
extern UINT8 g_cungen;
//���ѭ��ģ����
extern UINT8 CycleTempFlag;
//�����һ��Ϊѭ��ģ����
extern UINT8 BeginCycleTemp;

//��ӡ�Ҷ��������м仺����
static INT8  saveRightBuf[32] ;


//�洢�տ�Ա��������
static INT8    saveSkyContent[10];
UINT32 saveRealLocation = 0;//��¼���д�ӡλ��
UINT8 SKYContinueFlag = 0;//�տ�Ա���б�־

UINT8 CorpNameCounte = 0;//��¼��ҵ������Ҫ�������
//UINT8 CorpAddrCounte = 0;//��¼��ҵ������Ҫ�������
UINT8 *startPointer = NULL;
UINT8 *endPointer = NULL;

UINT8  GetPtLine(UINT8 **prnTempBuf, UINT8 *tempLineBuf)
{	
    UINT32 len=0;      //ģ���еĳ��ȣ��������س�;

	UINT8 *pSaveInit = NULL;//ÿһ����ȡ�µ�ģ��������ʱģ�建��������ʼλ��;
	
    //prn_log(" start GetPtLine ");
	if (!(*prnTempBuf) || (!tempLineBuf))
	{
		return 1;
	}	
	
	pSaveInit = *prnTempBuf;
	
	
	//TEMPLATE_LINE_END_CHARACTERΪÿһģ���еĽ�����'\n'
	while ( ( *(*prnTempBuf) != TEMPLATE_LINE_END_CHARACTER)
	            && ( *(*prnTempBuf) != '\0' ))
	{
	    if(len >= TEMPLATE_LINE_BUF_LEN)
	    {
	    	return 2;
	    }
		(*prnTempBuf)++;
		
		len++;
	}
	(*prnTempBuf)++;
	
	//len+1�����س����з�������tempLineBuf
	len++;
	memcpy(tempLineBuf,pSaveInit,len);
    //prn_log(" end GetPtLine ");
    return 0;
}


UINT8  GetPtField(UINT8 **tempLineBuf,UINT8 *tempLineFieldBuf)
{
	UINT8 *pHead = *tempLineBuf;
	UINT32  len = 0;
	
	if (!(*tempLineBuf) || (!tempLineFieldBuf))
	{
		return 1;
	}
	
	//��ģ���л����е�����(����~֮�������)��ȡ������memcpy��tempLineFieldBuf
	
	
	//TEMPLATE_ATTRIBUTE_SEPERATE_CHARACTERΪ�ַ�'~'
	while ((*(*tempLineBuf) != TEMPLATE_ATTRIBUTE_SEPERATE_CHARACTER)
	          && (*(*tempLineBuf) != '\0' ) )
	{
	    if(len >= PRINT_TEMPLATE_LINE_FIELD_BUF_LEN)
	    {	
	    	return 2;
	    	
	    }
		(*tempLineBuf)++;
		len++;
	}
	(*tempLineBuf)++;
	memcpy(tempLineFieldBuf,pHead,len);
	
	return 0;
	
}



UINT8  ParsePtLine0(UINT8 *tempLineBuf, TPrnTempLine0 *tempLine0)
{
	UINT8 *pMatchTemplateBuffer=NULL;     
	UINT8 *tempLineFieldBuf=NULL;
	UINT8 *pSaveMatchTemplateBuffer=NULL;
	UINT8 *pSavetempLineFieldBuffer=NULL;
	
	
	UINT32 lengthOfField=0;	
        UINT32 l=0;
	UINT8 *pTempLineField = NULL;//����ģ��������~֮�����Ե���ʼλ��
        //prn_log("start ParsePtLine0");
	
	if ((!tempLineBuf) || (!tempLine0))
	{
		return 1;
	}
	
	//��ȡģ�������Ի��棬���洢����~֮�������
	GetTemplateLineFieldBuffer((void **)&tempLineFieldBuf);
    pSavetempLineFieldBuffer = tempLineFieldBuf;
	
	//��ȡƥ��ģ�����Ի��棬������~֮������#ǰ��ֵ
	GetMatchFieldLabelBuffer((void **)&pMatchTemplateBuffer);
    pSaveMatchTemplateBuffer = pMatchTemplateBuffer;
	
	
	//��ȥ0~
	tempLineBuf+=2;
	


	/*ѭ������ֱ��ģ���н�������ȡģ��������GetPtField��ͨ��
	  ƥ��ģ�����ԣ������Ӧֵ�ĸ�ֵ*/
	
	while ( (*tempLineBuf != TEMPLATE_LINE_END_CHARACTER) && 
	         (*tempLineBuf != '\0')  )
	{
		
		if( GetPtField(&tempLineBuf,tempLineFieldBuf) != 0 )
        {
             return 2; 
        }		
		
		lengthOfField = 0;
		pTempLineField = tempLineFieldBuf;
		while ((*tempLineFieldBuf != ATTIBUTE_SEPERATE_FIELD) && 
		         (*tempLineFieldBuf != '\0' ))
		{
			if(lengthOfField >= MATCH_FIELD_LABEL_BUF_LEN)
			{
			    return 2;
			}
			tempLineFieldBuf++;
			lengthOfField++;
		}

		memcpy(pMatchTemplateBuffer,pTempLineField,lengthOfField);
		
		//�ж��Ƿ�ΪTEMP_Type
		if(memcmp(pMatchTemplateBuffer,"TEMP_TYPE",lengthOfField) == 0)
			
		{
			tempLine0->TempType = atoi((INT8 *)++pTempLineField);
					
		}
        //�ж��Ƿ�ΪVER
		else if(memcmp(pMatchTemplateBuffer,"VER",lengthOfField) == 0)
		{			
                        l=strlen((INT8 *)++tempLineFieldBuf);
                        l= l > PT_VER_LEN ? PT_VER_LEN : l ; 
                        memcpy((void *)tempLine0->chVer,(void *)++tempLineFieldBuf,l);
		}
		//�ж��Ƿ�ΪDIS
		else if(memcmp(pMatchTemplateBuffer,"DIS",lengthOfField) == 0)
		{
                        l=strlen((INT8 *)++tempLineFieldBuf);
                        l= l > PT_DIS_LEN ? PT_DIS_LEN : l ; 
                        memcpy((void *)tempLine0->chDis,(void *)++tempLineFieldBuf,l);
		}
		//�ж��Ƿ�ΪDATE
		else if(memcmp(pMatchTemplateBuffer,"DATE",lengthOfField) == 0)
		{
                        l=strlen((INT8 *)++tempLineFieldBuf);
                        l= l > PT_DATE_LEN ? PT_DATE_LEN : l ; 
                        memcpy((void *)tempLine0->chDate,(void *)++tempLineFieldBuf,l);
		}
/*
		else
		{
			return 0;
		}
*/				
		
		//memsetʹ�õ�����������		
		pMatchTemplateBuffer = pSaveMatchTemplateBuffer;		
		memset(pMatchTemplateBuffer,0,MATCH_FIELD_LABEL_BUF_LEN);
		
		tempLineFieldBuf = pSavetempLineFieldBuffer;
		memset(tempLineFieldBuf,0,PRINT_TEMPLATE_LINE_FIELD_BUF_LEN);
		
	}//end of while
        //prn_log("end ParsePtLine0");
	return 0;
	
}


UINT8  ParsePtLine1(UINT8 *tempLineBuf, TPrnTempLine1 *tempLine1)
{
	UINT8 *pMatchTemplateBuffer=NULL;
	UINT8 *tempLineFieldBuf=NULL;
	UINT8 *pSaveMatchTemplateBuffer=NULL;
	UINT8 *pSavetempLineFieldBuffer=NULL;
	
	
	UINT32 lengthOfField=0;
	UINT8 *pTempLineField=NULL;
	
	// ���ģ�������Ƿ��кڱ���һ��
	UINT32 MarkInTemplate = 0;
        //prn_log("start ParsePtLine1");	
	if ((!tempLineBuf) || (!tempLine1))
	{	       
            return 1;
	}
	
	
	GetMatchFieldLabelBuffer((void **)&pMatchTemplateBuffer);
	pSaveMatchTemplateBuffer = pMatchTemplateBuffer;
	
	GetTemplateLineFieldBuffer((void **)&tempLineFieldBuf);
	pSavetempLineFieldBuffer = tempLineFieldBuf;
	
	tempLineBuf+=2;

	tempLine1->EndBackwardFlag = 0;	//Ĭ��Ϊ0����ֹ��Щ��ģ��û�иò���
	
	while ( (*tempLineBuf != TEMPLATE_LINE_END_CHARACTER) && 
	         (*tempLineBuf != '\0' )) 
	{		
		
		if(GetPtField(&tempLineBuf,tempLineFieldBuf) != 0 )
	    {
		   return 2;
		}
		
		lengthOfField = 0;
		pTempLineField = tempLineFieldBuf;
		while ((*tempLineFieldBuf != ATTIBUTE_SEPERATE_FIELD) && 
		      (*tempLineFieldBuf != '\0'))
		{
			if(lengthOfField >= MATCH_FIELD_LABEL_BUF_LEN)
			{
			   return 2;
			}
			tempLineFieldBuf++;
			lengthOfField++;
		}
		memcpy(pMatchTemplateBuffer,pTempLineField,lengthOfField);
		
		//��ÿһ��field���д���
		
		if(memcmp(pMatchTemplateBuffer,"TYPE",lengthOfField) == 0)
		   {	
				INT8 *p;
				tempLine1->PaperL = atoi((INT8 *)++tempLineFieldBuf);
				p = strchr((INT8 *)tempLineFieldBuf,'#');
				tempLine1->PaperW = atoi(++p);
				p = NULL;			
			
		    }
		else if(memcmp(pMatchTemplateBuffer,"FONT",lengthOfField) == 0)
			{	
				INT8 *p;
				tempLine1->FontH = atoi((INT8 *)++tempLineFieldBuf);
				p = strchr((INT8 *)tempLineFieldBuf,'#');				
				tempLine1->FontW = atoi(++p);
				p = NULL;				
			}
        else if(memcmp(pMatchTemplateBuffer,"MARK",lengthOfField) == 0)
			{
			    //���ģ�������кڱ�ı�ǩ����MarkInTemplate��1
				tempLine1->MarkFlag = atoi((INT8 *)++tempLineFieldBuf);
				MarkInTemplate = 1;
					
			}
	   else	if (memcmp(pMatchTemplateBuffer,"BEGIN_FORWARDPOINT",lengthOfField) == 0)
			{
				tempLine1->BeginForwardPoint = atoi((INT8 *)++tempLineFieldBuf);
			}
	   else	if(memcmp(pMatchTemplateBuffer,"MLNS",lengthOfField) == 0)
			{
				tempLine1->MaxInvLineCount = atoi((INT8 *)++tempLineFieldBuf);
			}
			
	   else	if(memcmp(pMatchTemplateBuffer,"REPAIR",lengthOfField) == 0)
			{
				tempLine1->RepairPoint = atoi((INT8 *)++tempLineFieldBuf);
			}
			
	   else	if(memcmp(pMatchTemplateBuffer,"FKDW_MAX",lengthOfField) == 0)
			{
				tempLine1->MaxFKDWCharacter = atoi((INT8 *)++tempLineFieldBuf);
			}
			
	   else	if(memcmp(pMatchTemplateBuffer,"SKDW_MAX",lengthOfField) == 0)
			{
				tempLine1->MaxSKDWCharacter = atoi((INT8 *)++tempLineFieldBuf);
			}
	   else	if(memcmp(pMatchTemplateBuffer,"SKDWDZ_MAX",lengthOfField) == 0)
			{
				tempLine1->MaxSKDWDZCharacter = atoi((INT8 *)++tempLineFieldBuf);
			}
			
	   else	if(memcmp(pMatchTemplateBuffer,"SKY_MAX",lengthOfField) == 0)
			{
				tempLine1->MaxSKYCharacter = atoi((INT8 *)++tempLineFieldBuf);
			}
			
	   else	if(memcmp(pMatchTemplateBuffer,"SPMC_MAX",lengthOfField) == 0)
			{
				tempLine1->MaxSPMCCharacter = atoi((INT8 *)++tempLineFieldBuf);
			}
			
	   else if (memcmp(pMatchTemplateBuffer,"END_FORWARDPOINT",lengthOfField) == 0)
		    {
				tempLine1->EndForwardPoint = atoi((INT8 *)++tempLineFieldBuf);
			}
	 
	   else if (memcmp(pMatchTemplateBuffer,"END_BACKWARDFLAG",lengthOfField) == 0)
		   {
			   tempLine1->EndBackwardFlag = atoi((INT8 *)++tempLineFieldBuf);
		   }
	   
	   else if (memcmp(pMatchTemplateBuffer,"BACKWARD_POINT",lengthOfField) == 0)
	        {		
	        	tempLine1->BackwardPoint  = atoi((INT8 *)++tempLineFieldBuf);
	        }
	  
	    else if (memcmp(pMatchTemplateBuffer,"UNFIXED_FORWORD",lengthOfField) == 0)
	        {		
	        	tempLine1->UnfixedForwardPoint  = atoi((INT8 *)++tempLineFieldBuf);
	        } 
	   else if (memcmp(pMatchTemplateBuffer,"JEDX_MAX",lengthOfField) == 0)
			{
				tempLine1->MaxJEDXCharacter = atoi((INT8 *)++tempLineFieldBuf);
			}
	   else if (memcmp(pMatchTemplateBuffer,"MAX_GOODS_COUNT",lengthOfField) == 0)
	   		{
	   			tempLine1->MaxGoodsCount = atoi((INT8 *)++tempLineFieldBuf);
	  		}
	   else if(memcmp(pMatchTemplateBuffer,"BZ_MAX",lengthOfField) == 0)
			{
				tempLine1->MaxBZCharacter = atoi((INT8 *)++tempLineFieldBuf);
			}
	   else if(memcmp(pMatchTemplateBuffer,"QR_CODE_LEFT_MARGIN",lengthOfField) == 0)
	   {
		   tempLine1->QRCodeLeftMargin = atoi((INT8 *)++tempLineFieldBuf);
	   }
	   /**********for 57mm***********/
	   else if (memcmp(pMatchTemplateBuffer,"INV_76_MM",lengthOfField) == 0)
	   {
		   tempLine1->InvFlag76 = atoi((INT8 *)++tempLineFieldBuf);
	   }
	   /**********for 57mm***********/
	   /*		
	   else
	       {
	    	 return 0;
	       }	
		*/
		
		
		pMatchTemplateBuffer = pSaveMatchTemplateBuffer;		
		memset(pMatchTemplateBuffer,0,MATCH_FIELD_LABEL_BUF_LEN);
		
		tempLineFieldBuf = pSavetempLineFieldBuffer;
		memset(tempLineFieldBuf,0,PRINT_TEMPLATE_LINE_FIELD_BUF_LEN);
		
		
	}//end of while
	
	//���ģ�������޺ڱ��ǩ����Ĭ��Ϊ���Һڱ꣬��ģ����1��MarkFlag��Ϊ0
	if(MarkInTemplate == 0)
	{
		tempLine1->MarkFlag = 0;
	}

	return 0;
}


UINT8  ParsePtLine2(UINT8 *tempLineBuf, TPrnTempRow *tempLine2,TPrnLineInfo *prnLineInfo,TPrnTempLine1 *tempLine1)
{

	UINT8 *pMatchTemplateBuffer = NULL;
	UINT8 *tempLineFieldBuf = NULL;
	UINT8 *pSaveMatchTemplateBuffer = NULL;
	UINT8 *pSavetempLineFieldBuffer = NULL;
	
	UINT32 nCount = 0;//��¼��ǩ�����ݵ���Ŀ
	UINT32 lengthOfField = 0;
	UINT8 *pTempLineField = NULL;
	
	INT8 *pLB = NULL;
	INT8 *pCO = NULL;
	
	//��¼д��ģ�����ݺ��chDatabuf�����λ�ã���һ��ģ�����ݿ�ʼд���λ�ã���
	INT8 *pSaveDataBuf = NULL;
//    prn_log("start ParsePtLine2 ");	
	
	if((!tempLineBuf) || (!tempLine2) )
	{
           return 1;
	}
	
	GetMatchFieldLabelBuffer((void **)&pMatchTemplateBuffer);
	pSaveMatchTemplateBuffer = pMatchTemplateBuffer;
	
	GetTemplateLineFieldBuffer((void **)&tempLineFieldBuf);
	pSavetempLineFieldBuffer = tempLineFieldBuf;
	
	tempLineBuf+=2;
	
	//����ӡ������������ΪĬ�����ԣ�����ģ����1���ã�
	prnLineInfo->FontH = tempLine1->FontH;
	prnLineInfo->FontW = tempLine1->FontW;
	
	//prn_log2("prnLineInfo->FontH = %d", prnLineInfo->FontH);
	
	
	while ((*tempLineBuf != TEMPLATE_LINE_END_CHARACTER) &&
	      (*tempLineBuf != '\0') )
	{
		
	
		if( GetPtField(&tempLineBuf,tempLineFieldBuf) != 0 )
        {
            return 2;
        }
		
		lengthOfField = 0;
		pTempLineField = tempLineFieldBuf;
		while ( (*tempLineFieldBuf != ATTIBUTE_SEPERATE_FIELD) && 
		        (*tempLineFieldBuf != '\0' ))
		{
			if(lengthOfField >= MATCH_FIELD_LABEL_BUF_LEN)
			{
			    return 2;
			}
			tempLineFieldBuf++;
			lengthOfField++;
		}
		memcpy(pMatchTemplateBuffer,pTempLineField,lengthOfField);
		
		//��ÿһ��field���д���
		
		
		//prn_log2("pMatchTemplateBuff = %s",pMatchTemplateBuffer);
		//prn_log2("lengthOfField = %u",lengthOfField);
		if(memcmp(pMatchTemplateBuffer,"LN",lengthOfField) == 0)
			
		{	
			tempLine2->Index = atoi((INT8 *)++tempLineFieldBuf);
			
		}
		
		if(memcmp(pMatchTemplateBuffer,"HEAD",lengthOfField) == 0)
			
		{			     
			tempLine2->Type = 0;
			prnLineInfo->Property = tempLine2->Type;
			
		}

		if(memcmp(pMatchTemplateBuffer,"DATACYCLE",lengthOfField) == 0)
			
		{			     
			tempLine2->Type = 0;
			prnLineInfo->Property = tempLine2->Type;
			CycleTempFlag = 1;
			
			
		}
		if(memcmp(pMatchTemplateBuffer,"START_TAIL",lengthOfField) == 0)
			
		{			     
			tempLine2->Type = END_INVOICE_DATA_LINE;
			prnLineInfo->Property = tempLine2->Type;
			CycleTempFlag = 0;
			
		}
		
		if(memcmp(pMatchTemplateBuffer,"TAIL",lengthOfField) == 0)
			
		{			     
			tempLine2->Type = 0;
			prnLineInfo->Property = tempLine2->Type;
			
		}
		/*--------�����һ��Ϊѭ��ģ����-------------------------------*/		
		if(memcmp(pMatchTemplateBuffer,"CYCLE_BEGIN",lengthOfField) == 0)
			
		{	 prn_log("here  !!!");
		    tempLine2->Type = END_INVOICE_HEAD_LINE;
			prnLineInfo->Property = tempLine2->Type;		     
			BeginCycleTemp = 1;
									
		}
		
		//ģ���е��������ã����ģ�������д˱�ǩ���򽫽��������������Ը����ӡ�нṹ��
		if(memcmp(pMatchTemplateBuffer,"FONT",lengthOfField) == 0)
		{	
			INT8 *p;
			tempLine2->FontH = atoi((INT8 *)++tempLineFieldBuf);
			p = strchr((INT8 *)tempLineFieldBuf,'#');				
			tempLine2->FontW = atoi(++p);
			p = NULL;
			prnLineInfo->FontH = tempLine2->FontH;
			prnLineInfo->FontW = tempLine2->FontW;	
		
		}		
	
		if(memcmp(pMatchTemplateBuffer,"ROWH",lengthOfField) == 0)
		{
			tempLine2->High = atoi((INT8 *)++tempLineFieldBuf);
			prnLineInfo->High = tempLine2->High;
			
		}
		if(memcmp(pMatchTemplateBuffer,"ROWBH",lengthOfField) == 0)
		{
			INT8 *p;
			tempLine2->BhighOne = atoi((INT8 *)++tempLineFieldBuf);
			p = strchr((INT8 *)tempLineFieldBuf,'#');	
			if (p == NULL)
			{
				//prn_log("p is NULL");
				tempLine2->BhighTwo = 0;
			}
			else
			{
				tempLine2->BhighTwo = atoi(++p);
				//prn_log2("tempLine2->BhighTwo = %u", tempLine2->BhighTwo);
			}
			p = NULL;
			prnLineInfo->Bhigh = tempLine2->BhighOne;
			//prnLineInfo->BhighTwo = tempLine2->BhighTwo;
			
		}
		
		if(memcmp(pMatchTemplateBuffer,"EMPTY_FORWARD",lengthOfField) == 0)
		{
			tempLine2->EmptyForwardHigh = atoi((INT8 *)++tempLineFieldBuf);
			prnLineInfo->EmptyForwardHigh = (INT16)tempLine2->EmptyForwardHigh;
			
		}
		
		if(memcmp(pMatchTemplateBuffer,"LB",lengthOfField) == 0)
			
		{	
		
			tempLineFieldBuf++;
			
            //ÿһ����ǩ�������Ƿ��ӡ�ı�־,0--��ӡ��1--����ӡ
			if(*tempLineFieldBuf == '0' || g_cungen == 1)		     
			
			{	
                if(nCount >= PT_MAX_ITEM_COUNT) 
                {
                    return 3;
                }
				nCount++;
				tempLine2->TotalCount = (UINT8)nCount;
				
				
				if (nCount == 1)
				{
					memset((void *)tempLine2->chDatabuf,0,PRINT_LINE_BUF_LEN);
					
					tempLine2->Items[nCount-1].dataPtr = tempLine2->chDatabuf;
					
					pSaveDataBuf = tempLine2->chDatabuf;
				}
				else
				{
					tempLine2->Items[nCount-1].dataPtr = pSaveDataBuf;
					
				}
				
				//����LB#0#��Ʊ���룺#2Ϊ��
								
				//��ǰָ��ָ��'0',��ָ��ָ��'��'
				tempLineFieldBuf += 2;
				
				//pLB��ֵΪָ��'#'
				pLB = strchr((INT8 *)tempLineFieldBuf,'#');
				
				//DataLen��ֵΪ'��Ʊ���룺'�ĳ���
				tempLine2->Items[nCount-1].DataLen = pLB-(INT8 *)tempLineFieldBuf;
				
				//��'��Ʊ���룺'������dataPtr��ָ��Ļ�����
				strncpy((INT8 *)tempLine2->Items[nCount-1].dataPtr,
					(INT8 *)tempLineFieldBuf,pLB-(INT8 *)tempLineFieldBuf);
					
				//LeftΪ'��Ʊ���룺'�ڴ�ӡ����������λ��
				tempLine2->Items[nCount-1].Left = atoi(++pLB);
				
				//��ʾ����Ϊ��ǩ				
				tempLine2->Items[nCount-1].Type = 1;
				
				//��pSaveDataBufָ��'��Ʊ���룺'���λ��
				pSaveDataBuf +=  strlen((INT8 *)tempLineFieldBuf);
				
				pLB = NULL;					
			}
						
		}
		
		if(memcmp(pMatchTemplateBuffer,"CO",lengthOfField) == 0)
			
		{			
            if(nCount >= PT_MAX_ITEM_COUNT) 
            {
                return 3;
            }
			nCount++;
			tempLine2->TotalCount = (UINT8)nCount;
			if (nCount == 1)
			{
				memset((void *)tempLine2->chDatabuf,0,PRINT_LINE_BUF_LEN);
				tempLine2->Items[nCount-1].dataPtr = tempLine2->chDatabuf;
				pSaveDataBuf = tempLine2->chDatabuf;
			}
			else
			{
				tempLine2->Items[nCount-1].dataPtr = (INT8 *)pSaveDataBuf;				
			}						
			tempLineFieldBuf++;
			pCO = strchr((INT8 *)tempLineFieldBuf,'#');
			
			tempLine2->Items[nCount-1].DataLen = pCO-(INT8 *)tempLineFieldBuf;
			
			strncpy((INT8 *)tempLine2->Items[nCount-1].dataPtr,
				(INT8 *)tempLineFieldBuf,pCO-(INT8 *)tempLineFieldBuf);
			
			tempLine2->Items[nCount-1].Left = atoi(++pCO);
			tempLine2->Items[nCount-1].Type = 2;
			pSaveDataBuf += strlen((INT8 *)tempLineFieldBuf);
			pCO = NULL;		
		}
		
		pMatchTemplateBuffer = pSaveMatchTemplateBuffer;		
		memset(pMatchTemplateBuffer,0,MATCH_FIELD_LABEL_BUF_LEN);
		
		tempLineFieldBuf = pSavetempLineFieldBuffer;
		memset(tempLineFieldBuf,0,PRINT_TEMPLATE_LINE_FIELD_BUF_LEN);
		
	}//end of while
	pSaveDataBuf = NULL;
   // prn_log("end ParsePtLine2 ");	
	//prn_log2("prnLineInfo->FontH = %d", prnLineInfo->FontH);
		
	return 0;
}


static INT8 tmp[8];
UINT8 GetPrnLineData(TPrnTempRow *tempLine2, TPrnLineInfo *conWriteBuffer, TPrnTempLine1 *tempLine1,TPrnLineInfo *prnLineInfo,TPrnInvoiceInfo *pInv)
{	
	INT32 tmpLocation = 0;
    INT32 location = 0;//��¼����λ��
	UINT32 len = 0;
	UINT32 i = 0; //��¼ģ�����еı�ǩ�����ݵĸ���
	UINT8 j;
	UINT8 position = 0;
	UINT8 hzNum = 0;
	UINT8 gb2Num = 0;
	UINT8 gb4Num = 0;
	UINT8 ascNum = 0;
	UINT32 displen = 0;
	UINT32 displen2 =0;
	INT64 multiple;
	INT64 realAmount;

//	prn_log2("================pSaveTemplateInfo->workMode = %u==================", pSaveTemplateInfo->workMode);
	
	//���տ�Ա����,�����λ��ģ�岻����,����ӡʱ��������,Ҫ���տ�Ա����λ�����п�϶)
	UINT32 saveLocation = 0;//��¼λ��
	
    //prn_log("start GetPrnLineData ");	
    //prn_log2("TotalCount=%u",tempLine2->TotalCount);	
	//����Items�е�����,��ÿһ��ģ�����ݣ�������ǩ�ʹ�ӡ����
    for ( i=0; i<tempLine2->TotalCount; i++)
    {
		
		//locationΪ��ǩ�����ݴ�ӡ��λ��
		location = tempLine2->Items[i].Left;
        if( abs( location) >  PRINT_LINE_WORD_LEN )
        {
             return 3;
        }
	    
        //����ΪLB ����Ӧ��Type=1
		if (tempLine2->Items[i].Type == 1)
		{
			strncpy(&(prnLineInfo->chContent[location-1]),
				tempLine2->Items[i].dataPtr,
				tempLine2->Items[i].DataLen);
		}
		//����ΪCO
		else
		{
            //prn_log2("dataPtr=%s",tempLine2->Items[i].dataPtr);
            //prn_log2("dataLen=%u",tempLine2->Items[i].DataLen);
			//��Ʊ����
			if (memcmp(tempLine2->Items[i].dataPtr,"FPDM",
				tempLine2->Items[i].DataLen) == 0)
			{		
				prn_log("here  !!!");
				memcpy((void *)&(prnLineInfo->chContent[location-1]), 
					(void *)pInv->chTypeCode, INV_TYPE_CODE_PRN_LEN);
				
			}
			//��Ʊ���� 
            else if (memcmp(tempLine2->Items[i].dataPtr,"FPHM",
				tempLine2->Items[i].DataLen) == 0)
			{
				if (pSaveTemplateInfo->workMode == WORK_MODE)
				{
					sprintf((char *)&(prnLineInfo->chContent[location-1]),
						"%08lu",pInv->InvNo);
					//�ж��Ƿ�Ϊ��ӡ���Ӵ��
					
					//prn_log2("��ǰ��ӡ����%u",pInv->PrintType);
//					if (pInv->PrintType == STUB_PRINT_TEMPLATE)
//					{
//						stubFlag = 1;
//						stubPlace = (UINT8)location ;					
//					}	
				}
				else
				{
					memcpy((void *)&(prnLineInfo->chContent[location-1]),"********",8);
					
				}
				
			} 
			 //ԭ��Ʊ����
			else if (memcmp(tempLine2->Items[i].dataPtr,"YFPDM",
				tempLine2->Items[i].DataLen) == 0)
			{	
				prn_log("here  !!!");
				if(pInv->InvType ==RETURN_INV_TEMPLATE)
				{
					prn_log("here  !!!");
					memcpy((void *)&(prnLineInfo->chContent[location-1]), 
						(void *)pInv->chPosCode, INV_TYPE_CODE_PRN_LEN);
				}
				else
				{
						prn_log("hereTHERE!!!");
					prnLineInfo->Property = INVALID_TEMPLATE_LINE;
				}
				
			}
			//ԭ��Ʊ����
            else if (memcmp(tempLine2->Items[i].dataPtr,"YFPHM",
				tempLine2->Items[i].DataLen) == 0)
			{
				if(pInv->InvType ==RETURN_INV_TEMPLATE)
				{
					if (pSaveTemplateInfo->workMode == WORK_MODE)
					{
						sprintf((char *)&(prnLineInfo->chContent[location-1]),
							"%08lu",pInv->PosInvNo);
						
					}
					else
					{
						memcpy((void *)&(prnLineInfo->chContent[location-1]),"********",8);
						
					}
				}
				else
				{
					prnLineInfo->Property = INVALID_TEMPLATE_LINE;
				}
				
			}
			//��ַ���
			else if (memcmp(tempLine2->Items[i].dataPtr,"DZJC",
				tempLine2->Items[i].DataLen) == 0)
			{
				prn_log2("here  %s!!!", pInv->chKPDZJC);
				strncpy(&(prnLineInfo->chContent[location-1]),
					pInv->chKPDZJC, strlen(pInv->chKPDZJC));
				
			} 
			//�������
			else if (memcmp(tempLine2->Items[i].dataPtr,"JQBH",
				tempLine2->Items[i].DataLen) == 0)
			{
				prn_log2("here  %s!!!", pInv->chMachineNo);
				strncpy(&(prnLineInfo->chContent[location-1]),
					pInv->chMachineNo, strlen(pInv->chMachineNo));
				
			} //˰��
			else if (memcmp(tempLine2->Items[i].dataPtr,"SWDJH",
				tempLine2->Items[i].DataLen) == 0)
			{
				if (pSaveTemplateInfo->workMode == WORK_MODE)
				{				
					strncpy(&(prnLineInfo->chContent[location-1]),
						pInv->chCorpCode,strlen(pInv->chCorpCode));
			    }
			    else
			    {
			    	memcpy((void *)&(prnLineInfo->chContent[location-1]),"********************",CORP_TAX_CODE_PRN_LEN);
			    }
				
			} //�տλ���漰�����д���
			else if (memcmp(tempLine2->Items[i].dataPtr,"SKDW",
				tempLine2->Items[i].DataLen) == 0)
			{				
				if (strlen(pInv->chCorpName) > (tempLine1->MaxSKDWCharacter))
				{
					//�����д�ӡ���ݣ���־��3
					continueWriteFlag = 3;
					/**********for 57mm***********/
					continueWriteLocation = location;//����һ�и��λ����ʼ��ӡλ�ö���
					//continueWriteLocation = 2;//��һ�е���ʼλ�ÿ�ʼ��ӡ
					/**********for 57mm***********/
					
					prnLineInfo->Bhigh = tempLine2->BhighOne;
					//�жϵ�λ���Ƶ�ǰMaxSKDWCharacter�еİ�����ֵĸ��������Ϊ������
					//�����İ�������Ƶ���һ������
					//if(GetHalfHZCount((UINT8 *)pInv->chCorpName,tempLine1->MaxSKDWCharacter)%2 == 0)
					HZCount((UINT8 *)pInv->chCorpName, tempLine1->MaxSKDWCharacter, &ascNum, &gb2Num, &gb4Num);
					position = ascNum + gb2Num * 2 + gb4Num * 4;
					prn_log2("position = %u", position);
					strncpy(&(prnLineInfo->chContent[location-1]),
						pInv->chCorpName,position);
					prn_log2("����������  %s", &(prnLineInfo->chContent[location-1]));	
					startPointer = (UINT8 *)&(pInv->chCorpName[position]);
					endPointer = startPointer;
					hzNum = (42 - continueWriteLocation) / 2;
					prn_log2("location = %u", location);
					prn_log2("hzNum = %u", hzNum);
					prn_log2("�����ַ���   %s", &(pInv->chCorpName[position]));
					displen = HZCount(&(pInv->chCorpName[position]), strlen((INT8 *) &(pInv->chCorpName[position])), &ascNum, &gb2Num, &gb4Num);
					prn_log2("displen = %u", displen);
					if (displen % 2 == 0)
					{
						displen = displen / 2;
					}
					else
					{
						displen = displen / 2 + 1;
					}
					if (displen <= hzNum)
					{
						CorpNameCounte = 1;
					}
					else
					{
						if (displen % hzNum == 0)
						{
							CorpNameCounte = (UINT8)(displen / hzNum);
						}
						else
						{
							CorpNameCounte = (UINT8)(displen / hzNum + 1);
						}
					}
					conWriteBuffer->Bhigh = tempLine2->BhighTwo;
					conWriteBuffer->Property = NORMAL_TEMPLATE_LINE;
				}
				else
				{
				    //�տλ�������û�г�������ַ�����Ҫ��һ�ξ�����ٴ���һ��
				      //��ʱ�����߿��еľ���conWriteBuffer->Bhigh
				      
					//�����޴�ӡ���ݣ���Ҫ��һ�ξ��룬��־��2

	                // ���ı�־λ��Ϊ�˲����д�ӡ
					continueWriteFlag = 0;
					//continueWriteFlag = 2;

					prnLineInfo->Bhigh = tempLine2->BhighOne;
					
					strncpy(&(prnLineInfo->chContent[location-1]),
						pInv->chCorpName,strlen(pInv->chCorpName));
					
				}
				
			}

			//�տλ��ַ
			else if (memcmp(tempLine2->Items[i].dataPtr,"SKDWDZ",
				tempLine2->Items[i].DataLen) == 0)
			{
				if (strlen(pInv->chCorpAddr) > (tempLine1->MaxSKDWDZCharacter))
				{
					//�����д�ӡ���ݣ���־��3
					continueWriteFlag = 3;
					/**********for 57mm***********/
					continueWriteLocation = location;//����һ�и��λ����ʼ��ӡλ�ö���
					//continueWriteLocation = 2;//��һ�е���ʼλ�ÿ�ʼ��ӡ
					/**********for 57mm***********/
					
					prnLineInfo->Bhigh = tempLine2->BhighOne;
					//�жϵ�λ���Ƶ�ǰMaxSKDWCharacter�еİ�����ֵĸ��������Ϊ������
					//�����İ�������Ƶ���һ������
					//if(GetHalfHZCount((UINT8 *)pInv->chCorpName,tempLine1->MaxSKDWCharacter)%2 == 0)
					HZCount((UINT8 *)pInv->chCorpAddr, tempLine1->MaxSKDWDZCharacter, &ascNum, &gb2Num, &gb4Num);
					position = ascNum + gb2Num * 2 + gb4Num * 4;
					prn_log2("position = %u", position);
					strncpy(&(prnLineInfo->chContent[location-1]),
						pInv->chCorpAddr,position);
					prn_log2("����������  %s", &(prnLineInfo->chContent[location-1]));	
					startPointer = (UINT8 *)&(pInv->chCorpAddr[position]);
					endPointer = startPointer;
					hzNum = (42 - continueWriteLocation) / 2;
					prn_log2("location = %u", location);
					prn_log2("hzNum = %u", hzNum);
					prn_log2("�����ַ���   %s", &(pInv->chCorpAddr[position]));
					displen = HZCount(&(pInv->chCorpAddr[position]), strlen((INT8 *) &(pInv->chCorpAddr[position])), &ascNum, &gb2Num, &gb4Num);
					prn_log2("displen = %u", displen);
					if (displen % 2 == 0)
					{
						displen = displen / 2;
					}
					else
					{
						displen = displen / 2 + 1;
					}
					if (displen <= hzNum)
					{
						CorpNameCounte = 1;
					}
					else
					{
						if (displen % hzNum == 0)
						{
							CorpNameCounte = (UINT8)(displen / hzNum);
						}
						else
						{
							CorpNameCounte = (UINT8)(displen / hzNum + 1);
						}
					}
					conWriteBuffer->Bhigh = tempLine2->BhighTwo;
					conWriteBuffer->Property = NORMAL_TEMPLATE_LINE;
				}
				else
				{
				    //�տλ�������û�г�������ַ�����Ҫ��һ�ξ�����ٴ���һ��
				      //��ʱ�����߿��еľ���conWriteBuffer->Bhigh
				      
					//�����޴�ӡ���ݣ���Ҫ��һ�ξ��룬��־��2

					continueWriteFlag = 2;
					prnLineInfo->Bhigh = tempLine2->BhighOne;
					
					strncpy(&(prnLineInfo->chContent[location-1]),
						pInv->chCorpAddr,strlen(pInv->chCorpAddr));
					
					
					if( prnLineInfo->EmptyForwardHigh > 0)
						
					{
					  	memset((void *)conWriteBuffer->chContent, 0, PRINT_LINE_BUF_LEN+1);
					 	conWriteBuffer->Bhigh = (UINT8)prnLineInfo->EmptyForwardHigh;	
					  	conWriteBuffer->Property = EMPTY_TEMPLATE_LINE;						
					}
					else
				    {
				    	strncpy(conWriteBuffer->chContent," ", 1);
				    	conWriteBuffer->Bhigh = tempLine2->BhighTwo;	
					    conWriteBuffer->Property =NORMAL_TEMPLATE_LINE;		
				    	
				    }				
          
				}				
			}	

			//���λ��Ҫ���У�ͬ�ϴ���
			else if (memcmp(tempLine2->Items[i].dataPtr,"FKDW",
				tempLine2->Items[i].DataLen) == 0)
			{
					j = 0;
					while(1)
					{	
						prn_log2("while  j = %u", j);					
						displen = HZCount((UINT8 *)pInv->chClientName, (tempLine1->MaxFKDWCharacter - j), &ascNum, &gb2Num, &gb4Num);
						position = ascNum + gb2Num * 2 + gb4Num * 4;
						if (j == 0)
							displen2 = displen;
						prn_log2("position = %u", position);
						if (SKYContinueFlag == 1)
						{
							if ((location + displen) > (saveRealLocation - 2))
							{
								j++;
								continue;
							}
							break;
						}
						else
						{
							break;
						}
					}
						
					if (strlen(pInv->chClientName) > (tempLine1->MaxFKDWCharacter)
						|| ( (strlen(pInv->chClientName) <= tempLine1->MaxFKDWCharacter) && ((location + displen2) > (saveRealLocation - 2)) && (SKYContinueFlag == 1)))
					{					
						continueWriteFlag = 3;
						/**********for 57mm***********/
						continueWriteLocation = location;		
					//	continueWriteLocation = 2;	
						/**********for 57mm***********/
						prnLineInfo->Bhigh = tempLine2->BhighOne;
						
						strncpy(&(prnLineInfo->chContent[location-1]),
							pInv->chClientName,position);
						if (SKYContinueFlag == 1)
							strncpy(&(prnLineInfo->chContent[saveRealLocation - 1]),
						    		saveSkyContent,strlen(saveSkyContent));
						prn_log2("����������  %s", &(prnLineInfo->chContent[location-1]));	
						startPointer = (UINT8 *)&(pInv->chClientName[position]);
						endPointer = startPointer;
						hzNum = (42 - location) / 2;
						prn_log2("location = %u", location);
						prn_log2("hzNum = %u", hzNum);
						prn_log2("�����ַ���   %s", &(pInv->chClientName[position]));
						displen = HZCount(&(pInv->chClientName[position]), strlen((INT8 *) &(pInv->chClientName[position])), &ascNum, &gb2Num, &gb4Num);
						if (displen % 2 == 0)
						{
							displen = displen / 2;
						}
						else
						{
							displen = displen / 2 + 1;
						}
						if (displen <= hzNum)
						{
							CorpNameCounte = 1;
						}
						else
						{
							if (displen % hzNum == 0)
							{
								CorpNameCounte = (UINT8)(displen / hzNum);
							}
							else
							{
								CorpNameCounte = (UINT8)(displen / hzNum + 1);
							}
						}
						conWriteBuffer->Bhigh = tempLine2->BhighTwo;
						conWriteBuffer->Property = NORMAL_TEMPLATE_LINE;
					}
					else
					{
					    //prn_log("����������û�г�������ַ������Ǻ�");
						//  ���ı�־λ��Ϊ�˲����д�ӡ
                        continueWriteFlag = 0;
                       	//continueWriteFlag = 2;
						prnLineInfo->Bhigh = tempLine2->BhighOne;
						
					    //prn_log("�տ�Աû������");
					    //prn_log2("pInv->chClientName = %s",pInv->chClientName);
						strncpy(&(prnLineInfo->chContent[location - 1]),
							     pInv->chClientName, strlen(pInv->chClientName));
							     
						if (SKYContinueFlag == 1)
							strncpy(&(prnLineInfo->chContent[saveRealLocation - 1]),
						    		saveSkyContent,strlen(saveSkyContent));
						//ע��Ŀ����Ϊ�˲����У�������ʾһ��
						 /*   			     
						if( prnLineInfo->EmptyForwardHigh > 0)

						{
							memset((void *)conWriteBuffer->chContent, 0, PRINT_LINE_BUF_LEN+1);
							conWriteBuffer->Bhigh = (UINT8)prnLineInfo->EmptyForwardHigh;	
							conWriteBuffer->Property = EMPTY_TEMPLATE_LINE;						
						}
						else
						{
							strncpy(conWriteBuffer->chContent," ", 1);
							conWriteBuffer->Bhigh = tempLine2->BhighTwo;	
							conWriteBuffer->Property =NORMAL_TEMPLATE_LINE;		
						}
                       */
						/*-------------added end---------------------------------*/									
					}						
			//	}	
				
			}//END FKDW 
			 
			//��Ʊ����
			else if (memcmp(tempLine2->Items[i].dataPtr,"KPRQ",
				tempLine2->Items[i].DataLen) == 0)
			{
				sprintf(&(prnLineInfo->chContent[location-1]),
					"%04lu-%02lu-%02lu", (pInv->m_Date) / 10000, ( (pInv->m_Date) % 10000 ) / 100 ,
					( (pInv->m_Date) % 10000 ) % 100  );			
				//�ж��Ƿ�Ϊ��ӡ���Ӵ��	
				if (pInv->PrintType == STUB_PRINT_TEMPLATE)
				{
					stubFlag = 1;
					stubPlace = location ;					
				}			
				if (pSaveTemplateInfo->workMode != WORK_MODE) //ѧϰģʽ��ӡ�����ɱ�����
				{				
					stubFlag = 2;
					stubPlace = (UINT8)location;	
				}
			}
			else if	(memcmp(tempLine2->Items[i].dataPtr,"KPSJ",
				tempLine2->Items[i].DataLen) == 0)
			{
				sprintf(&(prnLineInfo->chContent[location-1]),
					"%02lu:%02lu:%02lu", (pInv->m_Time) / 10000, ( (pInv->m_Time) % 10000 ) / 100 ,
					( (pInv->m_Time) % 10000 ) % 100  );
				
				//�ж��Ƿ�Ϊ��ӡ���Ӵ��	
//				if (pInv->PrintType == STUB_PRINT_TEMPLATE)
//				{
//					stubFlag = 1;
//					stubPlace = location ;					
//				}			
			} 
			//�տ�Ա���д��������û�г�������ַ�������Ҫ�߿��У�
			else if (memcmp(tempLine2->Items[i].dataPtr,"SKY",
				tempLine2->Items[i].DataLen) == 0)
			{
				memset((void *)saveSkyContent,0,10);

                //prn_log2("�տ�ԱpInv->chOperatorName = %s",pInv->chOperatorName);
                //prn_log2("�տ�Ա����ַ���tempLine1->MaxSKYCharacter = %u",tempLine1->MaxSKYCharacter);
				if (strlen(pInv->chOperatorName) > (tempLine1->MaxSKYCharacter))
				{
				    //prn_log("�տ�Ա���У��ñ�־Ϊ1");
				
					/*��־�տ�Ա����*/
						SKYContinueFlag = 1;
						strncpy(&(prnLineInfo->chContent[location-1]),
							pInv->chOperatorName,tempLine1->MaxSKYCharacter);
                                            
						saveRealLocation = location; //��¼����λ��
						
						strncpy(saveSkyContent,
							&(pInv->chOperatorName[tempLine1->MaxSKYCharacter]),
							strlen(pInv->chOperatorName) - (tempLine1->MaxSKYCharacter)); //���������ݴ洢
						
				
				}
				else
				{	
				    //prn_log("�տ�Աδ���У��ñ�־Ϊ0");
				    SKYContinueFlag = 0;
					strncpy(&(prnLineInfo->chContent[location-1]),
						pInv->chOperatorName,strlen(pInv->chOperatorName));
				}
				
			} //���Сд
			else if (memcmp(tempLine2->Items[i].dataPtr,"JEXX",
				tempLine2->Items[i].DataLen) == 0)
			{	
				
				
				//prn_log2("��Ʊ����*********%u",pInv->InvType);
				tmpLocation = location;
				
				if (location < 0)
				{
					location = -location;
				}
				if (pSaveTemplateInfo->workMode == WORK_MODE)
				{				
				
					memset((void *)saveRightBuf,0,sizeof(saveRightBuf));
					
					
					if ((pInv->InvType == RETURN_INV_TEMPLATE) || (pInv->InvType == RETURN_INV_NOTEXIT_TEMPLATE) ||
						(pInv->InvType == RET_SPECIAL_INV))
					{
						sprintf(saveRightBuf,"��%.2f",-(double)((double)pInv->InvSumLowcase) / 100);
					}
					else
					{
						sprintf(saveRightBuf,"��%.2f",(double)((double)pInv->InvSumLowcase) / 100);
					}
					
					len = strlen(saveRightBuf);
					
					if (tmpLocation < 0)
					{
						memcpy((void *)&prnLineInfo->chContent[location-len], (void *)saveRightBuf, len);
					}
					else
					{
						memcpy((void *)&prnLineInfo->chContent[location-1], (void *)saveRightBuf, len);
					}
				}
				else
				{
				  if (tmpLocation < 0)
				  {
					memcpy((void *)&prnLineInfo->chContent[location-4], "****", 4);
				
				  }
				  else
				  {
				  	memcpy((void *)&prnLineInfo->chContent[location-1], "****", 4);
				  }
				}
				
			} //����д����Ҫ���д���
			else if (memcmp(tempLine2->Items[i].dataPtr,"JEDX",
				tempLine2->Items[i].DataLen) == 0)
			{
				//prn_log2("��Ʊ����*********%u",pInv->InvType);
				if (pSaveTemplateInfo->workMode == WORK_MODE)
				{
					if (strlen(pInv->chInvSumUppercase) > (tempLine1->MaxJEDXCharacter))
					{
						if(pInv->InvType == WASTE_INV_TEMPLATE)
						{
				    		strncpy(&(prnLineInfo->chContent[location-1]),
									pInv->chInvSumUppercase,strlen(pInv->chInvSumUppercase));
						}
						else
						{
							continueWriteFlag = 1;
							continueWriteLocation = (UINT8)location;
						
							//���Ϊ��Ʊ
							//prn_log2("************��ʱ�ķ�Ʊ����%u",pInv->InvType);
							if ((pInv->InvType == RETURN_INV_TEMPLATE) || (pInv->InvType == RETURN_INV_NOTEXIT_TEMPLATE) ||
								(pInv->InvType == RET_SPECIAL_INV))
							{
								strncpy(&(prnLineInfo->chContent[location-1]), "(��)", 4);
							
								strncpy(&(prnLineInfo->chContent[location+3]),
									pInv->chInvSumUppercase,tempLine1->MaxJEDXCharacter);
								
								strncpy(&(conWriteBuffer->chContent[location-1]),
									&(pInv->chInvSumUppercase[tempLine1->MaxJEDXCharacter]),
									strlen(pInv->chInvSumUppercase) - (tempLine1->MaxJEDXCharacter));
							
							}
							else
							{
						    
								strncpy(&(prnLineInfo->chContent[location-1]),
									pInv->chInvSumUppercase,tempLine1->MaxJEDXCharacter);
								
								strncpy(&(conWriteBuffer->chContent[location-1]),
									&(pInv->chInvSumUppercase[tempLine1->MaxJEDXCharacter]),
									strlen(pInv->chInvSumUppercase) - (tempLine1->MaxJEDXCharacter));
							
							}	
							conWriteBuffer->Bhigh = prnLineInfo->Bhigh;
							conWriteBuffer->Property = NORMAL_TEMPLATE_LINE;
						}			
						
					}
					else
					{	
						//prn_log2("��ʱ��Ʊ����Ϊ%u",pInv->InvType);
						if(pInv->InvType == WASTE_INV_TEMPLATE)
						{
				    		//prn_log2("pInv->chInvSumUppercase = %s",pInv->chInvSumUppercase);
				    		strncpy(&(prnLineInfo->chContent[location-1]),
									pInv->chInvSumUppercase,strlen(pInv->chInvSumUppercase));
						}
						else
						{
							continueWriteFlag = 1;				
							if ((pInv->InvType == RETURN_INV_TEMPLATE) || (pInv->InvType == RETURN_INV_NOTEXIT_TEMPLATE) ||
								(pInv->InvType == RET_SPECIAL_INV))
							{
								strncpy(&(prnLineInfo->chContent[location-1]), "(��)", 4);
								strncpy(&(prnLineInfo->chContent[location+3]),
									pInv->chInvSumUppercase,strlen(pInv->chInvSumUppercase));
							}
							else
							{
								strncpy(&(prnLineInfo->chContent[location-1]),
									pInv->chInvSumUppercase,strlen(pInv->chInvSumUppercase));
							}
							memset((void *)conWriteBuffer->chContent, 0, PRINT_LINE_BUF_LEN+1);
						
							conWriteBuffer->Bhigh = (UINT8)prnLineInfo->EmptyForwardHigh;	
							conWriteBuffer->Property = EMPTY_TEMPLATE_LINE;	
						}
					
					}
				}
				else
				{
					memcpy(&(prnLineInfo->chContent[location-1]),"****",4);
				}
			}//�ϼ�˰��
			else if (memcmp(tempLine2->Items[i].dataPtr,"HJSE",
				tempLine2->Items[i].DataLen) == 0)
			{	
				//prn_log2("��Ʊ����*********%u",pInv->InvType);
				tmpLocation = location;
				
				if (location < 0)
				{
					location = -location;
				}
				if (pSaveTemplateInfo->workMode == WORK_MODE)
				{				
				
					memset((void *)saveRightBuf,0,sizeof(saveRightBuf));
					
					
					if ((pInv->InvType == RETURN_INV_TEMPLATE) || (pInv->InvType == RETURN_INV_NOTEXIT_TEMPLATE) ||
						(pInv->InvType == RET_SPECIAL_INV))
					{
						sprintf(saveRightBuf,"��%.2f",-(double)((double)pInv->InvTaxLowcase) / 100);
					}
					else
					{
						sprintf(saveRightBuf,"��%.2f",(double)((double)pInv->InvTaxLowcase) / 100);
					}
					
					len = strlen(saveRightBuf);
					
					if (tmpLocation < 0)
					{
						memcpy((void *)&prnLineInfo->chContent[location-len], (void *)saveRightBuf, len);
					}
					else
					{
						memcpy((void *)&prnLineInfo->chContent[location-1], (void *)saveRightBuf, len);
					}
				}
				else
				{
				  if (tmpLocation < 0)
				  {
					memcpy((void *)&prnLineInfo->chContent[location-4], "****", 4);
				
				  }
				  else
				  {
				  	memcpy((void *)&prnLineInfo->chContent[location-1], "****", 4);
				  }
				}
				
			}//�ϼƽ��
			else if (memcmp(tempLine2->Items[i].dataPtr,"HJJE",
				tempLine2->Items[i].DataLen) == 0)
			{	
				//prn_log2("��Ʊ����*********%u",pInv->InvType);
				tmpLocation = location;
				
				if (location < 0)
				{
					location = -location;
				}
				if (pSaveTemplateInfo->workMode == WORK_MODE)
				{				
				
					memset((void *)saveRightBuf,0,sizeof(saveRightBuf));
					
					
					if ((pInv->InvType == RETURN_INV_TEMPLATE) || (pInv->InvType == RETURN_INV_NOTEXIT_TEMPLATE) ||
						(pInv->InvType == RET_SPECIAL_INV))
					{
						sprintf(saveRightBuf,"��%.2f",-(double)((double)pInv->InvMoneyLowcase) / 100);
					}
					else
					{
						sprintf(saveRightBuf,"��%.2f",(double)((double)pInv->InvMoneyLowcase) / 100);
					}
					
					len = strlen(saveRightBuf);
					
					if (tmpLocation < 0)
					{
						memcpy((void *)&prnLineInfo->chContent[location-len], (void *)saveRightBuf, len);
					}
					else
					{
						memcpy((void *)&prnLineInfo->chContent[location-1], (void *)saveRightBuf, len);
					}
				}
				else
				{
				  if (tmpLocation < 0)
				  {
					memcpy((void *)&prnLineInfo->chContent[location-4], "****", 4);
				
				  }
				  else
				  {
				  	memcpy((void *)&prnLineInfo->chContent[location-1], "****", 4);
				  }
				}
				
			} //˰����
			else if (memcmp(tempLine2->Items[i].dataPtr,"SKM",
				tempLine2->Items[i].DataLen) == 0)
			{
				/*
				if (pSaveTemplateInfo->workMode == WORK_MODE)
				{
					memcpy(&(prnLineInfo->chContent[location-1]),
						pInv->chTaxCtrCode,4);
					prnLineInfo->chContent[location-1+4] = ' ';
					
					memcpy(&prnLineInfo->chContent[location-1+5],
						&(pInv->chTaxCtrCode[4]),4);
					prnLineInfo->chContent[location-1+9] = ' ';
					
					memcpy(&prnLineInfo->chContent[location-1+10],
						&(pInv->chTaxCtrCode[8]),4);
					prnLineInfo->chContent[location-1+14] = ' ';
					
					memcpy(&prnLineInfo->chContent[location-1+15],
						&(pInv->chTaxCtrCode[12]),4);
					prnLineInfo->chContent[location-1+19] = ' ';
					
					memcpy(&prnLineInfo->chContent[location-1+20],
						&(pInv->chTaxCtrCode[16]),4);
				}
				else
				{
					memcpy(&(prnLineInfo->chContent[location-1]),"**** **** **** **** ****",24);
					stubFlag = 2;
					stubPlace = (UINT8)location;
				}
				*/
				sprintf(&(prnLineInfo->chContent[location-1]),
					"%s", pInv->chTaxCtrCode);	
			}
			else if (memcmp(tempLine2->Items[i].dataPtr,"JZLSH",
				tempLine2->Items[i].DataLen) == 0)
			{
				
				if (pSaveTemplateInfo->workMode == WORK_MODE)
				{
					memcpy(&(prnLineInfo->chContent[location-1]),
						pInv->chJzlshCode,4);
					prnLineInfo->chContent[location-1+4] = ' ';
					
					memcpy(&prnLineInfo->chContent[location-1+5],
						&(pInv->chJzlshCode[4]),4);
					prnLineInfo->chContent[location-1+9] = ' ';
					
					memcpy(&prnLineInfo->chContent[location-1+10],
						&(pInv->chJzlshCode[8]),4);
					prnLineInfo->chContent[location-1+14] = ' ';
					
					memcpy(&prnLineInfo->chContent[location-1+15],
						&(pInv->chJzlshCode[12]),4);
					prnLineInfo->chContent[location-1+19] = ' ';
					
					memcpy(&prnLineInfo->chContent[location-1+20],
						&(pInv->chJzlshCode[16]),4);
				}
				else
				{
					memcpy(&(prnLineInfo->chContent[location-1]),"**** **** **** **** ****",24);
					stubFlag = 2;
					stubPlace = (UINT8)location;
				}
			}


			else if(memcmp(tempLine2->Items[i].dataPtr,"SKDWDH",
				tempLine2->Items[i].DataLen) == 0)
			{
				sprintf(&(prnLineInfo->chContent[location-1]),
					"%s", pInv->chPhoneNo);				
			}

			//���λ˰��
			else if(memcmp(tempLine2->Items[i].dataPtr,"FKDWSH",
				tempLine2->Items[i].DataLen) == 0)
			{
				sprintf(&(prnLineInfo->chContent[location-1]),
					"%s", pInv->chClientCode);				
			}
			//��ҵ����
			else if (memcmp(tempLine2->Items[i].dataPtr,"HYFL",
				tempLine2->Items[i].DataLen) == 0)
			{
				strncpy(&(prnLineInfo->chContent[location-1]),
					pInv->chHYFL, strlen(pInv->chHYFL));
				
			} 
			//�Զ����ǩ1
			else if(memcmp(tempLine2->Items[i].dataPtr,"ZDY1",
				tempLine2->Items[i].DataLen) == 0)
			{
				sprintf(&(prnLineInfo->chContent[location-1]),
					"%s", pInv->chSelfDefTab1);				
			}
			//�Զ�������1
			else if(memcmp(tempLine2->Items[i].dataPtr,"ZDYZ1",
				tempLine2->Items[i].DataLen) == 0)
			{
				sprintf(&(prnLineInfo->chContent[location-1]),
					"%s", pInv->chSelfDefCont1);				
			}
			//�Զ����ǩ2
			else if(memcmp(tempLine2->Items[i].dataPtr,"ZDY2",
				tempLine2->Items[i].DataLen) == 0)
			{
				sprintf(&(prnLineInfo->chContent[location-1]),
					"%s", pInv->chSelfDefTab2);				
			}
			//�Զ�������2
			else if(memcmp(tempLine2->Items[i].dataPtr,"ZDYZ2",
				tempLine2->Items[i].DataLen) == 0)
			{
				sprintf(&(prnLineInfo->chContent[location-1]),
					"%s", pInv->chSelfDefCont2);				
			}
			//BZ
			else if (memcmp(tempLine2->Items[i].dataPtr,"BZ",
				tempLine2->Items[i].DataLen) == 0)
			{
				if (strlen(pInv->chRemarks) > (tempLine1->MaxBZCharacter))
				{
					//�����д�ӡ���ݣ���־��3
					continueWriteFlag = 3;
					//continueWriteLocation = location;
					continueWriteLocation = 2;
					
					prnLineInfo->Bhigh = tempLine2->BhighOne;
					//�жϵ�λ���Ƶ�ǰMaxSKDWCharacter�еİ�����ֵĸ��������Ϊ������
					//�����İ�������Ƶ���һ������
					//if(GetHalfHZCount((UINT8 *)pInv->chCorpName,tempLine1->MaxSKDWCharacter)%2 == 0)
					HZCount((UINT8 *)pInv->chRemarks, tempLine1->MaxBZCharacter, &ascNum, &gb2Num, &gb4Num);
					position = ascNum + gb2Num * 2 + gb4Num * 4;
					prn_log2("position = %u", position);
					strncpy(&(prnLineInfo->chContent[location-1]),
						pInv->chRemarks,position);
					prn_log2("����������  %s", &(prnLineInfo->chContent[location-1]));	
					startPointer = (UINT8 *)&(pInv->chRemarks[position]);
					endPointer = startPointer;
					hzNum = (42 - continueWriteLocation) / 2;
					prn_log2("location = %u", location);
					prn_log2("hzNum = %u", hzNum);
					prn_log2("�����ַ���   %s", &(pInv->chRemarks[position]));
					displen = HZCount(&(pInv->chRemarks[position]), strlen((INT8 *) &(pInv->chRemarks[position])), &ascNum, &gb2Num, &gb4Num);
					prn_log2("displen = %u", displen);
					if (displen % 2 == 0)
					{
						displen = displen / 2;
					}
					else
					{
						displen = displen / 2 + 1;
					}
					if (displen <= hzNum)
					{
						CorpNameCounte = 1;
					}
					else
					{
						if (displen % hzNum == 0)
						{
							CorpNameCounte = (UINT8)(displen / hzNum);
						}
						else
						{
							CorpNameCounte = (UINT8)(displen / hzNum + 1);
						}
					}
					conWriteBuffer->Bhigh = tempLine2->BhighTwo;
					conWriteBuffer->Property = NORMAL_TEMPLATE_LINE;
				}
				else
				{
				    //�տλ�������û�г�������ַ�����Ҫ��һ�ξ�����ٴ���һ��
				      //��ʱ�����߿��еľ���conWriteBuffer->Bhigh
				      
					//�����޴�ӡ���ݣ���Ҫ��һ�ξ��룬��־��2
					continueWriteFlag = 2;
					prnLineInfo->Bhigh = tempLine2->BhighOne;
					
					strncpy(&(prnLineInfo->chContent[location-1]),
						pInv->chRemarks,strlen(pInv->chRemarks));
					
					
					if( prnLineInfo->EmptyForwardHigh > 0)
						
					{
					  	memset((void *)conWriteBuffer->chContent, 0, PRINT_LINE_BUF_LEN+1);
					 	conWriteBuffer->Bhigh = (UINT8)prnLineInfo->EmptyForwardHigh;	
					  	conWriteBuffer->Property = EMPTY_TEMPLATE_LINE;						
					}
					else
				    {
				    	strncpy(conWriteBuffer->chContent," ", 1);
				    	conWriteBuffer->Bhigh = tempLine2->BhighTwo;	
					    conWriteBuffer->Property =NORMAL_TEMPLATE_LINE;		
				    	
				    }				
				}				
			}
#if PETROL_STATION_VER
			else if(memcmp(tempLine2->Items[i].dataPtr,"BCH",
				tempLine2->Items[i].DataLen) == 0)
			{
			    //prn_log("�����κűȽ�");
			  
				if( (pInv->m_Time >= 70000) &&(pInv->m_Time < 120000))			
				{
					memcpy(&(prnLineInfo->chContent[location-1]),"��",2);
				}
				else if((pInv->m_Time >= 120000) &&(pInv->m_Time < 183000))
				{
					memcpy(&(prnLineInfo->chContent[location-1]),"��",2);
				}
				else
				{
					memcpy(&(prnLineInfo->chContent[location-1]),"��",2);
				}
			}
			else if(memcmp(tempLine2->Items[i].dataPtr,"SKDWDH",
				tempLine2->Items[i].DataLen) == 0)
			{
				sprintf(&(prnLineInfo->chContent[location-1]),
					"%u", pInv->OilGunID);				
			}
#endif
            else
            {

                //prn_log2("***************pInv->GoodsLineCount = %u",pInv->GoodsLineCount);
                //prn_log2("***************templateNo = %u",templateNo);
               			   		
			    
		        if(pInv->GoodsLineCount == 0)
				{  				
					strncpy(prnLineInfo->chContent,	" ", 1);					
					break; 
					
				}
				
				//prn_log2("��ǰ��ӡ����%u",pInv->PrintType);	
				//����ǲ��������Ҵ�ӡ���ͣ�templatNoһֱΪ0
				if ((pSaveTemplateInfo->FixedModeFlag == 0) &&(pInv->InvType != RETURN_INV)&&
					(pInv->InvType != RET_MANUAL_INV))
				{
					//������Ǵ����ӡ�����Ҳ�����Ʒȡ����
					if ((pInv->PrintType != STUB_PRINT) && (DetailCancelFlag == 0))
					{
						templateNo = 0;	
					}
									
				}
				
			    //prn_log2("prnLineInfo->chContent = %s",prnLineInfo->chContent);		   
			    //��Ʒ���ƣ������Ʒ���ƴ�������ַ���������Ʒ���Ƶ��д�ӡ
			    
				//prn_log2("prnLineInfo->FontH = %d", prnLineInfo->FontH);
				if (memcmp(tempLine2->Items[i].dataPtr,"SPMC",
					tempLine2->Items[i].DataLen) == 0)
				{					
					//prn_log2("prnLineInfo->FontH = %d", prnLineInfo->FontH);
					
                    if (strlen(pInv->GoodsLines[templateNo].chProductName)  
						<= (tempLine1->MaxSPMCCharacter) )
					{
					    //prn_log("��Ʒ���Ʋ���������ַ���");
						strncpy(&(prnLineInfo->chContent[location-1]),
							pInv->GoodsLines[templateNo].chProductName,
							strlen(pInv->GoodsLines[templateNo].chProductName));
						
                    }							
			
                    else
                    {   						 
					   						 
				 		if(GetHalfHZCount((UINT8 *) pInv->GoodsLines[templateNo].chProductName,tempLine1->MaxSPMCCharacter)%2==0 )  
					  	{
					  		//prn_log2("tempLine1->MaxSPMCCharacter = %u",tempLine1->MaxSPMCCharacter);
				  			//prn_log2("pInv->GoodsLines[templateNo].chProductName = %s",pInv->GoodsLines[templateNo].chProductName);
					  		
					  		strncpy(&(prnLineInfo->chContent[location-1]),
								pInv->GoodsLines[templateNo].chProductName,tempLine1->MaxSPMCCharacter);
							//prn_log2("prnLineInfo->chContent = %s",prnLineInfo->chContent);
							
							
							strncpy(&(conWriteBuffer->chContent[location-1]),
								&(pInv->GoodsLines[templateNo].chProductName[tempLine1->MaxSPMCCharacter]),
								strlen(pInv->GoodsLines[templateNo].chProductName) - (tempLine1->MaxSPMCCharacter));
							
							//prn_log2("conWriteBuffer->chContent = %s",conWriteBuffer->chContent);
							conWriteBuffer->Bhigh = prnLineInfo->Bhigh;
							
							
						}
					  	else
					  	{
					  		strncpy(&(prnLineInfo->chContent[location-1]),
								pInv->GoodsLines[templateNo].chProductName,tempLine1->MaxSPMCCharacter-1);
							
							strncpy(&(conWriteBuffer->chContent[location-1]),
								&(pInv->GoodsLines[templateNo].chProductName[tempLine1->MaxSPMCCharacter - 1]),
									strlen(pInv->GoodsLines[templateNo].chProductName) - (tempLine1->MaxSPMCCharacter - 1));
							
							conWriteBuffer->Bhigh = prnLineInfo->Bhigh;
							//prn_log2("conWriteBuffer->Bhigh = %u",conWriteBuffer->Bhigh);
								
						}	
						
						continueWriteFlag = 1;
						
					}
				}//END SPMC 
				//��Ʒ����
				else if (memcmp(tempLine2->Items[i].dataPtr,"SPDJ",
					tempLine2->Items[i].DataLen) == 0)
				{
					
					//��ӡ�Ҷ���Ĵ������ģ���д�ӡ����λ��Ϊ�������
					
					//tmpLocationΪ��ʼֵ������������
					tmpLocation = location;
					
					//prn_log2("prnLineInfo->FontH = %d", prnLineInfo->FontH);
					//���Ϊ������location��Ϊ��ֵ
					if (location < 0)
					{
						location = -location;
					}
					
					memset((void *)saveRightBuf,0,sizeof(saveRightBuf));
					
					//prn_log2("prnLineInfo->FontH = %d", prnLineInfo->FontH);
					//�ۿ۴���
					if ((pInv->GoodsLines[templateNo].Type == DETAIL_DISCOUNT_TEMPLATE))
					{
						sprintf(saveRightBuf, "%.1f%%",
							(double)((double)pInv->GoodsLines[templateNo].Price / RATE_EXTENSION_TEMPLATE));
					}
					else if (pInv->GoodsLines[templateNo].Type == DETAIL_REDUCTION_TEMPLATE || pInv->GoodsLines[templateNo].Type == DETAIL_SERVICE_TEMPLATE)
					{
						;
					}
					else
					{
									sprintf(saveRightBuf, "%.2f",
							((double)pInv->GoodsLines[templateNo].Price)  / PRICE_EXTENSION_TEMPLATE);
					}
					
					len = strlen(saveRightBuf);
					
					//�����ʼΪ������ӡλ��Ϊ���ұ������㣬��len��λ�ÿ�ʼ��ӡ
					if ( tmpLocation < 0 )
					{
						memcpy((void *)&prnLineInfo->chContent[location-len], (void *)saveRightBuf, len);
						
					}
					else
					{
						memcpy((void *)&prnLineInfo->chContent[location-1], (void *)saveRightBuf, len);
					}
					
				}//END SPDJ  
				//��Ʒ����
				else if (memcmp(tempLine2->Items[i].dataPtr,"SPSL",
					tempLine2->Items[i].DataLen) == 0)
				{		
//					if((pInv->GoodsLines[templateNo].Amount % NUMBER_EXTENSION_TEMPLATE) == 0)
					if (0)
					{
					    /*----------------------added xiaopk 2005111-----------------------*/
					    if(pInv->InvType == RETURN_INV_TEMPLATE)
						{
							sprintf(&prnLineInfo->chContent[location-1],
								"%lu",(pInv->GoodsLines[templateNo].Amount / NUMBER_EXTENSION_TEMPLATE));	
						}
						else
						{
							sprintf(&prnLineInfo->chContent[location-1],
								"%lu",(pInv->GoodsLines[templateNo].Amount / NUMBER_EXTENSION_TEMPLATE));	
						}
						/*-----------------------added end-----------------------------------*/
					
					}
					else
					{
					   
						/*___________________added Yinct 20051115______________________________*/
						/*******************************zs20070418***************************/
						if (pInv->GoodsLines[templateNo].Type == DETAIL_DISCOUNT_TEMPLATE || pInv->GoodsLines[templateNo].Type == DETAIL_REDUCTION_TEMPLATE
							|| pInv->GoodsLines[templateNo].Type == DETAIL_SERVICE_TEMPLATE)
						{
							memset((void *)tmp, 0, 8);
						}
						else
						{
							prn_log2("Amount= %u",pInv->GoodsLines[templateNo].Amount);
							realAmount = pInv->GoodsLines[templateNo].Amount & 0xFFFFFFUL;
							prn_log2("realAmount = %u", realAmount);
							multiple = 1;
							for(j=0; j<((pInv->GoodsLines[templateNo].Amount & 0xFF000000UL) >> 24); j++)
							{
								multiple *= 10;
							}
							prn_log2("multiple = %lld", multiple);
							prn_log2("realAmount = %u", realAmount);
							if (multiple <= 100)
							{
								sprintf(tmp, "%%.2f");
							}
							else
							{
								sprintf(tmp, "%%.%luf", ((pInv->GoodsLines[templateNo].Amount & 0xFF000000UL) >> 24) & (0xFF));
							}
						}
						sprintf(&prnLineInfo->chContent[location-1], tmp, (double)((double)realAmount / multiple));
						
						/*______________________________end____________________________________*/
							
					   
					}
				}
				//��Ʒ���Ҷ��룬ͬ��Ʒ���۴���
				else if (memcmp(tempLine2->Items[i].dataPtr,"SPJE",
					tempLine2->Items[i].DataLen) == 0)
				{	
					tmpLocation = location;
					if (location < 0)
					{
						location = -location;
					}


					if (pSaveTemplateInfo->workMode == WORK_MODE)
					{
						memset(saveRightBuf,0,sizeof(saveRightBuf));
						prn_log2("��Ʊ����pInv->InvType = %u", pInv->InvType);
						prn_log2("DetailCancelFlag = %u", DetailCancelFlag);
						prn_log2("��Ʒ������pInv->GoodsLines[templateNo].Type = %u",pInv->GoodsLines[templateNo].Type);
						//���Ϊ������Ʊ��Ϊ�ۿۻ���Ϊ��Ʊ��Ϊ�ۿ�
						prn_log("�����ۿ�����");
						prn_log2("���Ϊ%u",pInv->GoodsLines[templateNo].Sum / SUM_EXTENSION_TEMPLATE);
						prn_log2("(double)pInv->GoodsLines[templateNo].Sum / SUM_EXTENSION_TEMPLATE = %u",(double)pInv->GoodsLines[templateNo].Sum / SUM_EXTENSION_TEMPLATE);
						sprintf(saveRightBuf, "%.2f",
							(double)pInv->GoodsLines[templateNo].Sum / SUM_EXTENSION_TEMPLATE);

						prn_log2("saveRightBuf = %s********************",saveRightBuf);
						len = strlen(saveRightBuf);
						prn_log2("strlen(saveRightBuf) = %u",len);
						prn_log2("saveRightBuf = %s********************",saveRightBuf);


						if ( tmpLocation < 0 )
						{  
							//prn_log("��ӡλ��Ϊ��");
							//prn_log2("saveRightBuf = %s********************",saveRightBuf);
							memcpy((void *)&prnLineInfo->chContent[location-len], (void *)saveRightBuf, len);
							//prn_log2("prnLineInfo->chContent[location - len] = %s*********",&prnLineInfo->chContent[location-len]);

						}
						else
						{
							memcpy((void *)&prnLineInfo->chContent[location-1], (void *)saveRightBuf, len);
							//prn_log2("prnLineInfo->chContent[location - len] = %s*********",prnLineInfo->chContent[location-len]);

						}
					} 
					else
					{
						if(tmpLocation < 0)				
						{
							memcpy((void *)&prnLineInfo->chContent[location-4],"****",4);
							//prn_log2("prnLineInfo->chContent = %s",prnLineInfo->chContent);
						}
						else
						{
							memcpy((void *)&prnLineInfo->chContent[location-1],"****",4);
						}
					}
					
				}//end (SPJE)
				
            } //end else
		}//end (else)
	}//end (for)
	
	//prn_log2("prnLineInfo->FontH = %d", prnLineInfo->FontH);
    //prn_log("end GetPrnLineData ");	
	return 0;	
}
