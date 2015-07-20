/************************************************************************
*�ļ�˵��: ��������ͷ�ļ�
*ʹ��˵��:
    
��  �ߣ�  ������
��  �ڣ�  2007��08��03��
��  ����  1.0

****************************************************************************/
#ifndef		__PHRASE_H
#define		__PHRASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comdatatype.h"

#define MAX_PHRASE_SIZE		8030
#define PHRASE_OFFSET		0xdb30
#define PHRASE_BUFFER_SIZE	64
#define PHRASE_BUFFER_LEN		16

struct Phrase_Index
{
	UINT16 code;
	UINT8 size;
	UINT32 address;
};
#ifdef __cplusplus
extern "C"
{ 
#endif
/********************************************************************************
����     ����������
��ʽ     ��UINT8 Phrase_Strokes_enter(INT8 *enter_strokes, UINT8 *OutSize);
������� ��
����ֵ   ��
*********************************************************************************/

UINT8 Phrase_Strokes_enter(INT8 *enter_strokes, UINT8 *OutSize);
INT8 *Phrase_Result(UINT8 index);

#ifdef __cplusplus
}
#endif

#endif

