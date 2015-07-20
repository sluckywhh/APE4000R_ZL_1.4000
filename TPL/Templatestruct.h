/*! \file    Templatestruct.h
\brief    ��Ʊ��ӡ��ؽṹ�嶨���ļ�
\author   zfj
 */

#ifndef TEMPLATE_H
#define TEMPLATE_H
#include "comdatatype.h"

#define NAME_LEN                      30     ///��Ʊͷ���������ֶ�
#define VALUE_LEN   	 	          200	 ///��Ʊ��������

#define  ATTRIBUTENAMECOUNT           100    ///̧ͷ����
#define  ATTRIBUTEVALUECOUNT          100    ///��ӡ��������

#define  NORMAL_PRINT                 0     //��ͨ��ӡ
#define  ALL_PRINT                    1     //(ȫ��ӡ)���Ӵ����ӡ
#define  TEST_PRINT					  2



#ifdef WIN32

PACK_PREFIX struct TmpAttribute 
{
	UINT32		nPaperLen;				//����	
	UINT32		nPaperWidth;			//���
	UINT8		bClockLen;				//������־
	UINT32		nTextHeight;			//�ָ�
	UINT32		nTextWith;				//�ֿ�
	UINT32		nDy;					//�м�ࣨ��y����
	UINT32		nDx;					//�ּ��(��x����)
	UINT32		nPrntendLen;			//��ӡ����ֽ����
	UINT32		nPrntBegLen;			//��ӡǰ��ֽ����
	UINT32      nxPos;                  //��ӡ��ͷ����ƫ��
	UINT32      nyPos;                  //��ӡ��ͷ����ƫ��
	UINT8       nPrntType;              //��ӡģʽ--�״� 1 ��ͨ��ӡ  0
	UINT8       nAutoPaper;             //�Ƿ��Զ���ֽ
};

//��Ʊ̨ͷ�ṹ��,���Եĺ��ֲ���
PACK_PREFIX struct TmpAttributeName
{
	UINT16		ID;
	UINT16		TYPE;
	UINT8		bPrnted;				//��ӡ��־,�Ƿ��Ѿ���ӡ
	UINT32		nX;
	UINT32		nY;
   	UINT32      nRight;
	UINT32      nBottom;
	UINT8		content[NAME_LEN];//�洢����
};

//���Ե�ֵ
PACK_PREFIX struct TmpAttributeValue
{
	UINT16		ID;
	UINT16		TYPE;
	UINT8		bPrnted;				   //��ӡ��־,�Ƿ��Ѿ���ӡ
	UINT32		nX;						   //��ӡ���
	UINT32		nY;						   //��ӡ�϶�
	UINT32      nRight;					   //��ӡ�Ҷ�
	UINT32      nBottom;				   //��ӡ��ײ�λ��
	UINT8		content[VALUE_LEN];        //�洢����
	UINT8       curLine;                   //��ǰ��ӡ��
};

//�洢ģ������
PACK_PREFIX struct  TmplateData
{
  struct TmpAttribute        tmpattrData;
  struct TmpAttributeName    tmpattrnameData[ATTRIBUTENAMECOUNT];   //��ӡģ��̧ͷ����
  struct TmpAttributeValue   tmpPrntValueData[ATTRIBUTEVALUECOUNT];  //��ӡ����
};

#else
//ģ����������
PACK_PREFIX struct TmpAttribute 
{
	UINT32		nPaperLen;				//����	
	UINT32		nPaperWidth;			//���
	UINT8		bClockLen;				//������־
	UINT32		nTextHeight;			//�ָ�
	UINT32		nTextWith;				//�ֿ�
	UINT32		nDy;					//�м�ࣨ��y����
	UINT32		nDx;					//�ּ��(��x����)
	UINT32		nPrntendLen;			//��ӡ����ֽ����
	UINT32		nPrntBegLen;			//��ӡǰ��ֽ����
	UINT32      nxPos;                  //��ӡ��ͷ����ƫ��
	UINT32      nyPos;                  //��ӡ��ͷ����ƫ��
	UINT8       nPrntType;              //��ӡģʽ--�״� 1 ��ͨ��ӡ  0
	UINT8       nAutoPaper;             //�Ƿ��Զ���ֽ
} __attribute__ ((packed));

//��Ʊ̨ͷ�ṹ��,���Եĺ��ֲ���
PACK_PREFIX struct TmpAttributeName
{
	UINT16		ID;
	UINT16		TYPE;
	UINT8		bPrnted;				//��ӡ��־,�Ƿ��Ѿ���ӡ
	UINT32		nX;
	UINT32		nY;
   	UINT32      nRight;
	UINT32      nBottom;
	UINT8		content[NAME_LEN];//�洢����
} __attribute__ ((packed));

//���Ե�ֵ
PACK_PREFIX struct TmpAttributeValue
{
	UINT16		ID;
	UINT16		TYPE;
	UINT8		bPrnted;				   //��ӡ��־,�Ƿ��Ѿ���ӡ
	UINT32		nX;						   //��ӡ���
	UINT32		nY;						   //��ӡ�϶�
	UINT32      nRight;					   //��ӡ�Ҷ�
	UINT32      nBottom;				   //��ӡ��ײ�λ��
	UINT8		content[VALUE_LEN];        //�洢����
	UINT8       curLine;                   //��ǰ��ӡ��
} __attribute__ ((packed));

//�洢ģ������
PACK_PREFIX struct  TmplateData
{
  struct TmpAttribute        tmpattrData;
  struct TmpAttributeName    tmpattrnameData[ATTRIBUTENAMECOUNT];   //��ӡģ��̧ͷ����
  struct TmpAttributeValue   tmpPrntValueData[ATTRIBUTEVALUECOUNT];  //��ӡ����
} __attribute__ ((packed));

#endif


#endif

