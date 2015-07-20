/*! \file    des.h
   \brief    des����
 */
#ifndef __DES_H
#define __DES_H

#include "comdatatype.h"
#include "SYSModuleHeader.h"

#if (USE_DES_FUNC!=0)


#ifdef __cplusplus
extern "C"
{
#endif
	
#define	DES_ECB_PADDING					1
#define	DES_ZERO_PADDING				2

#define	DES_PADDING_MODE			DES_ECB_PADDING	
	

INT32 des(UINT8 *source, UINT8 * dest, UINT8 * inkey, INT32 flg);


/*!
@brief ִ��3Des���ܡ�
@param[in] in  ԭ������
@param[in] in_len  ԭ�ĳ���
@param[out] out  ���ܺ�������
@param[in] flag  ��䷽ʽ��DES_ECB_PADDING��DES_ZERO_PADDING
@param[in] key  ��Կ
*/
int data_convert(unsigned char *in,int in_len,unsigned char * out,char flag,unsigned char *key);



#ifdef __cplusplus
}
#endif


#endif		//USE_DES_FUNC

#endif		//__DES_H


