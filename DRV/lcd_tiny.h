
/*! \file  lcd_tiny.h
\brief     ��ʾ������  
\author   zl
*/

#ifndef LCD_TINY
#define LCD_TINY

#define LCD_DRIVER_NAME				"/dev/lcd"

#define LCD_WIDTH				192
#define LCD_HEIGHT				64
#define LCD_DATA_BIT				8	//LCD����λ��
#ifdef __cplusplus
extern "C"
{ 
#endif
#define DISP_BUFFER_SIZE		(LCD_WIDTH*LCD_HEIGHT/LCD_DATA_BIT)

#define LCD_DISP_UNIT_MODE			1	

#define CHN_FONT_SIZE		12
#define USE_CHNFONT_FILE	1
	

/*
* Common define
*/
#define UINT32		unsigned int

/*IOCTLs define*/
#define IOCTLSETCURSOR						_IOW('v', 1, UINT32)	//set cursor position
#define IOCTLSETSTARTLINE					_IOW('v', 2, UINT32)	//set display-start line in display buffer
#define IOCTLREADSTATUS						_IOW('v', 3, UINT32)	//read lcd module status
#define IOCTLDISPLAYON						_IOW('v', 4, UINT32)	//display on
#define IOCTLDISPLAYOFF						_IOW('v', 5, UINT32)	//display off
#define IOCTLCLEARSCREEN					_IOW('v', 6, UINT32)	//clear screen
#define IOCTLCLEARPARTOFSCREEN					_IOW('v', 7, UINT32)	//clear part of screen
#define IOCTLFILLPARTOFSCREEN					_IOW('v', 8, UINT32)	//display off
#define IOCTLBKLON						_IOW('v', 9, UINT32)	//clear screen
#define IOCTLBKLOFF						_IOW('v', 10, UINT32)	//clear part of screen
#define IOCTLREDRAWSCREEN					_IOW('v', 11, UINT32)	//refresh screen

#ifndef WIN32

/*!
@brief   ���ݻ�����Ϣˢ������LCD��
*/
void LCDRedraw();
/*!
@brief   ��ʼ��LCD
*/
void LCD_Init(void);
/*!
@brief		������
@param [in] x0 �������ϵ������
@param [in] y0 �������ϵ�������
@param [in] w  ���ο��
@param [in] h  ���θ߶�
@param [in] color 1��ʾ��0����   
*/
void LCDFillRect(int x0, int y0, int w, int h, int color);
/*!
@brief		�����α߿�
@param [in] x0 �������ϵ������
@param [in] y0 �������ϵ�������
@param [in] w  ���ο��
@param [in] h  ���θ߶�
@param [in] color 1��ʾ��0����  
*/
void LCDFillRectLine(int x0, int y0, int w, int h, int color);

/*!
@brief		���ͼ����Ϣ���������뺺����Ϣ�ȣ�
@param [in] x0  �������ϵ������
@param [in] y0  �������ϵ�������
@param [in] w   ���ο��
@param [in] h   ���θ߶�
@param [in] buf ͼ����Ϣ
*/
void LCDPutImage(int x0, int y0, int w, int h, char *buf);
/*!
@brief		��ɫ���ͼ����Ϣ���������뺺����Ϣ�ȣ�
@param [in] x0  �������ϵ������
@param [in] y0  �������ϵ�������
@param [in] w   ���ο��
@param [in] h   ���θ߶�
@param [in] buf ͼ����Ϣ 
*/
void LCDPutImageRev(int x0, int y0, int w, int h, char *buf);
/*!
@brief		 ����������Һ�����е�����(x,y)���û����ж�Ӧ��λ
@param [in]  x  ������
@param [in]  y  ������
@param [in]  c 1��ʾ��0����ʾ 
*/
void putpixel( int x, int y, int c );
/*!
@brief  ����
*/
void LCDClearDisplay(void);
/*!
@brief ������ 
*/
void LCDBlkOn();
/*!
@brief �ر��� 
*/
void LCDBlkOff();

/*!
@brief		 ����������Һ�����е�����(x,y)��λ�����ж�Ӧ��λ
@param [in]  x ������
@param [in]  y ������
@param [in]  row  ��Ӧ���б��
@param [in]  col  ��Ӧ���б��
@param [in]  Bit  ��Ӧ���ֽ���λ���
*/
static void LocateInBuff( int x, int y, int *row, int *col, int *Bit );
#endif

/****add by nhp****/
/*!
@brief ���⿪�� 
*/
void WB_LCM_BKL_ON(void);
/*!
@brief ����ر�  
*/
void WB_LCM_BKL_OFF(void);
/*!
@brief ����״̬
@return  ����״ֵ̬				
*/
int WB_LCM_BKL_STATUS(void);
/*!
@brief ����״̬����
@return  ����״̬����ֵ
*/
void WB_LCM_BKL_ADD(void);
/****add by nhp****/

#ifdef __cplusplus     
}
#endif

#endif  /* LCD_TINY */
