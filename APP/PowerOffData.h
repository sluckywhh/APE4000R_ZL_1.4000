/****************************************************************************
�ļ���           ��PowOffData.h
����             ��awe4000r���籣�����õĽṹ�塣
��ʼ����         ��2008-03-15
����             ��Yu Yan     
****************************************************************************/


#ifndef POWER_OFF_DATA_H
#define POWER_OFF_DATA_H

#include <stdlib.h>
#include <signal.h> 
#include <errno.h> 
 
#ifndef WIN32
#include  <stdio.h>
#include  <sys/ioctl.h>
#include  <sys/timeb.h>
#include  <unistd.h>
#include  <fcntl.h>
#include  <termios.h>
#endif
#include "comdatatype.h"
#include "SysMacDef.h"
#include "powoff_protect.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define INIT_PROC 			0x01 //��ʼ������
#define FPFF_PROC 			0x02 //��Ʊ�ַ�����
#define FPDR_PROC 			0x03 //��Ʊ�������
#define FPTK_NORMAL_PROC 	0x04 //��Ʊ�����
#define FPTK_RETURN_PROC 	0x05 //��Ʊ�����
#define FPTK_WASTE_PROC 	0x06 //��Ʊ�����
#define SB_PROC   			0x07 //�걨���� 
#define WS_PROC   			0x08 //��˰����
#define INV_ROLL_PROC 		0x09 //��Ʊ��������



enum CHS_CHILD_PROC{UPDATE_INT_INFO=1};
enum FPFF_CHILD_PROC{UPDATE_INV_INFO=1, DISTRIBUTE_INV_IC};
enum FPTK_CHILD_PROC{WRITE_ICCARD=1, WRITE_INV,PRINT_INV};
enum SB_CHILD_PROC{UPDATE_DEC_INFO=1};
enum WS_CHILD_PROC{UPDATE_TAX_PAY_INFO=1};



#define MAX_FPJ_LEN 1 			//��Ʊ�ַ����籣�������Ʊ����
#define MAX_BLK_INV_LEN 4 		//�հ׷�Ʊ����˰���뱣��������
#define MAX_INVOICE_DETAILS_NUM        	16   	/**<֧�������Ʒ����*/



/**
 *@struct TInvHeadInfo 
 *@brief ��Ʊͷ��Ϣ
 */
struct TInvHeadInfo
{
	//UINT32  TypeCodeNo;                       /**<��Ʊ��������� */
	INT8	TypeCodeNo[21];						/**<��Ʊ���� *///xsr
	UINT32  InvNo;                             	/**<��Ʊ����     */
	UINT8   MachineNo;                         	/**<��Ʊ���� HEX  */
	UINT8   Type;                              	/**<��Ʊ����      */
	                                           	/**< 01����Ʊ  02����Ʊ   03����Ʊ */
	UINT32  Date;                              	/**<��Ʊ���� CCYYMMDD  */
	UINT32  Time;                              	/**<��Ʊʱ�� hhmmss    */
	INT64   TotalSum;                          	/**<��Ʊ�ܽ�� ��λ����  */
	UINT32  PosInvNo;                          	/**<ԭ��Ʊ����           */
	UINT8   ClientName[FKDW_NAME_LEN+1];       	/**<������               */
	UINT8   OperatorName[OPERATOR_NAME_LEN+1]; 	/**<��ƱԱ���HEX        */
	UINT8   OpId; 								/**<��ƱԱ���ID       */
	UINT8   TaxCtrCode[INV_TAX_CTRL_CODE_LEN]; 	/**<˰���� HEX            */
	UINT8   PayMode;                           	/**<���ʽ             
	                                           	01���ֽ�02�����ÿ���03��֧Ʊ 
	                                           	04����㣬05��ǩ��     */
	UINT8   TableID;                           	/**<̨�� HEX ���ڲ���      */
	UINT16  detailCount;					   	/**<��Ʒ�и���        	*/ 
	float   sl;									//˰��
	float   zsl;								//������
	UINT16  pzlb;								//Ʊ�����
//	UINT8   fplb;								//��Ʊ���
	UINT8   scbz;								//�ϴ���־
	UINT16  dycs;								//��ӡ����                                  	
};


/**
 *@struct TInvDetailInfo 
 *@brief ��Ʊ��Ʒ��ϸ��Ϣ
 */
struct TInvDetailInfo
{
	UINT8   Property;                      		/**<��ϸ������ HEX             */
	                                       		/**<1-һ����Ʒ�У�2-�ۿ��� 5-����      
	                                       		    3-���ۿ۵���Ʒ��,4-�������*/ 
	UINT8   GoodsCode[GOODS_CODE_LEN];     		/**<��Ʒ����                   */
	UINT8   GoodsName[GOODS_NAME_LEN+1];   		/**<��Ʒ����                   */ 
	float   TaxItem;							/**<˰��			           *///xsr
	float   zsl;								//������
	double  Amount;                        		/**<��Ʒ����                   */
	double  Price;                         		/**<����                       */
	INT64   Sum;                           		/**<���                       */
	INT64   TaxSum;                           		/**<˰��                       */
//	UINT32  rebate;                             /**<��Ʒ�ۿ�                   */  
};  


/**
 *@struct TInvFullInfo 
 *@brief ��Ʊ��Ϣ
 */
struct TInvFullInfo                            
{			  
	struct TInvHeadInfo	head;								/**< ��Ʊͷ*/					  
	struct TInvDetailInfo  detail[MAX_INVOICE_DETAILS_NUM];	/**< ��ϸ */		
												                      
};


/**
 *@struct TInvVolInfo 
 *@brief ��Ʊ������Ϣ
 */
struct TInvVolInfo
{
	//UINT8   TypeCodeNo; 						/**<��Ʊ��������� */
	INT8	TypeCodeNo[20];						/**<��Ʊ����		*/
	UINT32  StartNo;                     		/**<��ʼ��Ʊ����  */      
	UINT32  EndNo;                       		/**<��ֹ��Ʊ����  */     
	UINT32  RemainAmount;                		/**<ʣ�����      */      
	UINT8   Mac[INV_VOL_MAC_LEN];        		/**<MAC  BCD      */                
	UINT8   UsingFalg;                   		/**<0�������־   */      
	UINT8   OverFlag;                       	/**<0-�����־    */                                  	
};


/*  ��ʼ�����̵��籣������  */
typedef struct TCSHPwOffdata 
{
//	BaseInfo_f baseInfo_f;
  	unsigned char pin_buf[FCARD_PWD_LEN];             		/*��ʼ��˰�ؿ���ʼPIN��	*/                                                     
} TCSHPwOffdata; 

/*  ��Ʊ�ַ����̵��籣������  */
typedef struct TFPFFPwOffData
{
	unsigned int fpjs;                                  	/*��Ʊ����            	*/
//	InvoiceInfoPer_u fpffmx[MAX_FPJ_LEN];               	/*��Ʊ����Ϣ����      	*/
} TFPFFPwOffData;

/*  ��Ʊ������̵��籣������  */
typedef struct TFPDRPwOffData
{
	struct TInvVolInfo curInvVol;                        /*��ǰ��Ʊ����Ϣ     	*/
//	CInvVol curInvVol;                     		
} TFPDRPwOffData;


/*  ��Ʊ����̵��籣������  */
typedef struct TFPTKPwOffData
 {	
	UINT8 wasteCount;
    struct TInvFullInfo posInvInfo;						//����Ʊ��Ϣ
 //	struct TReInvInfo reInvInfo; 
 //	struct TCurInvVolInfo curInvVol; 					//��ǰ��Ʊ����Ϣ
 	UINT8  RemainLineCount;                             //����ʣ���ӡ�и���
	UINT8  BeginPrintFlag;                                   //��ǵ���ʱ�Ƿ��Ѿ���ʼ��ӡ����
 } TFPTKPwOffData;

/*  �걨���̵��籣������  */
typedef struct TSBPwOffData
{
	UINT8 reDeclareFlag;
	UINT32 declareDate;
//   	DeclareDutyData decDutyData; 							//�걨��Ϣ
} TSBPwOffData; 

/*  ��Ʊ�洢���������̱�������  */
typedef struct
{
	UINT32 invDatelimit;								/**<InvHead�����ɾ���Ľ�ֹ����  */   	
	UINT32 sumDatelimit;								/**<InvSum�����ɾ���Ľ�ֹ����  */   	
	UINT32 rtNolimit;									/**<RtInv�����ɾ���Ľ�ֹ����  */ 
	UINT32 nRefDate;                                    /**<�ϴ��걨�Ľ�ֹ����  */ 
}InvRollPwOffData;


/*  ҵ��������籣������  */
typedef struct TYWPwOffData
{
	unsigned char 	pw_off_flg; 							//0000 0000 ���λΪ1��ʾ���籣����־ Ϊ0��ʾ����
	unsigned char 	main_proc_id; 							//�����̺� 
	unsigned char 	child_proc_id; 							//�ӹ��̺�
	unsigned int 	pwoffdate; 								//��������
	unsigned int 	pwofftime; 								//����ʱ��
	unsigned char 	logflag; 								//��¼��־
	unsigned char 	invoiceException;						//��Ʊ�ַ��쳣��־
	unsigned char 	declareException;						//�걨�쳣��־
	unsigned char 	machineCancel;							//ͣ����־

//	TaxItemIndex_u taxItems[TAX_ITEM_RECORD_NUM];
//	SuperviseData_f spvData_f;
	InvRollPwOffData invRollPwOffData;						//ͣ����־

// 	struct TOperatorInfo operator;

	struct _ProcData
	{
	  struct TCSHPwOffdata    init_data; 
	  struct TFPFFPwOffData   fpff_data;
	  struct TFPDRPwOffData   fpdr_data;
	  struct TFPTKPwOffData   fptk_data;             // ��Ʊ����̵��籣������
	  struct TSBPwOffData     sb_data;
	  
	  
	}ProcData;
  
}TYWPwOffData; 


//ȡ�����־
//#define GetPowerOffFlag() g_YW_PowerOffData->pw_off_flg & 0x01
#define GetPowerOffFlag() g_YW_PowerOffData->pw_off_flg


//��������־
#define CleanPowerOffFlag() { g_YW_PowerOffData->pw_off_flg = 0; g_YW_PowerOffData->main_proc_id = 0 ; g_YW_PowerOffData->child_proc_id = 0 ;}


//���õ����־
#define SetPowerOffFlag() { g_YW_PowerOffData->pw_off_flg = 0x01 ;}


//���������̺�
#define SetPowerOffProcID_M(x) { g_YW_PowerOffData->main_proc_id = x ;}

//�����ӹ��̺� 
#define SetPowerOffProcID_C(x) { g_YW_PowerOffData->child_proc_id = x ; }

//ȡ�����̺�
#define GetPowerOffProcID_M(x) { x = g_YW_PowerOffData->main_proc_id  ;}

//ȡ�ӹ��̺� 
#define GetPowerOffProcID_C(x) { x = g_YW_PowerOffData->child_proc_id  ; }



extern struct TYWPwOffData *g_YW_PowerOffData;


void PowOff_init();
void PowOff_release();


#ifdef __cplusplus
}
#endif

#endif
