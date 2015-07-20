/**
 @file  trans_CURL.h
 @brief ���ļ��������������ݴ�����trans_CURL������ʹ��CURL�������ݴ��䡣
 */

#ifndef	__H_TRANS_BY_CURL_
#define	__H_TRANS_BY_CURL_

#include "IncludeMe.h"
#include "netHeaderDef.h"
#include "transfers_base.h"
#include "MycUrlHttp.h"



/**
 @class trans_CURL 
 @brief ����ʹ��CURL����ʵ���������ݴ��䡣
 */
class trans_CURL : public CNetTransfers
{
public:
	trans_CURL();
	virtual ~trans_CURL();

	void SetServerIP(const string IP, const string Port);
	int CheckServerLink(string &strErr);


private:
	TCUrlModel m_curModel;			/**< CURL��������� */
	
	int trans_proc(UINT8 *psBuf, INT32 sLen, UINT8 *prBuf, INT32 *rLen, string &strErr);

	
};


#endif




