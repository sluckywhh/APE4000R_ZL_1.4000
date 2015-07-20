
/*! \file  keypad.h
\brief     ��������  
\author   zl
*/

/*-----------------------���̲��ֵĽӿں���-------------------------*/
#ifndef KEYPAD_POS_DESIGN_H
#define KEYPAD_POS_DESIGN_H
#include "VersionConfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if (POS_TYPE == POS_APE3000R)
#define SINGLE_KEY_MAX_NUMBER	80
#else
#define SINGLE_KEY_MAX_NUMBER	34
#endif

#define DOUBLE_KEY_MAX_NUMBER	20

#define KEYPAD_MAX_ROW		5
#define KEYPAD_MAX_COL		7

#define MAX_KEYMAP_NUM		99

#define	GET_SINGLEKEY_VALUE(x1,y1)			((UINT32)(x1<<8 | y1))
#define	GET_DOUBLEKEY_VALUE(x1,y1,x2,y2)	((UINT32)(x1<<24 | y1<<16 | x2<<8 | y2))


#define KEYPAD_MAGIC 'k'
#define KEYPAD_MAXNR  3
#define KPD_BLOCK					_IOW('k', 1, unsigned int)
#define KPD_NONBLOCK				_IOW('k', 2, unsigned int)
#define KPD_SET_CONTINUOUS_MODE		_IOW('k', 3, unsigned int)


typedef struct _KeyStruct
{
	unsigned char type;		//�������ͣ�1��3��Ӧ����/˫��/����
	unsigned short row1;
	unsigned short col1;
	unsigned short row2;
	unsigned short col2;
}KeyStruct;


typedef struct _SingleKey
{
	unsigned short row1;
	unsigned short col1;
	unsigned char key;
	unsigned char flag;		//�Ƿ�ɸ��ļ�ֵ���� 0���ɸģ�1�����ɸ�
}SingleKey;

typedef struct _DoubleKey
{
	unsigned short row1;
	unsigned short col1;
	unsigned short row2;
	unsigned short col2;
	unsigned char key;
	unsigned char flag;		//�Ƿ�ɸ��ļ�ֵ���� 0���ɸģ�1�����ɸ�
}DoubleKey;

/*!
@brief ���̿��� 
*/
void KeyEnable(void);

/*!
@brief ���̹ر�
*/
void KeyDisable(void);

/*!
@brief ��ȡ������ֵ
@return ��ȡ����ֵ 
*/
unsigned char ReadKeypad(void);

/*!
@brief ��������������Ӧģʽ
@param[in] mode 1 - ��Ӧ��������
                0 - ����Ӧ 
*/
void SetKeypadPressMode(unsigned int mode);

#ifdef __cplusplus
}
#endif

#endif
