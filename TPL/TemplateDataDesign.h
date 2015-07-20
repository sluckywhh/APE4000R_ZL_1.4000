/*! \file    TemplateDataDesign.h
\brief    ��ӡģ�����ݽṹ��
\author   Xiao Pengkun   2005-07-20
 */

#ifndef  PRN_DATA_DESIGN_H
#define  PRN_DATA_DESIGN_H

#include "TemplateMacro.h"
#include "VersionConfig.h"

#define PT_NAME_LEN          20          //ģ�����Ƴ���
#define PT_VER_LEN           8          //ģ��汾�ų���
#define PT_DIS_LEN           20         //����������
#define PT_DATE_LEN          16         //���ڳ��� 
#define PT_MAX_ITEM_COUNT    12         //ģ���д�ӡ��������
#define PT_FIELD_NAME_LEN    16         //�ؼ������Ƴ���
#define PT_FIELD_VALUE_COUNT 6          //һ���ֶ�ֵ��������
#define PT_LINE_TMP_BUF_LEN  32         //ģ������ʱ���泤��

#define PRINT_DATA_BUF_LEN  4096 //��ӡ������棬��Ҫ�Ƿ�Ʊ�ͱ����������

#define PRINT_LINE_WORD_LEN 64 //��ӡ������ӡ�ַ���

#define PRINT_LINE_BUF_LEN 128 //��ӡ�л���,���������ӡ������

#define PRINT_TEMPLATE_BUF_LEN  4096//��ӡģ�建��,�洢ģ���ļ�

#define TEMPLATE_LINE_BUF_LEN   256 //ģ���л��棬ÿ����ȡģ���ļ�һ��

#define PRINT_TEMPLATE_LINE_FIELD_BUF_LEN  256//ģ�����и������Ի���

#define MATCH_FIELD_LABEL_BUF_LEN   64       //ƥ�����и����Ա�ǩ

#define BEGIN_END_CHARACTER0  '/' //ģ���ļ���ע�ͱ�־

#define BEGIN_END_CHARACTER1  '*'

#define ATTIBUTE_SEPERATE_FIELD '#'//ģ�������Ա�ǩ�����ݵķָ���

#define TEMPLATE_LINE_END_CHARACTER '\n'//ģ���н�����־

#define TEMPLATE_ATTRIBUTE_SEPERATE_CHARACTER '~'//ģ�������Էָ���

#define PRINT_TEMPLATE_FILE_NAME  "../template"//��ӡģ��Ĵ洢�ļ�·�����ļ�����ǰ8�ֽ�

/*ģ���й����ݽṹ*/

//#define CPLUSPLUS_A
#define SIG_LINE_LEN   50   //һ�д�ӡ����


//��ӡģ����0
typedef struct
{
	//INT8 rptName[PT_NAME_LEN+1];     //��������ASC��20
	UINT8    TempType;                //ģ�����ͣ���Ʊ�򱨱�
	INT8     chVer[PT_VER_LEN+1];      //�汾
	INT8     chDis[PT_DIS_LEN+1];      //Ӧ�õ���
	INT8    chDate[PT_DATE_LEN+1];     //Ӧ������
}TPrnTempLine0;

//��ӡģ����1
typedef struct 
{
	UINT16 PaperW;                  //��ӡֽ���  
	UINT16 PaperL;                  //��ӡֽ���� 
	INT16  FontH;                   //����߶�
	INT16  FontW;                   //������
	UINT8  MarkFlag;                //�ڱ��־ 1���޺ڱ꣬2����3���ң�4������ 
	//UINT8  SetFlag;                 //�״��־ 1��ȫ��2���״�
/*-----------------added xiaopk 20060207--------------------*/
	UINT8  FixedLengthFlag;             //������ӡ��־
/*-------------------added end------------------------------*/
	UINT8  MaxInvLineCount;         //��Ʊ�����ϸ����
	//UINT8  PrintType;               //��Ʊ���ͣ�1---���Ӵ����0---����Ʊ 
	INT32   RepairPoint;                  //��Ʊ��ӡ������
	UINT8  MaxFKDWCharacter;        //��Ʊ��ӡ�и��λÿ������ַ���
	UINT8  MaxSKDWCharacter;        //��Ʊ��ӡ���տλÿ������ַ���
	UINT8  MaxSKDWDZCharacter;        //��Ʊ��ӡ���տλ��ַÿ������ַ���
	UINT8  MaxSKYCharacter;         //��Ʊ��ӡ���տ�Աÿ������ַ���
	UINT8  MaxSPMCCharacter;        //��Ʊ��ӡ����Ʒ����ÿ������ַ���
	UINT8  MaxJEDXCharacter;        //��Ʊ��ӡ�н���дÿ������ַ���
	UINT8  EndBackwardFlag;		//��ӡ��������ֽ��־  0����ֽ��1����ֽ�����룺EndForwardPoint
    INT32  EndForwardPoint;         //��ӡ��������ֽ����
    INT32  BeginForwardPoint;       //��ӡ��ʼ��ֽ����
	UINT8  MaxBZCharacter;        //��Ʊ��ӡ�б�עÿ������ַ���
    
    /*---------added xiaopk 20051123------------------------*/
    INT16  BackwardPoint;           // 2010��ӡ��������ֽ����
    /*----------added end------------------------------------*/
    UINT8  MaxGoodsCount;           //���ڶ�����������Ʒ����
    UINT16 UnfixedForwardPoint;    //��������ӡ��������ֽ�ľ���
/**********for 57mm***********/
	UINT8  InvFlag76;              //�ж��Ƿ��76/57mm	
/**********for 57mm***********/
	

	UINT16  QRCodeLeftMargin;		//��ά����߾�

}TPrnTempLine1;

//��ӡ��
typedef struct
{
	UINT8 Type;                   //0-δʹ�ã�1����ǩ��2����ӡ����
	INT16 Left;                   //����λ��
	UINT8 DataLen;
	INT8  *dataPtr;
	
}TPrnTempItem;

//��ӡ������
typedef struct 
{
	UINT8 Index;                            //�к�
	UINT8 Type;                             //�����ͣ�0--��ͨ�� 1-���У�2����Ч��
	UINT8 High;                             //�и�
	UINT8 BhighOne;					       //�м��1
    UINT8 BhighTwo;                        //�м��2 
    INT32 EmptyForwardHigh;                //������ֽ�ľ��� 
	INT16 FontW;						    //������
  	INT16 FontH;                            //����߶�
	INT8  chDatabuf[PRINT_LINE_BUF_LEN+1];  //�л���
    TPrnTempItem Items[PT_MAX_ITEM_COUNT];  //��ӡ�����12��
	UINT8 TotalCount;                       //��ǩ�����ݸ����ĺ�
	UINT8 GoodsNo;                          //��Ʒ��ϸ�����
	
}TPrnTempRow;


//��ӡ�����ݽṹ
typedef struct
{
  INT32 Property;					   //0-��ͨ�У�1������, 2--��Ч�У�3--������
  INT32 High;						   //�и�
  UINT8 Bhigh; 
 
  INT16 EmptyForwardHigh;              //������ֽ�ľ��� 
  INT16 BeginForwardPoint;             //��ӡ��ʼ��ֽ����
  INT16 EndForwardPoint;               //��ӡ������ֽ����
  INT16 BackwardPoint;                 // 2010��ӡ��������ֽ����
 
  INT8  MarkFlag;                      //�Ƿ��Һڱ�
  INT16 FontW;						   //������
  INT16 FontH;                         //����߶�
  INT8	chContent[PRINT_LINE_BUF_LEN+1]; //��ӡ����  
} TPrnLineInfo;



//��Ʊ��Ʒ�����ݽṹ
typedef struct
{

	UINT8    Type;                                  //��Ʒ��
	                                                //���ʣ�1-��ͨ��Ʒ�� 2-�ۿ��� 3-���ۿ۵���Ʒ�� 4-���
	                                                //������������,���Ϊ�� ��,ֻ��ӡ����* 7--��Ʒ���Ƴ���վ׮����Ʒ��
	INT8     chProductPLUCode[PLU_CODE_PRN_LEN+1];  //��Ʒ����
	INT8     chCorpDefCode[PLU_CODE_PRN_LEN+1];     //�̼��Զ������(Ψһ) 
	INT8     chProductName[PLU_NAME_PRN_LEN+1];		//��Ʒ����

#ifdef CPLUSPLUS_A //C++�ӿ���������
	double   Amount;                                //��Ʒ����
	double   Price;                                 //���� 
	double   DiscountPrice;                         //�ۺ��
	double   Sum;                                   //���
	double   DiscountSum;                           //�ۺ���  
#else              //C�ӿ���������
	INT64   Amount;                                //��Ʒ����
//	UINT32   Price;                                 //���� 
	INT64   Price;                                 //���� 
	UINT32   DiscountPrice;                         //�ۺ��
//	UINT32   Sum;                                   //���
	INT64   Sum;                                   //���
	INT64   TaxSum;                                 //˰��
	UINT32   DiscountSum;                           //�ۺ���  
#endif

	float    TaxItemIndex;                          //˰��
	float    Zsl;									//������
	UINT32   DeptIndex;                             //��Ʒ��������������
	UINT8    ProductLineNo;                         //��Ʒ�����

}TPrnInvGoodsLine;

//
typedef struct 
{
	UINT8   PrintType;				//�״����ȫ��,01:�״� 02��ȫ�� 03:���Ӵ��
	UINT8   InvType;                //��Ʊ����, 01����Ʊ 02����Ʊ 03����Ʊ
	UINT8   PayMode;                //���ʽ    
	UINT32  PosInvNo;               //ԭ��Ʊ����,��Ϊ��Ʊ��
	UINT8   GoodsLineCount;         //��Ʒ��ϸ������
	UINT8   PrintKind;               //��Ʊ��ӡ��ʽ 

#ifdef CPLUSPLUS_A		//C++�ӿ���������
	INT8    DateStr[DATE_PRN_LEN+1];					//��Ʊ���� 
#else					//C�ӿ���������
	UINT32	m_Date;                                     //��Ʊ���� CCYYMMDD
	UINT32  m_Time;	                                    //��Ʊʱ��
#endif

	INT8    chTypeCode[INV_TYPE_CODE_PRN_LEN+1];		//��Ʊ���� 
	UINT32  InvNo;										//��Ʊ����
	INT8    chCorpName[CORP_NAME_PRN_LEN+1];			//��˰������
	INT8    chCorpNo[CORP_NO_PRN_LEN+1];				//��˰�˱��
	INT8    chCorpCode[CORP_TAX_CODE_PRN_LEN+1];		//��˰��˰��20ASC
	INT8    chClientName[CORP_NAME_PRN_LEN+1];			//������
	INT8    chClientCode[CORP_TAX_CODE_PRN_LEN+1];							//�����˴���
	INT8    chMachineNo[MACHINE_NO_PRN_LEN+1];			//��������   

	INT8    chPosCode[INV_TYPE_CODE_PRN_LEN+1];		//ԭ��Ʊ���� 


	UINT32  OperatorID;									//�տ�Ա���
	INT8    chOperatorName[OPERATOR_NAME_PRN_LEN+1];    //�տ�Ա����
	INT8    chShopNo[SHOP_CODE_PRN_LEN+1];              //���   
	INT8    chMachineIndex[CORP_DEF_MACHINE_NO_PRN_LEN+1];//��ҵ�Զ���������
	INT8    chKPLSH[KPLSH_PRN_LEN+1];                   //��Ʊ��ˮ��  
	INT64  InvSumLowcase;										//���ŷ�Ʊ��˰�ϼ�Сд
	INT8    chInvSumUppercase[INV_SUM_CH_PRN_LEN+1];			//���ŷ�Ʊ��˰�ϼƴ�д

	INT64  InvTaxLowcase;										//���ŷ�Ʊ�ϼ�˰��Сд
	INT64  InvMoneyLowcase;									//���ŷ�Ʊ�ϼƽ��Сд

	INT8    chTaxCtrCode[INV_TAX_CTRL_CODE_PRN_LEN+1];			//˰���� 8HEX->20ASC
	INT8    chJzlshCode[INV_TAX_CTRL_CODE_PRN_LEN+1];			//˰���� 8HEX->20ASC
	INT8    chClientTelephoneNo[CLIENT_PHONE_PRN_LEN +1];          //����ֻ���

	INT8    chCorpAddr[CORP_ADDR_PRN_LEN+1];					//��˰�˵�ַ
	INT8    chPhoneNo[CORP_PHONE_PRN_LEN+1];					//��˰�˵绰

	INT8    chRemarks[REMARKS_LEN+1];                 //�����ֶ�
	INT8    chSelfDefTab1[SELF_DEF_TAB_LEN+SELF_DEF_TAB_LEN+4];        //�Զ���1,��ΪҪ�ӡ�����
	INT8    chSelfDefCont1[SELF_DEF_TAB_LEN+1];       //�Զ�������1
	INT8    chSelfDefTab2[SELF_DEF_TAB_LEN+SELF_DEF_TAB_LEN+4];        //�Զ���2
	INT8    chSelfDefCont2[SELF_DEF_TAB_LEN+1];       //�Զ�������2
	INT8	chHYFL[SZSM_CH_NAME_LEN+1];		//��ҵ����

	INT8    chKPDZJC[KPDZJC_CH_LEN+1];            //��Ʊ��ַ���

	INT8    chYWTM[YWTM_CH_LEN+1];            //һά����
/*
#if YILIAO_VERSION
	UINT8	chZYH[ZYH_LEN+1];									//סԺ��
	UINT8   chZPH[ZPH_LEN+1];
#endif*/
	
	
/*
#if PETROL_STATION_VER
    UINT8   OilGunID;											//��ǹ��
   
#endif*/


	TPrnInvGoodsLine GoodsLines[GOODS_LINE_MAX_PRN_COUNT];		//��Ʒ��

}TPrnInvoiceInfo;

//��Ҫ�����ģ������
typedef struct 
{
	UINT8	markFlag;                 //1 �ڱ� �� 0 ����
	INT8	TempVersion[32];           
	UINT8   MaxSPMCCharacter;        //��Ʊ��ӡ����Ʒ����ÿ������ַ���
	UINT8   EndBackwardFlag;		//��ӡ��������ֽ��־  0����ֽ��1����ֽ�����룺EndForwardPoint
	UINT16  EndForwardPoint;         //��ֽ�ľ���
	UINT8   MaxGoodsCount;            //���ŷ�Ʊ�����Ʒ����
	UINT8   workMode;                   /*��Ʊ������ģʽ WORK_MODE-�������� */
										/*           TRAINING_MODE-ѵ��ģʽ	*/
	UINT8   FixedModeFlag;              //��������ģʽ��־��1Ϊ������0Ϊ������
	UINT16  BackwardPoint;           // 2010��ӡ��������ֽ����
	INT32   RepairPoint;			 //zongcan test
/**********for 57mm***********/
	UINT8   InvFlag76;                 //�ж��Ƿ��76/57
/**********for 57mm***********/
	UINT16	QRCodeLeftMargin;			//��ά����߾�
/*	UINT16  FontH;
	UINT16  FontW;
	UINT8   MaxFKDWCharacter;        //��Ʊ��ӡ�и��λÿ������ַ���
	UINT8   MaxSKDWCharacter;        //��Ʊ��ӡ���տλÿ������ַ���
	UINT8   MaxSKYCharacter;         //��Ʊ��ӡ���տ�Աÿ������ַ���
	UINT8   MaxJEDXCharacter;        //��Ʊ��ӡ�н���дÿ������ַ���
    INT32   BeginForwardPoint;       //��ӡ��ʼ��ֽ����
    UINT16  BackwardPoint;           // 2010��ӡ��������ֽ����
    UINT16  UnfixedForwardPoint;
 */
}TSaveTemplateInfo;

#endif

