/*! \file    TemplateGeneralFuc.h
\brief    ��ӡģ��ͨ�ú���
\author   Xiao Pengkun   2005-07-20
 */

#ifndef TEMPLATE_GENERAL_FUN_H
#define TEMPLATE_GENERAL_FUN_H


#ifdef __cplusplus
extern "C"
{
#endif

#include "TemplateDataDesign.h"

//----------------------------------------------------
//��Ʒȡ����־��Ӧ���ڲ����������У���ӡȡ����Ʒ����Ҫ
extern UINT8 DetailCancelFlag;
extern UINT8 g_cungen;
extern UINT8 is_gb_4byte(unsigned char *str);
extern UINT32 HZCount(UINT8 *str, UINT32 len, 
			   UINT8 *num_asc, UINT8 *num_hz2B, UINT8 *num_hz4B);
//----------------------------------------------------


/*!
@brief �жϰ�����ֵĸ���
@param[in] str	��Ҫ�жϵ��ַ���
@param[in] len	�ַ�������
@note �ж��ַ����а�����ֵĸ��������Ϊ����������Ҫ���д���
@return  ������ֵĸ���
*/
UINT32 GetHalfHZCount(UINT8 *str,UINT32 len);


/*!
@brief ��ȡ��ӡģ�壨�ļ�������
@param[in] p	
@note ����ָ�룬��û��棬����ָ��ָ�����뵽�Ļ��档
@return  
*/
void GetPrintTemplateBuffer(void **p); 
/*!
@brief ��ȡ���մ�ӡ�л���
@param[in] p	
@note ����ָ�룬��û��棬����ָ��ָ�����뵽�Ļ��档
@return  
*/
void GetPrintLineBuffer(void **p);


/*!
@brief ��ȡ��ӡģ��ÿһ�л���
@param[in] p	
@note ����ָ�룬��û��棬����ָ��ָ�����뵽�Ļ��档
@return  
*/
void GetTemplateLineBuffer(void **p);


/*!
@brief ��ȡÿһ��ģ����������~֮������ݻ���
@param[in] p	
@note ����ָ�룬��û��棬����ָ��ָ�����뵽�Ļ��档
@return  
*/
void GetTemplateLineFieldBuffer(void **p);


/*!
@brief ��ȡ����ƥ������~֮������ݱ�ǩ�Ļ���
@param[in] p	
@note ����ָ�룬��û��棬����ָ��ָ�����뵽�Ļ��档
@return  
*/
void GetMatchFieldLabelBuffer(void **p);

/*!
@brief ��ʼ�����մ�ӡ��
@param[in] prnLineInfo	
@note ����ӡ�����ݽṹ��ʼ��������chContent����Ϊ�ո񣬽�βΪ'\0'��
@return  
*/
void InitPrinLineInfo(TPrnLineInfo *prnLineInfo);


/*!
@brief ��chContent�е�'\0'�滻Ϊ�ո�' ',���˽�β
@param[in] pPrnLineInfo	
@note �����������ӡ���еĽ������滻Ϊ�ո�ʹ�����ݿ��Դ�ӡ������
@return  
*/
void ScanReplaceSpace(TPrnLineInfo *pPrnLineInfo);

#ifdef __cplusplus
}
#endif

#endif

