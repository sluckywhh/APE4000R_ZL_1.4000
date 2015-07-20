#include"CaLabel.h"
#include "display.h"

#include"LOGCTRL.h"
#include"pos_debug.h"

CaLabel::CaLabel(bool bFocus,ALIGN_TYPE alType,int objtype):CaObject(objtype,bFocus)
{
	m_bFocus=bFocus;
	m_iTitleLen=0;
	m_iAlignType=alType;
	memset( m_caTitle, 0, OBJ_TITLE_MAX_LEN );
	memset( m_caTitleImgBuf, 0, OBJ_TITLE_MAX_LEN*IMG_BYTES );
	m_iBoxType=BOX_NO;
}
CaLabel::CaLabel(bool bFocus,ALIGN_TYPE alType,CaGroup *pOwner):CaObject(CA_LABEL,bFocus,pOwner)
{
	m_bFocus=bFocus;
	m_iTitleLen=0;
	m_iAlignType=alType;
	memset( m_caTitle, 0, OBJ_TITLE_MAX_LEN );
	memset( m_caTitleImgBuf, 0, OBJ_TITLE_MAX_LEN*IMG_BYTES );
	m_iBoxType=BOX_NO;
}

CaLabel::CaLabel():CaObject(CA_LABEL,false)
{
	m_bFocus=false;
	m_iTitleLen=0;
	m_iAlignType=ALIGN_LEFT;
	m_iBoxType=BOX_NO;
	memset( m_caTitle, 0, OBJ_TITLE_MAX_LEN );
	memset( m_caTitleImgBuf, 0, OBJ_TITLE_MAX_LEN*IMG_BYTES );
}
CaLabel::~CaLabel()
{

}

int CaLabel::SetFocus()
{
// if(m_bFocus)
// {
	 return SetFocusIn();
// }
// else
// {
//	 return -1;
// }
}
int CaLabel::ReFresh()
{
	if(!IsRefreshAble())
	{
		return 0;
	}
	if(m_iTitleLen>0)
	{
//		LCDPutImage(m_iX+(m_iW-m_iTitleLen*CHAR_W)/2,m_iY,m_iTitleLen*CHAR_W,GRID_LINE_H,(char *)m_caTitleImgBuf+BUF_OFFSET);
				LCDPutImage(m_iX+(m_iW-(m_iW/CHAR_W)*CHAR_W)/2,m_iY,(m_iW/CHAR_W)*CHAR_W,GRID_LINE_H,(char *)m_caTitleImgBuf+BUF_OFFSET);
				m_bRefreshFlag=true;
	}
	DrawBox();
	return 1;
}
int CaLabel::SetFocusIn()
{
	if(!IsRefreshAble())
	{
		return 0;
	}
	LCDPutImageRev(m_iX+(m_iW-(m_iW/CHAR_W)*CHAR_W)/2,
		m_iY,(m_iW/CHAR_W)*CHAR_W,GRID_LINE_H,(char *)m_caTitleImgBuf+BUF_OFFSET);

//	LCDRedraw();
	m_bRefreshFlag=true;
//	DBG_PRN("------------",("LCDRedraw"));

//	LCDPutImageRev(m_iX+(m_iW-m_iTitleLen*CHAR_W)/2,
//		m_iY,m_iTitleLen*CHAR_W,GRID_LINE_H,(char *)m_caTitleImgBuf+BUF_OFFSET);
	return 1;
}

//������д��ĳ���ڴ�����

int CaLabel::SetTitle(const char * pData, int iLen)
{
	DBG_ASSERT_EXIT((pData != 0 ),(" pData is null!"));

	memset( m_caTitle, 0, OBJ_TITLE_MAX_LEN );
	memset( m_caTitleImgBuf, 0, OBJ_TITLE_MAX_LEN*IMG_BYTES );

	int len = ( iLen <= OBJ_TITLE_MAX_LEN )?iLen:OBJ_TITLE_MAX_LEN;
	memcpy( m_caTitle, pData, len );
	m_iTitleLen = len;

	int bufLen=m_iW/CHAR_W;
	char buf[OBJ_TITLE_MAX_LEN+2];
	AlignBuf(pData,buf,bufLen,m_iAlignType);

	str2image((unsigned char *)buf,bufLen,m_caTitleImgBuf);

	return len;	
}
//������д��ĳ���ڴ�������?
int CaLabel::GetTitle(char *pData,int &iLen)
{
	DBG_ASSERT_EXIT((pData != 0 ),(" pData is null!"));
	if (m_iTitleLen == 0)//m_iTitleLen = 0ʱ��memecpy����
	{
		iLen = 0;
		return 0;
	}
	int len = ( iLen <= m_iTitleLen )?iLen:m_iTitleLen;
	
	memcpy(pData, m_caTitle,  len );
	iLen=len ;
	return len;
}
void CaLabel::SetTitleAlign(ALIGN_TYPE alType)
{
	if(	m_iAlignType==alType)
	{
		return;
	}
	else
	{
		m_iAlignType=alType;
		memset( m_caTitleImgBuf, 0, OBJ_TITLE_MAX_LEN*IMG_BYTES );
		int bufLen=m_iW/CHAR_W;
		char buf[OBJ_TITLE_MAX_LEN+2];
		AlignBuf((char *)m_caTitle,buf,bufLen,m_iAlignType);
		str2image((unsigned char *)buf,bufLen,m_caTitleImgBuf);		
	}
}


