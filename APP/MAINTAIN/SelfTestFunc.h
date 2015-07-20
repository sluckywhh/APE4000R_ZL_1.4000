/****************************************************************************
�ļ���           ��SelfTestFunc.cpp
����             ��awe4000r���۳����л����Լ�ĵײ㺯����
��ʼ����         ��2008-3-19 
����             ��Yu Yan     
****************************************************************************/
#ifndef SELF_TEST_FUNC_H
#define SELF_TEST_FUNC_H

#include "IncludeMe.h"
#include "SysMacDef.h"
#include "CaMsgBox.h"


/*!
@brief CPU�Լ�	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 CPUTest();

/*!
@brief Flash�Լ�	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 FlashTest(void);

/*!
@brief RAM�Լ�	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 RAMTest(void);

/*!
@brief COM0�Լ�	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 COM0Test(void);

/*!
@brief COM2�Լ�	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 COM2Test(void);

/*!
@brief ��ʾ���Լ�	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 LCDTest(void);

/*!
@brief �����Լ�	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 KeyboardTest(void);

/*!
@brief USB�Լ�	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 USBTest(void);

/*!
@brief �������Լ�	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 BeepTest(void);

/*!
@brief Ǯ���Լ�	
@return  1: SUCCESS; 0: FAILURE
*/
UINT8 MoneyBoxTest(void);


#endif


