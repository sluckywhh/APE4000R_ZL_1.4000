
#include "APIzhqProc.h"

#include <sys/timeb.h>
#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#if TYPE_MODE == ZHQ_MODE

CAPIzhqProc::CAPIzhqProc()
{
	
}

CAPIzhqProc::~CAPIzhqProc()
{
	
}


INT32 CAPIzhqProc::OnLine(string &strErr)
{
	UINT8 ret = SUCCESS;
	
	UINT64 fTime, fTime2;
	struct timeb tp;
	ftime(&tp);
	
	fTime = tp.time * 1000 + tp.millitm;
	DBG_PRINT(("1 ����������ʼʱ��, fTime = %llu ", fTime));

	ret = m_SerialProc.onLine_Serial(strErr);
	
	ftime(&tp);
	fTime2 = tp.time * 1000 + tp.millitm;
	DBG_PRINT(("2 ������������ʱ��  fTime2 - fTime = %llu ", (fTime2 - fTime)));
	

	return ret;
}

INT32 CAPIzhqProc::SetBaudRate(UINT32 btl, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.setBaudRate_Serial(btl, strErr);
	
	return ret;
}

/*!
��ȡ˰���豸���		
*/
INT32  CAPIzhqProc::GetSksbbh_API(CYWXML_GY &ywxml_gy, string &sksbbh, string &bspbh, string &qtxx, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.skpbhcx_Serial(ywxml_gy, sksbbh, strErr);
	if (ret != SUCCESS)
	{
		return ret;
	}
	
	ret = m_SerialProc.bspbhcx_Serial(ywxml_gy, bspbh, strErr);
	return ret;
}

/*!
��ȡ˰���豸��Ϣ		
*/
INT32  CAPIzhqProc::GetTaxpayerInfo_API(CYWXML_GY &ywxml_gy, CUserInfo &UserInfo, string &strCurTime, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.skpxxcx_Serial(ywxml_gy, UserInfo, strCurTime, strErr);
	
	return ret;
}

/*!
��ȡ��˰����Ϣ		
*/
INT32  CAPIzhqProc::GetBSPInfo_API(CYWXML_GY &ywxml_gy, CUserInfo &userInfo, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.bspxxcx_Serial(ywxml_gy, userInfo,  strErr);
	
	return ret;
}

/*!
��ȡ�������		
*/
INT32  CAPIzhqProc::GetJKSJ_API(CYWXML_GY &ywxml_gy, CInvKind &InvKind, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.jksjcx_Serial(ywxml_gy, InvKind,  strErr);
	
	return ret;
}

/*!
��ȡ˰����Ϣ		
*/
INT32  CAPIzhqProc::GetTaxRateInfo_API(CYWXML_GY &ywxml_gy, CTax *pTax, UINT8 &taxNum, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.sqslcx_Serial(ywxml_gy, pTax, taxNum, strErr);
	
	return ret;
}

/*!
��˰�̿�����
*/
INT32  CAPIzhqProc::SKPKLBG_API(CYWXML_GY &ywxml_gy, string ykl, string xkl, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.sksbklgg_Serial(ywxml_gy, ykl, xkl, strErr);
	
	return ret;
}
/*!
@brief ���֤�����
*/
INT32 CAPIzhqProc::BGZSKL_API(CYWXML_GY &ywxml_gy, string ykl, string xkl, string &strErr)
{
	INT32 ret = SUCCESS;
	
	
	ret= m_SerialProc.zsklgg_Serial(ywxml_gy, ykl, xkl, strErr);
	
	if (ret !=SUCCESS)
	{
		return FAILURE;
	}
	
	return ret;
	
}
/*!
����������Ϣ		
*/
INT32  CAPIzhqProc::LXXXUpdatePro_API(CYWXML_GY &ywxml_gy, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.lxqxgx_Serial(ywxml_gy, strErr);
	
	return ret;
}


/*!
�������ά��
*/
INT32  CAPIzhqProc::NetParaManage_API(CNetPara *pNetPara, string &strErr)
{
	UINT8 ret = SUCCESS;

	ret = m_SerialProc.wlcswh_Serial(pNetPara, strErr);

	return ret;
}


/*!
��˰�̷�Ʊ��ѯ����Ʊ����Ϣ��ѯ��
*/
INT32  CAPIzhqProc::BSPFPCXPro_API(CYWXML_GY &ywxml_gy, UINT32 &InvCount, CInvVol *pInvVol, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	DBG_PRINT(("��ȡ�������InvCount = %u", InvCount));
	ret = m_SerialProc.bspfpcx_Serial(ywxml_gy, InvCount, pInvVol, strErr);
	
	return ret;
}

/*!
��Ʊ�ַ���������
*/
INT32  CAPIzhqProc::ZJInvDistribute_API(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, UINT8 strJzlx, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	DBG_PRINT(("ywxml_gy.m_fplxdm : %s", ywxml_gy.m_fplxdm.c_str()));
	
	ret = m_SerialProc.fpff_Serial(ywxml_gy, strJzlx, pInvVol, strErr);
	
	return ret;
}

/*!
��Ʊ���գ�������
*/

INT32  CAPIzhqProc::ZJInvRecover_API(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, UINT8 strJzlx, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.fphs_Serial(ywxml_gy, pInvVol, strJzlx, strErr);
	
	return ret;
}

/*!
��Ʊ�˻أ��ֻ���
*/
INT32  CAPIzhqProc::FJInvReturn_API(CYWXML_GY &ywxml_gy, UINT8 strJzlx, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.fjth_Serial(ywxml_gy, strJzlx, strErr);
	
	return ret;
}

/*!
ͳ����Ϣ��ѯ
*/
INT32 CAPIzhqProc::TJXXCXPro_API(CYWXML_GY &ywxml_gy, CTjxxhz *pTjxxhz, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.fptjcx_Serial(ywxml_gy, pTjxxhz, strErr);
	
	return ret;
}

/*!
���ʹ�Ʊ(��Ʊ����)
*/
INT32  CAPIzhqProc::InvReadIn_API(CYWXML_GY &ywxml_gy, UINT8 strJzlx, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.fpdr_Serial(ywxml_gy, strJzlx, strErr);
	
	return ret;
}

/*!
������ȡ��Ʊ��������
*/
INT32  CAPIzhqProc::WLLQFPPro_API(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.wlgp_Serial(ywxml_gy, pInvVol, strErr);
	
	return ret;
}

/*!
������ȡ��Ʊ���ȷ�ϣ�������
*/
INT32  CAPIzhqProc::WLLQFPJGQRPro_API(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, string &strErr)
{
	UINT8 ret = SUCCESS;
	//������ȡ��ƱWLLQFPPro_API �ڲ��Ѿ�ʵ�֣�ת����û���ṩ�˽ӿڣ����UI��ȷ���Ƿ�ʹ�ô˽ӿ�
	
	//	ret = m_SerialProc.wlgp_Serial(ywxml_gy, pInvVol, strErr);
	
	return ret;
}

/*!
��Ʊ��Ϣ��ѯ����ȡ��ǰƱ�ţ�
*/
INT32  CAPIzhqProc::GetCurInvInfo_API(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.gpxxcx_Serial(ywxml_gy, pInvVol, strErr);
	
	return ret;
}

/*!
��Ʊ���ߣ�������Ʊ����Ʊ��		
*/
INT32  CAPIzhqProc::MakeNormalInv_API(CYWXML_GY &ywxml_gy, CInvHead *pInvHead, string &strErr)
{
	UINT8 ret = SUCCESS;
	

	UINT64 fTime, fTime2;
	struct timeb tp;
	ftime(&tp);
	
	fTime = tp.time * 1000 + tp.millitm;
	DBG_PRINT(("1 ��Ʊ��ʼʱ��, fTime = %llu ", fTime));
	
	ret = m_SerialProc.fpkj_Serial(ywxml_gy, pInvHead, strErr);
	
	ftime(&tp);
	fTime2 = tp.time * 1000 + tp.millitm;
	DBG_PRINT(("2 ��Ʊ����ʱ��  fTime2 - fTime = %llu ", (fTime2 - fTime)));

	return ret;
}

/*!
��Ʊ���ϣ��հ׷�Ʊ���ѿ�Ʊ���ϣ�
*/
INT32  CAPIzhqProc::MakeWasteInv_API(CYWXML_GY &ywxml_gy, CInvHead *pInvHead, UINT8 zflx, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.fpzf_Serial(ywxml_gy, pInvHead, zflx, strErr);
	
	return ret;
}

/*!
��Ʊ��ѯ
*/
INT32  CAPIzhqProc::GetInvHeadInfo_API(CYWXML_GY &ywxml_gy, UINT8 cxfs, string cxtj, UINT32  &invNum, CInvHead *pInvhead, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.fpcx_Serial(ywxml_gy, cxfs, cxtj, invNum, pInvhead, strErr);
	
	return ret;
}

/*!
��Ʊʵʱ�ϴ�
*/
INT32  CAPIzhqProc::InvoiceUpload_API(CYWXML_GY &ywxml_gy, string &strErr)
{
	UINT8 ret = SUCCESS;
	UINT8 czlx = 0; //0:δ�ϴ���Ʊ�ϴ�
	UINT32 fpzs = 1; //ÿ���ϴ�һ�ŷ�Ʊ
	ret = m_SerialProc.fpsssc_Serial(ywxml_gy, czlx, fpzs, strErr);
	
	return ret;
}

/*!
���糭��
*/
INT32  CAPIzhqProc::NetDeclareProc_API(CYWXML_GY &ywxml_gy, string &strErr)
{
	UINT8 ret = SUCCESS;
	UINT32 jzlx = 1; //1�����磨˰�������˰�̣�
	//	2��˰���豸����˰��ר�ã�
	
	
	ret = m_SerialProc.sjcb_Serial(ywxml_gy, jzlx, strErr);
	return ret;
}

/*!
���ʳ���������ʱ��ʾѡ���˰�̻��߱�˰�̣�
*/
INT32  CAPIzhqProc::DeclareProc_API(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	DBG_PRINT(("ywxml_gy.m_nsrsbh : %s", ywxml_gy.m_nsrsbh.c_str()));
	DBG_PRINT(("ywxml_gy.m_sksbbh : %s", ywxml_gy.m_sksbbh.c_str()));
	DBG_PRINT(("ywxml_gy.m_sksbkl : %s", ywxml_gy.m_sksbkl.c_str()));
	DBG_PRINT(("ywxml_gy.m_fplxdm : %s", ywxml_gy.m_fplxdm.c_str()));
	DBG_PRINT(("ywxml_gy.m_jqbh : %s", ywxml_gy.m_jqbh.c_str()));
	if (jzlx ==2)
	{
		ret = m_SerialProc.sjcb_Serial(ywxml_gy, jzlx, strErr);  //��˰��
	}
	else if(jzlx == 1)
	{
		UINT8 czlx=1;	//1�����ݳ���
						//2���������
						//3����д��Ʊ��Ϣ
						//4��У׼˰���豸ʱ��
		ret =m_SerialProc.skpbspzhcz_Serial(ywxml_gy, czlx, strErr); //��˰��
	}
	
	
	return ret;
}

/*!
�����忨
*/
INT32  CAPIzhqProc::NetUpdateTaxProc_API(CYWXML_GY &ywxml_gy, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.wljkhc_Serial(ywxml_gy, strErr);
	
	return ret;
}


/*!
��˰���忨
*/
INT32  CAPIzhqProc::UpdateTaxProc_API(CYWXML_GY &ywxml_gy, string &strErr)
{
	UINT8 ret = SUCCESS;
	UINT8 czlx = 2;		//1�����ݳ���
						//2���������
						//3����д��Ʊ��Ϣ
						//4��У׼˰���豸ʱ��

	ret = m_SerialProc.skpbspzhcz_Serial(ywxml_gy, czlx, strErr);
	
	return ret;
}

/*!
��Ʊ��¼
*/
INT32 CAPIzhqProc::Fpbl_API(CYWXML_GY &ywxml_gy, UINT32 bsqsrq, UINT32 bszzrq, string &strErr)
{
	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.fpbl_Serial(ywxml_gy, bsqsrq, bszzrq, strErr);
	
	return ret;
}


/*!
 ��ȡ��������
*/
INT32 CAPIzhqProc::Hqlxsj_API(string &wscfpzs, string &wscfpsj, string &wscfpljje, string &sczs, string &scsjjg, string &strErr)
{

	UINT8 ret = SUCCESS;
	
	ret = m_SerialProc.hqlxsj_Serial(wscfpzs, wscfpsj, wscfpljje, sczs, scsjjg, strErr);
	
	return ret;
}

#endif

