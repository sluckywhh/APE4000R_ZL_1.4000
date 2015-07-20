
/*! \file   vfd.h
   \brief   ��������
   \author 
*/
#ifndef LED_VFD_POS_H
#define LED_VFD_POS_H


#ifdef __cplusplus
extern "C"
{
#endif

#ifndef WIN32                      

#define VFD_MAGIC 'd'

#define VFD_INIT               _IO(VFD_MAGIC, 0)
#define VFD_SET_SPEED          _IOW(VFD_MAGIC, 1, int)
#define VFD_WRITE_BYTE         _IOW(VFD_MAGIC, 2, int)
#define VFD_WRITE_STR          _IOW(VFD_MAGIC, 3, int)
#define VFD_CLEAR              _IO(VFD_MAGIC, 4)

#define VFD_MAXNR  4
	
#endif	//WIN32

/*!
@brief   ��ʼ��SPI  
*/
void SPI_Init(void);


void SPI_SET_SPEED(int spd);

/*!
@brief     ��������  
@param[in] �����ַ�   
*/
void SPI_WRITE_STR(char *str);


void SPI_WRITE_BYTE(char data);

/*!
@brief  �ͷſ��� 
*/
void SPI_Release(void);


#ifdef __cplusplus
}
#endif

#endif
