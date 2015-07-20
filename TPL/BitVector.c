/*! \file    BitVector.c
\brief    ��ά���ӡ�ײ㺯��ʵ��
\author   gaoyang
 */

#include "BitVector.h"


#if (PRINT_BIZNFO!=0)

unsigned char bitVectorBuffer[10*1024];
int indexMatrix[300][300];

//����id��ȡλֵ
int readByID_Fun(void *pHandle,int id)
{
	BitVector *pBitVector = (BitVector *)pHandle;
	BitWord Mask = 1 << (BITWORD_SIZE -1 - id % BITWORD_SIZE);
    if ((pBitVector->m_bits[id / BITWORD_SIZE] & Mask) != 0)
		return 1;
	else
		return 0;
     
}
//���������ȡλֵ
int read_Fun(void *pHandle,int row,int col)
{
	BitVector *pBitVector = (BitVector *)pHandle;
	int id = pBitVector->getIdFromVector(pBitVector, row, col);
	BitWord Mask = 1 << (BITWORD_SIZE -1 - id % BITWORD_SIZE);
    if ((pBitVector->m_bits[id / BITWORD_SIZE] & Mask) != 0)
		return 1;
	else
		return 0;

}
//����id����λֵ
void writeByID_Fun(void *pHandle, int id, int value)
{
	BitVector *pBitVector = (BitVector *)pHandle;
	if (value == 1)
		pBitVector->m_bits[id / BITWORD_SIZE] |= 1 << (BITWORD_SIZE -1 - id % BITWORD_SIZE);
	else
		pBitVector->m_bits[id / BITWORD_SIZE] &= ~(1 << (BITWORD_SIZE -1 - id % BITWORD_SIZE));	   
}

//������������λֵ
void write_Fun(void *pHandle, int row,int col, int value)
{
	BitVector *pBitVector = (BitVector *)pHandle;
	int id = pBitVector->getIdFromVector(pBitVector, row, col);
	if (value == 1)
		pBitVector->m_bits[id / BITWORD_SIZE] |= 1 << (BITWORD_SIZE -1 - id % BITWORD_SIZE);
	else
		pBitVector->m_bits[id / BITWORD_SIZE] &= ~(1 << (BITWORD_SIZE -1 - id % BITWORD_SIZE));
}
//����λ����λ
void setAll_Fun(void *pHandle,int value)
{
	BitVector *pBitVector = (BitVector *)pHandle;
	int i;

	for (i=0; i<((pBitVector->m_size+BITWORD_SIZE-1)/BITWORD_SIZE); i++)
	{
		if (value == 0)
			pBitVector->m_bits[i] = 0x00;
		else
			pBitVector->m_bits[i] = 0xFF;		
	}

}
//��ʼ������λΪֵ0
void init_Fun(void *pHandle,int rowLen,int colLen)
{
	BitVector *pBitVector = (BitVector *)pHandle;
	pBitVector->m_size = rowLen * colLen;

	pBitVector->m_idProjector[0]=1;
	pBitVector->m_idProjector[1]=rowLen;

	pBitVector->m_maxCoordinates[0] = colLen;
	pBitVector->m_maxCoordinates[1] = rowLen;

}
//���λͼ�Ƿ����id
int containsByID_Fun(void *pHandle,int id)
{
	BitVector *pBitVector = (BitVector *)pHandle;
	if (id < pBitVector->m_size)
		return 1;
	else
		return 0;
}
//���λͼ�Ƿ��������
int contains_Fun(void *pHandle,int row,int col)
{
	BitVector *pBitVector = (BitVector *)pHandle;
	if (row >= pBitVector->m_maxCoordinates[1])
		return 0;
	else
		return 1;

	if (col >= pBitVector->m_maxCoordinates[0])
		return 0;
	else
		return 1;
}

//������õ�ID
int getIdFromVector_Fun(void *pHandle, int row,int col)
{
	int id;
	BitVector *pBitVector = (BitVector *)pHandle;
	id = row * pBitVector->m_idProjector[0] + col * pBitVector->m_idProjector[1];
	return id;
}
//��ID�õ�����
void setVectorFromId_Fun(void *pHandle, int id, int row,int col)
{
	BitVector *pBitVector = (BitVector *)pHandle;
	row = id % pBitVector->m_idProjector[0];
	col = id / pBitVector->m_idProjector[1];
}


int BitmapTranse_old(unsigned char * imgData, int imgWidth, int imgHeight, int pixelNum, unsigned char * output, int *outWidth,int *outHeight)
{
	int i,j,k;
	int ii,jj;
	int rowSum = 0;
	int colSum = 0;
	BitVector bitmap = BITVECTOR_DEFAULT;
	int pixelHeight;//���س���
	int pixelWidth;//���ؿ��

	int rowLen = 0;
	int colLen = 0;
/*	int colLen = (imgWidth/2* (pixelNum+1)) +(imgWidth - imgWidth/2)*pixelNum;*/
	for (i=0; i<imgHeight; i++)
	{
		if (i%10 == 0)
			colLen +=pixelNum;
		else
			colLen += pixelNum+1;
	}
/*	int colLen = imgWidth* (pixelNum+1);*/
	int pos = 0;
	unsigned char tmpCharUp=0;
	unsigned char tmpCharDown=0;
	for (i=0; i<imgHeight; i++)
	{
		if (i%3 == 0)
			rowLen +=pixelNum+1;
		else
			rowLen += pixelNum;
	}
	printf("realrowLen =%d",rowLen);
	rowLen = ((rowLen+ 15)/16)*16;

	bitmap.init((void *)&bitmap, rowLen, colLen);
	printf("rowLen =%d colLen = %d\n",rowLen,colLen);
	bitmap.setAll((void *)&bitmap, 0);
	pixelWidth = pixelNum+1;
	for(i = 0; i < imgHeight; i++)
	{
		colSum = 0;
		if (i%3 == 0)
			pixelHeight = pixelNum+1;
		else
			pixelHeight = pixelNum;

		for (j = 0; j < imgWidth; j++)
		{
			if (j%10 == 0)
				pixelWidth = pixelNum;
			else
				pixelWidth = pixelNum+1;

			for (ii = rowSum; ii < rowSum + pixelHeight; ii++)
			{
				for (jj = colSum; jj < colSum + pixelWidth; jj++)
				{
					if (*(imgData + i*imgWidth + j) == 1 )
						bitmap.write((void *)&bitmap, ii, jj, 1);
					else
						bitmap.write((void *)&bitmap, ii, jj, 0);
				}
			}
			colSum = colSum + pixelWidth;				
		}
		rowSum = rowSum + pixelHeight;			
	}



// 	for (i=0; i<rowLen/8; i++)
// 	{
// 		for (j=0; j<colLen; j++)
// 		{
// 			*(output+pos++) = bitmap.m_bits[j*rowLen/8 +i];
// 		}
// 		
// 	}
	pos = rowLen/8*colLen;//�����ֽ���


	*outWidth = colSum;
	*outHeight = pos*8/colSum;

	for (i=0; i<(* outHeight)/8; i+=2)
	{
		for (j=0; j<*outWidth; j++)
		{
			tmpCharUp = 0x00;
			for (k=0;k<8;k+=2)
			{
				//��������λ
				 tmpCharUp |= bitmap.read((void *)&bitmap,i*8+k,j)<<(7-k/2);	
				//��������λ
				 tmpCharUp |= bitmap.read((void *)&bitmap,(i+1)*8+k,j)<<(3-k/2);
			}
			output[i*(*outWidth)+j]= tmpCharUp;
			
			tmpCharDown = 0x00;
			for (k=1;k<8;k+=2)
			{
				//ż������λ
				tmpCharDown |= bitmap.read((void *)&bitmap,i*8+k,j)<<(7-(k-1)/2);	
				//ż������λ
				tmpCharDown |= bitmap.read((void *)&bitmap,(i+1)*8+k,j)<<(3-(k-1)/2);
			}
			output[(i+1)*(*outWidth)+j]= tmpCharDown;
		}
	}

	return 1;
}




int BitmapTranse(unsigned char * imgData, int imgWidth, int imgHeight, unsigned char * output, int *outWidth,int *outHeight, double length)
{
	int i,j,k;
	int ii,jj;
	int starRow = 0;
	int endRow = 0;
	int starCol = 0;
	int endCol = 0;
	BitVector bitmap = BITVECTOR_DEFAULT;
	int rowLen = 0;
	int colLen = 0;
	//�������
	rowLen = (int)(length*10 /0.176);
	colLen = (int)(length*10 /0.151);
	printf("rowLen =%d colLen = %d\n",rowLen,colLen);
	unsigned char tmpCharUp=0;
	unsigned char tmpCharDown=0;

	//ÿ������ռ�ݵ�������
	double rowPixel = (double)rowLen / (double)imgHeight;
	double colPixel = (double)colLen / (double)imgWidth;
	
	//�����±����
	for(i = 0; i < imgHeight; i++)
	{
		endRow=(int)((i+1) * rowPixel);
		starCol =0;
		for (j = 0; j < imgWidth; j++)
		{
			endCol = (int)((j+1) * colPixel);
			for (ii = starRow; ii < endRow; ii++)
			{
				for (jj = starCol; jj < endCol; jj++)
				{
					indexMatrix[ii][jj] = i*imgWidth + j;
				}
			}
			starCol = endCol;
			
		}
		starRow = endRow;			
	}

	//����Ŀ��������
	int adjustRowLen = (rowLen +15)/16 *16;//����16�ı���

	bitmap.init((void *)&bitmap, adjustRowLen, colLen);
	printf("adjustRowLen =%d colLen = %d\n",adjustRowLen,colLen);
	bitmap.setAll((void *)&bitmap, 0);

	int	pos = adjustRowLen/8*colLen;//�����ֽ���
	int flag = 0;//
	
	for (i = 0; i < rowLen; i++)
	{
		for (j=0; j< colLen;j++)
		{
			flag = *(imgData + indexMatrix[i][j]);
			if (flag == 0)
				bitmap.write((void *)&bitmap, i, j, 0);	
			else
				bitmap.write((void *)&bitmap, i, j, 1);
		}
	}

	//��ż��װ
	for (i=0; i<adjustRowLen/8; i+=2)
	{
		for (j=0; j<colLen; j++)
		{
			tmpCharUp = 0x00;
			for (k=0;k<8;k+=2)
			{
				//��������λ
				 tmpCharUp |= bitmap.read((void *)&bitmap,i*8+k,j)<<(7-k/2);	
				//��������λ
				 tmpCharUp |= bitmap.read((void *)&bitmap,(i+1)*8+k,j)<<(3-k/2);
			}
			output[i*(colLen)+j]= tmpCharUp;
			
			tmpCharDown = 0x00;
			for (k=1;k<8;k+=2)
			{
				//ż������λ
				tmpCharDown |= bitmap.read((void *)&bitmap,i*8+k,j)<<(7-(k-1)/2);	
				//ż������λ
				tmpCharDown |= bitmap.read((void *)&bitmap,(i+1)*8+k,j)<<(3-(k-1)/2);
			}
			output[(i+1)*(colLen)+j]= tmpCharDown;
		}
	}

	*outWidth = colLen;
	*outHeight = adjustRowLen;
	return 1;
}

#endif		//#if (PRINT_BIZNFO!=0)






