/****************************************************************************
�ļ���           ��PowOffRecover.h
����             ��awe4000r�����е�Ӧ�ú�����
��ʼ����         ��2008-01-31
����             ��Yu Yan     
****************************************************************************/

#ifndef POWER_OFF_RECOVER_H
#define POWER_OFF_RECOVER_H

#include "powoff_protect.h"
#include "SaleData.h"

//------�������̵ĵ���ָ�

/*!
@brief ����ӡ��Ʊ�ṹ��ķ�Ʊͷ
@param[in] invFullInfo ��Ʊͷ��Ϣ�ṹ��ָ��
@param[out] smallInvInfo ��Ʊ������Ϣָ��
@return  1�� �ɹ��� ������ʧ��
*/
UINT8 InvStuctToClass(struct TInvFullInfo *invFullInfo, CInvHead *smallInvInfo);

/*!
@brief ��Ʊ�ָ�
@param[in] invFullInfo ��Ʊͷ��Ϣ�ṹ��ָ��
@param[in] nChildId ����ָ��ӹ��̺�
@return  1�� �ɹ��� 0��ʧ��
*/
UINT8 MakeInvRecover(struct TInvFullInfo *invFullInfo, UINT8 nChildId);

/*!
@brief �����ָ�
@return  1�� �ɹ��� 0��ʧ��
*/
UINT8 RollRecover(void);



//-----�ܵ���ָ�

/*!
@brief ����ָ�
@return  1�� �ɹ��� 0��ʧ��
*/
UINT8 poweroff_recover();

/*!
@brief ����ָ�������ʾ
@param[in] strInfo ��ʾ��Ϣ
*/
void ShowMsg(string strInfo);

#endif
