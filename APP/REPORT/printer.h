#ifndef PRN_PRINTER_H
#define PRN_PRINTER_H


#include "SysMacDef.h"
#include "comdatatype.h"
#include "TemplateDataDesign.h"
#include "PowerOffData.h"
#include "TemplatePrintInv.h"

#ifdef __cplusplus
extern "C"
{
#endif


#define SHIDA 		1
#define PRINT_INV_DEFAULT 	0

#define MAX_CHAR_NUM		40


extern INT8 *pGeneralPrnBuff;

/*-----------------------------------------------------------------------------
��Ʊ��ӡ����  
��ӡ���ݣ�
1-��Ʊ����
2-��Ʊ�ţ���ӡ��
3-�������
4-�տλ
5-˰��
6-��Ʊ����
7-�տ�������
8-���λ�����ˣ�
9-��Ʒ���ƣ�ѭ���
10-����  ��ѭ���
11-����(���) ��ѭ���
12-��� ��ѭ���
13-���ϼƣ�Сд��
14-���ϼƣ���д��
15-˰���� 
ע����ƱҪ���ˡ���
              
------------------------------------------------------------------------------*/
PACK_PREFIX struct TInvDetailPrnData
{
	UINT8   Property;                    /*��ϸ������ HEX              1   */
	                                     /*1-һ����Ʒ�У�2-�ۿ���          */
	                                     /*3-���ۿ۵���Ʒ��,4-�������     */
	UINT8   GoodsCode[GOODS_CODE_LEN+1]; /*��Ʒ����   14 ASC               */
	UINT8   GoodsName[GOODS_NAME_LEN+1]; /*��Ʒ����   20 ASC               */
	UINT8   TaxItem;                     /*˰��˰Ŀ������              1   */
	UINT32  Amount;                      /*��Ʒ����                    4   */
	UINT32  Price;                       /*����                        4   */
	UINT32  Sum;                         /*���                        4   */
};

PACK_PREFIX struct TInvPrnData
{
	UINT8         PrintType;					/*��ӡ����             	
												NORMAL_PRINT 0  ������ӡ
												STUB_PRINT 1	�����ӡ*/
		
	UINT8         TypeCode[INV_TYPE_CODE_LEN]; /*��Ʊ������ 10 BCD             */
	UINT32        InvNo;                       /*��Ʊ����                      */
	UINT8         MachineCode[MACHINE_NO_LEN+1];/*��Ʊ����� 16 ASC             */
	UINT8         Type;                        /*��Ʊ����                      */
	                                           /* 01����Ʊ  02����Ʊ   03����Ʊ*/
	UINT8         CorpName[CORP_NAME_LEN+1];   /*�տλ���� 40 ASC           */
	UINT8         TaxCode[TAX_CODE_LEN+1];     /* ˰�� 20 ASC                  */ 
	UINT32        Date;                        /*��Ʊ���� CCYYMMDD             */
	UINT32        TotalSum;                    /*��Ʊ�ܽ�� ��λ����           */
	UINT32        PosInvNo;                    /*ԭ��Ʊ����                    */
	UINT8         ClientName[FKDW_NAME_LEN+1]; /*������ 40 ASC                 */
	UINT8         OperatorID;                  /*��ƱԱ���HEX                 */
	UINT8         OperatorName[OPERATOR_NAME_LEN+1];/*��ƱԱ������10 ASC       */
	UINT8         TaxCtrCode[INV_TAX_CTRL_CODE_LEN];/*˰���� ��8λHEX          */ 
	UINT8         InvDetailCount;              /* ��Ʒ������                   */
	struct TInvDetailPrnData InvDetailPrnData[INV_GOODS_MAX_COUNT]; /*6����Ʒ��,�ṹ���� */        	
	
};



/*--------------------------------------------------------------------------
���������Ϣ��
1����λ����
2��˰��
3�������ţ�16λ�Ļ�����ţ�
4����Ʊ��ʼʱ��
5����Ʊ��ֹʱ��
6����Ʊ����
7����Ʊ��ʼ�š�
8����Ʊ��ֹ��  
9��������Ʊ����
10��������Ʊ���߽��
11����Ʊ����
12����Ʊ����
13����Ʊ���
----------------------------------------------------------------------------*/
PACK_PREFIX struct TVolSumPrnData
{
	
	UINT8        CorpName[CORP_NAME_LEN+1];     /*��λ���� 40 ACS ���20������  */
	UINT8        TaxCode[TAX_CODE_LEN+1];       /* ˰�� 20 ASC                  */ 
	UINT8        MachineCode[MACHINE_NO_LEN+1]; /*��Ʊ����� 16 ASC             */
	UINT32       StartDate;                     /*��Ʊ��ʼ����   YYYYMMDD       */
	UINT32       EndDate;                       /*��Ʊ��������   YYYYMMDD       */
	UINT8        TypeCode[INV_TYPE_CODE_LEN*2+1];   /*��Ʊ����   10 BCD             */
	UINT32       StartInvNo;                    /*��Ʊ��ʼ����                  */
	UINT32       EndInvNo;                      /*��Ʊ��ֹ����                  */
	UINT32       PosInvCount;                   /*������Ʊ����                  */
	UINT32       PosInvSum;                     /*������Ʊ���                  */
	UINT32       WasteInvCount;                 /*��Ʊ����                      */
	UINT32       ReInvCount;                    /*��Ʊ����                      */
	UINT32       ReInvSum;                      /*��Ʊ���                      */
};
/*----------------------------------------------------------------------------
ʱ��λ��ܣ�
1����λ����
2��˰��
3�������ţ�16λ�Ļ�����ţ�
4����Ʊ��ʼʱ��
5����Ʊ��ֹʱ��
6��������Ʊ����
7��������Ʊ���߽��
8����Ʊ����
9����Ʊ����
10����Ʊ���
----------------------------------------------------------------------------*/
PACK_PREFIX struct TDateSegSumPrnData
{
	UINT8        CorpName[CORP_NAME_LEN+1];     /*��λ���� 40 ACS ���20������  */
	UINT8        TaxCode[TAX_CODE_LEN+1];       /* ˰�� 20 ASC                  */ 
	UINT8        MachineCode[MACHINE_NO_LEN+1]; /*��Ʊ����� 16 ASC             */
	UINT32       StartDate;                     /*��Ʊ��ʼ����   YYYYMMDD       */
	UINT32       EndDate;                       /*��Ʊ��������   YYYYMMDD       */
	UINT32       PosInvCount;                   /*������Ʊ����                  */
	UINT32       PosInvSum;                     /*������Ʊ���                  */
	UINT32       WasteInvCount;                 /*��Ʊ����                      */
	UINT32       ReInvCount;                    /*��Ʊ����                      */
	UINT32       ReInvSum;                      /*��Ʊ���                      */	
//	UINT8        TaxItem[TAX_ITEM_MAX_COUNT];   /*˰��˰Ŀ����hex               */
//	UINT32       PosInvSumByTax[TAX_ITEM_MAX_COUNT]; /*������Ʊ���                  */
//	UINT32       ReInvSumByTax[TAX_ITEM_MAX_COUNT];  /*��Ʊ���                      */	
};


/*--------------------------------------------------------------------------- 
�ս��׻��ܱ���
1����λ����
2��˰��
3���������
4����Ʊʱ��
5��������Ʊ����
6����Ʊ����
7����Ʊ����
8��˰��˰Ŀ��ѭ�� �ܹ�6�֣�
9��������Ʊ���߽�� ��ѭ����
10����Ʊ��� ��ѭ����
--------------------------------------------------------------------------*/
PACK_PREFIX struct TDaySumInfoPrnData
{

	UINT8        CorpName[CORP_NAME_LEN+1];     /*��λ���� 40 ACS ���20������  */
	UINT8        TaxCode[TAX_CODE_LEN+1];       /* ˰�� 20 ASC                  */ 
	UINT8        MachineCode[MACHINE_NO_LEN+1]; /*��Ʊ����� 16 ASC             */
	UINT32       Date;                          /*��Ʊ����   YYYYMMDD           */
	UINT32       PosInvCount;                   /*������Ʊ����                  */
	UINT32       WasteInvCount;                 /*��Ʊ����                      */
	UINT32       ReInvCount;                    /*��Ʊ����                      */
	UINT32		 PosInvSum;						/*������Ʊ���                  */
	UINT32		 ReInvSum;						/*��Ʊ���                      */	
//	UINT8        TaxItem[TAX_ITEM_MAX_COUNT];   /*˰��˰Ŀ����hex               */
//	UINT32       PosInvSum[TAX_ITEM_MAX_COUNT]; /*������Ʊ���                  */
//	UINT32       ReInvSum[TAX_ITEM_MAX_COUNT];  /*��Ʊ���                      */	
};


/*---------------------------------------------------------------------------
�걨��Ϣ����
1����λ����
2��˰��
3��������
4���걨��ʼ����
5���걨��������
6����Ʊ����
7����Ʊ����
8����Ʊ����
9��˰��˰Ŀ��ѭ�� �ܹ�6�֣�
10��������Ʊ���߽�� ��ѭ����
11����Ʊ��� ��ѭ����
----------------------------------------------------------------------------*/
PACK_PREFIX struct TDeclareSumPrnData
{
	UINT8        CorpName[CORP_NAME_LEN+1];     /*��λ���� 40 ACS ���20������  */
	UINT8        TaxCode[TAX_CODE_LEN+1];       /* ˰�� 20 ASC                  */ 
	UINT8        MachineCode[MACHINE_NO_LEN+1]; /*��Ʊ����� 16 ASC             */
	UINT32       StartDate;                     /*�걨��ʼ����   YYYYMMDD       */
	UINT32       EndDate;                       /*�걨��������   YYYYMMDD       */
	UINT32       PosInvCount;                   /*������Ʊ����                  */
	UINT32       WasteInvCount;                 /*��Ʊ����                      */
	UINT32       ReInvCount;                    /*��Ʊ����                      */
	UINT8        TaxItem[TAX_ITEM_MAX_COUNT];   /*˰��˰Ŀ����hex               */
	UINT32       PosInvSum[TAX_ITEM_MAX_COUNT]; /*������Ʊ���                  */
	UINT32       ReInvSum[TAX_ITEM_MAX_COUNT];  /*��Ʊ���                      */	
};


/*---------------------------------------------------------------------------
 ������Ϣ��
1���������
2����������
3��Ӳ���汾��
4������汾��
 ----------------------------------------------------------------------------*/
PACK_PREFIX struct TMachinePrnData 
{
	UINT8    MachineNo[MACHINE_NO_LEN+1];      	/* �������ASC         16       */  
	UINT32   MakeDate;		                    /* ��������             4       */  
	UINT8    SoftVer[SOFT_VER_LEN +1];	        /* ����汾ASC         18       */
	UINT8    HardVer[HARD_VER_LEN +1];  	    /* Ӳ���汾ASC         18       */
	UINT8    IMEI[M2M_IMEI_LEN+1];					/*����IMEI�� */
	UINT8    IMEIFlag;
};

/*---------------------------------------------------------------------------
��Ʊ�޶�:
1-��λ����
2-˰��
3-��Ʊ���ű��
4-���ŷ�Ʊ��Ʊ����޶�
5-��Ʊ�ۼƽ���޶�
6-��Ʊ�ۼƽ���޶�
-----------------------------------------------------------------------------*/
PACK_PREFIX struct TInvLimitPrnData
{
	UINT8    CorpName[CORP_NAME_LEN+1];         /*��λ���� 40 ACS ���20������  */
	UINT8    TaxCode[TAX_CODE_LEN+1];           /* ˰�� 20 ASC                  */
	UINT8    MachineNo[MACHINE_NO_LEN+1];      	/* ������� ASC        16       */  
	UINT32   SigleInvLimit;                     /*���ŷ�Ʊ�޶�                  */
	UINT32   PosInvTotalLimit;                  /*������Ʊ�ۼ��޶�              */  
	UINT32   ReInvTotalLimit;                   /*��Ʊ�ۼ��޶�                  */
};

/*----------------------------------------------------------------------------
 ��ҵ��Ϣ
1-˰�ؿ����
2-˰�ؿ�ʹ�ÿ���
3-Ӧ����������
4-Ӧ����Ч����
5-��˰������
6-��˰�˱���
7-˰��
8-���ܷ־ִ���
9-�걨��ʽ
10-��Ʊ��ֹ����
11-���ŷ�Ʊ��Ʊ����޶�
12-��Ʊ�ۼƽ���޶�
13-��Ʊ�ۼƽ���޶�
---------------------------------------------------------------------------- */
PACK_PREFIX struct TCorpInfoPrnData
{
	UINT8  Nsrsbh[CORP_SBH_LEN+1];				/**< ��˰��ʶ��� */
	UINT8  Nsrmc[CORP_NAME_LEN+1];				/**< ��˰������ */
	UINT8  Nsrswjgdm[CORP_SWJGDM_LEN+1];		/**< ����˰����ش��� */
	UINT8  Nsrswjgmc[CORP_JYXMZWMC_LEN+1];		/**< ����˰��������� */
	UINT8  Jspsbh[CORP_JSPBH_LEN + 1];			/**< ��˰���豸�� */		
	UINT8  Zfbz[CORP_ZFBZ_LEN];					/**< ���ֻ���־�� 0�������� 1����ֻ� */
	UINT8  Qylx[CORP_QYLX_LEN + 1];				/**< ��ҵ���� */
	UINT8  Qysj[CORP_QYSJ_LEN + 1];				/**< ����ʱ�� */
};
/*----------------------------------------------------------------------------
Ʊ����Ϣ
1-��Ʊ�������
2-��Ʊ��������
3-��Ʊ��С���߽��
4-��Ʊ��󿪾߽��
---------------------------------------------------------------------------- */
PACK_PREFIX struct TInvKindInfoPrnData
{
	UINT8  InvKindCode[INV_KIND_CODE_LEN+1];	/**< ��Ʊ������� */
	INT64 MaxSign;		/**< ���ŷ�Ʊ�޶� */	
	UINT32 Lxssr;			/**< ���������գ�ÿ�µĵڼ��죩 */
	UINT32 Lxkjsj;		/**< ���߿���ʱ�䣨��λСʱ�� */
	INT64  InvMaxMoney;		/**< ��Ʊ��󿪾߽�� */
};

/*------------------------------------------------------------------------
 ���񱨱�
1-��ʼ����
2-��ֹ����
3-�ۿ�
4-�����
5-�˻�
6-�ֽ�����
7-�ֽ����
8-�ֽ�֧��
9-���ÿ�֧��
10-���֧��
11-ǩ��֧��
12-Ӫҵ��
 --------------------------------------------------------------------------*/
PACK_PREFIX struct TFinancePrnData
{
	UINT32 StartDate;              /*��ʼ����                                 */          
	UINT32 EndDate;                /*��ֹ����                                 */
	UINT32 DiscountSum;            /*�ۿ�                                     */
	UINT32 ServiceFeeSum;          /*�����                                   */
	UINT32 ReInvSum;               /*�˻�                                     */
	UINT32 CashEnterSum;           /*�ֽ�����                                 */
	UINT32 CanshOutSum;            /*�ֽ����                                 */
	UINT32 CashPaySum;             /*�ֽ�                                     */ 
	UINT32 CreditPaySum;           /*���ÿ�                                   */ 
	UINT32 ExchangePaySum;         /*���                                     */
	UINT32 SignPaySum;             /*ǩ��                                     */
	UINT32 Turnover;               /*Ӫҵ��                                   */
};

//--------------------------------------------------------------------------
//˰��˰Ŀ��Ϣ                                                   51
//--------------------------------------------------------------------------
PACK_PREFIX struct TTaxItem                       
{
	UINT8   ID;                           		//˰��˰Ŀ������HEX   Ψһ  1 
	UINT8   Code[TAX_ITME_CODE_LEN*2+1];      		//˰����Ŀ���� BCD          4
	UINT32  TaxRate;                      		//˰������1000��, ��130��ʾ˰��0.13 4
//	UINT8   ChName[TAX_ITEM_NAME_LEN+1];  		//��Ӫ��Ŀ��������         21
	//UINT8   EnName[TAX_ITEM_NAME_LEN+1];  		//��Ӫ��ĿӢ������         21
	//Key:ID                                                 
	//Query: ID                                               
};

/*------------------------------------------------------------------------
˰��˰Ŀ��Ϣ��
1-��Ŀ��
2-˰��˰Ŀ������
3-˰����Ŀ����
4-˰��
5-��Ӫ��Ŀ��������
6-��Ӫ��ĿӢ������
 --------------------------------------------------------------------------*/
PACK_PREFIX struct TTaxItemPrnData
{
	UINT8   Count;                               /*˰��˰Ŀʵ��ʹ�ø���     */     
	struct TTaxItem TaxItems[TAX_ITEM_MAX_COUNT];/*˰��˰Ŀ�б�             */
};

/*----------------------------------------------------------------------------
 ��ȡ����������ݣ�
		
1-δ�ϴ���Ʊ����
2-δ�ϴ���Ʊʱ��
3-δ�ϴ���Ʊ�ۼƽ��
4-�ϴ�����
5-�ϴ�ʱ����
---------------------------------------------------------------------------- */
PACK_PREFIX struct TGetOffLineData
{
	UINT32 Wscfpzs;
	UINT32 Wscfpsj;
	INT64  Wscfpljje;
	UINT32 Sczs;
	UINT32 Scsjjg;
};

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
int print_macinfo(struct TMachinePrnData *machineData,  UINT8 bFindBlackMark );

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
int print_corpinfo(struct TCorpInfoPrnData *corpData,  UINT8 bFindBlackMark );


/*!
@brief Ʊ����Ϣ��ӡ����
@param[in] invkindData Ʊ����Ϣָ��
@param[in] bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ��ʼ��ӡ
\author   zcy
\version  1.0
\date     2011-7-5

*/
int print_invKindinfo(struct TInvKindInfoPrnData *invkindData,  UINT8 bFindBlackMark );


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
INT8 print_volumeinfo(struct TVolSumPrnData *volsumdata,UINT8 bFindBlackMark);


/**************************************************************************
����     ����ӡʱ��η�Ʊʹ�û������ݱ���
��ʽ     ��int print_dateseginvsuminfo( struct TDateSegSumPrnData * dateSegSumData
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
                             UINT8 bFindBlackMark, UINT32 startTime, UINT32 endTime);

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
int print_daystatinfo( struct TDaySumInfoPrnData *daySumData, UINT8 bFindBlackMark );

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
int print_sbstatinfo(  struct TDeclareSumPrnData *DeclareSumPrnData  );

/**************************************************************************
����     ����ӡ57mm��Ʊ
��ʽ     ��UINT8 print_inv57( struct TInvPrnData *invData,
                 UINT8 bFindBlackMark )
������� ��struct TInvPrnData *invData  ��Ʊ����
         ��UINT8 bFindBlackMark �Ƿ�Ѱ�Һڱ꣬Ϊ1ʱ,���������ҵ���һ���ڱ�
                               ��ʼ��ӡ
������� ��
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/

INT8 print_inv57(TPrnInvoiceInfo *invData);
                 
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

//INT8 print_taxiteminfo(UINT8 bFindBlackMark );

/**************************************************************************
����     �����ʼ���ص���Ϣ
��ʽ     ��int print_initinfo()
������� ��struct TCorpInfoPrnData *corpData ��ҵ�û���Ϣ
         ��
������� ��
����ֵ   ��
����     ��
����     ��
ժҪ     ��
**************************************************************************/
void  print_initinfo(UINT8 Init_Update);

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

INT8 print_invoiceLimits( struct TInvLimitPrnData *invLimits, UINT8 bFindBlackMark );

/**************************************************************************
����     ���жϴ�ӡ����ǰ�Ƿ�Ϊæ
��ʽ     ��UINT8  IsBusy(void);
������� ����
������� ����
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
UINT8  IsBusy(void);


PACK_PREFIX struct TBegin_End_Date
{
	UINT32       StartDate;                     /*ͳ����ʼ����   YYYYMMDD       */
	UINT32       EndDate;                       /*ͳ�ƽ�������   YYYYMMDD       */
};

//----------------------------------���С�--------------------------------
PACK_PREFIX struct TInvDetail_Line
{
	UINT32      Date;                	  /*����   YYYYMMDD       */
	UINT32      InvNo;                    /*��Ʊ����              */
	INT64  	Sum;                      /*���              4   */
};

//----------------------------------��β��--------------------------------
PACK_PREFIX struct TInvDetail_End
{
	UINT32      PosInvSum;              	 /* ��Ʊ���  */
	UINT32      ReInvSum;                    /* ��Ʊ���  */
	INT64  	NetInvSum;                   /* �����    */
};

/*--------------------------------------------------------------------------
�Խ��� 2005-04-06

����վ ��Ʊ��ͳ�Ʊ��� ���ݽṹ
------------------------------------���С�----------------------------------*/
PACK_PREFIX struct TDay
{
	UINT32      Date;                	  /*����   YYYYMMDD       */
	UINT32  	Amount;                   /*��Ʒ����          4   */
	INT64  	Sum;                      /*���              4   */
};

/*--------------------------------------------------------------------------
�Խ��� 2005-04-06

����վ ��Ʊ��ͳ�Ʊ��� ���ݽṹ
------------------------------------���С�----------------------------------*/
PACK_PREFIX struct TMonth
{
	UINT32      month;                	  /*����   YYYYMM       */
	UINT32  	Amount;                   /*��Ʒ����          4   */
	INT64  	Sum;                      /*���              4   */
};

/*--------------------------------------------------------------------------
�Խ��� 2005-04-07

����վ ���۱��� ���ݽṹ
------------------------------------���С�----------------------------------*/
PACK_PREFIX struct TSalesman
{
	char       Name[OPERATOR_NAME_LEN+1];/*��ƱԱ������10 ASC       */
	UINT32  	Amount;                   /*��Ʊ����          4   */
	INT64  	Sum;                      /*���              4   */
};

/*--------------------------------------------------------------------------
�Խ��� 2005-04-07

����վ ��Ʒ ���ݽṹ
------------------------------------���С�----------------------------------*/
PACK_PREFIX struct TGoods
{
	UINT32 GoodsNum;					/*��Ʒ��������ӡʱ����С����2λ	*/	
	UINT32  Price;                       /*����                  4   */
	INT64  SalesSum;                    /*���۽��              4   */

	char   	GoodsName[GOODS_NAME_LEN+1]; /*��Ʒ����   20 ASC         */
};

/*-------------------------------------------------------------------------
		����վҪ�� ��ͳ�� ����
		
����     ���Խ���                       
����     ��2005-04-06
---------------------------------��ͷ��----------------------------------*/


/**************************************************************************
����     ��
��ʽ     ��
������� ����
������� ����
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
void print_Head( struct TBegin_End_Date *Begin_End_Date, \
						   int x0,int y0,char *Title, \
						   int x1,int y1,char *FieldName_1, \
						   int x2,int y2,char *FieldName_2, \
						   int x3,int y3,char *FieldName_3 );

/**************************************************************************
����     ��
��ʽ     ��
������� ����
������� ����
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
void print_invDetail_Line( struct TInvDetail_Line *invDetail_Line );

/**************************************************************************
����     ��
��ʽ     ��
������� ����
������� ����
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
void print_invDetail_End( struct TInvDetail_End *invDetail_End );

/**************************************************************************
����     ��
��ʽ     ��
������� ����
������� ����
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
void print_Day_Line( struct TDay *day );

/**************************************************************************
����     ��
��ʽ     ��
������� ����
������� ����
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
void print_NetSum_End( INT64 NetSum , INT64 LiterSum);

/**************************************************************************
����     ��
��ʽ     ��
������� ����
������� ����
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
void print_Month_Line( struct TMonth *Month );

/**************************************************************************
����     ��
��ʽ     ��
������� ����
������� ����
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
void print_Goods_Line( struct TGoods * Goods );

/**************************************************************************
����     ��
��ʽ     ��
������� ����
������� ����
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
void print_Sales_Line( struct TSalesman *Salesman );

/**************************************************************************
����     ��
��ʽ     ��
������� ����
������� ����
����ֵ   ��-1����ʧ�ܣ�0�����ɹ�
����     ��
����     ��
ժҪ     ��
**************************************************************************/
INT8 PrintRptTitle(INT8 *title);

#ifdef __cplusplus
}
#endif

#endif
