/*! \file    MaintenanceFunc.h
   \brief    awe4000r���۳�����ϵͳά���ĺ���
   \author   Yu Yan
   \version  1.0
   \date     2008-3-19
 */

#ifndef MAINTENANCE_FUNC_H
#define MAINTENANCE_FUNC_H

#include "IncludeMe.h"
#include "SysMacDef.h"
#include "CaMsgBox.h"

/*!
@brief yes/no��Ϣ��ʾ��	
@param[in] strInfo   ��ʾ����ʾ���ַ���
@return  1: SUCCESS���ǣ�; 0: FAILURE����
*/
UINT8 YesNoMsBox(string strInfo);


//-------�����Լ�--------//
/*!
@brief yes/no��Ϣ��ʾ��	
@param[in] strInfo   ��ʾ����ʾ���ַ���
@return  1: SUCCESS���ǣ�; 0: FAILURE����
*/
void PrintStr(INT8 *str);

/*!
@brief CPU�Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 CPUEvent(UINT8 IfForward);

/*!
@brief Beep�Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 BeepEvent(UINT8 IfForward);

/*!
@brief Ǯ���Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 BoxEvent(UINT8 IfForward);

/*!
@brief FLash�Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 FlashEvent(UINT8 IfForward);

/*!
@brief RAM�Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 RAMEvent(UINT8 IfForward);

/*!
@brief ����0�Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 COM0Event(UINT8 IfForward);

/*!
@brief ����2�Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 COM2Event(UINT8 IfForward);

/*!
@brief ��ӡ���Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 PrinterEvent(UINT8 IfForward);

/*!
@brief LCD�Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 LCDEvent(UINT8 IfForward);

/*!
@brief �����Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 KeyboardEvent(UINT8 IfForward);

/*!
@brief USB�Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 USBEvent(UINT8 IfForward);
UINT8 USBEvent2(UINT8 IfForward);

/*!
@brief IC���Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 ICCardEvent(UINT8 IfForward);

/*!
@brief ���������Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 ContinuousTestEvent(void);

/*!
@brief ������ʱ�Լ����	
@param[in] IfForward   �Ƿ��ֽ 1=��ֽ�� 0=����
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 MachineAutoCheck(void);

//-----------��������
/*!
@brief ������������	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 DownloadFCRCode(void);

//-----------MAC����
/*!
@brief MAC��ַ����
@param[in] nMacLen   ���mac��ַ�Ļ��������� ����С��18��
@param[out] pMacAddr   ���mac��ַ�Ļ������׵�ַ	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 DownloadMAC(INT8* pMacAddr, INT32 nMacLen);


/*!
@brief ���̰���	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 CheckKey(UINT8 &nKeyTime);

#endif
