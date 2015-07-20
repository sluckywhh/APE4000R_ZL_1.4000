/*! \file    SaleData.cpp
\brief    awe4000r���۳����е�����������
\author   Yu Yan
\version  1.0
\date     2007-11-28
*/


#include "SaleData.h"
//#include "SysMacDef.h"
#include "TDateTime.h"
#include "VersionConfig.h"

#include "CaProgressBar.h"
#include "CaMsgBox.h"
#include "CInvServ.h"
#include "CInvSum.h"
#include "powoff_protect.h"
#include "CTax.h"


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


#define POWEROF_SPEED_TEST	0  /**< ������Ҫ���籣���Ĵ��������ʱ��*/

#ifndef WIN32
#if POWEROF_SPEED_TEST
#include <sys/timeb.h>
#endif
#endif



SaleData *pSaleData = NULL; /**< ����������ָ��*/


SaleData::SaleData()
{
	DBG_PRINT(("����SaleData������������Ϣ��ʼ����"));
	
	InitSaleData(1);  
	m_deptInfo = NULL;				//������Ϣ				
	m_pInvPrnData = NULL;			//��Ʊ��ӡ����			
	m_singleInvInfo = NULL;	        //���ŷ�Ʊ��Ϣ
	m_smallInvInfo = NULL;          //���Ŵ�ӡ��Ʊ��Ϣ 
	m_invDet = NULL;				//?
	m_pHead = NULL;					//?
	m_tmpGoodsNum = 0;
	m_returnOther = 0;	
	m_nInvCount=0;
	m_singleInvInfo = new CInvHead();	//���ŷ�Ʊ��Ϣ��ʼ��
	InitInvHead();
	
	DBG_PRINT(("�˳�SaleData������"));
}

SaleData::~SaleData()
{
	m_deptInfo = NULL;
	
	if( m_singleInvInfo != NULL )
	{
		delete m_singleInvInfo;
		m_singleInvInfo = NULL;
	}
	
	m_smallInvInfo = NULL;	
}


//UINT8 SaleData::SearchGoodsByPLU(string PLUCode, CPlu *pluInfo)
//{
// 	DBG_ENTER("SaleData::SearchGoodsByPLU");
// 	DBG_ASSERT_EXIT((pluInfo != NULL), (" pluInfo == NULL!"));
// 	
// 	char value[256];
// 	memset((void*)value, 0, sizeof(value));
// 	string filter;
// 	INT32 errorcode;
// 	UINT8 ret = SUCCESS;
// 
// 	pluInfo->m_filter.append("WHERE CODE = '");
// 	pluInfo->m_filter.append(PLUCode);
// 	pluInfo->m_filter.append("'");
// 
// 	//��ѯ
// 	pluInfo->Requery();
// 	errorcode = pluInfo->LoadOneRecord();
// 	DBG_PRINT(("errorcode : %d ", errorcode));	
// 	if (errorcode != SQLITE_OK)
// 	{
// 		DBG_PRINT((" Warning: No matched goods!"));
// 		ret = NO_SUCH_GOODS;
// 		DBG_RETURN(ret);	
// 	}
// 
//     DBG_PRINT(("m_code : %s ", pluInfo->m_code.c_str()));
// 	DBG_PRINT(("m_name : %s ", pluInfo->m_name.c_str()));
// 	DBG_PRINT(("m_nameAbbr : %s ", pluInfo->m_nameAbbr.c_str()));
// 	DBG_PRINT(("m_dept : %d ", pluInfo->m_dept));
// 	DBG_PRINT(("m_taxId : %d ", pluInfo->m_taxId));
// 	DBG_PRINT(("m_price : %lf ", pluInfo->m_price));
// 	DBG_PRINT(("m_rate : %f ", pluInfo->m_rate));
// 	DBG_PRINT(("m_unit : %s ", pluInfo->m_unit.c_str()));
// 
// 	DBG_RETURN(ret);
//}


UINT8 SaleData::PLUSale(string strName, string &strErr)
{
	DBG_ENTER("SaleData::PLUSale");
	
	//	char value[256];
	//	memset((void*)value, 0, sizeof(value));
	//	string filter;
	//	INT32 errorcode;
	UINT8 ret = SUCCESS;
	INT32 nLen = strName.length();
	
	DBG_PRINT(("strName : %s ", strName.c_str()));
	if (nLen > GOODS_NAME_LEN) 
	{
		strErr = "��Ʒ���ƹ���";
		DBG_RETURN(FAILURE);		
	}
	else if (nLen <= 0) 
	{
		strErr = "��������Ʒ����";
		DBG_RETURN(FAILURE);		
	}
	
	//��ѯ��Ʒ��Ϣ
	CDept curDept;
	m_deptInfo = &curDept;
	
	//�����Ʒ��Ϣ
	m_deptInfo->m_spbm = "0000000000000000";		/**< ���� */
	m_deptInfo->m_spmc = strName;		/**< ���� */
	m_deptInfo->m_spjm = "";		/**< ��� */
	m_deptInfo->m_spgg = "";		/**< ��� */
	m_deptInfo->m_spdw = "��";		/**< ��λ */
	m_deptInfo->m_zspmdm = "";	/**< ������Ʒ����(˰Ŀ) */
	m_deptInfo->m_spsl = 0.0;		/**< ˰�� */
	m_deptInfo->m_spzsl = 0.0;		/**< ������ */
	m_deptInfo->m_spdj = m_tmpPrice;		/**< ���� */
	m_deptInfo->m_rate = 100.0;		/**< ��Ʒ�ۿ��� */
	m_deptInfo->m_blh = 0;       /**< ��Ӧ�Ĳ���ţ�Ĭ��Ϊ�� */
	
	DBG_PRINT(("��ʱ��Ʒ��Ϣ����:"));
    DBG_PRINT(("m_spbm : %s ", m_deptInfo->m_spbm.c_str()));
	DBG_PRINT(("m_spmc : %s ", m_deptInfo->m_spmc.c_str()));
	DBG_PRINT(("m_spsl : %f ", m_deptInfo->m_spsl));
	DBG_PRINT(("m_spjm : %s ", m_deptInfo->m_spjm.c_str()));
	DBG_PRINT(("m_spdj : %f ", m_deptInfo->m_spdj));
	
	//����Ʒ��Ϣ�޵��ۣ�������ܼ�����
	DBG_PRINT(("m_tmpSum==%d", m_tmpSum));
	if( m_deptInfo->m_spdj == 0 )
	{
		if( (m_cancel != CANCEL_PRODUCT) && (m_tmpSum == 0) )
		{
			ret = MUST_INPUT_SUM;			
			InitSaleData(0);  //������Ϣ��ʼ��
			DBG_PRINT(("�˳�DeptSale����"));
			DBG_RETURN(ret);			
		}
		//�����Ʒ����Ϊ��,��ô��Ϊ1
		if (m_tmpAmount == 0)
		{
			m_tmpAmount = 1;
		}
		DBG_PRINT(("����: %.2f", m_tmpAmount));
		// 		m_deptInfo->m_spdj = ((double)m_tmpSum)/SUM_EXTENSION;//���ܼ۸�ֵ������
		// 		DBG_PRINT(("m_spdj == %f ", m_deptInfo->m_spdj));
		m_deptInfo->m_spdj = ((double)m_tmpSum)/SUM_EXTENSION / m_tmpAmount;
		//�������
		m_tmpSum = 0;
		//		m_tmpAmount = 1.0;   //ǿ������Ϊ1
		m_saveAmount = 1.0;  //ǿ������Ϊ1
		m_dotNum = 0;
		m_tmpPrice = 0.0;    //��������ʱ������
	}
	
	//m_deptInfo = &curDept;
	//	DBG_ASSERT_EXIT((m_deptInfo != NULL), (" m_deptInfo == NULL!"));
	
	//�������������̺���
	ret = Sale(m_deptInfo);
	m_deptInfo = NULL;
	InitSaleData(0);  //������Ϣ��ʼ��
	DBG_RETURN(ret);
}

//-------------------------------------------------------------------
//����������
//-------------------------------------------------------------------
UINT8 SaleData::Sale( CDept *deptInfo )
{
	DBG_ENTER("SaleData::Sale");
	DBG_ASSERT_EXIT((m_deptInfo != NULL), (" m_deptInfo == NULL!"));
	DBG_PRINT(("����Sale����"));
	
	char value[256];
	memset((void*)value, 0, sizeof(value));
	string filter;
	INT32 errorcode;
	UINT8 ret;
	INT64 tmpDJ=0;
	
	//�����ǰ���޷�Ʊ�����˳��ú�����
	//if( 0 == g_globalArg->m_curInvVol->m_remain ) 
	if (0==g_globalArg->m_curInvVol->m_curInvNo)
	{
		InitSaleData(0);  //������Ϣ��ʼ��
		DBG_RETURN(INV_ZERO);			
	}
	
	//���ÿ�Ʊ���ͺ�ԭ��Ʊ�š�
	m_singleInvInfo->m_kplx = m_invtype;		//��Ʊ����
    m_singleInvInfo->m_yfphm = m_oldInv;		//ԭ��Ʊ��
	m_singleInvInfo->m_yfpdm = m_oldCodeNo;		//ԭ��Ʊ����
	
	//�����Ʒ���ۿ��ʲ�����100	//xsr ���ʡ�m_property��Discount�����ﱻ����ֵ��
	DBG_PRINT(("deptInfo->m_rate==%f", deptInfo->m_rate));
	if( 0==doublecmp(deptInfo->m_rate, 100.00) && (m_property != DETAIL_GOODS_DISCOUNT) )
	{
		m_property = DETAIL_GOODS_DISCOUNT;
		m_tmpRate = (INT32)(deptInfo->m_rate);
		DBG_PRINT(("m_tmpRate =  %f", m_tmpRate));
	}
	
	//�ж���ʱ��
    DBG_PRINT(("m_tmpPrice == %lf ", m_tmpPrice));
    if( m_tmpPrice >= BASE_PRICE )
	{
		deptInfo->m_spdj = m_tmpPrice;
		m_tmpPrice = 0;
	}
	
	//������Ʒȡ��
	if (m_cancel == CANCEL_PRODUCT)
	{
		double dPrice;
		DBG_PRINT(("deptInfo->m_spbm = %s", deptInfo->m_spbm.c_str()));
		
		ret = CancelGoodsByDept(deptInfo->m_spbm, m_saveAmount, dPrice); 
		
		if( NO_SUCH_GOODS == ret )
		{
			m_invDet = m_singleInvInfo->pEnd;
			InitSaleData(0);  //������Ϣ��ʼ��
			DBG_PRINT(("*******NO_SUCH_GOODS*******NO_SUCH_GOODS*******!"));
			DBG_RETURN(ret);		
		}
		m_invDet = &m_cancelDet; 
		DBG_ASSERT_EXIT((m_invDet != NULL), (" m_invDet == NULL!"));
		m_invDet->m_spmc = deptInfo->m_spmc;
		m_invDet->m_spdj = dPrice;
		m_invDet->m_dotNum = AmountRound(&m_realCancelNum); //��Ʒ������������	
		m_invDet->m_spsl = m_realCancelNum;
		DBG_PRINT(("m_realCancelNum = %f!", m_realCancelNum));
		InitSaleData(0);  //������Ϣ��ʼ��
		DBG_RETURN(ret);
	}
	
    //�ж���Ʒ����Ƿ񳬵��ſ�Ʊ�޶�
	INT64 moneySum, orgMoneySum;			//orgMoneySum���ۿ�ǰ����Ʒ�еĽ�moneySum���ۿۺ����Ʒ�еĽ�
	INT64 moneyTaxSum=0;
	DBG_PRINT(("m_tmpSum==%lf ", m_tmpSum));//m_tmpSum��DeptSale�������ó���0
	//����û��������ܼ�
	if( m_tmpSum > 0 )  
	{
		orgMoneySum = m_tmpSum;										//ԭʼ�ܽ��
		m_tmpAmount = orgMoneySum/(deptInfo->m_spdj)/SUM_EXTENSION;	//��Ʒ����
		m_saveAmount = m_tmpAmount;
		DBG_PRINT(("m_saveAmount : %f ", m_saveAmount));
		m_dotNum = AmountRound(&m_saveAmount); //��Ʒ������������
		DBG_PRINT(("m_saveAmount : %f ", m_saveAmount));
		DBG_PRINT(("m_dotNum : %d ", m_dotNum)); 
		if (m_dotNum == -1)
		{
			m_dotNum = 0;
			m_tmpAmount = 1.0;
			m_saveAmount = 1.0;
			m_tmpSum = 0;
			DBG_PRINT(("The goods amount exceeds the limit!"));
			InitSaleData(0);  //������Ϣ��ʼ��
			DBG_RETURN(EXCEED_AMOUNT);
		}
	}
	//����û�û�����ܼ�
	else
	{
		DBG_PRINT(("deptInfo->m_spdj==%lf ", deptInfo->m_spdj));
		DBG_PRINT(("m_tmpAmount==%lf ", m_tmpAmount));

		orgMoneySum = double2int(deptInfo->m_spdj * 1000.0 * m_tmpAmount * SUM_EXTENSION);//ԭʼ�ܽ��
		DBG_PRINT(("orgMoneySum == %lld", orgMoneySum));
		orgMoneySum = double2int(orgMoneySum / 1000.0);
		DBG_PRINT(("orgMoneySum == %lld", orgMoneySum));
	}
	//���ˣ�orgMoneySum������˸���Ʒ�еĽ�100Ԫ��
	
    //������ۿۡ�
    if( m_property==DETAIL_GOODS_DISCOUNT )  
	{
		moneySum = double2int(deptInfo->m_spdj * m_tmpRate/100*1000.0*m_tmpAmount*SUM_EXTENSION);//ԭʼ�ܽ��
		moneySum = double2int(moneySum / 1000.0);
		DBG_PRINT(("moneySum = %lld", moneySum));
	}
	else
	{
		moneySum = orgMoneySum;
		DBG_PRINT((" moneySum = %lld", moneySum));
	}
	//���ˣ�moneySum��������ۿۺ�ĸ���Ʒ�еĽ�80Ԫ��
	
	//���Ž�����
	if ((moneySum > g_globalArg->m_invKind->m_maxSign)||
		((m_tmpMoneySum+moneySum) > g_globalArg->m_invKind->m_maxSign)) 
	{	
		ret = NM_EXCEED;
        DBG_PRINT((" g_globalArg->m_invKind->m_maxSign = %u!", g_globalArg->m_invKind->m_maxSign));
		DBG_PRINT((" Warning: sigal invoice money exceed the limit!"));
		InitSaleData(0);  //������Ϣ��ʼ��
		DBG_RETURN(ret);	
	}
	
	//����
	DBG_PRINT(("moneySum==%lld ", moneySum));
	if (moneySum <= 0)
	{
		DBG_PRINT(("moneySum==%d��not enough!", moneySum));
		InitSaleData(0);  //������Ϣ��ʼ��
		DBG_RETURN(MONEY_NOT_ENOUGH);
	}
	//�ۿ۵��Ľ��Ϊ0
	if( (m_property==DETAIL_GOODS_DISCOUNT) && (moneySum - orgMoneySum >= 0) )
	{
		DBG_PRINT((" �ۿ۵��Ľ��moneySum - orgMoneySum = %d", moneySum - orgMoneySum));
		InitSaleData(0);  //������Ϣ��ʼ��
		DBG_RETURN(DISCOUNT_MONEY_ZERO);
	}
	
	//�ۼƽ���
	m_tmpMoneySum += moneySum; //���ŷ�Ʊ����ۼ�
	DBG_PRINT((" g_globalArg->m_normalSum = %lld!", g_globalArg->m_normalSum));
	DBG_PRINT((" g_globalArg->m_returnSum = %lld!", g_globalArg->m_returnSum));
	if (g_globalArg->m_operator->m_role != DEMO_ROLE) //��ѧϰģʽ
	{
		switch(m_singleInvInfo->m_kplx) 
		{
		case NORMAL_INV:
			//������Ʊ�ۼƽ���
			//			if ((g_globalArg->m_normalSum + m_tmpMoneySum)>g_globalArg->m_invKind->m_maxSum)
			//			{
			//				ret = NM_SUM_EXCEED;//NVM_SUM_EXCEED;
			//				m_tmpMoneySum -= moneySum;//�����ۼƽ���ȥ����Ʒ�н��
			//				DBG_PRINT((" Warning: m_normalVolSum exceed the limit!"));
			//				InitSaleData(0);  //������Ϣ��ʼ��
			//				DBG_RETURN(ret);
			//			}
			//			break;
		case RET_MANUAL_INV:   //�����ֹ���Ʊ���˻��� 
		case RET_SPECIAL_INV:  //�������ⷢƱ
		case RETURN_INV:  
			//�����Ʊ�ۼƽ���
			//			if ((g_globalArg->m_returnSum + m_tmpMoneySum)>g_globalArg->m_invKind->m_maxRetSum)
			//			{
			//				ret = RM_SUM_EXCEED;//RVM_SUM_EXCEED;
			//				m_tmpMoneySum -= moneySum;//�����ۼƽ���ȥ����Ʒ�н��
			//				DBG_PRINT((" Warning: m_returnVolSum exceed the limit!"));
			//				InitSaleData(0);  //������Ϣ��ʼ��
			//				DBG_RETURN(ret);
			//			}
			break;
		default:;
		}
	}
	
	//----�ж�˰��˰Ŀ�Ƿ�Ϸ�
	//	 UINT8 nLeagal = 0;
	//	if (g_globalArg->m_operator->m_role != DEMO_ROLE) //��ѧϰģʽ
	//	{
	// 		if (deptInfo->m_taxId ==0 )
	// 		{
	// 			ret = TAX_ID_ILLEGAL;
	// 			m_tmpMoneySum -= moneySum;//�����ۼƽ���ȥ����Ʒ�н��
	// 			InitSaleData(0);  //������Ϣ��ʼ�� 
	// 			DBG_RETURN(ret);
	// 		}
	// 		for(INT32 i=0; i<TAX_ID_NUM; i++)
	// 		{
	// 			if (pluInfo->m_taxId == g_globalArg->m_taxID[i]) 
	// 			{
	// 				nLeagal = 1;
	// 				break;
	// 			}
	// 		}
	// 		if (nLeagal==0)
	// 		{ 
	// 			ret = TAX_ID_ILLEGAL;
	// 			m_tmpMoneySum -= moneySum;//�����ۼƽ���ȥ����Ʒ�н��
	// 			DBG_PRINT((" Warning: the tax ID is illegal!"));
	// 			InitSaleData(0);  //������Ϣ��ʼ��
	// 			DBG_RETURN(ret);		
	// 		}
	//	}
	
	
    //��ӵ���Ʊ��ϸ
	m_invDet = m_invDet->GetNewInvDet();	//�Ӿ�̬�����ȡһ�����õ�CInvDet����
	DBG_ASSERT_EXIT((m_invDet != NULL), (" m_invDet == NULL!"));
	
	m_invDet->m_kplx = m_invtype;           //��Ʊ���ͣ������ϡ���Ʊ
	m_invDet->m_sky = g_globalArg->m_operator->m_name; //����Ա����
	m_invDet->m_spbm = deptInfo->m_spbm;	//��Ʒ����
	DBG_PRINT(("m_invDet->m_spbm == %s", m_invDet->m_spbm.c_str()));
	m_invDet->m_spmc = deptInfo->m_spmc;	//��Ʒ����
	m_invDet->m_spsl = m_tmpAmount;			//��Ʒ����
	m_invDet->m_dotNum = m_dotNum;			// �������������С��λ��
	m_invDet->m_spdj = deptInfo->m_spdj;	//��Ʒ����(��˰)
	m_invDet->m_spje = orgMoneySum;			//��Ʒ���(��˰)
	m_invDet->m_sl = deptInfo->m_spsl;		//��Ʒ˰��
//	m_invDet->m_spse = CountTax(((double)m_invDet->m_spje)/SUM_EXTENSION, m_invDet->m_sl); //��Ʒ˰��

	m_invDet->m_spse = CountTax(m_invDet->m_spje, (UINT32)(m_invDet->m_sl*SUM_EXTENSION)); //��Ʒ˰��

	m_invDet->m_property = m_property;		//��Ʒ������
	m_invDet->m_spdw = deptInfo->m_spdw;	//��Ʒ��λ
	
	tmpDJ = double2int(m_invDet->m_spdj*SUM_EXTENSION);
	DBG_PRINT(("tmpDJ==%lld ", tmpDJ));

	//tmpDJ -=CountTax(m_invDet->m_spdj, m_invDet->m_sl);
	tmpDJ -=CountTax(double2int(m_invDet->m_spdj*SUM_EXTENSION), (UINT32)(m_invDet->m_sl*SUM_EXTENSION));
	DBG_PRINT(("tmpDJ==%lld ", tmpDJ));

	m_invDet->m_dj= (double)(tmpDJ*1.0)/SUM_EXTENSION; //��Ʒ����(����˰)
	
	
	m_invDet->m_je= m_invDet->m_spje-m_invDet->m_spse; //��Ʒ���(����˰)
	
	m_singleInvInfo->InsertNode(m_invDet);	//����ڵ�
	m_singleInvInfo->m_sphsl++;				//��ǰ��Ʊ����Ʒ�м�1
	m_tmpGoodsNum++;						//��ǰ����Ʒ�м�1
	
	moneyTaxSum =m_invDet->m_spse;
	
	
	DBG_PRINT(("m_invDet->m_dotNum==%d ", m_invDet->m_dotNum));
	DBG_PRINT(("m_tmpGoodsNum==%u", m_tmpGoodsNum));

	DBG_PRINT(("m_invDet->m_spsl==%lf ", m_invDet->m_spsl));
	DBG_PRINT(("m_invDet->m_spse==%lld ", m_invDet->m_spse));
	DBG_PRINT(("m_invDet->m_spje==%lld ", m_invDet->m_spje));
    DBG_PRINT(("m_invDet->m_je==%lld ", m_invDet->m_je));
	DBG_PRINT(("m_invDet->m_spdj==%lf ", m_invDet->m_spdj));
    DBG_PRINT(("m_invDet->m_dj==%lf ", m_invDet->m_dj));
 
	DBG_PRINT(("m_property==%d", m_property));
    DBG_PRINT(("*******m_invDet->m_spdw = %s m_spdw : %s ", m_invDet->m_spdw.c_str(), m_deptInfo->m_spdw.c_str()));
	
	//�����ۿ�
	INT64 nRebateSum;
	CInvDet *rebateDet;
    if(m_property==DETAIL_GOODS_DISCOUNT)
	{
		rebateDet = rebateDet->GetNewInvDet();//�Ӿ�̬�����ȡһ�����õ�CInvDet����
		DBG_ASSERT_EXIT((rebateDet != NULL), (" rebateDet == NULL!"));
		
		nRebateSum = moneySum - orgMoneySum;//�۵��Ľ��
		rebateDet->m_kplx = m_invtype;
		
		rebateDet->m_spbm = deptInfo->m_spbm;
		rebateDet->m_spmc = "�ۿ�";
		rebateDet->m_spsl= m_tmpAmount;//����ԭʼֵ
		m_invDet->m_dotNum = m_dotNum;
		rebateDet->m_spdj = m_tmpRate;
		rebateDet->m_spdw = deptInfo->m_spdw;	//��Ʒ��λ
		
		rebateDet->m_spje = nRebateSum;
		rebateDet->m_spse =CountTax(rebateDet->m_spje,(UINT32)(deptInfo->m_spsl*SUM_EXTENSION));
		rebateDet->m_property = DETAIL_DISCOUNT;
		
		m_singleInvInfo->InsertNode(rebateDet);	//����ڵ�
		rebateDet = NULL;
		m_singleInvInfo->m_sphsl++;		//��ǰ��Ʊ����Ʒ�м�1
		m_tmpGoodsNum++;				////��ǰ����Ʒ�м�1
	}
	
	
    //�ж�ʣ�෢Ʊ�����Ƿ��� 
	
	//��Ʊʣ��ݶ��(�����ۿۣ���ɾ�������ڵ�)
	UINT32 nInvCount = CalculateInvNum();   //��Ʒ�����跢Ʊ��
	DBG_PRINT(("nInvCount==%d", nInvCount));
	
	m_nInvCount= nInvCount;
	DBG_PRINT(("m_nInvCount==%d", m_nInvCount));


	UINT32 nIfReturn = 0; //�Ƿ�ȡ������Ʒ�У�ֹͣ��Ʊ
	DBG_PRINT((" g_globalArg->m_curInvVol->m_remain = %u !", g_globalArg->m_curInvVol->m_remain));
	
	if( nInvCount > g_globalArg->m_curInvVol->m_remain )
	{
		nIfReturn = 1;
			ret = SHORT_OF_INV; 
		DBG_PRINT((" g_globalArg->m_curInvVol->m_remain = %u !", g_globalArg->m_curInvVol->m_remain));
	}
	if ((nInvCount>1)&&(m_singleInvInfo->m_kplx==RETURN_INV)) 
	{
		nIfReturn = 1;
		ret = RETURN_GOODS_EXCEED;
	}
	if( 1==nIfReturn )
	{
		m_singleInvInfo->m_sphsl--;			//��ǰ��Ʊ����Ʒ�м�1
		m_tmpGoodsNum--; ////��ǰ����Ʒ�м�1
		m_singleInvInfo->DelLastNode();		//ɾ���ռ���Ľڵ�
		if (m_property==DETAIL_GOODS_DISCOUNT) 
		{
			m_singleInvInfo->m_sphsl--;		//��ǰ��Ʊ����Ʒ�м�1
			m_tmpGoodsNum--; ////��ǰ����Ʒ�м�1
			m_singleInvInfo->DelLastNode();	//ɾ���ռ���Ľڵ�
		}
		m_tmpMoneySum -= moneySum;			//�����ۼƽ���ȥ����Ʒ�н��
		InitSaleData(0);					//������Ϣ��ʼ��
		DBG_RETURN(ret);
	}
	
    //�ͷſռ�,����
	//��ǰ��Ʊ�ۼƽ������
	m_singleInvInfo->m_kphjje += moneySum;
	DBG_PRINT((" m_singleInvInfo->m_kphjje = %u !", m_singleInvInfo->m_kphjje));
	
	
	//��ǰ��Ʊ�ۼ�˰������
	m_singleInvInfo->m_kpse += moneyTaxSum;
	DBG_PRINT((" m_singleInvInfo->m_kphjse = %u !", m_singleInvInfo->m_kpse));
    moneyTaxSum=0;
	
	InitSaleData(0);  //������Ϣ��ʼ��
	
    ret = SUCCEED;
	DBG_PRINT(("�˳�Sale�������ɹ���"));
	DBG_RETURN(ret);
	
}

//-------------------------------------------------
//��ʼ����Ʊͷ�еĳ�Ա����
//-------------------------------------------------
UINT8 SaleData::InitInvHead()
{
	DBG_PRINT(("����InitInvHead����"));
	m_singleInvInfo->m_fpdm = g_globalArg->m_curInvVol->m_code;	//��Ʊ����
	//	m_singleInvInfo->m_fphm = g_globalArg->m_curInvVol->m_ieno + 1 - g_globalArg->m_curInvVol->m_remain;
	m_singleInvInfo->m_fphm = g_globalArg->m_curInvVol->m_curInvNo;		/**< ��Ʊ���� */
	
	
	m_singleInvInfo->m_kplx = NORMAL_INV;		//��Ʊ����
	
	m_singleInvInfo->m_kphjje = 0;				//��Ʊ�ϼƽ��
	m_singleInvInfo->m_yfpdm = "";				//ԭ��Ʊ����
	
	m_singleInvInfo->m_fkdw = g_globalArg->m_defaultPayerName;  //���λ
	m_singleInvInfo->m_fkdwsh = "";        //���λ˰��ʶ���
	m_singleInvInfo->m_sky = g_globalArg->m_operator->m_name;	//�տ�Ա
	m_singleInvInfo->m_skr = g_globalArg->m_operator->m_name;
	//	m_singleInvInfo->m_skyid = g_globalArg->m_operator->m_opid;	//�տ�ԱID
	
	m_singleInvInfo->m_sphsl = 0;			//��Ʒ��ϸ����
	
	m_singleInvInfo->m_bzkz = "";
	m_singleInvInfo->m_backup1 = "";		//�����ֶ�1
	//	m_singleInvInfo->m_backup2 = "";		//�����ֶ�2
	//	m_singleInvInfo->m_backup3 = "";		//�����ֶ�3
	
	m_singleInvInfo->m_scbz = 0;
	
    m_singleInvInfo->DelList();				//�ͷ�����ռ�
	
	DBG_PRINT(("�˳�InitInvHead����"));
	return SUCCESS;
}

UINT8 SaleData::InitSaleData(UINT8 set)
{	
	m_reductFlag = 0;							//�ӳɱ�־		
	m_serviceFeeFlag = 0;						//����ѱ�־	
	
	m_tmpPrice = 0.0;							//��ʱ�۸�		
	m_tmpSum = 0;								//��ʱ���			
	m_tmpAmount = 1.0;							//��ʱ��Ʒ����	
	m_tmpDept = 0;								//��ʱ����		
	m_tmpRate = 0.0;							//��ʱ�ٷ���
	m_tmpClient = "";                           //��ʱ������
	
	m_saleMode = g_globalArg->m_saleMode;	    //����ģʽ���ܼۡ���ʱ�ۣ�����	
	m_maxAllowCount = 6;					    //ÿ�ŷ�Ʊ���������Ʒ������	
	m_detailCount = 0;							//��Ʒ�������������ŷ�Ʊ��														
	m_goodsSum = 0;								//��Ʒ���ۼƽ��			         
	
	m_property = DETAIL_GENERAL_GOODS;          //��Ʒ�Ƿ����ۿۣ��ӳɵ� 
    m_cancel = 0;                               //�Ƿ�ȡ����Ʒ
	m_realCancelNum = 0;
	
	m_dotNum = 0;                               //���������������С��λ��
	m_saveAmount = 1.0;                         //������������Ʒ����
	
	if (set == 1) 
	{
		m_tmpMoneySum = 0;                      //����Ʊ���ۼƽ��
		m_invtype = NORMAL_INV;                 //��Ʊ���ͣ������ϡ���Ʊ
		m_oldInv = 0;                           //��Ʊ�ķ�Ʊ��
		m_oldCodeNo = "";						//��Ʊ�ķ�Ʊ����
	}
	return SUCCESS;
}

//-----------------------------------------------------
//�ֽ����
//-----------------------------------------------------
UINT8 SaleData::PayByCash( UINT8 &IfInvSum )
{
	DBG_PRINT(("����PayByCash����"));
	DBG_ENTER("SaleData::PayByCash");
	UINT8 ret;
	string strErr;
	IfInvSum = 0;

	//������Ʒ 
	if( m_singleInvInfo->m_sphsl == 0 )
	{
		ret = NO_GOODS;
		m_workState = WORK_COMPLETE;
		DBG_PRINT(("ret= %u",ret));
		DBG_RETURN(ret);
	}
	
	//�ж�װ��ֽ�ʷ�Ʊ	
	if( isPaper() != 0 )
	{		
		ret = NO_PAPER;
		DBG_PRINT(("ret= %u",ret));
		DBG_RETURN(ret);
	}

	//��Ʊ������
	//	if (m_singleInvInfo->m_kphjje < g_globalArg->m_invKind->m_minSum) 
	//	{	
	//		ret = NM_EXCEED_MIN;
	//		DBG_PRINT((" g_globalArg->m_invKind->m_minSum = %u!", g_globalArg->m_invKind->m_minSum));
	//		DBG_PRINT((" m_singleInvInfo->m_kphjje = %ld!", m_singleInvInfo->m_kphjje));
	//		DBG_PRINT((" Warning: sigal invoice money exceed the min limit!"));
	//		DBG_RETURN(ret);	
	//	}
	
	
	//��ַ�Ʊ����ӡ
	CInvHead smallInvHead;//�洢��ֳ��ķ�Ʊ����
	m_smallInvInfo = &smallInvHead; 
	DBG_ASSERT_EXIT((m_smallInvInfo != NULL), (" m_smallInvInfo == NULL!"));
	
    m_detailCount = m_singleInvInfo->m_sphsl;  //���۵���Ʒ������
	DBG_PRINT(("m_detailCount == %d", m_detailCount));
    m_pHead = m_singleInvInfo->pHead;
	
	g_YW_PowerOffData->ProcData.fptk_data.RemainLineCount = 0;
	DBG_PRINT(("*****����ģʽ******��%u", g_globalArg->pSaveTemplateInfo->workMode));
	while( !ScanGoodsLine(1) )
	{
		DBG_PRINT((" After ScanGoodsLine, begin printing the invoice"));
		
		//��װ��ӡ�ķ�Ʊͷ����ϸ
		ComposePrnInv();
		DBG_PRINT(("*****����ģʽ******��%u", g_globalArg->pSaveTemplateInfo->workMode));
		
		DBG_PRINT(("���ÿ�Ʊ���"));
		if( (ret = MakeInvoiceHandle(1, INV_ROLL_PROC)) != SUCCESS )

		{
			m_tmpGoodsNum = 0;			//��ǰ����Ʒ��������
			InitSaleData(1);			//������Ϣ��ʼ��
			InitInvHead();				//���ŷ�Ʊ��Ϣ��ʼ�����ͷ�ʣ�෢Ʊ����Ʒ�нڵ�
			m_smallInvInfo->DelList();  //�ͷű��ŷ�Ʊ����Ʒ�нڵ�
			DBG_PRINT(("m_smallInvInfo->DelList() ���"));
			m_workState = WORK_COMPLETE;
			m_smallInvInfo = NULL;
			DBG_RETURN(ret);			//��ʵ���ش�������			
		}
		
		m_smallInvInfo->DelList();  //�ͷ��Ѵ�ӡ����Ʒ�нڵ�
		
	}
	
	//������ر�����λ
    m_tmpGoodsNum = 0;  //��ǰ����Ʒ��������
	InitSaleData(1);	//������Ϣ��ʼ��
	InitInvHead();		//���ŷ�Ʊ��Ϣ��ʼ��
	m_workState = WORK_COMPLETE;
	
	//�жϣ��������Զ�����
	//if(g_globalArg->m_curInvVol->m_remain == 0)
	if (0==g_globalArg->m_curInvVol->m_curInvNo)
	{
		if (g_globalArg->m_operator->m_role==DEMO_ROLE)
		{
			m_smallInvInfo = NULL;
			DBG_PRINT((" g_globalArg->m_curInvVol->m_remain = 0!"));
			DBG_RETURN(MUST_RE_LOGIN);
		}
		else
		{
			// 			POWOFF_DISABLE(); //���ε����ж�
			//  			if(!InvSum(IfInvSum))
			// 			{
			// 				m_smallInvInfo = NULL;
			// 				DBG_PRINT(("Get volume Sum error !"));
			// 				POWOFF_ENABLE(); //�������ж�
			// 				DBG_RETURN(INV_SUM_ERROR);
			// 			}
			// 			POWOFF_ENABLE(); //�������ж�
		}
		
	}
	
	m_smallInvInfo = NULL;
	ret = SUCCEED;
	
	DBG_PRINT(("�˳�PayByCash�������ɹ���"));
	DBG_RETURN(ret);	
}


UINT8 SaleData::MakeInvoiceHandle(UINT8 nIfPrn, UINT8 nId)
{
	DBG_ENTER("SaleData::MakeInvoiceHandle");
	UINT32  errorcode;
	UINT32 preInvNo = 0;
	UINT8  nGetFiscalCode;
	UINT8  nIfRolled = 0;
	UINT8  errCodeJSK=0;
	
	UINT8 ret, TransRet;
	UINT32 nLIndex = 0;//����ʧ�ܼ���������
	UINT32 nLmt = 3;	//���Դ���
	UINT8 nLinkFlag = 0;//������ͨ��־ 0����ͨ��1����ͨ
	string strErr("");
	
	
	//	IssuedInvoice issuedInvoiceData;       /**< ִ�п�Ʊ����͵����ݽṹ*/
	
	switch(nId)
	{
	case INV_ROLL_PROC:
		
		if( g_globalArg->m_operator->m_role != DEMO_ROLE ) //����ѧϰ��ɫ
		{
			POWOFF_DISABLE();					//���ε����ж�
			SetPowerOffFlag();
			SetPowerOffProcID_M(INV_ROLL_PROC);	//��������ID		
			errorcode = RollData(nIfRolled);	//�ں�POWOFF_ENABLE();
			if(errorcode!= SUCCESS)
			{
				DBG_PRINT((" Roll() error !"));
				CleanPowerOffFlag();
				POWOFF_ENABLE();
				DBG_RETURN(errorcode);	
			}
			CleanPowerOffFlag();
			DBG_PRINT(("��������"));
			
			//����������ʱ��������Ҫ�˳���Ʊ�����Ա�˶Թ�������
			if( (1==AUTOISSUE) && (1==nIfRolled) )
			{
				DBG_PRINT((" Roll(): have rolled successfully!"));
				DBG_RETURN(HAVE_ROLLED); //�����������˳�����					
			}
		}
		
#ifndef WIN32
#if POWEROF_SPEED_TEST
		fTime = tp.time * 1000 + tp.millitm;
		DBG_PRINT(("1 ����˰���룬��ʼ, Time = %llu ", fTime));
#endif
#endif
		
		//����˰����
		case WRITE_ICCARD:
			if (g_globalArg->m_operator->m_role!=DEMO_ROLE) //����ѧϰ��ɫ
			{
				POWOFF_DISABLE(); //���ε����ж�
				// 				SetPowerOffFlag();
				// 				SetPowerOffProcID_M(FPTK_NORMAL_PROC);//��������ID
				// 				SetPowerOffProcID_C(WRITE_INV); //���ӹ���ID
				DBG_PRINT(("������籣��"));
				//				DBG_PRINT((" m_smallInvInfo->pHead = %x!", m_smallInvInfo->pHead));
				//				m_issuedInvoiceData = &issuedInvoiceData;
				//				if(m_issuedInvoiceData==NULL)
				//				{
				//					DBG_PRINT((" malloc(sizeof(IssuedInvoice) error !"));
				//					//					CleanPowerOffFlag();
				//					POWOFF_ENABLE();
				//					DBG_RETURN(MALLOC_MEM_ERROR);		
				//				}
				
				
				// 				DBG_PRINT((" m_smallInvInfo->pHead = %x!", m_smallInvInfo->pHead));
				//				if (ComposeIssuedInvData(m_smallInvInfo, m_issuedInvoiceData) == FAILURE)
				//				{
				//					m_workState = WORK_COMPLETE;
				//					//					CleanPowerOffFlag();
				//					POWOFF_ENABLE();
				//					DBG_RETURN(GET_FISCAL_CODE_ERROR);
				//				}				
				DBG_PRINT((" m_smallInvInfo->pHead = %x!", m_smallInvInfo->pHead));	
				
				//����ѧϰ��ɫ
				if( g_globalArg->m_operator->m_role != DEMO_ROLE ) 
				{
					//���������ߣ��ж��Ƿ�����3������ 

					ret = IsOffLineOk(m_smallInvInfo->m_kphjje, strErr);
					if (SUCCESS != ret) 
					{
						return ret;
					}										
				}
				
				DBG_PRINT(("m_smallInvInfo->m_kplx= %u",m_smallInvInfo->m_kplx));
				BAR_DEF();
				BAR_SHOW("��ȡ˰������Ϣ��...");
				
				if ("" == m_smallInvInfo->m_fkdwsh)
				{
				    m_smallInvInfo->m_fkdwsh=PAYER_NAME_DEF;
				}
				
				DBG_PRINT(("m_smallInvInfo->m_fkdwsh= %s",m_smallInvInfo->m_fkdwsh.c_str()));
				m_smallInvInfo->m_zskl =  g_globalArg->m_strZskl;
				DBG_PRINT(("m_smallInvInfo->m_zskl= %s",m_smallInvInfo->m_zskl.c_str()));

					errCodeJSK=SALE_MakeInvHand(m_smallInvInfo,g_globalArg->m_strMsg);					
					DBG_PRINT(("m_smallInvInfo->m_kprq= %u",m_smallInvInfo->m_kprq));
					DBG_PRINT(("m_smallInvInfo->m_kpsj= %u",m_smallInvInfo->m_kpsj));
					if (SUCCESS != errCodeJSK)
					{
					DBG_RETURN(INV_LIB_ERR);
					}

				
				//	m_issuedInvoiceData=NULL;
				DBG_PRINT((" m_smallInvInfo->pHead = 0x%x!", m_smallInvInfo->pHead));
				//	InvClassToStuct(&(g_YW_PowerOffData->ProcData.fptk_data.posInvInfo), m_smallInvInfo);
				POWOFF_ENABLE();//�������ж�
				
			}
			
			
#ifndef WIN32
#if POWEROF_SPEED_TEST
			ftime(&tp);
			fTime2 = tp.time * 1000 + tp.millitm;
			DBG_PRINT((" ********fiscal code, Time = %llu ", (fTime2 - fTime)));
#endif
#endif
			
			//-----------------------------------------------------------------------------
			//д���ݿ�
			//-----------------------------------------------------------------------------
		case WRITE_INV:
			
			//����ѧϰ��ɫ
			if( g_globalArg->m_operator->m_role != DEMO_ROLE ) 
			{
				POWOFF_DISABLE();				//���ε����ж�
				DBG_PRINT(("��䷢Ʊ��ӡ�ṹ�壬д���ݿ�"));
				SetPowerOffProcID_C(PRINT_INV); //���ӹ���ID
			}
			
			DBG_PRINT(("��Ʊ������1"));
			g_globalArg->m_curInvVol->m_curInvNo = 0;//��ǰƱ�Ÿ�λ
			if (g_globalArg->m_operator->m_role==DEMO_ROLE) 
			{
				g_globalArg->m_curInvVol->m_remain--;  //��Ʊ������1
				DBG_PRINT(("g_globalArg->m_curInvVol->m_remain == %d", g_globalArg->m_curInvVol->m_remain));
			}
			
			//����ѧϰ��ɫ
			if (g_globalArg->m_operator->m_role != DEMO_ROLE) 
			{
				
				// #ifndef WIN32
				// #if POWEROF_SPEED_TEST
				// 				ftime(&tp);
				// 				fTime = tp.time * 1000 + tp.millitm;
				// #endif
				// #endif				
				// 
				// 				//д���ݿ⣬����INV_VOL��
				// 			//	DBG_PRINT(("g_globalArg->m_curInvVol->m_remain == %d", g_globalArg->m_curInvVol->m_remain));
				// 				if( UpdateVolRemain(g_globalArg->m_curInvVol->m_remain)== FAILURE)
				// 				{
				// 					DBG_PRINT((" UpdateVolRemain() error!"));
				// 				//	CleanPowerOffFlag();
				// 					POWOFF_ENABLE();
				// 					DBG_RETURN(UPDATE_INV_VOL_ERROR);			
				// 				}
				// 
				// #ifndef WIN32
				// #if POWEROF_SPEED_TEST
				// 				ftime(&tp);
				// 				fTime2 = tp.time * 1000 + tp.millitm;
				// 				DBG_PRINT((" ******INV_VOL, Time = %llu ", (fTime2 - fTime)));
				// #endif
				// #endif
				
				//	DBG_PRINT((" m_smallInvInfo->pHead = %x!", m_smallInvInfo->pHead));
				
				//����INV_HEAD��INV_DET��
				errorcode = m_smallInvInfo->Save();
//				errorcode=SUCCESS;
				if (errorcode != SUCCESS)
				{
					DBG_PRINT(("m_smallInvInfo->Save() wrong"));
					//	CleanPowerOffFlag();
					POWOFF_ENABLE();
					DBG_RETURN(DB_SAVE_ERROR);
				}
				(g_globalArg->m_invCount)++; //��¼��������
				DBG_PRINT((" save SUCCESS"));
				
				
#ifndef WIN32
#if POWEROF_SPEED_TEST
				ftime(&tp);
				fTime = tp.time * 1000 + tp.millitm;
				DBG_PRINT((" *****INV_HEAD��INV_DET, Time = %llu ", (fTime-fTime2)));
#endif
#endif
				
				//����RT_INV��
				if(( m_smallInvInfo->m_kplx == RETURN_INV )||(m_singleInvInfo->m_kplx==RET_MANUAL_INV)) 
				{
					DBG_PRINT(("����RT_INV��"));
					CRtInv curRtInv;
					CRtInv *pRtInv = &curRtInv;
					if( m_oldCodeNo != "" )
					{
						pRtInv-> m_fpdm = m_oldCodeNo;			//�û�����ĺ�Ʊ����
						m_oldCodeNo = "";
					}
					else
					{
						pRtInv-> m_fpdm = m_smallInvInfo->m_fpdm;					
					}
					pRtInv-> m_fphm = m_smallInvInfo->m_yfphm;
					errorcode = pRtInv->AddNew();				//д���˷�Ʊ��Ϣ��
					if( errorcode != SQLITE_OK )
					{
						DBG_PRINT((" pRtInv->AddNew() error!"));
						//		CleanPowerOffFlag();
						POWOFF_ENABLE();
						DBG_RETURN(DB_SAVE_ERROR);
					}
					(g_globalArg->m_rtInvCount)++; //��¼��������
				}
				
				POWOFF_ENABLE();//�������ж�
			}
			
#ifndef WIN32
#if POWEROF_SPEED_TEST
			ftime(&tp);
			fTime2 = tp.time * 1000 + tp.millitm;
			DBG_PRINT((" ****RT_INV, Time = %llu ", (fTime2- fTime)));
#endif
#endif
			
			//------------------------------------------------------------
			//��䷢Ʊ��ӡ�ṹ�壬��ӡ
			//------------------------------------------------------------
		case PRINT_INV:  		
			DBG_PRINT(("��䷢Ʊ��ӡ�ṹ�壬��ӡ"));
			if( nIfPrn == 1 )
			{
				//���ٴ�ӡ���ݽṹ����ڴ�
				m_pInvPrnData = &g_invPrnData;
				if(m_pInvPrnData==NULL)
				{
					DBG_PRINT((" malloc(sizeof(TPrnInvoiceInfo) error !"));
					//	POWOFF_DISABLE(); //���ε����ж�
					//	CleanPowerOffFlag();
					//	POWOFF_ENABLE();
					DBG_RETURN(MALLOC_MEM_ERROR);		
				}
				//	DBG_PRINT(("*****����ģʽ******��%u", g_globalArg->pSaveTemplateInfo->workMode));
				memset((void *)m_pInvPrnData, 0, sizeof(TPrnInvoiceInfo));//��ӡ�ṹ����������
				
				FillPrnInvHead(m_pInvPrnData, m_smallInvInfo);		
				FillPrnInvDetail(m_pInvPrnData, m_smallInvInfo);	
				FillPrnInvTail(m_pInvPrnData, m_smallInvInfo);
				
				
#ifndef WIN32
#if POWEROF_SPEED_TEST
				ftime(&tp);
				fTime2 = tp.time * 1000 + tp.millitm;
				DBG_PRINT((" ******* fill, Time = %llu ", (fTime2- fTime)));
#endif
#endif
				BAR_DEF();
				BAR_SHOW("��Ʊ��Ϣ��ӡ��.....");
				
				//�����棬��ӡ       	
				print_invoice_head(m_pInvPrnData);
				print_invoice_data_cycle(m_pInvPrnData, 0);						
				print_invoice_tail(m_pInvPrnData);
				m_pInvPrnData = NULL;
			}
			
		default:
			break;
			
	}
	
#ifndef WIN32
#if POWEROF_SPEED_TEST
	ftime(&tp);
	fTime = tp.time * 1000 + tp.millitm;
	DBG_PRINT((" ******print, Time = %llu ", (fTime-fTime2)));
#endif
#endif		
	
	if (g_globalArg->m_operator->m_role!=DEMO_ROLE) //����ѧϰ��ɫ
	{
		POWOFF_DISABLE(); //���ε����ж�
		MakeInvLog(m_smallInvInfo->m_kplx, SUCCESS);//дϵͳ��־
		//	CleanPowerOffFlag();
		POWOFF_ENABLE();
	}
	
	DBG_PRINT(("m_nInvCount= %u",m_nInvCount));
	if (m_nInvCount >1)
	{
		ret = SALE_GetCurInv(g_globalArg->m_curInvVol,g_globalArg->m_strMsg);
		DBG_PRINT(("ret= %u",ret))
		if (ret ==FAILURE)
		{
			g_globalArg->m_curInvVol->ResetVol();
			DBG_PRINT((",g_globalArg->m_strMsg= %s",g_globalArg->m_strMsg.c_str()));
		} 	
	}
	
	DBG_PRINT(("�˳�MakeInvoiceHandle����"));
	DBG_RETURN(SUCCESS);	
}

//�Ƚ������������Ƿ����
UINT8 SaleData::doublecmp(double d1, double d2)
{
    if((d1>=d2-MINIMUM_PRECISION)&&(d1<=d2+MINIMUM_PRECISION))
	{
		return 1;
	}
	return 0;
}

//------------------------------------------------------------------
//�������ܣ�ɨ����Ʒ��
//------------------------------------------------------------------
UINT8 SaleData::ScanGoodsLine(UINT8 flagMakeInv)
{
	DBG_PRINT(("����ScanGoodsLine����"));
	DBG_ENTER("SaleData::ScanGoodsLine");
	
	INT64  invSum = 0;
	INT64  invTaxSum=0;
	UINT32 namelength = 0;	
	UINT32 tempdetailCount = 0;	//ͳ�Ʊ��Ŵ�ӡ��Ʊ����ϸ�С�xsr��������¼�Ѿ�ʹ���˵�ǰ���ŷ�Ʊ�еļ���
	UINT32 GoodLineNum = 0;		//���Ŵ�ӡ��Ʊ����Ʒ�У������еĽڵ���
	
	DBG_PRINT(("��ʱ��m_detailCount == %u",m_detailCount));
	DBG_PRINT(("��ʱ��flagMakeInv == %u",flagMakeInv));
	DBG_PRINT(("m_pHead = 0x%x",m_pHead));
    
	if( flagMakeInv==1 )
	{
		GoodLineNum = 0;
		m_smallInvInfo->pHead = m_pHead;
	}
	
	CInvDet *p = m_pHead;
	
	//
	while( GoodLineNum < m_detailCount )
	{
		DBG_ASSERT_EXIT((p != NULL), (" ��Ʊ��ϸ����ͷָ�� m_pHead == NULL!"));
		namelength = p->m_spmc.length();
		
		//���Ŵ�ӡ��Ʊ�޿�����
		if (tempdetailCount >= g_globalArg->pSaveTemplateInfo->MaxGoodsCount)	//xsr ��ʱע��
			//if (tempdetailCount >= 6)
		{			
			m_detailCount -= GoodLineNum;			//�޸���Ʒ����			
			m_pHead = p;							//ͷָ��ָ���´δ�ӡ����ʼ�ڵ�
			
			if (flagMakeInv == 1)
			{
				m_singleInvInfo->pHead = m_pHead;		//m_singleInvInfo���������ʣ����ϸ�ڵ�
				m_smallInvInfo->m_kphjje = invSum;
				m_smallInvInfo->m_kpse =invTaxSum;
				m_smallInvInfo->m_sphsl = GoodLineNum;	//����ӡ�ĵ��ŷ�Ʊ��Ʒ����Ŀ��ֵ 
			}
			DBG_RETURN(FAILURE);
		}
		//���Ŵ�ӡ��Ʊ��ʣһ������
		else if (tempdetailCount == g_globalArg->pSaveTemplateInfo->MaxGoodsCount - 1)
		{
			//DBG_PRINT(("���ŷ�Ʊ��ʣһ������"));
			//�����ʱ��Ҫ���У���Ʒ�д����ۿۣ�
			//                  ��Ʒ�в������ۿۣ���Ʒ�г���
			if ((p->m_property==DETAIL_GOODS_DISCOUNT)||(p->m_property==DETAIL_GOODS_REDUCT)
				|| ((p->m_property!=DETAIL_GOODS_DISCOUNT) && (namelength > g_globalArg->pSaveTemplateInfo->MaxSPMCCharacter))
				|| ((p->m_property!=DETAIL_GOODS_REDUCT) && (namelength > g_globalArg->pSaveTemplateInfo->MaxSPMCCharacter)))
			{
				//�޸���Ʒ����
				m_detailCount -= GoodLineNum;
				//ͷָ��ָ���´δ�ӡ����ʼ�ڵ�
				m_pHead = p;				
				
				if (flagMakeInv == 1)
				{
					m_singleInvInfo->pHead = m_pHead;//m_singleInvInfo���������ʣ����ϸ�ڵ�
					m_smallInvInfo->m_kphjje = invSum;
					m_smallInvInfo->m_kpse =invTaxSum;
					m_smallInvInfo->m_sphsl = GoodLineNum; 
				}				
				DBG_RETURN(FAILURE);
			}
		}
		//���Ŵ�ӡ��Ʊ��ʣ��������
		else if (tempdetailCount == g_globalArg->pSaveTemplateInfo->MaxGoodsCount - 2)
		{
			//��Ʒ�г����������ۿ�
			//DBG_PRINT(("���ŷ�Ʊ��ʣ��������"));
			if (((p->m_property==DETAIL_GOODS_DISCOUNT) && (namelength > g_globalArg->pSaveTemplateInfo->MaxSPMCCharacter))
				||((p->m_property==DETAIL_GOODS_REDUCT) && (namelength > g_globalArg->pSaveTemplateInfo->MaxSPMCCharacter)))
			{
				
				//�޸���Ʒ����
				m_detailCount -= GoodLineNum;
				//ͷָ��ָ���´δ�ӡ����ʼ�ڵ�
				m_pHead = p;
				
				if (flagMakeInv == 1)
				{
					m_singleInvInfo->pHead = m_pHead;//m_singleInvInfo���������ʣ����ϸ�ڵ�
					m_smallInvInfo->m_kphjje = invSum;
					m_smallInvInfo->m_kpse =invTaxSum;
					m_smallInvInfo->m_sphsl = GoodLineNum; 
				}					
				DBG_RETURN(FAILURE);
			}
		}
		
		//���ڷ��ۿ��У�������жϵ��Ž���Ƿ���
		INT64 realSum = 0;
		INT64 realTaxSum=0;
		CInvDet *s = NULL;
		
		//����Ȳ����ۿ���Ҳ����������
		if ((p->m_property != DETAIL_DISCOUNT)&&(p->m_property != DETAIL_REDUCTION_TEMPLATE))
		{
			realSum = p->m_spje ;
			realTaxSum =p->m_spse;
			
			if(p->m_property == DETAIL_GOODS_DISCOUNT) //���ۿ�
			{
				s = p->pNext;
				DBG_PRINT(("�ۿ���Ϊ%u",s->m_spdj));
				realSum = p->m_spje + s->m_spje; //�ۿ۽��
				DBG_PRINT(("�ۺ���Ϊ%d",realSum));
				
				realTaxSum = p->m_spse + s->m_spse; //�ۿۺ�˰��
				DBG_PRINT(("���ú�˰��Ϊ%d",realTaxSum));
			}
			else if(p->m_property == DETAIL_GOODS_REDUCT) //������
			{
				s = p->pNext;
				realSum = p->m_spje + s->m_spje; //���ú���
				DBG_PRINT(("���ú���Ϊ%d",realSum));
				
				realTaxSum = p->m_spse + s->m_spse; //���ú�˰��
				DBG_PRINT(("���ú�˰��Ϊ%d",realTaxSum));
			}
			
			//����������޶�
			if ( (invSum+realSum) > g_globalArg->m_invKind->m_maxSign)
			{
				DBG_PRINT(("��ʱ��Ʒ���ۼӽ��=====%d",invSum));
				DBG_PRINT(("����Ʒ�н��=====%d",realSum));
				DBG_PRINT(("g_globalArg->m_invKind->m_maxSign=%u",g_globalArg->m_invKind->m_maxSign));
				
				m_detailCount -= GoodLineNum;
				//ͷָ��ָ���´δ�ӡ����ʼ�ڵ�
				m_pHead = p;
				
				//�޸���Ʒ����
				if (flagMakeInv == 1)
				{
					m_singleInvInfo->pHead = m_pHead;//m_singleInvInfo���������ʣ����ϸ�ڵ�
					m_smallInvInfo->m_kphjje = invSum;
					m_smallInvInfo->m_kpse =invTaxSum;
					m_smallInvInfo->m_sphsl = GoodLineNum; 
				}
				DBG_RETURN(FAILURE);
			}
		}
		
		
		//�ýڵ�ɼ��뱾�ŷ�Ʊ
		tempdetailCount++;
		invSum += realSum;	
		invTaxSum += realTaxSum;
		//��Ʒ�����Ƴ���,��Ŀ��1
		if (namelength > g_globalArg->pSaveTemplateInfo->MaxSPMCCharacter)
		{
			tempdetailCount++;
		}
		
		//���Ŵ�ӡ��Ʊ��Ʒ�м�1
		GoodLineNum++;
		p = p->pNext;
		continue;
	}
	
	DBG_PRINT(("invSum == %u", invSum));
	//���
	if( invSum > 0 )
	{		
		m_detailCount -= GoodLineNum;		//�޸�����Ʒ����		
		m_pHead = p;						//ͷָ��ָ���´δ�ӡ����ʼ�ڵ�
		
		if( flagMakeInv == 1 )
		{
			m_singleInvInfo->pHead = m_pHead;			//m_singleInvInfo���������ʣ����ϸ�ڵ�
			m_smallInvInfo->m_sphsl = GoodLineNum;		//��Ʒ������
            m_smallInvInfo->m_kphjje = invSum;			//��Ʊ��˰�ϼƽ��
			m_smallInvInfo->m_kpse = invTaxSum;			//��Ʊ�ϼ�˰����
			m_singleInvInfo->pHead = NULL;				//m_singleInvInfo��Ʒ�нڵ�ȫ������
			m_singleInvInfo->pEnd = NULL; 
			m_pHead = NULL;
			DBG_PRINT(("m_smallInvInfo->m_sphsl = %u",m_smallInvInfo->m_sphsl));
			DBG_PRINT(("SaleData->m_detailCount = %u",m_detailCount));
		}
		DBG_RETURN(FAILURE);
	}
	
	DBG_PRINT(("�˳�ScanGoodsLine����"));
    DBG_RETURN(SUCCESS);
}

//-------------------------------------------------------
//��װ��ӡ�ķ�Ʊͷ����ϸ
//xsr �޸Ĺ�
//-------------------------------------------------------
UINT8 SaleData::ComposePrnInv()
{
	DBG_PRINT(("����ComposePrnInv����"));
	DBG_ENTER("SaleData::ComposePrnInv");
	INT8 value[128];
	memset((void*)value, 0, sizeof(value));
	
	m_smallInvInfo->m_fpdm = g_globalArg->m_curInvVol->m_code;												//��Ʊ����
	//m_smallInvInfo->m_fphm = g_globalArg->m_curInvVol->m_ieno + 1 - g_globalArg->m_curInvVol->m_remain;		//��Ʊ���� 
	m_smallInvInfo->m_fphm =g_globalArg->m_curInvVol->m_curInvNo;
	m_smallInvInfo->m_kprq = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);	//��Ʊ����
	m_smallInvInfo->m_kpsj = TDateTime::CurrentDateTime().FormatInt(HHMMSS);	//��Ʊʱ��
	
	m_smallInvInfo->m_kplx = m_singleInvInfo->m_kplx;		//��Ʊ����
	
	m_smallInvInfo->m_yfpdm = m_singleInvInfo->m_yfpdm;	
	m_smallInvInfo->m_yfphm = m_singleInvInfo->m_yfphm;		//ԭ��Ʊ����	
	m_smallInvInfo->m_fkdw = m_singleInvInfo->m_fkdw;		//���λ
	m_smallInvInfo->m_fkdwsh = m_singleInvInfo->m_fkdwsh;   //����˰��
	m_smallInvInfo->m_sky = m_singleInvInfo->m_sky;			//�տ�Ա
	//	m_smallInvInfo->m_skyid = m_singleInvInfo->m_skyid;		//�տ�ԱID
	//	m_smallInvInfo->m_ptype = m_singleInvInfo->m_ptype;		//���ʽ
	m_smallInvInfo->m_scbz = m_singleInvInfo->m_scbz;
	
	
	if(RET_MANUAL_INV == m_smallInvInfo->m_kplx)
	{
		sprintf(value, "��Ӧ������Ʊ����:%s����:%08lu",
			m_smallInvInfo->m_yfpdm.c_str(), m_smallInvInfo->m_yfphm);	
		m_smallInvInfo->m_backup1 = value;	
	}
    else
	{
		m_smallInvInfo->m_backup1 = m_singleInvInfo->m_backup1;		//�����ֶ�1
	}
	
	//	m_smallInvInfo->m_backup2 = m_singleInvInfo->m_backup2;		//�����ֶ�2 
	//	m_smallInvInfo->m_backup3 = m_singleInvInfo->m_backup3;		//�����ֶ�3
    
	CInvDet *p = m_smallInvInfo->pHead;
	CInvDet *pe;
	
    //��Ϊ������
	if (p == NULL)
	{
		DBG_PRINT((" m_smallInvInfo->pHead = NULL !"));
		DBG_RETURN(FAILURE);		
	}    
    //��Ϊ�ǿ�������ֵ
	DBG_PRINT(("��Ʒ������m_smallInvInfo->m_sphsl == %d", m_smallInvInfo->m_sphsl));
	for( INT32 i=0; i<m_smallInvInfo->m_sphsl; i++, p = p->pNext )
	{
		p->m_fpdm = g_globalArg->m_curInvVol->m_code; 
        //p->m_fphm = g_globalArg->m_curInvVol->m_ieno + 1 - g_globalArg->m_curInvVol->m_remain;
        p->m_fphm =g_globalArg->m_curInvVol->m_curInvNo;
		p->m_kplx = m_smallInvInfo->m_kplx;
		p->m_sky =g_globalArg->m_operator->m_name;
			p->m_sphxh = (i+1);
		//p->m_sphxh = i;
		p->m_kprq = m_smallInvInfo->m_kprq; 
        p->m_kpsj = m_smallInvInfo->m_kpsj;
		
		DBG_PRINT(("��Ʊ����  p->m_fpdm == %s",p->m_fpdm.c_str()));
		DBG_PRINT(("��Ʊ����  p->m_fphm == %d",p->m_fphm));
		DBG_PRINT(("��Ʒ�����p->m_sphxh == %d",p->m_sphxh));
		pe = p;
	}
	pe->pNext = NULL;
    m_smallInvInfo->pEnd = pe;
	
	DBG_PRINT(("�˳�ComposePrnInv����"));
	DBG_RETURN(SUCCESS);
}

//-------------------------------------------------------------------
//�������ܣ����㵱ǰ��Ʒ�����跢Ʊ��Ŀ
//-------------------------------------------------------------------
UINT32 SaleData::CalculateInvNum()
{
	DBG_ENTER("SaleData::CalculateInvNum");
	DBG_PRINT(("����CalculateInvNum����"));
	
	UINT32 invoiceNum = 0;
	DBG_PRINT(("m_singleInvInfo->m_sphsl==%d", m_singleInvInfo->m_sphsl));
	m_detailCount = m_singleInvInfo->m_sphsl;		//���۵���Ʒ������
	DBG_PRINT(("m_detailCount==%d", m_detailCount));
	
	m_pHead = m_singleInvInfo->pHead;
	while( ScanGoodsLine(0)==FAILURE )			//ɨ����Ʒ�У�����0������Ʊ��
	{
		invoiceNum++;
	}
	DBG_PRINT(("ʵ����Ҫ��Ʊ���� = invoiceNum = %u", invoiceNum));
	DBG_PRINT(("�˳�CalculateInvNum����"));
	DBG_RETURN(invoiceNum);
}

//------------------------------------------------------------
//���·�Ʊ������Ϣ����ʣ�෢Ʊ����
//------------------------------------------------------------
UINT8 SaleData::UpdateVolRemain(UINT32 remain)
{
	DBG_PRINT(("����UpdateVolRemain����"));
	DBG_PRINT(("remain == %d", remain));
	DBG_PRINT(("g_globalArg->m_curInvVol->m_code == %s", g_globalArg->m_curInvVol->m_code.c_str()));
	DBG_PRINT(("g_globalArg->m_curInvVol->m_isno == %d", g_globalArg->m_curInvVol->m_isno));
	DBG_ENTER("SaleData::UpdateVolRamain");
	
	char value[256];
	memset((void*)value, 0, sizeof(value));
	string codeNo = g_globalArg->m_curInvVol->m_code;
	UINT32 isNo = g_globalArg->m_curInvVol->m_isno;
    string strSql;
	
	DBG_PRINT(("codeNo == %s", codeNo.c_str()));
	DBG_PRINT(("isNo == %d", isNo));
	
    sprintf(value, "UPDATE INV_VOL SET REMAIN = %u ", remain);	
    strSql = "";
	strSql.append(value);
    
	sprintf(value, "WHERE CODE = '%s' AND IS_NO = %u", codeNo.c_str(), isNo);
	g_globalArg->m_curInvVol->m_filter = "";
	g_globalArg->m_curInvVol->m_filter.append(value);
	
    strSql.append(g_globalArg->m_curInvVol->m_filter);
    g_globalArg->m_curInvVol->SetSQL(strSql);
    DBG_PRINT(("�޸ķ�Ʊʣ����� strSql = %s", strSql.c_str()));
	
	if (g_globalArg->m_curInvVol->ExecuteSQL()!= SQLITE_OK)
	{
		DBG_RETURN(FAILURE);
	}
	
	DBG_PRINT(("�˳�UpdateVolRemain����"));
	DBG_RETURN(SUCCESS);
}

//-------------------------------------------------------------------------------------
//��֮ǰ��pIssuedInvData��Ҫnew����
//��װΪ���˰���������͵����ݽṹ
//-------------------------------------------------------------------------------------
/*
UINT8 SaleData::ComposeIssuedInvData( CInvHead *smallInv, IssuedInvoice *pIssuedInvData )
{
DBG_PRINT(("����ComposeIssuedInvData����"));
DBG_ENTER("SaleData::ComposeIssuedInvData");

 UINT8 i;
	UINT8 j;
	
	 DBG_ASSERT_EXIT((smallInv != NULL)&&(pIssuedInvData != NULL), (" m_con == NULL or pIssuedInvData = NULL "));
	 
	  memset((void *)pIssuedInvData, 0, sizeof(IssuedInvoice));
	  
	   smallInv->m_kprq = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);
	   smallInv->m_kpsj = TDateTime::CurrentDateTime().FormatInt(HHMMSS);
	   CInvDet *p = smallInv->pHead;
	   for(; p != NULL; p = p->pNext)
	   {
	   p->m_kprq = smallInv->m_kprq; 
	   p->m_kpsj = smallInv->m_kpsj;
	   }
	   pIssuedInvData->invoice_date = smallInv->m_kprq;
	   DBG_PRINT(("m_smallInvInfo->m_kprq =  %u", smallInv->m_kprq));
	   DBG_PRINT(("m_smallInvInfo->m_kpsj =  %u", smallInv->m_kpsj));
	   DBG_PRINT(("pIssuedInvData->invoice_date =  %u", pIssuedInvData->invoice_date));
	   
		
		 pIssuedInvData->invoice_no = smallInv->m_fphm;
		 pIssuedInvData->invoice_type = smallInv->m_kplx;
		 
		  p = smallInv->pHead;
		  //  DBG_ASSERT_EXIT((p != NULL), (" smallInv->pHead = NULL "));
		  
		   //��Ʊ�ܽ��
		   pIssuedInvData->sum_money = smallInv->m_kphjje;		//xsr ���Ͳ�ͬ
		   DBG_PRINT(("pIssuedInvData->sum_money = %d",pIssuedInvData->sum_money));
		   
			DBG_PRINT(("�˳�ComposeIssuedInvData����"));
			DBG_RETURN(SUCCESS);
			}
*/
//ͳ��һ�ŷ�Ʊĳ˰��˰Ŀ�Ŀ�Ʊ�ܽ��
//INT64 SaleData::GetTaxIDMoneySUM(CInvDet * invDet, UINT32 CodeNo, UINT32 InvNo, UINT8 TaxID)
//{
// 	DBG_ENTER("SaleData::GetTaxIDMoneySUM");
//     DBG_ASSERT_EXIT((invDet != NULL), (" invDet == NULL!"));
// 
// 	char value[256];
// 	memset((void*)value, 0, sizeof(value));
// 	string strFilter = "";
//     
// 	strFilter = "SELECT SUM(M_SUM) FROM INV_DET";
// 	sprintf(value, "WHERE CODE_NO = %u AND INV_NO = %u AND TAX_ID = %u",CodeNo, InvNo, TaxID);
// 	strFilter.append(value);
// 	invDet->SetSQL(strFilter);
// 
//     INT64 nSum;
//     invDet->GetOneResult(DB_INT64, &nSum);
// 	DBG_PRINT(("nSum =  %d", nSum));
//     DBG_RETURN(nSum);
//}

//���ۿ�
UINT8 SaleData::Discount(double fRate)
{
	DBG_ENTER("SaleData::Discount");
	
	if ((fRate<1)||(fRate>=100))
	{
		DBG_RETURN(REBATE_ERROR);
	}
	
	m_property = DETAIL_GOODS_DISCOUNT;
	m_tmpRate = fRate;
	DBG_PRINT(("m_tmpRate =  %f", m_tmpRate));
	
	DBG_RETURN(SUCCESS);
	
}

//������Ʊ��α��
// UINT8 SaleData::GetFiscalCode(IssuedInvoice *pIssuedInvData, string fpdm, UINT8 *fiscal_code)
// {
// 	DBG_ENTER("SaleData::GetFiscalCode");
// 	DBG_ASSERT_EXIT((pIssuedInvData != NULL), ("pIssuedInvData = NULL "));
// 	DBG_ASSERT_EXIT((fiscal_code != NULL), ("fiscal_code = NULL "));
// 
// 	UINT8 pdata[128];
// 	UINT8 poutdata[128];
// 	UINT8 skm[32];
// 	UINT8 tmpBuf[32];
// 	INT8 chValue[21] = "00000000000000000000";
// 	UINT32 outlen=0;
// 	int sqmlen=1024*8;
// 	int len = 0;
// 	memset(pdata,0,sizeof(pdata));
// 	memset(poutdata,0,sizeof(poutdata));
// 
// 	DBG_PRINT(("invoice_date=%d", pIssuedInvData->invoice_date));
// 	sprintf((INT8 *)pdata, "%08d", pIssuedInvData->invoice_date);	//��Ʊ����
// 
// 	DBG_PRINT(("invoice_no=%d", pIssuedInvData->invoice_no));
// 	sprintf((INT8 *)(pdata+8), "%010d", pIssuedInvData->invoice_no); //��Ʊ���� 10������
// 
// 	len =  fpdm.length();
// 	sprintf((chValue+20-len), "%s", fpdm.c_str());
// 	sprintf((INT8 *)(pdata+8+10), "%s", chValue); //��Ʊ���� 20λ
// 	DBG_PRINT(("pdata: %s", pdata));
// 
// 	DBG_PRINT((" m_smallInvInfo->pHead = %x!", m_smallInvInfo->pHead));
// 	if(!param_encrypt(1,pdata,poutdata,&outlen))
// 	{
// 		DBG_PRINT(("param_encrypt ERR !"));
// 		DBG_RETURN(FAILURE);
// 	}
// 	memset(skm,0,sizeof(skm));
// 
// 	sqmlen=strlen(g_globalArg->m_sq_wm);
// 	DBG_PRINT(("sqmlen = %d", sqmlen));
// 	if(!init_sqm(g_globalArg->m_sq_wm, sqmlen))
// 	{
// 		DBG_PRINT(("init_sqm ERR !"));
// 		DBG_RETURN(FAILURE);
// 	}
// 
// 	if(!get_wlkp_skm(1, (UINT8 *)g_globalArg->m_corpInfo->m_Nsrsbh.c_str(), 
// 						g_globalArg->m_corpInfo->m_Nsrsbh.length(), 
// 						poutdata, outlen, pIssuedInvData->sum_money, skm))
// 	{
// 		DBG_PRINT(("get_wlkp_skm ERR !"));
// 		DBG_RETURN(FAILURE);
// 	}
// 	else
// 	{
// 		DBG_PRINT(("skm=%s", skm));
// 	}	
// 	DBG_PRINT((" m_smallInvInfo->pHead = %x!", m_smallInvInfo->pHead));
// 	strcpy((INT8 *)fiscal_code, (const INT8 *)skm);
// 
// 	DBG_PRINT((" m_smallInvInfo->pHead = %x!", m_smallInvInfo->pHead));
// 	DBG_RETURN(SUCCESS);
// }

//����˰����
UINT8 SaleData::GetFiscalCode(CInvHead *pInv,UINT8 *fiscalCode, UINT32 &nRetCode, string &strErr)
{
	DBG_ENTER("SaleData::GetFiscalCode");
	DBG_ASSERT_EXIT((pInv != NULL), ("pInv = NULL "));
	
	
	memset((void*)fiscalCode, 0, sizeof(fiscalCode));
	// 	nRetCode = CJSKInfoFunc::TaxCardInvHeadInfo(pInv,fiscalCode, strErr);
	// 	if (JSK_SUCCESS != nRetCode)//ȡ˰����ʧ��
	// 	{
	// 		DBG_PRINT(("GetFiscalCode ERR: %s !", strErr.c_str()));
	// 		DBG_RETURN(FAILURE);
	// 	}
	
	DBG_PRINT((" fiscalCode = %s!", (INT8*)fiscalCode));
	DBG_RETURN(SUCCESS);
}

UINT8 SaleData::PriceInput(double dPrice)
{
	DBG_ENTER("SaleData::PriceInput");
	DBG_PRINT(("����SaleData::PriceInput����"));
	if( dPrice < BASE_PRICE )
	{
		DBG_RETURN(PRICE_NOT_ENOUGH);
	}
    m_tmpPrice = dPrice;
	DBG_PRINT(("m_tmpPrice = %f", m_tmpPrice));
	DBG_PRINT(("�˳�SaleData::PriceInput����"));
	DBG_RETURN(SUCCESS);
}

//------------------------------------------------------------------
//�������ƣ��ܼ�����
//�������ܣ����û���������ִ浽m_tmpSum�С�
//------------------------------------------------------------------
UINT8 SaleData::SumInput(double dSum)
{
	DBG_ENTER("SaleData::SumInput");
	INT64 nSum = 0;
	nSum = double2int(dSum * SUM_EXTENSION*10.0);//ԭʼ�ܽ��
	nSum = double2int(nSum / 10.0);
	//�ܼ۲���
	if (0 == nSum) 
	{
		DBG_RETURN(MONEY_ZERO);
	}
	if (nSum<=0)
	{
		DBG_RETURN(MONEY_NOT_ENOUGH);
	}
    m_tmpSum = nSum;
	DBG_PRINT(("m_tmpSum = %d", m_tmpSum));
	DBG_RETURN(SUCCESS);
}

UINT8 SaleData::ClientNameInput(const char *content)
{
	DBG_ENTER("SaleData::ClientNameInput");
	UINT8 len;
	
	//���Ƴ���
	len = strlen(content);
    DBG_PRINT(("len = %u", len));
	if (len > PAYER_NAME_LEN) 
	{
		DBG_RETURN(EXCEED_NAME_LEN);	
	}
	else if(len == 0)
	{
		DBG_PRINT(("len = %u", len));
		DBG_RETURN(NO_NAME);
	}
	DBG_PRINT(("content = %s", content));
	
	m_singleInvInfo->m_fkdw = content;
	
	DBG_PRINT(("m_singleInvInfo->m_fkdw = %s", m_singleInvInfo->m_fkdw.c_str()));
	DBG_RETURN(SUCCESS);
}

UINT8 SaleData::ClientNameInput(const char *chfkdw, const char *chfkdwsh)
{
	DBG_ENTER("SaleData::ClientNameInput");
	UINT8 len=0;
	UINT8 shlen=0;
	//���Ƴ���
	len = strlen(chfkdw);
    DBG_PRINT(("len = %u", len));
	if (len > PAYER_NAME_LEN) 
	{
		DBG_RETURN(EXCEED_NAME_LEN);	
	}
	else if(len == 0)
	{
		DBG_PRINT(("len = %u", len));
		DBG_RETURN(NO_NAME);
	}
	DBG_PRINT(("chfkdw = %s", chfkdw));
	
	m_singleInvInfo->m_fkdw = chfkdw;
	
	DBG_PRINT(("m_singleInvInfo->m_fkdw = %s", m_singleInvInfo->m_fkdw.c_str()));

	m_singleInvInfo->m_fkdwsh = chfkdwsh;
	DBG_PRINT(("m_singleInvInfo->m_fkdwsh = %s", m_singleInvInfo->m_fkdwsh.c_str()));

	DBG_RETURN(SUCCESS);
}

UINT8 SaleData::ClientCodeInput(const char *content, string &strErr)
{
	DBG_ENTER("SaleData::ClientCodeInput");
	UINT8 len;
	
	//���Ƴ���
	len = strlen(content);
    DBG_PRINT(("len = %u", len));
	if (len > TAX_CODE_LEN) 
	{
		strErr = "���˰�Ź���";
		DBG_RETURN(FAILURE);
	}
	else if(len == 0)
	{				
		strErr = "δ���븶�˰��";
		DBG_RETURN(FAILURE);
	}
	DBG_PRINT(("content = %s", content));
	
	m_singleInvInfo->m_fkdwsh = content;
	
	DBG_PRINT(("m_singleInvInfo->m_fkdwsh = %s", m_singleInvInfo->m_fkdwsh.c_str()));
	DBG_RETURN(SUCCESS);
}

UINT8 SaleData::RemarksInput(const char *content, string &strErr)
{
	DBG_ENTER("SaleData::RemarksInput");
	UINT8 len;
	
	//���Ƴ���
	len = strlen(content);
    DBG_PRINT(("len = %u", len));
	if (len > SALE_REMARKS_LEN) 
	{
		strErr = "��ע���ݹ���";
		DBG_RETURN(FAILURE);
	}
	else if(len == 0)
	{				
		strErr = "δ���뱸ע����";
		DBG_RETURN(FAILURE);
	}
	DBG_PRINT(("content = %s", content));
	
	m_singleInvInfo->m_backup1 = content;
	
	DBG_PRINT(("m_singleInvInfo->m_backup1 = %s", m_singleInvInfo->m_backup1.c_str()));
	DBG_RETURN(SUCCESS);
}

UINT8 SaleData::CancelGoods(void)
{
	DBG_ENTER("SaleData::CancelGoods");
	m_cancel = CANCEL_PRODUCT;
	DBG_PRINT(("CancelGoods"));
	DBG_RETURN(SUCCESS);
}

UINT8 SaleData::NoCancelGoods(void)
{
	DBG_ENTER("SaleData::NoCancelGoods");
	m_cancel = 0;
	DBG_PRINT(("NoCancelGoods"));
	DBG_RETURN(SUCCESS);
}

UINT8 SaleData::CancelGoodsByPLU(string &strCode, double nCancelNum, double &dPrice)
{
	DBG_ENTER("SaleData::CancelGoods");
	CInvDet *invDet, *nextInvDet;
	INT64 moneySum = 0;
	INT64 orgMoneySum = 0;
	m_realCancelNum = 0; //ʵ��ɾ������Ʒ����
	UINT32 nEnterTime = 0;//����whileѭ���Ĵ���
	
	DBG_PRINT(("CancelGoodsByPLU 11"));
	DBG_PRINT(("strCode = %s", strCode.c_str()));
    DBG_PRINT(("nCancelNum = %f", nCancelNum));
	
	//�û�������ȡ����Ʒ�����������ϸ�����ȡ������Ʒ
	while (1)
	{
		nEnterTime++;
		DBG_PRINT(("CancelGoodsByPLU nEnterTime = %u", nEnterTime));
		invDet = m_singleInvInfo->SearchNode(strCode);
		if(invDet==NULL) //��û�ҵ��ýڵ���Ʒ
		{
			if (1==nEnterTime) 
			{
				DBG_PRINT(("CancelGoodsByPLU 2"));
				DBG_RETURN(NO_SUCH_GOODS);//�����ڸ���Ʒ
			}
			break;
		}		
		nextInvDet = invDet->pNext;
		
		DBG_PRINT(("CancelGoodsByPLU 2"));
		
		m_realCancelNum += invDet->m_spsl;				//ʵ��ɾ������Ʒ��������
		dPrice = invDet->m_spdj;						//���汻ɾ����Ʒ�ļ۸��Թ���Ļ��ʾ
		m_tmpGoodsNum--;								//��ʾ�ĵ�ǰ��Ʒ�м�1
		m_singleInvInfo->m_sphsl--;						//��Ʊ����Ʒ�м�1
		m_singleInvInfo->m_kphjje -= invDet->m_spje;	//��Ʊ�ܽ�����
        m_singleInvInfo->m_kpse -= invDet->m_spse;	    //��Ʊ˰�����
		m_tmpMoneySum -= invDet->m_spje;				//��ʱ���Ž�����
		
		if (invDet->m_property == DETAIL_GOODS_DISCOUNT)		//���ۿ�
		{
			m_singleInvInfo->m_sphsl--;							//��Ʊ����Ʒ�м�1
			m_tmpGoodsNum--;									//��ʾ�ĵ�ǰ��Ʒ�м�1
			m_singleInvInfo->m_kphjje -= nextInvDet->m_spje;	//��Ʊ�ܽ�����
			m_singleInvInfo->m_kpse -= nextInvDet->m_spse;	//��Ʊ˰�����
			m_tmpMoneySum -= nextInvDet->m_spje;				//��ʱ���Ž�����
			m_singleInvInfo->DelNode(strCode);				
		}
		else if (invDet->m_property == DETAIL_GOODS_REDUCT)		//������
		{
			m_singleInvInfo->m_sphsl--;					//��Ʊ����Ʒ�м�1
			m_tmpGoodsNum--;									//��ʾ�ĵ�ǰ��Ʒ�м�1
			m_singleInvInfo->m_kphjje -= nextInvDet->m_spje;	//��Ʊ�ܽ�����
			m_singleInvInfo->m_kpse -= nextInvDet->m_spse;	//��Ʊ˰�����
			m_tmpMoneySum -= nextInvDet->m_spje;				//��ʱ���Ž�����
			m_singleInvInfo->DelNode(strCode);				
		}
		
		m_singleInvInfo->DelNode(strCode);
	}
	
	DBG_PRINT(("CancelGoodsByPLU over"));
	DBG_RETURN(SUCCESS);	
}

UINT8 SaleData::CancelGoodsByDept(string dpNo, double nCancelNum, double &dPrice)
{
	DBG_ENTER("SaleData::CancelGoods");
	CInvDet *invDet, *nextInvDet;
	INT64 moneySum = 0;
	INT64 orgMoneySum = 0;
	m_realCancelNum = 0;	//ʵ��ɾ������Ʒ����
	UINT32 nEnterTime = 0;	//����whileѭ���Ĵ���
	
	DBG_PRINT(("dpNo == %s", dpNo.c_str()));
    DBG_PRINT(("nCancelNum == %d", nCancelNum));
	
	//�û�������ȡ����Ʒ�����������ϸ�����ȡ������Ʒ
	while (1)
	{
		nEnterTime++;
		DBG_PRINT(("CancelGoodsByDept nEnterTime = %u", nEnterTime));
		invDet = m_singleInvInfo->SearchNode(dpNo);
		
		if( invDet==NULL ) //�������ڸ���Ʒ
		{
			if( 1==nEnterTime ) 
			{
				DBG_PRINT(("CancelGoodsByDept "));
				DBG_RETURN(NO_SUCH_GOODS);//�����ڸ���Ʒ
			}
			break;
		}
		nextInvDet = invDet->pNext;
		
		DBG_PRINT(("CancelGoodsByDept 2"));
		
		m_realCancelNum += invDet->m_spsl;				//ʵ��ɾ������Ʒ��������
		dPrice = invDet->m_spdj;						//���汻ɾ����Ʒ�ļ۸��Թ���Ļ��ʾ
		m_tmpGoodsNum--;								//��ʾ�ĵ�ǰ��Ʒ�м�1
		m_singleInvInfo->m_sphsl--;						//��Ʊ����Ʒ�м�1
		m_singleInvInfo->m_kphjje -= invDet->m_spje;	//��Ʊ�ܽ�����
		m_singleInvInfo->m_kpse -= invDet->m_spse;	//��Ʊ˰�����
		m_tmpMoneySum -= invDet->m_spje;				//��ʱ�����ܽ�����
		
		if (invDet->m_property == DETAIL_GOODS_DISCOUNT)		//���ۿ�
		{
			m_tmpGoodsNum--;								//��ʾ�ĵ�ǰ��Ʒ�м�1
			m_singleInvInfo->m_sphsl--;							//��Ʊ����Ʒ�м�1
			m_singleInvInfo->m_kphjje -= nextInvDet->m_spje;	//��Ʊ�ܽ�����
			m_singleInvInfo->m_kpse -= nextInvDet->m_spse;	//��Ʊ˰�����
			m_tmpMoneySum -= nextInvDet->m_spje;				//��ʱ�����ܽ�����
			m_singleInvInfo->DelNode(dpNo);			
		}
		else if (invDet->m_property == DETAIL_GOODS_REDUCT)		//������
		{
			m_tmpGoodsNum--;								//��ʾ�ĵ�ǰ��Ʒ�м�1
			m_singleInvInfo->m_sphsl--;							//��Ʊ����Ʒ�м�1
			m_singleInvInfo->m_kphjje -= nextInvDet->m_spje;	//��Ʊ�ܽ�����
			m_singleInvInfo->m_kpse -= nextInvDet->m_spse;	//��Ʊ˰�����
			m_tmpMoneySum -= nextInvDet->m_spje;				//��ʱ�����ܽ�����
			m_singleInvInfo->DelNode(dpNo);				
		}
		m_singleInvInfo->DelNode(dpNo);
	}
	
	DBG_PRINT(("CancelGoodsByDept SUCCESS"));
	DBG_RETURN(SUCCESS);	
}

//�˷�����
UINT8 SaleData::Plus(double tmpAmount)
{
	DBG_ENTER("SaleData::Plus");
	DBG_PRINT(("����Plus����"));
	double amount = tmpAmount;
	
	if((doublecmp(tmpAmount, 0.0))==1)
	{
		DBG_PRINT(("The goods amount = 0.0! "));
		DBG_RETURN(ILLEGAL_AMOUNT);
	}
	
	m_dotNum = AmountRound(&tmpAmount);
	if (m_dotNum == -1) //��������
	{
		m_dotNum = 0;
		DBG_PRINT(("The goods amount exceeds the limit!"));
		DBG_RETURN(EXCEED_AMOUNT);
	}
	m_saveAmount = tmpAmount; //���������õ�����ֵ
	m_tmpAmount = amount;     //�����ܽ��ʱ�õ�ԭʼ����ֵ
	
	DBG_PRINT(("Plus"));
	
	INT8 tmp[16];
	INT8 tmp2[16];
	sprintf(tmp, "%%.%luf", m_dotNum);
	sprintf(tmp2, tmp, m_saveAmount);
    DBG_PRINT(("����ֵ =  %s", tmp2));
	DBG_PRINT(("m_dotNum =  %d", m_dotNum));
	DBG_PRINT(("ԭʼֵ m_tmpAmount = %f", m_tmpAmount));
	
	DBG_PRINT(("�˳�Plus����"));
	DBG_RETURN(SUCCESS);
}

UINT8 SaleData::TotalCancel(void)
{
	DBG_ENTER("SaleData::TotalCancel");
	
	m_tmpGoodsNum = 0;  //��ǰ����Ʒ��������
	if (m_returnOther == 1) //�˷Ǳ�����Ʊ
	{
		m_tmpMoneySum = 0; //����Ʊ���ۼƽ��
		InitSaleData(0);  //������Ϣ��ʼ��		
	}
	else
	{
		InitSaleData(1);  //������Ϣ��ʼ��
	}
	
	InitInvHead();   //���ŷ�Ʊ��Ϣ��ʼ��
	m_workState = WORK_COMPLETE;
	
	DBG_PRINT(("TotalCancel"));
	DBG_RETURN(SUCCESS);
}

//--------------------------------------------------------
//��������
//--------------------------------------------------------
UINT8 SaleData::DeptSale(UINT32 nDeptNo, string strCode)
{
	DBG_ENTER("SaleData::DeptSale");
	DBG_PRINT(("����DeptSale����"));
	DBG_PRINT(("nDeptNo==%s", strCode.c_str()));
	DBG_PRINT(("nDeptNo==%u", strCode.c_str()));
	
	char value[128];
	memset((void*)value, 0, sizeof(value));
	string filter;
	INT32 errorcode;
	UINT8 ret = SUCCESS, len = 0;
	
	//��ѯ��Ʒ��Ϣ
	CDept curDept;
	m_deptInfo = &curDept;
	
	if (strCode != "")//����PLU���� 
	{
		sprintf(value,"WHERE SP_BM = '%s'",strCode.c_str());	
	}
	else //���ݲ���ż���
	{
		sprintf(value,"WHERE BLH = %u",nDeptNo);	
	}
	//��װ��ѯ����	
	DBG_PRINT(("value==%s", value));
	m_deptInfo->m_filter = value;
	DBG_PRINT(("m_deptInfo->m_filter==%s", m_deptInfo->m_filter.c_str()));
	
	//��ѯ
	m_deptInfo->Requery();
	errorcode = m_deptInfo->LoadOneRecord();
	if( errorcode != SQLITE_OK )
	{
		DBG_PRINT(("���棺û�鵽��Ʒ errorcode = %d", errorcode));
		ret = NO_SUCH_GOODS;
		InitSaleData(0);
		DBG_RETURN(ret);	
	}
	//�����Ʒ˰���Ƿ���Ȩ
	CTax temptax;
	memset((void*)value, 0, sizeof(value));
	sprintf(value,"where SL = %u", (UINT32)(m_deptInfo->m_spsl*DEPT_TAX_EXTENSION));//��Ȩ˰�ʱ�CTax��˰����UINT32��ʽ���棬��CDept�в�һ��
	temptax.m_filter = value;
	temptax.Requery();
	errorcode = temptax.LoadOneRecord();
	if( errorcode != SQLITE_OK )
	{
		DBG_PRINT(("���棺��Ʒ˰��δ��Ȩ errorcode = %d", errorcode));
		ret = TAX_UNAUTHORIZED;
		InitSaleData(0);
		DBG_RETURN(ret);	
	}
	
	DBG_PRINT(("�鵽����Ʒ����Ϣ����:"));
    DBG_PRINT(("m_spbm : %s ", m_deptInfo->m_spbm.c_str()));
	DBG_PRINT(("m_spmc : %s ", m_deptInfo->m_spmc.c_str()));
	DBG_PRINT(("m_spsl : %f ", m_deptInfo->m_spsl));
	DBG_PRINT(("m_spjm : %s ", m_deptInfo->m_spjm.c_str()));
	DBG_PRINT(("m_spdw : %s ", m_deptInfo->m_spdw.c_str()));
	
	//����Ʒ��Ϣ�޵��ۣ�������ܼ�����
	DBG_PRINT(("m_tmpSum==%d", m_tmpSum));
	if( m_deptInfo->m_spdj == 0 )
	{
		if( (m_cancel != CANCEL_PRODUCT) && (m_tmpSum == 0) )
		{
			ret = MUST_INPUT_SUM;			
			InitSaleData(0);  //������Ϣ��ʼ��
			DBG_PRINT(("�˳�DeptSale����"));
			DBG_RETURN(ret);			
		}
		
		m_deptInfo->m_spdj = ((double)m_tmpSum)/SUM_EXTENSION;//���ܼ۸�ֵ������
		DBG_PRINT(("m_spdj == %f ", m_deptInfo->m_spdj));
		//�������
		m_tmpSum = 0;
		m_tmpAmount = 1.0;   //ǿ������Ϊ1
		m_saveAmount = 1.0;  //ǿ������Ϊ1
		m_dotNum = 0;
		m_tmpPrice = 0.0;    //��������ʱ������
	}
	
	//m_deptInfo = &curDept;
	DBG_ASSERT_EXIT((m_deptInfo != NULL), (" m_deptInfo == NULL!"));
	
	//������Ʒ��ϸ��Ϣ�������ܼ�����ģʽ��������ܼۼ������������
	//	if( g_globalArg->m_saleMode == 0 )
	//	{
	//		m_deptInfo->m_spdj = ((double)m_tmpSum)/SUM_EXTENSION;
	//	}
	//	m_deptInfo->m_rate = 100.0;				//��δ���ۣ���Ĭ����Ϊ100
	//	m_deptInfo->m_spdw = "piece";
	
	
	//	//�������
	//	m_tmpSum = 0;						//xsr ����	
	//	m_dotNum = 0;						//
	//	if( g_globalArg->m_saleMode == 0 )	//�����ܼ�����ģʽ
	//	{
	//		m_tmpPrice = 0.0;				//��������ʱ������
	//		m_tmpAmount = 1.0;				//ǿ������Ϊ1
	//		m_saveAmount = 1.0;				//ǿ������Ϊ1
	//	}
	
	//�������������̺���
	ret = Sale(m_deptInfo);
	m_deptInfo = NULL;
	InitSaleData(0);  //������Ϣ��ʼ��
	DBG_RETURN(ret);
}

//---------------------------------------------------------------------------------------
//����ӡ��Ʊ�ṹ��ķ�Ʊͷ����ϸ
//---------------------------------------------------------------------------------------
UINT8 SaleData::InvClassToStuct(struct TInvFullInfo *invFullInfo, CInvHead *smallInvInfo)
{
	DBG_PRINT(("����InvClassToStuct����"));
	DBG_ENTER("SaleData::InvClassToStuct");
	
	DBG_ASSERT_EXIT((invFullInfo != NULL)&&(smallInvInfo != NULL), (" invFullInfo == NULL or smallInvInfo = NULL "));
	
	//ת����Ʊ������Ϣ 
	
	//��Ʊ����
	memset((void *)invFullInfo->head.TypeCodeNo, 0, sizeof(invFullInfo->head.TypeCodeNo));
	strcpy( (char *)invFullInfo->head.TypeCodeNo, smallInvInfo->m_fpdm.c_str() );
	DBG_PRINT(("��Ʊ����  : %s ", invFullInfo->head.TypeCodeNo));
	
	//��Ʊ����
	invFullInfo->head.InvNo = smallInvInfo->m_fphm; 
	DBG_PRINT(("��Ʊ����  : %u ", invFullInfo->head.InvNo));
	
	//��Ʊ���� CCYYMMDD
	invFullInfo->head.Date = smallInvInfo->m_kprq;
	DBG_PRINT(("��Ʊ����  : %u ", invFullInfo->head.Date));
	
	//��Ʊʱ��
	invFullInfo->head.Time = smallInvInfo->m_kpsj;
    DBG_PRINT(("��Ʊʱ��  : %u ", invFullInfo->head.Time));
	
	//��Ʊ����
	invFullInfo->head.Type = smallInvInfo->m_kplx;
	DBG_PRINT(("��Ʊ����  : %u ", invFullInfo->head.Type));
	
	//��Ʊ�ϼƽ�� ��λ���� Сд
	invFullInfo->head.TotalSum = smallInvInfo->m_kphjje;
	DBG_PRINT(("��Ʊ�ϼƽ�� : %d", invFullInfo->head.TotalSum));
	
	//ԭ��Ʊ����
	invFullInfo->head.PosInvNo = smallInvInfo->m_yfphm;
	DBG_PRINT(("ԭ��Ʊ����  : %u ", invFullInfo->head.PosInvNo));
	
	//���λ  ASC
	UINT8 nLen = smallInvInfo->m_fkdw.length() + 1;
	memcpy((void *)invFullInfo->head.ClientName, (void *)smallInvInfo->m_fkdw.c_str(), nLen);
	DBG_PRINT(("���λ : %s ", invFullInfo->head.ClientName));
	
	//�տ�Ա ASC
	nLen = smallInvInfo->m_sky.length() + 1;
	memcpy((void *)invFullInfo->head.OperatorName, (void *)smallInvInfo->m_sky.c_str(), nLen);
    DBG_PRINT(("�տ�Ա : %s ", invFullInfo->head.OperatorName));
	
	//�տ�ԱID
	//	invFullInfo->head.OpId = smallInvInfo->m_skyid;
	//	DBG_PRINT(("�տ�ԱID : %u ", invFullInfo->head.OpId));
	
	//���ʽ
	// 	invFullInfo->head.PayMode = smallInvInfo->m_ptype;
	// 	DBG_PRINT(("���ʽ  : %u ", invFullInfo->head.PayMode));
	
	//��Ʒ������
	invFullInfo->head.detailCount = smallInvInfo->m_sphsl;	//xsr ���ʣ����Ͳ�ƥ��
	DBG_PRINT(("��Ʒ������ : %u", invFullInfo->head.detailCount));
	
	//��α˰����
	memset(invFullInfo->head.TaxCtrCode, 0, sizeof(invFullInfo->head.TaxCtrCode));
	memcpy(invFullInfo->head.TaxCtrCode, smallInvInfo->m_fwm.c_str(), smallInvInfo->m_fwm.length());
	DBG_PRINT(("��α˰���� : %s", invFullInfo->head.TaxCtrCode));
	
	//˰��
	smallInvInfo->m_sl = 0.0;
	invFullInfo->head.sl = 0.0;
	DBG_PRINT(("˰��      : %f", invFullInfo->head.sl));
	
	
	//��Ʊ���
	//	smallInvInfo->m_fplb = 0;
	//	invFullInfo->head.fplb = 0;
	//	DBG_PRINT(("��Ʊ���    : %d", invFullInfo->head.fplb));
	
	//�ϴ���־
	smallInvInfo->m_scbz = 0;
	invFullInfo->head.scbz = 0;
	DBG_PRINT(("�ϴ���־    : %d", invFullInfo->head.scbz));
	
	//��ӡ����
	smallInvInfo->m_dycs = 0;
	invFullInfo->head.dycs = 0;
	DBG_PRINT(("��ӡ����    : %d", invFullInfo->head.dycs));
	
	
	
	//ת����Ʊ��ϸ��Ϣ
	CInvDet *p = smallInvInfo->pHead;
	
    //��Ϊ������
	if (p == NULL)
	{
		DBG_PRINT((" smallInvInfo->pHead = NULL !"));
		DBG_RETURN(SUCCESS);		
	}
	
	//--------------------------------------------------------------------------
    //��Ϊ�ǿ�����
	//--------------------------------------------------------------------------
	for(UINT8 i=0; i<smallInvInfo->m_sphsl; i++, p = p->pNext)
	{
		//�������ۿ��ʵ���Ʒ�зֳ���������
		invFullInfo->detail[i].Property = p->m_property;    //��Ʒ������
		invFullInfo->detail[i].Amount =  p->m_spsl;			//��Ʒ����		   
		invFullInfo->detail[i].Price = p->m_spdj;			//��Ʒ����		
		invFullInfo->detail[i].Sum = p->m_spje;				//��Ʒ���
		invFullInfo->detail[i].TaxSum = p->m_spse;			//˰��
		invFullInfo->detail[i].TaxItem = p->m_sl;			//˰��
		memcpy((void *)invFullInfo->detail[i].GoodsCode, (void *)p->m_spbm.c_str(), p->m_spbm.length());	//��Ʒ����
		nLen = p->m_spmc.length() + 1;
		memcpy((void *)invFullInfo->detail[i].GoodsName, (void *)p->m_spmc.c_str(), nLen);				//��Ʒ����
		
		DBG_PRINT(("---------------------------------"));
		DBG_PRINT(("��Ʒ������  : %u ", invFullInfo->detail[i].Property));
		DBG_PRINT(("��Ʒ����    : %f ", invFullInfo->detail[i].Amount));
		DBG_PRINT(("��Ʒ����    : %f ", invFullInfo->detail[i].Price));
		DBG_PRINT(("��Ʒ���    : %d ", invFullInfo->detail[i].Sum));
		DBG_PRINT(("��Ʒ˰��    : %d ", invFullInfo->detail[i].TaxSum));
		DBG_PRINT(("��Ʒ˰��    : %f ", invFullInfo->detail[i].TaxItem));
		DBG_PRINT(("��Ʒ����    : %s ", invFullInfo->detail[i].GoodsCode));
		DBG_PRINT(("��Ʒ����    : %s ", invFullInfo->detail[i].GoodsName));
	}
	
	DBG_PRINT(("�˳�InvClassToStuct����"));
	DBG_RETURN(SUCCESS);
}

//------------------------------------------------------
//�������ݿ����ݹ���
//------------------------------------------------------
UINT8 SaleData::RollData(UINT8 &nIfRolled)
{
	CInvHead curInvHead;
	CRtInv curRtInv;
	CInvSum curInvSum;
	
	UINT8 ret = SUCCESS;
	
	UINT32 nInvDelDate = 0;
	UINT32 nSumDelDate = 0;
	UINT32 nRtDetNo = 0;
	nIfRolled = 0;
	
	// 	CInvDet countDet;			//ѹ��������
	// 	countDet.Requery();			//ѹ��������
	// 	countDet.LoadOneRecord();	//ѹ��������
	// 	DBG_PRINT(("��һ����ϸ������invDet.m_kprq = %u", countDet.m_kprq));
	DBG_PRINT(("g_globalArg->m_invCount = %u", g_globalArg->m_invCount));
	DBG_PRINT(("g_globalArg->m_invSumCount = %u", g_globalArg->m_invSumCount));
	
	
	TDateTime lastDate(g_globalArg->m_startDecDate, 000001);
	lastDate--;
	UINT32 nRefDate = lastDate.FormatInt(YYYYMMDD);//�ϴ��걨�Ľ�ֹ����
	
	//�ж��Ƿ���Ҫ������������������ļ�¼����
	ret = curInvHead.CheckRoll(g_globalArg->m_invCount, nRefDate,nInvDelDate);
	if (ret!=SUCCESS)
	{
		DBG_RETURN(FAILURE);
	}
	
	ret = curInvSum.CheckRoll(g_globalArg->m_invSumCount, nRefDate,nSumDelDate);
	if (ret!=SUCCESS)
	{
		DBG_RETURN(FAILURE);
	}
	
	ret = curRtInv.CheckRoll(g_globalArg->m_rtInvCount,nRtDetNo);
	if (ret!=SUCCESS)
	{
		DBG_RETURN(FAILURE);
	}
	
	//���籣�� ��������
	g_YW_PowerOffData->invRollPwOffData.invDatelimit = nInvDelDate;/**<InvHead�����ɾ���Ľ�ֹ����  */ 
	g_YW_PowerOffData->invRollPwOffData.sumDatelimit = nSumDelDate;/**<InvSum�����ɾ���Ľ�ֹ����  */  
	g_YW_PowerOffData->invRollPwOffData.rtNolimit = nRtDetNo;/**<RtInv�����ɾ���Ľ�ֹ����  */   
    g_YW_PowerOffData->invRollPwOffData.nRefDate = nRefDate; /**<�ϴ��걨�Ľ�ֹ����  */ 
	POWOFF_ENABLE();//�������ж�	
	
	UINT8 retRoll;
	BAR_DEF();
	//����
	if (nInvDelDate>0)
	{
		DBG_PRINT(("��Ʊ��Ϣ������..... "));
		BAR_SHOW("��Ʊ��Ϣ������.....");
		retRoll = curInvHead.Roll(nInvDelDate, nRefDate);//InvHead�����
		if (FAILURE==retRoll) 
		{
			BAR_SHOW("��������������ɷ�Ʊ����");
			while (1);
		}
		CGlobalArg::SysLog(EVENT_INVOICE_ROLL , SUCCESS);		//дϵͳ��־
		g_globalArg->m_invCount = curInvHead.GetInvHeadNum();	//InvHead���¼��
		nIfRolled = 1;
		BAR_SHOW("��Ʊ��Ϣ�������!");
	}	
	
	
	if (nSumDelDate>0)
	{
		DBG_PRINT(("�������Ϣ������..... "));
		BAR_SHOW("�������Ϣ������.....");
		curInvSum.Roll(nSumDelDate);//InvSum�����
		CGlobalArg::SysLog(EVENT_VOLUME_ROLL , SUCCESS);//дϵͳ��־
		g_globalArg->m_invSumCount = curInvSum.GetRecordNum();//InvSum���¼��
		nIfRolled = 1;
		BAR_SHOW("�������Ϣ�������!");
	}
	
	
	if (nRtDetNo>0)
	{
		DBG_PRINT(("��Ʊ��Ϣ������..... "));
		BAR_SHOW("��Ʊ��Ϣ������.....");
		curRtInv.Roll(nRtDetNo);//RtInv�����
		CGlobalArg::SysLog(EVENT_RTINV_ROLL , SUCCESS);//дϵͳ��־
		g_globalArg->m_rtInvCount = curRtInv.GetRecordNum();//RtInv���¼��
		nIfRolled = 1;
		BAR_SHOW("��Ʊ��Ϣ�������!");
	}
	
	
	DBG_RETURN(SUCCESS);
}


UINT8 SaleData::GoodsReduct(double money)
{
	UINT8 ret;
	INT64 nReDuctSum;
	
	if (NULL == m_singleInvInfo->pHead) 
	{
		return NO_GOODS;
	}
	
	//�ѽ��������
	nReDuctSum = double2int(money*SUM_EXTENSION*10);		
	nReDuctSum = double2int(nReDuctSum / 10.0);//���õ��Ľ��
	DBG_PRINT((" money = %f��not enough!", money));
	DBG_PRINT((" ȡ���� nReDuctSum = %d!", nReDuctSum));
	
	//����
	if (nReDuctSum <= 0)
	{
		DBG_PRINT((" nReDuctSum = %d��not enough!", nReDuctSum));
		InitSaleData(0);  //������Ϣ��ʼ��
		DBG_RETURN(REDUCT_MONEY_SMALL);
	}
	
	//�޸����һ���ڵ������
	m_invDet = m_singleInvInfo->pEnd;
	if (m_invDet->m_property != DETAIL_GENERAL_GOODS) 
	{
		DBG_PRINT((" ����ͨ��Ʒ�� m_property = %u!", m_invDet->m_property));
		InitSaleData(0);  //������Ϣ��ʼ��
		DBG_RETURN(NO_REDUCT);
	}
	//���ý�����������Ʒ���ܽ��
	if (m_invDet->m_spje <= nReDuctSum) 
	{
		DBG_PRINT((" nReDuctSum = %d��not enough!", nReDuctSum));
		InitSaleData(0);  //������Ϣ��ʼ��
		DBG_RETURN(REDUCT_EXCEED);
	}
	
	m_invDet->m_property = DETAIL_GOODS_REDUCT;//�ĳɴ����õ���Ʒ��
	nReDuctSum = 0 - nReDuctSum;//���õĽ���Ը�����¼
	
	//����һ����㣨�����У�	
	CInvDet *reductDet; 
	reductDet = reductDet->GetNewInvDet();//�Ӿ�̬�����ȡһ�����õ�CInvDet����
	DBG_ASSERT_EXIT((reductDet != NULL), (" reductDet == NULL!"));	
	reductDet->m_spbm = ""; 
	reductDet->m_kplx = m_invDet->m_kplx;
	//	reductDet->m_issuetype = m_invDet->m_issuetype;
	reductDet->m_spbm = m_invDet->m_spbm;
	reductDet->m_spmc = "����";
	reductDet->m_sl = m_invDet->m_sl;	//˰��
	reductDet->m_spsl = m_saveAmount;
	m_invDet->m_dotNum = m_dotNum;
	reductDet->m_spdj = 0;				//??
	reductDet->m_spje = nReDuctSum;
//	reductDet->m_spje = CountTax(((double)reductDet->m_spje)/SUM_EXTENSION,m_invDet->m_sl);
    reductDet->m_spje =CountTax(reductDet->m_spje,(UINT32)(m_invDet->m_sl*SUM_EXTENSION));
	reductDet->m_property = DETAIL_REDUCTION_TEMPLATE;//???������
	//	reductDet->m_backup = "";
	
	m_singleInvInfo->InsertNode(reductDet);		//����ڵ�
	m_singleInvInfo->m_sphsl++;					//��ǰ��Ʊ����Ʒ�м�1
	reductDet = NULL;
	
	
    //----�ж�ʣ�෢Ʊ�����Ƿ���(�������ã���ɾ�������ڵ�)
	UINT32 nInvCount = CalculateInvNum();
	UINT32 nIfReturn = 0; //�Ƿ�ȡ������Ʒ�У�ֹͣ��Ʊ
	if (nInvCount > g_globalArg->m_curInvVol->m_remain)
	{
		//	nIfReturn = 1;
		ret = SHORT_OF_INV; 
		DBG_PRINT((" g_globalArg->m_curInvVol->m_remain = %u !", g_globalArg->m_curInvVol->m_remain));
	}
	if ((nInvCount>1)&&((m_singleInvInfo->m_kplx==RETURN_INV)||(m_singleInvInfo->m_kplx==RET_MANUAL_INV))) 
	 {
	 		nIfReturn = 1;
			ret = RETURN_GOODS_EXCEED;
	 }
// 	if ((nInvCount>1)) //Ϊ��֤�ϴ������ò���
// 	{
// 		nIfReturn = 1;
// 		//	ret = RETURN_GOODS_EXCEED;
// 		ret = ONE_INV;
// 	}
	if (1 == nIfReturn)
	{
		DBG_PRINT((" ȡ��������!"));
		m_singleInvInfo->m_sphsl--;//��ǰ��Ʊ����Ʒ�м�1
		m_singleInvInfo->DelLastNode();	//ɾ���ռ���Ľڵ�
		m_singleInvInfo->pEnd->m_property = DETAIL_GENERAL_GOODS;//�ĳɴ����õ���Ʒ��
		InitSaleData(0);  //������Ϣ��ʼ��
		DBG_RETURN(ret);
	}
	
    //----�ͷſռ�,����
	//��ǰ��Ʊ�ۼƽ������
	m_singleInvInfo->m_kphjje += nReDuctSum;
	m_tmpGoodsNum++;								//��ǰ����Ʒ�м�1
	m_tmpMoneySum += nReDuctSum;					//�����ۼƽ����������н��
	DBG_PRINT((" m_singleInvInfo->m_kphjje = %u !", m_singleInvInfo->m_kphjje));
	
	InitSaleData(0);  //������Ϣ��ʼ��
	
    ret = SUCCESS;
	DBG_PRINT((" GoodsReduct Succeed !"));
	DBG_RETURN(ret);
	
}
#if 0
UINT8 SaleData::InvSum(UINT8 &nIfSum)
{
	DBG_ENTER("SaleData::InvSum");
	
	nIfSum = 0;
	UINT8  ret = SUCCESS;
	string strTmp;
	char chValue[256], chTmpValue[128];
	memset((void*)chValue, 0, sizeof(chValue));
	memset((void*)chTmpValue, 0, sizeof(chTmpValue));
	
	CInvHead sumInvHead;
	CInvDet  sumInvDet; 
	CInvSum  sumInvSum;
	CInvVol  sumInvVol;
	
	CInvHead *pInvHead = &sumInvHead;
	CInvDet  *pInvDet = &sumInvDet; 
	CInvSum  *pInvSum = &sumInvSum;
	CInvVol  *pInvVol = &sumInvVol;
	DBG_ASSERT_EXIT((pInvHead != NULL)&&(pInvDet != NULL), (" pInvHead == NULL or pInvDet = NULL "));
    DBG_ASSERT_EXIT((pInvSum != NULL), (" pInvSum == NULL!"));
	DBG_ASSERT_EXIT((pInvVol != NULL), (" pInvVol == NULL!"));
	
    if (!((0==g_globalArg->m_curInvVol->m_usedflag)&&(1==g_globalArg->m_curInvVol->m_overflag))) 
	{
		DBG_PRINT(("û�е���ķ�Ʊ��"));
		DBG_RETURN(SUCCESS);		
    }
	
	//��Ʊ���룬��ʼ���룬��ֹ����
    pInvSum->m_code = g_globalArg->m_curInvVol->m_code;
    pInvSum->m_InvStartNo = g_globalArg->m_curInvVol->m_isno;
	pInvSum->m_InvEndNo = g_globalArg->m_curInvVol->m_ieno;
	
	sprintf(chValue, "where CODE = '%s' and IS_NO = %u",pInvSum->m_code.c_str(),pInvSum->m_InvStartNo);
	pInvSum->m_filter = chValue;
	pInvSum->Requery();
	if ((pInvSum->LoadOneRecord())==SQLITE_OK) 
	{
		DBG_PRINT(("�þ��ѻ���"));
		pInvHead = NULL;
		pInvDet = NULL;	
		pInvSum = NULL;
		pInvVol = NULL;
		DBG_RETURN(SUCCESS);
	}
	
    //��Ʊ����Ʊ����Ʊ����
	pInvHead->m_filter = "";
	sprintf(chValue, "where FPHM>=%u and FPHM<=%u and FPDM= '%s'",pInvSum->m_InvStartNo,pInvSum->m_InvEndNo,pInvSum->m_code.c_str());
    pInvHead->m_filter.append(chValue);
	pInvHead->GetInvoiceSum(pInvSum->m_normalInvSum, pInvSum->m_returnInvSum, pInvSum->m_wasteInvSum);
    
    DBG_PRINT(("pInvSum->m_normalInvSum = %u", pInvSum->m_normalInvSum));
    DBG_PRINT(("pInvSum->m_returnInvSum = %u", pInvSum->m_returnInvSum));
	DBG_PRINT(("pInvSum->m_wasteInvSum = %u", pInvSum->m_wasteInvSum));
	
	//��Ʊ�ܽ��
	strTmp = "";
	strTmp = "select sum(KPHJJE) from INV_HEAD "; 
	strTmp.append(chValue);
	sprintf(chTmpValue, " and KPLX = %u",NORMAL_INV);
	strTmp.append(chTmpValue);
    pInvHead->SetSQL(strTmp);
	pInvHead->GetOneResult(DB_UINT32, (void*)&(pInvSum->m_nomalMoneySum)); 
    
	//��Ʊ�ܽ��
	strTmp = "";
	strTmp = "select sum(KPHJJE) from INV_HEAD "; 
	strTmp.append(chValue);
	sprintf(chTmpValue, " and (KPLX = %u or KPLX = %u or KPLX = %u)",RETURN_INV, RET_MANUAL_INV, RET_SPECIAL_INV);
	strTmp.append(chTmpValue);
    pInvHead->SetSQL(strTmp);
	pInvHead->GetOneResult(DB_UINT32, (void*)&(pInvSum->m_returnMoneySum)); 
	
	//��Ʊ��ʼ����
    strTmp = "";
	strTmp = "select KPRQ from INV_HEAD "; 
	//	sprintf(chValue, "where INV_NO=%u and CODE_NO=%u",pInvSum->m_InvStartNo,pInvSum->m_codeNo);
	sprintf(chValue, "where FPHM>=%u and FPDM= '%s'",pInvSum->m_InvStartNo,pInvSum->m_code.c_str());
	strTmp.append(chValue);
    pInvHead->SetSQL(strTmp);
	pInvHead->GetOneResult(DB_UINT32, (void*)&(pInvSum->m_issueStartDate)); 
    
	//��Ʊ��ֹ����
	strTmp = "";
	strTmp = "select KPRQ from INV_HEAD "; 
	sprintf(chValue, "where FPHM=%u and FPDM= '%s'",pInvSum->m_InvEndNo,pInvSum->m_code.c_str());
	strTmp.append(chValue);
    pInvHead->SetSQL(strTmp);
	pInvHead->GetOneResult(DB_UINT32, (void*)&(pInvSum->m_issueEndDate)); 
	
	//��Ӽ�¼
    pInvSum->AddNew();
	
	//�޸ķ�Ʊ������Ϣ
	strTmp = "";
	strTmp = "update INV_VOL set OVER_FLAG = 0 "; 
    sprintf(chValue, "where IS_NO=%u and CODE= '%s'",pInvSum->m_InvStartNo,pInvSum->m_code.c_str());
    strTmp.append(chValue);
	DBG_PRINT(("strTmp = %s", strTmp.c_str()));
	pInvVol->SetSQL(strTmp);
    if(pInvVol->ExecuteSQL()!= SQLITE_OK)
	{
		DBG_PRINT(("�޸ķ�Ʊ������Ϣʧ�ܣ�"));
		ret = FAILURE;
	}
	
	
    pInvHead = NULL;
	pInvDet = NULL;
	pInvSum = NULL;
	pInvVol = NULL;
	
	nIfSum = 1;//�ɹ������˾����
	g_globalArg->m_curInvVol->m_overflag = 0;//��ǰ��������
	(g_globalArg->m_invSumCount)++; //��¼��������
	//	g_globalArg->m_normalVolSum = 0;//��Ʊ����Ʊ�ۼƽ������
	//	g_globalArg->m_returnVolSum = 0;//��Ʊ���Ʊ�ۼƽ������
	//	DBG_PRINT(("*****g_globalArg->m_normalVolSum  = %d", g_globalArg->m_normalVolSum ));
	//	DBG_PRINT(("*****g_globalArg->m_returnVolSum  = %d", g_globalArg->m_returnVolSum ));
	DBG_RETURN(ret);
	
}
#endif

// �ж����߽��������������������
UINT8 SaleData::IsOffLineOk(INT64 nSum, string& strErr)
{
#if 0
	//�Ƿ񳬷�Ʊ����
	DBG_PRINT(("m_InvServNum = %u, m_nNum = %u", g_globalArg->m_InvServNum, g_globalArg->m_invKind->m_nNum));
	if ((g_globalArg->m_InvServNum+1) > g_globalArg->m_invKind->m_nNum) 
	{
		DBG_PRINT(("���߿�Ʊ��������"));
		strErr = "���߿�Ʊ��������";
		return GX_SV_NUM_EXCEED;
	}
	
	//�Ƿ񳬷�Ʊ���
	if ((g_globalArg->m_InvServSum+nSum) > g_globalArg->m_invKind->m_nSum) 
	{
		DBG_PRINT(("���߿�Ʊ���� m_InvServSum = %u", g_globalArg->m_InvServSum));
		strErr = "���߿�Ʊ����";
		return GX_SV_SUM_EXCEED;
	}
	
	
	//�Ƿ񳬹���Ʊʱ��  
	CInvServ invServ;
	//	invServ.m_filter = "where UP_FLAG = 0 ";//��һ��δ�ϴ��ķ�Ʊ
	invServ.Requery();
	UINT8 errCode = invServ.LoadOneRecord();
	if (SQLITE_DONE == errCode)
	{
		return SUCCESS;
	}
	else if (SQLITE_OK != errCode) 
	{
		DBG_PRINT(("Requery INV_SERV error = %d", errCode));
		strErr = "��ѯ��Ʊ��������";
		return GX_SV_TIME_EXCEED;
	}
	
	// 	TDateTime fDate(invServ.m_issueDate, invServ.m_issueTime);
	// 	fDate += (INT32)(g_globalArg->m_invKind->m_nTime);//���߽�ֹ����
	// 	DBG_PRINT(("���߽�ֹ�� = %s", fDate.FormatString(YYYYMMDDHHMMSS).c_str()));
	// 	
	// 	TDateTime curDate = TDateTime::CurrentDateTime();
	// 	if (curDate > fDate) 
	// 	{
	// 		DBG_PRINT(("���߿�Ʊʱ�䳬��"));
	// 		DBG_PRINT(("Eg_globalArg->m_usermore->m_nTime = %"));
	// 		strErr = "���߿�Ʊʱ�䳬��";
	// 		return GX_SV_TIME_EXCEED;		
	// 	}
	
	
	TDateTime fDate(invServ.m_issueDate, invServ.m_issueTime);
	//fDate = fDate.HourAdd(fDate, g_globalArg->m_invKind->m_nTime);
	DBG_PRINT(("���߽�ֹʱ�� = %s", fDate.FormatString(YYYYMMDDHHMMSS).c_str()));
	// 	UINT32 nfHour = fDate.Hour();
	// 	DBG_PRINT(("nfHour = %u", nfHour));
	// 	
	// 	UINT32 nDay = (nfHour + g_globalArg->m_invKind->m_nTime)/24;
	// 	UINT32 nHour = (nfHour + g_globalArg->m_invKind->m_nTime)%24;
	// 	DBG_PRINT(("g_globalArg->m_invKind->m_nTime = %u", g_globalArg->m_invKind->m_nTime));	
	// 	DBG_PRINT(("nDay = %u", nDay));	
	// 	DBG_PRINT(("nHour = %u", nHour));
	
	// 	fDate += nDay;//����ʱ��Ľ�ֹ����
	// 	UINT32 fMinute = fDate.Minute();
	// 	UINT32 fSecond = fDate.Second();
	// 
	// 
	// 
	// 	fDate.ComposeTime(nHour, fMinute, fSecond);//����ʱ��Ľ�ֹʱ��
	TDateTime curDate = TDateTime::CurrentDateTime();
	// 	if (NULL != pEndDate) 
	// 	{
	// 		*pEndDate = fDate;
	// 		DBG_PRINT(("*pEndDate = %s", (*pEndDate).FormatString(YYYYMMDDHHMMSS).c_str()));
	// 	}
	DBG_PRINT(("���߿�Ʊʱ�䳬��, fDate = %s", fDate.FormatString(YYYYMMDDHHMMSS).c_str()));
	DBG_PRINT(("��ǰʱ��, curDate = %s", curDate.FormatString(YYYYMMDDHHMMSS).c_str()));
	if (curDate > fDate) 
	{
		// 		DBG_PRINT(("���߿�Ʊʱ�䳬��, fDate = %s", fDate.FormatString(YYYYMMDDHHMMSS).c_str()));
		// 		DBG_PRINT(("���߿�Ʊʱ�䳬��, curDate = %s", curDate.FormatString(YYYYMMDDHHMMSS).c_str()));
		//		nM2MRet = wmmp_trapAlarmCode(M2M_EXCD_SV_TIME);
		//		DBG_PRINT((" nM2MRet = %d!", nM2MRet));
		DBG_PRINT(("g_globalArg->m_invKind->m_nTime = %u", g_globalArg->m_invKind->m_nTime));
		strErr = "���߿�Ʊʱ�䳬��";
		return GX_SV_TIME_EXCEED;	
	}
#endif	
	return SUCCESS;
}

/*
//������Ʒ˰��
INT64 SaleData::CountTax(double fJe, double fSl)
{
	DBG_ENTER("SaleData::CountTax");
	
	DBG_PRINT(("fJe= %.4f",fJe));
	DBG_PRINT(("fSl= %.4f",fSl));
    INT64 nSe =0;

	double fTmp =0.0;
	
	fTmp =fSl;
    fTmp += 1.0;
	DBG_PRINT(("fTmp= %.4f",fTmp));
	
	fTmp  = fJe / fTmp;
	DBG_PRINT(("fTmp= %.4f",fTmp));
	
	fTmp *= fSl;
    DBG_PRINT(("fTmp= %.4f",fTmp));
		
    nSe =double2int(fTmp*PRICE_EXTENSION);
	DBG_PRINT(("nSe= %u",nSe));
	
	return nSe;
	
}
*/

//������Ʒ˰��
INT64 SaleData::CountTax(INT64 nJe, INT32 nSl)
{
	DBG_ENTER("SaleData::CountTax");
	
	DBG_PRINT(("nJe= %lld",nJe));
	DBG_PRINT(("nSl= %d",nSl));
    INT64 nSe =0;
	
	INT64 nTmp =0;
	
	nTmp =nSl;
    nTmp += SUM_EXTENSION;
	DBG_PRINT(("nTmp= %lld",nTmp));

	double fTmp= (double)(nJe*1.0) / nTmp;
	DBG_PRINT(("fTmp= %.4f",fTmp));

	nTmp  = double2int(fTmp*SUM_EXTENSION);
	
	DBG_PRINT(("nTmp= %lld",nTmp));
	
	nSe = nJe-nTmp;

	DBG_PRINT(("nSe= %lld",nSe));
	
	return nSe;
	
}