/****************************************************************************
�ļ���           ��APIBase.h
����             ��awe4000rҵ�����̳�����
��ʼ����         ��
����             �� 
****************************************************************************/

#ifndef API_BASE_H
#define API_BASE_H

#include "YWXMLGY.h"
#include "YWXmlBase.h"
#include "CUserInfo.h"
#include "CInvHead.h"
#include "CInvKind.h"
#include "CInvVol.h"
#include "CNetPara.h"
#include "CTax.h"
#include "CTjxxhz.h"

//ҵ�����̵��ú����ӿڷ�ʽ
#define SKJ_MODE	1		//�տ��ֱ�����ýӿ�
#define ZHQ_MODE	2		//ת������ʽ���ýӿ�
#define TYPE_MODE	ZHQ_MODE


#include "CNetPara.h"



class CAPIBase;
extern CAPIBase *g_pAPIBase;


class CAPIBase
{
public:

	static void InitAPI();

	/*!
	@brief ��ȡ˰���豸���		
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 GetSksbbh_API(CYWXML_GY &ywxml_gy, string &sksbbh, string &bspbh, string &qtxx, string &strErr)=0;

	/*!
	@brief ��ȡ˰���豸��Ϣ		
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 GetTaxpayerInfo_API(CYWXML_GY &ywxml_gy, CUserInfo &UserInfo, string &strCurTime, string &strErr)=0;
	
	/*!
	@brief ��ȡ��˰����Ϣ		
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 GetBSPInfo_API(CYWXML_GY &ywxml_gy, CUserInfo &userInfo, string &strErr)=0;

	/*!
	@brief ��ȡ�������		
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 GetJKSJ_API(CYWXML_GY &ywxml_gy, CInvKind &InvKind, string &strErr)=0;

	/*!
	@brief ��ȡ˰����Ϣ		
	@param[in] pTax ˰��������
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 GetTaxRateInfo_API(CYWXML_GY &ywxml_gy, CTax *pTax, UINT8 &taxNum, string &strErr)=0;

	/*!
	@brief ��˰�̿�����
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 SKPKLBG_API(CYWXML_GY &ywxml_gy, string ykl, string xkl, string &strErr)=0;


	/*!
	@brief ���֤�����
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 BGZSKL_API(CYWXML_GY &ywxml_gy, string ykl, string xkl, string &strErr)=0;



	/*!
	@brief ����������Ϣ		
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 LXXXUpdatePro_API(CYWXML_GY &ywxml_gy, string &strErr)=0;


	/*!
	@brief ����	
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 OnLine(string &strErr) = 0;

	/*!
	@brief ���ò�����	
	@param[in] ������
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 SetBaudRate(UINT32 btl, string &strErr) = 0;

	/*!
	@brief �������ά��
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 NetParaManage_API(CNetPara *pNetPara, string &strErr)=0;
	
	/*!
	@brief ��˰�̷�Ʊ��ѯ����Ʊ����Ϣ��ѯ��
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 BSPFPCXPro_API(CYWXML_GY &ywxml_gy, UINT32 &InvCount, CInvVol *pInvVol, string &strErr)=0;


	/*!
	@brief ��Ʊ�ַ���������
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 ZJInvDistribute_API(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, UINT8 strJzlx, string &strErr)=0;

	/*!
	@brief ��Ʊ�ջأ�������
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/

	virtual INT32 ZJInvRecover_API(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, UINT8 strJzlx, string &strErr)=0;

	/*!
	@brief ��Ʊ�˻أ��ֻ���
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 FJInvReturn_API(CYWXML_GY &ywxml_gy, UINT8 strJzlx, string &strErr)=0;

	/*!
	@brief ͳ����Ϣ��ѯ
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 TJXXCXPro_API(CYWXML_GY &ywxml_gy, CTjxxhz *pTjxxhz, string &strErr)=0;
	
	/*!
	@brief ���ʹ�Ʊ(��Ʊ����)
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 InvReadIn_API(CYWXML_GY &ywxml_gy, UINT8 strJzlx, string &strErr)=0;

	/*!
	@brief ������ȡ��Ʊ��������
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 WLLQFPPro_API(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, string &strErr)=0;

	/*!
	@brief ������ȡ��Ʊ���ȷ�ϣ�������
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 WLLQFPJGQRPro_API(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, string &strErr)=0;

	/*!
	@brief ��Ʊ��Ϣ��ѯ����ȡ��ǰƱ�ţ�
	@param[in] 
	@param[out] pInvVol  ��Ʊ��Ϣ��
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 GetCurInvInfo_API(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, string &strErr)=0;
	
	/*!
	@brief ��Ʊ���ߣ�������Ʊ����Ʊ��		
	@param[in] invhead			��Ʊͷ��Ϣ
	@param[out] taxCode   	˰���루20�ֽڣ�
	@param[out] strErr   		������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 MakeNormalInv_API(CYWXML_GY &ywxml_gy, CInvHead *pInvHead, string &strErr)=0;
	
	/*!
	@brief ��Ʊ���ϣ��հ׷�Ʊ���ѿ�Ʊ���ϣ�
	@param[in] invhead	��Ʊͷ��Ϣ
	@param[in] zflx   ��������	0���հ׷�Ʊ����	1���ѿ���Ʊ����
	@param[out] strErr   		������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 MakeWasteInv_API(CYWXML_GY &ywxml_gy, CInvHead *pInvHead, UINT8 zflx, string &strErr)=0;
	
	/*!
	@brief ��Ʊ��ѯ
	@param[in] cxfs	��ѯ��ʽ
	@param[in] cxtj	��ѯ����
	@param[out] invNum  ��Ʊ����
	@param[in/out] invhead	��Ʊͷ��Ϣ
	@param[out] strErr   		������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 GetInvHeadInfo_API(CYWXML_GY &ywxml_gy, UINT8 cxfs, string cxtj, UINT32 &invNum, CInvHead *pInvhead, string &strErr)=0;
	
	/*!
	@brief ��Ʊʵʱ�ϴ�
	@param[out] strErr   		������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 InvoiceUpload_API(CYWXML_GY &ywxml_gy, string &strErr)=0;

		/*!
	@brief ���糭��
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 NetDeclareProc_API(CYWXML_GY &ywxml_gy, string &strErr)=0;

	/*!
	@brief ���ʳ���������ʱ��ʾѡ���˰�̻��߱�˰�̣�
	@param[in] jzlx �������� 2����˰�� 3����˰�� 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 DeclareProc_API(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr)=0;

	/*!
	@brief �����忨
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 NetUpdateTaxProc_API(CYWXML_GY &ywxml_gy, string &strErr)=0;

	/*!
	@brief ��˰���忨
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	virtual INT32 UpdateTaxProc_API(CYWXML_GY &ywxml_gy, string &strErr)=0;

	/*!
	@brief  ��Ʊ��¼
	@param[in] ywxml_gy	��������
	@param[in] bsqsrq	��˰��ʼ����
	@param[in] bszhrq	��˰��ֹ����
	@param[out] strErr	������Ϣ
	*/
	virtual INT32 Fpbl_API(CYWXML_GY &ywxml_gy, UINT32 bsqsrq, UINT32 bszzrq, string &strErr)=0;

	/*!
	@brief  ��ȡ�����������
	@param[out] wscfpzs		δ�ϴ���Ʊ����
	@param[out] wscfpsj		δ�ϴ���Ʊʱ��
	@param[out] wscfpljje	δ�ϴ���Ʊ�ۼƽ��
	@param[out] sczs		�ϴ�����
	@param[out] scsjjg		�ϴ�ʱ����
	@param[out] strErr		������Ϣ
	*/
	virtual INT32 Hqlxsj_API(string &wscfpzs, string &wscfpsj, string &wscfpljje, string &sczs, string &scsjjg, string &strErr)=0;
	
};


#endif


