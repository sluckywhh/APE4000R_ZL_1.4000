#include "IncludeMe.h"
#include "CBusinessSerialProc.h"
#include "SerialConfig.h"
#include "CGlobalArg.h"


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CBusinessSerialProc::CBusinessSerialProc()
{
	m_serialProtocol = SerialProtocol::getInstance();
}

CBusinessSerialProc::~CBusinessSerialProc()
{

}

//��������
UINT8 CBusinessSerialProc::onLine_Serial(string &strErr)
{
	DBG_PRINT(("----------����----------"));

	UINT8 cmdNo = SERIAL_ONLINE_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	DBG_PRINT(("ret= %u",ret));
	if (ret != SUCCESS)
	{
		 m_serialProtocol->resetAll();
		 
		 return FAILURE;
	}

	 ret = m_serialProtocol->revData(strErr);
	 DBG_PRINT(("ret = %u", ret));
	 if (ret != SERCMD_SUCCESS)
	 {
		 m_serialProtocol->resetAll();
		 
		 DBG_PRINT(("revData() ret = %u", ret));
		 return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;
		}

		m_serialProtocol->resetAll();
	}

	return SUCCESS;
}

//˰���̱�Ų�ѯ
UINT8 CBusinessSerialProc::skpbhcx_Serial(CYWXML_GY &ywxml_gy, string &sksbbh, string &strErr)
{
	DBG_PRINT(("----------˰���̱�Ų�ѯ----------"));

	UINT8 cmdNo = SERIAL_SKPBHCX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;

	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);
		
		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			sksbbh = (INT8 *)m_serialProtocol->m_rspCmd->rspData;	
			DBG_PRINT(("sksbbh: %s", sksbbh.c_str()));
			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;
		}
	}

	return SUCCESS;
}

//��˰�̱�Ų�ѯ
UINT8 CBusinessSerialProc::bspbhcx_Serial(CYWXML_GY &ywxml_gy, string &bspbh, string &strErr)
{
	DBG_PRINT(("----------��˰�̱�Ų�ѯ----------"));

	UINT8 cmdNo = SERIAL_BSPBHCX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;

	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);
		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			bspbh = (INT8 *)m_serialProtocol->m_rspCmd->rspData;
			DBG_PRINT(("bspbh: %s", bspbh.c_str()));
			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;
		}
	}

	return SUCCESS;
}

//˰������Ϣ��ѯ
UINT8 CBusinessSerialProc::skpxxcx_Serial(CYWXML_GY &ywxml_gy, CUserInfo &UserInfo, string &strCurTime, string &strErr)
{
	DBG_PRINT(("----------˰������Ϣ��ѯ----------"));
	
	UINT8 cmdNo = SERIAL_SKPXXCX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	UINT32 offset = 0;
	
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	DBG_PRINT(("����Ļ�����ţ�%s", ywxml_gy.m_jqbh.c_str()));
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);

		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{

			INT8 StrTempBuf[TMP_BUF_LEN];

 			memset(StrTempBuf, 0, sizeof(StrTempBuf));
 			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SBBH_LEN);
 			UserInfo.m_Jspsbh.assign(StrTempBuf);
 			DBG_PRINT(("UserInfo.m_Jspsbh: %s", UserInfo.m_Jspsbh.c_str()));
			offset += SBBH_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, NSRSBH_LEN);
 			UserInfo.m_Nsrsbh.assign(StrTempBuf);
 			DBG_PRINT(("UserInfo.m_Nsrsbh: %s", UserInfo.m_Nsrsbh.c_str()));
			offset += NSRSBH_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, NSRMC_LEN);
			UserInfo.m_Nsrmc.assign(StrTempBuf);
  			DBG_PRINT(("UserInfo.m_Nsrmc: %s", UserInfo.m_Nsrmc.c_str()));
			offset += NSRMC_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SWJGDM_LEN);
			UserInfo.m_Swjgdm.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_Swjgdm: %s", UserInfo.m_Swjgdm.c_str()));
			offset += SWJGDM_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SWJGMC_LEN);
			UserInfo.m_Swjgmc.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_Swjgmc: %s", UserInfo.m_Swjgmc.c_str()));
			offset += SWJGMC_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPLXDM_A_LEN);
			UserInfo.m_fplxdm.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_fplxdm: %s", UserInfo.m_fplxdm.c_str()));
			offset += FPLXDM_A_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SZSJ_LEN);
			strCurTime.assign(StrTempBuf);
			DBG_PRINT(("strCurTime: %s", strCurTime.c_str()));
			offset += SZSJ_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SZSJ_LEN);
			UserInfo.m_qysj.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_qysj: %s", UserInfo.m_qysj.c_str()));
			offset += SZSJ_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, BBH_LEN);
			UserInfo.m_bbh.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_bbh: %s", UserInfo.m_bbh.c_str()));
			offset += BBH_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, KPJH_LEN);
			UserInfo.m_Kpjhm = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("UserInfo.m_Kpjhm: %u", UserInfo.m_Kpjhm));
			offset += KPJH_LEN;
		
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, QYLX_LEN);
			UserInfo.m_Qylx.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_Qylx: %s", UserInfo.m_Qylx.c_str()));
			offset += QYLX_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, BLXX_LEN);
			UserInfo.m_blxx.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_blxx: %s", UserInfo.m_blxx.c_str()));
			offset += BLXX_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, KZXX_LEN);
			UserInfo.m_qtkzxx.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_qtkzxx: %s", UserInfo.m_qtkzxx.c_str()));

			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();
			return FAILURE;
		}
	}

	return SUCCESS;
}

//��˰����Ϣ��ѯ
UINT8 CBusinessSerialProc::bspxxcx_Serial(CYWXML_GY &ywxml_gy, CUserInfo &UserInfo, string &strErr)
{
	DBG_PRINT(("----------��˰����Ϣ��ѯ----------"));

	UINT32 offset = 0;
	UINT8 cmdNo = SERIAL_BSPXXCX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_bspkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);
		
		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			
			INT8 StrTempBuf[TMP_BUF_LEN];
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SBBH_LEN);
			UserInfo.m_bspbh.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_bspbh: %s", UserInfo.m_bspbh.c_str()));
			offset += SBBH_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, NSRSBH_LEN);
 			UserInfo.m_Nsrsbh.assign(StrTempBuf);
 			DBG_PRINT(("UserInfo.m_Nsrsbh: %s", UserInfo.m_Nsrsbh.c_str()));
			offset += NSRSBH_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, NSRMC_LEN);
			UserInfo.m_Nsrmc.assign(StrTempBuf);
  			DBG_PRINT(("UserInfo.m_Nsrmc: %s", UserInfo.m_Nsrmc.c_str()));
			offset += NSRMC_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SWJGDM_LEN);
			UserInfo.m_Swjgdm.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_Swjgdm: %s", UserInfo.m_Swjgdm.c_str()));
			offset += SWJGDM_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SWJGMC_LEN);
			UserInfo.m_Swjgmc.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_Swjgmc: %s", UserInfo.m_Swjgmc.c_str()));
			offset += SWJGMC_LEN;
			
			//��ǰʱ�Ӳ�����
			offset += SZSJ_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SZSJ_LEN);
			UserInfo.m_qysj.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_qysj: %s", UserInfo.m_qysj.c_str()));
			offset += SZSJ_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FFBZ_LEN);
			UserInfo.m_ffbz.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_ffbz: %s", UserInfo.m_ffbz.c_str()));
			offset += FFBZ_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, BBH_LEN);
			UserInfo.m_bbh.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_bbh: %s", UserInfo.m_bbh.c_str()));
			offset += BBH_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, KPJH_LEN);
			UserInfo.m_Kpjhm = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("UserInfo.m_Kpjhm: %u", UserInfo.m_Kpjhm));
			offset += KPJH_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, QYLX_LEN);
			UserInfo.m_Qylx.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_Qylx: %s", UserInfo.m_Qylx.c_str()));
			offset += QYLX_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, BLXX_LEN);
			UserInfo.m_blxx.assign(StrTempBuf);
			DBG_PRINT(("UserInfo.m_blxx: %s", UserInfo.m_blxx.c_str()));

			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;
		}
	}
	
	return SUCCESS;
}

//������ݲ�ѯ
UINT8 CBusinessSerialProc::jksjcx_Serial(CYWXML_GY &ywxml_gy, CInvKind &InvKind, string &strErr)
{
	DBG_PRINT(("----------������ݲ�ѯ----------"));

	UINT32 offset = 0;
	UINT8 cmdNo = SERIAL_JKSJCX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;

	DBG_PRINT(("ywxml_gy.m_nsrsbh : %s", ywxml_gy.m_nsrsbh.c_str()));
	DBG_PRINT(("ywxml_gy.m_sksbbh : %s", ywxml_gy.m_sksbbh.c_str()));
	DBG_PRINT(("ywxml_gy.m_sksbklm_fplxdm : %s", ywxml_gy.m_sksbkl.c_str()));
	DBG_PRINT(("ywxml_gy.m_fplxdm : %s", ywxml_gy.m_fplxdm.c_str()));
	DBG_PRINT(("ywxml_gy.m_jqbh : %s", ywxml_gy.m_jqbh.c_str()));

	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);

	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);
		
		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			INT8 StrTempBuf[TMP_BUF_LEN];
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPLXDM_S_LEN);
			InvKind.m_fplxdm.assign(StrTempBuf);
			DBG_PRINT(("InvKind.m_fplxdm: %s", InvKind.m_fplxdm.c_str()));
			offset += FPLXDM_S_LEN;
			
			//��Ʊ��ֹʱ�䲻����
			offset += DATE_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SZSJ_LEN);
			InvKind.m_bsqsrq.assign(StrTempBuf);			
			DBG_PRINT(("InvKind.m_bsqsrq: %s", InvKind.m_bsqsrq.c_str()));
			offset += SZSJ_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SZSJ_LEN);
			InvKind.m_bszzrq.assign(StrTempBuf);			
			DBG_PRINT(("InvKind.m_bszzrq: %s", InvKind.m_bszzrq.c_str()));
			offset += SZSJ_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, XIANE_LEN);;
			InvKind.m_maxSign = double2int(atof(StrTempBuf)*SUM_EXTENSION);
			DBG_PRINT(("InvKind.m_maxSign: %lld", InvKind.m_maxSign));
			offset += XIANE_LEN;

			//���±�˰���ڲ�����
			offset += SZSJ_LEN;

			//ʣ������������
			offset += SYRL_LEN;	

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SCJZRQ_LEN);
			InvKind.m_Lxssr = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("InvKind.m_Lxssr: %u", InvKind.m_Lxssr));
			offset += SCJZRQ_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, LXKPSC_LEN);
			InvKind.m_Lxkjsj = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("InvKind.m_Lxkjsj: %u", InvKind.m_Lxkjsj));
			offset += LXKPSC_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, XIANE_LEN);
			InvKind.m_maxSum = double2int(atof(StrTempBuf)*SUM_EXTENSION);
			DBG_PRINT(("InvKind.m_maxSum: %lld", InvKind.m_maxSum));

			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;
		}
	}
	
	return SUCCESS;
}

//��Ȩ˰�ʲ�ѯ
UINT8 CBusinessSerialProc::sqslcx_Serial(CYWXML_GY &ywxml_gy, CTax *pTax, UINT8 &taxNum, string &strErr)
{
	DBG_PRINT(("----------��Ȩ˰�ʲ�ѯ----------"));
	
	UINT32 offset = 0;
	UINT8 cmdNo = SERIAL_SQSLCX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);
		
		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			INT8 StrTempBuf[TMP_BUF_LEN];
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPLXDM_S_LEN);
			ywxml_gy.m_fplxdm.assign(StrTempBuf);
			DBG_PRINT(("ywxml_gy.m_fplxdm: %s", ywxml_gy.m_fplxdm.c_str()));
			offset += FPLXDM_S_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SZSMSYH_LEN);
			taxNum = (UINT8)atoi(StrTempBuf);
			DBG_PRINT(("taxNum: %u", taxNum));
			offset += SZSMSYH_LEN;
			
			for (UINT8 i=0; i<taxNum; i++)
			{
				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TAXRATE_LEN);
				pTax[i].m_sl = double2int(atof(StrTempBuf)*DEPT_TAX_EXTENSION);
				DBG_PRINT(("pTax[%u].m_sl: %u", i, pTax[i].m_sl));
				offset += TAXRATE_LEN;
			}	
			
			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;
		}
	}


	return SUCCESS;
}

//��Ʊ��Ϣ��ѯ
UINT8 CBusinessSerialProc::gpxxcx_Serial(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, string &strErr)
{
	DBG_PRINT(("----------��Ʊ��Ϣ��ѯ----------"));

	UINT32 offset = 0;
	UINT8 cmdNo = SERIAL_GPXXCX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;

	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);
		
		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			INT8 StrTempBuf[TMP_BUF_LEN];
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPLXDM_S_LEN);
			pInvVol->m_fplxdm.assign(StrTempBuf);
			DBG_PRINT(("pInvVol->m_fplxdm: %s", pInvVol->m_fplxdm.c_str()));
			offset += FPLXDM_S_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPDM_LEN);
			pInvVol->m_code.assign(StrTempBuf);
			DBG_PRINT(("pInvVol->m_code: %s", pInvVol->m_code.c_str()));
			offset += FPDM_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPHM_LEN);
			pInvVol->m_curInvNo = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("pInvHead->m_curInvNo: %u", pInvVol->m_curInvNo));
			offset += FPHM_LEN;
		
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPFS_LEN);
			pInvVol->m_remain = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("pInvVol->m_remain: %u", pInvVol->m_remain));

			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;
		}
	}

	return SUCCESS;
}

//˰���豸�������
UINT8 CBusinessSerialProc::sksbklgg_Serial(CYWXML_GY &ywxml_gy, string ykl, string xkl, string &strErr)
{
	DBG_PRINT(("----------�������----------"));

	UINT8 cmdNo = SERIAL_KLGG_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ykl, KOULING_LEN);
	m_serialProtocol->FillParament(xkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;
		}

		m_serialProtocol->resetAll();
	}

	return SUCCESS;
}

//��Ʊ����
UINT8 CBusinessSerialProc::fpkj_Serial(CYWXML_GY &ywxml_gy, CInvHead *pInvHead, string &strErr)
{
	DBG_PRINT(("----------��Ʊ����----------"));

	INT8 tempbuf[BUF_LEN];
	UINT32 offset = 0;
	UINT8 cmdNo = SERIAL_FPKJ_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(pInvHead->m_zskl, ZSKOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_nsrmc, NSRMC_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);

	if (NORMAL_INV == pInvHead->m_kplx)
	{
		UINT8 kplx_temp = 0;	//�淶Ҫ����Ʊ����Ҫ��0
		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", kplx_temp);
	}
	else if (RETURN_INV == pInvHead->m_kplx)
	{
		UINT8 kplx_temp = 1;	//�淶Ҫ���Ʊ����Ҫ��1
		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", kplx_temp);
	}
	m_serialProtocol->FillParament(tempbuf, KPLX_LEN);
	DBG_PRINT(("��Ʊ���ͣ� %u", pInvHead->m_kplx));
	DBG_PRINT(("��Ʊ���ͣ� %s", tempbuf));

	m_serialProtocol->FillParament(pInvHead->m_fkdwsh, FKDWSH_LEN);
	DBG_PRINT(("������λʶ��ţ�%s", pInvHead->m_fkdwsh.c_str()));
	m_serialProtocol->FillParament(pInvHead->m_fkdw, FKDWMC_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", pInvHead->m_sphsl);
	m_serialProtocol->FillParament(tempbuf, SPHSL_LEN);

	UINT8 i = 0;
	CInvDet *pInvDet = pInvHead->pHead;
	for (i=0; i<pInvHead->m_sphsl; i++, pInvDet = pInvDet->pNext)
	{
		m_serialProtocol->FillParament(pInvDet->m_spmc, XMMC_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%0.3lf", pInvDet->m_dj);
		m_serialProtocol->FillParament(tempbuf, DJ_LEN);
		DBG_PRINT(("���ۣ�����˰��pInvDet->m_dj = %lf", pInvDet->m_dj));
		
		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%0.3lf", pInvDet->m_spsl);
		m_serialProtocol->FillParament(tempbuf, SL_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%.2lf", ((double)pInvDet->m_je)/SUM_EXTENSION);
		m_serialProtocol->FillParament(tempbuf, JE_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%0.2f", pInvDet->m_sl);
		m_serialProtocol->FillParament(tempbuf, TAXRATE_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%.2lf", ((double)pInvDet->m_spse)/SUM_EXTENSION);
		m_serialProtocol->FillParament(tempbuf, TAX_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));	
		sprintf(tempbuf, "%0.3lf", pInvDet->m_spdj);		//��˰����
		m_serialProtocol->FillParament(tempbuf, DJ_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%0.2lf", ((double)pInvDet->m_spje)/SUM_EXTENSION);			//��˰���
		m_serialProtocol->FillParament(tempbuf, JE_LEN);
	}

	pInvHead->m_kpje = pInvHead->m_kphjje - pInvHead->m_kpse;
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%.2lf", ((double)pInvHead->m_kpje)/SUM_EXTENSION);
	m_serialProtocol->FillParament(tempbuf, JE_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%.2lf", ((double)pInvHead->m_kpse)/SUM_EXTENSION);
	m_serialProtocol->FillParament(tempbuf, TAX_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%.2lf", ((double)pInvHead->m_kphjje)/SUM_EXTENSION);
	m_serialProtocol->FillParament(tempbuf, JE_LEN);

	m_serialProtocol->FillParament(pInvHead->m_backup1, BZ_LEN);
	m_serialProtocol->FillParament(pInvHead->m_sky, RYMC_LEN);
	m_serialProtocol->FillParament(pInvHead->m_yfpdm, FPDM_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%08u", pInvHead->m_yfphm);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);
		
		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			INT8 StrTempBuf[TMP_BUF_LEN];
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPLXDM_S_LEN);
			ywxml_gy.m_fplxdm.assign(StrTempBuf);
			DBG_PRINT(("ywxml_gy.m_fplxdm: %s", ywxml_gy.m_fplxdm.c_str()));
			offset += FPLXDM_S_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPDM_LEN);
			pInvHead->m_fpdm.assign(StrTempBuf);
			DBG_PRINT(("pInvHead->m_fpdm: %s", pInvHead->m_fpdm.c_str()));
			offset += FPDM_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPHM_LEN);
			pInvHead->m_fphm = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("pInvHead->m_fphm: %u", pInvHead->m_fphm));
			offset += FPHM_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, DATE_LEN);
			pInvHead->m_kprq = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("pInvHead->m_kprq: %u", pInvHead->m_kprq));
			offset += DATE_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TIME_LEN);
			pInvHead->m_kpsj = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("pInvHead->m_kpsj: %u", pInvHead->m_kpsj));
			offset += TIME_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SKM_SHORT_LEN);
			pInvHead->m_fwm.assign(StrTempBuf);
			DBG_PRINT(("pInvHead->m_fwm: %s", pInvHead->m_fwm.c_str()));
			offset += SKM_SHORT_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SIGN_LEN);
			pInvHead->m_casign.assign(StrTempBuf);
			DBG_PRINT(("pInvHead->m_casign: %s", pInvHead->m_casign.c_str()));

			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;
		}
	}

	return SUCCESS;
}

//��Ʊ����
UINT8 CBusinessSerialProc::fpzf_Serial(CYWXML_GY &ywxml_gy, CInvHead *pInvHead, UINT8 zflx, string &strErr)
{
	DBG_PRINT(("----------��Ʊ����----------"));
	
	INT8 tempbuf[BUF_LEN];
	UINT32 offset = 0;
	UINT8 cmdNo = SERIAL_FPZF_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;

	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(pInvHead->m_zskl, ZSKOULING_LEN);
	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", zflx);
	DBG_PRINT(("�������� %u", zflx));
	DBG_PRINT(("�������� %s", tempbuf));
	m_serialProtocol->FillParament(tempbuf, ZFLX_LEN);

	m_serialProtocol->FillParament(pInvHead->m_fpdm, FPDM_LEN);
	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%08u", pInvHead->m_fphm);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);

	m_serialProtocol->FillParament(pInvHead->m_sky, RYMC_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);

	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);
		
		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			INT8 StrTempBuf[TMP_BUF_LEN + 1];
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPLXDM_S_LEN);
			ywxml_gy.m_fplxdm.assign(StrTempBuf);
			DBG_PRINT(("ywxml_gy.m_fplxdm: %s", ywxml_gy.m_fplxdm.c_str()));
			offset += FPLXDM_S_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPDM_LEN);
			pInvHead->m_fpdm.assign(StrTempBuf);
			DBG_PRINT(("pInvHead->m_fpdm: %s", pInvHead->m_fpdm.c_str()));
			offset += FPDM_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPHM_LEN);
			pInvHead->m_fphm = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("pInvHead->m_fphm: %u", pInvHead->m_fphm));
			offset += FPHM_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, DATE_LEN);
			pInvHead->m_kprq = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("pInvHead->m_kprq: %u", pInvHead->m_kprq));
			offset += DATE_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TIME_LEN);
			pInvHead->m_kpsj = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("pInvHead->m_kpsj: %u", pInvHead->m_kpsj));
			offset += TIME_LEN;
			
		
			pInvHead->m_zfrq = pInvHead->m_kprq;   /**<  ��������*/
			pInvHead->m_zfsj = pInvHead->m_kpsj;   /**<  ����ʱ��*/
			DBG_PRINT(("pInvHead->m_zfrq: %u", pInvHead->m_zfrq));
			DBG_PRINT(("pInvHead->m_zfsj: %u", pInvHead->m_zfsj));

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SIGN_LEN);
			pInvHead->m_casign.assign(StrTempBuf);
			DBG_PRINT(("pInvHead->m_casign: %s", pInvHead->m_casign.c_str()));
			
			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;
		}
	}

	return SUCCESS;
}

//��Ʊ��ѯ
UINT8 CBusinessSerialProc::fpcx_Serial(CYWXML_GY &ywxml_gy, UINT8 cxfs, string cxtj, UINT32 &invNum, CInvHead *pInvHead, string &strErr)
{
	DBG_PRINT(("----------��Ʊ��ѯ----------"));

	INT8 tempbuf[BUF_LEN];
	UINT32 offset = 0;
	UINT8 cmdNo = SERIAL_FPCX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	INT32 iFpzt = 0;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", cxfs);
	m_serialProtocol->FillParament(tempbuf, CXFS_LEN);

	DBG_PRINT(("��ѯ������%s", cxtj.c_str()));
	m_serialProtocol->FillParament(cxtj, CXTJ_LEN);

	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);

		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			INT8 StrTempBuf[TMP_BUF_LEN + 1];
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPDM_LEN);
			pInvHead->m_fpdm.assign(StrTempBuf);
			DBG_PRINT(("pInvHead->m_fpdm: %s", pInvHead->m_fpdm.c_str()));
			offset += FPDM_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPHM_LEN);
			pInvHead->m_fphm = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("pInvHead->m_fphm: %u", pInvHead->m_fphm));
			offset += FPHM_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPCX_FPZT_LEN);
			iFpzt = atoi(StrTempBuf);	//��Ʊ״̬
			DBG_PRINT(("fpcx: fpzt = %d", iFpzt));
			switch(iFpzt)
			{
			case 0:
				pInvHead->m_kplx = NORMAL_INV;
				break;
			case 1:
				pInvHead->m_kplx = RETURN_INV;
				break;
			case 2:
				pInvHead->m_kplx = WASTE_INV;
				break;
			case 3:
				pInvHead->m_kplx = WASTE_NOR;
				break;
			case 4:
				pInvHead->m_kplx = WASTE_RET;
				break;
			}
			DBG_PRINT(("fpcx: kplx = %u", pInvHead->m_kplx));
			offset += FPCX_FPZT_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPCX_SCBZ_LEN);
			pInvHead->m_scbz = (UINT8)atoi(StrTempBuf);	//�ϴ���ʶ
			DBG_PRINT(("fpcx: m_scbz = %u", pInvHead->m_scbz));
			offset += FPCX_SCBZ_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, DATE_LEN);
			pInvHead->m_kprq = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("pInvHead->m_kprq: %u", pInvHead->m_kprq));
			offset += DATE_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TIME_LEN);
			pInvHead->m_kpsj = (UINT32)atoi(StrTempBuf);
			DBG_PRINT(("pInvHead->m_kpsj: %u", pInvHead->m_kpsj));
			offset += TIME_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SKM_SHORT_LEN);
			pInvHead->m_fwm.assign(StrTempBuf);
			DBG_PRINT(("pInvHead->m_fwm: %s", pInvHead->m_fwm.c_str()));
			offset += SKM_SHORT_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SBBH_LEN);
			string strSksbbh = "";
			strSksbbh.assign(StrTempBuf);
			DBG_PRINT(("fpcx: sksbbh = %s", strSksbbh.c_str()));
			offset += SBBH_LEN;

// 			memset(StrTempBuf, 0, sizeof(StrTempBuf));
// 			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SKDWMC_LEN);
// 			string strSkdwmc = "";
// 			strSkdwmc.assign(StrTempBuf);
// 			DBG_PRINT(("fpcx: skdwmc = %s", strSkdwmc.c_str()));
// 			offset += SKDWMC_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, NSRSBH_LEN);
			string strXhdwsbh = "";	//������λʶ���
			strXhdwsbh.assign(StrTempBuf);
			DBG_PRINT(("fpcx: xhdwsbh = %s", strXhdwsbh.c_str()));
			offset += NSRSBH_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, NSRMC_LEN);			
			string strXhdmc = "";	//������λ����
			strXhdmc.assign(StrTempBuf);
			DBG_PRINT(("fpcx: xhdwmc = %s", strXhdmc.c_str()));
			offset += NSRMC_LEN;


			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FKDWSH_LEN);
			pInvHead->m_fkdwsh.assign(StrTempBuf);		//������λʶ���
			DBG_PRINT(("fpcx: ghdwsbh = %s", pInvHead->m_fkdwsh.c_str()));	
			offset += FKDWSH_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FKDWMC_LEN);
			pInvHead->m_fkdw.assign(StrTempBuf); //������λ����
			DBG_PRINT(("fpcx: ghdwmc = %s", pInvHead->m_fkdw.c_str()));
			offset += FKDWMC_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SPHSL_LEN);
			pInvHead->m_sphsl = (UINT32)atoi(StrTempBuf);	//��Ŀ����
			DBG_PRINT(("fpcx: m_sphsl = %u", pInvHead->m_sphsl));
			offset += SPHSL_LEN;

			CInvDet *pInvDet = NULL;

			for (INT32 itemp=0; itemp<pInvHead->m_sphsl; itemp++)
			{
				pInvDet = pInvDet->GetNewInvDet();	//�Ӿ�̬�����ȡһ�����õ�CInvDet����
				DBG_ASSERT_EXIT((pInvDet != NULL), (" pInvDet == NULL!"));

				pInvDet->m_fpdm = pInvHead->m_fpdm;
				pInvDet->m_fphm = pInvHead->m_fphm;
				pInvDet->m_kprq = pInvHead->m_kprq;
				pInvDet->m_kpsj = pInvHead->m_kpsj;
				pInvDet->m_kplx = pInvHead->m_kplx;
				pInvDet->m_sky =g_globalArg->m_operator->m_name;
			    pInvDet->m_sphxh = itemp+1;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, XMMC_LEN);
				pInvDet->m_spmc.assign(StrTempBuf);	//��Ŀ
				DBG_PRINT(("fpcx: m_spmc = %s", pInvDet->m_spmc.c_str()));
				offset += XMMC_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, DJ_LEN);
				pInvDet->m_dj = atof(StrTempBuf);	//����
				DBG_PRINT(("fpcx: m_spdj = %.3lf", pInvDet->m_dj));
				offset += DJ_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SL_LEN);
				pInvDet->m_spsl = atof(StrTempBuf);	//����
				DBG_PRINT(("fpcx: m_spsl = %.3lf", pInvDet->m_spsl));
				offset += SL_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
				pInvDet->m_je = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//���
				DBG_PRINT(("fpcx: m_spje = %lld", pInvDet->m_je));
				offset += JE_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TAXRATE_LEN);
				pInvDet->m_sl = atof(StrTempBuf);	//˰��
				DBG_PRINT(("fpcx: m_sl = %f", pInvDet->m_sl));
				offset += TAXRATE_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TAX_LEN);
				pInvDet->m_spse = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//˰��
				DBG_PRINT(("fpcx: m_spse = %lld", pInvDet->m_spse));
				offset += TAX_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, DJ_LEN);
				pInvDet->m_spdj = atof(StrTempBuf);	//��˰����
				DBG_PRINT(("fpcx: m_spdj = %.3lf", pInvDet->m_spdj));
				offset += DJ_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
				pInvDet->m_spje = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//��˰���
				DBG_PRINT(("fpcx: m_spje = %lld", pInvDet->m_spje));
				offset += JE_LEN;

				pInvHead->InsertNode(pInvDet);
				
				pInvDet =NULL;
			}

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			pInvHead->m_kpje = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//�ϼƽ��
			DBG_PRINT(("fpcx: m_kpje = %lld", pInvHead->m_kpje));
			offset += JE_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			pInvHead->m_kpse = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//�ϼ�˰��
			DBG_PRINT(("fpcx: m_kpse = %lld", pInvHead->m_kpse));
			offset += JE_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			pInvHead->m_kphjje = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//��˰�ϼ�
			DBG_PRINT(("fpcx: m_kphjje = %lld", pInvHead->m_kphjje));
			offset += JE_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, BZ_LEN);
			pInvHead->m_backup1.assign(StrTempBuf);	//��ע
			DBG_PRINT(("fpcx: bz = %s", pInvHead->m_backup1.c_str()));
			offset += BZ_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, RYMC_LEN);
			pInvHead->m_sky.assign(StrTempBuf);	//�淶�еĿ�Ʊ��
			DBG_PRINT(("fpcx: m_sky = %s", pInvHead->m_sky.c_str()));
			offset += RYMC_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPDM_LEN);
			pInvHead->m_yfpdm.assign(StrTempBuf);	//ԭ��Ʊ����
			DBG_PRINT(("fpcx: m_yfpdm = %s", pInvHead->m_yfpdm.c_str()));
			offset += FPDM_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPHM_LEN);
			pInvHead->m_yfphm = atoi(StrTempBuf);	//ԭ��Ʊ����
			DBG_PRINT(("fpcx: m_yfphm = %u", pInvHead->m_yfphm));
			offset += FPHM_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SZSJ_LEN);
			pInvHead->m_zfrq = atoi(StrTempBuf);	//��������
			DBG_PRINT(("fpcx: m_zfrq = %u", pInvHead->m_zfrq));
			offset += SZSJ_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, RYMC_LEN);
			pInvHead->m_sky.assign(StrTempBuf);	//������
			DBG_PRINT(("fpcx: m_sky = %s", pInvHead->m_sky.c_str()));
			offset += RYMC_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			INT64 iYkfsje = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//�ѿ��������
			DBG_PRINT(("fpcx: ykfsje = %lld", iYkfsje));
			offset += JE_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SIGN_LEN);
			pInvHead->m_casign.assign(StrTempBuf);	//ǩ��ֵ
			DBG_PRINT(("fpcx: m_casign = %s", pInvHead->m_casign.c_str()));

			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;			
		}
	}

	return SUCCESS;
}

//˰���̱�˰����ϲ���
UINT8 CBusinessSerialProc::skpbspzhcz_Serial(CYWXML_GY &ywxml_gy, UINT8 czlx, string &strErr)
{
	DBG_PRINT(("----------˰���̱�˰����ϲ���----------"));

	INT8 tempbuf[BUF_LEN];
	
	UINT8 cmdNo = SERIAL_SKPBSPZHCZ_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_bspbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_bspkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", czlx);
	m_serialProtocol->FillParament(tempbuf, CZLX_LEN);

	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);		
			m_serialProtocol->resetAll();	

			return FAILURE;			
		}
		
		m_serialProtocol->resetAll();
	}

	return SUCCESS;
}

//��˰�̷�Ʊ��ѯ
UINT8 CBusinessSerialProc::bspfpcx_Serial(CYWXML_GY &ywxml_gy,  UINT32 &InvCount, CInvVol *pInvVol, string &strErr)
{
	DBG_PRINT(("----------��˰�̷�Ʊ��ѯ----------"));

	UINT8 cmdNo = SERIAL_BSPFPCX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;	
	UINT32 offset = 0;

	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);
		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			INT8 StrTempBuf[TMP_BUF_LEN];
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPLXDM_S_LEN);
		//	ywxml_gy.m_fplxdm.assign(StrTempBuf);	//��Ʊ���ʹ���
		//	DBG_PRINT(("bspfpcx: fplxdm = %s", g_YwXmlArg->m_fplxdm.c_str()));	
			offset = FPLXDM_S_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, BSPFPCX_FPSL_LEN);
			InvCount = atoi(StrTempBuf);	//��˰���з�Ʊ�Ŷ�����
			DBG_PRINT(("bspfpcx: InvCount = %u", InvCount));
			offset += BSPFPCX_FPSL_LEN;

			for (int itemp=0; itemp<InvCount; itemp++)
			{	
				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPDM_LEN);
				pInvVol[itemp].m_code.assign(StrTempBuf);	//��Ʊ����
				DBG_PRINT(("bspfpcx[%d]: code = %s", itemp, pInvVol[itemp].m_code.c_str()));
				offset += FPDM_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPHM_LEN);
				pInvVol[itemp].m_isno = (UINT32)atoi(StrTempBuf);	//��Ʊ��ʼ����
				DBG_PRINT(("bspfpcx[%d]: m_isno = %u", itemp, pInvVol[itemp].m_isno));
				offset += FPHM_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPHM_LEN);
				pInvVol[itemp].m_ieno = (UINT32)atoi(StrTempBuf);	//��Ʊ��ֹ����
				DBG_PRINT(("bspfpcx[%d]: m_ieno = %u", itemp, pInvVol[itemp].m_ieno));
				offset += FPHM_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPFS_LEN);
				pInvVol[itemp].m_fpzfs = (UINT32)atoi(StrTempBuf);	//��Ʊ�칺����
				DBG_PRINT(("bspfpcx[%d]: m_fpzfs = %u", itemp, pInvVol[itemp].m_fpzfs));
				offset += FPFS_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPFS_LEN);
				pInvVol[itemp].m_remain = (UINT32)atoi(StrTempBuf);	//��Ʊʣ�����
				DBG_PRINT(("bspfpcx[%d]: m_remain = %u", itemp, pInvVol[itemp].m_remain));
				offset += FPFS_LEN;

				memset(StrTempBuf, 0, sizeof(StrTempBuf));
				memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, DATE_LEN);
				pInvVol[itemp].m_date = (UINT32)atoi(StrTempBuf);	//�칺����
				DBG_PRINT(("bspfpcx[%d]: m_date = %u", itemp, pInvVol[itemp].m_date));
				offset += DATE_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, RYMC_LEN);
			string strLgry = "";
			strLgry.assign(StrTempBuf);	//�칺��Ա
                offset += RYMC_LEN;
			}

			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;			
		}
	}
	
	return SUCCESS;
}

//��Ʊ�ַ�
UINT8 CBusinessSerialProc::fpff_Serial(CYWXML_GY &ywxml_gy, UINT8 jzlx, CInvVol *pInvVol, string &strErr)
{
	DBG_PRINT(("----------��Ʊ�ַ�----------"));

	INT8 tempbuf[BUF_LEN];
	
	UINT8 cmdNo = SERIAL_FPFF_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", jzlx);
	DBG_PRINT(("��������: %u", jzlx));
	DBG_PRINT(("��������: %s", tempbuf));
	m_serialProtocol->FillParament(tempbuf, JZLX_LEN);

	m_serialProtocol->FillParament(ywxml_gy.m_bspbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_bspkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	DBG_PRINT(("ywxml_gy.m_fplxdm : %s", ywxml_gy.m_fplxdm.c_str()));

	m_serialProtocol->FillParament(pInvVol->m_code, FPDM_LEN);
	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", pInvVol->m_isno);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", pInvVol->m_fpzfs);
	m_serialProtocol->FillParament(tempbuf, FPFS_LEN);

	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
	    if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);	
			m_serialProtocol->resetAll();

			return FAILURE;			
		}
		
		m_serialProtocol->resetAll();
	}

	return SUCCESS;
}

//��Ʊ����
UINT8 CBusinessSerialProc::fphs_Serial(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, UINT8 strJzlx, string &strErr)
{
	DBG_PRINT(("----------��Ʊ����----------"));


	INT8 tempbuf[BUF_LEN];
	
	UINT8 cmdNo = SERIAL_FPHS_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", strJzlx);
	m_serialProtocol->FillParament(tempbuf, JZLX_LEN);
	
	m_serialProtocol->FillParament(ywxml_gy.m_bspbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_bspkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	
	m_serialProtocol->FillParament(pInvVol->m_code, FPDM_LEN);
	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%08u", pInvVol->m_isno);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);
	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", pInvVol->m_fpzfs);
	m_serialProtocol->FillParament(tempbuf, FPFS_LEN);
	
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;			
		}

		m_serialProtocol->resetAll();
	}
	
	return SUCCESS;
}

//���ݳ���
UINT8 CBusinessSerialProc::sjcb_Serial(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr)
{
	DBG_PRINT(("----------���ݳ���----------"));

	INT8 tempbuf[BUF_LEN];
	
	UINT8 cmdNo = SERIAL_SJCB_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", jzlx);
	m_serialProtocol->FillParament(tempbuf, JZLX_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_kpjh, KPJH_LEN);

	DBG_PRINT(("ywxml_gy.m_nsrsbh : %s", ywxml_gy.m_nsrsbh.c_str()));
	DBG_PRINT(("ywxml_gy.m_sksbbh : %s", ywxml_gy.m_sksbbh.c_str()));
	DBG_PRINT(("ywxml_gy.m_sksbkl : %s", ywxml_gy.m_sksbkl.c_str()));
	DBG_PRINT(("ywxml_gy.m_fplxdm : %s", ywxml_gy.m_fplxdm.c_str()));
	DBG_PRINT(("ywxml_gy.m_jqbh : %s", ywxml_gy.m_jqbh.c_str()));
	DBG_PRINT(("�������ͣ� %s", tempbuf));
	DBG_PRINT(("ywxml_gy.m_kpjh : %s", ywxml_gy.m_kpjh.c_str()));

	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);	
			m_serialProtocol->resetAll();
			return FAILURE;			
		}

		m_serialProtocol->resetAll();
	}

	return SUCCESS;
}

//�����ػش�
UINT8 CBusinessSerialProc::wljkhc_Serial(CYWXML_GY &ywxml_gy, string &strErr)
{
	DBG_PRINT(("----------�����ػش�----------"));

	UINT8 cmdNo = SERIAL_WLJKHC_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_kpjh, KPJH_LEN);
	DBG_PRINT(("ywxml_gy.m_kpjh : %s", ywxml_gy.m_kpjh.c_str()));
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;			
		}

		m_serialProtocol->resetAll();
	}

	return SUCCESS;
}

//��Ʊͳ����Ϣ��ѯ
UINT8 CBusinessSerialProc::fptjcx_Serial(CYWXML_GY &ywxml_gy, CTjxxhz *pTjxxhz, string &strErr)
{
	DBG_PRINT(("----------��Ʊͳ����Ϣ��ѯ----------"));

	INT8 tempbuf[BUF_LEN];
	
	UINT8 cmdNo = SERIAL_FPTJXXCX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	UINT32 offset = 0;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%08u", pTjxxhz->m_Qsrq);
	m_serialProtocol->FillParament(tempbuf, DATE_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", pTjxxhz->m_Jzrq);
	m_serialProtocol->FillParament(tempbuf, DATE_LEN);

	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);

	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);
		
		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			INT8 StrTempBuf[TMP_BUF_LEN];
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, FPLXDM_S_LEN);
			ywxml_gy.m_fplxdm.assign(StrTempBuf);	//��Ʊ���ʹ���
			DBG_PRINT(("bspfpcx: fplxdm = %s", g_YwXmlArg->m_fplxdm.c_str()));	
			offset = FPLXDM_S_LEN;	

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TJCX_FPSL_LEN);
			UINT32  tjcx_fpsl = (UINT32)atoi(StrTempBuf);	//��˰���з�Ʊ�Ŷ������������޶�Ӧ����
			DBG_PRINT(("fptjcx: fpsl = %u", tjcx_fpsl));	
			offset += TJCX_FPSL_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, DATE_LEN);
			pTjxxhz->m_Qsrq = (UINT32)atoi(StrTempBuf);	//��ʼ����
			DBG_PRINT(("fptjcx: qsrq = %u", pTjxxhz->m_Qsrq));
			offset += DATE_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, DATE_LEN);
			pTjxxhz->m_Jzrq = (UINT32)atoi(StrTempBuf);	//��ֹ����
			DBG_PRINT(("fptjcx: jzrq = %u", pTjxxhz->m_Jzrq));
			offset += DATE_LEN;		
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TJCX_FPFS_LEN);
			pTjxxhz->m_Qckcfs = (UINT32)atoi(StrTempBuf);	//�ڳ�������
			DBG_PRINT(("fptjcx: m_Qckcfs = %u", pTjxxhz->m_Qckcfs));	
			offset += TJCX_FPFS_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TJCX_FPFS_LEN);
			pTjxxhz->m_Lgfpfs = (UINT32)atoi(StrTempBuf);	//�칺��Ʊ����
			DBG_PRINT(("fptjcx: m_Lgfpfs = %u", pTjxxhz->m_Lgfpfs));
			offset += TJCX_FPFS_LEN;	

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TJCX_FPFS_LEN);
			pTjxxhz->m_Thfpfs = (UINT32)atoi(StrTempBuf);	//�˻ط�Ʊ����
			DBG_PRINT(("fptjcx: m_Thfpfs = %u", pTjxxhz->m_Thfpfs));	
			offset += TJCX_FPFS_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TJCX_FPFS_LEN);
			pTjxxhz->m_Zsfpfs = (UINT32)atoi(StrTempBuf);	//������Ʊ����
			DBG_PRINT(("fptjcx: m_Zsfpfs = %u", pTjxxhz->m_Zsfpfs));
			offset += TJCX_FPFS_LEN;	
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TJCX_FPFS_LEN);
			pTjxxhz->m_Zffpfs = (UINT32)atoi(StrTempBuf);	//���Ϸ�Ʊ����
			DBG_PRINT(("fptjcx: m_Zffpfs = %u", pTjxxhz->m_Zffpfs));
			offset += TJCX_FPFS_LEN;	

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TJCX_FPFS_LEN);
			pTjxxhz->m_Fsfpfs = (UINT32)atoi(StrTempBuf);	//������Ʊ����
			DBG_PRINT(("fptjcx: m_Fsfpfs = %u", pTjxxhz->m_Fsfpfs));
			offset += TJCX_FPFS_LEN;	
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TJCX_FPFS_LEN);
			pTjxxhz->m_Fffpfs = (UINT32)atoi(StrTempBuf);	//���Ϸ�Ʊ����
			DBG_PRINT(("fptjcx: m_Fffpfs = %u", pTjxxhz->m_Fffpfs));
			offset += TJCX_FPFS_LEN;	

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TJCX_FPFS_LEN);
			pTjxxhz->m_Kffpfs = (UINT32)atoi(StrTempBuf);	//�շϷ�Ʊ����
			DBG_PRINT(("fptjcx: m_Kffpfs = %u", pTjxxhz->m_Kffpfs));
			offset += TJCX_FPFS_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, TJCX_FPFS_LEN);
			pTjxxhz->m_Qmkcfs = (UINT32)atoi(StrTempBuf);	//��ĩ������
			DBG_PRINT(("fptjcx: m_Qmkcfs = %u", pTjxxhz->m_Qmkcfs));
			offset += TJCX_FPFS_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			pTjxxhz->m_Zsfpljje = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//������Ʊ�ۼƽ��
			DBG_PRINT(("fptjcx: m_Zsfpljje = %lld", pTjxxhz->m_Zsfpljje));
			offset += JE_LEN;	
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			pTjxxhz->m_Zsfpljse = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//������Ʊ�ۼ�˰��
			DBG_PRINT(("fptjcx: m_Zsfpljse = %lld", pTjxxhz->m_Zsfpljse));
			offset += JE_LEN;

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			pTjxxhz->m_Zffpljje = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//���Ϸ�Ʊ�ۼƽ��
			DBG_PRINT(("fptjcx: m_Zffpljje = %lld", pTjxxhz->m_Zffpljje));		
			offset += JE_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			pTjxxhz->m_Zffpljse = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//���Ϸ�Ʊ�ۼ�˰��
			DBG_PRINT(("fptjcx: m_Zffpljse = %lld", pTjxxhz->m_Zffpljse));
			offset += JE_LEN;	

			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			pTjxxhz->m_Fsfpljje = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//������Ʊ�ۼƽ��
			DBG_PRINT(("fptjcx: m_Fsfpljje = %lld", pTjxxhz->m_Fsfpljje));			
			offset += JE_LEN;	
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			pTjxxhz->m_Fsfpljse = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//������Ʊ�ۼ�˰��
			DBG_PRINT(("fptjcx: m_Fsfpljse = %lld", pTjxxhz->m_Fsfpljse));		
			offset += JE_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			pTjxxhz->m_Fffpljje = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//���Ϸ�Ʊ�ۼƽ��
			DBG_PRINT(("fptjcx: m_Fffpljje = %lld", pTjxxhz->m_Fffpljje));	
			offset += JE_LEN;
			
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			pTjxxhz->m_Fffpljse = double2int(atof(StrTempBuf)*SUM_EXTENSION);	//���Ϸ�Ʊ�ۼ�˰��
			DBG_PRINT(("fptjcx: m_Fffpljse = %lld", pTjxxhz->m_Fffpljse));

			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;			
		}
	}

	return SUCCESS;
}

//��ҵ��Ϣ����
UINT8 CBusinessSerialProc::qyxxgx_Serial(CYWXML_GY &ywxml_gy, string &strErr)
{
	DBG_PRINT(("----------��ҵ��Ϣ����----------"));

	UINT8 cmdNo = SERIAL_QYXXGX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_kpjh, KPJH_LEN);
	DBG_PRINT(("ywxml_gy.m_kpjh : %s", ywxml_gy.m_kpjh.c_str()));

	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();

			return FAILURE;			
		}

		m_serialProtocol->resetAll();
	}

	return SUCCESS;
}


//����Ȩ�޸���
UINT8 CBusinessSerialProc::lxqxgx_Serial(CYWXML_GY &ywxml_gy, string &strErr)
{
	DBG_PRINT(("----------����Ȩ�޸���----------"));
	
	UINT8 cmdNo = SERIAL_LXQXGX_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_kpjh, KPJH_LEN);
	DBG_PRINT(("ywxml_gy.m_kpjh : %s", ywxml_gy.m_kpjh.c_str()));
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);	
			m_serialProtocol->resetAll();

			return FAILURE;			
		}

		m_serialProtocol->resetAll();

	}

	return SUCCESS;
}

//��Ʊʵʱ�ϴ�
UINT8 CBusinessSerialProc::fpsssc_Serial(CYWXML_GY &ywxml_gy, UINT8 czlx, UINT32 &fpzs, string &strErr)
{
	DBG_PRINT(("----------��Ʊʵʱ�ϴ�----------"));

	INT8 tempbuf[BUF_LEN];
	
	UINT8 cmdNo = SERIAL_FPSSSC_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", fpzs);
	m_serialProtocol->FillParament(tempbuf, FPZS_LEN);	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", czlx);
	m_serialProtocol->FillParament(tempbuf, CZLX_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_kpjh, KPJH_LEN);
	DBG_PRINT(("ywxml_gy.m_kpjh : %s", ywxml_gy.m_kpjh.c_str()));
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);	
			m_serialProtocol->resetAll();

			return FAILURE;			
		}

		m_serialProtocol->resetAll();

	}

	return SUCCESS;

}
//�������ά��
UINT8 CBusinessSerialProc::wlcswh_Serial(CNetPara *pNetPara, string &strErr)
{
	DBG_PRINT(("----------�����������----------"));
	INT8 tempbuf[BUF_LEN];
	
	UINT8 cmdNo = SERIAL_WLCSWH_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", pNetPara->m_IsDhcp);
	m_serialProtocol->FillParament(tempbuf, IFDTIP_LEN);
	m_serialProtocol->FillParament(pNetPara->m_LocalIP, IP_LEN);
	m_serialProtocol->FillParament(pNetPara->m_LocalGate, GATE_LEN);
	m_serialProtocol->FillParament(pNetPara->m_LocalMask, MASK_LEN);
	m_serialProtocol->FillParament(pNetPara->m_LocalDNS, DNS_LEN);
	m_serialProtocol->FillParament(pNetPara->m_ServIP, IP_LEN);
	m_serialProtocol->FillParament(pNetPara->m_ServPort, PORT_LEN);
	m_serialProtocol->FillParament(pNetPara->m_ServAddr, FWQBSLJ_LEN);
	m_serialProtocol->FillParament(pNetPara->m_FtpIP, IP_LEN);
	m_serialProtocol->FillParament(pNetPara->m_FtpPort, PORT_LEN);
	m_serialProtocol->FillParament(pNetPara->m_FtpUser, USERNAME_LEN);
	m_serialProtocol->FillParament(pNetPara->m_FtpPwd, PASSWORD_LEN);

	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);	
			m_serialProtocol->resetAll();

			return FAILURE;			
		}
		m_serialProtocol->resetAll();
	}

	return SUCCESS;
}

//���ô��ڲ�����
UINT8 CBusinessSerialProc::setBaudRate_Serial(UINT32 btl, string &strErr)
{
	DBG_PRINT(("----------���ò�����----------"));
	INT8 tempbuf[BUF_LEN];
	
	UINT8 cmdNo = SERIAL_SZCKBTL_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%06u", btl);
	DBG_PRINT(("�����ʣ�%u", btl));
	DBG_PRINT(("�����ʣ�%s", tempbuf));
	m_serialProtocol->FillParament(tempbuf, CKBTL_LEN);

	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
 		
		return FAILURE;
	}

	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
 		m_serialProtocol->resetAll();
 		
 		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);	
			m_serialProtocol->resetAll();
			
			return FAILURE;			
		}

		m_serialProtocol->resetAll();
	}

	return SUCCESS;
}

//��Ʊ����
UINT8 CBusinessSerialProc::fpdr_Serial(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr)
{
	DBG_PRINT(("----------��Ʊ����----------"));
	INT8 tempbuf[BUF_LEN];

	UINT8 cmdNo = SERIAL_FPDR_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", jzlx);
	m_serialProtocol->FillParament(tempbuf, JZLX_LEN);
	DBG_PRINT(("����Ľ�������%u", jzlx));
	DBG_PRINT(("��װ��Ľ�������%s", tempbuf));
	
	m_serialProtocol->FillParament(ywxml_gy.m_bspbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_bspkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();
			return FAILURE;			
		}

		m_serialProtocol->resetAll();
	}
	
	return SUCCESS;
}

//�ֻ��˻�
UINT8 CBusinessSerialProc::fjth_Serial(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr)
{
	DBG_PRINT(("----------�ֻ��˻�----------"));

	INT8 tempbuf[BUF_LEN];
	
	UINT8 cmdNo = SERIAL_FJTH_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", jzlx);
	m_serialProtocol->FillParament(tempbuf, JZLX_LEN);
	
	m_serialProtocol->FillParament(ywxml_gy.m_bspbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_bspkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);		
			m_serialProtocol->resetAll();

			return FAILURE;			
		}

		m_serialProtocol->resetAll();
	}

	return SUCCESS;
}

//���繺Ʊ
UINT8 CBusinessSerialProc::wlgp_Serial(CYWXML_GY &ywxml_gy, CInvVol *pInvVol, string &strErr)
{
	DBG_PRINT(("----------���繺Ʊ----------"));

	INT8 tempbuf[BUF_LEN];
	UINT8 cmdNo = SERIAL_WLGP_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);

	m_serialProtocol->FillParament(pInvVol->m_code, FPDM_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", pInvVol->m_isno);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", pInvVol->m_ieno);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);

	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", pInvVol->m_fpzfs);
	m_serialProtocol->FillParament(tempbuf, FPFS_LEN);

	m_serialProtocol->FillParament("", QTXX_LEN);

	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_kpjh, KPJH_LEN);
	DBG_PRINT(("ywxml_gy.m_kpjh : %s", ywxml_gy.m_kpjh.c_str()));
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);		
			m_serialProtocol->resetAll();

			return FAILURE;			
		}

		m_serialProtocol->resetAll();
	}

	return SUCCESS;
}


UINT8 CBusinessSerialProc::zsklgg_Serial(CYWXML_GY &ywxml_gy, string yzskl, string xzskl, string &strErr)
{
	DBG_PRINT(("----------֤��������----------"));
	
	UINT8 cmdNo = SERIAL_ZSKLBG_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(yzskl, KOULING_LEN);
	m_serialProtocol->FillParament(xzskl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);

	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);	
			m_serialProtocol->resetAll();
			
			return FAILURE;
		}

		m_serialProtocol->resetAll();
	}
	
	return SUCCESS;
}

UINT8 CBusinessSerialProc::fpbl_Serial(CYWXML_GY &ywxml_gy, UINT32 bsqsrq, UINT32 bszzrq, string &strErr)
{
	DBG_PRINT(("----------��Ʊ��¼----------"));
	
	UINT8 cmdNo = SERIAL_FPBL_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;
	
	m_serialProtocol->FillParament(ywxml_gy.m_nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbbh, SBBH_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_sksbkl, KOULING_LEN);
	m_serialProtocol->FillParament(ywxml_gy.m_fplxdm, FPLXDM_S_LEN);

	INT8 tempbuf[32];
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", bsqsrq);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);
	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", bszzrq);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);

	m_serialProtocol->FillParament(ywxml_gy.m_jqbh, JQBH_LEN);
	
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		if('E'==m_serialProtocol->m_rspCmd->head[0] && 'R'==m_serialProtocol->m_rspCmd->head[1])
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);	
			m_serialProtocol->resetAll();
			
			return FAILURE;			
		}
		
		m_serialProtocol->resetAll();
		
	}
	
	return SUCCESS;
}

UINT8 CBusinessSerialProc::hqlxsj_Serial(string &wscfpzs, string &wscfpsj, string &wscfpljje, string &sczs, string &scsjjg, string &strErr)
{
	DBG_PRINT(("----------��ȡ��������----------"));
	
	UINT32 offset = 0;
	UINT8 cmdNo = SERIAL_HQLXSJ_CMD;	//����Ÿ�ֵ
	enum ProtocolType cmdType = ZC_PROTOCOL;		
	UINT8 ret = m_serialProtocol->sendData(cmdType, cmdNo, strErr);
	if (ret != SUCCESS)
	{
		DBG_PRINT(("strErr : %s", strErr.c_str()));
		m_serialProtocol->resetAll();
		
		return FAILURE;
	}
	
	ret = m_serialProtocol->revData(strErr);
	DBG_PRINT(("ret = %u", ret));
	if (ret != SERCMD_SUCCESS)
	{
		DBG_PRINT(("strErr : %s", strErr.c_str()));
		m_serialProtocol->resetAll();
		
		DBG_PRINT(("revData() ret = %u", ret));
		return FAILURE;
	}
	if(ret == SERCMD_SUCCESS)
	{
		DBG_PRINT(("m_serialProtocol->m_rspCmd->head : %c%c", m_serialProtocol->m_rspCmd->head[0], m_serialProtocol->m_rspCmd->head[1]));
		DBG_NPRINT_HEX(m_serialProtocol->m_rspCmd->rspData, m_serialProtocol->m_rspCmd->dataLen);
		if('O'==m_serialProtocol->m_rspCmd->head[0] && 'K'==m_serialProtocol->m_rspCmd->head[1])
		{
			INT8 StrTempBuf[TMP_BUF_LEN];
		
			//δ�ϴ���Ʊ����
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, WSCFPZS_LEN);
			wscfpzs.assign(StrTempBuf);
			DBG_PRINT(("wscfpzs: %s", wscfpzs.c_str()));
			offset += WSCFPZS_LEN;
			
			//δ�ϴ���Ʊʱ��
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SZSJ_LEN);
			wscfpsj.assign(StrTempBuf);
			DBG_PRINT(("wscfpsj: %s", wscfpsj.c_str()));
			offset += SZSJ_LEN;
			
			//δ�ϴ���Ʊ�ۼƽ��
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, JE_LEN);
			wscfpljje.assign(StrTempBuf);
			DBG_PRINT(("wscfpljje: %s", wscfpljje.c_str()));
			offset += JE_LEN;
			
			//�ϴ�����
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SCZS_LEN);
			sczs.assign(StrTempBuf);
			DBG_PRINT(("sczs: %s", sczs.c_str()));
			offset += SCZS_LEN;
			
			//�ϴ�ʱ����
			memset(StrTempBuf, 0, sizeof(StrTempBuf));
			memcpy(StrTempBuf, m_serialProtocol->m_rspCmd->rspData+offset, SCSJJG_LEN);
			scsjjg.assign(StrTempBuf);
			DBG_PRINT(("scsjjg: %s", scsjjg.c_str()));
			
			m_serialProtocol->resetAll();
		}
		else
		{
			FindErrInfo((INT8 *)m_serialProtocol->m_rspCmd->rspData, strErr);
			m_serialProtocol->resetAll();	

			return FAILURE;			
		}
	}
	
	return SUCCESS;
}

UINT8 CBusinessSerialProc::FindErrInfo(INT8 *ErrBuf, string &strErr)
{

	DBG_PRINT(("ErrBuf =  %s", ErrBuf));
	DBG_PRINT(("ErrBuf =  0x%x", *ErrBuf));
	DBG_PRINT(("ErrBuf =  %d", *ErrBuf));
	
	UINT32 ErrLen = strlen(ErrBuf);
	DBG_PRINT(("ErrLen =  %d", ErrLen));
	

		//-1:����ת�������صĴ���
	if (ErrLen==1)
	{
		switch(*ErrBuf)
		{
		case SERCMD_HEAD_ERR:
		strErr = "-1:��ͷ���ݸ�ʽ����!";
			break;

		case SERCMD_HEAD_PARA_ERR:
		strErr = "-1:��ͷ���ݲ�������!";
			break;
			
		case SERCMD_CRC_ERR:
		strErr = "-1:����CRC��!";
			break;
			
		case SERCMD_CMDNO_ERR:
		strErr = "-1:������޷�ʶ��!";
			break;
			
		case SERCMD_OVERTIME_ERR:
			strErr = "-1:������ܳ�ʱ!";
			break;
			
		default:
			strErr = "�޷�����ת�������صĴ���";
			break;
	}
	}
	else
	{
		strErr = ErrBuf;
	}		
}