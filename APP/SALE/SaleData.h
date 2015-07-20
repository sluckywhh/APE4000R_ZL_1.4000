/*! \file    SaleData.h
   \brief    awe4000r���۳����е�����������
   \author   Yu Yan
   \version  1.0
   \date     2007-11-28
 */


#ifndef SALE_DATA_H
#define SALE_DATA_H

#include "IncludeMe.h"
#include "SysMacDef.h"
 
#include "CMachine.h"
//#include "CPlu.h"
#include "CDept.h"
//#include "CInvSum.h"
#include "CInvHead.h"
#include "CInvDet.h"
#include "CInvVol.h"
#include "CUserInfo.h"
//#include "CInvcodeLink.h"
#include "CDB.h"
//#include "TemplateDataDesign.h"
//#include "TemplateGeneralFuc.h"
//#include "TemplateIndep.h"
//#include "TemplateInterface.h"
// #include "TemplateMacro.h"
//#include "printer.h"
#include "arithmetic.h"
#include "commonFunc.h"

#include "PrintDriver.h"
#include "CRtInv.h"
#include "SaleFunc.h"
#include "CGlobalArg.h"
#include "PowerOffData.h"
#include "PrintDriver.h"

class SaleData;

extern SaleData *pSaleData; /**< ����������ָ��*/


/**
 *@enum err 
 *@brief �������
 */
enum retType
{    //����
	 SUCCEED = 1,				/**< �ɹ�*/
	 NO_SUCH_GOODS = 2,			/**< ��Ʊ��ϸ��δ�ҵ�����Ʒ*/
     EXCEED_PRICE,				/**< ���۳���*/
	 SHORT_OF_INV,				/**< ����ʣ�෢Ʊ����*/
	 TAX_ID_ILLEGAL,			/**< ˰��˰Ŀ����*/
	 NM_EXCEED,					/**< ���ſ�Ʊ����*/
     NM_SUM_EXCEED,				/**< ��Ʊ�ۼƽ���*/
	 RM_SUM_EXCEED,				/**< ��Ʊ�ۼƽ���*/
	 NVM_SUM_EXCEED,			/**< ������Ʊ�ۼƽ���*/
	 RVM_SUM_EXCEED,			/**< �����Ʊ�ۼƽ���*/
	 MONEY_NOT_ENOUGH,			/**< �ֽ����*/
     MONEY_EXCEED,				/**< �ֽ����*/
	 MONEY_ZERO,				/**< �ֽ���Ϊ��*/
	 DISCOUNT_MONEY_ZERO,        /**< �ۿ۽��Ϊ��*/
	 REDUCT_MONEY_SMALL,        /**< ���ý���С*/
	 NO_GOODS,					/**< ��Ʊ��ϸ��û����Ʒ*/
	 NO_PAPER,					/**< û��ֽ�ʷ�Ʊ*/
	 INV_ZERO,					/**< û�е��ӷ�Ʊ*/
	 PRN_INV_ERROR,				/**< ��Ʊʧ��*/
	 UPDATE_INV_VOL_ERROR,		/**< ����INV_VOL��ʧ��*/
	 REBATE_ERROR,				/**< �ۿ��ʳ���*/
	 GET_FISCAL_CODE_ERROR,		/**< ȡ˰����ʧ��*/
	 DB_SAVE_ERROR,				/**< �����ݿ�ʧ��*/
	 DB_FULL,					/**< ���ݿ�����*/
	 MALLOC_MEM_ERROR,          /**<���붯̬�ڴ�ʧ��*/
	 INV_SUM_ERROR,				/**<�����ʧ��*/
	 PRICE_NOT_ENOUGH,			/**<�۸��С*/
	 EXCEED_NAME_LEN,			/**<���������ƹ���*/
	 EXCEED_AMOUNT,             /**<��Ʒ��������*/
	 ILLEGAL_AMOUNT,             /**<��Ʒ�����Ƿ�*/
	 NO_NAME,                   /**<δ���븶��������*/
	 MUST_INPUT_SUM,            /**<���������ܼ�*/
	 MUST_RE_LOGIN,             /**<�����ص�¼*/
	 NO_GOODS_CANCEL,           /**<����Ʒ��ȡ��*/
	 RETURN_GOODS_EXCEED,		/**<�˻���������*/
	 HAVE_ROLLED,				/**<���ݹ�����*/
	 REDUCT_EXCEED,				/**<���ý�����Ʒ�н��*/
	 NO_REDUCT,					/**<����ͨ��Ʒ�У��޷�����*/
	 ONE_INV,                   /**<һ�ŷ�Ʊֻ����4����Ʒ��*/
	 NM_EXCEED_MIN,              /**<��Ʊ������*/
	 BX_RET_MONTH_ERR,           /**< ���Ʊ�Ǳ�����ǰ*/
	 TAX_UNAUTHORIZED,				/**< ˰��δ��Ȩ*/


	 //��Ʊ����
     WASTE_NUM_EXCEED,          /**< ����ʣ�෢Ʊ����*/
	 WASTE_NUM_ERROR,           /**< ���Ϸ���������*/
	 RETURN_NUM_ERROR,          /**< ��Ʊ���벻����*/
	 QUERY_ERROR,               /**< ��ѯ���ŷ�Ʊʧ��*/
	 HAVE_RT_INV,				/**< �ѿ�����Ʊ*/
	 HAVE_FU_INV,				/**< ��Ʊ�ѳ��*/
	 NO_INV,                    /**< �Ǳ����ѿ���Ʊ*/
	 RT_INV,                    /**< ��Ʊ*/
	 WT_INV,                    /**< ��Ʊ*/
	 CODE_NO_ERROR,             /**< ��Ʊ����Ƿ�*/
	 PRE_INV_ERROR,             /**< ��ѯ�ϱʽ��׺���ʧ��*/
	 NO_DIST_INV ,              /**< ��ǰ0��Ʊδ����*/
	 NO_MATCHED_INV,            /**< ��ƥ��ķ�Ʊ���*/
	 NO_START_INV,				/**< δ���뷢Ʊ��ʼ����*/
	 NO_END_INV,				/**< δ���뷢Ʊ��ֹ����*/
	 NO_ISSUED_INV,				/**< �˱���δ���ķ�Ʊ*/
	 NO_ISSUED_VOL,				/**< �˷Ǳ���δ����Ʊ */
	 CODE_INV_NO,                  /**< ��Ʊ����  */
	 NO_INV_NO,                 /**< ��Ʊ����  */
	 DIF_PYCODE,                /**< Ʊ�����벻ͬ */
	 NO_INV_ERROR,              /**< ��Ʊ��ʼ�Ŵ��ڷ�Ʊ��ֹ�� */

	 WASTE_INV_STUB,			/**< ���Ϸ�Ʊ���ܴ�ӡ���Ӵ��*/
	 NO_NET,					/**< δ������������ */
	 INV_LIB_ERR,			/**< �м�ⷵ�ش�����Ϣ	*/

	 //������Ʊ
	 GX_SV_NUM_EXCEED,			/**< ������������*/
	 GX_SV_SUM_EXCEED,			/**< ����������*/
	 GX_SV_TIME_EXCEED			/**< ��������ʱ��*/
	 
};

//��������
#define REBATE  1				/**< �ۿ�*/
#define REDUCTION  2			/**< ����*/
#define SERVICE  3				/**< �ӳɣ������*/

//����״̬
#define WORK_INCOMPLETE	 0		/**< ���۽�����*/
#define WORK_COMPLETE	 1		/**< �������  */
#define WORK_ERROR	 	 2		/**< ���۴���  */

#define MINIMUM_PRECISION 0.0000000001  /**< �Ƚϸ������Ƿ�Ϊ0�Ļ�׼*/
#define BASE_PRICE  0.01				/**< �ж���ʱ�۸��Ƿ���ֵ�Ļ�׼*/

#define CANCEL_PRODUCT 1				/**< ȡ����Ʒ*/
#define MAX_GOODS_LINE 56              /**< һ���������ߵ���Ʒ��������*/

/**
 *@class SaleData 
 *@brief ��������
 */
class SaleData
{
public:
				
	UINT8 m_workState;						  /**< ����״̬			*/

	UINT8  m_firstGoodFlag;                   /**< ��һ����Ʒ��־��������ģʽ��   */
	UINT8  m_inputClientNameFlag;             /**< ���븶���˱�־  ������ģʽ��*/
	UINT8  m_reductFlag;					  /**< �ӳɱ�־	??����ɾ��		*/
	UINT8  m_serviceFeeFlag;				  /**< ����ѱ�־  ??����ɾ��	*/

	double m_tmpPrice;						  /**< ��ʱ�۸�			*/
	INT64  m_tmpSum;						  /**< ��ʱ���			*/
	double m_tmpAmount;						  /**< ��ʱ��Ʒ����		*/
	UINT8  m_tmpDept;						  /**< ��ʱ����			*/
	double m_tmpRate;						  /**< ��ʱ�ٷ���		*/
    UINT8  m_tmpGoodsNum;                     /**< ��ʱ��Ʒ�и���   */
	string m_tmpClient;                       /**< ��ʱ����������   */
	INT64  m_tmpMoneySum;					  /**< ��ʱ����Ʊ�ۼƽ��*/
	
	UINT8  m_tmptypeCode[INV_TYPE_CODE_LEN];  /**< ��Ʊ���루BCD��*/
	UINT32 m_tmpInvNo;

	UINT8 m_saleMode;						  /**< ����ģʽ���ܼۡ���ʱ�ۣ�����	*/
	UINT8 m_invtype;                          /**< ��Ʊ���ͣ������ϡ���Ʊ  */

//	class CMachine *m_macheineInfo;			  /**< ������Ϣ				*/
	UINT32 m_maxAllowCount;					  /**< ÿ�ŷ�Ʊ���������Ʒ������	*/
	UINT32 m_maxAllowSum;					  /**< ���������			*/

//	class CPlu  *m_pluInfo;                   /**< PLU��Ϣ	*/
	class CDept *m_deptInfo;                  /**< ������Ϣ */
//	class CInvSum *m_volSumInfo;              /**< ����Ʊ������Ϣ*/
				
   // IssuedInvoice *m_issuedInvoiceData;       /**< ִ�п�Ʊ����͵����ݽṹ*/
	TPrnInvoiceInfo *m_pInvPrnData;			  /**< ��Ʊ��ӡ����				*/

	UINT8 m_fiscalCode[INV_TAX_CTRL_CODE_LEN+1];/**< ��Ʊ˰����				*/ 

	class CInvHead *m_singleInvInfo;	      /**< ���ŷ�Ʊ��Ϣ	*/
	class CInvHead *m_smallInvInfo;	          /**< ���ŷ�Ʊ��Ϣ,������Ʊ��ֳ��ķ�Ʊ	*/
				
	UINT8 m_detailCount;					  /**< ��Ʒ�������������ŷ�Ʊ��	*/
											  /**< ��������ֵ�͵��ŷ�Ʊ��Ϣ�е�����һ��*/
											  /**< �����漰�����ŷ�Ʊʱ����ֵΪ������ */
													
	UINT32 m_goodsSum;						  /**< ��Ʒ���ۼƽ��			*/

    UINT8 m_cancel;                           /**< ȡ����־         */
	double m_realCancelNum;                   /**< ʵ��ȡ����Ʒ����    */
	UINT8 m_property;                         /**< ��Ʒ�Ƿ����ۿۣ��ӳɵ� */
	class CInvDet *m_invDet;                  /**< ��Ʒ��ϸ*/
	class CInvDet *m_pHead;                   /**< ���淢Ʊ�������ͷָ�� */
	class CInvDet m_cancelDet;                /**< ȡ������Ʒ��ϸ */
	
	double m_saveAmount;					  /**< ������������Ʒ���� */
	INT32  m_dotNum;						  /**< �������������С��λ�� */

	UINT32 m_oldInv;                          /**< ���˵ķ�Ʊ���� */
//	UINT32 m_oldCodeNo;                       /**< ���˵ķ�Ʊ��������� */
	string m_oldCodeNo;						  /**< ���˵ķ�Ʊ���� */
	UINT8  m_returnOther;                     /**< �Ƿ��˷Ǳ�����Ʊ 1=�ǣ�0=�� */

	UINT32  m_nInvCount;                      /**< ��Ʊ��ӡ��Ҫ������ */ 
public:
	/*!
	@brief ���캯��	
	*/
	SaleData();

	/*!
	@brief ��������	
	*/
	~SaleData();

    /*!
	@brief �ͷŲ��������������ٵ��ڴ�	
	@param[in] nPointerNum     ָ�����
	@return  1: SUCCESS 
	*/
 //    UINT8 DelDeptSalePointer(UINT8 nPointerNum);

	/*!
	@brief ��ʼ����Ʊͷ�еĳ�Ա����	
	@return  1: SUCCESS 
	*/
	UINT8 InitInvHead();
    
	/*!
	@brief ��ʼ�����������еĳ�Ա����
	@param[in] set �Ƿ����ò��ֱ��� 1�����ã� 0��������
	@return  1: SUCCESS 
	*/
	UINT8 InitSaleData(UINT8 set);

//------------------------------
	
	/*!
	@brief ����������	
	@param[in] pluInfo      ����PLU��Ϣ�Ķ���ָ�� 
	@return  1 �ɹ��� 0 ʧ��
	*/
	UINT8 Sale(CDept *deptInfo);

    /*!
	@brief ���ݲ����������Ʒ��Ϣ	
	@param[in] nDeptNo        ����� 
	@return  1 �ɹ��� 0 ʧ��
	*/
  	UINT8 SearchGoodsByDept(INT32 nDeptNo);

	/*!
	@brief ����PLU������Ʒ��Ϣ	
	@param[in] PLUCode      PLU��
	@param[out] pluInfo      ����PLU��Ϣ�Ķ���ָ��
	@return  1 �ɹ��� 0 ʧ��
	@attention  pluInfo������NULL��
	*/
//	UINT8 SearchGoodsByPLU(string PLUCode, CPlu *pluInfo);
    
	/*!
	@brief ɨ����Ʒ��	
	@param[in] flagMakeInv  ����Ƿ�Ʊ, 1����Ʊ��0������Ʊ
	@return  1�� �ɹ��� ������ʧ��
	*/
    UINT8 ScanGoodsLine(UINT8 flagMakeInv);	

	/*!
	@brief ��Ʊ���	
	@param[in] nIfPrn �Ƿ��ӡ��Ʊ��1=��ӡ��0=����ӡ
	@param[in] nId �ӹ���ID��
	@return  1�� �ɹ��� ������ʧ��
	*/
	UINT8 MakeInvoiceHandle(UINT8 nIfPrn, UINT8 nId);
    
    /*!
	@brief �Ƚ������������Ƿ����
	@return  1�� ��ȣ� 0�������
	*/
    UINT8 doublecmp(double d1, double d2);
    
	 /*!
	@brief ����˰��
	 ��˰���  nJe= 10*100
	   ˰��    nSl= 0.17*100
	@return  ˰�� 1.45*100
	*/
//	INT64 CountTax(double fJe, double fSl);
	INT64 CountTax(INT64 nJe, INT32 nSl);
	/*!
	@brief ��װ��ӡ�ķ�Ʊͷ
	@return  1�� �ɹ��� 0��ʧ��
	*/
	UINT8 ComposePrnInv();

	/*!
	@brief ���·�Ʊ������Ϣ����ʣ�෢Ʊ����
	@return  1�� �ɹ��� 0��ʧ��
	*/
	UINT8 UpdateVolRemain(UINT32 remain);
    
	/*!
	@brief ���㵱ǰ��Ʒ�����跢Ʊ��Ŀ
	@return  ���跢Ʊ��Ŀ
	*/
	UINT32 CalculateInvNum();

    /*!
	@brief ��װΪ���˰���������͵����ݽṹ
	@param[in] smallInv ��ǰ��Ʊ��Ϣ
	@param[out] pIssuedInvData  Ϊ���˰���������͵����ݽṹ
	@return  1: SUCCESS; 0: FAILURE
	*/
//	UINT8 ComposeIssuedInvData(CInvHead *smallInv, IssuedInvoice *pIssuedInvData);
    
	/*!
	@brief ͳ��һ�ŷ�Ʊĳ˰��˰Ŀ�Ŀ�Ʊ�ܽ��
	@param[in] CodeNo ��Ʊ���������
    @param[in] InvNo  ��Ʊ��
	@param[out] TaxID  ˰��˰Ŀ��
	@return  һ�ŷ�Ʊ��ӦTaxID�Ŀ�Ʊ�ܽ��
	*/
//	INT64 GetTaxIDMoneySUM(CInvDet * invDet, UINT32 CodeNo, UINT32 InvNo, UINT8 TaxID);
	
    /*!
	@brief ��÷�α˰����
	@param[in] pIssuedInvData  Ϊ���˰���������͵����ݽṹ
	@param[out] errorcode �������
    @param[out] fiscalCode ˰����ָ��
	@return  1: SUCCESS; 0: FAILURE
	*/
//	UINT8 GetFiscalCode(IssuedInvoice *pIssuedInvData, string fpdm, UINT8 *fiscal_code);
	/*!
	@brief ��÷�α˰����
	@param[in] pInv  Ϊ���˰���������͵ķ�Ʊ���ݽṹ
	@param[out] fiscalCode  ˰����
	@param[out] strErr ������Ϣ
    @param[out] nRetCode ���̵Ĵ����
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 GetFiscalCode(CInvHead *pInv,UINT8 *fiscalCode, UINT32 &nRetCode, string &strErr);
    
   	/*!
	@brief �����
	@param[out] �Ƿ�ִ���˾���ܲ��� 1���ǣ� 0����
	@return  1: SUCCESS; 0: FAILURE
	*/
	//UINT8 InvSum(UINT8 &nIfSum);

	/*!
	@brief ����PLU��ɾ����Ʒ
	@param[in] strCode        PLU�� 
	@param[in] nCancelNum     ɾ����Ʒ���� 
	@param[out] dPrice        ɾ����Ʒ�۸�
	@return  1: SUCCESS; ��1  �������
	*/
	UINT8 CancelGoodsByPLU(string &strCode, double nCancelNum, double &dPrice);

	/*!
	@brief ���ݲ������ɾ����Ʒ
	@param[in] dpNo        ������� 
	@param[in] nCancelNum     ɾ����Ʒ���� 
	@param[out] dPrice        ɾ����Ʒ�۸�
	@return  1: SUCCESS; ��1  �������
	*/
	UINT8 CancelGoodsByDept(string dpNo, double nCancelNum, double &dPrice);

	/*!
	@brief ����ӡ��Ʊ�ṹ��ķ�Ʊͷ
	@param[out] invFullInfo ��Ʊͷ��Ϣ�ṹ��ָ��
	@param[in] smallInvInfo ��Ʊ������Ϣָ��
	@return  1�� �ɹ��� ������ʧ��
	*/
	UINT8 InvClassToStuct(struct TInvFullInfo *invFullInfo, CInvHead *smallInvInfo);

	/*!
	@brief �������ݿ����ݹ���
	@param[out] nIfRolled �Ƿ�ʵʩ�˹������� 1���ǣ�0����
	@return  1�� �ɹ��� ������ʧ��
	*/
	UINT8 RollData(UINT8 &nIfRolled);


//---------------------------������Ӧ����
    /*!
	@brief ��������	
	@param[in] nDeptNo        ����� 
	@param[in] strCode        ��Ʒ����
	@return  1 �ɹ�����1  �������
	*/
//	UINT8 DeptSale(string nDeptNo);
	UINT8 DeptSale(UINT32 nDeptNo=0, string strCode="");

	/*!
	@brief PLU����	
	@param[in] strName       ��ʱ��Ʒ���� 
	@param[in] strErr       ������Ϣ
	@return  1 SUCCESS��0��FAILURE��������Ϣ��strErr�����������������
	*/
	UINT8 PLUSale(string strName, string &strErr);
    
	/*!
	@brief �ֽ����	
	@param[out] IfInvSum   �Ƿ�����˾���� 1���ǣ�0���� 
	@return  1 �ɹ�����1  �������
	*/
	UINT8 PayByCash(UINT8 &IfInvSum);

    /*!
	@brief ���ۿ�	
	@param[in] fRate      �ۿ��� 
	@return  1 �ɹ�����1  �������
	*/
	UINT8 Discount(double fRate);

	/*!
	@brief ��ʱ������	
	@param[in] dPrice      ��ʱ�� 
	@return  1 �ɹ�����1  �������
	*/
	UINT8 PriceInput(double dPrice);

	/*!
	@brief �ܼ�����	
	@param[in] dSum     �ܼ� 
	@return  1 �ɹ�����1  �������
	*/
	UINT8 SumInput(double dSum);

	/*!
	@brief ����������	
	@param[in] chfkdw     �������ַ���ָ�� 
	@return  1 �ɹ�����1  �������
	*/
	UINT8 ClientNameInput(const char *chfkdw);
	/*!
	@brief �����˼�������˰��ͬʱ����	
	@param[in] chfkdw     �������ַ���ָ�� 
	@param[in] chfkdwsh     ������˰���ַ���ָ�� 
	@return  1 �ɹ�����1  �������
	*/
	UINT8 ClientNameInput(const char *chfkdw, const char *chfkdwsh);

	/*!
	@brief ����������	
	@param[in] dSum     �������ַ���ָ�� 
	@return  1 �ɹ�����1  �������
	*/
	UINT8 ClientCodeInput(const char *content, string &strErr);


	/*!
	@brief ��ע����	
	@param[in] content     �ַ���ָ�� 
	@return  1 �ɹ�����1  �������
	*/
	UINT8 RemarksInput(const char *content, string &strErr);

	/*!
	@brief ��Ʒȡ��	
	@return  1 �ɹ�����1  �������
	*/
	UINT8 CancelGoods(void);

	/*!
	@brief ������Ʒȡ��	
	@return  1 �ɹ�����1  �������
	*/
	UINT8 NoCancelGoods(void);

	/*!
	@brief �˷�����	
	@return  1 �ɹ�����1  �������
	*/
	UINT8 Plus(double tmpAmount);

	/*!
	@brief ����ȡ��	
	@return  1 �ɹ�����1  �������
	*/
	UINT8 TotalCancel(void);

	/*!
	@brief ����
	@param[in] money ���õ��Ľ��
	@return  1 �ɹ�����1  �������
	*/
	UINT8 GoodsReduct(double money);


	/*!
	@brief ���߿�Ʊ3�������Ƿ�����
	@param[in] nSum ��Ʊ��������
	@param[out] strErr ������Ϣ
	@return  1 SUCCESS��0  FAILURE
	*/
	UINT8 IsOffLineOk(INT64 nSum, string& strErr);

	
};

#endif
