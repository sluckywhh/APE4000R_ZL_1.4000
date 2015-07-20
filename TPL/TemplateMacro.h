/*! \file   TemplateMacro.h
\brief    ��ӡģ��궨��
\author   Xiao Pengkun
 */

#ifndef PRN_MACRO_H
#define PRN_MACRO_H

#include "comdatatype.h"

#ifndef RETURN_INV
#define RETURN_INV    2
#endif

#ifndef RET_MANUAL_INV
#define RET_MANUAL_INV   6
#endif

#ifndef RET_SPECIAL_INV
#define RET_SPECIAL_INV		7
#endif

#ifndef NORMAL_INV
#define NORMAL_INV    1
#endif

#ifndef STUB_PRINT	
#define STUB_PRINT	1
#endif

#define NORMAL_TEMPLATE_LINE              0     //��ͨģ����
#define EMPTY_TEMPLATE_LINE               1     //��ģ����
#define INVALID_TEMPLATE_LINE             2     //��Чģ����
#define NEED_SAVE_TEMPLATE_LINE           3     //��Ҫ�洢���ݵ�ģ����
#define END_INVOICE_HEAD_LINE             4     //��Ʊͷ��ģ������� 
#define END_INVOICE_DATA_LINE             5     //��Ʊ����ģ�������

#define MAX_DETAIL_COUNT                 64
/*��Ʒ��ϸ������*/
#define  DETAIL_GENERAL_GOODS			0	/* һ����Ʒ��					*/
#define  DETAIL_DISCOUNT				1	/* �ۿ���						*/
#define  DETAIL_GOODS_DISCOUNT			2	/* ���ۿ۵���Ʒ��				*/
#define  DETAIL_SERVICE_FEE				3	/* �������						*/
#define  DETAIL_EMPTY					4	/* ����							*/
#define  DETAIL_GOODS_REDUCT			6	/* �����õ���Ʒ��	            */

#define WORK_MODE '\1'                      /* ��������ģʽ					*/
#define TRAINING_MODE '\2'                  /* ѵ��ģʽ						*/

#define  PRICE_EXTENSION_TEMPLATE		   100			/* �۸�Ŵ���					*/
#define  NUMBER_EXTENSION_TEMPLATE	       10000			/* �����Ŵ���					*/
#define  SUM_EXTENSION_TEMPLATE		       100				/* ���Ŵ���					*/
#define  RATE_EXTENSION_TEMPLATE		   100				/* �ۿ۷����ʷŴ���			*/

#define  NORMAL_PRINT_TEMPLATE 		    0				/* ������ӡ��Ʊ				 	*/
#define  STUB_PRINT_TEMPLATE 			1				/* ���Ӵ����ӡ 				*/

#define  NORMAL_INV_TEMPLATE             1               /*������Ʊ */
#define  RETURN_INV_TEMPLATE             2               /*���˷�Ʊ */
#define  WASTE_INV_TEMPLATE              3               /*���Ϸ�Ʊ */ 
#define  RETURN_INV_NOTEXIT_TEMPLATE     6               /*�˱��������ڷ�Ʊ*/  

#define  DETAIL_DISCOUNT_TEMPLATE		 1	     /* �ۿ���			*/
/*---------added zs 20070424----------------------------------------*/
#define  DETAIL_REDUCTION_TEMPLATE		 5		/* ������			*/
#define  DETAIL_SERVICE_TEMPLATE		 4		/* �ӳ���			*/
/*----------added end---------------------------------------------------*/
/*---------added xiaopk 20051204----------------------------------------*/
#define DETAIL_SPMCMAX_DISCOUNT_TEMPLATE  8      /* ������Ʒ�е��ۿ���*/
/*----------added end---------------------------------------------------*/
#define PRICE_DISCOUNT_PRN_DEC            1    //�����ۿ۾��� 
#define PRICE_PRN_DEC                     2    //���۾��� 
#define AMOUNT_PRN_DEC                    2    //�������� 
#define SUM_PRN_DEC                       2    //����

#define DATE_PRN_LEN                      20   //���ڴ�ӡ����
#define MACHINE_NO_PRN_LEN                16   //�������(ASC)����

#define SHOP_CODE_PRN_LEN                 10   //�̵���
#define CORP_DEF_MACHINE_NO_PRN_LEN       10   //��ҵ�Զ��������ų���

#define CORP_NAME_PRN_LEN                 200   //��˰�����Ƴ���ASC
#define CORP_NO_PRN_LEN                   20//16   //��ҵ��ų���(8BCD)->16ASC
#define CORP_TAX_CODE_PRN_LEN             20   //��ҵ˰�ų���       
#define INV_TYPE_CODE_PRN_LEN             20   //��Ʊ���볤��ASC
#define INV_TAX_CTRL_CODE_PRN_LEN         20   //��Ʊ˰���볤��8HEX->20ASC
#define INV_SUM_CH_PRN_LEN                64   //��Ʊ�ܽ������Ĵ�д�ĳ���
#define KPLSH_PRN_LEN                     12   //��Ʊ��ˮ��
#define PLU_CODE_PRN_LEN                  16   //��Ʒ���볤��
#define PLU_NAME_PRN_LEN                  40   //��Ʒ���Ƴ���
#define CORP_ADDR_PRN_LEN				  100		//��ҵ���Ƴ���
#define CORP_PHONE_PRN_LEN				   24		//��ҵ�绰����
#define CLIENT_PHONE_PRN_LEN               11      //����ֻ���
#define SZSM_CH_NAME_LEN					40		//˰��˰Ŀ���ƣ���ҵ���ࣩ
#define KPDZJC_CH_LEN                      100      //��Ʊ��ַ���
#define  YWTM_CH_LEN                        20       //һά����        

#define GOODS_LINE_MAX_PRN_COUNT          16//6    //��Ʊ��Ʒ��������    

#define OPERATOR_NAME_PRN_LEN             10   //����Ա���Ƴ���

#define REMARKS_LEN                        80  //��ע����
#define SELF_DEF_TAB_LEN                   18  //�Զ����ǩ����
#define SELF_DEF_CONT_LEN                  20  //�Զ������ݳ���

#endif























