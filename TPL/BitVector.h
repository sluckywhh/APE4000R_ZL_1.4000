/*! \file    BitVector.h
\brief    ��ά���ӡ�ײ㺯��
\author   gaoyang
 */

#ifndef BITVECTOR_H
#define BITVECTOR_H

#include "TPLModuleHeader.h"

#if (PRINT_BIZNFO!=0)

#ifdef __cplusplus
extern "C"
{
#endif
	typedef unsigned char BitWord;
	enum { BITWORD_SIZE = (unsigned)sizeof(BitWord) * 8 };
    extern unsigned char bitVectorBuffer[10*1024];
	//bitvector
	typedef struct BITVECTOR
	{
		unsigned char *m_bits;
		int m_size;
		int m_idProjector[2];
		int m_maxCoordinates[2];

		//����id��ȡλֵ
		int (* readByID)(void *pHandle,int id);
		//���������ȡλֵ
		int (* read)(void *pHandle,int row,int col);
		//����id����λֵ
		void (* writeByID)(void *pHandle, int id, int value);
		//������������λֵ
		void (* write)(void *pHandle, int row,int col, int value);
		//����λ����λ
		void (* setAll)(void *pHandle,int value);
		//��ʼ������λΪֵ0
		void (* init)(void *pHandle,int row,int col);
		//���λͼ�Ƿ����id
		int (* containsByID)(void *pHandle,int id);
		//���λͼ�Ƿ��������
		int (* contains)(void *pHandle,int row,int col);
		//������õ�ID
		int (* getIdFromVector)(void *pHandle, int row,int col);
		//��ID�õ�����
		void (* setVectorFromId)(void *pHandle, int id, int row,int col);

	}BitVector;


#define BITVECTOR_DEFAULT {bitVectorBuffer,\
	0,\
	{0,0},\
	{0,0},\
	readByID_Fun,\
	read_Fun,\
		writeByID_Fun,\
		write_Fun,\
		setAll_Fun,\
		init_Fun,\
		containsByID_Fun,\
		contains_Fun,\
		getIdFromVector_Fun,\
		setVectorFromId_Fun}

		//����id��ȡλֵ
		int readByID_Fun(void *pHandle,int id);
		//���������ȡλֵ
		int read_Fun(void *pHandle,int row,int col);
		//����id����λֵ
		void writeByID_Fun(void *pHandle, int id, int value);
		//������������λֵ
		void write_Fun(void *pHandle, int row,int col, int value);
		//����λ����λ
		void setAll_Fun(void *pHandle,int value);
		//��ʼ������λΪֵ0
		void init_Fun(void *pHandle,int row,int col);
		//���λͼ�Ƿ����id
		int containsByID_Fun(void *pHandle,int id);
		//���λͼ�Ƿ��������
		int contains_Fun(void *pHandle,int row,int col);
		//��ȡidλ�õ�dimension����
		int getCoord_Fun(void *pHandle,int id, int dimenson);
		//������õ�ID
		int getIdFromVector_Fun(void *pHandle, int row,int col);
		//��ID�õ�����
		void setVectorFromId_Fun(void *pHandle, int id, int row,int col);


		int BitmapTranse_old(unsigned char * imgData, int imgWidth, int imgHeight, int pixelNum, unsigned char * output, int *outWidth,int *outHeight);
		int BitmapTranse(unsigned char * imgData, int imgWidth, int imgHeight, unsigned char * output, int *outWidth,int *outHeight, double length);			
			
#ifdef __cplusplus
};
#endif

#endif	//PRINT_BIZNFO

#endif