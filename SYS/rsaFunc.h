/*! \file    rsaFunc.h
   \brief    Rsa�ӽ��ܽӿڶ���
 */
#ifndef __APE_RSA__FUNC_H
#define __APE_RSA__FUNC_H

#include "SYSModuleHeader.h"
#include "rsa.h"

#if (USE_RSA_FUNC!=0)


#ifdef __cplusplus
extern "C"
{
#endif



#define	RSA_PRI_KEY_FILE_DEF		"private.pem"
#define	RSA_PUB_KEY_FILE_DEF		"public.pem"

#define	RSA_PKC_MODE_DEF		RSA_PKCS1_PADDING

#define RSA_SUCCESS				0
#define RSA_OPEN_FILE_ER		-1
#define RSA_READ_PRIV_KEY_ER	-2
#define RSA_READ_PUB_KEY_ER		-3
#define RSA_ENCRYPT_ER			-4
#define RSA_DECRYPT_ER			-5
#define RSA_OUT_BUFF_OVERFLOW	-6



/*!
@brief Rsa��Կ���ܡ�
@param[in] inlen  ԭ�ĳ���
@param[in] from  ԭ��
@param[in,out] outlen  �������������ȣ��������ʵ�ʳ���
@param[out] to  �������
@param[in] pubfileName  ��Կ�����ļ���
*/
int encryptByPubKey(int inlen, unsigned char *from, int *outlen, unsigned char *to, char *pubfileName);

/*!
@brief Rsa˽Կ���ܡ�
@param[in] inlen  ���ĳ���
@param[in] from  ����
@param[in,out] outlen  ����ԭ�������ȣ����ԭ��ʵ�ʳ���
@param[out] to  ���ԭ��
@param[in] prifileName  ˽Կ�����ļ���
*/
int decryptByPriKey(int inlen, unsigned char *from, int *outlen, unsigned char *to, char *prifileName);

/*!
@brief Rsa˽Կ���ܡ�
@param[in] inlen  ԭ�ĳ���
@param[in] from  ԭ��
@param[in,out] outlen  �������������ȣ��������ʵ�ʳ���
@param[out] to  �������
@param[in] prifileName  ˽Կ�����ļ���
*/
int encryptByPriKey(int inlen, unsigned char *from, int *outlen, unsigned char *to, char *prifileName);

/*!
@brief Rsa��Կ���ܡ�
@param[in] inlen  ���ĳ���
@param[in] from  ����
@param[in,out] outlen  ����ԭ�������ȣ����ԭ��ʵ�ʳ���
@param[out] to  ���ԭ��
@param[in] pubfileName  ��Կ�����ļ���
*/
int decryptByPubKey(int inlen, unsigned char *from, int *outlen, unsigned char *to, char *pubfileName);



/*!
@brief Rsaǩ����
@param[in] inlen  ԭ�ĳ���
@param[in] from  ԭ��
@param[in,out] siglen  ����ǩ�������ȣ����ǩ��ʵ�ʳ���
@param[out] sigbuff  ���ǩ��
@param[in] prifileName  ˽Կ�����ļ���
*/
int rsaSign(int inlen, unsigned char *from, int *siglen, unsigned char *sigbuff, char *prifileName);


/*!
@brief Rsa��ǩ��
@param[in] inlen  ���ĳ���
@param[in] from  ����
@param[in] siglen  ǩ������
@param[out] sigbuff  ǩ������
@param[in] pubfileName  ��Կ�����ļ���
*/
int rsaVerify(int inlen, unsigned char *from, int siglen, unsigned char *sigbuff, char *pubfileName);



#ifdef __cplusplus
}
#endif


#endif		//USE_RSA_FUNC


#endif		//__APE_RSA__FUNC_H


