/************************************************************************
*�ļ�˵��: �ʻ������ѯ�㷨ͷ�ļ�
*ʹ��˵��:
��  �ߣ�  
��  �ڣ�  

****************************************************************************/
#ifndef		T9_BIHUA_H
#define		T9_BIHUA_H

#define 	T9BIHUA_SWITCH 		1

#if (T9BIHUA_SWITCH == 1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define IC1_BIHUA_START_ADDR              	0		
#define IC1_BIHUA_INDEX_START_ADDR          (IC1_BIHUA_START_ADDR+124*(1<<10))				


struct BiHua_Index
{
	INT8 bihua_num;			//�ʻ���
	INT32 startNo_index;		//��ʼ��(ǰ4λ)
	INT32 endNo_index;		//��ֹ��(��4λ)
	INT32 offset;				//��������ֵ
	INT32 Hanzi_num;			//������������
};

struct HanZi_Info
{
	INT32 bihua_code;
	INT8 GB_code[2];
};

struct _BHIndexBlock
{
	UINT8 start;
	UINT8 end;
};

struct _HZoffsetBlock
{
	UINT32 start;
	UINT32 end;
};

#ifdef __cplusplus
extern "C"
{
#endif
/********************************************************************************
����     ������ϴβ�ѯ�еĹ��̱���
��ʽ     ��void T9_Strokes_Clear(void)
������� ��
����ֵ   ��
*********************************************************************************/
void T9_Strokes_Clear(void);

/********************************************************************************
����     ���Ե�ǰƫ��Ϊ׼��������5������
��ʽ     ��T9_Strokes_pageDown(UINT8 *outbuff, UINT8 *outsize)
������� ��outbuff���ҵ��ĺ���
		   outsize���ҵ��ĺ��ָ���
����˵�� ��ÿ�ζ��������֣���outbuff�����5������outsize=6��˵����5�����ֺ������к��֡�
*********************************************************************************/
void T9_Strokes_pageDown(UINT8 *outbuff, UINT8 *outsize);

/********************************************************************************
����     ���Ե�ǰƫ��Ϊ׼����ǰ����5������
��ʽ     ��T9_Strokes_pageUP(UINT8 *outbuff, UINT8 *outsize)
������� ��outbuff���ҵ��ĺ���
		   outsize���ҵ��ĺ��ָ���
����˵�� ��ÿ�ζ��������֣���outbuff�����5������outsize=6��˵����5�����ֺ������к��֡�
*********************************************************************************/
void T9_Strokes_pageUP(UINT8 *outbuff, UINT8 *outsize);

/********************************************************************************
����     ��T9�ʻ����룬��������ıʻ���������ϵĺ���(1��5��)
��ʽ     ��T9_Strokes_enter(UINT8 *enter_strokes, UINT8 *OutHanZi)
������� ��enter_strokes���ʻ���
������� ��OutHanZi������ĺ��ִ�
		   OutSize������ĺ��ָ���
����ֵ   ��1���ҵ� 0�����ҵ�
����˵�� ��ÿ�ζ��������֣���OutHanZi���ǰ(��)5������outsize=6��˵����5�����ֺ�(ǰ)�����к��֡�
*********************************************************************************/
UINT8 T9_Strokes_enter(UINT8 *enter_strokes, UINT8 *OutHanZi, UINT8 *OutSize);

#ifdef __cplusplus
}
#endif


#endif	//T9BIHUA_SWITCH

#endif
