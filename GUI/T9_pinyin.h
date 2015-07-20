/************************************************************************
*�ļ�˵��: ��������ͷ�ļ�
*ʹ��˵��:
     �ļ���ƴ�����뷨��������ļ��������ַ���: abcdefghijklmnopqrstuvwxyz(Сд)
     ����ÿ���Ϸ����ַ���_pInput������unsigned char *GetPyIndex(unsigned char *_pInput)
     ������һ�������ַ�����մ�NULL;
     _pInputָ��Ŀռ�Ҫ������6���ֽڿռ䣬�����벻��6�ֽ�ʱ���ÿո�' '����
     ������ֻ��һ���ַ�ʱ����������5���Ը��ַ���ĸ�ĳ��ú���(��Ҳ�����������
     ����Ҫ���ַ������������������)�����ŵ�����Ϊ"zz",Ҳ�ɸı�{_PyMa_zz,"z}   "}�е�'z'
     ʹ�������Ҫ��
     _cByte�������¶��塣
��  �ߣ�  ���Ƿ�
��  �ڣ�  2004��9��27��
��  ����  0.9

****************************************************************************/
#ifndef		T9_CHNTOOL_H
#define		T9_CHNTOOL_H

#define 	T9PINYIN_SWITCH 		1

#if (T9PINYIN_SWITCH == 1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <wchar.h>


#ifndef SUCCESS
#define SUCCESS		1
#endif

#ifndef FAILURE
#define FAILURE		0
#endif

#define	PY_MAX_LENGTH	12

#define	PyIndex_i PyIndex_j
#define	PyIndex_u PyIndex_w
#define	PyIndex_v PyIndex_w
//#define NULL 0

typedef const char _cByte;     //�����ֽڣ����ڶ����ֿ���Ϣ

//��ƴ�����Ӧ����ĸ�����һ��
struct _PyIndexStru{
//	const char* _PyMa;
	const char* _YunMu;
};

//����������ƥ��
struct _KeyBuf    
{
        int KeyNum;           //1~8
        char* KeyStr;  //"abc","def"...
};

typedef struct _PyIndexStru _PyIndexType;


#ifdef __cplusplus
extern "C"
{
#endif

char IsPyStr(unsigned char* _pInput);      //�Ƿ�Ϊ��Чƴ��
unsigned char T9_Input(unsigned char *key, unsigned char *num, unsigned char (*PYBuf)[PY_MAX_LENGTH]); 	//������Ӧ����ĸ��������ϳ���Ч��ƴ��

#ifdef __cplusplus
}
#endif


#endif //T9PINYIN_SWITCH

#endif
