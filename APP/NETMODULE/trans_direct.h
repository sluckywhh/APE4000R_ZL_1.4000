/**
 @file  trans_direct.h
 @brief ���ļ���������Ӧ�ò�Э���µĴ����ࡣ
 */
#ifndef	__H_TRANS_DIRECT_
#define	__H_TRANS_DIRECT_

#include "IncludeMe.h"
#include "netHeaderDef.h"
#include "trans_abstrac.h"



/**
 @class trans_direct 
 @brief ʵ����Ӧ�ò�Э��Ĵ��䡣
 */
class trans_direct : public trans_abstrac
{
public:
	trans_direct(Sending *p);
	virtual ~trans_direct();

private:
	int sendData(UINT8 *psBuf, INT32 sLen, UINT8 *prBuf, INT32 *rLen, string &strErr);


};





#endif

