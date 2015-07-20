/*! \file    InvVolFun.cpp
\brief    ƱԴ����Ӧ�ú���
\author   zcy
\version  1.0
\date     2015-05-07
*/

#ifndef _INVVOL_FUN_H
#define _INVVOL_FUN_H

#include "IncludeMe.h"
#include <string>
using namespace std;


/*!
@brief ��ȡƱԴ����Ϣ�������浽inv_vol��
@brief ��Ӧֱ���淶��ı�˰�̷�Ʊ��ѯ������Ʊ���ѯ
@param[out] uNum    ƱԴ����Ϣ	
@param[out] strErr  ��Ϣ����ʾ��Ϣ 
@return  1��SUCCESS��0��FAILURE
*/
UINT8 INV_GetInvVol(UINT32 &uNum,string &strErr);


/*!
@brief ���繺Ʊ������ƱԴ����
@param[in] strCode  ��Ʊ���� 
@param[in] uStartNo  ��Ʊ��ʼ����
@param[in] uNum  ��Ʊ�ܷ��� 
@param[out] strErr  ��Ϣ����ʾ��Ϣ 
@return  1��SUCCESS��0��FAILURE
*/
UINT8 INV_NetInvVol(string strCode,UINT32 uStartNo,UINT32 uNum, string &strErr);

/*!
@brief ���繺Ʊ���ȷ��
@param[in] strCode  ��Ʊ���� 
@param[in] uStartNo  ��Ʊ��ʼ����
@param[in] uEndNo  ��Ʊ�ܷ��� 
@param[out] strErr  ��Ϣ����ʾ��Ϣ 
@return  1��SUCCESS��0��FAILURE
*/
// UINT8 INV_NetInvVolVerify(string strCode,UINT32 uStartNo,UINT32 uEndNo, string &strErr);

/*!
@brief �ѽ�˰����ƱԴ��ȡƱԴ��	
@param[in] uJZlx   ��������
@param[out] strErr  ��Ϣ����ʾ��Ϣ 
@return  1��SUCCESS��0��FAILURE
*/
UINT8 INV_ReadInvVol(UINT8 uJZlx,string &strErr);


/*!
@brief ������Ʊ
@param[in] uJZlx   ��������	
@param[in] string strCode ��Ʊ����
@param[in] UINT32 uNo ��Ʊ��ʼ��
@param[in] UINT32 uNum ��Ʊ����
@param[out] strErr  ��Ϣ����ʾ��Ϣ 
@return  1��SUCCESS��0��FAILURE
*/
UINT8 INV_HostToInvVol(UINT8 uJZlx,string strCode,UINT32 uNo,UINT32 uNum,string &strErr);

/*!
@brief ��Ʊ�˻�	
@param[in] uJZlx   ��������
@param[in] string strCode ��Ʊ����
@param[in] UINT32 uNo ��Ʊ��ʼ��
@param[in] UINT32 uNum ��Ʊ����
@param[out] strErr  ��Ϣ����ʾ��Ϣ 
@return  1��SUCCESS��0��FAILURE
*/
UINT8 INV_RetToInvVol(UINT8 uJZlx,string strCode,UINT32 uNo,UINT32 uNum,string &strErr);


/*!
@brief ��������ֻ��˻ط�Ʊ
@param[out] strErr  ��Ϣ����ʾ��Ϣ 
@return  1��SUCCESS��0��FAILURE
*/
UINT8 INV_HostGetInvVol(UINT8 uJZlx,string &strErr);


/*!
@brief ѡ���������
@param[out] uJZlx   ��������
@param[out] strErr  ��Ϣ����ʾ��Ϣ 
@return  1��SUCCESS��0��FAILURE
*/
UINT8 INV_MediumType(UINT8 &uJZlx,string &strErr);

/*!
@brief ѡ���������
@param[out] strErr  ��Ϣ����ʾ��Ϣ 
@return  1��SUCCESS��0��FAILURE
*/
UINT8 INV_InvoiceUpload(string &strErr);

#endif
