#ifndef BUSINESS_SERIAL_PROC_H
#define BUSINESS_SERIAL_PROC_H

#include <string>
#include <string.h>
#include <stdio.h>
#include "comdatatype.h"
#include "DataDesign.h"
#include "SerialProtocol.h"
#include "CUserInfo.h"
#include "CInvKind.h"
#include "CInvVol.h"
#include "CInvHead.h"
#include "CInvDet.h"
#include "CTax.h"
#include "CTjxxhz.h"
#include "CNetPara.h"

#include "YWXMLGY.h"

using namespace std;

/**
 *@class CBusinessSerialProc
 *@brief �������ݷ���
 */
class CBusinessSerialProc {
private:
	UINT8 ret;
	string sksbbhstr;
	string bspbhstr;
	string qtxx;
	string strErr;

	SerialProtocol* m_serialProtocol;

public:
	CBusinessSerialProc();
	~CBusinessSerialProc();
	

/*!
@brief  ��������
@param[in] 
@param[out] strErr	������Ϣ
*/
UINT8 onLine_Serial(string &strErr);


/*!
@brief  ˰���̱�Ų�ѯ
@param[in] ywxml_gy	��������
@param[out] sksbbh	˰���豸���
@param[out] strErr	������Ϣ
*/
UINT8 skpbhcx_Serial(CYWXML_GY &ywxml_gy, string &sksbbh, string &strErr);


/*!
@brief  ��˰�̱�Ų�ѯ
@param[in] ywxml_gy	��������
@param[out] bspbh	˰���豸���
@param[out] strErr	������Ϣ
*/
UINT8 bspbhcx_Serial(CYWXML_GY &ywxml_gy, string &bspbh, string &strErr);


/*!
@brief  ˰������Ϣ��ѯ
@param[in] ywxml_gy	��������
@param[out] UserInfo	��˰����Ϣ
@param[out] strCurTime	��ǰʱ��
@param[out] strErr	������Ϣ
*/
UINT8 skpxxcx_Serial(CYWXML_GY &ywxml_gy, CUserInfo &UserInfo, string &strCurTime, string &strErr);

/*!
@brief  ��˰����Ϣ��ѯ
@param[in] ywxml_gy	��������
@param[out] UserInf	��˰����Ϣ
@param[out] strErr	������Ϣ
*/
UINT8 bspxxcx_Serial(CYWXML_GY &ywxml_gy, CUserInfo &UserInfo, string &strErr);


/*!
@brief  ������ݲ�ѯ
@param[in] ywxml_gy	��������
@param[out] InvKind	Ʊ����Ϣ
@param[out] strErr	������Ϣ
*/
UINT8 jksjcx_Serial(CYWXML_GY &ywxml_gy, CInvKind &InvKind, string &strErr);


/*!
@brief  ��Ȩ˰�ʲ�ѯ
@param[in] ywxml_gy	��������
@param[out] pTax	˰����Ϣ
@param[out] taxNum	˰�ʸ���
@param[out] strErr	������Ϣ
*/
UINT8 sqslcx_Serial(CYWXML_GY &ywxml_gy, CTax *pTax, UINT8 &taxNum, string &strErr);


/*!
@brief  ��Ʊ��Ϣ��ѯ
@param[in] ywxml_gy	��������
@param[out] pInvVol	��Ʊ������Ϣ
@param[out] strErr	������Ϣ
*/
UINT8 gpxxcx_Serial(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, string &strErr);


/*!
@brief  ˰���豸�������
@param[in] ywxml_gy	��������
@param[in] ykl	ԭ����
@param[in] xkl	�¿���
@param[out] strErr	������Ϣ
*/
UINT8 sksbklgg_Serial(CYWXML_GY &ywxml_gy, string ykl, string xkl, string &strErr);


/*!
@brief  ��Ʊ����
@param[in] ywxml_gy	��������
@param[in & out] pInvHead	��Ʊ��Ϣ
@param[out] strErr	������Ϣ
*/
UINT8 fpkj_Serial(CYWXML_GY &ywxml_gy, CInvHead *pInvHead, string &strErr);

/*!
@brief  ��Ʊ����
@param[in] ywxml_gy	��������
@param[in & out] pInvHead	��Ʊ��Ϣ
@param[in] zflx	��������
@param[out] strErr	������Ϣ
*/
UINT8 fpzf_Serial(CYWXML_GY &ywxml_gy, CInvHead *pInvHead, UINT8 zflx, string &strErr);


/*!
@brief  ��Ʊ��ѯ
@param[in] ywxml_gy	��������
@param[in] cxfs	��ѯ��ʽ
@param[in] cxtj	��ѯ����
@param[out] invNum	��Ʊ����
@param[out] pInvHead	��Ʊ��Ϣ
@param[out] strErr	������Ϣ
*/
UINT8 fpcx_Serial(CYWXML_GY &ywxml_gy, UINT8 cxfs, string cxtj, UINT32 &invNum, CInvHead *pInvHead, string &strErr);


/*!
@brief  ˰���̱�˰����ϲ���
@param[in] ywxml_gy	��������
@param[in] czlx	��������
@param[out] strErr	������Ϣ
*/
UINT8 skpbspzhcz_Serial(CYWXML_GY &ywxml_gy, UINT8 czlx, string &strErr);


/*!
@brief  ��˰�̷�Ʊ��ѯ
@param[in] ywxml_gy	��������
@param[out] InvCount	��Ʊ��Ŀ
@param[out] pInvVol	��Ʊ����Ϣ
@param[out] strErr	������Ϣ
*/
UINT8 bspfpcx_Serial(CYWXML_GY &ywxml_gy,  UINT32 &InvCount, CInvVol *pInvVol, string &strErr);


/*!
@brief  ��Ʊ�ַ�
@param[in] ywxml_gy	��������
@param[in] jzlx	��������
@param[out] pInvVol	��Ʊ����Ϣ
@param[out] strErr	������Ϣ
*/
UINT8 fpff_Serial(CYWXML_GY &ywxml_gy, UINT8 jzlx, CInvVol *pInvVol, string &strErr);


/*!
@brief  ��Ʊ����
@param[in] ywxml_gy	��������
@param[out] pInvVol	��Ʊ����Ϣ
@param[in] strJzlx	��������
@param[out] strErr	������Ϣ
*/
UINT8 fphs_Serial(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, UINT8 strJzlx, string &strErr);


/*!
@brief  ���ݳ���
@param[in] ywxml_gy	��������
@param[in] jzlx	��������
@param[out] strErr	������Ϣ
*/
UINT8 sjcb_Serial(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr);


/*!
@brief  �����ػش�
@param[in] ywxml_gy	��������
@param[out] strErr	������Ϣ
*/
UINT8 wljkhc_Serial(CYWXML_GY &ywxml_gy, string &strErr);


/*!
@brief  ��Ʊͳ����Ϣ��ѯ
@param[in] ywxml_gy	��������
@param[out] pTjxxhz	ͳ����Ϣ
@param[out] strErr	������Ϣ
*/
UINT8 fptjcx_Serial(CYWXML_GY &ywxml_gy, CTjxxhz *pTjxxhz, string &strErr);


/*!
@brief  ��ҵ��Ϣ����
@param[in] ywxml_gy	��������
@param[out] strErr	������Ϣ
*/
UINT8 qyxxgx_Serial(CYWXML_GY &ywxml_gy, string &strErr);


/*!
@brief  ����Ȩ�޸���
@param[in] ywxml_gy	��������
@param[in] lxxxmw	������Ϣ����
@param[out] strErr	������Ϣ
*/
UINT8 lxqxgx_Serial(CYWXML_GY &ywxml_gy, string &strErr);


/*!
@brief  ��Ʊʵʱ�ϴ�
@param[in] ywxml_gy	��������
@param[in] czlx	��������
@param[out] fpzs	��Ʊ����
@param[out] strErr	������Ϣ
*/
UINT8 fpsssc_Serial(CYWXML_GY &ywxml_gy, UINT8 czlx, UINT32 &fpzs, string &strErr);


/*!
@brief  �������ά��
@param[in] ywxml_gy	��������
@param[out] strErr	������Ϣ
*/
UINT8 wlcswh_Serial(CNetPara *pNetPara, string &strErr);


/*!
@brief  ���ô��ڲ�����
@param[in] btl	������
@param[out] strErr	������Ϣ
*/
UINT8 setBaudRate_Serial(UINT32 btl, string &strErr);


/*!
@brief  ��Ʊ����
@param[in] ywxml_gy	��������
@param[in] jzlx	��������
@param[out] strErr	������Ϣ
*/
UINT8 fpdr_Serial(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr);


//�ֻ��˻�
/*!
@brief  ��˰����Ϣ��ѯ
@param[in] ywxml_gy	��������
@param[in] jzlx	��������
@param[out] strErr	������Ϣ
*/
UINT8 fjth_Serial(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr);


/*!
@brief  ���繺Ʊ
@param[in]  ywxml_gy ��������
@param[out] strErr	������Ϣ
*/
UINT8 wlgp_Serial(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, string &strErr);

/*!
@brief  ֤��������
@param[in] yzskl	ԭ����
@param[in] xzskl	�¿���
@param[out] strErr	������Ϣ
*/
UINT8 zsklgg_Serial(CYWXML_GY &ywxml_gy, string yzskl, string xzskl, string &strErr);

/*!
@brief  ��Ʊ��¼
@param[in] ywxml_gy	��������
@param[in] bsqsrq	��˰��ʼ����
@param[in] bszhrq	��˰��ֹ����
@param[out] strErr	������Ϣ
*/
UINT8 fpbl_Serial(CYWXML_GY &ywxml_gy, UINT32 bsqsrq, UINT32 bszzrq, string &strErr);

/*!
@brief  ��ȡ�����������
@param[out] wscfpzs		δ�ϴ���Ʊ����
@param[out] wscfpsj		δ�ϴ���Ʊʱ��
@param[out] wscfpljje	δ�ϴ���Ʊ�ۼƽ��
@param[out] sczs		�ϴ�����
@param[out] scsjjg		�ϴ�ʱ����
@param[out] strErr		������Ϣ
*/
UINT8 hqlxsj_Serial(string &wscfpzs, string &wscfpsj, string &wscfpljje, string &sczs, string &scsjjg, string &strErr);


/*!
@brief ����ת�������صĴ������������Ϣ
@param[in] ErrBuf		ת�������صĴ���
@param[out] strErr		������Ϣ
*/
UINT8 FindErrInfo(INT8 *ErrBuf, string &srrErr);

};

#endif
