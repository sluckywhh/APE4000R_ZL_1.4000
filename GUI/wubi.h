/************************************************************************
*�ļ�˵��: �������ͷ�ļ�
*ʹ��˵��:
    
��  �ߣ�  ������
��  �ڣ�  2007��07��02��
��  ����  1.0

****************************************************************************/
#ifndef		WUBI_H
#define		WUBI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comdatatype.h"


//98��
//#define MAX_WUBI_SIZE		68301
//#define WUBI_OFFSET			0x96200
//86��
#define MAX_WUBI_SIZE		68330
#define WUBI_OFFSET			0x96240

#define WUBI_BUFFER_SIZE	16
#define WUBI_BUFFER_LEN		16

struct WuBi_Index
{
	INT8 code[4];
	UINT8 size;
	UINT32 address;
};


/********************************************************************************
����     ������ϴβ�ѯ�еĹ��̱���
��ʽ     ��void T9_Strokes_Clear(void)
������� ��
����ֵ   ��
*********************************************************************************/

UINT8 Wubi_Strokes_enter(INT8 *enter_strokes, UINT8 *OutSize);
INT8 *Wubi_Result(UINT8 index);
#endif
